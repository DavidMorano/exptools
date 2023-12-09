##########################################################################
# Hardcoded paths here may have to change on your system
##########################################################################

# 630MTG development tools 
include /usr/add-on/630/src/stand.defs
include /usr/add-on/630/src/stand.targ

# C++ compiler
CCC = /usr/add-on/local/bin/CC 





##########################################################################
#  make combinations and utilities:
##########################################################################

# entire package
all : $(PFLIB) selfdoc pfcmain gialmms demo

# entire package except 630 MTG objects
allx630 : $(PFLIB) selfdoc pfcmain demo

CLEAN= $(DOBJS) $(PFOBJS) $(PFCOBJS) $(GIOBJS) selfdoc.o

CLOBBER= $(PFLIB) selfdoc pfcmain gialmms demo


##########################################################################
### PANELFEATURES HOST LIBRARY
##########################################################################

PFLIB = pf.a 

PFHEADR = ascknob.h cluster.h display.h knob.h knobtypes.h \
	panel.h pf.h screen.h enumhelp.h ascdisp.h proto.h

PFOBJS = pf.o knob.o ascknob.o cluster.o display.o panel.o knobtypes.o \
	screen.o pffind.o pfshow.o pfwrite.o pfgraphics.o \
	enumhelp.o setup.o pfattrib.o lowio.o ascdisp.o pfsnap.o proto.o

PFSRC =	pf.c knob.c ascknob.c cluster.c display.c panel.c knobtypes.c \
	screen.c pffind.c pfshow.c pfwrite.c pfgraphics.c \
	enumhelp.c setup.c pfattrib.c lowio.c ascdisp.c pfsnap.c proto.c 

############################################################

selfdoc : selfdoc.c
	$(CCC) selfdoc.c -o selfdoc
	echo "selfdoc made"

$(PFLIB) : $(PFOBJS) 
	ar cr $(PFLIB) $(PFOBJS)
	echo "PANELFEATURES LIBRARY - (pf.a) made"


lowio.o : lowio.c pf.h giproto.h
	cc -c lowio.c 

pf.o : pf.c pf.h
	$(CCC) -c  $*.c

knob.o : knob.c knob.h pf.h
	$(CCC) -c  $*.c

ascknob.o : ascknob.c ascknob.h pf.h
	$(CCC) -c  $*.c

ascdisp.o : ascdisp.c ascdisp.h pf.h
	$(CCC) -c  $*.c

cluster.o : cluster.c cluster.h pf.h
	$(CCC) -c  $*.c
	
display.o : display.c display.h pf.h
	$(CCC) -c  $*.c

panel.o : panel.c panel.h pf.h
	$(CCC) -c  $*.c

knobtypes.o : knob.o knobtypes.c knobtypes.h
	$(CCC) -c  $*.c

screen.o : screen.c screen.h pf.h
	$(CCC) -c  $*.c

setup.o : setup.c $(PFHEADR)
	$(CCC) -c  $*.c

pffind.o : pffind.c $(PFHEADR)
	$(CCC) -c  $*.c

proto.o : proto.c $(PFHEADR)
	$(CCC) -c  $*.c

pfsnap.o : pfsnap.c $(PFHEADR)
	$(CCC) -c  $*.c

pfattrib.o : pfattrib.c $(PFHEADR)
	$(CCC) -c  $*.c

pfshow.o : pfshow.c pfgraphics.h $(PFHEADR)
	$(CCC) -c  $*.c

pfwrite.o : pfwrite.c $(PFHEADR)
	$(CCC) -c  $*.c

pfgraphics.o : pfgraphics.c pf.h
	$(CCC) -c  $*.c

enumhelp.o : enumhelp.c enumhelp.h
	$(CCC) -c  $*.c



##########################################################################
#  make the CURSES based interface for non 630 MTG terminals
##########################################################################

PFCHEAD = pfc.h pfcfunc.h pfcglobals.h pfcglobdef.h pfcdef.h
PFCOBJS = pfclowio.o pfcmain.o pfcdraw.o pfcmsg.o pfcshorts.o \
	  pfchcmd.o pfckeys.o

