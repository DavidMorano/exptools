/*ident	"@(#)C++env:incl-master/proto-headers/sys/user.h	1.1" */

#ifndef __USER_H
#define __USER_H

/*	@(#)user.h 2.44 88/02/08 SMI; from UCB 7.1 6/4/86	*/

/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 */

#ifndef _user_h
#define _user_h

#ifdef sun386
#include <machine/tss.h>
#include <sys/filehdr.h>
#endif
#include <machine/pcb.h>
#include <machine/reg.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/exec.h>
#ifdef sun386
#include <sys/label.h>
#endif
#include <sys/proc.h>
#include <sys/ucred.h>

/*
 * Per process structure containing data that
 * isn't needed in core when the process is swapped out.
 * A redzone is set below the user structure as
 * a safe guard against kernel stack overflow.
 */

#define	SHSIZE		sizeof (struct exec)
#define	MAXCOMLEN	16		/* <= MAXNAMLEN, >= sizeof (ac_comm) */

struct	user {
	char	u_stack[KERNSTACK];	/* the kernel stack */
	struct	pcb u_pcb;
	struct	proc *u_procp;		/* pointer to proc structure */
	int	*u_ar0;			/* address of users saved R0 */
	char	u_comm[MAXCOMLEN + 1];

/* syscall parameters, results and catches */
	int	u_arg[8];		/* arguments to current system call */
	int	*u_ap;			/* pointer to arglist */
	label_t	u_qsave;		/* for non-local gotos on interrupts */
	union {				/* syscall return values */
		struct	{
			int	R_val1;
			int	R_val2;
		} u_rv;
#define	r_val1	u_rv.R_val1
#define	r_val2	u_rv.R_val2
		off_t	r_off;
		time_t	r_time;
	} u_r;
#define	u_rval1 u_r.r_val1
#define	u_rval2 u_r.r_val2
	char	u_error;		/* return error code */
	char	u_eosys;		/* special action on end of syscall */

/* 1.1 - processes and protection */
#ifdef KERNEL
#define	u_cred		u_procp->p_cred
#define	u_uid		u_cred->cr_uid
#define	u_gid		u_cred->cr_gid
#define	u_groups	u_cred->cr_groups
#define	u_ruid		u_cred->cr_ruid
#define	u_rgid		u_cred->cr_rgid
#define	u_auid		u_cred->cr_auid
#endif /*KERNEL*/

/* 1.2 - memory management */
#ifdef KERNEL
#define	u_tsize		u_procp->p_tsize
#define	u_dsize		u_procp->p_dsize
#define	u_ssize		u_procp->p_ssize
#endif /*KERNEL*/
	label_t u_ssave;		/* label for swapping/forking */

/* 1.3 - signal management */
	void	(*u_signal[NSIG])();	/* disposition of signals */
	int	u_sigmask[NSIG];	/* signals to be blocked */
	int	u_sigonstack;		/* signals to take on sigstack */
	int	u_sigintr;		/* signals that interrupt syscalls */
	int	u_sigreset;		/* signals that reset the handler when taken */
	int	u_oldmask;		/* saved mask from before sigpause */
	int	u_code;			/* ``code'' to trap */
	char	*u_addr;		/* ``addr'' to trap */
	struct	sigstack u_sigstack;	/* sp & on stack state variable */
#define	u_onstack	u_sigstack.ss_onstack
#define	u_sigsp		u_sigstack.ss_sp

/* 1.4 - descriptor management */
	/*
	 * The next two fields are placeholders for pointers to the
	 * u_ofile and u_pofile arrays.  When NOFILE goes over 64, these
	 * arrays will be allocated dynamically.  For the moment, these
	 * fields are just here so that kmem readers won't have to be
	 * rebuilt when the remaining support for a larger NOFILE value
	 * does go in.
	 */
	struct	file **u_ofileX;
	char	*u_pofileX;
	struct	file *u_ofile[NOFILE];	/* file structures for open files */
	char	u_pofile[NOFILE];	/* per-process flags of open files */
	int	u_lastfile;		/* high-water mark of u_ofile */
#define	UF_EXCLOSE 	0x1		/* auto-close on exec */
#define UF_FDLOCK	0x2		/* file desc locked (SysV style) */
 	struct	ucwd  *u_cwd;		/* ascii current directory */
	struct	vnode *u_cdir;		/* current directory */
	struct	vnode *u_rdir;		/* root directory of current process */
	short	*u_ttyp;		/* pointer to pgrp in streamtab */
	dev_t	u_ttyd;			/* controlling tty dev */
	struct	vnode *u_ttyvp;		/* vnode of controlling tty */
	short	u_cmask;		/* mask for file creation */

/* 1.5 - timing and statistics */
	struct	rusage u_ru;		/* stats for this proc */
	struct	rusage u_cru;		/* sum of stats for reaped children */
	struct	itimerval u_timer[3];
	int	u_XXX[3];
	struct timeval	u_start;
	short	u_acflag;

