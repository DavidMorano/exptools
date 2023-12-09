/*ident	"@(#)C++env:incl-master/proto-headers/fcntl.h	1.1" */

#ifndef __FCNTL_H
#define __FCNTL_H

#define fcntl ______fcntl

/*	@(#)fcntl.h 1.6 88/02/08 SMI	*/

#ifndef _FCNTL_
#define _FCNTL_

#include <sys/fcntlcom.h>

#define	O_NDELAY	FNDELAY	/* Non-blocking I/O (4.2 style) */

#endif !_FCNTL_
 

#undef fcntl

extern "C" {
	int fcntl(int, int, int);
}
#endif
