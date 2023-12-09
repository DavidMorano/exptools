static char vector_sccsid[]="%Z%%M% %I% %E% %U% bst";
 /*
 * Vector library
 * Brent Townshend (bst@alice)
 * AT&T Bell Laboratories
 * MH 2D-554 (201)582-4111
 *
 */
#include <stream.h>
#define NOTRIOPS
#include <vectorops.h>
#include <ucvec.h>
#include <cvec.h>
#include <svec.h>
#include <ivec.h>
#include <fvec.h>
#include <dvec.h>
#include <fcxvec.h>
#include <dcxvec.h>
 inline void add(complex *result,const complex *a,const complex *b, int n)
     { add((double*)result,(const double*)a,(const double*)b,n*2); }
 inline void add(complex *result,complex a,const complex *b, int n)
     { add((double*)result,real(a),(const double*)b,n*2,2,2);
       add(((double*)result)+1,imag(a),((const double*)b+1),n*2,2,2); }
 inline void add(complex *result,const complex *a,complex b, int n)
     { add((double*)result,(const double*)a,real(b),n*2,2,2);
       add(((double*)result)+1,((const double*)a)+1,imag(b),n*2,2,2); }
 inline void sub(complex *result,const complex *a,const complex *b, int n)
     { sub((double*)result,(const double*)a,(const double*)b,n*2); }
 inline void sub(complex *result,complex a,const complex *b, int n)
     { sub((double*)result,real(a),(const double*)b,n*2,2,2);
       sub(((double*)result)+1,imag(a),((const double*)b+1),n*2,2,2); }
 inline void sub(complex *result,const complex *a,complex b, int n)
     { sub((double*)result,(const double*)a,real(b),n*2,2,2);
       sub(((double*)result)+1,((const double*)a)+1,imag(b),n*2,2,2); }
 inline void neg(complex *result,const complex *a, int n)
     { neg((double*)result,(const double*)a,n*2); }
 inline void mov(complex *result,const complex *a, int n)
     { mov((double*)result,(const double*)a,n*2); }
inline void set(complex *result,complex a, int n)
    { set((double*)result,real(a),n*2,2);
      set(((double*)result)+1,imag(a),n*2,2); }
static void div(complex *result,const complex *a,const complex *b, int n)
    { for (int i=0;i<n;i++) result[i] = a[i] /b[i]; }
static void div(complex *result,complex a,const complex *b, int n)
    { for (int i=0;i<n;i++) result[i] = a /b[i]; }
static void div(complex *result,const complex *a,complex b, int n)
    { for (int i=0;i<n;i++) result[i] = a[i] /b; }
static void mul(complex *result,const complex *a,const complex *b, int n)
    { for (int i=0;i<n;i++) result[i] = a[i]*b[i]; }
static void mul(complex *result,complex a,const complex *b, int n)
    { for (int i=0;i<n;i++) result[i] = a*b[i]; }
