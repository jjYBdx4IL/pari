/*  This file was created by Configure. Any change made to it will be lost
 *  next time Configure is run. */
#ifndef __PARICFG_H__
#define __PARICFG_H__

#ifdef _MSC_VER
#pragma warning(disable: 4293 4477 4312 4047 4098)
#define _USE_MATH_DEFINES
#elif !defined(WIN32)
#define UNIX
#endif

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

#define LONG_IS_64BIT

#ifndef LONG_IS_64BIT
#define PARI_DOUBLE_FORMAT 1
#define INDEX0 1
#define INDEX1 0
#else
#define PARI_DOUBLE_FORMAT 2
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
