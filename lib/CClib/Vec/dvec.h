 /* Vector library
 *
 * Brent Townshend (bst@alice)
 * AT&T Bell Laboratories
 * MH 2D-554 (201)582-4111
 * Version: @(#)vector.h.mac 1.2 88/12/07 14:39:09
 */
#ifndef dvec_h
#define dvec_h
#include <libc.h>
#include <generic.h>
#include <stream.h>
#include <ivec.h>
#ifdef alliant
extern "C"{
    void vec_bmov(char*,const char*,int);
}
inline void COPY(double *to,const double *from, int n)
    { vec_bmov((char *)to,(const char *)from,(n)*sizeof(double)); }
#else
#include <memory.h>
inline void mov(double *to,const double *from, int n)
    { memcpy(to,from,(n)*sizeof(double)); }
inline void COPY(double *to,const double *from, int n)
    { memcpy(to,from,(n)*sizeof(double)); }
#endif
class ucvec;
class cvec;
class svec;
class ivec;
class fvec;
class dvec;
class dvec;
class dvec_Rep;
extern dvec_Rep *null_dvec_Rep;
struct dvec_Rep {
    int refc;
    int allocsz;
    double v[1];
    void Inc() { refc++; }
    void Dec() { refc--;
	    if ((refc == 0) && (this != null_dvec_Rep))
		delete (char *)this;
	  }
    dvec_Rep() { allocsz = 0; refc=0; }   /* Only used to create null_dvec_Rep */
    friend dvec_Rep *new_dvec_Rep(const dvec_Rep *old,int sz)
	{ dvec_Rep *result = new_dvec_Rep(sz);
	  COPY(result->v,old->v,sz);
	  return result; }
    friend dvec_Rep *new_dvec_Rep(int sz)
	{ if (sz==0) return null_dvec_Rep;
	  else {
	  dvec_Rep *result = (dvec_Rep *)
		new char[(sz-1)*sizeof(double)+sizeof(dvec_Rep)];
	  result->allocsz = sz;
	  result->refc = 1;
	  return result; } }
};
 /* A Subdvec are the same as a dvec except that assignments into do not create
    a copy of the representation.  Thus changes to a Subdvec affect the original
	dvec it was created from.
*/
class Subdvec {
    friend dvec;
    dvec *it;
    int offset;		 /* Offset in Rep for accesses */
    int sz;
    Subdvec(dvec *old, int off, int len)
	{ it=old;offset=off;sz=len; }
public:
    Subdvec& operator=(const dvec&);
    Subdvec& operator=(double);

     Subdvec& operator+=(const dvec&);
     Subdvec& operator+=(double);

     Subdvec& operator-=(const dvec&);
     Subdvec& operator-=(double);

     Subdvec& operator*=(const dvec&);
     Subdvec& operator*=(double);

     Subdvec& operator/=(const dvec&);
     Subdvec& operator/=(double);
};
class dvec {
    friend Subdvec;
    dvec_Rep *r;
    int sz;		 /* Number of elements accessed by this vector */
    int origin;		 /* Origin of indexing */
    static GPT handler;
    void Unique()
	{ if (r->refc != 1) { r->Dec(); r = new_dvec_Rep(r,sz);  } }
public:
    void error(int i,char* p) const
    {   if (handler)
	    (*handler)(i,p);
	else {
	    cerr << (p?p:"error in dvec :") << i << "\n";
	    abort();
	    }
    }
    dvec() { sz=origin=0; r = null_dvec_Rep; }
    dvec(int s)
    {	if (s<0) error(1,form("Bad vector size: %d",s));
	sz=s;
	origin = 0;
	r = new_dvec_Rep(sz);
    }
    dvec(int first,int last)
    {   if (last < first) error(1,form("Bad vector bounds: %d-%d",
	last,first));
	sz=last-first+1;
	origin = first;
	r = new_dvec_Rep(sz);
    }
    dvec(const Subdvec &old);
    ~dvec() { r->Dec(); }
    dvec(const ucvec&);
    dvec(const cvec&);
    dvec(const svec&);
    dvec(const ivec&);
    dvec(const fvec&);
    dvec(const dvec&);
    operator const double*()
	{ return r->v; }  /* Need to be careful this doesn't get relocated */
    Subdvec operator()(int first,int last);
    Subdvec operator()(int first) { return((*this)(first,origin+sz-1)); }
    const Subdvec operator()(int first,int last) const;
    const Subdvec operator()(int first) const
	{ return((*this)(first,origin+sz-1)); }
    int size() const { return sz; }
    void set_size(int);
    int orig() const { return origin; }
    void set_orig(int x) { origin = x; }
    double& elem(int i)
	{ Unique();  return r->v[i]; }
    const double& GetElem(int i) const
	{ return r->v[i]; }
    friend int equal(const dvec& left, const dvec& right) ;
    friend dvec abs(const dvec&) ;
    friend double max(const dvec&) ;
    friend double min(const dvec&) ;

