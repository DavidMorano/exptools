
#include <real.h>

Real modf(Real x, Real& i, Plimit t)
{
	i = x.round(round_neg,t) ;
	return x - i ;
	}

Real modf(Real x, Real y, Real& m, Plimit t)
{
	Real i ;
	modf(x/y,i,t) ;
	m = i*y ;
	return x - m ;
	}

Real frexp(Real x, int& i)
{
	Exp_t e ;
	Real r ;
	x.split(e,r) ;
	i = e ;
	return r ;
	}

Real frexp(Real x, int* i) 
{
	return frexp(x,*i) ;
	}