static void mul(complex *result,const complex *a,complex b, int n)
    { for (int i=0;i<n;i++) result[i] = a[i]*b; }
 complex sum(const dcxvec &x)
 {
     if (x.sz == 0) x.error(3,"Attempt to calculate sum of length 0 dcxvec");
     complex result=x.r->v[0];
     for (int i=1;i<x.sz;i++)
 	result+=x.r->v[i];
     return(result);
 }
 complex prod(const dcxvec &x)
 {
     if (x.sz == 0) x.error(3,"Attempt to calculate prod of length 0 dcxvec");
     complex result=x.r->v[0];
     for (int i=1;i<x.sz;i++)
 	result*=x.r->v[i];
     return(result);
 }

 dcxvec operator+(const dcxvec& left, const dcxvec& right)
 {
     if (right.sz != left.sz)
 	    left.error(3,form("Different dcxvec sizes in operator+ (%d operator+ %d)",
 		left.sz, right.sz));
     dcxvec result(left.sz);
     add(result.r->v,left.r->v,right.r->v,left.sz);
     return(result);
 }

 dcxvec operator+(complex left,const dcxvec& right)
 {
     dcxvec result(right.origin,right.origin+right.sz-1);
     add(result.r->v,left,right.r->v,right.sz);
     return(result);
 }

 dcxvec operator+(const dcxvec &left,complex right)
 {
     dcxvec result(left.origin,left.origin+left.sz-1);
     add(result.r->v,left.r->v,right,left.sz);
     return(result);
 }



 dcxvec& dcxvec::operator+=(const dcxvec& right)
 {
     if (right.sz != sz)
 	    error(3,form("Different dcxvec sizes in operator+= (%d operator+= %d)",
 		sz, right.sz));
     Unique();
     add(r->v,r->v,right.r->v,sz);
     return(*this);
 }

 dcxvec& dcxvec::operator+=(complex right)
 {
     Unique();
     add(r->v,r->v,right,sz);
     return(*this);
 }

 Subdcxvec& Subdcxvec::operator+=(const dcxvec& right)
 {
     if (right.sz != sz)
 	    right.error(3,form("Different dcxvec sizes in operator+= (%d operator+= %d)",
 		sz, right.sz));
     it->Unique();
     add(&it->r->v[offset],&it->r->v[offset],right.r->v,sz);
     return(*this);
 }

 Subdcxvec& Subdcxvec::operator+=(complex right)
 {
     it->Unique();
     add(&it->r->v[offset],&it->r->v[offset],right,sz);
     return(*this);
 }


 dcxvec operator-(const dcxvec& left, const dcxvec& right)
 {
     if (right.sz != left.sz)
 	    left.error(3,form("Different dcxvec sizes in operator- (%d operator- %d)",
 		left.sz, right.sz));
     dcxvec result(left.sz);
     sub(result.r->v,left.r->v,right.r->v,left.sz);
     return(result);
 }

 dcxvec operator-(complex left,const dcxvec& right)
 {
     dcxvec result(right.origin,right.origin+right.sz-1);
     sub(result.r->v,left,right.r->v,right.sz);
     return(result);
 }

 dcxvec operator-(const dcxvec &left,complex right)
 {
     dcxvec result(left.origin,left.origin+left.sz-1);
     sub(result.r->v,left.r->v,right,left.sz);
     return(result);
 }



 dcxvec& dcxvec::operator-=(const dcxvec& right)
 {
     if (right.sz != sz)
 	    error(3,form("Different dcxvec sizes in operator-= (%d operator-= %d)",
 		sz, right.sz));
     Unique();
     sub(r->v,r->v,right.r->v,sz);
     return(*this);
 }

 dcxvec& dcxvec::operator-=(complex right)
 {
     Unique();
     sub(r->v,r->v,right,sz);
     return(*this);
 }

 Subdcxvec& Subdcxvec::operator-=(const dcxvec& right)
 {
     if (right.sz != sz)
 	    right.error(3,form("Different dcxvec sizes in operator-= (%d operator-= %d)",
 		sz, right.sz));
     it->Unique();
     sub(&it->r->v[offset],&it->r->v[offset],right.r->v,sz);
     return(*this);
 }

 Subdcxvec& Subdcxvec::operator-=(complex right)
 {
     it->Unique();
     sub(&it->r->v[offset],&it->r->v[offset],right,sz);
     return(*this);
 }


 dcxvec operator/(const dcxvec& left, const dcxvec& right)
 {
     if (right.sz != left.sz)
 	    left.error(3,form("Different dcxvec sizes in operator/ (%d operator/ %d)",
 		left.sz, right.sz));
     dcxvec result(left.sz);
     div(result.r->v,left.r->v,right.r->v,left.sz);
     return(result);
 }

 dcxvec operator/(complex left,const dcxvec& right)
 {
     dcxvec result(right.origin,right.origin+right.sz-1);
     div(result.r->v,left,right.r->v,right.sz);
     return(result);
 }

 dcxvec operator/(const dcxvec &left,complex right)
 {
     dcxvec result(left.origin,left.origin+left.sz-1);
     div(result.r->v,left.r->v,right,left.sz);
     return(result);
 }



 dcxvec& dcxvec::operator/=(const dcxvec& right)
 {
     if (right.sz != sz)
 	    error(3,form("Different dcxvec sizes in operator/= (%d operator/= %d)",
 		sz, right.sz));
     Unique();
     div(r->v,r->v,right.r->v,sz);
     return(*this);
 }

 dcxvec& dcxvec::operator/=(complex right)
 {
     Unique();
     div(r->v,r->v,right,sz);
     return(*this);
 }

 Subdcxvec& Subdcxvec::operator/=(const dcxvec& right)
 {
     if (right.sz != sz)
 	    right.error(3,form("Different dcxvec sizes in operator/= (%d operator/= %d)",
 		sz, right.sz));
     it->Unique();
     div(&it->r->v[offset],&it->r->v[offset],right.r->v,sz);
     return(*this);
 }

 Subdcxvec& Subdcxvec::operator/=(complex right)
 {
     it->Unique();
     div(&it->r->v[offset],&it->r->v[offset],right,sz);
     return(*this);
 }


 dcxvec operator*(const dcxvec& left, const dcxvec& right)
 {
     if (right.sz != left.sz)
 	    left.error(3,form("Different dcxvec sizes in operator* (%d operator* %d)",
 		left.sz, right.sz));
     dcxvec result(left.sz);
     mul(result.r->v,left.r->v,right.r->v,left.sz);
     return(result);
 }

 dcxvec operator*(complex left,const dcxvec& right)
 {
     dcxvec result(right.origin,right.origin+right.sz-1);
     mul(result.r->v,left,right.r->v,right.sz);
     return(result);
 }

 dcxvec operator*(const dcxvec &left,complex right)
 {
     dcxvec result(left.origin,left.origin+left.sz-1);
     mul(result.r->v,left.r->v,right,left.sz);
     return(result);
 }



 dcxvec& dcxvec::operator*=(const dcxvec& right)
 {
     if (right.sz != sz)
 	    error(3,form("Different dcxvec sizes in operator*= (%d operator*= %d)",
 		sz, right.sz));
     Unique();
     mul(r->v,r->v,right.r->v,sz);
     return(*this);
 }

 dcxvec& dcxvec::operator*=(complex right)
 {
     Unique();
     mul(r->v,r->v,right,sz);
     return(*this);
 }

 Subdcxvec& Subdcxvec::operator*=(const dcxvec& right)
 {
     if (right.sz != sz)
 	    right.error(3,form("Different dcxvec sizes in operator*= (%d operator*= %d)",
 		sz, right.sz));
     it->Unique();
     mul(&it->r->v[offset],&it->r->v[offset],right.r->v,sz);
     return(*this);
 }

 Subdcxvec& Subdcxvec::operator*=(complex right)
 {
     it->Unique();
     mul(&it->r->v[offset],&it->r->v[offset],right,sz);
     return(*this);
 }

 dcxvec operator-(const dcxvec &x)
 {
     dcxvec result(x.origin,x.origin+x.sz-1);
     neg(result.r->v,x.r->v,x.sz);
     return(result);
 }
 ivec operator==(const dcxvec& left, const dcxvec& right)
 {
     if (right.size() != left.sz)
 	left.error(3,form("Different dcxvec sizes in operator== (%d operator== %d)",
 	    left.sz, right.size()));
     ivec result(left.sz);
     for (int i=0;i<left.sz;i++)
 	result[i] = left.r->v[i] == right.r->v[i];
     return(result);
 }

 ivec operator==(const dcxvec& left, complex right)
 {
     ivec result(left.sz);
     for (int i=0;i<left.sz;i++)
 	result[i] = left.r->v[i] == right;
     return(result);
 }

 ivec operator==(complex left,const dcxvec& right)
 {
     ivec result(right.size());
     for (int i=0;i<right.size();i++)
 	result[i] = left == right.r->v[i];
     return(result);
 }
 ivec operator!=(const dcxvec& left, const dcxvec& right)
 {
     if (right.size() != left.sz)
 	left.error(3,form("Different dcxvec sizes in operator!= (%d operator!= %d)",
 	    left.sz, right.size()));
     ivec result(left.sz);
     for (int i=0;i<left.sz;i++)
 	result[i] = left.r->v[i] != right.r->v[i];
     return(result);
 }

 ivec operator!=(const dcxvec& left, complex right)
 {
     ivec result(left.sz);
     for (int i=0;i<left.sz;i++)
 	result[i] = left.r->v[i] != right;
     return(result);
 }

 ivec operator!=(complex left,const dcxvec& right)
 {
     ivec result(right.size());
     for (int i=0;i<right.size();i++)
 	result[i] = left != right.r->v[i];
     return(result);
 }
 dvec real(const dcxvec& a)
 {
     dvec result(a.orig(),a.orig()+a.size()-1);
     for (int i=0;i<a.size();i++)
 	result[i+a.orig()] = real(a.GetElem(i));
     return result;
 }
 dvec imag(const dcxvec& a)
 {
     dvec result(a.orig(),a.orig()+a.size()-1);
     for (int i=0;i<a.size();i++)
 	result[i+a.orig()] = imag(a.GetElem(i));
     return result;
 }
 dvec arg(const dcxvec& a)
 {
     dvec result(a.orig(),a.orig()+a.size()-1);
     for (int i=0;i<a.size();i++)
 	result[i+a.orig()] = arg(a.GetElem(i));
     return result;
 }
 dvec abs(const dcxvec& a)
 {
     dvec result(a.orig(),a.orig()+a.size()-1);
     for (int i=0;i<a.size();i++)
 	result[i+a.orig()] = abs(a.GetElem(i));
     return result;
 }
 dvec norm(const dcxvec& a)
 {
     dvec result(a.orig(),a.orig()+a.size()-1);
     for (int i=0;i<a.size();i++)
 	result[i+a.orig()] = norm(a.GetElem(i));
     return result;
 }
 dcxvec conj(const dcxvec& a)
 {
     dcxvec result(a.origin,a.origin+a.sz-1);
     for (int i=0;i<a.sz;i++)
 	result.r->v[i] = conj(a.r->v[i]);
     return result;
 }
