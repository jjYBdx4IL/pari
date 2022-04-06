
cmake_minimum_required(VERSION 3.22)
project(pari VERSION 2.13.3 LANGUAGES C)

if(MSVC)
    add_compile_options(/MP)
    #set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:CONSOLE")
endif()

include_directories(src/headers .)

file(GLOB SRC_BASEMATH src/basemath/*.c)
file(GLOB HEADERS src/headers/*.h)
file(GLOB HEADERS_ASM src/kernel/ix86/*.h)
list(APPEND HEADERS_ASM src/kernel/none/level1.h)
file(GLOB SRC_LANGUAGE src/language/*.c src/language/*.h)
file(GLOB SRC_MODULES src/modules/*.c src/modules/*.h)
list(APPEND SRC_GRAPH "src/graph/plotnone.c;src/graph/plotport.c")
#list(APPEND SRC_GRAPH "src/graph/plotnone.c")
file(GLOB SRC_GP src/gp/*.c src/gp/*.h)
list(FILTER SRC_GP EXCLUDE REGEX "^.*/(gp|gp_rl)\\.[ch]$")
message(STATUS "SRC_GP=${SRC_GP}")



add_library(libpari STATIC ${SRC_BASEMATH} ${SRC_LANGUAGE} ${SRC_MODULES} ${SRG_GP} ${SRC_GRAPH} src/mt/single.c)

#add_executable(gp src/gp/gp.c)
#target_link_libraries(gp PRIVATE pari)


# 5. Select "Project\Add to project\Files..." to add files to the project.
# Select all the *.c and *.h files in src\basemath, src\headers,
# src\kernel\ix86, src\language, src\modules and Odos, EXCEPT pariCE.[ch];
# all of the files in src\gp except gp_rl.c; the files plotnull.c, plotport.c
# and rect.h in src\graph.c; and the file src\kernel\none\mp.c.



include(CTest)
set_property(GLOBAL PROPERTY CTEST_TARGETS_ADDED 1)
enable_testing()

add_executable (testlinking testlinking.c)
target_link_libraries(testlinking libpari)
add_test(testlinking testlinking)

if(MSVC)
    target_compile_definitions(testlinking PRIVATE _USE_MATH_DEFINES)
endif()
