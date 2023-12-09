
#include <exact.h> 

Single* mk_minus(Single* xx) 
{
	if ( xx->isz() )	return xx ;
	Shift rs = xx->s() ;
	if ( rs > 0 ) 		return mk_shift(mk_minus(xx->f(rs)),rs) ;

	return new Minus(xx) ;
	}


Minus::Minus(Single* x_arg)
{
	x = x_arg ;
	upref(x) ;
	Bigit low, up ;
	x->bounds(low,up) ;
	setb(-up,-low) ;
	}

void Minus::freeup()
{
	downref(x) ;
	}

void Minus::do_expand() 
{
	i_am(-x->n(),mk_minus(x->f())) ;
	}


void Minus::xnarrow(Bigit m)
{
	if ( m < 4 ) expand() ;
	else {
		x->narrow(m);
		Bigit low, up ;
		x->bounds(low,up)  ;
		setb(-up,-low) ;
		}
	}

Single* mk_abs(Single* xx)
{
	Bigit low, up ;
	xx->bounds(low,up) ;
	if ( low >= 0 ) return xx ;
	else if ( up <= 0 ) return mk_minus(xx) ;
	
	return new Abs(xx) ;
	}

Abs::Abs(Single* x_arg) {
	x = x_arg ;
	upref(x) ;
	Bigit low, up ;
	x->bounds(low,up) ;
	if ( -low > up ) up = -low ;
	setb(0,up) ;
	}

void Abs::freeup()
{
	downref(x) ;
	}

void Abs::do_expand()
{
	Bigit m = x->n() ;

	if ( m > 0 )	   i_am(m,x->f()) ;
	else if ( m < 0 )  i_am(-m,mk_minus(x->f())) ;
	else 		   i_am(0,mk_abs(x->f())) ;
	}	


void Abs::xnarrow(Bigit m)
{
	Bigit low,up ;
	x->narrow(m/2)->bounds(low,up) ;
	if ( -low > up ) up = -low ;
	setb(0,up) ;
	}
	
Single* mk_adjust(BBigit c, Single* x ) 
{
	if ( c==0 ) return x ;
	return new Sum(c,x,mk_zero()) ;
	}

Single* mk_sum(BBigit c, Single* x1, Single* x2)
{
	if ( c==0 ) {
		if ( x1->isz() ) return x2 ;
		if ( x2->isz() ) return x1 ;
		Shift s1 = x1->s() ;
		Shift s2 = x2->s() ;
		Shift xs = (s1>s2) ? s2 : s1 ;
		if ( xs > 1 ) {
			// xs-1 instead of xs below, because a leading 0'a
			// are needed to gurantee range constraints of
			// mk_sum. 
			return mk_shift(mk_sum(0,x1->f(xs-1),x2->f(xs-1)),
					xs-1) ;
			}
		}
	Sum* r = new Sum(c,x1,x2) ;
	return r ;
	}

static Small carryS(Single* x1, Single* x2)
{
	Bigit low1, up1, low2, up2 ;
	x1->bounds(low1,up1);
	x2->bounds(low2,up2);
	if ( low1+low2 > -B
			&& up1+up2 < B ) {
		return 0 ;
		}
	else if ( low1+low2 > 0 )	return 1 ;
	else if ( up1 + up2 < 0 ) 	return -1 ;
	else {
		x1->narrow(B/2-1);
		x2->narrow(B/2-1);
		return carryS(x1,x2) ;
		}
	}

Withcarry csum(Single* x1, Single* x2) 
{
	Small c = carryS(x1,x2) ;
	return Withcarry(c, mk_sum(-B*c,x1,x2) ) ;
	}

Sum::Sum(BBigit c_arg, Single* x_arg, Single* xprime_arg)
{
	i = c_arg ;
	x = x_arg ;
	xprime = xprime_arg ;
	upref(x) ;
	upref(xprime) ;
	Bigit low1, up1, low2, up2 ;
	x->bounds(low1,up1) ;
	xprime->bounds(low2,up2) ;
	setb(i+(BBigit)low1+(BBigit)low2, i+(BBigit)up1+(BBigit)up2) ;
	}

void Sum::xnarrow(Bigit m)
{
	// Narrow the one that has the smallest range first so that
	// when we narrow the second we can take advantage of any
	// extra leaway from a small range in the first.

	if ( x->range() < xprime->range() ) {
		x->narrow(m/2) ;
		xprime->narrow(m - x->range()) ;
		}
	else {
		xprime->narrow(m/2) ;
		x->narrow(m - xprime->range()) ;
		}

	BBigit low1, up1, low2, up2 ;
	x->bounds(low1,up1) ;
	xprime->bounds(low2,up2) ;
	setb(i+low1+low2, i+up1+up2) ;
	}

void Sum::freeup()
{
	downref(x) ;
	downref(xprime) ;
	}

void Sum::do_expand()
{
	Single* f1 = x->f() ;
	Single* f2 = xprime->f() ;
	Withcarry fs  = csum(f1,f2) ;
	i_am(i + (BBigit)x->n() + (BBigit)xprime->n() + fs.carry,
	     fs.bval) ;
	}

