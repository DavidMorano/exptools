/*ident	"@(#)C++env:incl-master/proto-headers/sys/uio.h	1.1" */

#ifndef __UIO_H
#define __UIO_H

#define readv ______readv
#define writev ______writev

/*	@(#)uio.h 2.7 88/02/08 SMI; from UCB 7.1 6/4/86	*/

/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 */

#ifndef	_UIO_
#define	_UIO_

struct iovec {
	caddr_t	iov_base;
	int	iov_len;
};

/*
 * The uio_seg define below is obsolete and is included only
 * for compatibility with previous releases.  New code should
 * use the uio_segflg field.
 */
struct uio {
	struct	iovec *uio_iov;
	int	uio_iovcnt;
	off_t	uio_offset;
	short	uio_segflg;
#define	uio_seg	uio_segflg		/* obsolete */
	short	uio_fmode;
	int	uio_resid;
};

enum	uio_rw { UIO_READ, UIO_WRITE };

/*
 * Segment flag values (should be enum).
 *
 * The UIOSEG_* defines are obsolete and are included only
 * for compatibility with previous releases.  New code should
 * use the UIO_* definitions.
 */
#define UIO_USERSPACE	0		/* from user data space */
#define UIO_SYSSPACE	1		/* from system space */
#define UIO_USERISPACE	2		/* from user I space */

#define UIOSEG_USER	0		/* obsolete */
#define UIOSEG_KERNEL	1		/* obsolete */

#endif	_UIO_
 

#undef writev
#undef readv

extern "C" {
	int readv(int, const struct iovec *, int);
	int writev(int, const struct iovec *, int);
}
#endif
