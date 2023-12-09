/*ident	"@(#)C++env:incl-master/proto-headers/pwdadj.h	1.1" */

#ifndef __PWDADJ_H
#define __PWDADJ_H

#ifndef __STDIO_H
#include <stdio.h>
#endif

#define getpwaent ______getpwaent
#define getpwanam ______getpwanam
#define getpwauid ______getpwauid
#define fgetpwaent ______fgetpwaent
#define setpwaent ______setpwaent
#define endpwaent ______endpwaent


/*      @(#)pwdadj.h 1.3 88/02/07 SMI      */ /* c2 secure */

struct	passwd_adjunct { /* see getpwaent(3) */
	char		*pwa_name;
	char		*pwa_passwd;
	blabel_t	pwa_minimum;
	blabel_t	pwa_maximum;
	blabel_t	pwa_def;
	audit_state_t	pwa_au_always;
	audit_state_t	pwa_au_never;
	int		pwa_version;
};

struct passwd_adjunct *getpwaent(), *getpwauid(), *getpwanam();

#define PWA_VALID 0
#define PWA_INVALID -1
#define PWA_UNKNOWN -2
 

#undef getpwanam
#undef endpwaent
#undef getpwauid
#undef getpwaent
#undef fgetpwaent
#undef setpwaent

extern "C" {
	struct passwd_adjunct *getpwaent();
	struct passwd_adjunct *getpwanam(char *);
	struct passwd_adjunct *fgetpwaent(FILE *);
	struct passwd_adjunct *getpwauid(int);
	void setpwaent();
	void endpwaent();


}

#endif



