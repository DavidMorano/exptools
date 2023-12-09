/*ident	"@(#)C++env:incl-master/proto-headers/sgtty.h	1.1" */

#ifndef __SGTTY_H
#define __SGTTY_H

/*	@(#)sgtty.h 1.6 88/02/07 SMI; from UCB 4.2 85/01/03	*/

#ifndef	_IOCTL_
#include <sys/ioctl.h>
#endif
 


extern "C" {
	int stty(int, struct sgttyb *);
	int gtty(int, struct sgttyb *);
}

#endif
