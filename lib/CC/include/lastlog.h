/*ident	"@(#)C++env:incl-master/proto-headers/lastlog.h	1.1" */

#ifndef __LASTLOG_H
#define __LASTLOG_H

/*	@(#)lastlog.h 1.5 88/02/07 SMI; from UCB 4.2 83/05/22	*/

struct lastlog {
	time_t	ll_time;
	char	ll_line[8];
	char	ll_host[16];		/* same as in utmp */
};
 


#endif
