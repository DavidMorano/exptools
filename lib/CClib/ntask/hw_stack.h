/*ident	"@(#)C++env:lib/task/task/hw_stack.h	1.2" */
/* Sun mods %Z%%M% %I% %E% SMI */
/* Ported to V2.0 by GRT 89/09/28 */
/* Re-ported to V2.1 by GRT 90/09/04 */
/**************************************************************************
			Copyright (c) 1984 AT&T
	  		  All Rights Reserved  	

	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T
	
	The copyright notice above does not evidence any   	
	actual or intended publication of such source code.

*****************************************************************************/
#ifndef __HW_STACK_H
#define __HW_STACK_H

/* Machine-dependent macros, typedefs, and externs for task library.
 * Porting these requires intimate knowledge of the stack frame layout,
 * call and return sequences for the machine.
 * They are used by task.c and fudge.c and sim.c.
 * 
 * Some are grouped according to direction of stack growth.
 * 
 * New-style asms would eliminate function calls for TOP, AP, and FP.
 */

typedef unsigned char MACHINE_BYTE;

#if defined(M32) || defined(u3b2) || defined(u3b5) || defined(u3b15)
#define BELLMAC_CHIP
#endif
#if defined(u3b) || defined(BELLMAC_CHIP) 
#define PROC_3B
#endif

////////////////////////// AT&T 3B series //////////////////////////
#ifdef PROC_3B

#define	STACK_GROWS_UP
/* typedefs for the hardware state saved on the stack after a call */
typedef struct {
	unsigned long	r3;
	unsigned long	r4;
	unsigned long	r5;
	unsigned long	r6;
	unsigned long	r7;
	unsigned long	r8;

} HW_REGS;

struct FrameLayout {
	short   n_saved;	// number of registers saved in this frame.
				// (3B's don't have masks of regs saved)
		FrameLayout(int*);	// called with frame pointer
};

extern "C" {
extern int* FP();	/* FP of caller */
extern int* AP();	/* AP of caller */
extern void FUDGE_SP(int*, int*);	/* reset ap to first arg */
extern int* TOP();	/* SP-1 of caller (pnts to last used word in stack) */
}
extern void	save_saved_regs(HW_REGS*, int*);

#define MAXINT_AS_FLOAT 2147483647.0

/* Save all current regs and regs saved in this frame in reg_struct_p,
 * for restoration when child runs.
 * Note: SAVE_REGS needed in case task::restore() saves more regs
 * than task::task.
 */
#define	SAVE_CHILD_REGS(reg_struct_p)				\
	SAVE_REGS(reg_struct_p);				\
	save_saved_regs((reg_struct_p), ta_fp);

extern "C" {
extern void set_r3(int*);
extern void set_r4(int*);
extern void set_r5(int*);
extern void set_r6(int*);
extern void set_r7(int*);
extern void set_r8(int*);
}

#ifdef u3b

#define OLD_FP(fp)	( *( (int*)(fp) - 11 ) )
#define OLD_AP(fp)	( *( (int*)(fp) - 12 ) )
#define OLD_PC(fp)	( *( (int*)(fp) - 13 ) )
#define FIRST_SAVED_REG_P(fp, n)	((int*)(fp) - (n))
#define	LAST_SAVED_REG_P(fp,n)		((int*)(fp) - 1)

#define IS_SAVE_OPCODE(instr) ((MACHINE_BYTE)(instr) == (MACHINE_BYTE)0x7A)

/* Given a pointer to a save instruction, yield the number of registers saved */
#define N_SAVED_REGS(instr)	(((char *)(instr))[1] >> 4)


#else	/* u3b2, u3b5, u3b15 */


#define OLD_FP(fp)	( *( (int*)(fp) - 7 ) )
#define OLD_AP(fp)	( *( (int*)(fp) - 8 ) )
#define OLD_PC(fp)	( *( (int*)(fp) - 9 ) )	
#define FIRST_SAVED_REG_P(fp,n)	( (int*)(fp) - 6 )
#define LAST_SAVED_REG_P(fp,n)	( (int*)(fp) - 6 + (n) - 1)
 
#define SAVE_OPERAND(instr)	(((char *)(instr))[1] & 0xf)

/* Given a pointer to a save instruction, yield the number of registers saved */
#define N_SAVED_REGS(instr)	(8 - SAVE_OPERAND(instr) + 1)

#define IS_SAVE_OPCODE(instr) ((MACHINE_BYTE)(instr) == (MACHINE_BYTE)0x10)

#endif
/* u3b, u3b2, u3b5, u3b15 */
#endif /* PROC_3B */


