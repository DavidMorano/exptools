
/*********************************************************************
LIBRARY: Trace

AUTHOR: Kim Tran
VERSION: 1

CLASS: f_trace : public btrace

TITLE: function trace

DESCRIPTION:

PUBLIC:
    see man page for f_trace

**********************************************************************/

#ifndef FTRACE_H
#define FTRACE_H

#include "c_btrace.h"

class f_trace : public btrace {
public:
    f_trace (char *fname, char *t1=NULL, int v1=0, char *t2=NULL, int v2=0);
    f_trace (char *fname, char *t1, char *v1, char *t2=NULL, int v2=0);
    f_trace (char *fname, char *t1, int v1, char *t2, char *v2);
    f_trace (char *fname, char *t1, char *v1, char *t2, char *v2);

    ~f_trace ();
};

#endif 
