
#define SHORTCODE
#define JOBS
#define LIST
#define STAB

#define MINN  3
#define MAXN 99
#define MINK  2
#define MAXK  9
#define MINT  3
#define MAXT  9

#define NOTSET 127
#define COUNTSTEP 100

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __unix__
#include <sys/times.h>
#include <time.h>
#include <limits.h>
#else
#include <time.h>
#define DOSTIME
#endif

/* The CPU-time code below modified by Brendan McKay */

#ifdef CLK_TCK
#define time_factor CLK_TCK
#else

#ifdef sun /* Sun */
#define time_factor 60
#endif

#ifdef __dec /* DEC */
#define time_factor 60
#endif

#ifdef __ultrix /* DEC */
#define time_factor 60
#endif        /* thanks to Gunnar */

#endif /* else part of #ifdef CLK_TCK */

#ifdef time_factor
#define UNIXTIME
#endif

#ifdef DOSTIME
#define time_factor CLK_TCK
#endif

#ifdef SHORTCODE
#define APP "scd"
#else
#define APP "lst"
#endif

typedef int SCHAR;
typedef unsigned long ULONG;
typedef unsigned int UINT;