     friend dvec min(const dvec&,const dvec&) ;
     friend dvec min(const dvec&,double) ;
     friend dvec min(double,const dvec&) ;

     friend dvec max(const dvec&,const dvec&) ;
     friend dvec max(const dvec&,double) ;
     friend dvec max(double,const dvec&) ;
    friend double dot(const dvec&,const dvec&) ;
    friend double prod(const dvec& x) ;
    friend double sum(const dvec& x) ;


     friend dvec operator+(const dvec&,const dvec&) ;
     friend dvec operator+(const dvec&,double) ;
     friend dvec operator+(double,const dvec&) ;


     dvec& operator+=(const dvec&);
     dvec& operator+=(double);


     friend dvec operator-(const dvec&,const dvec&) ;
     friend dvec operator-(const dvec&,double) ;
     friend dvec operator-(double,const dvec&) ;


     dvec& operator-=(const dvec&);
     dvec& operator-=(double);


     friend dvec operator*(const dvec&,const dvec&) ;
     friend dvec operator*(const dvec&,double) ;
     friend dvec operator*(double,const dvec&) ;


     dvec& operator*=(const dvec&);
     dvec& operator*=(double);


     friend dvec operator/(const dvec&,const dvec&) ;
     friend dvec operator/(const dvec&,double) ;
     friend dvec operator/(double,const dvec&) ;


     dvec& operator/=(const dvec&);
     dvec& operator/=(double);
    friend dvec operator-(const dvec& x) ;

     friend ivec operator>=(const dvec&, const dvec&) ;
     friend ivec operator>=(const dvec&, double) ;
     friend ivec operator>=(double,const dvec&) ;

     friend ivec operator>(const dvec&, const dvec&) ;
     friend ivec operator>(const dvec&, double) ;
     friend ivec operator>(double,const dvec&) ;

     friend ivec operator<=(const dvec&, const dvec&) ;
     friend ivec operator<=(const dvec&, double) ;
     friend ivec operator<=(double,const dvec&) ;

     friend ivec operator<(const dvec&, const dvec&) ;
     friend ivec operator<(const dvec&, double) ;
     friend ivec operator<(double,const dvec&) ;

     friend ivec operator==(const dvec&, const dvec&) ;
     friend ivec operator==(const dvec&, double) ;
     friend ivec operator==(double,const dvec&) ;

     friend ivec operator!=(const dvec&, const dvec&) ;
     friend ivec operator!=(const dvec&, double) ;
     friend ivec operator!=(double,const dvec&) ;
    dvec& operator=(const dvec&);
    dvec& operator=(double);
    double& operator[](int i)
    {   if (i<origin || origin+sz<=i)
	   error(2,form("Vector index (%d) out of range: [%d-%d]",
		i,origin,origin+sz-1));
	Unique();
	return r->v[i-origin];
    }
    const double& operator[](int i) const
    {   if (i<origin || origin+sz<=i)
	   error(2,form("Vector index (%d) out of range: [%d-%d]",
		i,origin,origin+sz-1));
	return r->v[i-origin];
    }
    friend ostream& operator<<(ostream&,const dvec&) ;
    friend istream& operator>>(istream&,dvec&) ;
    ostream& dvec::BinaryWrite(ostream& s) const;
    istream& dvec::BinaryRead(istream &s,int nelem=-1);
    GPT sethandler(GPT);
};
 /* These routines need to be inline to avoid pulling in other vec types
   when only one is used */
inline dvec::dvec(const dvec& a)
{
    sz = a.sz;
    origin = a.origin;
    r = a.r;
    r->Inc();
}
inline dvec::dvec(const Subdvec& a)
{
    sz = a.sz;
    origin = 0;
    r = new_dvec_Rep(sz);
    COPY(r->v,&a.it->r->v[a.offset],sz);
}
#endif
