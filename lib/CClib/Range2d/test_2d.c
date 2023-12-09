#include <iostream.h>
#include <assert.h>
#include <Range2d.h>

Range2ddeclare(int)

main()
{
 Range2d(int) a(0, 0, 10, 10);
 Range2d(int) b(5, 5, 11, 11);
 Range2d(int) c = a&b;
 assert(a != b);
 assert(a & b);
 assert(a | b);
 assert(c);
 assert(c == Range2d(int)(5, 5, 10, 10));
 assert(c.weight() == 36);
 assert(c.area() == gdoublet(int)(5, 5));
 c |= a;
 assert(c == a);
 c |= b;
 assert(c == (a | b));
 c &= Range2d(int)(2, 2, 3, 4);
 assert(c == Range2d(int)(2, 2, 3, 4));
 assert(a);
 assert(b);
 assert(c);
 {
  Range2d(int) x;
  Range2d(int) y(111, 112, 112, 113);
  assert(!x);
  assert(!(a & x));
  assert(y);
  assert(!(a & y));
  assert(x.weight() == 0);
  assert((x&y).weight() == 0);
 }
}

Range2dimplement(int)
nRangeimplement(int)
