/*ident	"@(#)C++env:incl-master/proto-headers/mp.h	1.1" */

#ifndef __MP_H
#define __MP_H

#define itom ______itom
#define xtom ______xtom
#define mtox ______mtox
#define xalloc ______xalloc
#define mfree ______mfree

/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 */

/*	@(#)mp.h 1.6 88/02/07 SMI; from UCB 5.1 5/30/85	*/

struct mint {
	int len;
	short *val;
};
typedef struct mint MINT;

extern MINT *itom();
extern MINT *xtom();
extern char *mtox();
extern short *xalloc();
extern void mfree();

#define	FREE(x)	xfree(&(x))		/* Compatibility */
 

#undef mtox
#undef xtom
#undef mfree
#undef itom
#undef xalloc


extern "C" {
	int 	madd(MINT*, MINT*, MINT*),
		msub(MINT*, MINT*, MINT*),	
		mult(MINT*, MINT*, MINT*),
		mdiv(MINT*, MINT*, MINT*, MINT*),
		min(MINT*),
		mout(MINT*),
		pow(MINT*, MINT*, MINT*, MINT*),
		gcd(MINT*, MINT*, MINT*),
		rpow(MINT*, short, MINT*),
		msqrt(MINT*, MINT*, MINT*),
		sdiv(MINT*, short, MINT*, short*);
	MINT	*itom(short);
	void	mfree(MINT*);				
	char	*mtox(MINT*);
	MINT	*xtom(char*);

	/* Can't find the prototype for xalloc.  Sorry. 
	*/
}

#endif