//////////////////////////// DEC VAX ////////////////////////////
#ifdef vax

#define	STACK_GROWS_DOWN
extern "C" {
extern int* FP();	/* FP of caller */
extern int* TOP();	/* SP of caller (pnts to last used word in stack) */
}
#define FUDGE_SP(ap, fp)	/* unnecessary on vax */
#define AP()		0	/* unnecessary on vax */
#define OLD_AP(fp)		(*((int*)(fp) + 2))
#define OLD_FP(fp)		(*((int*)(fp) + 3))
#define OLD_PC(fp)		(*((int*)(fp) + 4))
#define	FIRST_SAVED_REG_P(fp,n)	  ((int*)(fp) + 5)
#define	LAST_SAVED_REG_P(fp,n)	  ((int*)(fp) + 5 + (n) - 1)
#define	ENTRY_MASK(fp)		(*((short*)(fp) + 3))
#define	N_VOL_REGS	6    /* assumes compiler only allocates r6-r11 for users */

#define MAXINT_AS_FLOAT 2147483647.0
#define	STACK_GROWS_DOWN

/* typedef for the hardware state saved on the stack after a call */
typedef struct {
	unsigned long	r6;
	unsigned long	r7;
	unsigned long	r8;
	unsigned long	r9;
	unsigned long	r10;
	unsigned long	r11;

} HW_REGS;

/* Save all current regs and regs saved in this frame in reg_struct_p,
 * for restoration when child runs.  On the VAX, save_saved_regs is
 * unnecessary because the return from swap will restore the regs saved
 * in task:task.
 */
#define	SAVE_CHILD_REGS(reg_struct_p)			\
	SAVE_REGS(reg_struct_p);			

extern "C" {
extern void set_r6(int*);
extern void set_r7(int*);
extern void set_r8(int*);
extern void set_r9(int*);
extern void set_r10(int*);
extern void set_r11(int*);
}

#endif

///////////////////// Motorola-680x0/Sun-3 (&Sun-2) /////////////////////
#ifdef mc68000		/* Really, ifdef sun--stack frame layout
			 * is different on a UNIX PC, for example
			 */

#define	STACK_GROWS_DOWN
/* typedefs for the hardware state saved on the stack after a call.
 * Assumes d0, d1, a0, a1 are scratch registers, a6 is fp, a7 is sp.
 * a0 and a1 are included so that loops through a mask word work correctly.
 */
typedef struct {
	unsigned long	d2;
	unsigned long	d3;
	unsigned long	d4;
	unsigned long	d5;
	unsigned long	d6;
	unsigned long	d7;
	unsigned long	a0;	/* should not be used */
	unsigned long	a1;	/* should not be used */
	unsigned long	a2;
	unsigned long	a3;
	unsigned long	a4;
	unsigned long	a5;
} HW_REGS;

struct FrameLayout {
	short	offset;			// of top of saved registers from fp
	unsigned short	mask;   	// of registers saved in frame
		FrameLayout(int*);	// called with frame pointer
};

extern int*	Skip_pc_p;		/* global for FUDGE_SP and fudge_sp */
extern "C" {
extern int* FP();			/* FP of caller */
extern void FUDGE_SP(int*, int*);	/* prepare to reset sp */
extern void fudge_sp();			/* reset sp on return through fudged
					 * frame */
extern int* TOP();			/* SP of caller
					 * (pnts to last used word in stack) */
}
#define AP()		0	/* unnecessary on mc68000 */
#define OLD_AP(fp)	0	/* unnecessary on mc68000 */
#define OLD_FP(fp)	(*((int*)(fp)))
#define	OLD_PC(fp)	(*((int*)(fp) + 1))
#define	OLD_PC_P(fp)	((int*)(fp) + 1)
#define FIRST_SAVED_REG_P(fp, o)	((int*)(fp) + (o))


extern void	save_saved_regs(HW_REGS*, int*);

/* Save all current regs and regs saved in this frame in reg_struct_p,
 * for restoration when child runs.
 * Note: SAVE_REGS needed in case task::restore() saves more regs
 * than task::task.
 */
#define	SAVE_CHILD_REGS(reg_struct_p)				\
	SAVE_REGS(reg_struct_p);				\
	save_saved_regs((reg_struct_p), ta_fp);

extern "C" {
extern void set_d2(int*);
extern void set_d3(int*);
extern void set_d4(int*);
extern void set_d5(int*);
extern void set_d6(int*);
extern void set_d7(int*);
extern void set_a2(int*);
extern void set_a3(int*);
extern void set_a4(int*);
extern void set_a5(int*);
}

