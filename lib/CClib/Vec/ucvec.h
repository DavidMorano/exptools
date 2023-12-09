 /* Vector library
 *
 * Brent Townshend (bst@alice)
 * AT&T Bell Laboratories
 * MH 2D-554 (201)582-4111
 * Version: @(#)vector.h.mac 1.2 88/12/07 14:39:09
 */
#ifndef ucvec_h
#define ucvec_h
#include <libc.h>
#include <generic.h>
#include <stream.h>
#include <ivec.h>
#ifdef alliant
extern "C"{
    void vec_bmov(char*,const char*,int);
}
inline void COPY(unsigned char *to,const unsigned char *from, int n)
    { vec_bmov((char *)to,(const char *)from,(n)*sizeof(unsigned char)); }
#else
#include <memory.h>
inline void mov(unsigned char *to,const unsigned char *from, int n)
    { memcpy(to,from,(n)*sizeof(unsigned char)); }
inline void COPY(unsigned char *to,const unsigned char *from, int n)
    { memcpy(to,from,(n)*sizeof(unsigned char)); }
#endif
class ucvec;
class cvec;
class svec;
class ivec;
class fvec;
class dvec;
class ucvec;
class ucvec_Rep;
extern ucvec_Rep *null_ucvec_Rep;
struct ucvec_Rep {
    int refc;
    int allocsz;
    unsigned char v[1];
    void Inc() { refc++; }
    void Dec() { refc--;
	    if ((refc == 0) && (this != null_ucvec_Rep))
		delete (char *)this;
	  }
    ucvec_Rep() { allocsz = 0; refc=0; }   /* Only used to create null_ucvec_Rep */
    friend ucvec_Rep *new_ucvec_Rep(const ucvec_Rep *old,int sz)
	{ ucvec_Rep *result = new_ucvec_Rep(sz);
	  COPY(result->v,old->v,sz);
	  return result; }
    friend ucvec_Rep *new_ucvec_Rep(int sz)
	{ if (sz==0) return null_ucvec_Rep;
	  else {
	  ucvec_Rep *result = (ucvec_Rep *)
		new char[(sz-1)*sizeof(unsigned char)+sizeof(ucvec_Rep)];
	  result->allocsz = sz;
	  result->refc = 1;
	  return result; } }
};
 /* A Subucvec are the same as a ucvec except that assignments into do not create
    a copy of the representation.  Thus changes to a Subucvec affect the original
	ucvec it was created from.
*/
class Subucvec {
    friend ucvec;
    ucvec *it;
    int offset;		 /* Offset in Rep for accesses */
    int sz;
    Subucvec(ucvec *old, int off, int len)
	{ it=old;offset=off;sz=len; }
public:
    Subucvec& operator=(const ucvec&);
    Subucvec& operator=(unsigned char);

     Subucvec& operator+=(const ucvec&);
     Subucvec& operator+=(unsigned char);

     Subucvec& operator-=(const ucvec&);
     Subucvec& operator-=(unsigned char);

     Subucvec& operator*=(const ucvec&);
     Subucvec& operator*=(unsigned char);

     Subucvec& operator/=(const ucvec&);
     Subucvec& operator/=(unsigned char);

     Subucvec& operator^=(const ucvec&);
     Subucvec& operator^=(unsigned char);

     Subucvec& operator&=(const ucvec&);
     Subucvec& operator&=(unsigned char);

     Subucvec& operator|=(const ucvec&);
     Subucvec& operator|=(unsigned char);
};
class ucvec {
    friend Subucvec;
    ucvec_Rep *r;
    int sz;		 /* Number of elements accessed by this vector */
    int origin;		 /* Origin of indexing */
    static GPT handler;
    void Unique()
	{ if (r->refc != 1) { r->Dec(); r = new_ucvec_Rep(r,sz);  } }
public:
    void error(int i,char* p) const
    {   if (handler)
	    (*handler)(i,p);
	else {
	    cerr << (p?p:"error in ucvec :") << i << "\n";
	    abort();
	    }
    }
    ucvec() { sz=origin=0; r = null_ucvec_Rep; }
    ucvec(int s)
    {	if (s<0) error(1,form("Bad vector size: %d",s));
	sz=s;
	origin = 0;
	r = new_ucvec_Rep(sz);
    }
    ucvec(int first,int last)
    {   if (last < first) error(1,form("Bad vector bounds: %d-%d",
	last,first));
	sz=last-first+1;
	origin = first;
	r = new_ucvec_Rep(sz);
    }
    ucvec(const Subucvec &old);
    ~ucvec() { r->Dec(); }
    ucvec(const ucvec&);
    ucvec(const cvec&);
    ucvec(const svec&);
    ucvec(const ivec&);
    ucvec(const fvec&);
    ucvec(const dvec&);
    operator const unsigned char*()
	{ return r->v; }  /* Need to be careful this doesn't get relocated */
    Subucvec operator()(int first,int last);
    Subucvec operator()(int first) { return((*this)(first,origin+sz-1)); }
    const Subucvec operator()(int first,int last) const;
    const Subucvec operator()(int first) const
	{ return((*this)(first,origin+sz-1)); }
    int size() const { return sz; }
    void set_size(int);
    int orig() const { return origin; }
    void set_orig(int x) { origin = x; }
    unsigned char& elem(int i)
	{ Unique();  return r->v[i]; }
    const unsigned char& GetElem(int i) const
	{ return r->v[i]; }
    friend int equal(const ucvec& left, const ucvec& right) ;
    friend unsigned char max(const ucvec&) ;
    friend unsigned char min(const ucvec&) ;

