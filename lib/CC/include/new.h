/*ident	"@(#)C++env:incl-master/proto-headers/new.h	1.2" */
/***********************************************************************

	Copyright (c) 1984 AT&T, Inc. All rights Reserved
	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T, INC.

        The copyright notice above does not evidence any
        actual or intended publication of such source code.

**************************************************************************/

#ifndef __NEW_H
#define __NEW_H

#ifndef __STDDEF_H
#include <stddef.h>
#endif

extern void (*set_new_handler (void(*)()))();

void *operator new(size_t, void*);

#endif
