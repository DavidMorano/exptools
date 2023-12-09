/*
 *     C++ implementation of arbitrary precision integers.
 *     Version - 1 November 1992
 *
 *     Emden R. Gansner
 *     AT&T Bell Laboratories
 *     ulysses!erg
 *
 */

#ifndef INT_H
#define INT_H
#include <stddef.h>
#include <iostream.h>

typedef void (*OutFn)(char);

class INT_REP {

	short	refcnt;				// Reference count.
	long	*wt;				// First unused space.
	long	*beg;				// Start of allocated memory.
	long	*last;				// End of allocated memory.
                
	INT_REP (INT_REP *); 		// Duplicate INT_REP.

	void More ();				// Realloc.
	void Zero();				// Zero out everything.
	void Print(ostream &);		// Print using ostream.
	void Print(OutFn, int);		// Print using user supplied fn.
	void Prt();					// Print internal representation.
	void Chsign ();				// Change sign.
	void StripZero();			// Strip redundant zeros.
	void StripMinus();			// Strip redundant -1's.
	int  Twos();				

	int  Length()				{ return (wt-beg); }
	int  isNegative()			{ return ((wt > beg) && (*(wt-1) < 0));  }
	int  isZero ()				{ return (wt == beg); }
	int  isNonzero ()			{ return (wt != beg); }
	int  isOdd ()				{ return (*beg & 0x1); }	// Assuming positive.
	int  isEven ()				{ return (!(*beg & 0x1)); }	// Assuming positive.
	void SetZero ()				{ wt = beg; }
	void Putc(long c)			{ if (wt==last) More(); *wt++ = c; }
	void Alterc(int c, long *p)	{ if (p == last) More(); *p++ = c; if (p > wt) wt = p; }
	int  equalsOne()			{ return ((wt == beg+1) && (*(beg) == 1)); }
	void MakeZero()				{ beg = new long[0]; wt = last = beg; }

                  
	void	FillDec(char *, char *);
	void	FillHex(char *, char *);
	void	FillOct(char *, char *);
	void	FillLong(unsigned long);

	INT_REP *PutDec();
	INT_REP *PutHex();
	INT_REP *PutOct();

	int		Store(char *, int, int);

	int     Comp(INT_REP *);
	long    Trunc(int &);
	INT_REP *Add(INT_REP *);
	INT_REP *Sub(INT_REP *);
	INT_REP *Mult(INT_REP *);
	INT_REP *DivMod(INT_REP *, int);
	INT_REP *Div(INT_REP *b)		{ return DivMod(b,0); }
	INT_REP *Mod(INT_REP *b)		{ return DivMod(b,1); }
	INT_REP *Exp(INT_REP *b);
	INT_REP *GCD(INT_REP *b);

	INT_REP *And(INT_REP *);
	INT_REP *Or(INT_REP *);
	INT_REP *Xor(INT_REP *);
	INT_REP *Not();
	INT_REP *LeftShift(long);
	INT_REP *RightShift(long);
	INT_REP *LeftShift(INT_REP *);
	INT_REP *RightShift(INT_REP *);
    
        void *operator new (size_t);
        void operator delete (void*);
  public :

	INT_REP (int, int = 1);		// Create INT_REP of specified size.
	INT_REP (long);				// Create INT_REP of long.
	INT_REP (char *); 			// Create INT_REP from ascii representation.
	~INT_REP (); 

	static void IRMorehd ();
	friend class Int;
	friend INT_REP *IRAllocRep ();
	friend Int operator >> (Int b, long a);
	friend Int operator << (Int b, long a);
};
	
extern INT_REP ZeroRep;

class Int {
	INT_REP *rep;

	Int Reset (INT_REP *newrep)
	{
		rep->refcnt--;
		if (rep->refcnt == 0)
			delete rep;
		rep = newrep;
		rep->refcnt++;
		return (*this);
	}

	void Print(ostream &i)		// Print decimal representation on ostream.
		{ rep->Print(i); }

  public :

	Int(long i)					// Initialized to i.
		{ rep = new INT_REP (i); if (rep) rep->refcnt++; }
	Int ()						// Initialized to zero.
		{ rep = &ZeroRep; rep->refcnt++;          }
	Int (INT_REP *r)			// For return values from INT_REP operations.
		{ rep = r;	if(r) r->refcnt++;	}
	Int (Int &a)				// For assignment.
		{ rep = a.rep; if(rep) rep->refcnt++; }
	Int (char *s)				// Character representation, in decimal, octal or hex.
		{ rep = new INT_REP (s); if(rep) rep->refcnt++; }
	~Int ()
		{ rep->refcnt--; if(rep->refcnt == 0) delete rep; }
                                
