/*ident	"@(#)C++env:incl-master/proto-headers/utmp.h	1.1" */

#ifndef __UTMP_H
#define __UTMP_H

#define endutent ______endutent
#define getutent ______getutent
#define getutid ______getutid
#define getutline ______getutline
#define pututline ______pututline
#define setutent ______setutent
#define utmpname ______utmpname

/*	@(#)utmp.h 1.7 88/02/07 SMI; from UCB 4.2 83/05/22	*/

/*
 * Structure of utmp and wtmp files.
 *
 * Assuming the number 8 is unwise.
 */
struct utmp {
	char	ut_line[8];		/* tty name */
	char	ut_name[8];		/* user id */
	char	ut_host[16];		/* host name, if remote */
	long	ut_time;		/* time on */
};

/*
 * This is a utmp entry that does not correspond to a genuine user
 */
#define nonuser(ut) ((ut).ut_host[0] == 0 && \
	strncmp((ut).ut_line, "tty", 3) == 0 && ((ut).ut_line[3] == 'p' \
					      || (ut).ut_line[3] == 'q' \
					      || (ut).ut_line[3] == 'r' \
					      || (ut).ut_line[3] == 's'))
 

#undef pututline
#undef getutid
#undef utmpname
#undef endutent
#undef getutline
#undef getutent
#undef setutent

extern "C" {
}

#endif
