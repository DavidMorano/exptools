
/********************************************************************
LIBRARY: Trace

AUTHOR: Kim Tran
VERSION: 1

STRUCT: trace_gl

DESCRIPTION:
    this structure holds information that are global to Trace 
    facility within a process. It's updated by objects of type 
    'p_trace' or 'f_trace' using information in Trace shared memory 
    every time they are created. 
    There is exactly one instance of this struct for each 
    host process and it is global.

VARIABLES:
    pg_name
	    Name of the target program
    pid
	    UNIX process id of the target program
    init
	    Flag to indicate whether info has been copied from ShMem
    active
	    Flag to indicate whether Trace is active or not
    outfile
	    the name of the trace output files
    trace_type
	    Bit map of trace types
    beg_func
	    Function in the target program where trace is started
    end_func
	    Function in the target program where trace is stopped
    out_seq
	    order sequence of output files. Range: 1, 2
    out_ptr
	    pointer to trace output file
    ind_level
	    level of indentation for trace output alignment

*********************************************************************/
#ifndef TRACE_GL_H
#define TRACE_GL_H

#include <stdio.h>
#include "c_sm_slot.h"

struct trace_gl {
    char pg_name[NAME_SZ+1];
    int pid;
    int init;
    int active;
    char outfile [FNAME_SZ+1];
    int trace_type;
    char beg_func [NAME_SZ+1];
    char end_func [NAME_SZ+1];
    int out_seq;
    FILE *out_ptr;
    int ind_level;
};

#endif
