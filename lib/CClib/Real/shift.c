
#include <exact.h>
#include <assert.h>

Single* mk_shift(Single* x, Shift s)
{
	if ( s==0 ) return x ;
	if ( x->isz() ) return x ;
	//if ( s==1 ) return mk_single(0,x) ;

	return new Shifted(x,s) ;
	}

Shifted::Shifted(Single* x_arg, Shift rs_arg) :
	rightshift(rs_arg)
{
	x = x_arg ;
	assert(rs_arg>0) ;
	upref(x) ;
	Bigit low, up ;
	x->bounds(low,up) ;
	setb(low>0?0:-1, up<0?0:1) ;
	}

void Shifted::freeup()
{
	downref(x) ;
	}

void Shifted::do_expand() { i_am(0,mk_shift(x,rightshift-1)) ; }

Shift Shifted::leadingz() { return rightshift + x->s() - 1 ; }

Single* Shifted::remaining(Shift s)
{
	if ( s > rightshift ) return x->f(s-rightshift) ;
	else if ( s==rightshift ) return x ;
	else if ( s==1 ) {
		expand() ;
		return f(s) ; // won't be a recursive called because
				// we expanded.
		}
	else return mk_shift(x,rightshift-s) ;
	}
