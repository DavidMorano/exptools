

#ifndef EXACT_H
#define EXACT_H

#include <bigit.h>

class Real ;
class Single ;
class Series ;

overload upref ;
overload downref ;

// Some functions compute values with carries.  Because
// This needs two results I declare a class to hold the two values.

class Withcarry {
public:
	// Used to represent the value carry*B + bval
	Bigit		carry ;
	Single* 	bval ;
	Withcarry(Bigit c, Single* b) : carry(c), bval(b) { }
	Withcarry() { } 
} ;

class Single {
private:
	int		refcount ;
	Bigit		lbound ;
	Bigit		ubound ;
				// lower and upper bounds.
	short		expanded ;
				// If expanded is non-zero
				// value is leading+fraction^-1 
protected:
	// x and i can be used by derived classes for whatever
	// purpose they want before expansion.  (There should
	// be a way to enforce this, but I it isn't obvious)
	Single*		x ;	// used in expanded value to hold
				// fraction
	Bigit		i ;	// used in expanded value to hold 
				// leading Bigit
protected:
			Single() ;

	void		expand() ; 
	void		i_am(Bigit,Single*) ;
				// Used by expanders to set value
	void 		setb(Bigit low, Bigit up) ;
				// Record known bounds

	virtual void	do_expand() ;
	virtual Shift	leadingz() ;
	virtual Single*	remaining(Shift) ;
	virtual	void	dbout() ;	// prints on cdebug

	friend void	upref(Single*) ;
	friend void	downref(Single*) ;
					// bump reference count. Friends
					// rather than members because
					// I don't think you can delete
					// "this".
			Single::~Single() ;
	virtual	void 	freeup() ;
				// called to downbump any pointers stored
				// by derived class. Called by i_am
				// during expansion, and by ~Single
				// if there hasn't been an expansion.
	virtual void	xnarrow(Bigit n) ;	
public:
	void		bounds(Bigit& lower, Bigit& upper) ;
	void		bounds(BBigit& lower, BBigit& upper) ;
	Bigit		range() ;	// upper-lower 
	Bigit		n() ;		// Leading Bigit
	int		hibit();	// Leading bit.
	Single*		f(Shift s=1) ;	// Fraction part
	Shift		s() ;		// Number of known leading zero 
					// Bigits.

	int		isx() { return expanded ; }

	int		isz() ;
	Single*		narrow(Bigit n) ;



	int		whatsign(int n) ;
				// -1, 0 or 1 depending on whether
				// value is less than, equal, or greater
				// than 0.  Where may report 0 after
				// looking at n bits.


	void		show(char* pfx=0, char* sfx=0, int what=1) ;
				// Prints on cdebug, prefixed by pfx
				// suffixed by sfx.
				// Meaning of what bits
				//	1 = print expression
				//	2 = print address
	static int	debuglevel ;

	virtual Withcarry
			times(Bigit m) ;
private:
			Single(Single&) ;	// illegal
	void		operator=(Single&) ; 	// illegal
} ;

// The following combine Singles in some way.  They generally
// construct new data structures. Some might have been
// done as operators, but I prefered to use "mk" uniformly to avoid
// confusion.

// The following construct Singles (or return pointers to old
// data structures) without constraints except those implied by
// their types.  A Bigit must be between -B+1 and B-1.

Single* mk_single(Bigit m, Single* x) ;			// m+x^-1
Single* mk_shift(Single* x, Shift s) ;			// x^-s 
Single* mk_zero() ;					// 0
Single* mk_minus(Single* x) ;				// -x 
Single* mk_abs(Single* x) ;				// |x|
Single* mk_prod(Single* x1, Single* x2) ;		// x1*x2^-1

// The following construct Singles in ways that might not
// result in a value in range.  It is the callers obligation
// to ensure that the value is in range.

Single* mk_adjust(BBigit c, Single* x) ;		/* c+x */
Single* mk_sum(BBigit c, Single* x1, Single* x2) ;	/* c+x1+x2 */
Single* mk_mult(BBigit c, Bigit m, Single* x) ;		/* c+m*x */
Single* mk_div(Single* x1, Single* x2) ;		/* x1/x2 */
Single* mk_quot(BBigit c, Single* x1, Single* x2) ;	/* (c+x1)/x2 */
Single* mk_prod1(BBigit c, Single* x1, Single* x2) ; 	/* c+x1*x2 */

Single* mk_series(Single* x, Shift s, Series* t) ;	/* x + T^s */

