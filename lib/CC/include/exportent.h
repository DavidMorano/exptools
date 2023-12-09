/*ident	"@(#)C++env:incl-master/proto-headers/exportent.h	1.1" */

#ifndef __EXPORTENT_H
#define __EXPORTENT_H

#ifndef __STDIO_H
#include <stdio.h>
#endif

#define setexportent ______setexportent
#define getexportent ______getexportent
#define endexportent ______endexportent
#define addexportent ______addexportent
#define remexportent ______remexportent
#define getexportopt ______getexportopt

/* @(#)exportent.h 1.5 88/02/07 (C) 1986 SMI */

/*
 * Exported file system table, see exportent(3)
 * Copyright (C) 1986 by Sun Microsystems, Inc.
 */ 

#define TABFILE "/etc/xtab"		/* where the table is kept */

/*
 * Options keywords
 */
#define ACCESS_OPT	"access"	/* machines that can mount fs */
#define ROOT_OPT	"root"		/* machines with root access of fs */
#define RO_OPT		"ro"		/* export read-only */
#define RW_OPT		"rw"		/* export read-mostly */
#define ANON_OPT	"anon"		/* uid for anonymous requests */
#define SECURE_OPT	"secure"	/* require secure NFS for access */
#define WINDOW_OPT	"window"	/* expiration window for credential */

struct exportent {
	char *xent_dirname;	/* directory (or file) to export */
	char *xent_options;	/* options, as above */
};

extern FILE *setexportent();
extern void endexportent();
extern int remexportent();
extern int addexportent();
extern char *getexportopt();
extern struct exportent *getexportent();
 

#undef endexportent
#undef getexportent
#undef remexportent
#undef getexportopt
#undef setexportent
#undef addexportent


extern "C" {
	FILE *setexportent();
	struct exportent *getexportent(FILE*);
	extern void endexportent();
	int addexportent(FILE*, char*, char*);
	int remexportent(FILE*, char*);
	char *getexportopt(FILE*);
}

#endif
