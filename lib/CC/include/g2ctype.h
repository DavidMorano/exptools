#ifndef G2CTYPEH
#define G2CTYPEH

#include <String.h>

typedef int G2CTAB_ATTLC; // tunable: int for speed, char for size

extern G2CTAB_ATTLC g2Dtab_ATTLC[];
extern G2CTAB_ATTLC g2Ptab_ATTLC[];
extern G2CTAB_ATTLC g2N1tab_ATTLC[];
extern G2CTAB_ATTLC g2N2tab_ATTLC[];

inline int isdigit_ATTLC(int c){
    return (g2Dtab_ATTLC+1)[c];
}
inline int isprint_ATTLC(int c){
    return (g2Ptab_ATTLC+1)[c];
}
inline int isname1_ATTLC(int c){  // letters, _
    return (g2N1tab_ATTLC+1)[c];
}
inline int isname2_ATTLC(int c){  // letters, numbers, *, _
    return (g2N2tab_ATTLC+1)[c];
}
int isname_ATTLC(
    const String& s
);
int isint_ATTLC(
    const String& s
);

#endif
