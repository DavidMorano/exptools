#=======================================================================
# INSTALLER: set the following definitions for your environment
#=======================================================================
CC=NCC

TRACE_DIR=$(HOME)/rje/murray

# where to install the trace controller
INSDIR = $(TRACE_DIR)

# where to install/retrieve trace library
LIB = $(TRACE_DIR)/lib

# where to install/retrieve trace include files 
TRACE_INC = $(TRACE_DIR)/include

# C++ includes
CC_INC = /usr/include/NCC

#=======================================================================
# End of normal customization
#=======================================================================

CFLAGS=-O
LDFLAGS =
AR = ar

TRACE_LIB = trace.a
TRACER = tracer

LIBOBJS = btrace.o f_trace.o global.o p_trace.o trace_sm.o write_buf.o

TRACE_HDRS = c_tr_hdrs.h c_btrace.h c_f_trace.h c_sm_slot.h c_trace_sm.h c_write_buf.h

SRC = btrace.c f_trace.c global.c p_trace.c trace_sm.c write_buf.c

#======================================================================
#                            TARGETS
#======================================================================

all: $(TRACE_LIB) $(TRACER)

# trace library
$(TRACE_LIB): $(LIBOBJS)
	$(AR) cruv $(TRACE_LIB) $(LIBOBJS)

$(LIBOBJS): $(TRACE_HDRS)
	$(CC) $(CFLAGS) -c $(@F:.o=.c)

# trace controller
$(TRACER): main.c $(TRACE_LIB)
	$(CC) -o $(TRACER) main.c $(TRACE_LIB)

# sample test program
test: 
	$(CC) -o tr_test tr_test.c $(TRACE_LIB)

install: $(TRACE_LIB) $(TRACER)
	@if [ ! -d $(INSDIR) ] ; then \
		echo mkdir $(INSDIR) ;\
		mkdir $(INSDIR) ;\
		fi
	@if [ ! -d $(LIB) ] ; then \
		echo mkdir $(LIB) ;\
		mkdir $(LIB) ;\
		fi
	@if [ ! -d $(TRACE_INC) ] ; then \
		echo mkdir $(TRACE_INC) ;\
		mkdir $(TRACE_INC) ;\
		fi
	ln $(TRACE_LIB) $(LIB)
	ln $(TRACER) $(INSDIR)
	ln $(TRACE_HDRS) $(TRACE_INC)
	-chmod ugo+rx $(INSDIR)/$(TRACER)
clean:
	-rm -f *.o
	-rm -f $(TRACE_LIB) $(TRACER)
