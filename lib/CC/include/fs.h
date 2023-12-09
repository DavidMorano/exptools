/**************************************************************************
			Copyright (c) 1989 AT&T
	  		  All Rights Reserved  	

	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T
	
	The copyright notice above does not evidence any   	
	actual or intended publication of such source code.

*****************************************************************************/
#ifndef __FS_H
#define __FS_H

/* Prototypes of all the public freestore(3++) functions.
*
*  I made put them in the global name space and made them 
*  extern "C" so that the user can invoke them from the 
*  debugger, and without demangling the executable.
*/

extern "C" {
int fs_showall();
int fs_show(void *);
int fs_mark();
void fs_unmark();
int fs_since();
int fs_sincen(int);
int fs_watch(int);
int fs_unwatch(int);
void fs_watchall_d();
void fs_unwatchall_d();
void fs_watchall_n();
void fs_unwatchall_n();
void fs_break();
void fs_status();
void fs_dbxinit();
void fs_help();
void fs_verbose();
void fs_terse();
}

#endif
