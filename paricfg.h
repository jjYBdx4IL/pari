/*  This file was created by Configure. Any change made to it will be lost
 *  next time Configure is run. */
#ifndef __PARICFG_H__
#define __PARICFG_H__
//#define UNIX
#define _USE_MATH_DEFINES
#define GPHELP "\"/usr/local/bin/gphelp\""
#define GPDATADIR "/usr/local/share/pari"
#define SHELL_Q '\''

#define PARIVERSION "GP/PARI CALCULATOR Version 2.13.3 (released)"
#define PARIINFO "amd64 running cygwin (ix86 kernel) 32-bit version"
#define PARI_VERSION_CODE 134403
#define PARI_VERSION(a,b,c) (((a) << 16) + ((b) << 8) + (c))
#define PARI_VERSION_SHIFT 8
#define PARI_VCSVERSION ""
#define PARI_MT_ENGINE "single"

#define PARI_DOUBLE_FORMAT -

#define LONG_IS_64BIT
#ifdef WIN32 // windows uses 32bit longs and 64bit pointers
#undef LONG_IS_64BIT
#endif

// MSVC has no support for variable length stack allocations
#ifdef _MSC_VER
#define VAA(type,var,N) type* var = malloc(sizeof(type) * N)
#define VAA_FREE(var) free(var)
#else
#define VAA(type,var,N) type var[N]
#define VAA_FREE(var)
#endif

/*  Location of GNU gzip program (enables reading of .Z and .gz files). */
#define GNUZCAT
#define ZCAT "/usr/bin/gzip -dc"

#define HAS_EXP2
#define HAS_LOG2
#define HAS_SYSTEM
#define USE_FTIMEFORWALLTIME 1
//#define USE_GETTIMEOFDAY 1
//#define USE_CLOCK_GETTIME 1
#define HAS_GETENV
#define HAS_VSNPRINTF
#define HAS_STRFTIME

#define DL_DFLT_NAME NULL
#endif
