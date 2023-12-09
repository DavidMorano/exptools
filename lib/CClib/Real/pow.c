

#include <real.h>

Real pow(Real x,Exp_t n) {
    register Exp_t i = n ;
    if ( i < 0 ) {
	i = -i ;
	x = Real(1)/x ;
	}
    Real accum = 1 ;
    while ( i != 0 ) {
	if ( i&1 ) accum = accum*x ;
	i = i/2 ;
	x = x*x ;
	}
    return accum ;
    }

