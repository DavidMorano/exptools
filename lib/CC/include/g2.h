#ifndef G2H
#define G2H

//  Untyped I/O

#include "g2manip.h"
#include "g2tree.h"
#include <String.h>
#include <iostream.h>

istream& operator>>(istream& is,G2BUF& tree);
ostream& operator<<(ostream& os,G2BUF& tree);

#endif
