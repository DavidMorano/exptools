/**********************************************************************
CLASS: btrace
AUTHOR: Kim Tran
VERSION: 1
**********************************************************************/

#include <string.h>
#include <time.h>
#include "c_tr_hdrs.h"
extern "C" {
    long time (long *);
    void perror (char *);
}

btrace::btrace (char *name) {
    // save the routine name
    strncpy (func_name, name, NAME_SZ);
    func_name[NAME_SZ] = '\0';

    // increment indentation level
    ++Trace_GL.ind_level;
}

btrace::~btrace () {
    // decrement indentation level
    --Trace_GL.ind_level;
}


void
btrace::write (int type, char *sfile, int sline, char *t1, int v1, 
		char *t2, int v2) {
    // update trace activation status
    sm_chk ();

    // check if trace is ON AND this type is needed
    if (Trace_GL.active == YES) {
	// check desired type (HIGH > MED > LOW) - don't compare TIME bit
	if (type >= (Trace_GL.trace_type&(~TIME))) {
            line_buf.write_mid (func_name, sfile, sline, t1, v1, t2, v2);
	    write_rest (type);
	}
    }

    return;
}


void
btrace::write (int type, char *sfile, int sline, char *t1, char *v1, 
	char *t2, int v2) {

    // update trace activation status
    sm_chk ();

    // check if trace is ON AND this type is needed
    if (Trace_GL.active == YES) {
	// check desired type (HIGH > MED > LOW) - don't compare TIME bit
	if (type >= (Trace_GL.trace_type&(~TIME))) {
            line_buf.write_mid (func_name, sfile, sline, t1, v1, t2, v2);
	    write_rest (type);
	}
    }

    return;
}


void
btrace::write (int type, char *sfile, int sline, char *t1, 
	    int v1, char *t2, char *v2) {

    // update trace activation status
    sm_chk ();

    // check if trace is ON AND this type is needed
    if (Trace_GL.active == YES) {
	// check desired type (HIGH > MED > LOW) - don't compare TIME bit
	if (type >= (Trace_GL.trace_type&(~TIME))) {
            line_buf.write_mid (func_name, sfile, sline, t1, v1, t2, v2);
	    write_rest (type);
	}
    }

    return;
}


void
btrace::write (int type, char *sfile, int sline, char *t1, 
	    char *v1, char *t2, char *v2) {

    // update trace activation status
    sm_chk ();

    // check if trace is ON AND this type is needed
    if (Trace_GL.active == YES) {
	// check desired type (HIGH > MED > LOW) - don't compare TIME bit
	if (type >= (Trace_GL.trace_type&(~TIME))) {
            line_buf.write_mid (func_name, sfile, sline, t1, v1, t2, v2);
	    write_rest (type);
	}
    }

    return;
}


void
btrace::write_rest (int type) {
    // if requested trace AND current type both have TIME set, write time

    if (((Trace_GL.trace_type & TIME) > 0) && ((type & TIME) > 0)) {
        line_buf.write_time ();
    }

    // if requested trace type is LOW or MED, write type letter
    if ((Trace_GL.trace_type & LOW) || (Trace_GL.trace_type & MED)) {
        line_buf.write_type (type);
    }

    line_buf.write_nl ();
    flush_line ();

    return;
}


