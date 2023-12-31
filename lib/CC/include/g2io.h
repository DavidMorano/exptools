#ifndef G2IOH
#define G2IOH

//  Internal I/O resources

#include "g2desc.h"
#include "g2tree.h"

#include <iostream.h>
#include <String.h>

//  Global data

const int NOISY_ATTLC       =0;   // nonzero: err/warn msg on stderr
const int G2BUFSIZE_ATTLC  =100; // initial number of G2BUF nodes
const int G2MAXDEPTH_ATTLC  =10;  // deepest level in g2 record
const int G2TAGLEN_ATTLC    =10;  // size of generated type tags
const String DEFAULT_INITIAL_BLOCK_SIZE_ATTLC	= "10";  
const String DEFAULT_INITIAL_STRING_SIZE_ATTLC = "10";  

extern int (*g2errfp)(int);	// error function pointer 
extern char* g2prog;		// used if set by user
extern char* g2file;		// ditto 
extern int g2err;		// error code, not reset

//  Error codes 
//  Note: Update to account for codes no longer in use

const int G2LONGNAME=1; // name longer than G2MAXNAME
const int G2LONGVAL =2; // value longer that user buffer
const int G2INDEXREQ=3; // name where index is required
const int G2BADLEAF =4; // non-integers in integer leaf
const int G2CORRUPT =5; // G2 record descriptor corruption
const int G2OVERFLOW=6; // G2 input record too long
const int G2TOODEEP =7; // G2 input record too deeply nested
const int G2BADCKSUM=8; // G2 input record with bad checksum

//  Update G2HIGHCODE_ATTLC as necessary:

const int G2HIGHCODE_ATTLC = 9;// one greater than max code 

#define Eor(f)		0
#define Check_error(s)	0
#define Cchksum(f) 	0
#define BS_EOF		EOF
#define BS_FILE		FILE
#define MEMFILE(file) 	(((BS_FILE*)(file))->_file == -1)
#define SETMEMFILE(file) (file->_file = -1)
#define Mark(f)		0

#ifdef LSC
#	define main _main
#endif

const int MAXINTSTR_ATTLC=15;   // longest possible int string

const int CHAR_INT_ATTLC   =  -100;
const int SHORT_INT_ATTLC  =  -200;
const int LONG_INT_ATTLC   =  -300;
const int STRING_INT_ATTLC =  -400;

#define REALSIZE(n)  ((n)>=0?(n):CSIZE(n))

#define CSIZE(n) \
     ( \
	 ( (n)-1 )==STRING_INT_ATTLC?( \
	     sizeof(String) \
	 ):( \
	     ((n)-1)==LONG_INT_ATTLC?( \
		 sizeof(long) \
	     ):( \
		( (n)-1 )==SHORT_INT_ATTLC?( \
		    sizeof(short) \
		):( \
		    ( (n)-1 )==CHAR_INT_ATTLC?( \
			sizeof(char) \
		    ):( \
			0 \
		    ) \
		) \
	    ) \
	) \
     )

#define g2error(code) ((g2err=code),(g2errfp?(*g2errfp)(code):0))

//  The following is necessary to prevent conflict
//  with sys/values.h, which defines HIBITI and HIBITL
//  as complicated expressions, which can't be tested
//  for equality.

#undef HIBITI
#undef HIBITL
#include "g2values.h"

#if HIBITI == HIBITL
#define _g2itostr _g2ltostr
#else
extern char *_g2itostr (char *buf, int bufsize, int n);
#endif

extern char* _g2ltostr (char *buf, int bufsize, long n);
extern char* _g2ctostr (char *buf, int bufsize, int n);

//  Untyped I/O

G2BUF* getbuf_ATTLC(
    G2BUF* 		bp, 
    istream& 		is
);
int putbuf_ATTLC(
    G2BUF* 		bp, 
    ostream& 		os
);

//  Typed I/O

extern void* getrec_ATTLC(
    void* 		rec, 
    G2DESC* 		rd, 
    istream& 		is
);
extern int putrec_ATTLC(
    void* 		rec, 
    G2DESC* 		rd, 
    ostream& 		os
);

extern int 	_g2getdot (istream& is);
extern int 	_g2otoi (const char* s);
extern void 	_g2putdot (ostream& os);
extern int 	_g2sync (int c, istream& is);
extern G2BUF* 	 g2init ( G2BUF* bp );

#endif