     friend ucvec min(const ucvec&,const ucvec&) ;
     friend ucvec min(const ucvec&,unsigned char) ;
     friend ucvec min(unsigned char,const ucvec&) ;

     friend ucvec max(const ucvec&,const ucvec&) ;
     friend ucvec max(const ucvec&,unsigned char) ;
     friend ucvec max(unsigned char,const ucvec&) ;
    friend unsigned char dot(const ucvec&,const ucvec&) ;
    friend unsigned char prod(const ucvec& x) ;
    friend unsigned char sum(const ucvec& x) ;


     friend ucvec operator+(const ucvec&,const ucvec&) ;
     friend ucvec operator+(const ucvec&,unsigned char) ;
     friend ucvec operator+(unsigned char,const ucvec&) ;


     ucvec& operator+=(const ucvec&);
     ucvec& operator+=(unsigned char);


     friend ucvec operator-(const ucvec&,const ucvec&) ;
     friend ucvec operator-(const ucvec&,unsigned char) ;
     friend ucvec operator-(unsigned char,const ucvec&) ;


     ucvec& operator-=(const ucvec&);
     ucvec& operator-=(unsigned char);


     friend ucvec operator*(const ucvec&,const ucvec&) ;
     friend ucvec operator*(const ucvec&,unsigned char) ;
     friend ucvec operator*(unsigned char,const ucvec&) ;


     ucvec& operator*=(const ucvec&);
     ucvec& operator*=(unsigned char);


     friend ucvec operator/(const ucvec&,const ucvec&) ;
     friend ucvec operator/(const ucvec&,unsigned char) ;
     friend ucvec operator/(unsigned char,const ucvec&) ;


     ucvec& operator/=(const ucvec&);
     ucvec& operator/=(unsigned char);


     friend ucvec operator^(const ucvec&,const ucvec&) ;
     friend ucvec operator^(const ucvec&,unsigned char) ;
     friend ucvec operator^(unsigned char,const ucvec&) ;


     ucvec& operator^=(const ucvec&);
     ucvec& operator^=(unsigned char);


     friend ucvec operator&(const ucvec&,const ucvec&) ;
     friend ucvec operator&(const ucvec&,unsigned char) ;
     friend ucvec operator&(unsigned char,const ucvec&) ;


     ucvec& operator&=(const ucvec&);
     ucvec& operator&=(unsigned char);


     friend ucvec operator|(const ucvec&,const ucvec&) ;
     friend ucvec operator|(const ucvec&,unsigned char) ;
     friend ucvec operator|(unsigned char,const ucvec&) ;


     ucvec& operator|=(const ucvec&);
     ucvec& operator|=(unsigned char);

     friend ucvec eqv(const ucvec&,const ucvec&) ;
     friend ucvec eqv(const ucvec&,unsigned char) ;
     friend ucvec eqv(unsigned char,const ucvec&) ;
    friend ucvec operator~(const ucvec&) ;

     friend ivec operator>=(const ucvec&, const ucvec&) ;
     friend ivec operator>=(const ucvec&, unsigned char) ;
     friend ivec operator>=(unsigned char,const ucvec&) ;

     friend ivec operator>(const ucvec&, const ucvec&) ;
     friend ivec operator>(const ucvec&, unsigned char) ;
     friend ivec operator>(unsigned char,const ucvec&) ;

     friend ivec operator<=(const ucvec&, const ucvec&) ;
     friend ivec operator<=(const ucvec&, unsigned char) ;
     friend ivec operator<=(unsigned char,const ucvec&) ;

     friend ivec operator<(const ucvec&, const ucvec&) ;
     friend ivec operator<(const ucvec&, unsigned char) ;
     friend ivec operator<(unsigned char,const ucvec&) ;

     friend ivec operator==(const ucvec&, const ucvec&) ;
     friend ivec operator==(const ucvec&, unsigned char) ;
     friend ivec operator==(unsigned char,const ucvec&) ;

     friend ivec operator!=(const ucvec&, const ucvec&) ;
     friend ivec operator!=(const ucvec&, unsigned char) ;
     friend ivec operator!=(unsigned char,const ucvec&) ;
    ucvec& operator=(const ucvec&);
    ucvec& operator=(unsigned char);
    unsigned char& operator[](int i)
    {   if (i<origin || origin+sz<=i)
	   error(2,form("Vector index (%d) out of range: [%d-%d]",
		i,origin,origin+sz-1));
	Unique();
	return r->v[i-origin];
    }
    const unsigned char& operator[](int i) const
    {   if (i<origin || origin+sz<=i)
	   error(2,form("Vector index (%d) out of range: [%d-%d]",
		i,origin,origin+sz-1));
	return r->v[i-origin];
    }
    friend ostream& operator<<(ostream&,const ucvec&) ;
    friend istream& operator>>(istream&,ucvec&) ;
    ostream& ucvec::BinaryWrite(ostream& s) const;
    istream& ucvec::BinaryRead(istream &s,int nelem=-1);
    GPT sethandler(GPT);
};
 /* These routines need to be inline to avoid pulling in other vec types
   when only one is used */
inline ucvec::ucvec(const ucvec& a)
{
    sz = a.sz;
    origin = a.origin;
    r = a.r;
    r->Inc();
}
inline ucvec::ucvec(const Subucvec& a)
{
    sz = a.sz;
    origin = 0;
    r = new_ucvec_Rep(sz);
    COPY(r->v,&a.it->r->v[a.offset],sz);
}
#endif
