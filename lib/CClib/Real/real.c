
#include <real.h>
#include <exact.h>
#include <assert.h>
#include <math.h>

#include <stream.h>
#ifndef cdebug
	// stuff for backward compatibility with old stream package
#	define cdebug cerr
	typedef ostream iostream ;
	inline static long ptr(void* p) { return (long)p ; }
#else
	inline static void* ptr(void* p) { return p ; }
#endif

int inline bigit_size(BBigit b)
{
	return ( b<BB && b>-BB ) ;
	}

inline void Real::setm(Single* newm)
{
	upref(newm) ;
	if ( mantissa ) downref(mantissa) ;
	mantissa = newm ;
	}

Real::Real(Exp_t e, Single* f) : 
	exp(e),
	mantissa(0) 
{
	setm(f) ;
	}

Real::Real(long n) : 
	mantissa(0) 
{
	exp = 0 ;
	long t = long(BBigit(n)/BB)  ;
	setm( mk_single(BBigit(n)-B*t,0) ) ;
	while ( t != 0 ) {
		// biggests longs may be several Bigits
		n = t ;
		t = long(BBigit(t)/BB) ;
		setm( mk_single(BBigit(n)-B*t,mantissa) ) ;
		++exp ;
		} 
	}

Real::Real(int m) : mantissa(0) { *this = Real((long)m); }

Real::Real(double d) : mantissa(0) 
{
	int e ;
	double x ;
	x = frexp(d,&e) ;
	Real r = 0 ;
	while ( x ) {
		x =  x * double(1<<BITSINBIGIT)  ;
		e -= BITSINBIGIT ;
		r += Real(long(x)) << e ;
		x -= int(x) ;
		} 

	setm(r.mantissa) ;
	exp = r.exp ;
	}

Real::Real(Series* s) : mantissa(0)
{
	*this = s->embed() ;
	}
	
Real::Real(Real& r) :
	mantissa(0)
{
	this->exp = r.exp ;
	setm( r.mantissa );
	}

Real::~Real()
{
	if (mantissa) downref(mantissa) ;
	}

void  Real::operator=(Real& r) {
	this->exp = r.exp ;
	setm( r.mantissa );
	}

void Real::normalize(Plimit t) 
{
	int count = exp + t.absolute + 1 ;
	if ( t.relative > count ) count = t.relative ;
	normalize(count) ;
	}

void Real::normalize(int count) 
{
	if ( mantissa->isz() && exp > -underflow_plimit.absolute) {
		exp -= count ;
		return ;
		}

	Shift xs = mantissa->s() ;
	setm(mantissa->f(xs) ) ;
	exp -= xs ;

	while ( --count >= 0 ) {
		if ( mantissa->isz() ) return ;
		Bigit low, up ;
		mantissa->bounds(low,up) ;
		if ( low > 0 || up < 0 ) return ;

		Bigit b = mantissa->n() ;

		if ( b == 1 && mantissa->f()->whatsign(count-1) < 0 ) {
			setm(mk_sum(B,mantissa->f(),mk_zero())) ;
			--exp ;
			}
		else if ( b == -1
				&& mantissa->f()->whatsign(count-1) > 0 ) {
			setm(mk_sum(-B,mantissa->f(),mk_zero())) ;
			--exp ;
			}
		else if ( b == 0 ) {
			setm(mantissa->f());
			--exp ;
			}
		else {
			return ;
			}
		}
	}


static inline long nth_bit(long n, int b) 
{
	return (n>>(b-1)) & 1 ;
	}

void Real::split(Exp_t &e, long &m, int prec, Plimit t)
{
	normalize(t) ;
	if ( obvious_zero() ) {
		m = 0 ;
		e = exp ;
		return ;
		}
	Single* r = mantissa ;
	e = exp*BITSINBIGIT ;
	m = long(r->n()) ;
	r = r->f() ;

	if ( m == 0 )  underflow(t) ;

		
	if ( m>=-1 && m<=1 ) {
		// marginal value from normalization
		e = exp*BITSINBIGIT ;
		return ;
		}

	if ( prec < 1 ) prec = 1;

	long lowlim, uplim ;
	lowlim = 1<< (prec-1);
	uplim = lowlim ;
	uplim += lowlim-1 ;	// care in computing uplim to avoid
				// overflow whem maximum precision is
				// reqested.

	int msign  ;	// sign of m (1 or -1) 

	if ( m > 0 ) 	msign = 1 ;
	else {
		msign = -1 ;
		m = -m ;
		}
	
	int need = 0 ;
	while ( m < lowlim ) {
		m = m << 1 ;
		++need ;
		--e ;
		}
	while ( need >= BITSINBIGIT ) {
		m  |= (msign*(long)(r->n()))  << (need-BITSINBIGIT) ;
		r = r->f() ;
		need -= BITSINBIGIT ;
		}
	if ( need > 0 ) {
		m |= (msign*(long)(r->n())) >> (BITSINBIGIT-need) ;
		}
	assert ( m >= lowlim) ;

	while ( m > uplim ) {
		m = m/2 ;
		++ e ;
		}

	assert ( m <= uplim ) ;

	if ( msign < 0 ) m = -m ;
	}

