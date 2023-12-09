/*ident	"@(#)C++env:incl-master/proto-headers/sys/time.h	1.2" */

#ifndef __SYS_TIME_H
#define __SYS_TIME_H

#ifndef __TYPES_H
#include <sys/types.h>
#endif

#define gmtime ______gmtime
#define localtime ______localtime
#define asctime ______asctime
#define ctime ______ctime
#define tzset ______tzset
#define adjtime ______adjtime
#define getitimer ______getitimer
#define setitimer ______setitimer
#define gettimeofday ______gettimeofday
#define settimeofday ______settimeofday
#define select ______select
#define utimes ______utimes

/*	@(#)time.h 2.10 88/02/08 SMI; from UCB 7.1 6/4/86	*/

/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 */

#ifndef _TIME_
#define _TIME_

/*
 * Structure returned by gettimeofday(2) system call,
 * and used in other calls.
 */
struct timeval {
	long	tv_sec;		/* seconds */
	long	tv_usec;	/* and microseconds */
};

struct timezone {
	int	tz_minuteswest;	/* minutes west of Greenwich */
	int	tz_dsttime;	/* type of dst correction */
};
#define	DST_NONE	0	/* not on dst */
#define	DST_USA		1	/* USA style dst */
#define	DST_AUST	2	/* Australian style dst */
#define	DST_WET		3	/* Western European dst */
#define	DST_MET		4	/* Middle European dst */
#define	DST_EET		5	/* Eastern European dst */
#define	DST_CAN		6	/* Canada */
#define	DST_GB		7	/* Great Britain and Eire */
#define	DST_RUM		8	/* Rumania */
#define	DST_TUR		9	/* Turkey */
#define	DST_AUSTALT	10	/* Australian style with shift in 1986 */

/*
 * Operations on timevals.
 *
 * NB: timercmp does not work for >= or <=.
 */
#define	timerisset(tvp)		((tvp)->tv_sec || (tvp)->tv_usec)
#define	timercmp(tvp, uvp, cmp)	\
	((tvp)->tv_sec cmp (uvp)->tv_sec || \
	 (tvp)->tv_sec == (uvp)->tv_sec && (tvp)->tv_usec cmp (uvp)->tv_usec)
#define	timerclear(tvp)		(tvp)->tv_sec = (tvp)->tv_usec = 0

/*
 * Names of the interval timers, and structure
 * defining a timer setting.
 */
#define	ITIMER_REAL	0
#define	ITIMER_VIRTUAL	1
#define	ITIMER_PROF	2

struct	itimerval {
	struct	timeval it_interval;	/* timer interval */
	struct	timeval it_value;	/* current value */
};

#ifndef KERNEL
#include <time.h>
#endif

#endif !_TIME_
 

#undef localtime
#undef utimes
#undef getitimer
#undef tzset
#undef ctime
#undef gettimeofday
#undef setitimer
#undef adjtime
#undef select
#undef asctime
#undef gmtime
#undef settimeofday

extern "C" {
	int adjtime(const timeval*, timeval*);
	int getitimer(int, itimerval*);
	int setitimer(int, const itimerval*, itimerval*);
	int gettimeofday(timeval*, struct timezone*);
	int settimeofday(const timeval*, const struct timezone*);
	int utimes(const char*, timeval tvp[2]);
	int select(int, fd_set*, fd_set*, fd_set*, const timeval*);
}

#endif
