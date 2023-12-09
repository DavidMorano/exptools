

#include <real.h>
#include <assert.h>
#include <trig.h>

Real absbound(Real x) {
	if ( x.obvious_zero() ) return x ;
	Plimit bound_t = rel_plimit(10) ;
	int s = x.sign(bound_t) ;
	if ( s > 0 ) return x ;
	if ( s < 0 ) return -x ;
	Exp_t e ;
	long n ;
	x.split(e,n,1,bound_t) ;
	if ( n <= 0 ) n = 0 ;
	return Real(n+1) << e ;
	}

AtanSeries::AtanSeries(Real x) 
{
	n = 1 ;
	xsquare = x*x ;
	p = x ;
	term = x ;
	sgn = 1 ;
	}

AtanSeries::~AtanSeries() { }

void AtanSeries::step() {
	n += 2 ;
	sgn = -sgn ;
	p = p*xsquare ;
	term = p/Real(sgn*n) ;
	} 

Real AtanSeries::bound()
{
	return absbound(term) ;
	}

Real AtanSeries::next() 
{
	return term ;
	}

Real atan(Real x) {
	AtanSeries* s = new AtanSeries(x) ;
	return Real(s) ;
	}

SinSeries::SinSeries(Real x) :
	xsq(x*x),
	k(1),
	sgn(1),
	term(x)
{
	// Normalize
	term.sign(plimit(2) ) ;
	xsq.sign(plimit(2) ) ;
	}

SinSeries::~SinSeries() { } 

void SinSeries::step() {
	term = term*xsq/((k+1)*(k+2)) ;
	term.sign(rel_plimit(1)) ;
	k = k+2 ;
	sgn = -sgn ;
	}

Real SinSeries::bound() {
	return absbound(term) ;
	}

Real SinSeries::next() {
	return sgn*term ;
	}

CosSeries::CosSeries(Real x) :
	xsq(x*x),
	k(0),
	sgn(1),
	term(1)
{
	xsq.sign(abs_plimit(2) ) ;
	}

CosSeries::~CosSeries() { } 

void CosSeries::step() {
	term = term*xsq/((k+1)*(k+2)) ;
	term.sign(rel_plimit(1)) ;
	k = k+2 ;
	sgn = -sgn ;
	}

Real CosSeries::bound() {
	return term ; // Cos term is always positive
	}

Real CosSeries::next() {
	return sgn*term ;
	}


static Real mypi ;

Real half_pi = pi()>>1 ;

Real pi()
{
	static int initialized = 0 ;
	if ( !initialized ) {
		Real a5 = atan(Real(1)/Real(5)) ;
		Real a239 = atan(Real(1)/Real(239)) ;
		mypi = 4*(4*a5-a239) ;
		initialized = 1 ;
		}
	return mypi ;
	}

static inline Real twopi() { return pi() << 1 ; }
static inline Real halfpi() { return pi() >> 1 ; }

Real sin(Real x)
{
	Real n = (x/halfpi()).round(round_near,plimit(10)) ;
	x = x - n*halfpi() ;

	int quad = modf(n,Real(4),n).iround(round_near,abs_plimit(1)) ;

	while ( quad < 0 ) quad += 4 ; // in case funny % operation

	switch ( quad )
	{
		case 0 : return Real(new SinSeries(x)) ;
		case 1 : return Real(new CosSeries(x)) ;
		case 2 : return -Real(new SinSeries(x)) ;
		case 3 : return -Real(new CosSeries(x)) ;
		default : assert(0) ; return 0 ;
		}
	}

Real cos(Real x)
{
	return sin(x + half_pi ) ;
	}

Real tan(Real x) 
{
	Real n = (x/twopi()).round(round_near,plimit(10)) ;
	// I'm sure there is a better way, but this is simple.
	x = x-n*twopi() ;
	return sin(x)/cos(x) ;
	}