void
btrace::sm_chk () {

    // check if Trace ShMem is attached already
    if (Trace_SM.base_ptr() == NULL) {
	return;
    }

    // check ShMem (using trace_sm object), look for
    // the slot with matched program name AND PID first

    sm_slot *slot_ptr = Trace_SM.search (Trace_GL.pg_name, Trace_GL.pid);
    // if slot with matched program name AND PID not found, look for
    // one with matched program name only

    if (slot_ptr == NULL) {
	// need to lock ShMem just in case we need to add PID
	Trace_SM.setlock ();
        slot_ptr = Trace_SM.search (Trace_GL.pg_name);

	if (slot_ptr != NULL) {
	// add PID to ShMem slot if it is not reserved
	    if (slot_ptr->pid == 0) {
	        slot_ptr->pid = Trace_GL.pid;
	    }
	    else if (slot_ptr->pid != TEST_PID) {
	    // not one belong to this process or for testing
		slot_ptr = NULL;
	    }
	}

	// remember to unlock ShMem
	Trace_SM.unlock ();
    }
	
    if (slot_ptr != NULL) {
    // activation exists - several pre-conditions are possible:
    //    activation record not exist before
    //    same activation record as before:
    //        - trace currently made INACTIVE by function control
    //        - trace currently made ACTIVE by function control

        // save trace activation info if it's INITIATED the first time
	if (Trace_GL.init == NO) {
	    strncpy (Trace_GL.outfile, slot_ptr->outfile, FNAME_SZ);
	    Trace_GL.outfile[FNAME_SZ] = '\0';

	    Trace_GL.trace_type = slot_ptr->trace_type;

	    strncpy (Trace_GL.beg_func, slot_ptr->beg_func, NAME_SZ);
	    Trace_GL.beg_func[NAME_SZ] = '\0';

	    strncpy (Trace_GL.end_func, slot_ptr->end_func, NAME_SZ);
	    Trace_GL.end_func[NAME_SZ] = '\0';

	    Trace_GL.init = YES;

	    // open Trace output file 
	    init_file ();
	}

        // check if trace should change from INACTIVE to ACTIVE 
	if ((Trace_GL.beg_func[0] == '\0') || 
	    (strncmp (Trace_GL.beg_func, func_name, NAME_SZ) == 0)) {

	    if (Trace_GL.out_ptr != NULL) {
                Trace_GL.active = YES;
	    }
	}

	// check if Trace was ACTIVE before AND it is made INACTIVE by 
	// function
	if (strncmp (Trace_GL.end_func, func_name, NAME_SZ) == 0) {

	    // set flags to indicate OFF status
	    Trace_GL.active = NO;
	}
    }
    
    if (slot_ptr == NULL) {
	// Trace was ACTIVE before AND it is turned OFF by the 
	// removal of the trace activation
	Trace_GL.init = NO;
	Trace_GL.active = NO;
    }

    return;
}


void
btrace::write_hdr () {
    char hdr_buf[LINE_SZ], *ptr;
    ptr = hdr_buf;

    // the format is
    //    (pg_name:pid)     R3CMS TRACE    Date: xx/xx/xx hr:min

    long clock = time (0);
    const struct tm *tm_buf = localtime (&clock);

    int ch_count;
    ch_count = sprintf (ptr, "(%s:%d)\t\tR3CMS TRACE\t\t", 
		Trace_GL.pg_name, Trace_GL.pid);
    ptr += ch_count;

    ch_count = sprintf (ptr, "Date:%.2d/%.2d/%.2d (%.2d:%.2d)\n\n", 
            tm_buf->tm_mon, tm_buf->tm_mday, tm_buf->tm_year, 
	    tm_buf->tm_hour, tm_buf->tm_min);

    (void) fputs (hdr_buf, Trace_GL.out_ptr);

    return;
}


void
btrace::flush_line () {

    // flush line buffer to file - switch file if EOF
    if (line_buf.flush (Trace_GL.out_ptr) == EOF) {
	// close the current file first
	fclose (Trace_GL.out_ptr);

	// adjust file sequence
	if (Trace_GL.out_seq == 1) {
	    Trace_GL.out_seq = 2;
	}
	else {
	    Trace_GL.out_seq = 1;
	}

        // open the new file - format: file[1,2] 
	init_file ();

	// write again and don't care the result
        (void) line_buf.flush (Trace_GL.out_ptr);
    }
    return;
}


void
btrace::init_file () {
    // open Trace output file
    char path[20];
    sprintf (path, "%s%d", Trace_GL.outfile, Trace_GL.out_seq);

    Trace_GL.out_ptr = fopen (path, "w");
    if (Trace_GL.out_ptr == NULL) {
        perror ("fopen output file");
        return;
    }

    // write to the file a Trace header 
    write_hdr ();
    return;
}