	struct uprof {			/* profile arguments */
		short	*pr_base;	/* buffer base */
		u_int	 pr_size;	/* buffer size */
		u_int	 pr_off;	/* pc offset */
		u_int	 pr_scale;	/* pc scaling */
	} u_prof;

/* 1.6 - resource controls */
	struct	rlimit u_rlimit[RLIM_NLIMITS];

/* BEGIN TRASH */
	union {
		struct exec Ux_A;	/* header of executable file */
		char ux_shell[SHSIZE];	/* #! and name of interpreter */
#ifdef sun386
		struct exec UX_C;	/* COFF file header */
#endif
	} u_exdata;
#ifdef sun386
	/*
	 * The virtual address of the text and data is needed to exec
	 * coff files.  Unfortunately, they won't fit into Ux_A above.
	 */
	u_int	u_textvaddr;		/* virtual address of text segment */
	u_int	u_datavaddr;		/* virtual address of data segment */
	u_int	u_bssvaddr;		/* virtual address of bss segment */
#endif
#define	ux_mach		Ux_A.a_machtype
#define	ux_mag		Ux_A.a_magic
#define	ux_tsize	Ux_A.a_text
#define	ux_dsize	Ux_A.a_data
#define	ux_bsize	Ux_A.a_bss
#ifndef sun386
#define	ux_ssize	Ux_A.a_syms
#endif
#define	ux_entloc	Ux_A.a_entry
#ifdef sun386                   
#define ux_toffset	Ux_A.a_trsize
#define ux_doffset	Ux_A.a_drsize
#else 
#define	ux_unused	Ux_A.a_trsize
#define	ux_relflg	Ux_A.a_drsize
#endif
#ifdef sun
	int	u_lofault;		/* catch faults in locore.s */
#endif sun
/* END TRASH */
};

/*
 * Current directory structure for auditing, pointed to by u_cwd.
 */
struct ucwd {
 	u_short	cw_ref;			/* reference count */
 	u_short	cw_len;			/* size of this whole thing */
 	char	*cw_dir;		/* directory */
 	char	*cw_root;		/* root directory */
};
 
#ifdef KERNEL
void cwincr();
void cwfree();
#endif KERNEL

/* u_eosys values */
#define	NORMALRETURN	0	/* normal return; adjusts PC, registers */
#define	JUSTRETURN	1	/* just return, leave registers alone */
#define	RESTARTSYS	2	/* back up PC, restart system call */

/* u_error codes */
#ifdef KERNEL
#include <sys/errno.h>
#else KERNEL
#include <errno.h>
#endif KERNEL

#ifdef KERNEL
#ifdef sun
#define	u	(*(struct user *)UADDR)
#else sun
extern	struct user u;
#endif sun

extern	struct user forkutl;

#endif KERNEL

#ifdef sun
#define U_FPA_USED      0x0100
#define U_FPA_INFORK	0x80
#define U_FPA_FDBITS    0x7F
#endif

#endif !_user_h
 


#endif
