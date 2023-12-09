
/*********************************************************************
LIBRARY: trace

AUTHOR: Kim Tran
VERSION: 1

CLASS: write_buf

DESCRIPTION:
    maintains an output buffer for a line of trace text.

PUBLIC: 
    write_beg
            overloaded - write a formated trace text for begin of a 
	    function
    write_end
            write a formated trace text for end of a function
    write_mid
            overloaded - write a formated trace text for info within 
	    a function
    write_time
	    write a formated text for UNIX time
    write_type
	    write a trace type symbol
    write_nl
	    write a new line to buffer
    flush
	    flush the buffer contents to output file
PRIVATE:
    sp_indent
	    prepend space indentation
    line_buf
	    buffer for a line of text
    bufptr
	    pointer for line buffer
	     
**********************************************************************/

#ifndef WRITE_BUF_H
#define WRITE_BUF_H

#define LINE_SZ 256

class write_buf {
public:
    write_buf ();
    void write_beg (char *name, char *t1=NULL, int v1=0, char *t2=NULL, int v2=0);
    void write_beg (char *name, char *t1, char *v1, char *t2=NULL, int v2=0);
    void write_beg (char *name, char *t1, int v1, char *t2, char *v2);
    void write_beg (char *name, char *t1, char *v1, char *t2, char *v2);

    void write_end (char *name);
    void write_mid (char *name, char *sfile, int sline, char *t1=NULL, 
		    int v1=0, char *t2=NULL, int v2=0);
    void write_mid (char *name, char *sfile, int sline, char *t1, 
		    char *v1, char *t2=NULL, int v2=0);
    void write_mid (char *name, char *sfile, int sline, char *t1, 
		    int v1, char *t2, char *v2);
    void write_mid (char *name, char *sfile, int sline, char *t1, 
		    char *v1, char *t2, char *v2);
    void write_time ();
    void write_type (int type);
    void write_nl ();
    int flush (FILE *fptr);
private:
    void sp_indent ();
private:
    char line_buf[LINE_SZ];
    char *bufptr;
};

#endif