#define MAXINT_AS_FLOAT 2147483647.0

#endif /* mc68000 */

//////////////////////////// intel 80386 ////////////////////////////
#ifdef i386

#define	STACK_GROWS_DOWN

/* typedefs for the hardware state saved on the stack after a call.
 * Assumes eax, ecx, edx are scratch registers, ebp is fp, esp is sp.
 */
typedef struct {
	unsigned long	edi;
	unsigned long	esi;
	unsigned long	ebx;
} HW_REGS;

struct FrameLayout {
	int	offset;			// of base of saved registers from fp
	unsigned short	mask;   	// of registers saved in frame
		FrameLayout(int*);	// called with frame pointer
};

extern int*	Skip_pc_p;		/* global for FUDGE_SP and fudge_sp */
extern "C" {
extern int* FP();			/* FP of caller */
extern void FUDGE_SP(int*, int*);	/* prepare to reset sp */
extern void fudge_sp();			/* reset sp on return through fudged
					 * frame */
extern int* TOP();			/* SP of caller
					 * (pnts to last used word in stack) */
}

#define AP()		0	/* unnecessary on i386 */
#define OLD_AP(fp)	0	/* unnecessary on i386 */
#define OLD_FP(fp)	(*((int*)(fp)))
#define	OLD_PC(fp)	(*((int*)(fp) + 1))
#define	OLD_PC_P(fp)	((int*)(fp) + 1)
#define FIRST_SAVED_REG_P(fp, o)	(((int*)(fp) - (o)) - 1)


extern void	save_saved_regs(HW_REGS*, int*);

/* Save all current regs and regs saved in this frame in reg_struct_p,
 * for restoration when child runs.
 * Note: SAVE_REGS needed in case task::restore() saves more regs
 * than task::task.
 */
#define	SAVE_CHILD_REGS(reg_struct_p)				\
	SAVE_REGS(reg_struct_p);				\
	save_saved_regs((reg_struct_p), ta_fp);

extern "C" {
extern void set_ebx(int*);
extern void set_esi(int*);
extern void set_edi(int*);
}

#define MAXINT_AS_FLOAT 2147483647.0

#endif /* i386 */

//////////////////////////// Amdahl/IBM ////////////////////////////
#ifdef uts


#define	STACK_GROWS_DOWN

struct FrameLayout {
	int	begreg;
	int	endreg;
	unsigned short mask;
	FrameLayout(int *);	// called with frame pointer
};

typedef struct {
	unsigned long	r0;
	unsigned long	r1;
	unsigned long	r2;
	unsigned long	r3;
	unsigned long	r4;
	unsigned long	r5;
	unsigned long	r6;
	unsigned long	r7;
	unsigned long	r8;
	unsigned long	r9;
	unsigned long	r10;
	unsigned long	r11;
	unsigned long	r12;
	unsigned long	r13;
	unsigned long	r14;
	unsigned long	r15;
} HW_REGS;

extern "C" {
extern int* FP();	/* FP of caller */
extern int* AP();	/* AP of caller */
extern int* TOP();	/* SP of caller (pnts to last used word in stack) */
extern void set_r2(int*);
extern void set_r3(int*);
extern void set_r4(int*);
extern void set_r5(int*);
extern void set_r6(int*);
extern void set_r7(int*);
extern void set_r8(int*);
extern void set_r9(int*);
extern void set_r10(int*);
extern void set_r11(int*);
};

#define OLD_FP(fp)      ( *( (int*)(fp) + 12 ) )
#define OLD_AP(fp)      ( *( (int*)(fp) + 12 ) )
#define OLD_PC(fp)      ( *( (int*)(fp) + 14 ) )
#define	OLD_SP(fp)	( *( (int*)(fp) + 13 ) )
#define FIRST_SAVED_REG_P(fp)	(fp) 
#define LAST_SAVED_REG_P(fp)    (fp + 15)
#define FUDGE_SP(ap, fp)	/* unnecessary on uts */

#define MAXINT_AS_FLOAT 2147483647.0

/* Save all current regs and regs saved in this frame in reg_struct_p,
 * for restoration when child runs.
 * Note: SAVE_REGS needed in case task::restore() saves more regs
 * than task::task.
 *
 * Note that for uts the FP and SP in New_task_regs must be adjusted to 
 * refer to the new child stack.
 */

