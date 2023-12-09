 /* Vector library
 *
 * Brent Townshend (bst@alice)
 * AT&T Bell Laboratories
 * MH 2D-554 (201)582-4111
 * Version: @(#)vector.h.mac 1.2 88/12/07 14:39:09
 */
#ifndef fvec_h
#define fvec_h
#include <libc.h>
#include <generic.h>
#include <stream.h>
#include <ivec.h>
#ifdef alliant
extern "C"{
    void vec_bmov(char*,const char*,int);
}
inline void COPY(float *to,const float *from, int n)
    { vec_bmov((char *)to,(const char *)from,(n)*sizeof(float)); }
#else
#include <memory.h>
inline void mov(float *to,const float *from, int n)
    { memcpy(to,from,(n)*sizeof(float)); }
inline void COPY(float *to,const float *from, int n)
    { memcpy(to,from,(n)*sizeof(float)); }
#endif
class ucvec;
class cvec;
class svec;
class ivec;
class fvec;
class dvec;
class fvec;
class fvec_Rep;
extern fvec_Rep *null_fvec_Rep;
struct fvec_Rep {
    int refc;
    int allocsz;
    float v[1];
    void Inc() { refc++; }
    void Dec() { refc--;
	    if ((refc == 0) && (this != null_fvec_Rep))
		delete (char *)this;
	  }
    fvec_Rep() { allocsz = 0; refc=0; }   /* Only used to create null_fvec_Rep */
    friend fvec_Rep *new_fvec_Rep(const fvec_Rep *old,int sz)
	{ fvec_Rep *result = new_fvec_Rep(sz);
	  COPY(result->v,old->v,sz);
	  return result; }
    friend fvec_Rep *new_fvec_Rep(int sz)
	{ if (sz==0) return null_fvec_Rep;
	  else {
	  fvec_Rep *result = (fvec_Rep *)
		new char[(sz-1)*sizeof(float)+sizeof(fvec_Rep)];
	  result->allocsz = sz;
	  result->refc = 1;
	  return result; } }
};
 /* A Subfvec are the same as a fvec except that assignments into do not create
    a copy of the representation.  Thus changes to a Subfvec affect the original
	fvec it was created from.
*/
class Subfvec {
    friend fvec;
    fvec *it;
    int offset;		 /* Offset in Rep for accesses */
    int sz;
    Subfvec(fvec *old, int off, int len)
	{ it=old;offset=off;sz=len; }
public:
    Subfvec& operator=(const fvec&);
    Subfvec& operator=(float);

     Subfvec& operator+=(const fvec&);
     Subfvec& operator+=(float);

     Subfvec& operator-=(const fvec&);
     Subfvec& operator-=(float);

     Subfvec& operator*=(const fvec&);
     Subfvec& operator*=(float);

     Subfvec& operator/=(const fvec&);
     Subfvec& operator/=(float);
};
class fvec {
    friend Subfvec;
    fvec_Rep *r;
    int sz;		 /* Number of elements accessed by this vector */
    int origin;		 /* Origin of indexing */
    static GPT handler;
    void Unique()
	{ if (r->refc != 1) { r->Dec(); r = new_fvec_Rep(r,sz);  } }
public:
    void error(int i,char* p) const
    {   if (handler)
	    (*handler)(i,p);
	else {
	    cerr << (p?p:"error in fvec :") << i << "\n";
	    abort();
	    }
    }
    fvec() { sz=origin=0; r = null_fvec_Rep; }
    fvec(int s)
    {	if (s<0) error(1,form("Bad vector size: %d",s));
	sz=s;
	origin = 0;
	r = new_fvec_Rep(sz);
    }
    fvec(int first,int last)
    {   if (last < first) error(1,form("Bad vector bounds: %d-%d",
	last,first));
	sz=last-first+1;
	origin = first;
	r = new_fvec_Rep(sz);
    }
    fvec(const Subfvec &old);
    ~fvec() { r->Dec(); }
    fvec(const ucvec&);
    fvec(const cvec&);
    fvec(const svec&);
    fvec(const ivec&);
    fvec(const fvec&);
    fvec(const dvec&);
    operator const float*()
	{ return r->v; }  /* Need to be careful this doesn't get relocated */
    Subfvec operator()(int first,int last);
    Subfvec operator()(int first) { return((*this)(first,origin+sz-1)); }
    const Subfvec operator()(int first,int last) const;
    const Subfvec operator()(int first) const
	{ return((*this)(first,origin+sz-1)); }
    int size() const { return sz; }
    void set_size(int);
    int orig() const { return origin; }
    void set_orig(int x) { origin = x; }
    float& elem(int i)
	{ Unique();  return r->v[i]; }
    const float& GetElem(int i) const
	{ return r->v[i]; }
    friend int equal(const fvec& left, const fvec& right) ;
    friend fvec abs(const fvec&) ;
    friend float max(const fvec&) ;
    friend float min(const fvec&) ;

