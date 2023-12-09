/*ident	"@(#)C++env:incl-master/proto-headers/ranlib.h	1.1" */

#ifndef __RANLIB_H
#define __RANLIB_H

/*	@(#)ranlib.h 1.5 88/02/07 SMI; from UCB 4.1 83/05/03	*/

/*
 * Structure of the __.SYMDEF table of contents for an archive.
 * __.SYMDEF begins with a word giving the number of ranlib structures
 * which immediately follow, and then continues with a string
 * table consisting of a word giving the number of bytes of strings
 * which follow and then the strings themselves.
 * The ran_strx fields index the string table whose first byte is numbered 0.
 */
struct	ranlib {
	union {
		off_t	ran_strx;	/* string table index of */
		char	*ran_name;	/* symbol defined by */
	} ran_un;
	off_t	ran_off;		/* library member at this offset */
};
 


#endif
