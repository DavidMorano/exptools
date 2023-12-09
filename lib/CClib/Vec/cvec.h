 /* Vector library
 *
 * Brent Townshend (bst@alice)
 * AT&T Bell Laboratories
 * MH 2D-554 (201)582-4111
 * Version: @(#)vector.h.mac 1.2 88/12/07 14:39:09
 */
#ifndef cvec_h
#define cvec_h
#include <libc.h>
#include <generic.h>
#include <stream.h>
#include <ivec.h>
#ifdef alliant
extern "C"{
    void vec_bmov(char*,const char*,int);
}
inline void COPY(char *to,const char *from, int n)
    { vec_bmov((char *)to,(const char *)from,(n)*sizeof(char)); }
#else
#include <memory.h>
inline void mov(char *to,const char *from, int n)
    { memcpy(to,from,(n)*sizeof(char)); }
inline void COPY(char *to,const char *from, int n)
    { memcpy(to,from,(n)*sizeof(char)); }
#endif
class ucvec;
class cvec;
class svec;
class ivec;
class fvec;
class dvec;
class cvec;
class cvec_Rep;
extern cvec_Rep *null_cvec_Rep;
struct cvec_Rep {
    int refc;
    int allocsz;
    char v[1];
    void Inc() { refc++; }
    void Dec() { refc--;
	    if ((refc == 0) && (this != null_cvec_Rep))
		delete (char *)this;
	  }
    cvec_Rep() { allocsz = 0; refc=0; }   /* Only used to create null_cvec_Rep */
    friend cvec_Rep *new_cvec_Rep(const cvec_Rep *old,int sz)
	{ cvec_Rep *result = new_cvec_Rep(sz);
	  COPY(result->v,old->v,sz);
	  return result; }
    friend cvec_Rep *new_cvec_Rep(int sz)
	{ if (sz==0) return null_cvec_Rep;
	  else {
	  cvec_Rep *result = (cvec_Rep *)
		new char[(sz-1)*sizeof(char)+sizeof(cvec_Rep)];
	  result->allocsz = sz;
	  result->refc = 1;
	  return result; } }
};
 /* A Subcvec are the same as a cvec except that assignments into do not create
    a copy of the representation.  Thus changes to a Subcvec affect the original
	cvec it was created from.
*/
class Subcvec {
    friend cvec;
    cvec *it;
    int offset;		 /* Offset in Rep for accesses */
    int sz;
    Subcvec(cvec *old, int off, int len)
	{ it=old;offset=off;sz=len; }
public:
    Subcvec& operator=(const cvec&);
    Subcvec& operator=(char);

     Subcvec& operator+=(const cvec&);
     Subcvec& operator+=(char);

     Subcvec& operator-=(const cvec&);
     Subcvec& operator-=(char);

     Subcvec& operator*=(const cvec&);
     Subcvec& operator*=(char);

     Subcvec& operator/=(const cvec&);
     Subcvec& operator/=(char);

     Subcvec& operator^=(const cvec&);
     Subcvec& operator^=(char);

     Subcvec& operator&=(const cvec&);
     Subcvec& operator&=(char);

     Subcvec& operator|=(const cvec&);
     Subcvec& operator|=(char);
};
class cvec {
    friend Subcvec;
    cvec_Rep *r;
    int sz;		 /* Number of elements accessed by this vector */
    int origin;		 /* Origin of indexing */
    static GPT handler;
    void Unique()
	{ if (r->refc != 1) { r->Dec(); r = new_cvec_Rep(r,sz);  } }
public:
    void error(int i,char* p) const
    {   if (handler)
	    (*handler)(i,p);
	else {
	    cerr << (p?p:"error in cvec :") << i << "\n";
	    abort();
	    }
    }
    cvec() { sz=origin=0; r = null_cvec_Rep; }
    cvec(int s)
    {	if (s<0) error(1,form("Bad vector size: %d",s));
	sz=s;
	origin = 0;
	r = new_cvec_Rep(sz);
    }
    cvec(int first,int last)
    {   if (last < first) error(1,form("Bad vector bounds: %d-%d",
	last,first));
	sz=last-first+1;
	origin = first;
	r = new_cvec_Rep(sz);
    }
    cvec(const Subcvec &old);
    ~cvec() { r->Dec(); }
    cvec(const ucvec&);
    cvec(const cvec&);
    cvec(const svec&);
    cvec(const ivec&);
    cvec(const fvec&);
    cvec(const dvec&);
    operator const char*()
	{ return r->v; }  /* Need to be careful this doesn't get relocated */
    Subcvec operator()(int first,int last);
    Subcvec operator()(int first) { return((*this)(first,origin+sz-1)); }
    const Subcvec operator()(int first,int last) const;
    const Subcvec operator()(int first) const
	{ return((*this)(first,origin+sz-1)); }
    int size() const { return sz; }
    void set_size(int);
    int orig() const { return origin; }
    void set_orig(int x) { origin = x; }
    char& elem(int i)
	{ Unique();  return r->v[i]; }
    const char& GetElem(int i) const
	{ return r->v[i]; }
    friend int equal(const cvec& left, const cvec& right) ;
    friend cvec abs(const cvec&) ;
    friend char max(const cvec&) ;
    friend char min(const cvec&) ;

