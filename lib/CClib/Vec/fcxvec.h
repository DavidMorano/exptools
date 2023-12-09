 /* Vector library
 *
 * Brent Townshend (bst@alice)
 * AT&T Bell Laboratories
 * MH 2D-554 (201)582-4111
 * Version: @(#)vector.h.mac 1.2 88/12/07 14:39:09
 */
#ifndef fcxvec_h
#define fcxvec_h
#include <libc.h>
#include <generic.h>
#include <stream.h>
#include <ivec.h>
#ifndef scomplex
#include <scomplex.h>
#else
#include <dcxvec.h>
#endif
#include <fvec.h>
#ifndef scomplex
#ifdef alliant
extern "C"{
    void vec_bmov(char*,const char*,int);
}
inline void COPY(scomplex *to,const scomplex *from, int n)
    { vec_bmov((char *)to,(const char *)from,(n)*sizeof(scomplex)); }
#else
#include <memory.h>
inline void mov(scomplex *to,const scomplex *from, int n)
    { memcpy(to,from,(n)*sizeof(scomplex)); }
inline void COPY(scomplex *to,const scomplex *from, int n)
    { memcpy(to,from,(n)*sizeof(scomplex)); }
#endif
#endif
class ucvec;
class cvec;
class svec;
class ivec;
class fvec;
class dvec;
class fcxvec;
class dcxvec;
class fcxvec;
class fcxvec_Rep;
extern fcxvec_Rep *null_fcxvec_Rep;
struct fcxvec_Rep {
    int refc;
    int allocsz;
    scomplex v[1];
    void Inc() { refc++; }
    void Dec() { refc--;
	    if ((refc == 0) && (this != null_fcxvec_Rep))
		delete (char *)this;
	  }
    fcxvec_Rep() { allocsz = 0; refc=0; }   /* Only used to create null_fcxvec_Rep */
    friend fcxvec_Rep *new_fcxvec_Rep(const fcxvec_Rep *old,int sz)
	{ fcxvec_Rep *result = new_fcxvec_Rep(sz);
	  COPY(result->v,old->v,sz);
	  return result; }
    friend fcxvec_Rep *new_fcxvec_Rep(int sz)
	{ if (sz==0) return null_fcxvec_Rep;
	  else {
	  fcxvec_Rep *result = (fcxvec_Rep *)
		new char[(sz-1)*sizeof(scomplex)+sizeof(fcxvec_Rep)];
	  result->allocsz = sz;
	  result->refc = 1;
	  return result; } }
};
 /* A Subfcxvec are the same as a fcxvec except that assignments into do not create
    a copy of the representation.  Thus changes to a Subfcxvec affect the original
	fcxvec it was created from.
*/
class Subfcxvec {
    friend fcxvec;
    fcxvec *it;
    int offset;		 /* Offset in Rep for accesses */
    int sz;
    Subfcxvec(fcxvec *old, int off, int len)
	{ it=old;offset=off;sz=len; }
public:
    Subfcxvec& operator=(const fcxvec&);
    Subfcxvec& operator=(scomplex);

     Subfcxvec& operator+=(const fcxvec&);
     Subfcxvec& operator+=(scomplex);

     Subfcxvec& operator-=(const fcxvec&);
     Subfcxvec& operator-=(scomplex);

     Subfcxvec& operator*=(const fcxvec&);
     Subfcxvec& operator*=(scomplex);

     Subfcxvec& operator/=(const fcxvec&);
     Subfcxvec& operator/=(scomplex);
};
class fcxvec {
    friend Subfcxvec;
    fcxvec_Rep *r;
    int sz;		 /* Number of elements accessed by this vector */
    int origin;		 /* Origin of indexing */
    static GPT handler;
    void Unique()
	{ if (r->refc != 1) { r->Dec(); r = new_fcxvec_Rep(r,sz);  } }
public:
    void error(int i,char* p) const
    {   if (handler)
	    (*handler)(i,p);
	else {
	    cerr << (p?p:"error in fcxvec :") << i << "\n";
	    abort();
	    }
    }
    fcxvec() { sz=origin=0; r = null_fcxvec_Rep; }
    fcxvec(int s)
    {	if (s<0) error(1,form("Bad vector size: %d",s));
	sz=s;
	origin = 0;
	r = new_fcxvec_Rep(sz);
    }
    fcxvec(int first,int last)
    {   if (last < first) error(1,form("Bad vector bounds: %d-%d",
	last,first));
	sz=last-first+1;
	origin = first;
	r = new_fcxvec_Rep(sz);
    }
    fcxvec(const Subfcxvec &old);
    ~fcxvec() { r->Dec(); }
    fcxvec(const fcxvec&);
    fcxvec(const dcxvec&);
    fcxvec(const ucvec&);
    fcxvec(const cvec&);
    fcxvec(const svec&);
    fcxvec(const ivec&);
    fcxvec(const fvec&);
    fcxvec(const dvec&);
    operator const scomplex*()
	{ return r->v; }  /* Need to be careful this doesn't get relocated */
    Subfcxvec operator()(int first,int last);
    Subfcxvec operator()(int first) { return((*this)(first,origin+sz-1)); }
    const Subfcxvec operator()(int first,int last) const;
    const Subfcxvec operator()(int first) const
	{ return((*this)(first,origin+sz-1)); }
    int size() const { return sz; }
    void set_size(int);
    int orig() const { return origin; }
    void set_orig(int x) { origin = x; }
    scomplex& elem(int i)
	{ Unique();  return r->v[i]; }
    const scomplex& GetElem(int i) const
	{ return r->v[i]; }
    friend int equal(const fcxvec& left, const fcxvec& right) ;
    friend scomplex dot(const fcxvec&,const fcxvec&) ;
    friend scomplex prod(const fcxvec& x) ;
    friend scomplex sum(const fcxvec& x) ;


