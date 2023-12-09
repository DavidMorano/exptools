/*ident	"@(#)C++env:incl-master/proto-headers/kvm.h	1.1" */

#ifndef __KVM_H
#define __KVM_H

#define kvm_open ______kvm_open
#define kvm_close ______kvm_close
#define kvm_nlist ______kvm_nlist
#define kvm_read ______kvm_read
#define kvm_write ______kvm_write
#define kvm_getproc ______kvm_getproc
#define kvm_nextproc ______kvm_nextproc
#define kvm_setproc ______kvm_setproc
#define kvm_getu ______kvm_getu
#define kvm_getcmd ______kvm_getcmd

/*	@(#)kvm.h 2.2 88/02/08 SMI	*/

/*
 * Copyright (c) 1987 by Sun Microsystems, Inc.
 */

/* define a 'cookie' to pass around between user code and the library */
typedef struct _kvmd kvm_t;

/* libkvm routine definitions */
extern kvm_t		*kvm_open();
extern int		 kvm_close();
extern int		 kvm_nlist();
extern int		 kvm_read();
extern int		 kvm_write();
extern struct proc	*kvm_getproc();
extern struct proc	*kvm_nextproc();
extern int		 kvm_setproc();
extern struct user	*kvm_getu();
extern int		 kvm_getcmd();
 

#undef kvm_getcmd
#undef kvm_nextproc
#undef kvm_close
#undef kvm_open
#undef kvm_getu
#undef kvm_nlist
#undef kvm_write
#undef kvm_getproc
#undef kvm_read
#undef kvm_setproc

extern "C" {
	kvm_t            *kvm_open(char*, char*, char*, int, char*);
	int               kvm_close(kvm_t*);
	int               kvm_nlist(kvm_t*, struct nlist*);
	int               kvm_read(kvm_t*, unsigned long, char*, unsigned);
	int               kvm_write(kvm_t*, unsigned long, char*, unsigned);
	struct proc      *kvm_getproc(kvm_t*, int);
	struct proc      *kvm_nextproc(kvm_t*);
	int               kvm_setproc(kvm_t*);
	struct user      *kvm_getu(kvm_t*, struct proc*);
	int               kvm_getcmd(kvm_t*, struct proc*, struct user*, char***, char***);
}

#endif
