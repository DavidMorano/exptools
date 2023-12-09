/*ident	"@(#)C++env:incl-master/proto-headers/pwd.h	1.1" */

#ifndef __PWD_H
#define __PWD_H

#ifndef __STDIO_H
#include <stdio.h>
#endif

#define setpwent ______setpwent
#define endpwent ______endpwent
#define getpwent ______getpwent
#define getpwuid ______getpwuid
#define getpwnam ______getpwnam
#define fgetpwent ______fgetpwent
#define setpwfile ______setpwfile


/*	@(#)pwd.h 1.5 88/02/07 SMI; from UCB 4.1 83/05/03	*/

struct	passwd { /* see getpwent(3) */
	char	*pw_name;
	char	*pw_passwd;
	int	pw_uid;
	int	pw_gid;
	int	pw_quota;
	char	*pw_comment;
	char	*pw_gecos;
	char	*pw_dir;
	char	*pw_shell;
};

struct passwd *getpwent(), *getpwuid(), *getpwnam();
 

#undef getpwnam
#undef endpwent
#undef getpwuid
#undef getpwent
#undef setpwfile
#undef fgetpwent
#undef setpwent

extern "C" {
	struct passwd *getpwent();
	struct passwd *getpwnam(const char *);
	struct passwd *getpwuid(int);
	struct passwd *fgetpwent(FILE *);
	int putpwent(struct passwd *, FILE *);
	int setpwent();
	int endpwent();
	void setpwfile(const char *);
}

#endif
