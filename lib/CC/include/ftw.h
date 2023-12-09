/*ident	"@(#)C++env:incl-master/proto-headers/ftw.h	1.1" */

#ifndef __FTW_H
#define __FTW_H

#define ftw ______ftw

/*	@(#)ftw.h 1.3 88/02/07 SMI; from S5R2 1.1	*/

/*
 *	Codes for the third argument to the user-supplied function
 *	which is passed as the second argument to ftw
 */

#define	FTW_F	0	/* file */
#define	FTW_D	1	/* directory */
#define	FTW_DNR	2	/* directory without read permission */
#define	FTW_NS	3	/* unknown type, stat failed */
 

#undef ftw

extern "C" {
	int ftw(const char *, int (*)(char *, struct stat *, int), int);
}

#endif
