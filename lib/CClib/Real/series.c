
#include <real.h>
#include <exact.h>
#include <assert.h>

Series::Series() : embedded(0)  { }
Series::~Series() { }

Real Series::embed() 
{
	assert (!embedded) ;
	embedded = 1 ; 

	Real total = bound() ;
	Single* s = mk_series(mk_zero(),-total.exp,this) ;
	return Real(total.exp,s) ;
	} 

// Dummy virtuals

Real Series::bound() { return Real(0) ; }
Real Series::next() { return Real(0) ; }

void Series::step()  { } 

Single* mk_series(Single* a,Shift e,Series* s)
{
	return new Inf_sum(a,e,s) ;
	}

Inf_sum::Inf_sum(Single* x_arg, Shift e, Series* s)  :
	exp(e),
	terms(s)
{
	x = x_arg ;
	upref(x) ;
	// Should we use "total" to get good setb ranges?
	}

Real realB = B ;
Real minus_realB = -B ;

static void e_split(Real &r, Exp_t &e, Single* &s, Exp_t rel) 
{
	// Split r^e into Exp_t part and Bigit part, making sure
	// That we have normalized sufficiently to gurantee
	// that we know if e can be made less than 0.

	r.split(e,s,0) ;
	if ( e > rel-1 )  r.split(e,s,(int)(e-rel+2)) ;
	e -= rel ; 
	}

void Inf_sum::xnarrow(Bigit) 
{
	// Should do something here, but for the moment
	// just returning is correct if not efficient.
	}

void Inf_sum::do_expand()
{
	while( 1 ) {
		Bigit af_low, af_up ;
		x->f()->narrow(0)->bounds(af_low,af_up) ;
		Exp_t rem_exp ;
		Single* rem_mantissa ;
		Real rem = terms->bound() ;
		e_split(rem,rem_exp,rem_mantissa,-exp) ;
		assert(rem_exp <= 0 ) ;
		if ( rem_mantissa->isz() ) {
			i_am(x->n(),x->f()) ;
			return ;
			}

		BBigit rem_n ;
		if ( rem_exp == 0 )	  rem_n = 2*B+1 ;
		else if ( rem_exp == -1 ) rem_n = rem_mantissa->n() + 1 ;
		else 			  rem_n = 1 ;
		
		assert(rem_n>=0) ;

		if (  af_up+rem_n <= B && af_low-rem_n >= -B  ) {
			Single* s = mk_series(x->f(),exp+1,terms);
			terms = 0 ; // So it doesn't get deleted.
			i_am(x->n(),s);
			return ;
			}
	
		Exp_t ts ;
		Single* t ;
		e_split(terms->next(), ts, t, -exp ) ;
		upref(t) ;	// This might be only reference after
				// terms->step()
		terms->step() ;
		if ( t->isz() ) ts = 0 ;
		assert (ts<=0) ;
		Single* newx = mk_sum(0,x,mk_shift(t,-ts) ) ;
		upref(newx) ;
		downref(t) ;
		downref(x) ;
		x = newx ;
		}
	}


void Inf_sum::freeup()
{
	downref(x) ;
	if ( terms ) {
		delete terms ;
		}
	}
