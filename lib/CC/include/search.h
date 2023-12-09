/*ident	"@(#)C++env:incl-master/proto-headers/search.h	1.1" */

#ifndef __SEARCH_H
#define __SEARCH_H

#define bsearch ______bsearch
#define hcreate ______hcreate
#define hdestroy ______hdestroy
#define hsearch ______hsearch
#define lfind ______lfind
#define lsearch ______lsearch
#define tdelete ______tdelete
#define tfind ______tfind
#define tsearch ______tsearch
#define twalk ______twalk

/*	@(#)search.h 1.3 88/02/07 SMI; from S5R2 1.2	*/

/* HSEARCH(3C) */
typedef struct entry { char *key, *data; } ENTRY;
typedef enum { FIND, ENTER } ACTION;

/* TSEARCH(3C) */
typedef enum { preorder, postorder, endorder, leaf } VISIT;
 

#undef lfind
#undef bsearch
#undef hdestroy
#undef hcreate
#undef tfind
#undef hsearch
#undef lsearch
#undef tdelete
#undef tsearch
#undef twalk

extern "C" {
    /* BSEARCH(3C) */
	void *bsearch(const void *, void *, unsigned, unsigned, int(*)(const void *, const void *));

    /* HSEARCH(3C) */
	ENTRY *hsearch(ENTRY, ACTION);
	int hcreate(unsigned);
	void hdestroy();

    /* TSEARCH(3C) */
	void *tsearch(const void*, void**, int(*)(const void *, const void *));
	void *tfind(const void*, void**, int(*)(const void *, const void *));
	void *tdelete(const void*, void**, int(*)(const void *, const void *));
	void twalk(void*,void (*)(void *, VISIT, int));

    /* LSEARCH(3C) */
	void *lsearch(const void *, void *, unsigned *, unsigned, int(*)(const void *, const void *));
	void *lfind(const void *, void *, unsigned *, unsigned, int(*)(const void *, const void *));
}

#endif
