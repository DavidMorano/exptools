 /* Vector library
 *
 * Brent Townshend (bst@alice)
 * AT&T Bell Laboratories
 * MH 2D-554 (201)582-4111
 * Version: @(#)vector.h.mac 1.2 88/12/07 14:39:09
 */
#ifndef svec_h
#define svec_h
#include <libc.h>
#include <generic.h>
#include <stream.h>
#include <ivec.h>
#ifdef alliant
extern "C"{
    void vec_bmov(char*,const char*,int);
}
inline void COPY(short *to,const short *from, int n)
    { vec_bmov((char *)to,(const char *)from,(n)*sizeof(short)); }
#else
#include <memory.h>
inline void mov(short *to,const short *from, int n)
    { memcpy(to,from,(n)*sizeof(short)); }
inline void COPY(short *to,const short *from, int n)
    { memcpy(to,from,(n)*sizeof(short)); }
#endif
class ucvec;
class cvec;
class svec;
class ivec;
class fvec;
class dvec;
class svec;
class svec_Rep;
extern svec_Rep *null_svec_Rep;
struct svec_Rep {
    int refc;
    int allocsz;
    short v[1];
    void Inc() { refc++; }
    void Dec() { refc--;
	    if ((refc == 0) && (this != null_svec_Rep))
		delete (char *)this;
	  }
    svec_Rep() { allocsz = 0; refc=0; }   /* Only used to create null_svec_Rep */
    friend svec_Rep *new_svec_Rep(const svec_Rep *old,int sz)
	{ svec_Rep *result = new_svec_Rep(sz);
	  COPY(result->v,old->v,sz);
	  return result; }
    friend svec_Rep *new_svec_Rep(int sz)
	{ if (sz==0) return null_svec_Rep;
	  else {
	  svec_Rep *result = (svec_Rep *)
		new char[(sz-1)*sizeof(short)+sizeof(svec_Rep)];
	  result->allocsz = sz;
	  result->refc = 1;
	  return result; } }
};
 /* A Subsvec are the same as a svec except that assignments into do not create
    a copy of the representation.  Thus changes to a Subsvec affect the original
	svec it was created from.
*/
class Subsvec {
    friend svec;
    svec *it;
    int offset;		 /* Offset in Rep for accesses */
    int sz;
    Subsvec(svec *old, int off, int len)
	{ it=old;offset=off;sz=len; }
public:
    Subsvec& operator=(const svec&);
    Subsvec& operator=(short);

     Subsvec& operator+=(const svec&);
     Subsvec& operator+=(short);

     Subsvec& operator-=(const svec&);
     Subsvec& operator-=(short);

     Subsvec& operator*=(const svec&);
     Subsvec& operator*=(short);

     Subsvec& operator/=(const svec&);
     Subsvec& operator/=(short);

     Subsvec& operator^=(const svec&);
     Subsvec& operator^=(short);

     Subsvec& operator&=(const svec&);
     Subsvec& operator&=(short);

     Subsvec& operator|=(const svec&);
     Subsvec& operator|=(short);
};
class svec {
    friend Subsvec;
    svec_Rep *r;
    int sz;		 /* Number of elements accessed by this vector */
    int origin;		 /* Origin of indexing */
    static GPT handler;
    void Unique()
	{ if (r->refc != 1) { r->Dec(); r = new_svec_Rep(r,sz);  } }
public:
    void error(int i,char* p) const
    {   if (handler)
	    (*handler)(i,p);
	else {
	    cerr << (p?p:"error in svec :") << i << "\n";
	    abort();
	    }
    }
    svec() { sz=origin=0; r = null_svec_Rep; }
    svec(int s)
    {	if (s<0) error(1,form("Bad vector size: %d",s));
	sz=s;
	origin = 0;
	r = new_svec_Rep(sz);
    }
    svec(int first,int last)
    {   if (last < first) error(1,form("Bad vector bounds: %d-%d",
	last,first));
	sz=last-first+1;
	origin = first;
	r = new_svec_Rep(sz);
    }
    svec(const Subsvec &old);
    ~svec() { r->Dec(); }
    svec(const ucvec&);
    svec(const cvec&);
    svec(const svec&);
    svec(const ivec&);
    svec(const fvec&);
    svec(const dvec&);
    operator const short*()
	{ return r->v; }  /* Need to be careful this doesn't get relocated */
    Subsvec operator()(int first,int last);
    Subsvec operator()(int first) { return((*this)(first,origin+sz-1)); }
    const Subsvec operator()(int first,int last) const;
    const Subsvec operator()(int first) const
	{ return((*this)(first,origin+sz-1)); }
    int size() const { return sz; }
    void set_size(int);
    int orig() const { return origin; }
    void set_orig(int x) { origin = x; }
    short& elem(int i)
	{ Unique();  return r->v[i]; }
    const short& GetElem(int i) const
	{ return r->v[i]; }
    friend int equal(const svec& left, const svec& right) ;
    friend svec abs(const svec&) ;
    friend short max(const svec&) ;
    friend short min(const svec&) ;

