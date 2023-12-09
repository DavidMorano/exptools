

#include <assert.h>
#include <real.h>
#include <exact.h>

#include <stream.h>
#ifndef cdebug
	// stuff for backward compatibility with old stream package
#	define cdebug cerr
	typedef ostream iostream ;
	inline static long ptr(void* p) { return (long)p ; }
#else
	inline static void* ptr(void* p) { return p ; }
#endif

static int nesting = 0 ;
static nestlimit = 3 ;

void Single::show(char* pfx, char* sfx, int what)
{
	if ( pfx ) cdebug << pfx ;

	if ( what&2 ) {
		cdebug << "at " << (void*)this ;
		}
	if ( (what&3) == 3 ) cdebug << "=" ; 

	if ( nesting > nestlimit ) {
		Bigit low, up ;
		bounds(low,up) ;
		cdebug << "[" << low << ".." << up << "]" ;
		} 
	else if ( isx() ) {
 		Single::dbout() ;
		}
	else {
		++nesting ;
		dbout() ;
		--nesting ;
		}

	if ( sfx ) {
		cdebug << sfx ;
		cdebug.flush() ;
		}
	}

static iostream& operator<<(iostream& ios, Single& x) 
{
	assert( &ios == &cdebug ) ;
	x.show() ;
	return cdebug ;
	}

void Single::dbout()
{
	if ( isx() ) {
		if ( !x || x->isz() ) {
			cdebug << i ;
			}
		else {
			cdebug << i << "++" << *x ; 
			}
		}
	else {
		cdebug << "UNEXPANDED" ;
		}

	}

void Zero::dbout()
{
	cdebug << "0" ;
	}

void Shifted::dbout()
{
	cdebug << "((" << *x <<  ")>>" << rightshift << ")" ;
	}

void Minus::dbout() 
{
	cdebug << "-(" << *x <<  ")" ;
	}

void Abs::dbout() 
{
	cdebug << "abs(" << *x <<  ")" ;
	}

void Sum::dbout()
{
	if(i) {
		cdebug << "(" << i << "+(" << *x << ")+(" << *xprime << "))" ;
		}
	else {
		cdebug << "((" << *x << ")+(" << *xprime << "))" ;
		}
	}


void Mult::dbout()
{
	cdebug << "(" << i << "+" << m  << "*(" << *x << "))" ;
	}

void Prod::dbout()
{
	cdebug << "((" << *x << ")*(" << *xprime << ")>>1)" ;
	}

void Prod1::dbout()
{
	cdebug << "(" << i << "+(" << *x << ")*(" << *xprime << "))" ;
	}

void Quot::dbout()
{
	cdebug << "((" << i << "+(" << *x << "))/(" << *xden << "))" ;
	}


void Inf_sum::dbout()
{
	cdebug << "((" << *x << ")+" ;
	this->terms->show( "(", ")" ) ;
	cdebug << "))" ;
	}
