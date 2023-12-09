//version 10/28/88

#ifndef REAL_H
#define REAL_H

typedef long		Exp_t ;	// Type used for exponent

static int const BITSINLONG = 32 ;

			// Number of bits in a long (including sign)


// A Plimit specifies the amount to computation to do before
// deciding that some Real is zero.

class Real ;

struct Plimit {
public:
	friend Plimit abs_plimit(int) ;	// absolute in bits
	friend Plimit rel_plimit(int) ;	// relative in bits
	friend Plimit operator+(Plimit,Plimit) ;
	friend Plimit plimit(int) ;	// both in bits
private:
	short	relative ;
	short 	absolute ;
	friend	Real ;
	} ;

extern Plimit inf_plimit ;
	// infinite plimit. Loop forever on infinite
	// expansions.

extern Plimit divide_plimit ;	// denominator is zero
extern Plimit relation_plimit ;	// relations
extern Plimit io_plimit ;		// inserter
extern Plimit split_plimit ;	// split
extern Plimit round_plimit ;	// rounding.  Only abs is used.

extern Plimit underflow_plimit ;

					// An undeflow occurs when
					// some computation is done
					// to this plimit and we
					// still don't know if the value
					// is zero.

// The following variables are used to control the maximum number
// of bits certain operations are carried out to.  They are all initially
// set to 1024, but may be modified.  See normalize, truncate, equal,
// sign, and gt.
				
class Single ;
class Series ;

enum Round_dir {
	round_down,		// toward zero,
	round_up,		// away from zero,
	round_near,		// toward nearest,
	round_pos,		// toward positive infinity
	round_neg		// toward negative infinity
	} ;

class Real {
private:
	Exp_t			exp ;
	Single*			mantissa ;
	void			setm(Single* newm) ; 
			// Assign newm to mantissa.  This is 
			// an explicit operation to ease keeping track
			// of reference counts.

	void		normalize(int n=0) ;
			// Force expansion and adjustment of exp and
			// mantissa without changing value of *this.
			// Stop when one of the following has been
			// established 
			// 	Mantissa is a true zero.
			//	Mantissa has a non-zero leading Bigit with
			//		absolute value greater than 1
			//	Mantissa has a leading Bigit with absolute 
			//		value 1. And the sign of fraction
			//		is same as the sign of the leading
			//		Bigit.
			//	At least n bigits have been examined. 

	void		normalize(Plimit t) ;
			// Normalize according to the plimit
			// Used by lots of other functions that take a
			// plimit

	void		underflow(Plimit t = underflow_plimit ) ;
			// A computation has "run out" at plimit t.
			// Either treat as an underflow or return depending
			// on whether t required more computation than
			// underflow_plimit.

	friend Single ;	friend Series ;

	friend Real 		operator+(Real&,Real&) ;
	friend Real 		operator*(Real&,Real&) ;
	friend Real 		operator/(Real&,Real&) ;
	friend Real		operator-(Real&,Real&) ;

	friend Real 		operator+(long,Real&) ;
	friend Real 		operator*(long,Real&) ;
	friend Real 		operator/(long,Real&) ;
	friend Real		operator-(long,Real&) ;

	friend Real 		operator+(Real&,long) ;
	friend Real 		operator*(Real&,long) ;
	friend Real 		operator/(Real&,long) ;
	friend Real		operator-(Real&,long) ;

	friend Real		operator-(Real&) ;
	friend Real		operator<<(Real&,long) ;
	friend Real		operator>>(Real&,long) ;
	friend Real		fabs(Real) ;

				Real(Exp_t,Single*) ;
    public:
			Real() : mantissa(0) { }
			// Unitialized Reals are permitted (after all
			// this is C++ not Ada)

			Real(long) ;
			//Real(unsigned long) ;
			Real(int) ;
			//Real(unsigned int) ;
			// Initialize a Real with an integral value

			Real(double) ;
			// Initialize a Real with a double.

			Real(Series*) ;

