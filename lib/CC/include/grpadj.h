/*ident	"@(#)C++env:incl-master/proto-headers/grpadj.h	1.1" */

#ifndef __GRPADJ_H
#define __GRPADJ_H

#ifndef __STDIO_H
#include <stdio.h>
#endif

#define getgraent ______getgraent
#define getgragid ______getgragid
#define getgranam ______getgranam

/*      @(#)grpadj.h 1.3 88/02/07 SMI      */ /* c2 secure */

struct	group_adjunct { /* see getgraent(3) */
	char	*gra_name;
	char	*gra_passwd;
};

struct group_adjunct *getgraent(), *getgragid(), *getgranam();
 

#undef getgranam
#undef getgraent
#undef getgragid


extern "C" {
	struct group_adjunct 	*getgraent(), 
				*getgragid(int), 
				*getgranam(char*),
				*fgetgraent(FILE*);
	void setgraent(), endgraent();
}

#endif
