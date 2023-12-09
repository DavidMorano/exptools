/*	Copyright (c) 1984 AT&T
	All rights reserved

	THIS IS UNPUBLISHED PROPRIETARY
	SOURCE CODE OF AT&T
	The copyright notice above does not
	evidence any actual or intended
	publication of such source code.
*/
/* @(#)db.h	1.4 */
#include <stdio.h>
#include <sys/param.h>
#define MAXPTR 4096		/* maximum number of pointers in index */
#define NDSZ 284		/* node size in index */
#define MAXREC 4096		/* maximum record length */
#define MAXCHAR 0177		/* maximum ascii character */
#ifndef MAXATT
#define MAXATT	200		/* maximum number of attributes */
#endif
#define ANAMELEN 31		/* attribute name length */
#ifdef MAXPATHLEN
#define MAXPATH MAXPATHLEN	/* maximum path length for file */
#else
#define MAXPATH 128
#endif

#ifdef MAXNAMELEN
#define MAXFILE MAXNAMELEN	/* maximum simple file name length */
#else
#define MAXFILE 20		/* maximum simple file name length */
#endif

#ifdef pdp11
#define MAXUNAME 40		/* maximum user-friendly name */
#else
#define MAXUNAME 80		/* maximum user-friendly name */
#endif
#define MAXCMD 256		/* maximum buffer length for commands */
#define KEYLEN 128		/* maximum key value length in index */
#define ERR -1			/* error return code */
#define NLCHAR '~'		/* default new line character */

#define MAXTBL 20		/* maximum tables handled by umenu */
#define DBFILES "dbfiles"	/* name of file with list of tables for umenu */
#define OVERVIEW "overview"	/* name of overview file for umenu */

/* the following structures are used in the index handling programs */
struct hdr
{	int level;
	long nodeloc;
	int chksum;
};
#define HDR sizeof(struct hdr)
struct index
{	int fd;
	char *rdptr;
	char *ordptr;
	struct hdr *root;
	struct hdr *leaf;
};
#define INDEX sizeof(struct index)

/* the following defines are used in scanning the indexes */
#define END 0
#define FOUND 1
#define MISSED 2

/* the following defines are used for operator handling */
#define LLT 1
#define LLE 2
#define LEQ 3
#define LNE 4
#define LGE 5
#define LGT 6
#define REQ 7
#define RNE 8
#define LT 9
#define LE 10
#define EQ 11
#define NE 12
#define GE 13
#define GT 14

/* the following are for date processing */
#define DLT 15
#define DLE 16
#define DEQ 17
#define DNE 18
#define DGE 19
#define DGT 20

struct fmt
{	int flag;
	int flen;
	char aname[ANAMELEN+1];
	char inf[4];
	int prnt;
	char justify;	/* l for left justify, the default
			   r for right
			   c for center
			*/
	char *val;
};

#define WN 1	/* fixed length field */
#define T 2	/* variable length terminated field */

/* error message numbers used by error() */

#define E_DESFOPEN 0
#define E_DATFOPEN 1
#define E_DATFWRITE 2
#define E_TEMFOPEN 3
#define E_DIRWRITE 4
#define E_INDFOPEN 5
#define E_BADLINK 6
#define E_BADUNLINK 7
#define E_EXISTS 8
#define E_BADFLAG 9
#define E_ILLATTR 10
#define E_ERR 11
#define E_SPACE 12
#define E_NONNUMERIC 13
#define E_GENERAL 50

/*
 * Definition of what a signal function returns.  This definition
 * helps make the code cleaner portability-wise.  The most common
 * definition is that signal functions return an int.  Some
 * implementations say they are void, however.  This definition
 * can be changed depending on the circumstances.
 *
 */
#ifndef SIGFUNC
#define SIGFUNC	int
#endif
