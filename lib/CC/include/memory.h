/*ident	"@(#)C++env:incl-master/proto-headers/memory.h	1.1" */

#ifndef __MEMORY_H
#define __MEMORY_H


#define memccpy ______memccpy
#define memchr ______memchr
#define memcpy ______memcpy
#define memset ______memset
#define memcmp ______memcmp

/*	@(#)memory.h 1.3 88/02/07 SMI; from S5R2 1.2	*/

extern char
	*memccpy(),
	*memchr(),
	*memcpy(),
	*memset();
extern int memcmp();
 

#undef memccpy
#undef memset
#undef memcpy
#undef memchr
#undef memcmp

extern "C" {
    void* memcpy(void*, const void*, int);
    void* memccpy(void*, const void*, int, int);
    void* memchr(const void*, int, int);
    int   memcmp(const void*, const void*, int);
    void* memset(void*, int, int);
}





#endif


