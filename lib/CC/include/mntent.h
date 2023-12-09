/*ident	"@(#)C++env:incl-master/proto-headers/mntent.h	1.1" */

#ifndef __MNTENT_H
#define __MNTENT_H

#ifndef __STDIO_H
#include <stdio.h>
#endif

#define setmntent ______setmntent
#define getmntent ______getmntent
#define addmntent ______addmntent
#define hasmntopt ______hasmntopt
#define endmntent ______endmntent

/*	@(#)mntent.h 1.15 88/03/18 SMI	*/

/*
 * File system table, see mntent (5)
 *
 * Used by dump, mount, umount, swapon, fsck, df, ...
 *
 * Quota files are always named "quotas", so if type is "rq",
 * then use concatenation of mnt_dir and "quotas" to locate
 * quota file.
 */

#define	MNTTAB		"/etc/fstab"
#define	MOUNTED		"/etc/mtab"

#define	MNTMAXSTR	128

#define	MNTTYPE_42	"4.2"	/* 4.2 file system */
#define	MNTTYPE_NFS	"nfs"	/* network file system */
#define	MNTTYPE_PC	"pc"	/* IBM PC (MSDOS) file system */
#define	MNTTYPE_SWAP	"swap"	/* swap file system */
#define	MNTTYPE_IGNORE	"ignore"/* No type specified, ignore this entry */
#define MNTTYPE_LO	"lo"	/* Loop back File system */

#define	MNTOPT_RO	"ro"	/* read only */
#define	MNTOPT_RW	"rw"	/* read/write */
#define	MNTOPT_QUOTA	"quota"	/* quotas */
#define	MNTOPT_NOQUOTA	"noquota"/* no quotas */
#define	MNTOPT_SOFT	"soft"	/* soft mount */
#define	MNTOPT_HARD	"hard"	/* hard mount */
#define	MNTOPT_NOSUID	"nosuid"/* no set uid allowed */
#define	MNTOPT_NOAUTO	"noauto"/* hide entry from mount -a */
#define	MNTOPT_INTR	"intr"	/* allow interrupts on hard mount */
#define MNTOPT_SECURE 	"secure"/* use secure RPC for NFS */
#define MNTOPT_GRPID 	"grpid"	/* SysV-compatible group-id on create */
#define MNTOPT_REMOUNT	"remount"/* change options on previous mount */
#define MNTOPT_NOSUB	"nosub"  /* disallow mounts beneath this one */
#define MNTOPT_MULTI	"multi"  /* Do multi-component lookup */

struct	mntent{
	char	*mnt_fsname;		/* name of mounted file system */
	char	*mnt_dir;		/* file system path prefix */
	char	*mnt_type;		/* MNTTYPE_* */
	char	*mnt_opts;		/* MNTOPT* */
	int	mnt_freq;		/* dump frequency, in days */
	int	mnt_passno;		/* pass number on parallel fsck */
};

struct	mntent *getmntent();
char	*hasmntopt();
FILE	*setmntent();
int	endmntent();
 

#undef addmntent
#undef endmntent
#undef getmntent
#undef hasmntopt
#undef setmntent


extern "C" {
FILE *setmntent(char *, char *);
struct mntent *getmntent(FILE *);
int addmntent(FILE *, struct mntent *);
char *hasmntopt(struct mntent *, char *);
int endmntent(FILE *);
}

#endif
