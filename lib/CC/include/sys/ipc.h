/*ident	"@(#)C++env:incl-master/proto-headers/sys/ipc.h	1.1" */

#ifndef __IPC_H
#define __IPC_H

#ifndef __TYPES_H
#include <sys/types.h>
#endif

#define msgget ______msgget
#define semget ______semget
#define shmget ______shmget
#define ftok ______ftok

/*	@(#)ipc.h 1.4 88/02/08 SMI; from S5R2 6.1 */

/* Common IPC Access Structure */
struct ipc_perm {
	ushort	uid;	/* owner's user id */
	ushort	gid;	/* owner's group id */
	ushort	cuid;	/* creator's user id */
	ushort	cgid;	/* creator's group id */
	ushort	mode;	/* access modes */
	ushort	seq;	/* slot usage sequence number */
	key_t	key;	/* key */
};

/* Common IPC Definitions. */
/* Mode bits. */
#define	IPC_ALLOC	0100000		/* entry currently allocated */
#define	IPC_CREAT	0001000		/* create entry if key doesn't exist */
#define	IPC_EXCL	0002000		/* fail if key exists */
#define	IPC_NOWAIT	0004000		/* error if request must wait */

/* Keys. */
#define	IPC_PRIVATE	(key_t)0	/* private key */

/* Control Commands. */
#define	IPC_RMID	0	/* remove identifier */
#define	IPC_SET		1	/* set options */
#define	IPC_STAT	2	/* get options */
 

#undef ftok
#undef semget
#undef msgget
#undef shmget

extern "C" {
	key_t ftok(const char *, char);
}

#endif