     friend fvec min(const fvec&,const fvec&) ;
     friend fvec min(const fvec&,float) ;
     friend fvec min(float,const fvec&) ;

     friend fvec max(const fvec&,const fvec&) ;
     friend fvec max(const fvec&,float) ;
     friend fvec max(float,const fvec&) ;
    friend float dot(const fvec&,const fvec&) ;
    friend float prod(const fvec& x) ;
    friend float sum(const fvec& x) ;


     friend fvec operator+(const fvec&,const fvec&) ;
     friend fvec operator+(const fvec&,float) ;
     friend fvec operator+(float,const fvec&) ;


     fvec& operator+=(const fvec&);
     fvec& operator+=(float);


     friend fvec operator-(const fvec&,const fvec&) ;
     friend fvec operator-(const fvec&,float) ;
     friend fvec operator-(float,const fvec&) ;


     fvec& operator-=(const fvec&);
     fvec& operator-=(float);


     friend fvec operator*(const fvec&,const fvec&) ;
     friend fvec operator*(const fvec&,float) ;
     friend fvec operator*(float,const fvec&) ;


     fvec& operator*=(const fvec&);
     fvec& operator*=(float);


     friend fvec operator/(const fvec&,const fvec&) ;
     friend fvec operator/(const fvec&,float) ;
     friend fvec operator/(float,const fvec&) ;


     fvec& operator/=(const fvec&);
     fvec& operator/=(float);
    friend fvec operator-(const fvec& x) ;

     friend ivec operator>=(const fvec&, const fvec&) ;
     friend ivec operator>=(const fvec&, float) ;
     friend ivec operator>=(float,const fvec&) ;

     friend ivec operator>(const fvec&, const fvec&) ;
     friend ivec operator>(const fvec&, float) ;
     friend ivec operator>(float,const fvec&) ;

     friend ivec operator<=(const fvec&, const fvec&) ;
     friend ivec operator<=(const fvec&, float) ;
     friend ivec operator<=(float,const fvec&) ;

     friend ivec operator<(const fvec&, const fvec&) ;
     friend ivec operator<(const fvec&, float) ;
     friend ivec operator<(float,const fvec&) ;

     friend ivec operator==(const fvec&, const fvec&) ;
     friend ivec operator==(const fvec&, float) ;
     friend ivec operator==(float,const fvec&) ;

     friend ivec operator!=(const fvec&, const fvec&) ;
     friend ivec operator!=(const fvec&, float) ;
     friend ivec operator!=(float,const fvec&) ;
    fvec& operator=(const fvec&);
    fvec& operator=(float);
    float& operator[](int i)
    {   if (i<origin || origin+sz<=i)
	   error(2,form("Vector index (%d) out of range: [%d-%d]",
		i,origin,origin+sz-1));
	Unique();
	return r->v[i-origin];
    }
    const float& operator[](int i) const
    {   if (i<origin || origin+sz<=i)
	   error(2,form("Vector index (%d) out of range: [%d-%d]",
		i,origin,origin+sz-1));
	return r->v[i-origin];
    }
    friend ostream& operator<<(ostream&,const fvec&) ;
    friend istream& operator>>(istream&,fvec&) ;
    ostream& fvec::BinaryWrite(ostream& s) const;
    istream& fvec::BinaryRead(istream &s,int nelem=-1);
    GPT sethandler(GPT);
};
 /* These routines need to be inline to avoid pulling in other vec types
   when only one is used */
inline fvec::fvec(const fvec& a)
{
    sz = a.sz;
    origin = a.origin;
    r = a.r;
    r->Inc();
}
inline fvec::fvec(const Subfvec& a)
{
    sz = a.sz;
    origin = 0;
    r = new_fvec_Rep(sz);
    COPY(r->v,&a.it->r->v[a.offset],sz);
}
#endif
