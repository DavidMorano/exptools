#      Copyright (c) 1989, 1990, 1991 AT&T - All Rights Reserved

include variable.mk

#INCLUDE = include directory
#LIBDIR = lib directory
HFILES=sblib.h lcurses.h wgets.h relation.h
SLIB=$(LDIR)/libsblib.a
RLIB=$(LDIR)/librelation.a

.PRECIOUS: $(LIB)

all: include lib cmd man

include: $(HFILES)

sblib.h: sblib.H sblib.dd counter.dd file.dd roll.dd string.dd pathname.dd\
	error.dd pattern.dd list.dd link1.dd link1qs.dd link2.dd vfd.dd\
	vfile.dd wgets.dd curse.dd form.dd node.dd menu.dd heapchck.dd

relation.h: relation.H r_error.dd dname.dd domain.dd constr.dd attribut.dd\
	predicat.dd tuple.dd intensin.dd IValue.dd ext.dd ws_ext.dd bf_ext.dd\
	af_ext.dd relation.dd hash.dd combine.dd afRel.dd bfRel.dd bfLock.dd\
	wsRel.dd formRel.dd

lib: include libsblib librelation

libsblib: $(SLIB)(counter.o) $(SLIB)(curse.o) $(SLIB)(error.o) $(SLIB)(file.o)\
	$(SLIB)(form.o) $(SLIB)(list.o) $(SLIB)(link1.o) $(SLIB)(link2.o)\
	$(SLIB)(menu.o) $(SLIB)(node.o) $(SLIB)(pathname.o) $(SLIB)(pattern.o)\
	$(SLIB)(roll.o) $(SLIB)(string.o) $(SLIB)(upper.o) $(SLIB)(vfd.o)\
	$(SLIB)(vfile.o) $(SLIB)(wgets.o)

librelation: $(RLIB)(IValue.o) $(RLIB)(attribut.o) $(RLIB)(predicat.o)\
	$(RLIB)(constr.o) $(RLIB)(dname.o) $(RLIB)(domain.o) $(RLIB)(af_ext.o)\
	$(RLIB)(bf_ext.o) $(RLIB)(ext.o) $(RLIB)(ws_ext.o) $(RLIB)(intensin.o)\
	$(RLIB)(lineTupl.o) $(RLIB)(r_error.o) $(RLIB)(afRel.o) $(RLIB)(bfLock.o)\
	$(RLIB)(bfRel.o) $(RLIB)(closure.o) $(RLIB)(combine.o) $(RLIB)(formRel.o)\
	$(RLIB)(halfjoin.o) $(RLIB)(join.o) $(RLIB)(output.o) $(RLIB)(plusEq.o)\
	$(RLIB)(project.o) $(RLIB)(rConstr.o) $(RLIB)(relation.o) $(RLIB)(select.o)\
	$(RLIB)(setdiff.o) $(RLIB)(strFuncs.o) $(RLIB)(union.o) $(RLIB)(hash.o)\
	$(RLIB)(tuple.o)

cmd: $(BINDIR)/dspp

$(BINDIR)/dspp: dspp.c
	cc dspp.c -o $(BINDIR)/dspp

man: maninclude 3man

maninclude: $(MAN_INCLUDE)/ra2.mac

m $(MAN_INCLUDE)/ra2.mac: ra2.mac
	-@ mkdir $(MAN_INCLUDE) 2>/dev/null
	-@ $(LN) $(LNFLAGS) ra2.mac $(MAN_INCLUDE)

m $(MAN_INCLUDE)/ra2.str: ra2.str
	-@ mkdir $(MAN_INCLUDE) 2>/dev/null
	-@ $(LN) $(LNFLAGS) ra2.str $(MAN_INCLUDE)

3man: sblib3man rel3man

sblib3man: introSB.3MS counter.3MS curse.3MS error.3MS file.3MS file.3MS list.3MS\
	menu.3MS monitor.3MS node.3MS pathname.3MS pattern.3MS roll.3MS\
	string.3MS upper.3MS vfd.3MS wgets.3MS

rel3man: introRA.3MS IValue.3MS attribut.3MS domain.3MS ext.3MS intensin.3MS\
	relation.3MS tuple.3MS

clean:
	mv dspp.c dspp.sav
	mv wgets.c wgets.sav
	rm -f $(HFILES) *.c *.o *MS *PR *.cpp
	mv dspp.sav dspp.c
	mv wgets.sav wgets.c

clobber: clean
	cd ${INCLUDE}; rm -f $(HFILES) 
	rm -f $(SLIB) $(RLIB)
	rm -f $(MAN)/introSB.[34]* 

include Infer.mk