void Real::split(Exp_t &t, Real &r, Plimit tol)
{
	normalize(tol) ;
	if ( obvious_zero() ) {
		r = Real(0) ;
		return ;
		}

	// n and t will hold a preliminary split.

	Bigit n  = mantissa->n() ;
	t = exp*BITSINBIGIT ;
	
	if ( n==0 ) {
		underflow(tol) ;
		t = exp*BITSINBIGIT ;
		n = mantissa->n() ;
		if ( n==0 ) n = 1 ;
		}
	else if (n==1) {
		// We have to verify that we look at enough
		// bits after the binary point.
		normalize(tol.relative) ;
		n = mantissa->n() ;
		t = exp*BITSINBIGIT ;
		}
	int shift = 0 ;
	if ( n < 0 ) n = -n ;
	while ( n < B/2 ) {
		n=2*n ;
		++shift ;
		}

	t -= shift ;	
	t += BITSINBIGIT ;
	r = Real(-1,mk_mult(0,1<<shift,mantissa)) ;
	}

void Real::split(Exp_t &e_arg, Single* &mantissa_arg, int n) 
{
	normalize(n) ;
	e_arg = exp ;
	mantissa_arg = mantissa ;
	}

Real Real::round(Round_dir dir, Plimit t) 
{
	normalize(t) ;

	Exp_t e = exp+1;
	if ( e < 0 ) e = 0 ;

	Withcarry  r = cround(mantissa,e,dir,t.absolute) ;

	if ( r.carry != 0 ) {
		return Real(e,mk_single(r.carry,r.bval)) ;
		}
	else {
		return Real(e-1,r.bval) ;
		}
	}

long Real::iround(Round_dir dir, Plimit t)
{
	return long(double((round(dir,t)))) ;
	}

int Real::sign(Plimit t)
{
	normalize(t) ;
	if ( obvious_zero() ) return 0 ;

	int sg = mantissa->whatsign(1) ;
	if ( sg==0 && !mantissa->isz()) {
		underflow(t) ;
		normalize(0) ;
		sg = mantissa->whatsign(1) ;
		}
	return sg ;
	}

int Real::obvious_zero()
{
	return mantissa->isz() ;
	}

int Real::equal(Real &y, Plimit t)
{
	Real diff = *this-y ;
	return diff.sign(t) == 0;
	}

int Real::gt(Real &y, Plimit t)
{
	Real diff = *this-y ;
	return diff.sign(t) > 0;
	}

int Real::ge(Real &y, Plimit t)
{
	Real diff = *this-y ;
	return diff.sign(t) >= 0;
	}


static double powb(Exp_t e)
{
	// This function is subject to floating point overflow and
	// underflow. 
	double pow ; 
	if ( e < 0 ) {
		e = -e ;
		pow = 1./(double)B ;
		}
	else {
		pow = B ;
		}

	double accum = 1. ;

	while ( e ) {
		if ( e&1 ) accum = accum * pow ;
		e = e >> 1 ;
		if ( e ) pow = pow*pow ;
		}
	return accum ;
	}

Real::operator double () {
	return dbl(split_plimit) ;
	}

double Real::dbl(Plimit t)
{
	normalize(t) ;
	if ( obvious_zero() ) return 0.0 ;
	double e = 1 ;
	Single* m = mantissa ;
	double val = 0. ;
	for ( int x = (BITSINDOUBLE+BITSINBIGIT-1)/BITSINBIGIT ;
			x > 0 && !m->isz() ; --x ) {
		val += e * long(m->n()) ;
		e /= long(B) ;
		m = m->f() ;
		}
	return powb(exp) * val ;
	}
	
Real operator+(Real& x1, Real& x2) 
{
	Exp_t e;
	Single* f1 ;
	Single* f2 ;
	
	// Maybe some special cases should be handled here.  I leave that
	// for "tuning".  The general case is treated below.

	if ( x1.exp == x2.exp) {
		e = x1.exp ;
		f1 = x1.mantissa ;
		f2 = x2.mantissa ;
		}
	else if ( x1.exp > x2.exp ){
		e = x1.exp ;
		f1 = x1.mantissa ;
		f2 = mk_shift(x2.mantissa,x1.exp-x2.exp);
		}
	else { /* x2.exp > x1.exp */
		e = x2.exp ;
		f1 = mk_shift(x1.mantissa,x2.exp-x1.exp) ;
		f2 = x2.mantissa ;
		}

	Withcarry tot = csum(f1,f2) ;

	Real r ;
	if ( tot.carry != 0 ) {
		r = Real(e+1,mk_single(tot.carry,tot.bval)) ;
		}
	else {
		r = Real(e,tot.bval) ;
		}
	r.normalize(1) ;
	return r ;
	}

