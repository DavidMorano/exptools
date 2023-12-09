/*ident	"@(#)C++env:incl-master/proto-headers/ndbm.h	1.1" */

#ifndef __NDBM_H
#define __NDBM_H

#define dbm_open ______dbm_open
#define dbm_close ______dbm_close
#define dbm_fetch ______dbm_fetch
#define dbm_firstkey ______dbm_firstkey
#define dbm_nextkey ______dbm_nextkey
#define dbm_forder ______dbm_forder
#define dbm_delete ______dbm_delete
#define dbm_store ______dbm_store

/*
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	 @(#)ndbm.h 1.3 88/02/07 SMI; from UCB 4.3 5/30/85
 */

/*
 * Hashed key data base library.
 */
#define PBLKSIZ 1024
#define DBLKSIZ 4096

typedef struct {
	int	dbm_dirf;		/* open directory file */
	int	dbm_pagf;		/* open page file */
	int	dbm_flags;		/* flags, see below */
	long	dbm_maxbno;		/* last ``bit'' in dir file */
	long	dbm_bitno;		/* current bit number */
	long	dbm_hmask;		/* hash mask */
	long	dbm_blkptr;		/* current block for dbm_nextkey */
	int	dbm_keyptr;		/* current key for dbm_nextkey */
	long	dbm_blkno;		/* current page to read/write */
	long	dbm_pagbno;		/* current page in pagbuf */
	char	dbm_pagbuf[PBLKSIZ];	/* page file block buffer */
	long	dbm_dirbno;		/* current block in dirbuf */
	char	dbm_dirbuf[DBLKSIZ];	/* directory file block buffer */
} DBM;

#define _DBM_RDONLY	0x1	/* data base open read-only */
#define _DBM_IOERR	0x2	/* data base I/O error */

#define dbm_rdonly(db)	((db)->dbm_flags & _DBM_RDONLY)

#define dbm_error(db)	((db)->dbm_flags & _DBM_IOERR)
	/* use this one at your own risk! */
#define dbm_clearerr(db)	((db)->dbm_flags &= ~_DBM_IOERR)

/* for flock(2) and fstat(2) */
#define dbm_dirfno(db)	((db)->dbm_dirf)
#define dbm_pagfno(db)	((db)->dbm_pagf)

typedef struct {
	char	*dptr;
	int	dsize;
} datum;

/*
 * flags to dbm_store()
 */
#define DBM_INSERT	0
#define DBM_REPLACE	1

DBM	*dbm_open();
void	dbm_close();
datum	dbm_fetch();
datum	dbm_firstkey();
datum	dbm_nextkey();
long	dbm_forder();
int	dbm_delete();
int	dbm_store();
 

#undef dbm_store
#undef dbm_fetch
#undef dbm_nextkey
#undef dbm_delete
#undef dbm_firstkey
#undef dbm_close
#undef dbm_open
#undef dbm_forder

extern "C" {
	DBM	*dbm_open(const char*, int, int);
	long	dbm_forder(DBM*, datum);
	int	dbm_store(DBM*, datum, datum, int);
	int	dbm_delete(DBM*, datum);
	int	dbm_close(DBM*);
	datum	dbm_firstkey(DBM*);
	datum	dbm_nextkey(DBM*);
	datum	dbm_fetch(DBM*, datum);
}

#endif
