/*ident	"@(#)C++env:incl-master/proto-headers/vfork.h	1.1" */

#ifndef __VFORK_H
#define __VFORK_H

/*	@(#)vfork.h 1.2 88/02/07 SMI	*/

/*
 * Copyright (c) 1986 by Sun Microsystems, Inc.
 */

/*
 * this atrocity is necessary on sparc because registers modified
 * by the child get propagated back to the parent via the window
 * save/restore mechanism.
 */
extern int vfork();

#ifdef sparc
#pragma unknown_control_flow(vfork)
#endif
 


#endif
