/*ident	"@(#)C++env:incl-master/proto-headers/setjmp.h	1.1" */

#ifndef __SETJMP_H
#define __SETJMP_H

#define sigsetjmp ______sigsetjmp
#define setjmp ______setjmp
#define _setjmp _______setjmp
#define siglongjmp ______siglongjmp
#define longjmp ______longjmp
#define _longjmp _______longjmp

/*      @(#)setjmp.h 1.18 88/07/26 SMI; from UCB 4.1 83/05/03       */

#if defined(_CROSS_TARGET_ARCH)

   /* Used when building a cross-tool, with the target system architecture
    * determined by the _CROSS_TARGET_ARCH preprocessor variable at compile time.
    * Usage:
    *      #include <setjmp.h>
    * ...plus compilation with command (e.g. for Sun-4 target architecture):
    *      cc  -DSUN2=2 -DSUN3=3 -DSUN4=4  -D_CROSS_TARGET_ARCH=SUN4  ...
    * Note: this may go away in a future release.
    */
#  if   _CROSS_TARGET_ARCH == SUN2
#    include "sun2/setjmp.h"
#  elif _CROSS_TARGET_ARCH == SUN3
#    include "sun3/setjmp.h"
#  elif _CROSS_TARGET_ARCH == SUN4
#    include "sun4/setjmp.h"
#  elif _CROSS_TARGET_ARCH == VAX
#    include "vax/setjmp.h"
#  endif

#else /*!defined(_CROSS_TARGET_ARCH)*/

   /* The usual, native case.  Usage:
    *      #include <setjmp.h>
    *
    * These include's would be more accurately keyed by (only) target system
    * architecture instead of target processor type.  However, of the two,
    * only target processor type is currently predefined by the preprocessor.
    * [This will be fixed in release 4.1]
    */
#  if   defined(sun2) || defined(mc68010)
#    include "sun2/setjmp.h"
#  elif defined(sun3) || defined(mc68020)
#    include "sun3/setjmp.h"
#  elif defined(sun4) || defined(sparc)
#    include "sun4/setjmp.h"
#  elif defined(vax)
#    include "vax/setjmp.h"
#  endif

#endif /*defined(_CROSS_TARGET_ARCH)*/


/*
 * Usage when building a cross-tool with a fixed target system architecture
 * (Sun-4 in this example), bypassing this file:
 *      #include <sun4/setjmp.h>
 */
 

#undef _longjmp
#undef _setjmp
#undef longjmp
#undef setjmp
#undef siglongjmp
#undef sigsetjmp

extern "C" {
	int setjmp(jmp_buf);
	void longjmp(jmp_buf, int);
	int _setjmp(jmp_buf);
	void _longjmp(jmp_buf, int);
	int sigsetjmp(sigjmp_buf, int);
	void siglongjmp(sigjmp_buf, int);
}

#endif
