/*ident	"@(#)C++env:incl-master/proto-headers/alloca.h	1.2" */

#ifndef __ALLOCA_H
#define __ALLOCA_H

/*	@(#)alloca.h	1.3	88/02/07	SMI	*/
#if defined(sparc)
# define alloca(x) __builtin_alloca(x)
#endif
 

extern "C" {
	void *__builtin_alloca(int);
}
#endif
