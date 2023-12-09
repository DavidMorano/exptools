/*ident	"@(#)C++env:incl-master/proto-headers/sys/resource.h	1.1" */

#ifndef __RESOURCE_H
#define __RESOURCE_H

#ifndef __SYS_TIME_H
#include <sys/time.h>
#endif

#define getpriority ______getpriority
#define setpriority ______setpriority
#define getrlimit ______getrlimit
#define setrlimit ______setrlimit
#define getrusage ______getrusage

/*	@(#)resource.h 2.7 88/03/10 SMI; from UCB 4.1 83/02/10	*/

#ifndef	_sys_resource_h
#define	_sys_resource_h

/*
 * Process priority specifications to get/setpriority.
 */
#define	PRIO_MIN	-20
#define	PRIO_MAX	20

#define	PRIO_PROCESS	0
#define	PRIO_PGRP	1
#define	PRIO_USER	2

/*
 * Resource utilization information.
 */

#define	RUSAGE_SELF	0
#define	RUSAGE_CHILDREN	-1

struct	rusage {
	struct timeval ru_utime;	/* user time used */
	struct timeval ru_stime;	/* system time used */
	long	ru_maxrss;
#define	ru_first	ru_ixrss
	/*
	 * XXX: In 4.0, all three ru_i?rss fields are combined
	 *	and presented in idrss; ixrss and isrss are zero
	 */
	long	ru_ixrss;		/* integral shared memory size */
	long	ru_idrss;		/* integral unshared data " */
	long	ru_isrss;		/* integral unshared stack " */
	long	ru_minflt;		/* page reclaims */
	long	ru_majflt;		/* page faults */
	long	ru_nswap;		/* swaps */
	long	ru_inblock;		/* block input operations */
	long	ru_oublock;		/* block output operations */
	long	ru_msgsnd;		/* messages sent */
	long	ru_msgrcv;		/* messages received */
	long	ru_nsignals;		/* signals received */
	long	ru_nvcsw;		/* voluntary context switches */
	long	ru_nivcsw;		/* involuntary " */
#define	ru_last		ru_nivcsw
};

/*
 * Resource limits
 */
#define	RLIMIT_CPU	0		/* cpu time in milliseconds */
#define	RLIMIT_FSIZE	1		/* maximum file size */
#define	RLIMIT_DATA	2		/* data size */
#define	RLIMIT_STACK	3		/* stack size */
#define	RLIMIT_CORE	4		/* core file size */
#define	RLIMIT_RSS	5		/* resident set size */

#define	RLIM_NLIMITS	6		/* number of resource limits */

#define	RLIM_INFINITY	0x7fffffff

struct rlimit {
	int	rlim_cur;		/* current (soft) limit */
	int	rlim_max;		/* maximum value for rlim_cur */
};
#endif	_sys_resource_h
 

#undef getrusage
#undef getpriority
#undef getrlimit
#undef setpriority
#undef setrlimit

extern "C" {
	int getpriority(int which, int who);
	int setpriority(int which, int who, int prio);
	int getrlimit(int resource, rlimit* rlp);
	int setrlimit(int resource, const rlimit* rlp);
	int getrusage(int, rusage*);
}

#endif
