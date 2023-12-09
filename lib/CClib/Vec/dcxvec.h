 /* Vector library
 *
 * Brent Townshend (bst@alice)
 * AT&T Bell Laboratories
 * MH 2D-554 (201)582-4111
 * Version: @(#)vector.h.mac 1.2 88/12/07 14:39:09
 */
#ifndef dcxvec_h
#define dcxvec_h
#include <libc.h>
#include <generic.h>
#include <stream.h>
#include <ivec.h>
#include <complex.h>
#include <dvec.h>
#ifdef alliant
extern "C"{
    void vec_bmov(char*,const char*,int);
}
inline void COPY(complex *to,const complex *from, int n)
    { vec_bmov((char *)to,(const char *)from,(n)*sizeof(complex)); }
#else
#include <memory.h>
inline void mov(complex *to,const complex *from, int n)
    { memcpy(to,from,(n)*sizeof(complex)); }
inline void COPY(complex *to,const complex *from, int n)
    { memcpy(to,from,(n)*sizeof(complex)); }
#endif
class ucvec;
class cvec;
class svec;
class ivec;
class fvec;
class dvec;
class fcxvec;
class dcxvec;
class dcxvec;
class dcxvec_Rep;
extern dcxvec_Rep *null_dcxvec_Rep;
struct dcxvec_Rep {
    int refc;
    int allocsz;
    complex v[1];
    void Inc() { refc++; }
    void Dec() { refc--;
	    if ((refc == 0) && (this != null_dcxvec_Rep))
		delete (char *)this;
	  }
    dcxvec_Rep() { allocsz = 0; refc=0; }   /* Only used to create null_dcxvec_Rep */
    friend dcxvec_Rep *new_dcxvec_Rep(const dcxvec_Rep *old,int sz)
	{ dcxvec_Rep *result = new_dcxvec_Rep(sz);
	  COPY(result->v,old->v,sz);
	  return result; }
    friend dcxvec_Rep *new_dcxvec_Rep(int sz)
	{ if (sz==0) return null_dcxvec_Rep;
	  else {
	  dcxvec_Rep *result = (dcxvec_Rep *)
		new char[(sz-1)*sizeof(complex)+sizeof(dcxvec_Rep)];
	  result->allocsz = sz;
	  result->refc = 1;
	  return result; } }
};
 /* A Subdcxvec are the same as a dcxvec except that assignments into do not create
    a copy of the representation.  Thus changes to a Subdcxvec affect the original
	dcxvec it was created from.
*/
class Subdcxvec {
    friend dcxvec;
    dcxvec *it;
    int offset;		 /* Offset in Rep for accesses */
    int sz;
    Subdcxvec(dcxvec *old, int off, int len)
	{ it=old;offset=off;sz=len; }
public:
    Subdcxvec& operator=(const dcxvec&);
    Subdcxvec& operator=(complex);

     Subdcxvec& operator+=(const dcxvec&);
     Subdcxvec& operator+=(complex);

     Subdcxvec& operator-=(const dcxvec&);
     Subdcxvec& operator-=(complex);

     Subdcxvec& operator*=(const dcxvec&);
     Subdcxvec& operator*=(complex);

     Subdcxvec& operator/=(const dcxvec&);
     Subdcxvec& operator/=(complex);
};
class dcxvec {
    friend Subdcxvec;
    dcxvec_Rep *r;
    int sz;		 /* Number of elements accessed by this vector */
    int origin;		 /* Origin of indexing */
    static GPT handler;
    void Unique()
	{ if (r->refc != 1) { r->Dec(); r = new_dcxvec_Rep(r,sz);  } }
public:
    void error(int i,char* p) const
    {   if (handler)
	    (*handler)(i,p);
	else {
	    cerr << (p?p:"error in dcxvec :") << i << "\n";
	    abort();
	    }
    }
    dcxvec() { sz=origin=0; r = null_dcxvec_Rep; }
    dcxvec(int s)
    {	if (s<0) error(1,form("Bad vector size: %d",s));
	sz=s;
	origin = 0;
	r = new_dcxvec_Rep(sz);
    }
    dcxvec(int first,int last)
    {   if (last < first) error(1,form("Bad vector bounds: %d-%d",
	last,first));
	sz=last-first+1;
	origin = first;
	r = new_dcxvec_Rep(sz);
    }
    dcxvec(const Subdcxvec &old);
    ~dcxvec() { r->Dec(); }
    dcxvec(const fcxvec&);
    dcxvec(const dcxvec&);
    dcxvec(const ucvec&);
    dcxvec(const cvec&);
    dcxvec(const svec&);
    dcxvec(const ivec&);
    dcxvec(const fvec&);
    dcxvec(const dvec&);
    operator const complex*()
	{ return r->v; }  /* Need to be careful this doesn't get relocated */
    Subdcxvec operator()(int first,int last);
    Subdcxvec operator()(int first) { return((*this)(first,origin+sz-1)); }
    const Subdcxvec operator()(int first,int last) const;
    const Subdcxvec operator()(int first) const
	{ return((*this)(first,origin+sz-1)); }
    int size() const { return sz; }
    void set_size(int);
    int orig() const { return origin; }
    void set_orig(int x) { origin = x; }
    complex& elem(int i)
	{ Unique();  return r->v[i]; }
    const complex& GetElem(int i) const
	{ return r->v[i]; }
    friend int equal(const dcxvec& left, const dcxvec& right) ;
    friend complex dot(const dcxvec&,const dcxvec&) ;
    friend complex prod(const dcxvec& x) ;
    friend complex sum(const dcxvec& x) ;


