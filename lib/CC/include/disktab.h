/*ident	"@(#)C++env:incl-master/proto-headers/disktab.h	1.1" */

#ifndef __DISKTAB_H
#define __DISKTAB_H

#define getdiskbyname ______getdiskbyname

/*
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 */

/*	@(#)disktab.h 1.9 88/02/07 SMI; from UCB 5.2 10/01/85	*/

/*
 * Disk description table, see disktab(5)
 */
#define	DISKTAB		"/etc/disktab"

struct	disktab {
	char	*d_name;		/* drive name */
	char	*d_type;		/* drive type */
	int	d_secsize;		/* sector size in bytes */
	int	d_ntracks;		/* # tracks/cylinder */
	int	d_nsectors;		/* # sectors/track */
	int	d_ncylinders;		/* # cylinders */
	int	d_rpm;			/* revolutions/minute */
	struct	partition {
		int	p_size;		/* #sectors in partition */
		short	p_bsize;	/* block size in bytes */
		short	p_fsize;	/* frag size in bytes */
	} d_partitions[8];
	u_short d_apc;			/* alternates per cylinder */
	int	d_badsectforw;		/* supports DEC bad144 std */
	int	d_sectoffset;		/* use sect rather than cyl offsets */
};

struct	disktab *getdiskbyname();
 

#undef getdiskbyname

extern "C" {
	disktab *getdiskbyname(const char*);
}

#endif
