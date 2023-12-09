#ifndef RANGE2D_H
# define RANGE2D_H
/* Range2d -- rectangles.   C++ 2.1 all machines. */
/* version 1.1  Greg Kochanski  physics!gpk  2/13/91 */
# ifndef RANGE_T
#  include <Range.h>
# endif
# ifndef GDOUBLET_H
#  include <gdoublet.h>
# endif

# ifndef STD_H
 typedef short BOOL;	/* Use BOOL for logical variables as a reminder to
						the programmer. */
# endif

PT_names
Range2d(T) Range2d_ T
PT_end

PT_define Range2ddeclare(T)

nRangedeclare(T)
gdoubletdeclare(T)

class Range2d(T)	{
	public:
	nRange(T) x;
	nRange(T) y;
	gdoublet(T) hhc() const;
	gdoublet(T) hlc() const;
	gdoublet(T) llc() const;
	gdoublet(T) lhc() const;
	gdoublet(T) area(void) const;
	long weight() const;
	Range2d(T)(const gdoublet(T)& _llc, const gdoublet(T)& _hhc);
	Range2d(T)(const gdoublet(T)& c);
	Range2d(T)(const Range(T)& xr, const Range(T)& yr);
	Range2d(T)(T x1, T y1, T x2, T y2);
	Range2d(T)();
	operator void *() const;
	BOOL operator!() const	{return !(void *)(*this);}
	C Range2d(T)& operator &=(C Range2d(T)& a);
	C Range2d(T)& operator |=(C Range2d(T)& a);
	BOOL superset_of(C Range2d(T)& a) C;
	BOOL subset_of(C Range2d(T)& a) C;
	};

Range2d(T) operator&(const Range2d(T)& a, const Range2d(T)& b);
Range2d(T) operator|(const Range2d(T)& a, const Range2d(T)& b);
BOOL operator==(const Range2d(T)& a, const Range2d(T)& b);
BOOL operator==(const Range2d(T)& a, const gdoublet(T)& b);

inline BOOL operator!=(const Range2d(T)& a, const Range2d(T)& b)
	{return !(a==b);}
inline BOOL operator!=(const Range2d(T)& a, const gdoublet(T)& b)
	{return !(a==b);}
inline BOOL operator!=(const gdoublet(T)& a, const Range2d(T)& b)
	{return !(b==a);}
inline BOOL operator==(const gdoublet(T)& a, const Range2d(T)& b)
	{return b==a;}

PT_end

PT_define Range2dimplement(T)

Range2d(T)::Range2d(T)(const Range(T)& xr, const Range(T)& yr)
: x(xr), y(yr)
{}

Range2d(T)::Range2d(T)(const gdoublet(T)& _llc, const gdoublet(T)& _hhc)
: x(Range(T)(_llc.x, _hhc.x)), y(Range(T)(_llc.y, _hhc.y))
{}

Range2d(T)::Range2d(T)(T x1, T y1, T x2, T y2)
: x(Range(T)(x1, x2)), y(Range(T)(y1, y2))
{}

gdoublet(T) Range2d(T)::area() const
	{ return gdoublet(T)(x.length(), y.length());}
long Range2d(T)::weight() const
	{ return (long)(x.weight()) * (long)(y.weight());}

Range2d(T)::operator void *() const
	{ return (void *)x && (void *)y ? (void *)this : 0;}

Range2d(T) operator&(const Range2d(T)& a, const Range2d(T)& b)
{ return Range2d(T)(a.x&b.x, a.y&b.y); }

Range2d(T) operator|(const Range2d(T)& a, const Range2d(T)& b)
{ return Range2d(T)(a.x|b.x, a.y|b.y); }

gdoublet(T) Range2d(T)::llc() const {return gdoublet(T)(x.low, y.low);}
gdoublet(T) Range2d(T)::hlc() const {return gdoublet(T)(x.high, y.low);}
gdoublet(T) Range2d(T)::lhc() const {return gdoublet(T)(x.low, y.high);}
gdoublet(T) Range2d(T)::hhc() const {return gdoublet(T)(x.high, y.high);}

BOOL operator==(const Range2d(T)& a, const Range2d(T)& b)
{ return a.x==b.x && a.y==b.y; }

BOOL operator==(const Range2d(T)& a, const gdoublet(T)& b)
{ return b.x==a.x && b.y==a.y; }

C Range2d(T)& Range2d(T)::operator &=(C Range2d(T)& a)
{ x &= a.x; y &= a.y; return *this; }

C Range2d(T)& Range2d(T)::operator |=(C Range2d(T)& a)
{ x |= a.x; y |= a.y; return *this; }

Range2d(T)::Range2d(T)() {;}

BOOL Range2d(T)::superset_of(C Range2d(T)& a) C
{
 return x.superset_of(a.x) && y.superset_of(a.y);
}

BOOL Range2d(T)::subset_of(C Range2d(T)& a) C
{
 return x.subset_of(a.x) && y.subset_of(a.y);
}

Range2d(T)::Range2d(T)(const gdoublet(T)& c)
: x(c.x), y(c.y) {}

PT_end
#endif
