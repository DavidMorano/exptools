#ifndef G2MANIPH
#define G2MANIPH

#include <String.h>
class istream;
class ostream;

String getname_ATTLC(
    istream& is
);
String g2seek(
    istream& is
);
String g2seek(
    istream& is,
    const String& name
);

#endif
