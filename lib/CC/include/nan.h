/*ident	"@(#)C++env:incl-master/proto-headers/nan.h	1.1" */

#ifndef __NAN_H
#define __NAN_H

/*	@(#)nan.h 1.4 88/02/07 SMI; from S5R2 1.3	*/

/* Handling of Not_a_Number's (only in IEEE floating-point standard) */

#include <signal.h>
#define KILLFPE()	(void) kill(getpid(), SIGFPE)
#if u3b || u3b5 || sun
#define NaN(X)	(((union { double d; struct { unsigned :1, e:11; } s; } \
			*)&X)->s.e == 0x7ff)
#define KILLNaN(X)	if (NaN(X)) KILLFPE()
#else
#define Nan(X)	0
#define KILLNaN(X)
#endif
 


#endif
