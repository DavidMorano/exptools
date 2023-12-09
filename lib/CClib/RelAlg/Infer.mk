#ident "@(#) /sable/sdb/ra/templatesMk/s.Infer.mk"
 #	Copyright (c) 1989,1990,1991 AT&T - All Rights Reserved

.SUFFIXES:
.SUFFIXES: .dd .cpp .o .a .H .h .ex .ut .sh .C .c .1 .1MS .3 .3MS .4 .4MS .ug .UG 

.dd.cpp:
	m4 $*.m4 | grep '#define' >$*.cpp
	-@if [ -f $(MAN_INCLUDE)/$*.cpp ]; then rm -f $(MAN_INCLUDE)/$*.cpp; fi
	$(LN) $(LNFLAGS) $*.cpp $(MAN_INCLUDE)

.C.o:
	@if [ -f $*.c ]; then chmod ug+w $*.c; fi
	m4 $(M4FLAGS) $*.C >$*.c
	@chmod -w $*.c
	@if [ -f $*.o ]; then chmod ug+w $*.o; fi
	$(CPLUSPLUS) $(CFLAGS) $(INLINE) -c `pwd`/$*.c
	@chmod -w $*.o


.C.a:
	@if [ -f $*.c ]; then chmod ug+w $*.c; fi
	m4 $(M4FLAGS) $*.C >$*.c
	@chmod -w $*.c
	$(CPLUSPLUS) $(CFLAGS) $(INLINE) -c `pwd`/$*.c
	ar $(ARFLAGS) $@ $*.o
	-rm -f $*.o

.H.h:
	@if [ -f $*.h ]; then chmod ug+w $*.h; fi
	m4 $(M4FLAGS) $*.H > $*.h
	@chmod -w $*.h
	-@if [ -f $(INCLUDE)/$*.h ]; then rm -f $(INCLUDE)/$*.h; fi
	ln -f $*.h $(INCLUDE)

.C:     
	@if [ -f $*.c ]; then chmod ug+w $*.c; fi
	m4 $(M4FLAGS) $*.C >$*.c
	@chmod -w $*.c
	@if [ -f $* ]; then chmod ug+w $*; fi
	$(CPLUSPLUS) $(CFLAGS) $(INLINE) `pwd`/$*.c $(OFILES) $(LDFLAGS) -o $*
	@chmod -w $*
	-@if [ -f $(BINDIR)/$* ]; then rm -f $(BINDIR)/$*; fi
	$(LN) $(LNFLAGS) $* $(BINDIR)


.3.3MS:
	@if [ -f $*.3MS ]; then chmod ug+w $*.3MS; fi
	@if [ -f $*.3PR ]; then chmod ug+w $*.3PR; fi
	-/lib/cpp -I$(MAN_INCLUDE) $*.3  | $(MMSED) | cat $(LOCAL_STRINGS) - | $(DSPP) | tbl | cat $(LOCAL_MACROS) - | $(ROFF) -mm -rN4 | col -x > $*.3PR 
	-col -b -x <$*.3PR > $*.3MS
	-@chmod -w $*.3MS $*.3PR
	-@if [ -f $(MAN)/$*.3MS ]; then rm -f $(MAN)/$*.3MS; fi
	$(LN) $(LNFLAGS) $*.3MS $(MAN)
	-@if [ -f $(MAN)/$*.3PR ]; then rm -f $(MAN)/$*.3PR; fi
	$(LN) $(LNFLAGS) $*.3PR $(MAN)
