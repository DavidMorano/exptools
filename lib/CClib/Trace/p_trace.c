/*
********************************************************************
CLASS: p_trace
AUTHOR: Kim Tran
VERSION: 1
********************************************************************
*/

#include <string.h>
#include "c_tr_hdrs.h"
extern "C" {
    int getpid ();
};

p_trace::p_trace (char *pname, char *t1, int v1, char *t2, int v2) : btrace ("main") {
    // initiate for program trace
    init (pname);

    // check if trace is ON
    if (Trace_GL.active == YES) {
	// log the first trace for main routine
        line_buf.write_beg (func_name, t1, v1, t2, v2);

	// write TIME if so requested
	if ((Trace_GL.trace_type & TIME) > 0) {
	    line_buf.write_time ();
	}

        line_buf.write_nl ();
	flush_line ();
    }
}


p_trace::p_trace (char *pname, char *t1, char *v1, char *t2, int v2) : btrace ("main") {
    // initiate for program trace
    init (pname);

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

p_trace::p_trace (char *pname, char *t1, int v1, char *t2, char *v2) : btrace ("main") {
    // initiate for program trace
    init (pname);

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


p_trace::p_trace (char *pname, char *t1, char *v1, char *t2, char *v2) : btrace ("main") {
    // initiate for program trace
    init (pname);

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

void
p_trace::init (char *pname) {

    /// save program name (without path prefix) in global Trace_GL

    char *pp = strrchr (pname, '/');
    if (pp == NULL) {
	// no path prefix
	pp = pname;
    }
    else {
	// skip the '/'
	++pp;
    }

    strncpy (Trace_GL.pg_name, pp, NAME_SZ);
    Trace_GL.pg_name[NAME_SZ] = '\0';

    // get UNIX PID of the host process and save it in Trace_GL
    Trace_GL.pid = getpid ();

    // set output file sequence in Trace_GL to 1
    Trace_GL.out_seq = 1;

    // init indentation level
    Trace_GL.ind_level = 0;

    // init Trace status
    Trace_GL.init = NO;
    Trace_GL.active = NO;

    // attach the Trace ShMem with R/W
    Trace_SM.attach (0);

    // check ShMem for trace activation: call sm_chk ()
    p_trace::sm_chk ();

    return;
}

    
p_trace::~p_trace () {
    // update trace activation
    btrace::sm_chk ();

    // write the END trace line if trace is ON
    if (Trace_GL.active == YES) {
	// log the last trace
        line_buf.write_end (func_name);

	// write TIME if so requested
	if ((Trace_GL.trace_type & TIME) > 0) {
	    line_buf.write_time ();
	}

        line_buf.write_nl ();
	flush_line ();
    }

    // close Trace output file if it was opened
    if (Trace_GL.out_ptr != NULL) {
	fclose (Trace_GL.out_ptr);
    }

    // remove the activation slot if it exists
    struct sm_slot *slot_ptr = Trace_SM.search (Trace_GL.pg_name, Trace_GL.pid);
    if (slot_ptr != NULL) {
        Trace_SM.free (slot_ptr);
    }
    
    // detach Trace shared memory
    Trace_SM.detach ();
}

void
p_trace::sm_chk () {

    // check ShMem (using trace_sm object), look for
    // the first activation slot with matched program name 
    // (we need to lock ShMem just in case we need to add PID to slot,
    /// remember to unlock it asap)

    Trace_SM.setlock ();
    sm_slot *slot_ptr = Trace_SM.search (Trace_GL.pg_name);

    if (slot_ptr != NULL) {
	// activation record exists - save its info 
	strncpy (Trace_GL.outfile, slot_ptr->outfile, FNAME_SZ);
	Trace_GL.outfile[FNAME_SZ] = '\0';

	Trace_GL.trace_type = slot_ptr->trace_type;

	strncpy (Trace_GL.beg_func, slot_ptr->beg_func, NAME_SZ);
	Trace_GL.beg_func[NAME_SZ] = '\0';

	strncpy (Trace_GL.end_func, slot_ptr->end_func, NAME_SZ);
	Trace_GL.end_func[NAME_SZ] = '\0';

	// if activation slot is not intended for testing 
	// (pid == TEST_PID), make it unique by adding PID to 
	// activation slot in ShMem 

	if (slot_ptr->pid != TEST_PID) {
	    slot_ptr->pid = Trace_GL.pid;
	}

	// unlock ShMem after writing
	Trace_SM.unlock ();

	// set flag to indicate INITIATED status
	Trace_GL.init = YES;

        // open Trace output file
	init_file ();

	// check if trace should be ACTIVE with main routine
	if ((Trace_GL.beg_func[0] == '\0') || 
	    (strcmp (Trace_GL.beg_func, "main") == 0)) {
	    if (Trace_GL.out_ptr != NULL) {
                Trace_GL.active = YES;
	    }
	}
    }
    else {
	// unlock ShMem
	Trace_SM.unlock ();
    }

    return;
}
