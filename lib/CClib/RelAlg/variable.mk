#ident "@(#) /sable/sdb/ra/templatesMk/s.variable.mk"
 #      Copyright (c) 1989, 1990, 1991 AT&T - All Rights Reserved

 #  XTRACFLAGS should correspond to extra CFLAGS needed.  For example it should
 #  contain include directories that need to be searched 
 #  in addition to the standard UNIX ones and your local include directory.
 #  It should include the "-I" characters.
 #
 #  XTRALDFLAGS should correspond to directories that contain project libraries 
 #  that need to be linked in but will not be updated by your source files.
 #  It should include the "-L" characters.

BINDIR=$(msSOURCE)/bin
INCLUDE=$(msSOURCE)/include
LDIR=$(msSOURCE)/lib
MAN=$(msSOURCE)/man
MAN_INCLUDE=$(msSOURCE)/man/include
LOCAL_MACROS=$(MAN_INCLUDE)/ra2.mac
LOCAL_STRINGS=$(MAN_INCLUDE)/ra2.str
DSPP=$(BINDIR)/dspp
MMSED=sed -n -e '/^.PH/,$$p'

CPLUSPLUS=CC
CFLAGS=-I$(INCLUDE) $(XTRACFLAGS)
ROFF=nroff
#ROFF=iroff

#
#  LDFLAGS for the 3b2
#
LDFLAGS=-L$(LDIR) $(XTRALDFLAGS) -lrelation -lsblib -lPW -lcurses -lmalloc
#
#  LDFLAGS for the SUN  (it doesn't have a separate malloc library)
#
#LDFLAGS=-L$(LDIR) $(XTRALDFLAGS) -lrelation -lsblib -lPW -lcurses

M4FLAGS=-Uindex -Ulen -Ueval $(DEBUG)
ARFLAGS=-r
LN=ln
LNFLAGS=-f