     friend cvec min(const cvec&,const cvec&) ;
     friend cvec min(const cvec&,char) ;
     friend cvec min(char,const cvec&) ;

     friend cvec max(const cvec&,const cvec&) ;
     friend cvec max(const cvec&,char) ;
     friend cvec max(char,const cvec&) ;
    friend char dot(const cvec&,const cvec&) ;
    friend char prod(const cvec& x) ;
    friend char sum(const cvec& x) ;


     friend cvec operator+(const cvec&,const cvec&) ;
     friend cvec operator+(const cvec&,char) ;
     friend cvec operator+(char,const cvec&) ;


     cvec& operator+=(const cvec&);
     cvec& operator+=(char);


     friend cvec operator-(const cvec&,const cvec&) ;
     friend cvec operator-(const cvec&,char) ;
     friend cvec operator-(char,const cvec&) ;


     cvec& operator-=(const cvec&);
     cvec& operator-=(char);


     friend cvec operator*(const cvec&,const cvec&) ;
     friend cvec operator*(const cvec&,char) ;
     friend cvec operator*(char,const cvec&) ;


     cvec& operator*=(const cvec&);
     cvec& operator*=(char);


     friend cvec operator/(const cvec&,const cvec&) ;
     friend cvec operator/(const cvec&,char) ;
     friend cvec operator/(char,const cvec&) ;


     cvec& operator/=(const cvec&);
     cvec& operator/=(char);
    friend cvec operator-(const cvec& x) ;


     friend cvec operator^(const cvec&,const cvec&) ;
     friend cvec operator^(const cvec&,char) ;
     friend cvec operator^(char,const cvec&) ;


     cvec& operator^=(const cvec&);
     cvec& operator^=(char);


     friend cvec operator&(const cvec&,const cvec&) ;
     friend cvec operator&(const cvec&,char) ;
     friend cvec operator&(char,const cvec&) ;


     cvec& operator&=(const cvec&);
     cvec& operator&=(char);


     friend cvec operator|(const cvec&,const cvec&) ;
     friend cvec operator|(const cvec&,char) ;
     friend cvec operator|(char,const cvec&) ;


     cvec& operator|=(const cvec&);
     cvec& operator|=(char);

     friend cvec eqv(const cvec&,const cvec&) ;
     friend cvec eqv(const cvec&,char) ;
     friend cvec eqv(char,const cvec&) ;
    friend cvec operator~(const cvec&) ;

     friend ivec operator>=(const cvec&, const cvec&) ;
     friend ivec operator>=(const cvec&, char) ;
     friend ivec operator>=(char,const cvec&) ;

     friend ivec operator>(const cvec&, const cvec&) ;
     friend ivec operator>(const cvec&, char) ;
     friend ivec operator>(char,const cvec&) ;

     friend ivec operator<=(const cvec&, const cvec&) ;
     friend ivec operator<=(const cvec&, char) ;
     friend ivec operator<=(char,const cvec&) ;

     friend ivec operator<(const cvec&, const cvec&) ;
     friend ivec operator<(const cvec&, char) ;
     friend ivec operator<(char,const cvec&) ;

     friend ivec operator==(const cvec&, const cvec&) ;
     friend ivec operator==(const cvec&, char) ;
     friend ivec operator==(char,const cvec&) ;

     friend ivec operator!=(const cvec&, const cvec&) ;
     friend ivec operator!=(const cvec&, char) ;
     friend ivec operator!=(char,const cvec&) ;
    cvec& operator=(const cvec&);
    cvec& operator=(char);
    char& operator[](int i)
    {   if (i<origin || origin+sz<=i)
	   error(2,form("Vector index (%d) out of range: [%d-%d]",
		i,origin,origin+sz-1));
	Unique();
	return r->v[i-origin];
    }
    const char& operator[](int i) const
    {   if (i<origin || origin+sz<=i)
	   error(2,form("Vector index (%d) out of range: [%d-%d]",
		i,origin,origin+sz-1));
	return r->v[i-origin];
    }
    friend ostream& operator<<(ostream&,const cvec&) ;
    friend istream& operator>>(istream&,cvec&) ;
    ostream& cvec::BinaryWrite(ostream& s) const;
    istream& cvec::BinaryRead(istream &s,int nelem=-1);
    GPT sethandler(GPT);
};
 /* These routines need to be inline to avoid pulling in other vec types
   when only one is used */
inline cvec::cvec(const cvec& a)
{
    sz = a.sz;
    origin = a.origin;
    r = a.r;
    r->Inc();
}
inline cvec::cvec(const Subcvec& a)
{
    sz = a.sz;
    origin = 0;
    r = new_cvec_Rep(sz);
    COPY(r->v,&a.it->r->v[a.offset],sz);
}
#endif
