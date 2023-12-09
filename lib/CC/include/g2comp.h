#ifndef G2COMPH
#define G2COMPH

#include "g2io.h"
#include "g2tree.h"
#include <Block.h>
#include <Map.h>
#include <String.h>

//  ASC strings are used to prepopulate the symbol table 
//  so that CHAR, SHORT, LONG are recognized as keywords 
//  to indicate char, short, and long data types. 

const String CHAR_ASC_ATTLC   = int_to_str(CHAR_INT_ATTLC);
const String SHORT_ASC_ATTLC  = int_to_str(SHORT_INT_ATTLC);
const String LONG_ASC_ATTLC   = int_to_str(LONG_INT_ATTLC);
const String STRING_ASC_ATTLC = int_to_str(STRING_INT_ATTLC);

const int G2MOTHER_ATTLC=0xAAAA;

void bdef(
    G2NODE*, 
    FILE*, 
    FILE*
);
void desc(
    G2NODE*, 
    const String&, 
    FILE*
);
void error(
    const char*
);
void error(
    const char*,
    const char* 
);
void error(
    const char*,
    const char*,
    const char*
);
void error(
    const char*,
    const char*,
    long
);
G2NODE* lookup(
    const String&
);
void tdef(
    G2NODE*, 
    FILE*,
    FILE*
);
String upper(
    const String& s
);

Blockdeclare(String);

struct udt_info_ATTLC{
    Block(String) headers;
    int		header_count;
    String 	put;
    String 	get;
    String	null;
    String	isnull;
    // udt_info():headers(10){}  -- blowing up.  Why?
};

Mapdeclare(String,udt_info_ATTLC);

extern Map(String,udt_info_ATTLC) udt_map_ATTLC;

#endif
