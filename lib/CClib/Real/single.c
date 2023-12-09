
#include <real.h>
#include <exact.h>
#include <assert.h>
#include <string.h>

int expanded_count = 0 ;
int constructed_count = 0 ;
int deleted_count = 0 ;
int high_water_count = 0 ;

void debugnote() { }
long reftrap = 0 ;

static Zero* zero ;

static int dodelete = 1 ;
			// When zero, causes Singles that would otherwise
			// be deleted to be marked as deleted but not
			// really deleted.  This aids debugging of the
			// reference counts.

Single::Single() :
	expanded(0),
	lbound(-B),
	ubound(B),
	refcount(0)
{
	++constructed_count ;
	if ( constructed_count-deleted_count > high_water_count) {
		high_water_count = constructed_count-deleted_count ;
		}
	if ( reftrap == (long)this ) debugnote() ;
	}

Single::~Single() {
	assert(dodelete) ; // see downref 
	if ( expanded ) downref(x) ;
	else		freeup() ;
	}

static const char pfxletters[] =
	"0123456789abcdefghijklmnopqrstuvwxyzzABCDEFGHIJKLMNOPQRSTUVWXYZ" ;

void Single::expand()
{
	static int nesting ;
	if ( expanded ) return ;
	if ( debuglevel > 4 ) {
		char pfx[128] ;
		pfx[0] = pfxletters[nesting%sizeof(pfxletters)] ;
		for ( int n = 0 ; n < nesting ; ++n ) pfx[n+1] = ' ' ;
		strcpy(&pfx[nesting+1], "expanding ") ;
		show(pfx,"\n",3) ; 
		++nesting ;
		}

	do_expand() ;

	if ( debuglevel > 4 ) {
		char pfx[128] ;
		--nesting ;
		pfx[0] = pfxletters[nesting%sizeof(pfxletters)] ;
		for ( int n = 0 ; n < nesting ; ++n ) pfx[n+1] = ' ' ;
		strcpy(&pfx[nesting+1], "expanded  ") ;
		show(pfx,"\n",3) ; 
		}
	}

void Single::i_am(Bigit n, Single* f) 
{
	assert(n<= B && n>=-B ) ;
	assert(lbound <= n && n <= ubound ) ;
	assert(!expanded) ;
	++expanded_count ;
	upref(f) ;
	freeup() ;
	i = n ;
	x = f ? f : zero ;
	expanded = 1 ;
	if ( i==B ) {
		// Prerequistes for i_am imply that fraction must be
		// non-positive.  It would be nice to check that here.
		// But it isn't easy.
		i = B-1 ;
		Single* newx = mk_adjust(B,x) ;
		upref(newx) ;
		downref(x) ;
		x = newx ;
		}
	else if ( i==-B ) {
		// Similar to leading==B, but fraction must be at least
		// zero.

		i = -B+1 ;
		Single* newx = mk_adjust(-B,x) ;
		upref(newx) ;
		downref(x) ;
		x = newx ;
		}
	lbound = ubound = i ;
	Bigit flow, fup ;
	x->bounds(flow,fup) ;
	if ( fup > 0 ) ++ubound ;
	if ( flow < 0 ) --lbound ;
	}

void Single::setb(Bigit low, Bigit up) 
{
	assert(low<=up) ;
	if ( low > lbound ) lbound = low ;
	if ( up < ubound ) ubound = up ;
	}

void Single::do_expand() { assert(0) ; }

Shift Single::leadingz()
{
	if ( isx() && i==0 ) return x->leadingz() + 1 ;
	return 0 ;
	}

void Single::freeup() {
	assert(0) ;
	}

Single* Single::remaining(Shift n)
{
	assert(n>=0) ;
	if ( n==0 ) return this ;
	else {
		expand() ;
		return  x->f(n-1) ;
		}
	}

void Single::bounds(Bigit& low, Bigit& upper)
{

	low = lbound ;
	upper = ubound ;
	}

void Single::bounds(BBigit& low, BBigit& upper)
{

	low = lbound ;
	upper = ubound ;
	}

Bigit Single::range()
{
	Bigit lower, upper ;
	bounds(lower,upper);
	return upper - lower ;
	}

int Single::hibit()
{
	if ( isx() ) {
		return i>>(BITSINBIGIT-1) ; 
		}
	Bigit low, up ;
	narrow(B-1)->bounds(low,up) ;

	if ( low > 0 )		return 1 ;
	else if ( up < 0 )	return -1 ;
	else			return 0 ;
	}

Bigit Single::n() {
	assert(refcount>=0) ;
	if ( isx() ) return i ;
	else if ( leadingz() > 0 ) return 0 ;

	expand() ;
	return i ;
	}

Single* Single::f(Shift s) {
	assert(refcount>=0) ;
	if (s==0) {
		return this ;
		}
	else if ( isx() ) {
		return x->f(s-1) ;
		}

	return remaining(s) ;
	}

Shift Single::s() 
{
	if ( isz() ) return Bigshift ;
	if ( isx() ) {
		if ( i )	return 0 ;
		else		return x->s() + 1 ;
		}
	return leadingz() ;
	}

int Single::isz()
{
	assert(refcount >= 0) ;
	if ( lbound > 0 || ubound < 0 ) return 0 ;

	if ( expanded ) {
		return i==0 && ( x==this || x->isz() ) ;
		}
	
	return 0 ;
	}