		// Assignment operators.
	Int operator= (Int a)				{ return (Reset (a.rep)); }
	Int operator+= (Int a)				{ return (Reset (rep->Add(a.rep))); }
	Int operator-= (Int a)				{ return (Reset (rep->Sub(a.rep))); }
	Int operator*= (Int a)				{ return (Reset (rep->Mult(a.rep))); }
	Int operator/= (Int a)				{ return (Reset (rep->Div(a.rep))); }
	Int operator%= (Int a)				{ return (Reset (rep->Mod(a.rep))); }
	Int operator|= (Int a)				{ return (Reset (rep->Or(a.rep))); }
	Int operator&= (Int a)				{ return (Reset (rep->And(a.rep))); }
	Int operator^= (Int a)				{ return (Reset (rep->Xor(a.rep))); }
	Int operator<<= (Int a)			{ return (Reset (rep->LeftShift(a.rep))); }
	Int operator>>= (Int a)			{ return (Reset (rep->RightShift(a.rep))); }

		// Increment/decrement.
	void operator++ ()					{ INT_REP orep(1l); Reset (rep->Add(&orep)); }
	void operator-- ()					{ INT_REP orep(-1l); Reset (rep->Add(&orep)); }

		// Binary arithmetic operators.
	Int operator + (Int b)				{ return Int(rep->Add(b.rep)); }
	Int operator - (Int b)				{ return Int(rep->Sub(b.rep)); }
	Int operator * (Int b)				{ return Int(rep->Mult(b.rep)); } 
	Int operator / (Int b)				{ return Int(rep->Div(b.rep)); }  
	Int operator % (Int b)				{ return Int(rep->Mod(b.rep)); }  

		// Logical operators.
	int operator <= (Int b)				{ return (rep->Comp(b.rep) == 1 ? 0 : 1); }            
	int operator >= (Int b)				{ return (rep->Comp(b.rep) == -1 ? 0 : 1); }           
	int operator <  (Int b)				{ return (rep->Comp(b.rep) == -1 ? 1 : 0); }           
	int operator >  (Int b)				{ return (rep->Comp(b.rep) == 1 ? 1 : 0); }            
	int operator == (Int b)				{ return (rep->Comp(b.rep) == 0 ? 1 : 0); }            
	int operator != (Int b)				{ return (rep->Comp(b.rep) == 0 ? 0 : 1); }            
	int operator ! ()					{ return (rep->isZero() ? 1 : 0);  }                   
	int operator || (Int b)
		{ return (rep->isNonzero()>0 ? 1 : (b.rep->isNonzero()>0 ? 1 : 0)); }
	int operator && (Int b)
		{ return (rep->isZero() ? 0 : (b.rep->isZero() ? 0 : 1)); }

		// Bitwise operators.
	Int operator >> (Int b)				{ return Int(rep->RightShift(b.rep)); }
	Int operator << (Int b)				{ return Int(rep->LeftShift(b.rep)); }
	Int operator | (Int b)				{ return Int(rep->Or(b.rep)); }
	Int operator & (Int b)				{ return Int(rep->And(b.rep)); }
	Int operator ^ (Int b)				{ return Int(rep->Xor(b.rep)); }
	Int operator ~ ()					{ return Int(rep->Not()); }

		// Miscellaneous.	
	Int operator - ()			// Unary minus.
		{ INT_REP *b = new INT_REP(rep); b->Chsign(); return Int(b); }
	Int Exp (Int b)				// Exponentiate this to the given power.
		{ return Int(rep->Exp(b.rep)); }
	Int GCD (Int b)				// GCD of this and parameter.
		{ return Int(rep->GCD(b.rep)); }
	long Long(int &error)					// Convert this to signed long;
		{ return (rep->Trunc(error));  }	// if bits are lost, error will be nonzero.
	operator void * ()
		{ return (rep->isZero() ? (void *)0 : (void *)rep);  } 
                         
