/*ident	"@(#)C++env:incl-master/proto-headers/assert.h	1.2" */

/* This header file intentionally has no wrapper, since the user
*  may want to re-include it to turn off/on assertions for only
*  a portion of the source file.
*/

#ifndef __OSFCN_H
#include <sysent.h>
#endif

#ifndef __LIBC_H
#include <libc.h>
#endif

#ifndef __IOSTREAM_H
#include <iostream.h>
#endif

#ifdef assert
#undef assert
#endif
#ifdef _assert
#undef _assert
#endif

#ifdef NDEBUG
#define assert(e) ((void)0)
#else
#if defined(__STDC__)
#define assert(EX) (void)((EX) || ((cerr << "Assertion failed: " # EX ", file " << __FILE__ << ", line " << __LINE__ << endl), abort(), 0))
#else
#define assert(EX) (void)((EX) || ((cerr << "Assertion failed: EX, file " << __FILE__ << ", line " << __LINE__ << endl), abort(), 0))
#endif
#endif

#define _assert(e) assert(e)


