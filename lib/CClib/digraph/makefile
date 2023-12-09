ROOT = /usr2/mte/SFMAC/Lib/libsfmac

BIN = $(ROOT)

LIBS = $(ROOT)

PRODUCT = libdigraph

CC = CC

CFLAGS = -g 

LIBFLAGS = -lString

###############################################################################

SRC = Hash.c \
	SHash.c \
	universe.c \
	node.c \
	edge.c \
	sllist.c \
	int_sllist.c 


# Object files

OBJ = Hash.o \
	SHash.o \
	universe.o \
	node.o \
	edge.o \
	sllist.o \
	int_sllist.o

# Clean up the directory
cleanup:
	$(DIRCLEAN)

# Print the source code
PRTFILES = 

print:
	/usr/5bin/pr -n $(PRTFILES) | bubba lp -olandscape

back:



# These are the .o Dependencies

Hash.o:  Hash.c \
		$(ROOT)/Hash.h  \
		$(ROOT)/general.h


SHash.o:  SHash.c \
		$(ROOT)/SHash.h \
		$(ROOT)/general.h


edge.o:  edge.c \
		$(ROOT)/edge.h \
		$(ROOT)/universe.h \
		$(ROOT)/node.h \
		$(ROOT)/sllist.h \
		$(ROOT)/int_sllist.h \
		$(ROOT)/general.h


node.o:	node.c \
		$(ROOT)/edge.h \
		$(ROOT)/universe.h \
		$(ROOT)/node.h \
		$(ROOT)/sllist.h \
		$(ROOT)/int_sllist.h \
		$(ROOT)/general.h

universe.o:	universe.c \
		$(ROOT)/edge.h \
		$(ROOT)/universe.h \
		$(ROOT)/node.h \
		$(ROOT)/sllist.h \
		$(ROOT)/int_sllist.h \
		$(ROOT)/general.h

sllist.o:	sllist.c \
		$(ROOT)/sllist.h 

int_sllist.o:	int_sllist.c \
		$(ROOT)/int_sllist.h

product:	$(PRODUCT)

$(PRODUCT):	$(OBJ)
#		$(CC) -o $(PRODUCT) $(CFLAGS) $(OBJ) $(LIBFLAGS) 
		ar r $(PRODUCT).a $(OBJ)
		ranlib $(PRODUCT).a

