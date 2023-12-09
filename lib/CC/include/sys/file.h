/*ident	"@(#)C++env:incl-master/proto-headers/sys/file.h	1.1" */

#ifndef __FILE_H
#define __FILE_H

#ifndef __TYPES_H
#include <sys/types.h>
#endif

#define flock ______flock
#define access ______access
#define lseek ______lseek

/*	@(#)file.h 2.12 88/02/08 SMI; from UCB 7.1 6/4/86	*/

/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 */

#ifndef _FILE_
#define _FILE_

#ifdef KERNEL
/*
 * Descriptor table entry.
 * One for each kernel object.
 */
struct	file {
	int	f_flag;		/* see below */
	short	f_type;		/* descriptor type */
	short	f_count;	/* reference count */
	short	f_msgcount;	/* references from message queue */
	struct	fileops {
		int	(*fo_rw)();
		int	(*fo_ioctl)();
		int	(*fo_select)();
		int	(*fo_close)();
	} *f_ops;
	caddr_t	f_data;		/* ptr to file specific struct (vnode/socket) */
	off_t	f_offset;
	struct	ucred *f_cred;	/* credentials of user who opened file */
};

struct	file *file, *fileNFILE;
int	nfile;
struct	file *getf();
struct	file *falloc();
#endif KERNEL

#include <sys/fcntlcom.h>

/*
 * flags - see also fcntlcom.h
 */
#define	FOPEN		(-1)
#define	FREAD		00001		/* descriptor read/receive'able */
#define	FWRITE		00002		/* descriptor write/send'able */
#define	FMARK		00020		/* mark during gc() */
#define	FDEFER		00040		/* defer for next gc pass */
#define	FSHLOCK		00200		/* shared lock present */
#define	FEXLOCK		00400		/* exclusive lock present */

/* bits to save after open */
#define	FMASK		(FREAD|FWRITE|FAPPEND|FSYNC|FASYNC|FNBIO)
#define	FCNTLCANT	(FREAD|FWRITE|FMARK|FDEFER|FSHLOCK|FEXLOCK)

/*
 * User definitions.
 */

/*
 * Flock call.
 */
#define	LOCK_SH		1	/* shared lock */
#define	LOCK_EX		2	/* exclusive lock */
#define	LOCK_NB		4	/* don't block when locking */
#define	LOCK_UN		8	/* unlock */

/*
 * Access call.
 */
#define	F_OK		0	/* does file exist */
#define	X_OK		1	/* is it executable by caller */
#define	W_OK		2	/* writable by caller */
#define	R_OK		4	/* readable by caller */

/*
 * Lseek call.
 */
#define	L_SET		0	/* absolute offset */
#define	L_INCR		1	/* relative to current offset */
#define	L_XTND		2	/* relative to end of file */

#ifdef KERNEL
#define	GETF(fp, fd) { \
	if ((unsigned)(fd) >= NOFILE || ((fp) = u.u_ofile[fd]) == NULL) { \
		u.u_error = EBADF; \
		return; \
	} \
}

#define	DTYPE_VNODE	1	/* file */
#define	DTYPE_SOCKET	2	/* communications endpoint */
#endif KERNEL

#endif !_FILE_
 

#undef access
#undef flock
#undef lseek

extern "C" {
	int flock(int fd, int operation);
	int access(const char*, int);
	off_t lseek(int fd, off_t offset, int whence);
}

#endif
