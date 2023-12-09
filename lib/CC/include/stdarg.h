/*ident	"@(#)C++env:incl-master/const-headers/stdarg.h	1.3" */
/**************************************************************************
			Copyright (c) 1984 AT&T
	  		  All Rights Reserved  	

	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T
	
	The copyright notice above does not evidence any   	
	actual or intended publication of such source code.

*****************************************************************************/
/* stdarg.h */
/* ADAPTED FROM: */
/*	@(#)varargs.h	1.2	*/

#ifndef STDARGH
#define STDARGH

/*
	USAGE:
		f( arg-declarations ... ) {
			va_list ap;
			va_start(ap, parmN);	// parmN == last named arg
			// ...
			type arg = va_arg(ap, type);
			// ...
			va_end(ap);
		}
*/

#ifndef va_start

#ifdef pyr
typedef int     va_buf[3];
typedef va_buf  *va_list;

extern "C"
{
	extern void     _vastart(va_list, char*);
	extern char     *_vaarg(va_list, int);
}

#define         va_start(ap, parmN)     {\
        va_buf  _va;\
        _vastart(ap = (va_list)_va, (char *)&parmN + sizeof parmN)
#define         va_end(ap)      }
#define         va_arg(ap, mode)        *((mode *)_vaarg(ap, sizeof (mode)))
#else
typedef char *va_list;
#define va_end(ap)
#ifdef u370
#define va_start(ap, parmN) ap =\
	(char *) ((int)&parmN + 2*sizeof(parmN) - 1 & -sizeof(parmN))
#define va_arg(ap, mode) ((mode *)(ap = \
	(char *) ((int)ap + 2*sizeof(mode) - 1 & -sizeof(mode))))[-1]
#else
#ifdef hp9000s800
#define va_start(ap, parmN) (ap = (char *)&parmN + sizeof(parmN),(void)va_arg(ap,int))
#define va_arg(ap, mode) ((mode *)(ap = (char *)((int)(ap-sizeof(mode)) & ~(sizeof(mode)-1))))[0]
#else
#define va_start(ap, parmN) ap = (char *)( &parmN+1 )
#define va_arg(ap, mode) ((mode *)(ap += sizeof(mode)))[-1]
#endif
#endif
#endif

#if !pyr || !BSD
#include	<stdio.h>
extern "C" {
extern int vprintf(const char*, va_list),
	vfprintf(FILE*, const char*, va_list),
	vsprintf(char*, const char*, va_list);
}
#endif
#endif

#endif