     friend svec min(const svec&,const svec&) ;
     friend svec min(const svec&,short) ;
     friend svec min(short,const svec&) ;

     friend svec max(const svec&,const svec&) ;
     friend svec max(const svec&,short) ;
     friend svec max(short,const svec&) ;
    friend short dot(const svec&,const svec&) ;
    friend short prod(const svec& x) ;
    friend short sum(const svec& x) ;


     friend svec operator+(const svec&,const svec&) ;
     friend svec operator+(const svec&,short) ;
     friend svec operator+(short,const svec&) ;


     svec& operator+=(const svec&);
     svec& operator+=(short);


     friend svec operator-(const svec&,const svec&) ;
     friend svec operator-(const svec&,short) ;
     friend svec operator-(short,const svec&) ;


     svec& operator-=(const svec&);
     svec& operator-=(short);


     friend svec operator*(const svec&,const svec&) ;
     friend svec operator*(const svec&,short) ;
     friend svec operator*(short,const svec&) ;


     svec& operator*=(const svec&);
     svec& operator*=(short);


     friend svec operator/(const svec&,const svec&) ;
     friend svec operator/(const svec&,short) ;
     friend svec operator/(short,const svec&) ;


     svec& operator/=(const svec&);
     svec& operator/=(short);
    friend svec operator-(const svec& x) ;


     friend svec operator^(const svec&,const svec&) ;
     friend svec operator^(const svec&,short) ;
     friend svec operator^(short,const svec&) ;


     svec& operator^=(const svec&);
     svec& operator^=(short);


     friend svec operator&(const svec&,const svec&) ;
     friend svec operator&(const svec&,short) ;
     friend svec operator&(short,const svec&) ;


     svec& operator&=(const svec&);
     svec& operator&=(short);


     friend svec operator|(const svec&,const svec&) ;
     friend svec operator|(const svec&,short) ;
     friend svec operator|(short,const svec&) ;


     svec& operator|=(const svec&);
     svec& operator|=(short);

     friend svec eqv(const svec&,const svec&) ;
     friend svec eqv(const svec&,short) ;
     friend svec eqv(short,const svec&) ;
    friend svec operator~(const svec&) ;

     friend ivec operator>=(const svec&, const svec&) ;
     friend ivec operator>=(const svec&, short) ;
     friend ivec operator>=(short,const svec&) ;

     friend ivec operator>(const svec&, const svec&) ;
     friend ivec operator>(const svec&, short) ;
     friend ivec operator>(short,const svec&) ;

     friend ivec operator<=(const svec&, const svec&) ;
     friend ivec operator<=(const svec&, short) ;
     friend ivec operator<=(short,const svec&) ;

     friend ivec operator<(const svec&, const svec&) ;
     friend ivec operator<(const svec&, short) ;
     friend ivec operator<(short,const svec&) ;

     friend ivec operator==(const svec&, const svec&) ;
     friend ivec operator==(const svec&, short) ;
     friend ivec operator==(short,const svec&) ;

     friend ivec operator!=(const svec&, const svec&) ;
     friend ivec operator!=(const svec&, short) ;
     friend ivec operator!=(short,const svec&) ;
    svec& operator=(const svec&);
    svec& operator=(short);
    short& operator[](int i)
    {   if (i<origin || origin+sz<=i)
	   error(2,form("Vector index (%d) out of range: [%d-%d]",
		i,origin,origin+sz-1));
	Unique();
	return r->v[i-origin];
    }
    const short& operator[](int i) const
    {   if (i<origin || origin+sz<=i)
	   error(2,form("Vector index (%d) out of range: [%d-%d]",
		i,origin,origin+sz-1));
	return r->v[i-origin];
    }
    friend ostream& operator<<(ostream&,const svec&) ;
    friend istream& operator>>(istream&,svec&) ;
    ostream& svec::BinaryWrite(ostream& s) const;
    istream& svec::BinaryRead(istream &s,int nelem=-1);
    GPT sethandler(GPT);
};
 /* These routines need to be inline to avoid pulling in other vec types
   when only one is used */
inline svec::svec(const svec& a)
{
    sz = a.sz;
    origin = a.origin;
    r = a.r;
    r->Inc();
}
inline svec::svec(const Subsvec& a)
{
    sz = a.sz;
    origin = 0;
    r = new_svec_Rep(sz);
    COPY(r->v,&a.it->r->v[a.offset],sz);
}
#endif