Withcarry csum(Single* x1, Single* x2) ;	// x1+x2 
Withcarry cmult(Bigit m, Single* x) ;		// m*x 
Withcarry cprod(Single* x1, Single* x2) ;	// x1*x2

enum Round_dir ;

Withcarry cround(Single* x, Shift r, Round_dir dir, Shift p) ;
	// round(x,r,d,p) will round x after r Bigits.
	// Rounding occurs in direction dir as determined by looking
	// at up to p more Bigits.

	// If f is already appropriate, will return it.  Otherwise
	// constructs and returns new structure.
	// Carry is unlikely when r>0, but barely possible.
	// r==0 is the workhorse which rounds a "fraction".  carry
	// will be set, and bval will always be 0.

class Explicit : public Single {
	virtual	void 	freeup() ;
public :
			Explicit(Bigit n, Single* f) ;
} ;

class Zero : public Single {
public:
			Zero() ;
private:
	virtual void	do_expand() ;
	virtual Shift	leadingz() ;
	virtual Single*	remaining(Shift) ;
	virtual	void	dbout() ;
	virtual	void 	freeup() ;
} ;

class Shifted : public Single  {
public:
			Shifted(Single* x, Shift rs) ;
private:
	Shift		rightshift ;

	virtual void	do_expand() ;
	virtual Shift	leadingz() ;
	virtual Single*	remaining(Shift) ;
	virtual	void	dbout() ;
	virtual	void 	freeup() ;
};
	
class Minus : public Single {
public :
			Minus(Single* x) ;
private:
	
	// Value is -x

	virtual void	do_expand() ;
	virtual	void	dbout() ;
	virtual	void 	freeup() ;
	virtual void	xnarrow(Bigit m) ;
} ;
	
class Abs : public Single {
public :
			Abs(Single* x) ;
private:
	
	// Value is |x|

	virtual void	do_expand() ;
	virtual	void	dbout() ;
	virtual	void 	freeup() ;
	virtual void	xnarrow(Bigit m) ;
} ;

class Sum : public Single {
public:
			Sum(BBigit i, Single* x, Single* xprime) ;
			// Value is i+x+xprime

private:
	BBigit		i ;
	Single*		xprime ;

	virtual void	do_expand() ;
	virtual	void	dbout() ;
	virtual	void 	freeup() ;
	virtual void	xnarrow(Bigit) ;
} ;

class Mult : public Single {
public:
			Mult(BBigit i, Bigit m, Single* x) ;
			// Value is i+m*x
private:
	BBigit		i ;
	Bigit		m ;
	
	virtual void	do_expand() ;
	virtual	void	dbout() ;
	virtual	void 	freeup() ;
	virtual void	xnarrow(Bigit) ;
} ;


class Prod : public Single {
public:
			Prod(Single* x, Single* xprime) ;
			// Value is x*xprime^-1
private:
	Single*		xprime ;
	
	virtual void	do_expand() ;
	virtual	void	dbout() ;
	virtual	void 	freeup() ;
	virtual void	xnarrow(Bigit) ;
} ;

class Prod1 : public Single {
public:
			Prod1(BBigit i, Single* x, Single* xprime) ;
			// value is i+x*xprime
private:
	BBigit		i ;
	Single*		xprime;
	
	virtual void	do_expand() ;
	virtual	void	dbout() ;
	virtual	void 	freeup() ;
	virtual void	xnarrow(Bigit) ;
};

class Quot : public Single {
public:
			Quot(BBigit i, Single* x, Single* xden ) ;
			// Value is (i + x)/xden
			// xden satisfies xden->n() > 8 
			// (which implies xden!=0 ) 

private:
	BBigit		i ;
	Single*		xden ;
	
	virtual void	do_expand() ;
	virtual	void	dbout() ;
	virtual	void 	freeup() ;
	virtual void	xnarrow(Bigit) ;

	Withcarry 	times(Bigit m) ;
};

class Inf_sum : public Single {
public:
			Inf_sum( Single* x, Shift e, Series* s) ;
			// Value is x + S^-e 
			// where S is remaining sum in Series.
private:
	Series*		terms ;
	Shift		exp ;

	virtual void	do_expand() ;
	virtual	void	dbout() ;
	virtual	void 	freeup() ;
	virtual void	xnarrow(Bigit) ;
	
} ;

class Single_init {
	static int	initcount ;
    public:
			Single_init() ;
			~Single_init() ;
} single_initializer ;


#endif /* multiple include protection */