     friend dcxvec operator+(const dcxvec&,const dcxvec&) ;
     friend dcxvec operator+(const dcxvec&,complex) ;
     friend dcxvec operator+(complex,const dcxvec&) ;


     dcxvec& operator+=(const dcxvec&);
     dcxvec& operator+=(complex);


     friend dcxvec operator-(const dcxvec&,const dcxvec&) ;
     friend dcxvec operator-(const dcxvec&,complex) ;
     friend dcxvec operator-(complex,const dcxvec&) ;


     dcxvec& operator-=(const dcxvec&);
     dcxvec& operator-=(complex);


     friend dcxvec operator*(const dcxvec&,const dcxvec&) ;
     friend dcxvec operator*(const dcxvec&,complex) ;
     friend dcxvec operator*(complex,const dcxvec&) ;


     dcxvec& operator*=(const dcxvec&);
     dcxvec& operator*=(complex);


     friend dcxvec operator/(const dcxvec&,const dcxvec&) ;
     friend dcxvec operator/(const dcxvec&,complex) ;
     friend dcxvec operator/(complex,const dcxvec&) ;


     dcxvec& operator/=(const dcxvec&);
     dcxvec& operator/=(complex);
    friend dcxvec operator-(const dcxvec& x) ;
    friend dvec real(const dcxvec&);
    friend dvec imag(const dcxvec&);
    friend dvec arg(const dcxvec&);
    friend dvec abs(const dcxvec&);
    friend dvec norm(const dcxvec&);
    friend dcxvec conj(const dcxvec&);

     friend ivec operator==(const dcxvec&, const dcxvec&) ;
     friend ivec operator==(const dcxvec&, complex) ;
     friend ivec operator==(complex,const dcxvec&) ;

     friend ivec operator!=(const dcxvec&, const dcxvec&) ;
     friend ivec operator!=(const dcxvec&, complex) ;
     friend ivec operator!=(complex,const dcxvec&) ;
    dcxvec& operator=(const dcxvec&);
    dcxvec& operator=(complex);
    complex& operator[](int i)
    {   if (i<origin || origin+sz<=i)
	   error(2,form("Vector index (%d) out of range: [%d-%d]",
		i,origin,origin+sz-1));
	Unique();
	return r->v[i-origin];
    }
    const complex& operator[](int i) const
    {   if (i<origin || origin+sz<=i)
	   error(2,form("Vector index (%d) out of range: [%d-%d]",
		i,origin,origin+sz-1));
	return r->v[i-origin];
    }
    friend ostream& operator<<(ostream&,const dcxvec&) ;
    friend istream& operator>>(istream&,dcxvec&) ;
    ostream& dcxvec::BinaryWrite(ostream& s) const;
    istream& dcxvec::BinaryRead(istream &s,int nelem=-1);
    GPT sethandler(GPT);
};
 /* These routines need to be inline to avoid pulling in other vec types
   when only one is used */
inline dcxvec::dcxvec(const dcxvec& a)
{
    sz = a.sz;
    origin = a.origin;
    r = a.r;
    r->Inc();
}
inline dcxvec::dcxvec(const Subdcxvec& a)
{
    sz = a.sz;
    origin = 0;
    r = new_dcxvec_Rep(sz);
    COPY(r->v,&a.it->r->v[a.offset],sz);
}
#endif
