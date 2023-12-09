/*ident	"@(#)C++env:incl-master/proto-headers/sys/timeb.h	1.1" */

#ifndef __TIMEB_H
#define __TIMEB_H

/*	@(#)timeb.h 2.5 88/02/08 SMI; from UCB 4.2 81/02/19	*/

/*
 * Structure returned by ftime system call
 */
struct timeb
{
	time_t	time;
	unsigned short millitm;
	short	timezone;
	short	dstflag;
};
 


extern "C" {
	int ftime(struct timeb *);
}
#endif
