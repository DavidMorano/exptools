 /* Vector library
 *
 * Brent Townshend (bst@alice)
 * AT&T Bell Laboratories
 * MH 2D-554 (201)582-4111
 * Version: @(#)vector.h.mac 1.2 88/12/07 14:39:09
 */
#ifndef ivec_h
#define ivec_h
#include <libc.h>
#include <generic.h>
#include <stream.h>
#ifdef alliant
extern "C"{
    void vec_bmov(char*,const char*,int);
}
inline void COPY(int *to,const int *from, int n)
    { vec_bmov((char *)to,(const char *)from,(n)*sizeof(int)); }
#else
#include <memory.h>
inline void mov(int *to,const int *from, int n)
    { memcpy(to,from,(n)*sizeof(int)); }
inline void COPY(int *to,const int *from, int n)
    { memcpy(to,from,(n)*sizeof(int)); }
#endif
class ucvec;
class cvec;
class svec;
class ivec;
class fvec;
class dvec;
class ivec;
class ivec_Rep;
extern ivec_Rep *null_ivec_Rep;
struct ivec_Rep {
    int refc;
    int allocsz;
    int v[1];
    void Inc() { refc++; }
    void Dec() { refc--;
	    if ((refc == 0) && (this != null_ivec_Rep))
		delete (char *)this;
	  }
    ivec_Rep() { allocsz = 0; refc=0; }   /* Only used to create null_ivec_Rep */
    friend ivec_Rep *new_ivec_Rep(const ivec_Rep *old,int sz)
	{ ivec_Rep *result = new_ivec_Rep(sz);
	  COPY(result->v,old->v,sz);
	  return result; }
    friend ivec_Rep *new_ivec_Rep(int sz)
	{ if (sz==0) return null_ivec_Rep;
	  else {
	  ivec_Rep *result = (ivec_Rep *)
		new char[(sz-1)*sizeof(int)+sizeof(ivec_Rep)];
	  result->allocsz = sz;
	  result->refc = 1;
	  return result; } }
};
 /* A Subivec are the same as a ivec except that assignments into do not create
    a copy of the representation.  Thus changes to a Subivec affect the original
	ivec it was created from.
*/
class Subivec {
    friend ivec;
    ivec *it;
    int offset;		 /* Offset in Rep for accesses */
    int sz;
    Subivec(ivec *old, int off, int len)
	{ it=old;offset=off;sz=len; }
public:
    Subivec& operator=(const ivec&);
    Subivec& operator=(int);

     Subivec& operator+=(const ivec&);
     Subivec& operator+=(int);

     Subivec& operator-=(const ivec&);
     Subivec& operator-=(int);

     Subivec& operator*=(const ivec&);
     Subivec& operator*=(int);

     Subivec& operator/=(const ivec&);
     Subivec& operator/=(int);

     Subivec& operator^=(const ivec&);
     Subivec& operator^=(int);

     Subivec& operator&=(const ivec&);
     Subivec& operator&=(int);

     Subivec& operator|=(const ivec&);
     Subivec& operator|=(int);
};
class ivec {
    friend Subivec;
    ivec_Rep *r;
    int sz;		 /* Number of elements accessed by this vector */
    int origin;		 /* Origin of indexing */
    static GPT handler;
    void Unique()
	{ if (r->refc != 1) { r->Dec(); r = new_ivec_Rep(r,sz);  } }
public:
    void error(int i,char* p) const
    {   if (handler)
	    (*handler)(i,p);
	else {
	    cerr << (p?p:"error in ivec :") << i << "\n";
	    abort();
	    }
    }
    ivec() { sz=origin=0; r = null_ivec_Rep; }
    ivec(int s)
    {	if (s<0) error(1,form("Bad vector size: %d",s));
	sz=s;
	origin = 0;
	r = new_ivec_Rep(sz);
    }
    ivec(int first,int last)
    {   if (last < first) error(1,form("Bad vector bounds: %d-%d",
	last,first));
	sz=last-first+1;
	origin = first;
	r = new_ivec_Rep(sz);
    }
    ivec(const Subivec &old);
    ~ivec() { r->Dec(); }
    ivec(const ucvec&);
    ivec(const cvec&);
    ivec(const svec&);
    ivec(const ivec&);
    ivec(const fvec&);
    ivec(const dvec&);
    operator const int*()
	{ return r->v; }  /* Need to be careful this doesn't get relocated */
    Subivec operator()(int first,int last);
    Subivec operator()(int first) { return((*this)(first,origin+sz-1)); }
    const Subivec operator()(int first,int last) const;
    const Subivec operator()(int first) const
	{ return((*this)(first,origin+sz-1)); }
    int size() const { return sz; }
    void set_size(int);
    int orig() const { return origin; }
    void set_orig(int x) { origin = x; }
    int& elem(int i)
	{ Unique();  return r->v[i]; }
    const int& GetElem(int i) const
	{ return r->v[i]; }
    friend int equal(const ivec& left, const ivec& right) ;
    friend ivec abs(const ivec&) ;
    friend int max(const ivec&) ;
    friend int min(const ivec&) ;

