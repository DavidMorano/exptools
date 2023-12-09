/*ident	"@(#)C++env:incl-master/proto-headers/dbm.h	1.1" */

#ifndef __DBM_H
#define __DBM_H

#define fetch ______fetch
#define makdatum ______makdatum
#define firstkey ______firstkey
#define nextkey ______nextkey
#define firsthash ______firsthash
#define calchash ______calchash
#define hashinc ______hashinc


/* @(#)dbm.h 1.7 88/02/08 SMI; from UCB 4.1 83/06/27 */

#define	PBLKSIZ	1024
#define	DBLKSIZ	4096
#define	BYTESIZ	8
#define	NULL	((char *) 0)

long	bitno;
long	maxbno;
long	blkno;
long	hmask;

char	pagbuf[PBLKSIZ];
char	dirbuf[DBLKSIZ];

int	dirf;
int	pagf;
int	dbrdonly;

typedef	struct
{
	char	*dptr;
	int	dsize;
} datum;

datum	fetch();
datum	makdatum();
datum	firstkey();
datum	nextkey();
datum	firsthash();
long	calchash();
long	hashinc();

 

#undef makdatum
#undef firsthash
#undef fetch
#undef calchash
#undef nextkey
#undef firstkey
#undef hashinc


extern "C" {
	datum	firstkey();
	datum	nextkey(datum);
	datum	fetch(datum);
	datum	makdatum();
	datum	firsthash();
	long	calchash();
	long	hashinc();
        int     dbmclose();
        int     dbminit(char*);
        int     store(datum, datum);

/* "delete" is a C++ keyword, so the following function can't be called
* from within C++.
* 		delete(datum);
*/
}

#endif