Subdcxvec dcxvec::operator()(int first, int last)
{
    if ((first < origin) || (first >= origin+sz))
	error(3,form("Bad first index for dcxvec::subvec (%d)",first));
    if ((last < origin) || (last >= origin+sz))
	error(3,form("Bad last index for dcxvec::subvec (%d)",last));
    if (last < first)
	error(3,form("First index > last index in dcxvec::subvec (%d>%d)",
		first,last));
    return Subdcxvec(this, first-origin, last-first+1);
}
const Subdcxvec dcxvec::operator()(int first, int last) const
{
    if ((first < origin) || (first >= origin+sz))
	error(3,form("Bad first index for dcxvec::subvec (%d)",first));
    if ((last < origin) || (last >= origin+sz))
	error(3,form("Bad last index for dcxvec::subvec (%d)",last));
    if (last < first)
	error(3,form("First index > last index in dcxvec::subvec (%d>%d)",
		first,last));
    return Subdcxvec((dcxvec *)this, first-origin, last-first+1);
}
dcxvec& dcxvec::operator=(const dcxvec& right)
{
    if (this == &right)
	return(*this);
    if (right.sz != sz)	{
	set_size(right.sz);
	}
    origin = right.origin;
    r->Dec();
    r = right.r;
    r->Inc();
    return(*this);
}
dcxvec& dcxvec::operator=(complex right)
{
    Unique();
    set(r->v,right,sz);
    return(*this);
}
Subdcxvec& Subdcxvec::operator=(const dcxvec& right)
{
    if (right.sz != sz)	{
	it->error(3,form("Different dcxvec sizes in OP= (%d OP= %d)",
	    sz, right.sz));
	}
    it->Unique();
    mov(&it->r->v[offset],right.r->v,sz);
    return(*this);
}
Subdcxvec& Subdcxvec::operator=(complex right)
{
    it->Unique();
    set(&it->r->v[offset],right,sz);
    return(*this);
}
void dcxvec::set_size(int s)
{
    if (s<0) error(4,"set_size: bad new dcxvec size");
    if (s > r->allocsz) {
	dcxvec_Rep *newrep = new_dcxvec_Rep(s);
	mov(newrep->v,r->v,sz);
	r->Dec();
	r = newrep;
	}
    sz = s;
}
GPT dcxvec::sethandler(GPT a)
{
    GPT oo = handler;
    handler = a;
    return oo;
}
ostream& operator<<(ostream& s,const dcxvec& it)
{
    s << "[ ";
    if (it.sz)
	s << it.r->v[0];
    for (int i=1;i<it.sz;i++)
	s << " " << it.r->v[i];
    s << "]";
    return(s);
}
istream& operator>>(istream& s,dcxvec& it)
{
    char c;
    s >> c;
    if (c == '[') {
	int i;
	for (i=0;;i++) {
	    s >> c;
	    if (c == ']')
		break;
	    (void)s.putback(c);
	    if (i >= it.sz)
		it.set_size(it.sz+100);
	    s >> it.r->v[i];
	    }
	it.set_size(i);
	}
    else {
	(void)s.putback(c);
	for (int i=0;i<it.sz;i++)
	    s >> it.r->v[i];
	}
    return(s);
}
ostream& dcxvec::BinaryWrite(ostream& s) const
{
    if (sz)
	s.write((char *)r->v,sizeof(r->v[0])*sz);
    return s;
}
istream& dcxvec::BinaryRead(istream &s,int nelem)
{
    if (nelem == -1) {
	const int BufSize = 8192;
	struct MList { MList *next; char *buf; };
	MList *BHead= new MList;
	BHead->next = 0;
	MList *BEnd=BHead;
	int n = 0;
	while (s) {
	    BEnd->buf = new char[BufSize];
	    s.read(BEnd->buf,BufSize);
	    if (s) {
		BEnd->next = new MList;
		BEnd = BEnd->next;
		n += BufSize;
		}
	    else
		n += s.gcount();
	    }
	 /* Clear fail bit, just leave eof set */
	if (s.fail())
	    s.clear(s.rdstate()&(~ios::failbit));
	set_size(n /sizeof(r->v[0]));
	char *vptr = (char *)r->v;
	 /* Copy buffers into vector */
	for (MList *bptr=BHead;bptr!=BEnd;vptr+=BufSize) {
	    memcpy(vptr,bptr->buf,BufSize);
	    MList *nxt = bptr->next;
	    delete bptr->buf;
	    delete bptr;
	    bptr = nxt;
	    }
	 /* Copy last partially full buffer */
	memcpy(vptr,bptr->buf,size()*sizeof(r->v[0])-(vptr-(char*)r->v));
	delete bptr->buf;
	delete bptr;
	}
    else {
	set_size(nelem);
	s.read((char *)r->v,sizeof(r->v[0])*nelem);
	if (s.eof())
	    set_size(s.gcount() /sizeof(r->v[0]));
	}
    return s;
}
int equal(const dcxvec& left, const dcxvec& right)
{
    if (right.size() != left.size())
	return 0;
    for (int i=0;i<right.size();i++)
	if (left.r->v[i] != right.r->v[i])
	    return 0;
    return 1;
}
complex dot(const dcxvec& left, const dcxvec& right)
{
    if (right.sz != left.sz)
	left.error(3,form("Different dcxvec sizes in dot (%d and %d)",
	    left.sz, right.sz));
    complex result=0;
    for (int i=0;i<left.sz;i++) result += left.r->v[i]*right.r->v[i];
    return(result);
}
/**//**/
