/*ident	"@(#)C++env:incl-master/proto-headers/string.h	1.1" */

#ifndef __STRING_H
#define __STRING_H

#ifndef __MEMORY_H
#include <memory.h>
#endif

#define strcpy ______strcpy
#define strncpy ______strncpy
#define strcat ______strcat
#define strncat ______strncat
#define strchr ______strchr
#define strrchr ______strrchr
#define strpbrk ______strpbrk
#define strtok ______strtok
#define index ______index
#define rindex ______rindex
#define strdup ______strdup
#define strcmp ______strcmp
#define strncmp ______strncmp
#define strlen ______strlen
#define strspn ______strspn
#define strcspn ______strcspn

/*	@(#)string.h 1.4 88/02/07 SMI; from S5R2 1.2	*/

extern char
	*strcpy(),
	*strncpy(),
	*strcat(),
	*strncat(),
	*strchr(),
	*strrchr(),
	*strpbrk(),
	*strtok(),
	*strdup();
extern int
	strcmp(),
	strncmp(),
	strlen(),
	strspn(),
	strcspn();
 

#undef rindex
#undef strcat
#undef strchr
#undef strlen
#undef strcmp
#undef strncat
#undef strdup
#undef strncmp
#undef strpbrk
#undef strrchr
#undef strcpy
#undef strtok
#undef strcspn
#undef strspn
#undef index
#undef strncpy

extern "C" {
	char *strcpy(char*, const char*);
	char *strncpy(char*, const char*, int);
	char *strcat(char*, const char*);
	char *strncat(char*, const char*, int);
	int strcmp(const char*, const char*);
	int strncmp(const char*, const char*, int);
	int strlen(const char*);
	char *strchr(const char*, int);
	char *strpbrk(const char*, const char*);
	char *strrchr(const char*, int);
	char *strtok(char*, const char*);
	int strspn(const char*, const char*);
	int strcspn(const char*, const char*);
	char *index(const char*, char);
	char *rindex(const char*, char);
	char *strdup(const char*);
}

#endif
