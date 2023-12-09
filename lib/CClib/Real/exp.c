
#include <real.h>
#include <assert.h>
#include <exp.h>

static Real one = 1 ;
static Real two = 2 ;
static Real minus_one = -1 ;
static Real log2 = Real(new Log2) ;
static Real half = Real(1)>>1 ;


ExpSeries::ExpSeries(Real x_arg) :
	k(0),
	x(x_arg),
	term(1)
{
	Plimit easy_tol = plimit(10) ;

	if ( x_arg.sign(easy_tol) < 0 )	b = (-2)*x_arg + one ;
	else				b = 2*x_arg + one ;

	assert (!x_arg.gt(one,easy_tol) && !minus_one.gt(x_arg,easy_tol) ) ;
	}

ExpSeries::~ExpSeries() { }


Real ExpSeries::next()
{
	return term ;
	}

Real ExpSeries::bound()
{
	if ( term.obvious_zero() ) return Real(0) ;
	return b ;
	}

void ExpSeries::step() 
{
	k = k+1 ;
	b = b/k ;
	term = (term*x)/k ;
	}
LogSeries::LogSeries(Real x) :
	k(1)
{
	Real t = (x-Real(1))/(x+Real(1)) ;
	tpow = t ;
	tsq = t*t ;
	k = 1 ;
	term = 2*tpow ;
	}

LogSeries::~LogSeries()
{
	}

Real LogSeries::next()
{
	return term  ;
	}

void LogSeries::step() 
{
	k = k+2 ;
	tpow *= tsq ;
	term = 2*tpow/Real(k) ;
	}

Real LogSeries::bound()
{
	return Real(2)* fabs(term) ;
	}

Log2::Log2() :
	m( Real(1)/Real(9) ),
	p( Real(1)/Real(3) ),
	k(1)
{
	}

Log2::~Log2()
{
	}

Real Log2::next()
{
	return 2*(p/k) ;
	}

void Log2::step()
{
	k += 2 ;
	p = p*m ;
	}

Real Log2::bound()
{
	return 4*(p/k) ;
	}
	
static Real my_e ;

Real natlogbase() 
{
	static int einit = 0 ;
	if ( !einit ) {
		einit = 1 ;
		my_e = Real(new ExpSeries(one)) ;
		}
	return my_e ;
	}


Real exp(Real x) {
	// Return e raised to the x power.
	Real n  ;
	Real r = modf(x,n,plimit(10)) ;
	return pow(natlogbase(),long(double(n))) * Real(new ExpSeries(r)) ;
	}

Real log(Real x) {
	// Return natural log of x
	Exp_t e;
	Real r ;
	x.split(e,r,plimit(10)) ;
	--e ;
	r = r << 1 ;
	Real e1 = e*log2 ;
	Real l1 = Real(new LogSeries(r) ) ;
	Real sum = e1 + l1 ;
	return e1 + l1 ;
	} 

Real pow(Real x, Real y) 
{
	return exp(y*log(x)) ;
	}

Real sqrt(Real x) 
{
	return pow(x,half) ;
	}
