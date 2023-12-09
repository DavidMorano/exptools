/*ident	"@(#)C++env:incl-master/proto-headers/dirent.h	1.2" */

#ifndef __DIRENT_H
#define __DIRENT_H

#define opendir ______opendir
#define readdir ______readdir
#define telldir ______telldir
#define seekdir ______seekdir
#define closedir ______closedir

/*	@(#)dirent.h 1.3 88/02/07 SMI 	*/

/*
 * Filesystem-independent directory information. 
 */

#define	MAXNAMLEN	255

#define d_ino	d_fileno		/* compatability */

/*
 * Definitions for library routines operating on directories.
 */
typedef struct _dirdesc {
	int	dd_fd;			/* file descriptor */
	long	dd_loc;             /* buf offset of entry from last readddir() */
	long	dd_size;		/* amount of valid data in buffer */
	long	dd_bsize;		/* amount of entries read at a time */
	long	dd_off;             	/* Current offset in dir (for telldir) */
	char	*dd_buf;		/* directory data buffer */
} DIR;

#ifndef NULL
#define NULL 0
#endif
extern	DIR *opendir();
extern	struct dirent *readdir();
extern	long telldir();
extern	void seekdir();
#define rewinddir(dirp)	seekdir((dirp), (long)0)
extern	int closedir();

#include <sys/dirent.h>
 

#undef telldir
#undef closedir
#undef opendir
#undef readdir
#undef seekdir

extern "C" {
	DIR *opendir(const char*);
	struct dirent *readdir(DIR*);
	long telldir(DIR*);
	void seekdir(DIR*, long);
	void closedir(DIR*);
#ifndef rewinddir
	void rewinddir(DIR*);
#endif
}

#endif
