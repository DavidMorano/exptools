/*ident	"@(#)C++env:incl-master/proto-headers/sys/signal.h	1.4" */

#ifndef __SIGNAL_H
#define __SIGNAL_H

#define signal ______signal
#define sigset ______sigset
#define ssignal ______ssignal
#define gsignal ______gsignal
#define kill ______kill

/*	@(#)signal.h 2.29 88/03/03 SMI; from UCB 6.7 85/06/08	*/

/*
 * Copyright (c) 1982 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 */

/*
 * Copyright (c) 1987 by Sun Microsystems, Inc.
 */

#ifndef	_sys_signal_h
#define	_sys_signal_h
#include <vm/faultcode.h>
#define NSIG	32

#define	SIGHUP	1	/* hangup */
#define	SIGINT	2	/* interrupt */
#define	SIGQUIT	3	/* quit */
#define	SIGILL	4	/* illegal instruction (not reset when caught) */
#ifdef vax
#define     ILL_RESAD_FAULT	0x0	/* reserved addressing fault */
#define     ILL_PRIVIN_FAULT	0x1	/* privileged instruction fault */
#define     ILL_RESOP_FAULT	0x2	/* reserved operand fault */
/* CHME, CHMS, CHMU are not yet given back to users reasonably */
#endif vax
#ifdef mc68000
#define     ILL_ILLINSTR_FAULT	0x10	/* illegal instruction fault */
#define     ILL_PRIVVIO_FAULT	0x20	/* privilege violation fault */
#define     ILL_COPROCERR_FAULT	0x34	/* [coprocessor protocol error fault] */
#define     ILL_TRAP1_FAULT	0x84	/* trap #1 fault */
#define     ILL_TRAP2_FAULT	0x88	/* trap #2 fault */
#define     ILL_TRAP3_FAULT	0x8c	/* trap #3 fault */
#define     ILL_TRAP4_FAULT	0x90	/* trap #4 fault */
#define     ILL_TRAP5_FAULT	0x94	/* trap #5 fault */
#define     ILL_TRAP6_FAULT	0x98	/* trap #6 fault */
#define     ILL_TRAP7_FAULT	0x9c	/* trap #7 fault */
#define     ILL_TRAP8_FAULT	0xa0	/* trap #8 fault */
#define     ILL_TRAP9_FAULT	0xa4	/* trap #9 fault */
#define     ILL_TRAP10_FAULT	0xa8	/* trap #10 fault */
#define     ILL_TRAP11_FAULT	0xac	/* trap #11 fault */
#define     ILL_TRAP12_FAULT	0xb0	/* trap #12 fault */
#define     ILL_TRAP13_FAULT	0xb4	/* trap #13 fault */
#define     ILL_TRAP14_FAULT	0xb8	/* trap #14 fault */
#endif mc68000
#ifdef sparc
#define     ILL_STACK		0x00	/* bad stack */
#define     ILL_ILLINSTR_FAULT	0x02	/* illegal instruction fault */
#define     ILL_PRIVINSTR_FAULT	0x03	/* privileged instruction fault */
/* codes from 0x80 to 0xff are software traps */
#define     ILL_TRAP_FAULT(n)	((n)+0x80) /* trap n fault */
#endif sparc
#define	SIGTRAP	5	/* trace trap (not reset when caught) */
#define	SIGIOT	6	/* IOT instruction */
#define SIGABRT 6	/* used by abort, replace SIGIOT in the future */
#define	SIGEMT	7	/* EMT instruction */
#ifdef mc68000
#define     EMT_EMU1010		0x28	/* line 1010 emulator trap */
#define     EMT_EMU1111		0x2c	/* line 1111 emulator trap */
#endif mc68000
#ifdef sparc
#define	    EMT_TAG		0x0a	/* tag overflow */
#endif sparc
#define	SIGFPE	8	/* floating point exception */
#ifdef vax
#define     FPE_INTOVF_TRAP	0x1	/* integer overflow */
#define     FPE_INTDIV_TRAP	0x2	/* integer divide by zero */
#define     FPE_FLTOVF_TRAP	0x3	/* floating overflow */
#define     FPE_FLTDIV_TRAP	0x4	/* floating/decimal divide by zero */
#define     FPE_FLTUND_TRAP	0x5	/* floating underflow */
#define     FPE_DECOVF_TRAP	0x6	/* decimal overflow */
#define     FPE_SUBRNG_TRAP	0x7	/* subscript out of range */
#define     FPE_FLTOVF_FAULT	0x8	/* floating overflow fault */
#define     FPE_FLTDIV_FAULT	0x9	/* divide by zero floating fault */
#define     FPE_FLTUND_FAULT	0xa	/* floating underflow fault */
#endif vax
#ifdef mc68000
#define     FPE_INTDIV_TRAP	0x14	/* integer divide by zero */
#define     FPE_CHKINST_TRAP	0x18	/* CHK [CHK2] instruction */
#define     FPE_TRAPV_TRAP	0x1c	/* TRAPV [cpTRAPcc TRAPcc] instr */
#define     FPE_FLTBSUN_TRAP	0xc0	/* [branch or set on unordered cond] */
#define     FPE_FLTINEX_TRAP	0xc4	/* [floating inexact result] */
#define     FPE_FLTDIV_TRAP	0xc8	/* [floating divide by zero] */
#define     FPE_FLTUND_TRAP	0xcc	/* [floating underflow] */
#define     FPE_FLTOPERR_TRAP	0xd0	/* [floating operand error] */
#define     FPE_FLTOVF_TRAP	0xd4	/* [floating overflow] */
#define     FPE_FLTNAN_TRAP	0xd8	/* [floating Not-A-Number] */
#ifdef sun
#define     FPE_FPA_ENABLE	0x400	/* [FPA not enabled] */
#define     FPE_FPA_ERROR	0x404	/* [FPA arithmetic exception] */
#endif sun
#endif mc68000
#ifdef sparc
#define     FPE_INTOVF_TRAP	0x1	/* integer overflow */
#define     FPE_INTDIV_TRAP	0x14	/* integer divide by zero */
#define     FPE_FLTINEX_TRAP	0xc4	/* [floating inexact result] */
#define     FPE_FLTDIV_TRAP	0xc8	/* [floating divide by zero] */
#define     FPE_FLTUND_TRAP	0xcc	/* [floating underflow] */
#define     FPE_FLTOPERR_TRAP	0xd0	/* [floating operand error] */
#define     FPE_FLTOVF_TRAP	0xd4	/* [floating overflow] */
#endif sparc
#define	SIGKILL	9	/* kill (cannot be caught or ignored) */
/*
 * The codes for SIGBUS and SIGSEGV are described in <vm/faultcode.h>
 */
