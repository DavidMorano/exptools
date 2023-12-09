/*ident	"@(#)C++env:incl-master/proto-headers/unistd.h	1.1" */

#ifndef __UNISTD_H
#define __UNISTD_H

#ifndef __TYPES_H
#include <sys/types.h>
#endif

#define utime ______utime

/*	@(#)unistd.h 1.3 88/02/07 SMI; from SysV 1.5 */

#include <sys/fcntl.h>

/* Symbolic constants for the "lseek" routine: */
#define	SEEK_SET	0	/* Set file pointer to "offset" */
#define	SEEK_CUR	1	/* Set file pointer to current plus "offset" */
#define	SEEK_END	2	/* Set file pointer to EOF plus "offset" */

/* Path names: */
#define	GF_PATH	"/etc/group"	/* Path name of the "group" file */
#define	PF_PATH	"/etc/passwd"	/* Path name of the "passwd" file */

 

#undef utime

extern "C" {
	int lockf(int, int, long);
	int access (const char*, int);
	int utime(char *, time_t *);
	off_t lseek(int, off_t, int);
}

#endif
