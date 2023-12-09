
/*********************************************************************
LIBRARY: Trace

AUTHOR: Kim Tran
VERSION: 1

CLASS: p_trace : public btrace

TITLE: program trace initializer

DESCRIPTION:
    p_trace attaches the Trace shared memory segment to the host
    process. It will also check whether trace activation is on for
    this particular process. 

PUBLIC:
    see man page for p_trace

PRIVATE:
    init
	initializes Trace global data
    sm_chk
	this function is used to check ShMem and verify
	the trace status.
**********************************************************************/

#ifndef PTRACE_H
#define PTRACE_H

#include "c_btrace.h"

class p_trace : public btrace {
public:
    p_trace (char *pname, char *t1=NULL, int v1=0, char *t2=NULL, int v2=0);
    p_trace (char *pname, char *t1, char *v1, char *t2=NULL, int v2=0);
    p_trace (char *pname, char *t1, int v1, char *t2, char *v2);
    p_trace (char *pname, char *t1, char *v1, char *t2, char *v2);

    ~p_trace ();
private:
    void init (char *pname);
    void sm_chk ();
};

#endif