	static void	(*uflowaction)(Real&) ;
			// Program may set this non-zero.  If so it
			// is called by underflow, and underflow does
			// not itself coredump.  The argument is
			// the Real that is has overflowed. 

	void		split(Exp_t& e, long& n,
				int prec = BITSINLONG-1,
				Plimit = split_plimit ) ;

			// value is 2^e * n +- 1
			// n has prec bits.  I.e. it is, its absolute value
			// is between 1<<(prec-1) and (1<<prec)-1
			// Obviously prec must be at least 1.

					
	void		split(Exp_t& e, Real& r,
					Plimit = split_plimit ) ;

			// value is r*2^e 
			// with absolute value of r in range (half,1)
			// not including the boundary points.

			// Where half (an approximation to 1/2) is
			// 	1/2 - 1/2^(b+1)

			// The splitting is done on the basis of at least
			// b bits, and a number less than
			// 1/2^abs may be reported
			// as an underflow, with e being set to less
			// than -abs and r being set to 1.
		
	void		split(Exp_t &, Single* &, int n = 0 ) ;
			// Access to internal representation.  Useful
			// only in code that can manipulate Singles.
			// n is number of Bigits to normalize
			// rather than a Plimit.  

	Real		round(Round_dir=round_down,
				Plimit = round_plimit);
	long		iround(Round_dir=round_down,
				Plimit = round_plimit);

			// value is rounded to an integer.  Direction
			// depends on dir.

			// Plimit is slightly different than usual.
			// Relative is ignored, absolute is used
			// for "look ahead". 


	void		show(int force=0,char* pfx=0,char* sfx="\n") ;

			// Intended for debugging.
			// value is expanded to 
			// at least force bigits, and a symbolic value
			// is printed on cdebug, preceeded by pfx
			// and followed by sfx.

			// The format of this value is described in
			// the TM but is not considered a guaranteed
			// part of the package.
	
	int		sign(Plimit = relation_plimit ) ;

			// returns +1, 0, or -1 depending on whether
			// value is greater than, equal or less than
			// zero.  

			// "Exact zeros", such as those constructed as
			// Real(0), will always be reported as 0.
			// But some "obvious identities", such as x-x,
			// may be missed.
	
	
	int		obvious_zero() ;
			// Similar to sign.  It returns non-zero
			// if given a value that is "obviously"
			// zero.  

	int		equal(Real &r, Plimit = relation_plimit) ;
	int		gt(Real &r, Plimit = relation_plimit) ;
	int		ge(Real &r, Plimit = relation_plimit) ;
			
			// Equal, gt and ge return non-zero if "this" is
			// equal to , greater than, or at least
			// as great as (i.e. greater or equal) to r.
			// The comparison is made to within the specified
			// plimit and these differ in what they return
			// when the two values are equal as far as expanded,
			// but the expansion is cut off by the plimit.

			// In that case "equal" and "ge" return non-zero,
			// but "gt" returns 0.


	int		equal(long) ;
	int		lt(long) ;
	int		le(long) ;
	int		gt(long) ;
	int		ge(long) ;

			// Compare the Real  to the argument.  Using
			// relation_plimit. 

			operator double() ;
	double		dbl(Plimit) ;
			// returns the double approximation to
			// the value.  Overflow and underflow are
			// possible of course.

	Real operator+=(Real& y) ;
	Real operator-=(Real& y) ;
	Real operator*=(Real& y) ;
	Real operator/=(Real& y) ;
	Real operator+=(long y ) ;
	Real operator-=(long y ) ;
	Real operator*=(long y ) ;
	Real operator/=(long y ) ;

			Real(Real&) ;
			~Real() ;
	void		operator=(Real&) ;
		
} ;

inline int operator==(Real &x, Real &y) { return x.equal(y) ; }
inline int operator!=(Real &x, Real &y) { return !x.equal(y) ; }
inline int operator> (Real &x, Real &y) { return x.gt(y) ; }
inline int operator>=(Real &x, Real &y) { return !y.gt(x) ; }
inline int operator< (Real &x, Real &y) { return y.gt(x) ; }
inline int operator<=(Real &x, Real &y) { return !x.gt(y) ; }

