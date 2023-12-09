#ifndef __STDDEF_H
#define __STDDEF_H

typedef int ptrdiff_t;

typedef unsigned int size_t;

#ifndef NULL
#define NULL 0
#endif

#define offsetof(ty,mem) ((size_t)&(((ty*)0)->mem))

#endif
