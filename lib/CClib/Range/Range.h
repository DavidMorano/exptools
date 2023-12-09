#ifndef RANGE_H
# define RANGE_H
// Range version 1.6, 2/13/91, Greg Kochanski C++ 2.1 -- all machines.

// Ranges of integers, doubles, Strings, you name it.
// A Range seperates the set of all numbers into a region that is too small,
// one that is too big, and one that is just right.
// Ranges are ordered -- a range with low>high is empty.
// Comparison operators are necessary.
// Class nRange(T) has extra stuff for numeric ranges.
# ifndef STD_H
 typedef short BOOL;	/* Use BOOL for logical variables as a reminder to
						the programmer. */
# endif

PT_names
 Range(T) Range_ T
 nRange(T) nRange_ T
PT_end

PT_define Rangedeclare(T)
class Range(T)	{
	private:	// defined here to catch errors involving Range(T)(T x)
	BOOL superset_of(T);	// these functions do NOT exist.
	BOOL subset_of(T);
	const Range(T)& operator=(T);
	public:
	T low, high;
	Range(T)(T l, T h)	: low(l), high(h) {}
	Range(T)(T x) : low(x), high(x)	{}
	operator void *() const	{return high>=low ? (void *)this : 0;}
	BOOL operator!() const	{return high < low;}
	BOOL operator<(T x) const	{return x>high;}
	BOOL operator>=(T x) const	{return x<=high;}
	BOOL operator>(T x) const	{return x<low;}
	BOOL operator<=(T x) const	{return x>=low;}
	BOOL operator==(T x) const	{return x>=low && x<=high;}
	BOOL operator!=(T x) const	{return !((*this)==x);}
	const Range(T)& operator|=(const Range(T)& x);
	const Range(T)& operator&=(const Range(T)& x);
	int compare(T x) const;
	BOOL superset_of(const Range(T)& x)	const;
	BOOL subset_of(const Range(T)& x)	const;
	};
Range(T) operator&(const Range(T)& x, const Range(T)& y);
Range(T) operator|(const Range(T)& x, const Range(T)& y);

/* INLINE FUNCTION BODIES: */
inline BOOL operator==(const Range(T) &x, const Range(T)& y)
		{return (x.low==y.low && y.high==x.high) || (!x && !y);}
inline BOOL operator!=(const Range(T) &x, const Range(T)& y)
		{return !(x==y);}
inline BOOL operator<(T x, const Range(T)& y)	{return y>x;}
inline BOOL operator<=(T x, const Range(T)& y)	{return y>=x;}
inline BOOL operator>(T x, const Range(T)& y)	{return y<x;}
inline BOOL operator>=(T x, const Range(T)& y)	{return y<=x;}
inline BOOL operator==(T x, const Range(T)& y)	{return y==x;}
inline BOOL operator!=(T x, const Range(T)& y)	{return y!=x;}
inline BOOL Range(T)::superset_of(const Range(T)& x)	const
		{return (low<=x.low && high>=x.high) || !x;}
inline BOOL Range(T)::subset_of(const Range(T)& x)	const
		{return (low>=x.low && high<=x.high) || !*this;}
PT_end

PT_define Rangeimplement(T)
int Range(T)::compare(T x) const
		{return *this>x ? (-1) : (*this<x ? (1) : 0);}

const Range(T)& Range(T)::operator|=(const Range(T)& x)
{
 if(!*this)	(*this) = x;
 else if(x)	{
	if(x.low<low) low=x.low;
	if(high<x.high)high=x.high;
	}
 return *this;
}

const Range(T)& Range(T)::operator&=(const Range(T)& x)
{if(x.low>low) low=x.low; if(high>x.high)high=x.high; return *this;}
Range(T) operator&(const Range(T)& x, const Range(T)& y)
{
 const T *l = x.low>y.low ? &x.low : &y.low;
 const T *h = x.high>y.high ? &y.high : &x.high;
 return Range(T)(*l, *h);
}

Range(T) operator|(const Range(T)& x, const Range(T)& y)
{
 if(!x)	return y;
 else if(!y)	return x;
 const T *l = x.low<y.low ? &x.low : &y.low;
 const T *h = x.high<y.high ? &y.high : &x.high;
 return Range(T)(*l, *h);
}
PT_end

PT_define nRangedeclare(T)

Rangedeclare(T)

class nRange(T) : public Range(T)	{
	private:	// functions that do NOT exist:
	const nRange(T)& operator=(T);
	public:
	nRange(T)(T l, T h) : Range(T)(l, h) {;}
	nRange(T)(T x) : Range(T)(x) {;}
	nRange(T)() : Range(T)(1, 0) {;}
	nRange(T)(const Range(T)& x) : Range(T)(x) {;}
	const nRange(T)& operator=(const Range(T)& x) {low=x.low;high=x.high;return *this;}
	T length() const	{return (void *)(*this) ? high-low : 0;}
	T weight() const;
	double center(double fraction = 0.5) const;
	};
inline nRange(T) expand(const nRange(T)& x, double about, double factor);
inline nRange(T) expand(const nRange(T)& x, double factor);

inline nRange(T) expand(const nRange(T)& x,  double factor)
{ return expand(x, x.center(), factor);}
inline T nRange(T)::weight() const
{ return (void *)(*this) ? (0==(T)0.5 ? 1 : 0) + high-low : 0;}
PT_end

PT_define nRangeimplement(T)
Rangeimplement(T)
/* FUNCTION BODIES */
nRange(T) expand(const nRange(T)& x, double about, double factor)
	{return nRange(T)((T)(about-factor*(about-x.low)),
		(T)(about+factor*(x.high-about)));}
double nRange(T)::center(double fraction) const
		{return (1.0-fraction)*low + fraction*high;}
PT_end
#endif
