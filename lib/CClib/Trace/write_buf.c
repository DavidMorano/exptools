/*
***********************************************************************
CLASS: write_buf
AUTHOR: Kim Tran
VERSION: 1
***********************************************************************
*/

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include "c_tr_hdrs.h"
#include <sys/times.h>

write_buf::write_buf () {
    // initialize line_buf and its pointer
    line_buf[0] = '\0';
    bufptr = line_buf;
}


void
write_buf::write_beg (char *name, char *t1, int v1, char *t2, int v2) {
    // the format is
    //     (indentation) name (BEGIN): texts

    sp_indent ();
    int ch_count;
    ch_count = sprintf (bufptr, "%s (BEGIN):", name);
    bufptr += ch_count;

    if (t1 != NULL) {
	ch_count = sprintf (bufptr, " %s = %d", t1, v1);
	bufptr += ch_count;
    }

    if (t2 != NULL) {
	ch_count = sprintf (bufptr, ", %s = %d", t2, v2);
	bufptr += ch_count;
    }
}

void
write_buf::write_beg (char *name, char *t1, char *v1, char *t2, int v2) {
    // the format is
    //     (indentation) name (BEGIN): texts

    sp_indent ();
    int ch_count;
    ch_count = sprintf (bufptr, "%s (BEGIN): %s = '%s'", name, t1, v1);
    bufptr += ch_count;

    if (t2 != NULL) {
	ch_count = sprintf (bufptr, ", %s = %d", t2, v2);
	bufptr += ch_count;
    }
}

void
write_buf::write_beg (char *name, char *t1, int v1, char *t2, char *v2) {
    // the format is
    //     (indentation) name (BEGIN): texts

    sp_indent ();
    int ch_count;
    ch_count = sprintf (bufptr, "%s (BEGIN): %s = %d, %s = '%s'", 
			name, t1, v1, t2, v2);
    bufptr += ch_count;
}

void
write_buf::write_beg (char *name, char *t1, char *v1, char *t2, char *v2) {
    // the format is
    //     (indentation) name (BEGIN): texts

    sp_indent ();
    int ch_count;
    ch_count = sprintf (bufptr, "%s (BEGIN): %s = '%s', %s = '%s'", 
			name, t1, v1, t2, v2);
    bufptr += ch_count;
}

void
write_buf::sp_indent () {
    // put in enough spaces for indentation
    int i;
    for (i = 0; i < (Trace_GL.ind_level*IND_SP); i++) {
	*bufptr = ' ';
	++bufptr;
    }
}


void
write_buf::write_end (char *name) {
    // the format is 
    //     (indentation) name (END)

    sp_indent ();
    int ch_count;
    ch_count = sprintf (bufptr, "%s (END)", name);

    // update buffer pointer
    bufptr += ch_count;

    return;
}


void 
write_buf::write_mid (char *func, char *sfile, int sline, 
	char *t1, int v1, char *t2, int v2) {
    // the format is
    //     (indentation) func (sfile - sline): args

    sp_indent ();
    int ch_count;
    ch_count = sprintf (bufptr, "%s (%s - %d):", func, sfile, sline);
    bufptr += ch_count;

    if (t1 != NULL) {
	// write v1 if it is not default
	if (v1 != DEF_INT) {
            ch_count = sprintf (bufptr, " %s = %d", t1, v1);
	}
	else {
	    ch_count = sprintf (bufptr, " %s", t1);
	}

        bufptr += ch_count;
    }

    if (t2 != NULL) {
	// write v2 if it is not default
	if (v2 != DEF_INT) {
            ch_count = sprintf (bufptr, ", %s = %d", t2, v2);
	}
	else {
	    ch_count = sprintf (bufptr, ", %s", t2);
	}

        bufptr += ch_count;
    }

    return;
}


void 
write_buf::write_mid (char *func, char *sfile, int sline, 
	char *t1, char *v1, char *t2, int v2) {
    // the format is
    //     (indentation) func (sfile - sline): args

    sp_indent ();
    int ch_count;
    ch_count = sprintf (bufptr, "%s (%s - %d): %s = '%s'", 
		func, sfile, sline, t1, v1);
    bufptr += ch_count;

    if (t2 != NULL) {
	// write v2 if it is not default
	if (v2 != DEF_INT) {
            ch_count = sprintf (bufptr, ", %s = %d", t2, v2);
	}
	else {
            ch_count = sprintf (bufptr, ", %s", t2);
	}

        bufptr += ch_count;
    }

    return;
}


void 
write_buf::write_mid (char *func, char *sfile, int sline, 
	char *t1, int v1, char *t2, char *v2) {
    // the format is
    //     (indentation) func (sfile - sline): args

    sp_indent ();
    int ch_count;
    ch_count = sprintf (bufptr, "%s (%s - %d): %s = %d, %s = '%s'", 
	    func, sfile, sline, t1, v1, t2, v2);
    bufptr += ch_count;

    return;
}

void 
write_buf::write_mid (char *func, char *sfile, int sline, 
	char *t1, char *v1, char *t2, char *v2) {
    // the format is
    //     (indentation) func (sfile - sline): args

    sp_indent ();
    int ch_count;
    ch_count = sprintf (bufptr, "%s (%s - %d): %s = '%s', %s = '%s'", 
	    func, sfile, sline, t1, v1, t2, v2);
    bufptr += ch_count;

    return;
}


void
write_buf::write_type (int type) {
    if (type & HIGH) {
	(void) strncat (bufptr, " (H)", 4);
    }
    else if (type & MED) {
	(void) strncat (bufptr, " (M)", 4);
    }
    else if (type & LOW) {
	(void) strncat (bufptr, " (L)", 4);
    }

    // account for added chars
    bufptr += 4;
    return;
}


void
write_buf::write_time () {
    // get UNIX time (in 100th of sec)
    // and write the time to global line buffer

    struct tms dummy;
    long clock = times (&dummy);

    int ch_count;
    ch_count = sprintf (bufptr, " [%ld]", clock);
    bufptr += ch_count;

    return;
}

void
write_buf::write_nl () {
    // write a new line to global line buffer 
    *bufptr = '\n';
    ++bufptr;
    *bufptr = '\0';
    return;
}

int
write_buf::flush (FILE *fptr) {

    int ret = fputs (line_buf, fptr);

    // flush and reset buffer if sucessful write
    if (ret != EOF) {
	(void) fflush (fptr);
	line_buf[0] = '\0';
	bufptr = line_buf;
    }
    return (ret);
}

