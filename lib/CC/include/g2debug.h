#include "g2tree.h"
#include "g2desc.h"

//  To de-activate debug printing, change 
//  the DEBUG macro definition from
//
//      #define DEBUG(x) x
//
//  to
//
//      #define DEBUG(x)
//

#define DEBUG(x)

void showbuf_ATTLC(
    G2BUF* bp
);
void showdesc_ATTLC(
    G2DESC* rd
);
void shownode_ATTLC(
    G2NODE* np
);
void showtree_ATTLC(
    G2NODE*,int
);