#define	SIGBUS	10	/* bus error */
#define     BUS_HWERR	FC_HWERR	/* misc hardware error (e.g. timeout) */
#define     BUS_ALIGN	FC_ALIGN	/* hardware alignment error */
#define	SIGSEGV	11	/* segmentation violation */
#define     SEGV_NOMAP	FC_NOMAP	/* no mapping at the fault address */
#define     SEGV_PROT	FC_PROT		/* access exceeded protections */
#define     SEGV_OBJERR	FC_OBJERR	/* object returned errno value */
/*
 * The SEGV_CODE(code) will be SEGV_NOMAP, SEGV_PROT, or SEGV_OBJERR.
 * In the SEGV_OBJERR case, doing a SEGV_ERRNO(code) gives an errno value
 * reported by the underlying file object mapped at the fault address.
 */
#define     SEGV_CODE(C)	FC_CODE(C)
#define     SEGV_ERRNO(C)	FC_ERRNO(C)
#define	SIGSYS	12	/* bad argument to system call */
#define	SIGPIPE	13	/* write on a pipe with no one to read it */
#define	SIGALRM	14	/* alarm clock */
#define	SIGTERM	15	/* software termination signal from kill */
#define	SIGURG	16	/* urgent condition on IO channel */
#define	SIGSTOP	17	/* sendable stop signal not from tty */
#define	SIGTSTP	18	/* stop signal from tty */
#define	SIGCONT	19	/* continue a stopped process */
#define	SIGCHLD	20	/* to parent on child stop or exit */
#define	SIGCLD	20	/* System V name for SIGCHLD */
#define	SIGTTIN	21	/* to readers pgrp upon background tty read */
#define	SIGTTOU	22	/* like TTIN for output if (tp->t_local&LTOSTOP) */
#define	SIGIO	23	/* input/output possible signal */
#define	SIGPOLL	SIGIO	/* System V name for SIGIO */
#define	SIGXCPU	24	/* exceeded CPU time limit */
#define	SIGXFSZ	25	/* exceeded file size limit */
#define	SIGVTALRM 26	/* virtual time alarm */
#define	SIGPROF	27	/* profiling time alarm */
#define	SIGWINCH 28	/* window changed */
#define	SIGLOST 29	/* resource lost (eg, record-lock lost) */
#define SIGUSR1 30	/* user defined signal 1 */
#define SIGUSR2 31	/* user defined signal 2 */
/*
 * If addr cannot be computed it is set to SIG_NOADDR.
 */
#define SIG_NOADDR	((char *)~0)

#ifndef KERNEL
void	(*signal())();
/*
 * Define BSD 4.1 reliable signals for SVID compatibility.
 * These functions may go away in a future release.
 */
void  (*sigset())();
int   sighold();
int   sigrelse();
int   sigignore();
#endif !KERNEL

#ifndef LOCORE
/*
 * Signal vector "template" used in sigvec call.
 */
struct	sigvec {
	void	(*sv_handler)();	/* signal handler */
	int	sv_mask;		/* signal mask to apply */
	int	sv_flags;		/* see signal options below */
};
#define SV_ONSTACK	0x0001	/* take signal on signal stack */
#define SV_INTERRUPT	0x0002	/* do not restart system on signal return */
#define SV_RESETHAND	0x0004	/* reset signal handler to SIG_DFL when signal taken */
#define sv_onstack sv_flags	/* isn't compatibility wonderful! */

/*
 * Structure used in sigstack call.
 */
struct	sigstack {
	char	*ss_sp;			/* signal stack pointer */
	int	ss_onstack;		/* current status */
};

