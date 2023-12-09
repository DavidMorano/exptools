/*ident	"@(#)C++env:incl-master/proto-headers/grp.h	1.1" */

#ifndef __GRP_H
#define __GRP_H

#ifndef __STDIO_H
#include <stdio.h>
#endif

#define endgrent ______endgrent
#define setgrent ______setgrent
#define fgetgrent ______fgetgrent
#define getgrent ______getgrent
#define getgrgid ______getgrgid
#define getgrnam ______getgrnam

/*	@(#)grp.h 1.5 88/02/07 SMI; from UCB 4.1 83/05/03	*/

struct	group { /* see getgrent(3) */
	char	*gr_name;
	char	*gr_passwd;
	int	gr_gid;
	char	**gr_mem;
};

struct group *getgrent(), *getgrgid(), *getgrnam();
 

#undef getgrnam
#undef endgrent
#undef getgrent
#undef fgetgrent
#undef setgrent
#undef getgrgid

extern "C" {
	void endgrent();
	void setgrent();
	struct group *fgetgrent(FILE *);
	struct group *getgrent();
	struct group *getgrgid(int);
	struct group *getgrnam(const char *);
}

#endif