inline int operator==(Real &x, long y) { return x.equal(y) ; }
inline int operator!=(Real &x, long y) { return !x.equal(y) ; }
inline int operator> (Real &x, long y) { return x.gt(y) ; }
inline int operator>=(Real &x, long y) { return x.ge(y) ; } 
inline int operator< (Real &x, long y) { return x.lt(y) ; }
inline int operator<=(Real &x, long y) { return x.le(y) ; }

inline int operator==(long x, Real &y) { return y.equal(x) ;}
inline int operator!=(long x, Real &y) { return !y.equal(x) ;}
inline int operator> (long x, Real &y) { return y.lt(x) ;}
inline int operator>=(long x, Real &y) { return y.le(x) ;}
inline int operator< (long x, Real &y) { return y.gt(x) ;}
inline int operator<=(long x, Real &y) { return y.ge(x) ;}

// Define the asgop operations in terms of the basic operations 

// Define the asgop operations in terms of the basic operations 
inline Real Real::operator+=(Real& y) { *this = *this+y ; return *this ; }
inline Real Real::operator-=(Real& y) { *this = *this-y ; return *this ; }
inline Real Real::operator*=(Real& y) { *this = *this*y ; return *this ; }
inline Real Real::operator/=(Real& y) { *this = *this/y ; return *this ; }
inline Real Real::operator+=(long y ) { *this = *this+y ; return *this ; }
inline Real Real::operator-=(long y ) { *this = *this-y ; return *this ; }
inline Real Real::operator*=(long y ) { *this = *this*y ; return *this ; }
inline Real Real::operator/=(long y ) { *this = *this/y ; return *this ; }


// Series is intended to be derived from

class Inf_sum ;
class Series {
	friend		Real ; friend Inf_sum ;
	char		embedded ;
	Real		embed() ;
protected:
	/* Following virtuals must be supplied in derived class */

			Series() ;
			virtual ~Series() ;

	virtual Real	bound() ;	// bound on sum of all remaining terms
	virtual Real	next() ;	// next term
	virtual void	step() ;	// delete next term

public:
	void		show(char* pfx=0,char* sfx="\n") ;
} ;

class iostream ;
iostream& operator<<(iostream&,Real) ;
iostream& operator>>(iostream&,Real&) ;

// The following guarantees that initializations take place.
// before any use of Reals.

class Real_init {
	static int	initcount ;
    public:
			Real_init() ;
			~Real_init() ;
} real_initializer ;

// overload modf, sin, cos, tan;
// overload asin, acos, atan atan2;
// overload exp, log, pow, ator;
#include <math.h>
#undef  PI
#define PI pi() 
// If math.h is included later you will get a complaint about
// PI be redefined.  I think this is better than no warning
// although it does put an annoying constraint on order of includes

Real acos(Real) ;
Real asin(Real) ;
Real atan(Real) ;
Real atan(Real,Real) ; /* same as atan2, take advantage of overloading */
Real atan2(Real,Real) ;
Real ator(char*);
Real ator(unsigned char*);
Real cos(Real) ;
Real natlogbase() ;
Real exp(Real) ;
Real log(Real) ;
Real frexp(Real,int*) ;
Real modf(Real,Real&, Plimit = round_plimit) ;
Real modf(Real,Real,Real&, Plimit = round_plimit) ;
inline Real modf(Real v, Real* ip) { return modf(v,*ip) ; }
Real pi() ;
Real pow(Real,Exp_t) ;
Real pow(Real,Real) ;
Real sin(Real) ;
Real sqrt(Real) ;
Real tan(Real) ;

inline Real floor(Real v) { return v.iround(round_neg,round_plimit) ; }
inline Real ceil(Real v)  { return v.iround(round_pos,round_plimit) ; }
inline Real rint(Real v)  { return v.iround(round_near,round_plimit) ; }

// There are other math functions not yet implemented.

#endif /* REAL_H */
