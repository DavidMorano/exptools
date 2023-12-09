
#include <exact.h>
#include <assert.h>

Single* mk_mult(BBigit c, Bigit m, Single* x)
{
	if ( c==0 && m==1 ) return x ;
	if ( m==0 || x->isz() ) return mk_single(c,0) ;

	Shift xs = x->s() ;

	if ( c==0 && xs > 1 ) {
		// note that we need to preserve a leading 0 to
		// gurantee the range constraints of mk_mult.

		return mk_shift(mk_mult(0,m,x->f(xs-1)),xs-1) ;
		}

	// No optimizations
	return new Mult(c,m,x) ;
	}

static int mutual_top( Bigit& carry, BBigit low, BBigit up )
{
	// If there is some value that can be used as a carry when
	// The bounds on the value are low and up, return non-zero and
	// set carry.  Otherwise return 0.

	if ( up - low >= 2*BB ) return 0 ;

	Bigit t = lowtop(up) ;

	BBigit d = BBigit(t)*BB - low ;

	if ( -B < d && d < B ) {
		carry = t ;
		return 1 ;
		}
	else {
		return 0 ;
		}
	}

static Bigit carryM(Bigit m, Single* x) 
{
	BBigit mm = m ;
	BBigit low, up ;
	BBigit plow, pup ;
	if ( m == 0 ) return 0 ;
	if ( m > 0 ) {
		x->bounds(low,up) ;
		plow = mm*low ;
		pup = mm*up ;
		}
	else {
		x->bounds(low,up) ;
		plow = mm*up ;
		pup = mm*low ;
		}
	Bigit t ;
	if ( mutual_top(t,plow,pup) ) {
		return t ;
		}

	if ( x->isx() ) {
		// Big multiplier may need more than a single
		// Bigit of accuracy from x.  I think B/4 is narrow
		// enough, although I'm not 100% sure.
		BBigit p = mm*x->n() ;
		x->f()->narrow(B/4)->bounds(low,up) ;
		plow = p + lowtop(mm>=0 ? mm*low : mm*up) ;
		pup = p + uptop(mm>=0 ? mm*up : mm*low ) ;
		int ok = mutual_top(t,plow,pup) ;
		assert(ok) ;
		return t ;	
		}

	Bigit posm = m>0 ? m : -m ;
	assert(x->range() >= B/posm ) ;
	return carryM(m,x->narrow((B-1)/posm)) ;
	}

Withcarry Single::times(Bigit m) 
{
	Bigit n = carryM(m,this) ;
	return Withcarry(n,mk_mult(-BB*n,m,this)) ;
	}

Withcarry cmult(Bigit m, Single* x) 
{
	if ( m==0 ) return Withcarry(0,mk_zero()) ;
	if ( x->isz() ) return Withcarry(0,x) ;
	if ( m==1 ) return Withcarry(0,x) ;
	if ( m==-1) return Withcarry(0,mk_minus(x)) ;
	if ( x->isx() ) {
		Bigit n = carryM(m,x) ;
		return Withcarry(n,mk_mult(-BB*n,m,x)) ;
		}
	else {
		return x->times(m) ;
		}
	}
	
Mult::Mult(BBigit c_arg, Bigit m_arg, Single* x_arg)
{
	i = c_arg ;
	x = x_arg ;
	m = m_arg ;
	upref(x) ;
	Bigit xlow, xup ;
	x->bounds(xlow,xup) ;
	BBigit mm = m ;
	if ( m > 0 )	setb(i+mm*xlow, i+mm*xup ) ;
	else		setb(i+mm*xup, i+mm*xlow) ;
	}

void Mult::xnarrow(Bigit n)
{
	Bigit absm = m ;
	if ( absm < 0 ) absm = -absm ;
	x->narrow(n/absm) ;

	BBigit xlow, xup ;
	x->bounds(xlow,xup) ;
	BBigit mm = m ;
	if ( mm*(xup-xlow) <= n ) {
		if ( m >= 0 )	setb(i+mm*xlow, i+mm*xup ) ;
		else		setb(i+mm*xup, i+mm*xlow) ;
		}
	else {
		BBigit flow, fup ; 
		x->f()->narrow((BB*BBigit(n))/BBigit(absm)) ;
		x->f()->bounds(flow, fup) ;
		if ( m >= 0 ) {
			setb(i+mm*x->n()+lowtop(mm*flow),
			     i+mm*x->n()+uptop(mm*fup) ) ;
			}
		else { 
			setb(i+mm*x->n()+lowtop(mm*fup),
			     i+mm*x->n()+uptop(mm*flow) ) ;
			}
		}
	}

void Mult::freeup()
{
	downref(x) ;
	}