Real operator*(Real& x1, Real& x2) 
{
	Real r = Real(x1.exp+x2.exp+1,
			mk_prod(x1.mantissa,x2.mantissa)) ;
	r.normalize(1) ;
	return r ;
	}

// Multiplication by a long gets special case for efficiency.
// Others could too, but it seems more important here.

Real operator*(long m, Real& x)
{
	if ( bigit_size(m) ) {
		Withcarry p = cmult(m,x.mantissa) ;
		if ( p.carry != 0) {
			return Real(x.exp+1,mk_single(p.carry,p.bval)) ;
			} 
		else {
			return Real(x.exp,p.bval) ;
			}
		}
	else {
		return Real(m)*x ;
		}
	}
	
Real operator/(Real& n, Real& d)
{
	if ( d.sign() == 0 ) {
		d.underflow(underflow_plimit) ;
		if ( d.mantissa->n() == 0 ) {
			d = Real(1)>>(d.exp*BITSINBIGIT) ;
			}
		}

	Exp_t e = n.exp-d.exp ;
	Single*	num = n.mantissa ;
	d.normalize(1) ;
	Single* den = d.mantissa ;

	return Real(n.exp-d.exp,mk_div(num,den) ) ;
	}
	
Real operator-(Real& x)
{
	return Real(x.exp,mk_minus(x.mantissa)) ;
	}

Real operator-(Real& x1, Real& x2) 
{
	Real r = x1+(-x2) ;
	return r ;
	}

Real operator<<(Real& x, long s)
{
	Exp_t e = x.exp ;
	Exp_t steps = s/BITSINBIGIT ;
	e += steps ;
	s -= steps*BITSINBIGIT ;
	while ( s >= BITSINBIGIT ) {
		++e ;
		s -= BITSINBIGIT ;
		}
	while ( s < 0 ) {
		--e ;
		s += BITSINBIGIT ;
		}
	Real r = Real(e,x.mantissa) ;
	if ( s > 0 ) r = r * Real(1<<s) ;
	return r ;
	}

Real operator>>(Real& x, long s) 
{
	return x<<(-s) ;
	}

Real fabs(Real r) 
{
	Single* m ;
	Exp_t e ; 
	r.split(e,m) ;
	return Real(e,mk_abs(m)) ;
	}

// Some functions that might be inlined, but aren't to avoid
// unwanted constructor/destructor calls. (These tend to be a problem
// not for efficiency but because they limit use of arithmetic in
// conditions containing && and ||

int Real::equal(long n) { return *this == Real(n) ; }
int Real::lt(long n) { return *this <  Real(n) ; }
int Real::le(long n) { return *this <= Real(n) ; }
int Real::gt(long n) { return *this >  Real(n) ; }
int Real::ge(long n) { return *this >= Real(n) ; }
Real operator*(Real &x, long m) { return m*x ; }
Real operator/(Real &x, long m) { return x/Real(m) ; }
Real operator+(Real &x, long m) { return x+Real(m) ; }
Real operator-(Real &x, long m) { return x-Real(m) ; }
Real operator/(long m, Real &x) { return Real(m)/x ; }
Real operator+(long m, Real &x) { return Real(m)+x ; }
Real operator-(long m, Real &x) { return Real(m)-x ; }

void Real::underflow(Plimit t) 
{
	static const int Real_underflow = 0 ;

	if (t.absolute < underflow_plimit.absolute ) return ;
	if (t.relative < underflow_plimit.relative ) return ;

	// Want to treat this as a real underflow.

	if (uflowaction) (*uflowaction)(*this) ;
	else 		assert( Real_underflow ) ;
	}

void Series::show(char* pfx, char* sfx)
{
	cdebug << pfx << "SOMESERIES" << sfx ;
	cdebug.flush() ;
	}

static Single_init* requires_single ;

Real_init::Real_init() {
	// This constructor will be called once for each time real.h is
	// #included.  The following causes it to return immediatly 
	// except the first time it is called.

	++initcount ;
	if ( initcount > 1 ) return ;

	Plimit t = plimit(1<<10)  ;

	underflow_plimit	= t ;
	divide_plimit		= t ;
	relation_plimit		= t ;
	io_plimit		= t ;	
	split_plimit		= t ;
	round_plimit 		= t ; 

	Real::uflowaction 	= 0 ;

	/* Real constructors use things declared in exact.h.
	 * But real.h does not include exact.h.
	 * To insure proper initialization we must guarantee that
	 * The "Exact package" is initialized whenever the "Real
	 * package" has been initialized.
	 */
	requires_single		= new Single_init ;
	}

Real_init::~Real_init() {
	--initcount ;
	if ( initcount > 0 ) return ;
	
	delete requires_single ;
	}

// The following two functions ought to be defined in series.c
// They are put in this file because of a bug in the current
// version of cfront (3/15/88) 
