/*ident	"@(#)C++env:incl-master/proto-headers/malloc.h	1.1" */

#ifndef __MALLOC_H
#define __MALLOC_H

/* This macro is introduced for the sole purpose of making it possible to 
*  build cfront 2.0b6.1 and later versions with earlier versions of cfront.
*/
#ifndef __HAVE_SIZE_T
#define __HAVE_SIZE_T
#endif

#ifndef __STDDEF_H
#include <stddef.h>
#endif

#define calloc ______calloc
#define realloc ______realloc
#define malloc ______malloc
#define mallopt ______mallopt
#define free ______free
#define cfree ______cfree

/*	@(#)malloc.h 1.4 88/02/07 SMI; from S5R2 1.2	*/

/*
	Constants defining mallopt operations
*/
#define M_MXFAST	1	/* set size of 'small blocks' */
#define M_NLBLKS	2	/* set num of small blocks in holding block */
#define M_GRAIN		3	/* set rounding factor for small blocks */
#define M_KEEP		4	/* (nop) retain contents of freed blocks */

/*
	malloc information structure
*/
struct mallinfo  {
	int arena;	/* total space in arena */
	int ordblks;	/* number of ordinary blocks */
	int smblks;	/* number of small blocks */
	int hblks;	/* number of holding blocks */
	int hblkhd;	/* space in holding block headers */
	int usmblks;	/* space in small blocks in use */
	int fsmblks;	/* space in free small blocks */
	int uordblks;	/* space in ordinary blocks in use */
	int fordblks;	/* space in free ordinary blocks */
	int keepcost;	/* cost of enabling keep option */

	int mxfast;	/* max size of small blocks */
	int nlblks;	/* number of small blocks in a holding block */
	int grain;	/* small block rounding factor */
	int uordbytes;	/* space (including overhead) allocated in ord. blks */
	int allocated;	/* number of ordinary blocks allocated */
	int treeoverhead;	/* bytes used in maintaining the free tree */
};	

extern	char	*malloc();
extern	char	*realloc();
extern	int	mallopt();
extern	struct mallinfo mallinfo();
 

#undef mallopt
#undef cfree
#undef free
#undef calloc
#undef malloc
#undef realloc


extern "C" {
	char *malloc(size_t);
	void free(void*);
	void cfree(void*);
	char *realloc(void*, size_t);
	char *calloc(unsigned, size_t);
	int mallopt(int, int);
	struct mallinfo mallinfo(int);
	char *memalign(unsigned, size_t);
	char *valloc(size_t);
	int malloc_debug(int);
	int malloc_verify();
	char *alloca(int);
}

#endif
