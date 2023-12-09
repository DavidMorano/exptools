#ifndef G2PLUSPLUSH
#define G2PLUSPLUSH

//  Untyped I/O

#include "g2manip.h"
#include "g2tree.h"
#include <String.h>
class istream;
class ostream;

istream& operator>>(istream& is,G2BUF& tree);
ostream& operator<<(ostream& os,G2BUF& tree);

#endif