void Mult::do_expand()
{
	Withcarry r = cmult(m,x->f()) ;
	BBigit mn = (BBigit)m*(BBigit)x->n() + (BBigit)i + (BBigit)r.carry;
	i_am( mn, r.bval) ;
	}

Single* mk_prod(Single* x1, Single* x2) 
{
	if ( x1->isz() ) return mk_zero() ;
	if ( x2->isz() ) return mk_zero() ;

	Shift s1 = x1->s() ;
	Shift s2 = x2->s() ;
	if ( s1+s2 > 0 ) {
		return mk_shift(mk_prod(x1->f(s1),x2->f(s2)), s1+s2) ;
		}

	return new Prod(x1,x2) ;
	}


static void mbound(BBigit& low, BBigit&up, Single* x1, Single* x2)
{
	// Sets lower, upper to bounds on x1*x2
	// We go to a lot of trouble to make this accurate because
	// accuracy here means less bits are needed to form products
	// and this has a snowballing effect on amount of expansion
	// needed everywhere

	BBigit lim1[2], lim2[2] ;

	if ( x1->isx() ) {
		x1->f()->bounds(lim1[0],lim1[1]) ;
		lim1[0] += BB*BBigit(x1->n()) ;
		lim1[1] += BB*BBigit(x1->n()) ;
		}
	else {
		x1->bounds(lim1[0], lim1[1] ) ;
		lim1[0] *= BB ;
		lim1[1] *= BB ;
		}

	if ( x2->isx() ) {
		x2->f()->bounds(lim2[0],lim2[1]) ;
		lim2[0] += BB*BBigit(x2->n()) ;
		lim2[1] += BB*BBigit(x2->n()) ;
		}
	else {
		x2->bounds(lim2[0], lim2[1] ) ;
		lim2[0] *= BB ;
		lim2[1] *= BB ;
		}

	// at this point lim1[0] and lim1[1] are B times the bounds on x1.
	// And similary for lim2[0] and lim2[1] 
	
	low = BB*BB ;
	up = -BB*BB ;

	// We loop through the limits.  For each of the four possible
	// products we generate an exact product and compare this
	// to the previously determined limit.
	
	// Since the products get very large we have to do a double
	// precision computation ourselves.

	for ( int n1 = 0 ; n1 < 2 ; ++n1 ) {
		for ( int n2 = 0 ; n2 < 2 ; ++n2 ) {
			BBigit t1 = top(lim1[n1]) ;
			BBigit t2 = top(lim2[n2]) ;
			BBigit b1 = bot(lim1[n1]) ;
			BBigit b2 = bot(lim2[n2]) ;
			BBigit t = t1*t2 ;
			t += top(t1*b2) ;
			t += top(t2*b1) ;
			BBigit b = b1*b2 + BB*bot(t1*b2) + BB*bot(t2*b1) ;
			
			// There might be a carry
			while ( b >= BB*BB ) {
				++t ;
				b -= BB*BB ;
				}
			while ( b <= -BB*BB ) {
				--t ;
				b += BB*BB ;
				}

			// At this point we know that a limit is 
			// t + b^-2

			if ( t >= up ) { 
				up = t ;
				if ( b > 0 ) ++up ;
				}
			if ( t <= low ) {
				low = t ;
				if ( b < 0 ) --low ;
				}
			}
		}
	}
	 

Prod::Prod(Single* x_arg, Single* xprime_arg)
{
	x = x_arg ;
	xprime = xprime_arg ;
	upref(x) ;
	upref(xprime) ;
	BBigit low, up ;
	mbound(low,up,x,xprime) ;
	setb(lowtop(low),uptop(up)) ;
	}

static inline Bigit fast_sqrt(Bigit m)
{
	if (m >= (1<<10) )	return 1<<5 ;
	else if ( m >= (1<<8) )	return 1<<4 ;
	else			return m/2 ;
	}

void Prod::xnarrow(Bigit m)
{
	// Narrow the one that has the smallest range first.  In case
	// One of them has already been expanded this gives the largest
	// bound for the other.

	if ( x->range() < xprime->range() )  {
		x->narrow(fast_sqrt(m)) ;
		Bigit r = x->range() ; 
		if ( r <= 0 ) r = 1 ;
		xprime->narrow(m/r) ;
		}
	else {
		xprime->narrow(fast_sqrt(m)) ;
		Bigit r = xprime->range() ; 
		if ( r <= 0 ) r = 1 ;
		x->narrow(m/r) ;
		}
	BBigit low, up ;
	mbound(low,up,x,xprime) ;
	setb(lowtop(low),uptop(up)) ;
	}

void Prod::freeup()
{
	downref(x) ;
	downref(xprime) ;
	}

void Prod::do_expand()
{
	Withcarry r = cprod(x,xprime) ;
	i_am(r.carry,r.bval) ;
	}

	BBigit low, up ;

