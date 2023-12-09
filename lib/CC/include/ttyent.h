/*ident	"@(#)C++env:incl-master/proto-headers/ttyent.h	1.1" */

#ifndef __TTYENT_H
#define __TTYENT_H

#define getttyent ______getttyent
#define getttynam ______getttynam

/*	@(#)ttyent.h 1.3 88/02/07 SMI; from UCB 5.1 5/30/85	*/

/*
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 */

struct	ttyent { /* see getttyent(3) */
	char	*ty_name;	/* terminal device name */
	char	*ty_getty;	/* command to execute, usually getty */
	char	*ty_type;	/* terminal type for termcap (3X) */
	int	ty_status;	/* status flags (see below for defines) */
	char 	*ty_window;	/* command to start up window manager */
	char	*ty_comment;	/* usually the location of the terminal */
};

#define TTY_ON		0x1	/* enable logins (startup getty) */
#define TTY_SECURE	0x2	/* allow root to login */
#define TTY_LOCAL	0x4	/* local tty, supply software carrier */

extern struct ttyent *getttyent();
extern struct ttyent *getttynam();
 

#undef getttyent
#undef getttynam


extern "C" {
	struct ttyent *getttyent();
	struct ttyent *getttynam(const char*);
	void setttyent();
	void endttyent();
}

#endif

