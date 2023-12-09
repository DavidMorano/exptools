
/*********************************************************************
LIBRARY: Trace

AUTHOR: Kim Tran
VERSION: 1

CLASS: btrace

TITLE: base class for trace classes

DESCRIPTION:
    btrace contains information and operations common to p_trace and
    f_trace classes.

PUBLIC:
    btrace
	    stores the routine's name and set indentation level
    ~btrace
	    reset indentation level
    write
	    overloaded functions for writing trace info to files

PROTECTED:
    sm_chk
	this function is used to check ShMem and verify
	the trace status.
    init_file
	initiates a Trace output file
    flush_line
	    flush a line worth of buffer to output file
    func_name
	    name of the routine in which an instance of p_trace or
	    f_trace exists
    line_buf
	    buffer for a line of text

PRIVATE:
    write_hdr
	    write a header for trace output
    write_rest
	    a helper function for functions write above
*********************************************************************/

#ifndef BTRACE_H
#define BTRACE_H

#include "c_sm_slot.h"
#include "c_write_buf.h"


class btrace {
public:
    btrace (char *name);
    ~btrace ();
    void write (int type, char *sfile, int sline, char *t1=NULL, 
	    int v1=DEF_INT, char *t2=NULL, int v2=DEF_INT);
    void write (int type, char *sfile, int sline, char *t1, char *v1, 
	    char *t2=NULL, int v2=DEF_INT);
    void write (int type, char *sfile, int sline, char *t1, int v1, 
	    char *t2, char *v2);
    void write (int type, char *sfile, int sline, char *t1, char *v1, 
	    char *t2, char *v2);
protected:
    void sm_chk ();
    void init_file ();
    void flush_line ();
protected:
    char func_name[NAME_SZ];
    write_buf line_buf;
private:
    void write_hdr ();
    void write_rest (int type);
};

#endif
