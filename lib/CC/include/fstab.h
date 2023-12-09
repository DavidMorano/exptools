/*ident	"@(#)C++env:incl-master/proto-headers/fstab.h	1.1" */

#ifndef __FSTAB_H
#define __FSTAB_H

#define getfsent ______getfsent
#define getfsspec ______getfsspec
#define getfsfile ______getfsfile
#define getfstype ______getfstype
#define endfsent ______endfsent
#define setfsent ______setfsent

/*	@(#)fstab.h 1.5 88/02/07 SMI; from UCB 4.4 83/05/24	*/

/*
 * File system table, see fstab (5)
 *
 * Used by dump, mount, umount, swapon, fsck, df, ...
 *
 * The fs_spec field is the block special name.  Programs
 * that want to use the character special name must create
 * that name by prepending a 'r' after the right most slash.
 * Quota files are always named "quotas", so if type is "rq",
 * then use concatenation of fs_file and "quotas" to locate
 * quota file.
 */
#define	FSTAB		"/etc/fstab"

#define	FSTAB_RW	"rw"	/* read/write device */
#define	FSTAB_RQ	"rq"	/* read/write with quotas */
#define	FSTAB_RO	"ro"	/* read-only device */
#define	FSTAB_SW	"sw"	/* swap device */
#define	FSTAB_XX	"xx"	/* ignore totally */

struct	fstab{
	char	*fs_spec;		/* block special device name */
	char	*fs_file;		/* file system path prefix */
	char	*fs_type;		/* FSTAB_* */
	int	fs_freq;		/* dump frequency, in days */
	int	fs_passno;		/* pass number on parallel dump */
};

struct	fstab *getfsent();
struct	fstab *getfsspec();
struct	fstab *getfsfile();
struct	fstab *getfstype();
int	setfsent();
int	endfsent();
 

#undef getfsfile
#undef endfsent
#undef getfsspec
#undef getfsent
#undef setfsent
#undef getfstype

extern "C" {
	struct  fstab *getfsent();
	struct  fstab *getfsspec(const char*);
	struct  fstab *getfsfile(const char*);
	struct  fstab *getfstype(const char*);
	int     setfsent(), endfsent();
}

#endif
