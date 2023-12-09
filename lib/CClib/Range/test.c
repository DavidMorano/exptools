#include <Range.h>
#include <String.h>
#include <CC/assert.h>

nRangedeclare(int)
Rangedeclare(String)

main()
{
 nRange(int) x(0, 1);
 assert(x==1);
 assert(x==0);
 assert(x!=2);
 assert(x!=(-1));
 assert(expand(x, 0, 3.0).superset_of(x));
 assert(expand(x, 0, 3.0) != x);
 assert(expand(x, 0, 0.0).subset_of(x));
 assert(expand(x, 0, 0.0) != x);
 assert(expand(x, 2.0) == nRange(int)(-1,1));
 assert((-1) < Range(int)(x));
 assert(5 > x);
 assert((-1) <= x);
 assert(0 <= x);
 assert(1 >= x);
 assert(2 > x);
 assert(x < 2);

 assert(nRange(int)(0,1) == Range(int)(0,1));

 nRange(int) y(5);
 assert(y == 5);
 assert( 4 < y);
 assert(y > 4);
 assert(x != y);
 assert(!x.superset_of(y));
 assert(!x.subset_of(y));
 assert(!(x&y));
 assert(x|y);
 assert((y&y)==y);
 assert((x|x) == x);
 assert((x|y).superset_of(x));
 assert((x|y).superset_of(y));
 assert((x&y).subset_of(x));
 assert((x&y).subset_of(y));
 assert((x&y).subset_of(x|y));

 Range(int) z(1);
 assert(x != z);
 assert(x.superset_of(z));
 assert(!x.subset_of(z));
 assert(x&z);
 assert(x|z);
 assert((x|z) == x);
 assert((x&z) == z);

 nRange(int) w;
 assert(!w);

 nRange(int) ww(z);
 assert(ww);
 assert(ww == z);

 nRange(int) xx(0, 6);
 assert(xx.center() == 3);
 assert(xx.superset_of(z));

 Range(String) a(String("unicorn"), String("zymurgy"));
 cout << a.low << a.high << endl;
 BOOL ne = a!=String("Aardvark");
 BOOL eq = a==String("xylophone");
 assert(ne);
 assert(eq);
 exit(0);
}
