/*
********************************************************************
CLASS: f_trace
AUTHOR: Kim Tran
VERSION: 1
********************************************************************
*/
#include "c_tr_hdrs.h"

f_trace::f_trace (char *fname, char *t1, int v1, char *t2, int v2) : btrace (fname) {
    // check ShMem for trace activation
    sm_chk ();

    // check if trace is ON
    if (Trace_GL.active == YES) {
	// log the first trace for a function
        line_buf.write_beg (func_name, t1, v1, t2, v2);

	// write TIME if so requested
	if ((Trace_GL.trace_type & TIME) > 0) {
	    line_buf.write_time ();
	}

        line_buf.write_nl ();
	flush_line ();
    }
}


f_trace::f_trace (char *fname, char *t1, char *v1, char *t2, int v2) : btrace (fname) {
    // check ShMem
    sm_chk ();

    // check if trace is ON
    if (Trace_GL.active == YES) {
	// log the first trace
        line_buf.write_beg (func_name, t1, v1, t2, v2);

	// write TIME if so requested
	if ((Trace_GL.trace_type & TIME) > 0) {
	    line_buf.write_time ();
	}

        line_buf.write_nl ();
	flush_line ();
    }
}

f_trace::f_trace (char *fname, char *t1, int v1, char *t2, char *v2) : btrace (fname) {
    // check ShMem
    sm_chk ();

    // check if trace is ON
    if (Trace_GL.active == YES) {
	// log the first trace
        line_buf.write_beg (func_name, t1, v1, t2, v2);

	// write TIME if so requested
	if ((Trace_GL.trace_type & TIME) > 0) {
	    line_buf.write_time ();
	}

        line_buf.write_nl ();
	flush_line ();
    }
}


f_trace::f_trace (char *fname, char *t1, char *v1, char *t2, char *v2) : btrace (fname) {
    // check ShMem
    sm_chk ();

    // check if trace is ON
    if (Trace_GL.active == YES) {
	// log the first trace
        line_buf.write_beg (func_name, t1, v1, t2, v2);

	// write TIME if so requested
	if ((Trace_GL.trace_type & TIME) > 0) {
	    line_buf.write_time ();
	}

        line_buf.write_nl ();
	flush_line ();
    }
}

    
f_trace::~f_trace () {
    // update trace activation
    sm_chk ();

    // check if trace is ON
    if (Trace_GL.active == YES) {
	// log the END trace for this function 
        line_buf.write_end (func_name);

	// write TIME if so requested
	if ((Trace_GL.trace_type & TIME) > 0) {
	    line_buf.write_time ();
	}

        line_buf.write_nl ();
	flush_line ();
    }
}