     friend fcxvec operator+(const fcxvec&,const fcxvec&) ;
     friend fcxvec operator+(const fcxvec&,scomplex) ;
     friend fcxvec operator+(scomplex,const fcxvec&) ;


     fcxvec& operator+=(const fcxvec&);
     fcxvec& operator+=(scomplex);


     friend fcxvec operator-(const fcxvec&,const fcxvec&) ;
     friend fcxvec operator-(const fcxvec&,scomplex) ;
     friend fcxvec operator-(scomplex,const fcxvec&) ;


     fcxvec& operator-=(const fcxvec&);
     fcxvec& operator-=(scomplex);


     friend fcxvec operator*(const fcxvec&,const fcxvec&) ;
     friend fcxvec operator*(const fcxvec&,scomplex) ;
     friend fcxvec operator*(scomplex,const fcxvec&) ;


     fcxvec& operator*=(const fcxvec&);
     fcxvec& operator*=(scomplex);


     friend fcxvec operator/(const fcxvec&,const fcxvec&) ;
     friend fcxvec operator/(const fcxvec&,scomplex) ;
     friend fcxvec operator/(scomplex,const fcxvec&) ;


     fcxvec& operator/=(const fcxvec&);
     fcxvec& operator/=(scomplex);
    friend fcxvec operator-(const fcxvec& x) ;
    friend fvec real(const fcxvec&);
    friend fvec imag(const fcxvec&);
    friend fvec arg(const fcxvec&);
    friend fvec abs(const fcxvec&);
    friend fvec norm(const fcxvec&);
    friend fcxvec conj(const fcxvec&);

     friend ivec operator==(const fcxvec&, const fcxvec&) ;
     friend ivec operator==(const fcxvec&, scomplex) ;
     friend ivec operator==(scomplex,const fcxvec&) ;

     friend ivec operator!=(const fcxvec&, const fcxvec&) ;
     friend ivec operator!=(const fcxvec&, scomplex) ;
     friend ivec operator!=(scomplex,const fcxvec&) ;
    fcxvec& operator=(const fcxvec&);
    fcxvec& operator=(scomplex);
    scomplex& operator[](int i)
    {   if (i<origin || origin+sz<=i)
	   error(2,form("Vector index (%d) out of range: [%d-%d]",
		i,origin,origin+sz-1));
	Unique();
	return r->v[i-origin];
    }
    const scomplex& operator[](int i) const
    {   if (i<origin || origin+sz<=i)
	   error(2,form("Vector index (%d) out of range: [%d-%d]",
		i,origin,origin+sz-1));
	return r->v[i-origin];
    }
    friend ostream& operator<<(ostream&,const fcxvec&) ;
    friend istream& operator>>(istream&,fcxvec&) ;
    ostream& fcxvec::BinaryWrite(ostream& s) const;
    istream& fcxvec::BinaryRead(istream &s,int nelem=-1);
    GPT sethandler(GPT);
};
 /* These routines need to be inline to avoid pulling in other vec types
   when only one is used */
inline fcxvec::fcxvec(const fcxvec& a)
{
    sz = a.sz;
    origin = a.origin;
    r = a.r;
    r->Inc();
}
inline fcxvec::fcxvec(const Subfcxvec& a)
{
    sz = a.sz;
    origin = 0;
    r = new_fcxvec_Rep(sz);
    COPY(r->v,&a.it->r->v[a.offset],sz);
}
#endif
