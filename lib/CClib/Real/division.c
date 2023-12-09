
#include <exact.h>
#include <assert.h>

Single* mk_div(Single* x1, Single* x2)
{
	BBigit n2 = x2->n() ;
	assert ( n2 ) ;
	if ( x1->isz() ) return mk_zero() ;
	if(n2==1 && x2->f()->isz() ) return x1 ;
	if (n2==-1 && x2->f()->isz() ) return mk_minus(x1) ;

	Shift xs = x1->s() ;
	x1 = x1->f(xs) ;

	Bigit norm ;
	n2 = BB*n2 + x2->f()->n() ;
	if ( n2 > 0 ) {
		norm = (BB*BB/2+n2-1)/n2 ;
		}
	else {
		norm = (-BB*BB/2+n2+1)/(-n2) ;
		}
	Withcarry num = cmult(norm,x1) ;
	Withcarry den = cmult(norm,x2) ;
	if ( den.carry > 0 ) {
		den = Withcarry(den.carry-1, mk_adjust(B,den.bval)) ;
		}
	else if ( den.carry < 0 ) {
		den = Withcarry(den.carry+1, mk_adjust(-B,den.bval)) ;
		}
	assert(den.carry==0) ;
	assert(den.bval->n()>=B/2 ) ;
	return mk_shift( mk_quot(num.carry*BB, num.bval, den.bval), xs) ;
	}

Single* mk_quot(BBigit c, Single* x1, Single* x2)
{
	if ( c==0 && x1->isz() ) return mk_zero() ;
	
	return new Quot(c,x1,x2) ;
	}

static void try(Bigit& low, Bigit &up, Bigit t)
{
	if ( t+1 > up ) up = t+1 ;
	if ( t-1 < low ) low = t-1 ;
	}

static void qbound (Bigit& low, Bigit& up, BBigit c, Single* x, Single* d)
{
	Bigit xlow, xup, dlow, dup ;
	x->bounds(xlow,xup) ; 
	d->bounds(dlow,dup) ;
	
	low = B ;
	up = -B ;
	try(low, up, (c+xlow)/dlow ) ;
	try(low, up, (c+xlow)/dup ) ;
	try(low, up, (c+xup)/dlow ) ;
	try(low, up, (c+xup)/dup ) ;
	assert ( low <= up ) ;
	}
 
Quot::Quot(BBigit c_arg, Single* x_arg, Single* xden_arg)
{
	i = c_arg ;
	x = x_arg ;
	xden = xden_arg ;
	upref(x) ;
	upref(xden) ;
	assert(xden->n() >= 8 ) ;
	Bigit low, up ;
	qbound(low,up,i,x,xden) ;
	setb(low,up) ;	
	}

void Quot::xnarrow(Bigit m)
{
	Bigit d = xden->n() ;
	assert(d>8) ;
	x->narrow(m/(d+1)) ;
	Bigit low, up ;
	qbound(low,up,i,x,xden) ;
	setb(low,up) ;
	}
	
void Quot::freeup()
{
	downref(x) ;
	downref(xden) ;
	}

void Quot::do_expand()
{
	BBigit n1 = x->n() ;
	BBigit n2 = xden->n() ;
	Single* f1 = x->f() ;
	Single* f2 = xden->f() ;

	BBigit num = 4*(i + n1)  ;
	if ( num > 0 )	num += 2*n2 ;
	else		num -= 2*n2 ;

	BBigit den = 4*n2 + top(4*f2->n()) ;
	BBigit q = num/den ;
	assert ( q < BB && q > -BB ) ;
	
	BBigit forward = (i + n1 - (q*n2)) ;
	Withcarry qf = cmult(-q,f2) ;
	forward += qf.carry ; 
	Withcarry r = csum(f1,qf.bval) ;
	forward += r.carry ;

	assert ( forward < n2 && forward > -n2 ) ;
	i_am(q, mk_quot(BB*forward,r.bval,xden) ) ;
	}

Withcarry Quot::times(Bigit m)
{
	return this->Single::times(m) ;
	}

//Withcarry Quot::times(Bigit m)
//{
//	BBigit mm = m ;
//	Single* x_orig = x ; upref(x_orig) ;
//	Single* d_orig = xden ; upref(d_orig) ;
//	BBigit i_orig = i ;
//
//	expand() ; // force expansion to avoid recursive call
//	Withcarry qc = cmult(m,this) ; upref(qc.bval) ;
//
//	BBigit q = qc.carry ;
//	downref(qc.bval) ;
//	// q is the desired high order Bigit (carry) of the product.
//	// We ignore qc.bval.  (Maybe I could have computed q directly,
//	// but it is delicate and I don't want to duplicate the
//	// code in expand())
//
//	// Thus the low order (bval) part is
//	//	m*(i+x)/d - q*B == ( m*(i+x) - q*d*B ) / d
//	
//	// The numerator will be accumulated in 3 parts.
//	// The value being accumulated is represented by
//	// Accum =  accum1*B + accum0 + accumx.bval ;
//
//	BBigit accum1 = 0 ;
//	BBigit accum0 = 0 ;
//	Withcarry accumx ;
//		// accumx.carry will always be kept at 0
//
//	accum0 += bot(i_orig) * mm ;
//	accum1 += top(accum0) ; accum0 = bot(accum0) ;
//	accum1 += top(i_orig) * mm ;
//
//	// Accum now contains m*i
//
//	accumx = cmult(m,x_orig) ;
//	accum1 += accumx.carry ; accumx.carry = 0 ;
//
//	// Accum now contains m*i + m*x ;
//
//	Withcarry qd = cmult(-q,d_orig) ;
//	
//	accum1 += qd.carry*B + qd.bval->n() ;
//	accumx = csum(qd.bval->f(),accumx.bval) ;
// 	accum1 += accumx.carry ; accumx.carry = 0 ;
//
//	// Finally Accum contains m*i + m*x + d*q*B
//
//	assert ( accum1 < B && accum1 > -B ) ;
//
//	Single* r = mk_quot(B*accum1+accum0,accumx.bval,d_orig) ;
//
//	downref(x_orig) ; downref(d_orig) ; 
//
//	return Withcarry(Bigit(q),r) ;
//
//	} ;
