#include <Range.h>
#include <String.h>
#include <assert.h>
#include <iostream.h>

nRangedeclare(int)
Rangedeclare(String)
nRangedeclare(double)

main()
{
 ENTER_FCN("main");
 assert_assert::desperate = 1;
 nRange(int) x(0, 1);
 {
 assert(x==1);
 assert(x==0);
 assert(x!=2);
 assert(x!=(-1));
 assert(x.length() == 1);
 assert(x.weight() == 2);
 assert(expand(x, 0, 3.0).superset_of(x));
 assert(expand(x, 0, 3.0) != x);
 assert(expand(x, 0, 0.0).subset_of(x));
 assert(expand(x, 0, 0.0) != x);
 assert(expand(x, 3.1) == nRange(int)(-1,2));
 assert((-1) < Range(int)(x));
 assert(5 > x);
 assert((-1) <= x);
 assert(0 <= x);
 assert(1 >= x);
 assert(2 > x);
 assert(x < 2);
 }

 {assert(nRange(int)(0,1) == Range(int)(0,1));}

 nRange(int) y(5);
 {
 nRange(int) yy = y;
 assert(y == 5);
 assert( 4 < y);
 assert(y > 4);
 assert(x != y);
 assert(!x.superset_of(y));
 assert(!x.subset_of(y));
 assert(!(x&y));
 assert(x|y);
 assert((y&y)==y);
 yy &= y;
 assert(yy);
 assert(yy == y);
 assert((x|x) == x);
 assert((x|y).superset_of(x));
 assert((x|y).superset_of(y));
 yy |= x;
 assert(yy.superset_of(x) && yy.superset_of(y));
 assert((x&y).subset_of(x));
 assert((x&y).subset_of(y));
 assert((x&y).subset_of(x|y));
 yy = y;
 yy &= x;
 assert(yy.subset_of(x) && yy.subset_of(y));
 }

 Range(int) z(1);
 {
 cerr << "x:("<<x.low<<", "<<x.high<<')'<<endl;
 cerr << "z:("<<z.low<<", "<<z.high<<')'<<endl;
 assert(x != z);
 assert(x.superset_of(z));
 assert(!x.subset_of(z));
 assert(x&z);
 assert(x|z);
 assert((x|z) == x);
 assert((x&z) == z);
 }

 {
 nRange(int) w;
 nRange(int) wq(y & z);
 cerr << "w:("<<w.low<<", "<<w.high<<')'<<endl;
 cerr << "wq:("<<wq.low<<", "<<wq.high<<')'<<endl;
 assert(!w);
 assert(!wq);
 assert(w.weight() == 0);
 assert(w.length() == 0);
 assert(w != z);
 assert(w.subset_of(z));
 assert(z.superset_of(w));
 assert(!w.superset_of(z));
 assert(!z.subset_of(w));
 assert(wq != z);
 assert(w.subset_of(wq));
 assert(wq.superset_of(w));
 assert(wq.subset_of(w));
 assert(w.superset_of(wq));
 assert(w == wq);
 assert((w | wq) == wq);
 assert((w | z) == z);
 assert((w & wq) == wq);
 assert((w & z) == wq);
 }

 {
 nRange(int) ww(z);
 assert(ww);
 assert(ww == z);
 assert(ww.length() == 0);
 assert(ww.weight() == 1);
 }

 {
 nRange(int) xx(0, 6);
 assert(xx.center() == 3);
 assert(xx.superset_of(z));
 }

 {
 Range(String) a(String("unicorn"), String("zymurgy"));
 cout << a.low << a.high << endl;
 BOOL ne = a!=String("Aardvark");
 BOOL eq = a==String("xylophone");
 assert(ne);
 assert(eq);
 }

 {
  nRange(double) q(0.1, 0.2);
  assert(q.length()>0.0999 && q.length()<0.1001);
  assert(q.length()==q.weight());
 }
 exit(0);
}

nRangeimplement(int)
Rangeimplement(String)
nRangeimplement(double)
