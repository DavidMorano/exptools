#ident	"@(#)C++env:lib/task/mk/makefile	1.1"
# Sun mods @(#)makefile 1.2 88/07/03 SMI
# Ported to V2.0 by GRT 89/09/28
# Reported to V2.1 by GRT 90/09/05
# Edited for single-directory compilation by GRT 90/10/02
###############################################################################
#			Copyright (c) 1984 AT&T
#	  		  All Rights Reserved  	
#
#	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T
#	
#	The copyright notice above does not evidence any   	
#	actual or intended publication of such source code.
#
###############################################################################
O_TASK		=	erand.o event.o fudge.o hw_stack.o obj.o qhead.o qtail.o sched.o sim.o swap.o swap_supp.o task.o timer.o 
OFILES	=	$(O_TASK)
CC	=	CC

# macros handed down from top-level C++ makefile
# machine-dependent macros come first

# type of operating system
#SYS=SYSV
SYS=BSD
BSD=1

# processor type
#MACH=3b
#MACH=vax
#MACH=386
#68k is for Sun-2 or Sun-3
#MACH=68k
MACH=sparc

MAKE	=	make
SHELL	=	/bin/sh
CCFLAGS	=	-O2 -D$(SYS)
CCOPT0	=	-D$(SYS)
CCOPT1	=	-O1 -D$(SYS)

# source files and makefiles merged into common directory
SRC=.

# commanded executed in top-level C++ makefile
# $(MAKE) CC="$(CC)" CCFLAGS="$(CCFLAGS)" CCOPT0="$(CCOPT0)" CCOPT1="$(CCOPT1)" $(SYS)=1 MACH=$(MACH)

libntask.a:	$(OFILES)
		ar r libntask.a $(OFILES)
		ar r libntask.a $(OFILES)
		if test "$(BSD)" ; then ranlib libntask.a; fi

erand.o:	$(SRC)/erand.c
	$(CC) $(CCFLAGS) -I$(SRC) -c $(SRC)/erand.c

event.o:	$(SRC)/event.c
	$(CC) $(CCFLAGS) -I$(SRC) -c $(SRC)/event.c

fudge.o:	$(SRC)/hw_stack.h $(SRC)/fudge.c
	case "$(MACH)" in						\
	sparc)	$(CC) $(CCOPT0) -I$(SRC) -c $(SRC)/fudge.c ;;	\
	68k)	$(CC) $(CCOPT1) -I$(SRC) -c $(SRC)/fudge.c ;;	\
	*)	$(CC) $(CCFLAGS) -I$(SRC) -c $(SRC)/fudge.c ;;	\
	esac

$(SRC)/fudge.c:	$(SRC)/fudge.c.$(MACH)
	cp $(SRC)/fudge.c.$(MACH) $(SRC)/fudge.c

$(SRC)/swap.s:	$(SRC)/swap.s.$(MACH)
	cp $(SRC)/swap.s.$(MACH) $(SRC)/swap.s

hw_stack.o:	$(SRC)/hw_stack.h $(SRC)/hw_stack.c
	case "$(MACH)" in						\
	sparc)	$(CC) $(CCOPT0) -I$(SRC) -c $(SRC)/hw_stack.c ;;	\
	68k)	$(CC) $(CCOPT1) -I$(SRC) -c $(SRC)/hw_stack.c ;;	\
	*)	$(CC) $(CCFLAGS) -I$(SRC) -c $(SRC)/hw_stack.c ;;	\
	esac

obj.o:		$(SRC)/obj.c
	$(CC) $(CCFLAGS) -I$(SRC) -c $(SRC)/obj.c

qhead.o:	$(SRC)/qhead.c
	$(CC) $(CCFLAGS) -I$(SRC) -c $(SRC)/qhead.c

qtail.o:	$(SRC)/qtail.c
	$(CC) $(CCFLAGS) -I$(SRC) -c $(SRC)/qtail.c

sched.o:	$(SRC)/sched.c
	$(CC) $(CCFLAGS) -I$(SRC) -c $(SRC)/sched.c

sim.o:		$(SRC)/hw_stack.h $(SRC)/sim.c
	$(CC) $(CCFLAGS) -I$(SRC) -c $(SRC)/sim.c

swap.o:		$(SRC)/swap.s
	case "$(MACH)" in					\
	sparc)							\
		echo /bin/cp $(SRC)/swap.s $(SRC)/swap.S ;	\
		/bin/cp $(SRC)/swap.s $(SRC)/swap.S ;		\
		/bin/cc $(CCOPT0) -I$(SRC) -c $(SRC)/swap.S ;;	\
	68k)							\
		$(CC) $(CCOPT1) -I$(SRC) -c $(SRC)/swap.s ;;	\
	*)							\
		$(CC) $(CCFLAGS) -I$(SRC) -c $(SRC)/swap.s ;;	\
	esac


swap_supp.o:	$(SRC)/swap_supp.c
	$(CC) $(CCFLAGS) -I$(SRC) -c $(SRC)/swap_supp.c

task.o:		$(SRC)/hw_stack.h $(SRC)/task.c
	case "$(MACH)" in						\
	sparc)	$(CC) $(CCOPT0) -I$(SRC) -c $(SRC)/task.c ;;	\
	68k)	$(CC) $(CCOPT1) -I$(SRC) -c $(SRC)/task.c ;;	\
	*)	$(CC) $(CCFLAGS) -I$(SRC) -c $(SRC)/task.c ;;	\
	esac

timer.o:	$(SRC)/timer.c
	$(CC) $(CCFLAGS) -I$(SRC) -c $(SRC)/timer.c
