/**********************************************************************
LIBRARY: trace

AUTHOR: Kim Tran
VERSION: 1

STRUCT: sm_slot

TITLE: Trace shared memory slot

DESCRIPTION:
    represents the structure of information stored in each slot of
    shared memory reserved for Trace. 

VARIABLES:
    pg_name
	    Name of the target program
    pid
	    UNIX process id of the target program
    outfile
	    the name of the trace output files
    trace_type
	    Bit map of trace types
    beg_func
	    Function in the target program where trace is started
    end_func
	    Function in the target program where trace is stopped
    acttime
	    the time the trace activation is issued for this program.
            This field is used to remove old activation slots.

**********************************************************************/

#ifndef SM_SLOT_H
#define SM_SLOT_H

#include <stdio.h>

// size of program and function names (exclude NULL byte)
#define NAME_SZ 14
// size of output file names (exclude NULL byte and sequence number)
#define FNAME_SZ 13
// size of C/C++ function name
// #define CNAME_SZ 20

struct sm_slot {
    char pg_name [NAME_SZ+1];
    int pid;
    char outfile [FNAME_SZ+1];
    short trace_type;
    char beg_func [NAME_SZ+1];
    char end_func [NAME_SZ+1];
    long acttime;
};

// number of slots in Trace shared memory
#define MAX_SLOTS 20

// size of each slot
#define SLOT_SZ   sizeof (struct sm_slot)

#endif
