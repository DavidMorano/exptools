#include "assert_cpp.h"
#include <iostream.h>

extern "C" {
void abort(void)
{
 cout << "ABORT\n";
}
}


void foo(void)
{
 ENTER_FCN("foo()");
 assert2(0, cerr << "assert_2 in foo");
}

main( int argc, char **argv)
{
 assert_assert::desperate = argc>1;
 ENTER_FCN("main()");
 int a, b;
 MARK_LINE;
 assert(&a == &b);
 MARK_LINE;
 {
 ENTER_FCN("main-block");
 foo();
 }
 assert(0);
}
