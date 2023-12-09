#include "assert_cpp.h"
#include <iostream.h>
#include <libc.h>

static void msgsend(const char *x)
{
 cout << flush;
 cerr << x << flush;
}

void (*assert_assert::display_msg)(const char *) = msgsend;
void (*assert_assert::terminate)(int) = exit;