#define	SAVE_CHILD_REGS(reg_struct_p)				\
	SAVE_REGS(reg_struct_p);				\
	save_saved_regs((reg_struct_p), ta_fp);			\
        OLD_FP(reg_struct_p) = int((int*)OLD_FP(ta_fp) - distance);\
        OLD_SP(reg_struct_p) = int((int*)OLD_SP(ta_fp) - distance);


extern void	save_saved_regs(HW_REGS*, int*);


#endif	/* uts */


//////////////////////////// Sun SPARC/Sun-4 ////////////////////////////
#ifdef sparc

//
// The sparc is different from the other machines represented here
// in three major ways:
//	1- Its stack frames are disjoint (arguments to a function
//	   can be stored in the middle of the parent's frame);
//	2- The role of frame pointer is shared by two registers --
//	   %sp (%o6) and %fp (%i6);
//	3- Stack switching requires a little help from the kernel.
//


#define	STACK_GROWS_DOWN
#define	N_GLOBAL_REGS	7
#define	N_STK_PARAMS	6

/* typedefs for the hardware state saved on the stack after a call.
 * SPARC always saves the same number of registers.  Here we just worry
 * about the global (%g1 - %g7) registers and the six words in the
 * caller's frame where the callee might have dumped its in-register
 * parameters.  The locals and ins are taken care of by the way they're
 * represented in the standard stack frame, and the compilers do not
 * expect the out-registers to be preserved across calls.
 */

typedef struct {					// Offsets (bytes)
	unsigned long	global_regs[ N_GLOBAL_REGS ];	//  0 - 27
	unsigned long	param_dump[ N_STK_PARAMS ];	// 28 - 51
} HW_REGS;

struct FrameLayout {
		// FullFrameLen is the length (in bytes) from %sp to the
		// far end (highest addresses) of the parent's frame -- in
		// order to be sure of getting all of my in-parameters,
		// we need to copy the parent's whole frame.
	int	FullFrameLen;
		FrameLayout(int*);	// called with frame pointer
};

extern int*	Skip_pc_p;		/* global for FUDGE_SP and fudge_sp */
extern "C" {
extern int* FP();			/* FP of caller */
extern void FUDGE_SP(int*, int*);	/* prepare to reset sp */
extern void fudge_sp();			/* reset sp on return through fudged
					 * frame */
extern int* TOP();			/* SP of caller */
}
#define AP()		0	/* unnecessary on sparc */
#define OLD_AP(fp)	0	/* unnecessary on sparc */
#define OLD_FP(fp)	(*((int*)(fp) + 14))
#define	OLD_PC(fp)	(*((int*)(fp) + 15))
#define	OLD_PC_P(fp)	((int*)(fp) + 15)

#define SAVE_CHILD_REGS( reg_struct_p ) SAVE_REGS( reg_struct_p )

#define MASK(x) ABS(x)
#define MAXINT_AS_FLOAT 2147483647.0

#endif		/* sparc */

//////////////////////////// Common code ////////////////////////////

#ifdef STACK_GROWS_DOWN
#define	STACK_LAST_WORD_P(b,s)	((b) - (s) + 1)
#define COPY_STACK(f,c,t)   while ((c)--) *(t)-- = *(f)--
#define ACTIVE_STK_SZ(b,t)  (b) - (t) + 1	/* size of active stack */
#ifdef sparc
	/* SPARC Stack must be aligned on double-word boundary.  Can't
	 * use <machine/asm.h> (q.v.) macro "SA" directly because it
	 * rounds up and we want to round down, and because STACK_BASE
	 * is used with "int *" variables instead of "char *".
	 */
#    include <machine/asm_linkage.h>
#    define SA_DOWN(X) ((X) & ~(STACK_ALIGN-1))
#    define STACK_BASE(b,s) (int *) ( SA_DOWN( (int)((b)+(s)-1)) )
#else
#    define STACK_BASE(b,s)     (b) + (s) - 1
#endif
#define SAVED_AREA(b,s)     (b) - (s) + 1
#endif

#ifdef STACK_GROWS_UP
#define	STACK_LAST_WORD_P(b,s)	((b) + (s) - 1)
#define COPY_STACK(f,c,t)   while ((c)--)  *(t)++ = *(f)++
#define ACTIVE_STK_SZ(b,t)  (t) - (b) + 1	/* size of active stack */
#define STACK_BASE(b,s)     (b)
#define SAVED_AREA(b,s)     (b)
#endif

/* externs needed for all machines, definitions in hw_stack.c */
extern "C" {
extern void SAVE_REGS(HW_REGS*);	/* call SAVE_REGS(&New_task_regs)
					 * copies caller's registers into
					 * HW_REGS structure
					 */
};


#endif /* __HW_STACK_H */
