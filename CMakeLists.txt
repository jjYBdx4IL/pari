
cmake_minimum_required(VERSION 3.22)
project(pari VERSION 2.13.3 LANGUAGES C)

if(MSVC)
    add_compile_options(/MP)
    #set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:CONSOLE")
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/src/headers ${CMAKE_CURRENT_SOURCE_DIR}/src)

file(GLOB SRC_BASEMATH src/basemath/*.c)
file(GLOB HEADERS src/headers/*.h)
file(GLOB HEADERS_ASM src/kernel/ix86/*.h)
list(APPEND HEADERS_ASM src/kernel/none/level1.h)
file(GLOB SRC_LANGUAGE src/language/*.c src/language/*.h)
file(GLOB SRC_MODULES src/modules/*.c src/modules/*.h)
list(APPEND SRC_GRAPH src/graph/plotnone.c src/graph/plotport.c src/graph/plottty.c)
file(GLOB SRC_GP src/gp/*.c src/gp/*.h)
list(FILTER SRC_GP EXCLUDE REGEX "^.*/(gp|gp_rl)\\.[ch]$")
message(STATUS "SRC_GRAPH=${SRC_GRAPH}")

# gen parilvl0.h
execute_process(COMMAND bash ./config/genkernel src src/kernel/x86_64/asm0.h
    OUTPUT_FILE parilvl0.h
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMAND_ERROR_IS_FATAL ANY
)

# gen parilvl1.h
set(PARILVL1_H "${CMAKE_CURRENT_SOURCE_DIR}/parilvl1.h")
file(REMOVE "${PARILVL1_H}")
foreach(SRC src/kernel/gmp/tune.h src/kernel/gmp/int.h src/kernel/none/level1.h)
    file(READ ${SRC} contents)
    #string(REGEX REPLACE "^(#line [0-9]+ \")\\.\\./" "\\1${CMAKE_CURRENT_SOURCE_DIR}/" contents "${contents}")
    #string(REGEX REPLACE "^(#line [0-9]+ \"[^\"]*\")" "" contents "${contents}")
    file(APPEND ${PARILVL1_H} "${contents}")
endforeach()

# gen parimt.h
file(COPY src/mt/single.h DESTINATION parimt.h)

# gen mpker.c
set(MPKER_C "${CMAKE_CURRENT_SOURCE_DIR}/mpker.c")
file(REMOVE "${MPKER_C}")

foreach(SRC src/kernel/none/mp.c src/kernel/none/cmp.c src/kernel/none/gcdll.c 
    src/kernel/none/halfgcd.c src/kernel/none/ratlift.c  src/kernel/none/invmod.c 
    src/kernel/none/gcd.c src/kernel/none/gcdext.c src/kernel/none/mp_indep.c src/kernel/none/add.c)
    file(READ ${SRC} contents)
    #string(REGEX REPLACE "^(#line [0-9]+ \")\\.\\./" "\\1${CMAKE_CURRENT_SOURCE_DIR}/" contents "${contents}")
    #string(REGEX REPLACE "^(#line [0-9]+ \"[^\"]*\")" "" contents "${contents}")
    file(APPEND ${MPKER_C} "${contents}")
endforeach()

# gen mpinl.h
set(MPINL_H "${CMAKE_CURRENT_SOURCE_DIR}/mpinl.h")
file(REMOVE "${MPINL_H}")

foreach(SRC parilvl0.h parilvl1.h)
    file(READ ${SRC} contents)
    file(APPEND ${MPINL_H} "${contents}")
endforeach()



add_library(libpari STATIC ${SRC_BASEMATH} ${SRC_LANGUAGE} ${SRC_MODULES} ${SRG_GP}
    ${SRC_GRAPH} ${MPKER_C} ${HEADERS} src/mt/single.c paricfg.h src/mt/mt.c src/kernel/none/mpinl.c)

#add_executable(gp src/gp/gp.c)
#target_link_libraries(gp PRIVATE pari)



include(CTest)
set_property(GLOBAL PROPERTY CTEST_TARGETS_ADDED 1)
enable_testing()

add_executable (testlinking testlinking.c)
target_link_libraries(testlinking libpari)
add_test(testlinking testlinking)

#if(MSVC)
#    target_compile_definitions(testlinking PRIVATE _USE_MATH_DEFINES)
#endif()