Withcarry cprod(Single* x1, Single* x2)
{
	BBigit low, up ;
	Bigit c ;

	mbound(low,up,x1,x2) ;
	if ( mutual_top(c,low,up) ) {
		return Withcarry(c, mk_prod1(-BB*c,x1,x2)) ;
		}

	// Expand x1 and x2 and try again
	x1->narrow(1);
	x2->narrow(1);
	mbound(low,up,x1,x2) ;
	if ( mutual_top(c,low,up) ) {
		return Withcarry(c, mk_prod1(-BB*c,x1,x2)) ;
		}

	// Still not enough, do more expansion. 

	BBigit n1 = x1->n() ;
	Bigit abs1 = (n1>=0 ? n1 : -n1 ) ;
	BBigit n2 = x2->n() ;
	Bigit abs2 = (n2>=0 ? n2 : -n2 ) ;
	BBigit plow = n1*n2 ;
	BBigit pup = plow ;

	x2->f()->narrow(((B-4)/2)/abs1)->bounds(low,up)  ;
	if ( n1 >= 0 ) {
		plow += lowtop(n1*low) ;
		pup += uptop(n1*up) ;
		}
	else {
		plow += lowtop(n1*up) ;
		pup += uptop(n1*low) ;
		}
	// Fudge of 4 is supplied because we have to worry about
	// more carries in from other terms.  The lower parts of the
	// mults implicit in the above, and from x1->f()*x2->f().
	// 4 is too big, but it doesn't matter.  There is more than
	// enough redundancy in the representation to deal with this.

	x1->f()->narrow((B-4-(pup-plow))/abs2)->bounds(low,up) ;
	if ( n2 >= 0 ) {
		plow += lowtop(n2*low) ;
		pup += uptop(n2*up) ;
		}
	else {
		plow += lowtop(n2*up) ;
		pup += uptop(n2*low) ;
		}

	if ( mutual_top(c,plow,pup) ) {
		return Withcarry(c, mk_prod1(-BB*c,x1,x2)) ;
		}

	// Can't get here, but compiler doesn't know that.
	assert(0) ;
	return Withcarry(0,mk_zero()) ;
	}

Single* mk_prod1(BBigit c, Single* x1, Single* x2)
{
	if ( x1->isz() ) return mk_single(c,mk_zero()) ;
	if ( x2->isz() ) return mk_single(c,mk_zero()) ;
	
	return new Prod1(c,x1,x2) ;
	}

Prod1::Prod1(BBigit c_arg, Single* x_arg, Single* xprime_arg)
{
	x = x_arg ;
	xprime = xprime_arg ;
	i = c_arg ;
	upref(x) ;
	upref(xprime) ;
	BBigit low, up ;
	mbound(low,up,x,xprime) ;
	setb(i+low,i+up) ;
	}

void Prod1::xnarrow(Bigit m) 
{
	// Narrow the one that is aleady narrowest first.
	// In many common cases this allow greater range in second narrowing

	Single** first ;
	Single** second ;
	Bigit first_range = fast_sqrt(m) ;
	if ( x->range() <= xprime->range() )  {
		first = &x ;
		second = &xprime ;
		}
	else {
		first = &xprime ;
		second = &x ;
		}

	(*first)->narrow(first_range) ;
	Bigit r = x->range() ; 
	if ( r <= 0 ) r = 1 ;
	(*second)->narrow(m/r) ;

	BBigit low, up ;
	mbound(low,up,x,xprime) ;
	if ( up-low > m ) {
		BBigit absr = xprime->n() ;

		if ( absr < 0 ) absr = -absr ;
		else if ( absr==0 ) absr = 1 ;

		x->f()->narrow((BB*first_range)/absr) ;

		absr = x->f()->range() ;
		if ( absr <= 0 ) absr = 1 ;
		xprime->f()->narrow((BB*m)/absr) ;
		mbound(low,up,x,xprime) ;
		}
	setb(i+low,i+up) ;
	} ;

void Prod1::freeup() 
{
	downref(x) ;
	downref(xprime) ;
	}

void Prod1::do_expand() 
{
	BBigit p0 = i + (BBigit)x->n() * (BBigit)xprime->n() ;
	Withcarry p1 = cmult(x->n(),xprime->f()) ;
	Withcarry p2 = cmult(xprime->n(),x->f()) ;
	Single* p3 = mk_prod(x->f(),xprime->f()) ;
	
	p0 += p1.carry + p2.carry ;
	
	Withcarry p12 = csum(p1.bval, p2.bval) ;
	p0 += p12.carry ;

	Withcarry p123 = csum(p12.bval,p3) ;
	p0 += p123.carry ;

	assert( p0 <= B && p0 >= -B ) ;
	i_am(p0,p123.bval) ;
	}

