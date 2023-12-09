
/**********************************************************************
LIBRARY: trace

AUTHOR: Kim Tran
VERSION: 1

DESCRIPTION:
    header to be included by target programs

**********************************************************************/

// source location (temporarily defined here)
#define __LOC__  __FILE__, __LINE__

// PID for repeated testing of test program
#define TEST_PID -1

// default integer arg
#define DEF_INT 99999

// success code
#define OK 1

// Boolean code
#define YES 1
#define NO  0

// ShMem iteration codes
#define CONT 1
#define RESET 2

// number of spaces per indentation level
#define IND_SP 4

// trace types - one per bit - requires TIME < LOW < MED < HIGH
#define TIME 001
#define LOW  002
#define MED  004
#define HIGH  010

// temp defines for IPC ids here - should be in a global CMS hdr
#define TRACE_CH   'z'
#define TRACE_LK   'z'

// trace lib headers
#include "c_sm_slot.h"
#include "c_trace_sm.h"
#include "c_trace_gl.h"
#include "c_p_trace.h"
#include "c_f_trace.h"

// global variables
extern struct trace_gl Trace_GL;
extern struct trace_sm Trace_SM;
