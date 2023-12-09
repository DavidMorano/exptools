/*ident	"@(#)C++env:incl-master/proto-headers/sys/times.h	1.1" */

#ifndef __TIMES_H
#define __TIMES_H

#define times ______times
#define utime ______utime

/*	@(#)times.h 2.5 88/02/08 SMI; from UCB 4.2 81/02/19	*/

/*
 * Structure returned by times()
 */
struct tms {
	time_t	tms_utime;		/* user time */
	time_t	tms_stime;		/* system time */
	time_t	tms_cutime;		/* user time, children */
	time_t	tms_cstime;		/* system time, children */
};
 

#undef times
#undef utime

extern "C" {
	long times(struct tms *);
}
#endif