void Single::xnarrow(Bigit)
{
	}

Single* Single::narrow(Bigit n) 
{
	if ( n >= 2 && n<(ubound-lbound) ) xnarrow(n) ;
	if ( !isx() && n<(ubound-lbound) ) {
		expand() ;
		}
	return this ;
	}

int Single::whatsign(int howmany)
{
	if ( isz() ) return 0 ;
	Bigit low,up ;
	bounds(low,up) ;

	if ( low > 0 ) return 1 ;
	else if ( up < 0 ) return -1 ;

	if ( howmany<=0 ) return 0 ;
	Bigit i = n() ;
	if ( i < 0 ) return -1 ;
	else if ( i > 0 ) return 1 ;
	else return f()->whatsign(howmany-1) ;
	}


static int cround_fraction(Single* x, Round_dir dir,Shift p )
{
	switch(dir) {
		case round_pos : {
			if(x->whatsign(p) > 0 ) return 1 ;
			} break ;
		case round_neg : {
			if(x->whatsign(p) < 0 ) return -1 ;
			} break ;
		case round_near : {
			Bigit i = x->n() ;
			if ( i > B/2 ) return 1 ;
			else if ( i < -B/2 ) return -1 ;
			else if ( i==B/2 && x->f()->whatsign(p-1)>0) {
				return 1;
				}
			else if ( i==-B/2 && x->f()->f()->whatsign(p-1)<0 ) {
				return -1 ;
				}
			} break ;
		case round_up : { 
			int sg = x->whatsign(p) ;
			if ( sg > 0 )	   return 1 ;
			else if ( sg < 0 ) return -1 ;
			} break ;
		case round_down : {  // do nothing
			} break ;
		} /* end switch */

	return 0 ;
	}

Withcarry cround(Single* x, Shift r, Round_dir dir, Shift p)
{
	if ( x->isz() ) return Withcarry(0,x) ;
	

	if ( r==0 ) {
		return Withcarry(cround_fraction(x,dir,p), mk_zero() ) ;
		}
	
	assert ( r > 0 ) ;
	Bigit m = x->n() ;

	if ( dir==round_up ) {
		if ( m > 0 )	  dir = round_pos ;
		else if ( m < 0 ) dir = round_neg ;
		}
	else if ( dir==round_down ) {
		if ( m > 0 ) 	  dir = round_neg ;
		else if ( m < 0 ) dir = round_pos ;
		}

	Withcarry rest = cround(x->f(),r-1,dir,p) ;

	m += rest.carry ;
	Single* rem = rest.bval ;
	if (rem==x->f() && m==x->n() ) {
		return Withcarry(0,x) ;
		}
	else if ( m==B ) {
		return Withcarry(1,mk_single(0,rem)) ;
		}
	else if ( m==-B ) {
		return Withcarry(-1,mk_single(0,rem)) ;
		}
	else {
		return Withcarry(0,mk_single(m,rem)) ;
		}
	}
 
void upref(Single* s)
{
	if ( reftrap == (long)s ) debugnote() ;
	++s->refcount ;
	}

void downref(Single* s) 
{
	if ( reftrap == (long)s ) debugnote() ;
	if ( --s->refcount <= 0 ) {
		assert(s->refcount==0) ;
		++deleted_count ;

		s->refcount = -100 ; // mark as "freed"
					// if we really delete as below
					// Then this will still catch
					// quick rereferences.

		if (dodelete)	delete s ;
		else {
			// Don't delete, but do actions that destructor
			// would do.  This is to ease debugging.  In case
			// reference counting isn't working it is easier to
			// figure out what is happening by marking the
			// Single as freed, but not allowing it to
			// be reallocated.
		
			if ( s->isx() ) downref(s->x) ;
			else		s->freeup() ;
			}

		}
	}

Single*	mk_zero()
{
	return zero ;
	}

Zero::Zero() {
	setb(0,0) ;
	i_am(0,this) ;
	}

void	Zero::do_expand() { i_am(0,this) ; }
Shift	Zero::leadingz() { return Bigshift ; }
Single*	Zero::remaining(Shift) { return this ; }
void	Zero::freeup() { } ;

Explicit::Explicit(Bigit n, Single* f) { i_am(n,f) ; }
void Explicit::freeup() { } 


static const int precomp_offset = 16 ;
static Single* precomp[2*precomp_offset+1] ;

Single* mk_single( Bigit n, Single* f)
{
	if ( !f ) f = zero ;
	if ( n >= -precomp_offset && n <= precomp_offset && f->isz() ) {
		return precomp[n+precomp_offset] ;
		}
	return new Explicit(n,f) ;
	}

Single_init::Single_init() {
	// This constructor will be called once for each time real.h is
	// #included.  The following causes it to return immediatly 
	// except the first time it is called.

	++initcount ;
	if ( initcount > 1 ) return ;

	zero = new Zero ;
	upref(zero) ;
	for ( int n = -precomp_offset ; n <= precomp_offset  ; ++n ) {
		int x = n+precomp_offset ;
		precomp[x] = new Explicit(n,zero) ;
		upref(precomp[x]) ;
		}
	precomp[precomp_offset] = zero ;
	}

Single_init::~Single_init() {
	--initcount ;
	if ( initcount > 0 ) return ;
	
	// No need to delete zero.
	}

// Stick this in for calling from debugger.

void dbp(long s) {
	((Single*)s)->show(0,"\n") ;
	}