/*
 * Information pushed on stack when a signal is delivered.
 * This is used by the kernel to restore state following
 * execution of the signal handler.  It is also made available
 * to the handler to allow it to properly restore state if
 * a non-standard exit is performed.
 */
struct	sigcontext {
	int	sc_onstack;		/* sigstack state to restore */
	int	sc_mask;		/* signal mask to restore */
#ifdef vax
	int	sc_sp;			/* sp to restore */
	int	sc_fp;			/* fp to restore */
	int	sc_ap;			/* ap to restore */
	int	sc_pc;			/* pc to restore */
	int	sc_ps;			/* psl to restore */
#endif vax
#ifdef mc68000
	int	sc_sp;			/* sp to restore */
	int	sc_pc;			/* pc to retore */
	int	sc_ps;			/* psl to restore */
#endif mc68000
#ifdef sparc
#define MAXWINDOW	31		/* max usable windows in sparc */
	int	sc_sp;			/* sp to restore */
	int	sc_pc;			/* pc to retore */
	int	sc_npc;			/* next pc to restore */
	int	sc_psr;			/* psr to restore */
	int	sc_g1;			/* register that must be restored */
	int	sc_o0;
	int	sc_wbcnt;		/* number of outstanding windows */
	char	*sc_spbuf[MAXWINDOW];	/* sp's for each wbuf */
	int	sc_wbuf[MAXWINDOW][16];	/* outstanding window save buffer */
#endif sparc
#ifdef sun386
	int	sc_sp;			/* sp to restore */
	int	sc_pc;			/* pc to retore */
	int	sc_ps;			/* psl to restore */
	int	sc_eax;			/* eax to restore */
	int	sc_edx;			/* edx to restore */
#endif
};
#endif !LOCORE

#define	BADSIG		(void (*)())-1
#define	SIG_ERR		(void (*)())-1
#define	SIG_DFL		(void (*)())0
#define	SIG_IGN		(void (*)())1

#ifdef KERNEL
#define	SIG_CATCH	(void (*)())2
#endif KERNEL
#define	SIG_HOLD	(void (*)())3

/*
 * Macro for converting signal number to a mask suitable for sigblock().
 */
#define sigmask(m)	(1 << ((m)-1))
#endif	!_sys_signal_h
 

#undef ssignal
#undef sigset
#undef kill
#undef signal
#undef gsignal

typedef void SIG_FUNC_TYP(int);
typedef SIG_FUNC_TYP *SIG_TYP;
#define SIG_PF SIG_TYP

typedef void COMPLETE_SIG_FUNC_TYP(int, int, struct sigcontext*, char*);
typedef COMPLETE_SIG_FUNC_TYP *COMPLETE_SIG_TYP;
#define COMPLETE_SIG_PF COMPLETE_SIG_TYP

extern "C" {
	SIG_TYP signal(int, SIG_TYP);
	int kill(int, int);
	int sigpause(int);
	int sigblock(int);
	int sigsetmask(int);
	SIG_TYP ssignal(int, SIG_TYP);
	int gsignal(int);
	/* Following line commented out per mail from dmm 1992/04/17:
	 * since this is defined only in 5lib.a, the delaration should
	 * appear only in 5include/signal.h, not in sys/signal.h...
	 */
	// SIG_TYP sigset(int, SIG_TYP);
	int sigstack(const struct sigstack*, struct sigstack*);
	int sigvec(int, const struct sigvec*, struct sigvec*);
	int sigreturn(sigcontext*);
#ifndef sigmask
	int sigmask(int);
#endif
}

inline COMPLETE_SIG_TYP signal(int s, COMPLETE_SIG_TYP f)
{
	return (COMPLETE_SIG_TYP)signal(s, (SIG_TYP)f);
}
inline COMPLETE_SIG_TYP ssignal(int s, COMPLETE_SIG_TYP f)
{
	return (COMPLETE_SIG_TYP)ssignal(s, (SIG_TYP)f);
}
// inline COMPLETE_SIG_TYP sigset(int s, COMPLETE_SIG_TYP f)
// {
// 	return (COMPLETE_SIG_TYP)sigset(s, (SIG_TYP)f);
// }

/* The type of these defines are wrong in the native header.
*/


#ifdef SIG_ERR
#undef SIG_ERR
#define SIG_ERR (SIG_PF)-1
#endif

#ifdef BADSIG
#undef BADSIG
#define BADSIG SIG_ERR
#endif

#ifdef SIG_DFL
#undef SIG_DFL
#define SIG_DFL (SIG_PF)0
#endif

#ifdef SIG_IGN
#undef SIG_IGN
#define SIG_IGN (SIG_PF)1
#endif

#ifdef KERNEL

#ifdef SIG_CATCH
#undef SIG_CATCH
#define SIG_CATCH (SIG_PF)2
#endif

#endif

#ifdef SIG_HOLD
#	undef SIG_HOLD
#	ifdef SIG_CATCH
#		define SIG_HOLD (SIG_PF)3
#	else
#		define SIG_HOLD (SIG_PF)2
#	endif
#endif


#endif