     friend ivec min(const ivec&,const ivec&) ;
     friend ivec min(const ivec&,int) ;
     friend ivec min(int,const ivec&) ;

     friend ivec max(const ivec&,const ivec&) ;
     friend ivec max(const ivec&,int) ;
     friend ivec max(int,const ivec&) ;
    friend int dot(const ivec&,const ivec&) ;
    friend int prod(const ivec& x) ;
    friend int sum(const ivec& x) ;


     friend ivec operator+(const ivec&,const ivec&) ;
     friend ivec operator+(const ivec&,int) ;
     friend ivec operator+(int,const ivec&) ;


     ivec& operator+=(const ivec&);
     ivec& operator+=(int);


     friend ivec operator-(const ivec&,const ivec&) ;
     friend ivec operator-(const ivec&,int) ;
     friend ivec operator-(int,const ivec&) ;


     ivec& operator-=(const ivec&);
     ivec& operator-=(int);


     friend ivec operator*(const ivec&,const ivec&) ;
     friend ivec operator*(const ivec&,int) ;
     friend ivec operator*(int,const ivec&) ;


     ivec& operator*=(const ivec&);
     ivec& operator*=(int);


     friend ivec operator/(const ivec&,const ivec&) ;
     friend ivec operator/(const ivec&,int) ;
     friend ivec operator/(int,const ivec&) ;


     ivec& operator/=(const ivec&);
     ivec& operator/=(int);
    friend ivec operator-(const ivec& x) ;


     friend ivec operator^(const ivec&,const ivec&) ;
     friend ivec operator^(const ivec&,int) ;
     friend ivec operator^(int,const ivec&) ;


     ivec& operator^=(const ivec&);
     ivec& operator^=(int);


     friend ivec operator&(const ivec&,const ivec&) ;
     friend ivec operator&(const ivec&,int) ;
     friend ivec operator&(int,const ivec&) ;


     ivec& operator&=(const ivec&);
     ivec& operator&=(int);


     friend ivec operator|(const ivec&,const ivec&) ;
     friend ivec operator|(const ivec&,int) ;
     friend ivec operator|(int,const ivec&) ;


     ivec& operator|=(const ivec&);
     ivec& operator|=(int);

     friend ivec eqv(const ivec&,const ivec&) ;
     friend ivec eqv(const ivec&,int) ;
     friend ivec eqv(int,const ivec&) ;
    friend ivec operator~(const ivec&) ;

     friend ivec operator>=(const ivec&, const ivec&) ;
     friend ivec operator>=(const ivec&, int) ;
     friend ivec operator>=(int,const ivec&) ;

     friend ivec operator>(const ivec&, const ivec&) ;
     friend ivec operator>(const ivec&, int) ;
     friend ivec operator>(int,const ivec&) ;

     friend ivec operator<=(const ivec&, const ivec&) ;
     friend ivec operator<=(const ivec&, int) ;
     friend ivec operator<=(int,const ivec&) ;

     friend ivec operator<(const ivec&, const ivec&) ;
     friend ivec operator<(const ivec&, int) ;
     friend ivec operator<(int,const ivec&) ;

     friend ivec operator==(const ivec&, const ivec&) ;
     friend ivec operator==(const ivec&, int) ;
     friend ivec operator==(int,const ivec&) ;

     friend ivec operator!=(const ivec&, const ivec&) ;
     friend ivec operator!=(const ivec&, int) ;
     friend ivec operator!=(int,const ivec&) ;
    ivec& operator=(const ivec&);
    ivec& operator=(int);
    int& operator[](int i)
    {   if (i<origin || origin+sz<=i)
	   error(2,form("Vector index (%d) out of range: [%d-%d]",
		i,origin,origin+sz-1));
	Unique();
	return r->v[i-origin];
    }
    const int& operator[](int i) const
    {   if (i<origin || origin+sz<=i)
	   error(2,form("Vector index (%d) out of range: [%d-%d]",
		i,origin,origin+sz-1));
	return r->v[i-origin];
    }
    friend ostream& operator<<(ostream&,const ivec&) ;
    friend istream& operator>>(istream&,ivec&) ;
    ostream& ivec::BinaryWrite(ostream& s) const;
    istream& ivec::BinaryRead(istream &s,int nelem=-1);
    GPT sethandler(GPT);
};
 /* These routines need to be inline to avoid pulling in other vec types
   when only one is used */
inline ivec::ivec(const ivec& a)
{
    sz = a.sz;
    origin = a.origin;
    r = a.r;
    r->Inc();
}
inline ivec::ivec(const Subivec& a)
{
    sz = a.sz;
    origin = 0;
    r = new_ivec_Rep(sz);
    COPY(r->v,&a.it->r->v[a.offset],sz);
}
#endif
