/*ident	"@(#)C++env:incl-master/proto-headers/struct.h	1.1" */

#ifndef __STRUCT_H
#define __STRUCT_H

/*	@(#)struct.h 1.5 88/02/07 SMI; from UCB 4.1 83/05/03	*/

/*
 * access to information relating to the fields of a structure
 */

#define	fldoff(str, fld)	((int)&(((struct str *)0)->fld))
#define	fldsiz(str, fld)	(sizeof(((struct str *)0)->fld))
#define	strbase(str, ptr, fld)	((struct str *)((char *)(ptr)-fldoff(str, fld)))
 


#endif