		// Output.
	int	Dec (char *buf, int buflen = -1)	{ return (rep->Store (buf, buflen, 0)); }
	int	Oct (char *buf, int buflen = -1)	{ return (rep->Store (buf, buflen, 1)); }
	int	Hex (char *buf, int buflen = -1)	{ return (rep->Store (buf, buflen, 2)); }
	void Dec (OutFn fn)			{ rep->Print (fn, 0); }
	void Oct (OutFn fn)			{ rep->Print (fn, 1); }
	void Hex (OutFn fn)			{ rep->Print (fn, 2); }
	friend ostream & operator << (ostream &i, Int n)
		{ n.Print(i); return(i); }
#ifdef DEBUG
	void Prt()					// Print internal representation.
		{ rep->Prt(); }
#endif DEBUG

		// Friends.
	friend Int operator >> (Int b, long a);
	friend Int operator << (Int b, long a);

};


			/* Mixed long and Int functions. */

	// Binary arithmetic operators.
inline Int operator + (long a, Int b)				{ return (Int(a) + b); }
inline Int operator + (Int b, long a)				{ return (b + Int(a)); }
inline Int operator - (long a, Int b)				{ return (Int(a) - b); }
inline Int operator - (Int b, long a)				{ return (b - Int(a)); }
inline Int operator * (long a, Int b)				{ return (Int(a) * b); }
inline Int operator * (Int b, long a)				{ return (b * Int(a)); }
inline Int operator / (long a, Int b)				{ return (Int(a) / b); }
inline Int operator / (Int b, long a)				{ return (b / Int(a)); }
inline Int operator % (long a, Int b)				{ return (Int(a) % b); }
inline Int operator % (Int b, long a)				{ return (b % Int(a)); }

	// Logical operators.
inline int operator <= (long a, Int b)				{ return (Int(a) <= b); }
inline int operator <= (Int b, long a)				{ return (b <= Int(a)); }
inline int operator >= (long a, Int b)				{ return (Int(a) >= b); }
inline int operator >= (Int b, long a)				{ return (b >= Int(a)); }
inline int operator <  (long a, Int b)				{ return (Int(a) <  b); }
inline int operator <  (Int b, long a)				{ return (b  < Int(a)); }
inline int operator >  (long a, Int b)				{ return (Int(a) >  b); }
inline int operator >  (Int b, long a)				{ return (b  > Int(a)); }
inline int operator == (long a, Int b)				{ return (Int(a) == b); }
inline int operator == (Int b, long a)				{ return (b == Int(a)); }
inline int operator != (long a, Int b)				{ return (Int(a) != b); }
inline int operator != (Int b, long a)				{ return (b != Int(a)); }
inline int operator || (long a, Int b) 				{ return (a ? 1 : (b ? 1 : 0)); }
inline int operator || (Int b, long a) 				{ return (b ? 1 : (a ? 1 : 0)); }
inline int operator && (long a, Int b) 				{ return (a==0 ? 0 : (b ? 1 : 0)); }
inline int operator && (Int b, long a) 				{ return (!b ? 0 : (a==0 ? 0 : 1)); }

	// Bitwise operators.
inline Int operator >> (long a, Int b)				{ return (Int(a)>>b); }
inline Int operator >> (Int b, long a)				{ return Int(b.rep->RightShift(a)); }
inline Int operator << (long a, Int b)				{ return (Int(a)<<b); }
inline Int operator << (Int b, long a)				{ return Int(b.rep->LeftShift(a)); }
inline Int operator | (long a, Int b)				{ return (Int(a) | b); }
inline Int operator | (Int b, long a)				{ return (b | Int(a)); }
inline Int operator & (long a, Int b)				{ return (Int(a) & b); }
inline Int operator & (Int b, long a)				{ return (b & Int(a)); }
inline Int operator ^ (long a, Int b)				{ return (Int(a) ^ b); }
inline Int operator ^ (Int b, long a)				{ return (b ^ Int(a)); }

	// Miscellaneous functions.
inline Int Exp (Int a, Int b)						{ return (a.Exp(b)); }
inline Int Exp (long a, Int b)						{ return (Int(a).Exp(b)); }
inline Int Exp (Int b, long a)						{ return (b.Exp(Int(a))); }
inline Int GCD (Int a, Int b)						{ return (b.GCD(a)); }
inline Int GCD (long a, Int b)						{ return (b.GCD(Int(a))); }
inline Int GCD (Int b, long a)						{ return (b.GCD(Int(a))); }

#endif INT_H