###########################################################

pfcmain : pfcmain.o pfclowio.o pfcdraw.o pfcmsg.o pfcshorts.o \
	pfchcmd.o pfckeys.o
	$(CCC) pfcmain.o pfclowio.o pfcdraw.o pfcmsg.o \
	 pfcshorts.o pfchcmd.o pfckeys.o -lcurses -o pfcmain
	echo " 'pfcmain - non-630 MTG graphics interface'  now loaded"

pfclowio.o : pfclowio.c
	cc -c pfclowio.c 

pfcmain.o : pfcmain.c $(PFCHEAD)
	$(CCC) -c  $*.c

pfcdraw.o : pfcdraw.c $(PFCHEAD)
	$(CCC) -c  $*.c

pfcmsg.o : pfcmsg.c $(PFCHEAD)
	$(CCC) -c  $*.c

pfcshorts.o : pfcshorts.c $(PFCHEAD)
	$(CCC) -c  $*.c

pfchcmd.o : pfchcmd.c $(PFCHEAD)
	$(CCC) -c  $*.c

pfckeys.o : pfckeys.c $(PFCHEAD)
	$(CCC) -c  $*.c

##########################################################################
#  make 630 MTG download code module for graphics interface
##########################################################################


MCFLAGS= -O 

GIOBJS= gialmms.o gihcmd.o gishorts.o gidraw.o gimouse.o giwindow.o \
	giwdraw.o giutil.o giplot.o flipstring.o




########
gialmms: gialmms.o gihcmd.o gishorts.o giutil.o gidraw.o gimouse.o \
	 giwindow.o giwdraw.o giplot.o flipstring.o
	$(MCC) $(MCFLAGS)  gialmms.o gihcmd.o gishorts.o giwindow.o giwdraw.o \
		 giutil.o gimouse.o gidraw.o giplot.o flipstring.o \
		-lm -o gialmms
	chmod 644 gialmms
	echo " 'gialmms - 630 MTG graphics interface'  now loaded"

gialmms.o: gialmms.c gi.h gidef.h
	$(MCC) $(MCFLAGS)  -c  gialmms.c 

gihcmd.o: gihcmd.c gi.h gidef.h giwindow.h
	$(MCC) $(MCFLAGS)  -c  gihcmd.c 

gishorts.o: gishorts.c gi.h gidef.h giwindow.h
	$(MCC) $(MCFLAGS)  -c  gishorts.c 

giplot.o: giplot.c gi.h gidef.h giwindow.h
	$(MCC) $(MCFLAGS)  -c  giplot.c 

giutil.o: giutil.c gi.h gidef.h giwindow.h
	$(MCC) $(MCFLAGS)  -c  giutil.c 

gidraw.o: gidraw.c gi.h gidef.h giwindow.h
	$(MCC) $(MCFLAGS)  -c  gidraw.c 

gimouse.o: gimouse.c gi.h gidef.h giwindow.h
	$(MCC) $(MCFLAGS)  -c  gimouse.c 

giwindow.o: giwindow.c gi.h gidef.h giwindow.h
	$(MCC) $(MCFLAGS)  -c  giwindow.c 

giwdraw.o: giwdraw.c gi.h gidef.h giwindow.h
	$(MCC) $(MCFLAGS)  -c  giwdraw.c 

flipstring.o: flipstring.c 
	$(MCC) $(MCFLAGS)  -c  flipstring.c 


##########################################################################
# Demo Program
##########################################################################

DHEADR = wavecalc.h 

DOBJS =	wavecalc.o demo.o

DSRC =	wavecalc.c demo.c


demo :  demo.o wavecalc.o $(PFLIB)
	$(CCC) $(DOBJS) $(PFLIB) -o demo

wavecalc.o : wavecalc.c $(DHEADR)
	$(CCC) -c $*.c

demo.o : demo.c $(DHEADR)
	$(CCC) -c $*.c

