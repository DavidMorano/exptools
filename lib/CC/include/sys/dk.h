/*ident	"@(#)C++env:incl-master/proto-headers/sys/dk.h	1.1" */

#ifndef __DK_H
#define __DK_H

#define dkdial ______dkdial
#define dkndial ______dkndial
#define dkerr ______dkerr
#define dkmgr ______dkmgr
#define dknmgr ______dknmgr
#define dkmgrack ______dkmgrack
#define dkmgrnak ______dkmgrnak
#define dkminor ______dkminor
#define dknamer ______dknamer
#define dtnamer ______dtnamer
#define dxnamer ______dxnamer
#define dksplice ______dksplice
#define dksplwait ______dksplwait
#define dkxenviron ______dkxenviron
#define dkxlwrite ______dkxlwrite
#define dkxwrite ______dkxwrite
#define dkxpwrite ______dkxpwrite
#define maphost ______maphost
#define miscfield ______miscfield

/*	@(#)dk.h 2.6 88/02/08 SMI; from UCB 4.2 81/02/19	*/

/*
 * Instrumentation
 */
#define	CPUSTATES	4

#define	CP_USER		0
#define	CP_NICE		1
#define	CP_SYS		2
#define	CP_IDLE		3

#define	DK_NDRIVE	4

#ifdef KERNEL
long	cp_time[CPUSTATES];
int	dk_busy;
long	dk_time[DK_NDRIVE];
long	dk_seek[DK_NDRIVE];
long	dk_xfer[DK_NDRIVE];
long	dk_wds[DK_NDRIVE];
long	dk_bps[DK_NDRIVE];
long	dk_read[DK_NDRIVE];

long	tk_nin;
long	tk_nout;
#endif
 

#undef dxnamer
#undef dkminor
#undef maphost
#undef dkdial
#undef dkndial
#undef dksplwait
#undef dkxwrite
#undef dkmgr
#undef dkmgrack
#undef dkerr
#undef dknamer
#undef dkxlwrite
#undef dknmgr
#undef miscfield
#undef dkxpwrite
#undef dkxenviron
#undef dksplice
#undef dtnamer
#undef dkmgrnak

extern "C" {
	int dkdial(const char *);
	int dkndial(const char *, int);
	char *dkerr(int);
	struct mgrmsg *dkmgr(const char *);
	struct mgrmsg *dknmgr(const char *, int);
	int dkmgrack(int);
	int dkmgrnak(int, int);
	int dkminor(int);
	char *dknamer(int);
	char *dtnamer(int);
	char *dxnamer(int);
	int dksplice(int, int);
	int dksplwait(int);
	int dkxenviron(int);
	int dkxlwrite(int, const char *, short);
	int dkxwrite(int, const char *, short);
	int dkxpwrite(int, short);
	char *maphost(const char *, char, const char *, const char *, const char *);
	char *miscfield(char, char);
};

#endif
