
#include <real.h>
#include <iostream.h>
#include <strstream.h>
#include <ctype.h>
#include <assert.h>
#include <exact.h>


static Real ten = 10 ;
static Real powten(int e)
{
	return pow(ten,e) ;
	}

iostream& operator<<(iostream& ios, Real x)
{
	// This code is ridiculously inefficient.  But it
	// will do for the time being. 

	int p = ios.precision() ;
	if ( p<=0 ) p=6 ;
	Real blow = powten(p-1) ;
	Real bup = 10*blow ;


	int e = 0 ;
	int sg = x.sign(io_plimit) ;
	if ( sg < 0 ) {
		x = -x ;
		}
	else if ( sg == 0 ) {
		if (x.obvious_zero()) return ios << "0" ;
		Exp_t e ;
		long i ;
		x.split(e,i,2,rel_plimit(0)) ;

		if ( e > 0 )		return ios << "0E" << (e+2)/3 ;
		else if ( e < 0 )	return ios << "0E" << e/4 ;
		else 			return ios << "0E1" ;
		}

	Real half = Real(1)>>1 ;
	Plimit bits = abs_plimit(4*p+1) ;
	while ( bup <= x.round(round_near,bits) ) { 
		x=x/10 ;
		++e ;
		}
	while ( blow > x.round(round_near,bits) ) {
		x = 10*x ;
		--e ;
		}
	x = x.round(round_near,bits) ;
	assert( bup.gt(x,bits) && !blow.gt(x,bits) ) ;

	if ( sg < 0 ) ios << "-" ;
	ios << "." ;
	while ( p >= 1 ) {
		Real d = (x/blow).round(round_down,bits) ;
		int digit = (int)(double)d ;
		assert(digit<10 && digit>=0) ;
		ios << digit  ;
		x = x-d*blow ;
		blow = blow/10 ;
		--p ;
		++e ;
		}
	
	return ios << "E" << e ;
	}

iostream& operator>>(iostream& ios, Real& x) 
{
	ios.pushfmt() ;
	char firstc ;
	ios.skip(1) ;
	ios >> firstc ;
	ios.skip(0) ;
	char digit ;
	int sg  = 1 ;
	int ptseen = 0 ;
	int digitseen = 0 ;
	int e = 0 ;
	if ( firstc == '+' ) {
		ios >> digit ;
		}
	else if ( firstc == '-' ) {
		sg = -1 ;
		ios >> digit ;
		}
	else if ( firstc == '.' ) {
		ptseen = 1 ;
		ios >>digit ;
		}
	else {
		digit = firstc;
		}

	x = 0 ;
	while(ios && isdigit(digit)) {
		digitseen = 1 ;
		if ( ptseen ) --e ;
		x = 10*x + Real(sg*(digit-'0')) ;
		ios >> digit ;
		if ( ios && digit=='.' && !ptseen) {
			ptseen = 1 ;
			ios >> digit ;
			}
		}

	if ( digit=='e' || digit=='E' ) {
		int exp ;
		ios >> exp ;
		e += exp ;
		}
	else {
		ios.putback(digit) ;
		}

	// Don't multiply by powten(-n) because that creates
	// unneccessary infinite expansions.

	//if ( e >= 0 )	x = x*powten(e) ;
	//else		x = x/powten(-e) ;
x = x*powten(e);
	ios.popfmt() ;
	if ( !digitseen ) ios.clear(ios.rdstate()|_bad) ;
	return ios ;
	}

void Real::show(int force,char* pfx, char* sfx)
{
	if ( force < 0 ) force = 256 ; // arbitrary large number
	Single* x = mantissa ;
	while ( force-- > 0 ) {
		Bigit n = x->n() ;
		x = x->f() ;
		}
	cdebug << pfx
		<< "(" ; mantissa->show() ; cdebug << ")^" << exp
		<< sfx  ;
	cdebug.flush() ;
	}

Real ator(char* s) {
	Real r ;
	strstream(s,input) >> r ;
	return r ;
	}

Real ator(unsigned char* s) {
	Real r ;
	strstream(s,input) >> r ;
	return r ;
	}
