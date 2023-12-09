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
 ucvec min(const ucvec& left, const ucvec& right)
 {
     if (right.sz != left.sz)
 	    left.error(3,form("Different ucvec sizes in min (%d min %d)",
 		left.sz, right.sz));
     ucvec result(left.sz);
     for (int i=0;i<left.sz;i++)
 	result.r->v[i] = left.r->v[i] < right.r->v[i] ? left.r->v[i]: right.r->v[i];
     return(result);
 }

 ucvec min(const ucvec& left, unsigned char right)
 {
     ucvec result(left.origin,left.origin+left.sz-1);
     for (int i=0;i<left.sz;i++)
 	result.r->v[i] = left.r->v[i] < right ? left.r->v[i]: right;
     return(result);
 }

 ucvec min(unsigned char left,const ucvec& right)
 {
     ucvec result(right.origin,right.origin+right.sz-1);
     for (int i=0;i<right.sz;i++)
 	result.r->v[i] = left < right.r->v[i] ? left : right.r->v[i];
     return(result);
 }
 ucvec max(const ucvec& left, const ucvec& right)
 {
     if (right.sz != left.sz)
 	    left.error(3,form("Different ucvec sizes in max (%d max %d)",
 		left.sz, right.sz));
     ucvec result(left.sz);
     for (int i=0;i<left.sz;i++)
 	result.r->v[i] = left.r->v[i] > right.r->v[i] ? left.r->v[i]: right.r->v[i];
     return(result);
 }

 ucvec max(const ucvec& left, unsigned char right)
 {
     ucvec result(left.origin,left.origin+left.sz-1);
     for (int i=0;i<left.sz;i++)
 	result.r->v[i] = left.r->v[i] > right ? left.r->v[i]: right;
     return(result);
 }

 ucvec max(unsigned char left,const ucvec& right)
 {
     ucvec result(right.origin,right.origin+right.sz-1);
     for (int i=0;i<right.sz;i++)
 	result.r->v[i] = left > right.r->v[i] ? left : right.r->v[i];
     return(result);
 }
 unsigned char max(const ucvec &x)
 {
     if (x.sz == 0) x.error(3,"Attempt to calculate max of length 0 ucvec");
     unsigned char result=x.r->v[0];
     for (int i=1;i<x.sz;i++)
 	if(x.r->v[i]>result)result=x.r->v[i];
     return(result);
 }
 unsigned char min(const ucvec &x)
 {
     if (x.sz == 0) x.error(3,"Attempt to calculate min of length 0 ucvec");
     unsigned char result=x.r->v[0];
     for (int i=1;i<x.sz;i++)
 	if(x.r->v[i]<result)result=x.r->v[i];
     return(result);
 }
 unsigned char sum(const ucvec &x)
 {
     if (x.sz == 0) x.error(3,"Attempt to calculate sum of length 0 ucvec");
     unsigned char result=x.r->v[0];
     for (int i=1;i<x.sz;i++)
 	result+=x.r->v[i];
     return(result);
 }
 unsigned char prod(const ucvec &x)
 {
     if (x.sz == 0) x.error(3,"Attempt to calculate prod of length 0 ucvec");
     unsigned char result=x.r->v[0];
     for (int i=1;i<x.sz;i++)
 	result*=x.r->v[i];
     return(result);
 }

 ucvec operator+(const ucvec& left, const ucvec& right)
 {
     if (right.sz != left.sz)
 	    left.error(3,form("Different ucvec sizes in operator+ (%d operator+ %d)",
 		left.sz, right.sz));
     ucvec result(left.sz);
     add(result.r->v,left.r->v,right.r->v,left.sz);
     return(result);
 }

 ucvec operator+(unsigned char left,const ucvec& right)
 {
     ucvec result(right.origin,right.origin+right.sz-1);
     add(result.r->v,left,right.r->v,right.sz);
     return(result);
 }

 ucvec operator+(const ucvec &left,unsigned char right)
 {
     ucvec result(left.origin,left.origin+left.sz-1);
     add(result.r->v,left.r->v,right,left.sz);
     return(result);
 }



 ucvec& ucvec::operator+=(const ucvec& right)
 {
     if (right.sz != sz)
 	    error(3,form("Different ucvec sizes in operator+= (%d operator+= %d)",
 		sz, right.sz));
     Unique();
     add(r->v,r->v,right.r->v,sz);
     return(*this);
 }

 ucvec& ucvec::operator+=(unsigned char right)
 {
     Unique();
     add(r->v,r->v,right,sz);
     return(*this);
 }

 Subucvec& Subucvec::operator+=(const ucvec& right)
 {
     if (right.sz != sz)
 	    right.error(3,form("Different ucvec sizes in operator+= (%d operator+= %d)",
 		sz, right.sz));
     it->Unique();
     add(&it->r->v[offset],&it->r->v[offset],right.r->v,sz);
     return(*this);
 }

 Subucvec& Subucvec::operator+=(unsigned char right)
 {
     it->Unique();
     add(&it->r->v[offset],&it->r->v[offset],right,sz);
     return(*this);
 }


 ucvec operator-(const ucvec& left, const ucvec& right)
 {
     if (right.sz != left.sz)
 	    left.error(3,form("Different ucvec sizes in operator- (%d operator- %d)",
 		left.sz, right.sz));
     ucvec result(left.sz);
     sub(result.r->v,left.r->v,right.r->v,left.sz);
     return(result);
 }

 ucvec operator-(unsigned char left,const ucvec& right)
 {
     ucvec result(right.origin,right.origin+right.sz-1);
     sub(result.r->v,left,right.r->v,right.sz);
     return(result);
 }

 ucvec operator-(const ucvec &left,unsigned char right)
 {
     ucvec result(left.origin,left.origin+left.sz-1);
     sub(result.r->v,left.r->v,right,left.sz);
     return(result);
 }



 ucvec& ucvec::operator-=(const ucvec& right)
 {
     if (right.sz != sz)
 	    error(3,form("Different ucvec sizes in operator-= (%d operator-= %d)",
 		sz, right.sz));
     Unique();
     sub(r->v,r->v,right.r->v,sz);
     return(*this);
 }

 ucvec& ucvec::operator-=(unsigned char right)
 {
     Unique();
     sub(r->v,r->v,right,sz);
     return(*this);
 }

 Subucvec& Subucvec::operator-=(const ucvec& right)
 {
     if (right.sz != sz)
 	    right.error(3,form("Different ucvec sizes in operator-= (%d operator-= %d)",
 		sz, right.sz));
     it->Unique();
     sub(&it->r->v[offset],&it->r->v[offset],right.r->v,sz);
     return(*this);
 }

 Subucvec& Subucvec::operator-=(unsigned char right)
 {
     it->Unique();
     sub(&it->r->v[offset],&it->r->v[offset],right,sz);
     return(*this);
 }


 ucvec operator/(const ucvec& left, const ucvec& right)
 {
     if (right.sz != left.sz)
 	    left.error(3,form("Different ucvec sizes in operator/ (%d operator/ %d)",
 		left.sz, right.sz));
     ucvec result(left.sz);
     div(result.r->v,left.r->v,right.r->v,left.sz);
     return(result);
 }

 ucvec operator/(unsigned char left,const ucvec& right)
 {
     ucvec result(right.origin,right.origin+right.sz-1);
     div(result.r->v,left,right.r->v,right.sz);
     return(result);
 }

 ucvec operator/(const ucvec &left,unsigned char right)
 {
     ucvec result(left.origin,left.origin+left.sz-1);
     div(result.r->v,left.r->v,right,left.sz);
     return(result);
 }



 ucvec& ucvec::operator/=(const ucvec& right)
 {
     if (right.sz != sz)
 	    error(3,form("Different ucvec sizes in operator/= (%d operator/= %d)",
 		sz, right.sz));
     Unique();
     div(r->v,r->v,right.r->v,sz);
     return(*this);
 }

 ucvec& ucvec::operator/=(unsigned char right)
 {
     Unique();
     div(r->v,r->v,right,sz);
     return(*this);
 }

 Subucvec& Subucvec::operator/=(const ucvec& right)
 {
     if (right.sz != sz)
 	    right.error(3,form("Different ucvec sizes in operator/= (%d operator/= %d)",
 		sz, right.sz));
     it->Unique();
     div(&it->r->v[offset],&it->r->v[offset],right.r->v,sz);
     return(*this);
 }

 Subucvec& Subucvec::operator/=(unsigned char right)
 {
     it->Unique();
     div(&it->r->v[offset],&it->r->v[offset],right,sz);
     return(*this);
 }


 ucvec operator*(const ucvec& left, const ucvec& right)
 {
     if (right.sz != left.sz)
 	    left.error(3,form("Different ucvec sizes in operator* (%d operator* %d)",
 		left.sz, right.sz));
     ucvec result(left.sz);
     mul(result.r->v,left.r->v,right.r->v,left.sz);
     return(result);
 }

 ucvec operator*(unsigned char left,const ucvec& right)
 {
     ucvec result(right.origin,right.origin+right.sz-1);
     mul(result.r->v,left,right.r->v,right.sz);
     return(result);
 }

 ucvec operator*(const ucvec &left,unsigned char right)
 {
     ucvec result(left.origin,left.origin+left.sz-1);
     mul(result.r->v,left.r->v,right,left.sz);
     return(result);
 }



 ucvec& ucvec::operator*=(const ucvec& right)
 {
     if (right.sz != sz)
 	    error(3,form("Different ucvec sizes in operator*= (%d operator*= %d)",
 		sz, right.sz));
     Unique();
     mul(r->v,r->v,right.r->v,sz);
     return(*this);
 }

 ucvec& ucvec::operator*=(unsigned char right)
 {
     Unique();
     mul(r->v,r->v,right,sz);
     return(*this);
 }

 Subucvec& Subucvec::operator*=(const ucvec& right)
 {
     if (right.sz != sz)
 	    right.error(3,form("Different ucvec sizes in operator*= (%d operator*= %d)",
 		sz, right.sz));
     it->Unique();
     mul(&it->r->v[offset],&it->r->v[offset],right.r->v,sz);
     return(*this);
 }

 Subucvec& Subucvec::operator*=(unsigned char right)
 {
     it->Unique();
     mul(&it->r->v[offset],&it->r->v[offset],right,sz);
     return(*this);
 }


 ucvec operator&(const ucvec& left, const ucvec& right)
 {
     if (right.sz != left.sz)
 	    left.error(3,form("Different ucvec sizes in operator& (%d operator& %d)",
 		left.sz, right.sz));
     ucvec result(left.sz);
     and(result.r->v,left.r->v,right.r->v,left.sz);
     return(result);
 }

 ucvec operator&(unsigned char left,const ucvec& right)
 {
     ucvec result(right.origin,right.origin+right.sz-1);
     and(result.r->v,left,right.r->v,right.sz);
     return(result);
 }

 ucvec operator&(const ucvec &left,unsigned char right)
 {
     ucvec result(left.origin,left.origin+left.sz-1);
     and(result.r->v,left.r->v,right,left.sz);
     return(result);
 }



 ucvec& ucvec::operator&=(const ucvec& right)
 {
     if (right.sz != sz)
 	    error(3,form("Different ucvec sizes in operator&= (%d operator&= %d)",
 		sz, right.sz));
     Unique();
     and(r->v,r->v,right.r->v,sz);
     return(*this);
 }

 ucvec& ucvec::operator&=(unsigned char right)
 {
     Unique();
     and(r->v,r->v,right,sz);
     return(*this);
 }

 Subucvec& Subucvec::operator&=(const ucvec& right)
 {
     if (right.sz != sz)
 	    right.error(3,form("Different ucvec sizes in operator&= (%d operator&= %d)",
 		sz, right.sz));
     it->Unique();
     and(&it->r->v[offset],&it->r->v[offset],right.r->v,sz);
     return(*this);
 }

 Subucvec& Subucvec::operator&=(unsigned char right)
 {
     it->Unique();
     and(&it->r->v[offset],&it->r->v[offset],right,sz);
     return(*this);
 }


 ucvec operator^(const ucvec& left, const ucvec& right)
 {
     if (right.sz != left.sz)
 	    left.error(3,form("Different ucvec sizes in operator^ (%d operator^ %d)",
 		left.sz, right.sz));
     ucvec result(left.sz);
     eor(result.r->v,left.r->v,right.r->v,left.sz);
     return(result);
 }

 ucvec operator^(unsigned char left,const ucvec& right)
 {
     ucvec result(right.origin,right.origin+right.sz-1);
     eor(result.r->v,left,right.r->v,right.sz);
     return(result);
 }

 ucvec operator^(const ucvec &left,unsigned char right)
 {
     ucvec result(left.origin,left.origin+left.sz-1);
     eor(result.r->v,left.r->v,right,left.sz);
     return(result);
 }



 ucvec& ucvec::operator^=(const ucvec& right)
 {
     if (right.sz != sz)
 	    error(3,form("Different ucvec sizes in operator^= (%d operator^= %d)",
 		sz, right.sz));
     Unique();
     eor(r->v,r->v,right.r->v,sz);
     return(*this);
 }

 ucvec& ucvec::operator^=(unsigned char right)
 {
     Unique();
     eor(r->v,r->v,right,sz);
     return(*this);
 }

 Subucvec& Subucvec::operator^=(const ucvec& right)
 {
     if (right.sz != sz)
 	    right.error(3,form("Different ucvec sizes in operator^= (%d operator^= %d)",
 		sz, right.sz));
     it->Unique();
     eor(&it->r->v[offset],&it->r->v[offset],right.r->v,sz);
     return(*this);
 }

 Subucvec& Subucvec::operator^=(unsigned char right)
 {
     it->Unique();
     eor(&it->r->v[offset],&it->r->v[offset],right,sz);
     return(*this);
 }

 ucvec operator~(const ucvec &x)
 {
     ucvec result(x.origin,x.origin+x.sz-1);
     not(result.r->v,x.r->v,x.sz);
     return(result);
 }

 ucvec operator|(const ucvec& left, const ucvec& right)
 {
     if (right.sz != left.sz)
 	    left.error(3,form("Different ucvec sizes in operator| (%d operator| %d)",
 		left.sz, right.sz));
     ucvec result(left.sz);
     or(result.r->v,left.r->v,right.r->v,left.sz);
     return(result);
 }

 ucvec operator|(unsigned char left,const ucvec& right)
 {
     ucvec result(right.origin,right.origin+right.sz-1);
     or(result.r->v,left,right.r->v,right.sz);
     return(result);
 }

 ucvec operator|(const ucvec &left,unsigned char right)
 {
     ucvec result(left.origin,left.origin+left.sz-1);
     or(result.r->v,left.r->v,right,left.sz);
     return(result);
 }



 ucvec& ucvec::operator|=(const ucvec& right)
 {
     if (right.sz != sz)
 	    error(3,form("Different ucvec sizes in operator|= (%d operator|= %d)",
 		sz, right.sz));
     Unique();
     or(r->v,r->v,right.r->v,sz);
     return(*this);
 }

 ucvec& ucvec::operator|=(unsigned char right)
 {
     Unique();
     or(r->v,r->v,right,sz);
     return(*this);
 }

 Subucvec& Subucvec::operator|=(const ucvec& right)
 {
     if (right.sz != sz)
 	    right.error(3,form("Different ucvec sizes in operator|= (%d operator|= %d)",
 		sz, right.sz));
     it->Unique();
     or(&it->r->v[offset],&it->r->v[offset],right.r->v,sz);
     return(*this);
 }

 Subucvec& Subucvec::operator|=(unsigned char right)
 {
     it->Unique();
     or(&it->r->v[offset],&it->r->v[offset],right,sz);
     return(*this);
 }

 ivec operator==(const ucvec& left, const ucvec& right)
 {
     if (right.size() != left.sz)
 	left.error(3,form("Different ucvec sizes in operator== (%d operator== %d)",
 	    left.sz, right.size()));
     ivec result(left.sz);
     eq(&result[0],left.r->v,right.r->v,left.sz);
     return(result);
 }

 ivec operator==(const ucvec& left, unsigned char right)
 {
     ivec result(left.sz);
     eq(&result[0],left.r->v,right,left.sz);
     return(result);
 }

 ivec operator==(unsigned char left,const ucvec& right)
 {
     ivec result(right.size());
     eq(&result[0],left,right.r->v,right.sz);
     return(result);
 }
 ivec operator!=(const ucvec& left, const ucvec& right)
 {
     if (right.size() != left.sz)
 	left.error(3,form("Different ucvec sizes in operator!= (%d operator!= %d)",
 	    left.sz, right.size()));
     ivec result(left.sz);
     ne(&result[0],left.r->v,right.r->v,left.sz);
     return(result);
 }

 ivec operator!=(const ucvec& left, unsigned char right)
 {
     ivec result(left.sz);
     ne(&result[0],left.r->v,right,left.sz);
     return(result);
 }

 ivec operator!=(unsigned char left,const ucvec& right)
 {
     ivec result(right.size());
     ne(&result[0],left,right.r->v,right.sz);
     return(result);
 }
 ivec operator>=(const ucvec& left, const ucvec& right)
 {
     if (right.size() != left.sz)
 	left.error(3,form("Different ucvec sizes in operator>= (%d operator>= %d)",
 	    left.sz, right.size()));
     ivec result(left.sz);
     for (int i=0;i<left.sz;i++)
 	result[i] = left.r->v[i] >= right.r->v[i];
     return(result);
 }

 ivec operator>=(const ucvec& left, unsigned char right)
 {
     ivec result(left.sz);
     for (int i=0;i<left.sz;i++)
 	result[i] = left.r->v[i] >= right;
     return(result);
 }

 ivec operator>=(unsigned char left,const ucvec& right)
 {
     ivec result(right.size());
     for (int i=0;i<right.size();i++)
 	result[i] = left >= right.r->v[i];
     return(result);
 }
 ivec operator>(const ucvec& left, const ucvec& right)
 {
     if (right.size() != left.sz)
 	left.error(3,form("Different ucvec sizes in operator> (%d operator> %d)",
 	    left.sz, right.size()));
     ivec result(left.sz);
     for (int i=0;i<left.sz;i++)
 	result[i] = left.r->v[i] > right.r->v[i];
     return(result);
 }

 ivec operator>(const ucvec& left, unsigned char right)
 {
     ivec result(left.sz);
     for (int i=0;i<left.sz;i++)
 	result[i] = left.r->v[i] > right;
     return(result);
 }

 ivec operator>(unsigned char left,const ucvec& right)
 {
     ivec result(right.size());
     for (int i=0;i<right.size();i++)
 	result[i] = left > right.r->v[i];
     return(result);
 }
 ivec operator<=(const ucvec& left, const ucvec& right)
 {
     if (right.size() != left.sz)
 	left.error(3,form("Different ucvec sizes in operator<= (%d operator<= %d)",
 	    left.sz, right.size()));
     ivec result(left.sz);
     for (int i=0;i<left.sz;i++)
 	result[i] = left.r->v[i] <= right.r->v[i];
     return(result);
 }

 ivec operator<=(const ucvec& left, unsigned char right)
 {
     ivec result(left.sz);
     for (int i=0;i<left.sz;i++)
 	result[i] = left.r->v[i] <= right;
     return(result);
 }

 ivec operator<=(unsigned char left,const ucvec& right)
 {
     ivec result(right.size());
     for (int i=0;i<right.size();i++)
 	result[i] = left <= right.r->v[i];
     return(result);
 }
 ivec operator<(const ucvec& left, const ucvec& right)
 {
     if (right.size() != left.sz)
 	left.error(3,form("Different ucvec sizes in operator< (%d operator< %d)",
 	    left.sz, right.size()));
     ivec result(left.sz);
     for (int i=0;i<left.sz;i++)
 	result[i] = left.r->v[i] < right.r->v[i];
     return(result);
 }

 ivec operator<(const ucvec& left, unsigned char right)
 {
     ivec result(left.sz);
     for (int i=0;i<left.sz;i++)
 	result[i] = left.r->v[i] < right;
     return(result);
 }

 ivec operator<(unsigned char left,const ucvec& right)
 {
     ivec result(right.size());
     for (int i=0;i<right.size();i++)
 	result[i] = left < right.r->v[i];
     return(result);
 }
Subucvec ucvec::operator()(int first, int last)
{
    if ((first < origin) || (first >= origin+sz))
	error(3,form("Bad first index for ucvec::subvec (%d)",first));
    if ((last < origin) || (last >= origin+sz))
	error(3,form("Bad last index for ucvec::subvec (%d)",last));
    if (last < first)
	error(3,form("First index > last index in ucvec::subvec (%d>%d)",
		first,last));
    return Subucvec(this, first-origin, last-first+1);
}
const Subucvec ucvec::operator()(int first, int last) const
{
    if ((first < origin) || (first >= origin+sz))
	error(3,form("Bad first index for ucvec::subvec (%d)",first));
    if ((last < origin) || (last >= origin+sz))
	error(3,form("Bad last index for ucvec::subvec (%d)",last));
    if (last < first)
	error(3,form("First index > last index in ucvec::subvec (%d>%d)",
		first,last));
    return Subucvec((ucvec *)this, first-origin, last-first+1);
}
ucvec& ucvec::operator=(const ucvec& right)
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
ucvec& ucvec::operator=(unsigned char right)
{
    Unique();
    set(r->v,right,sz);
    return(*this);
}
Subucvec& Subucvec::operator=(const ucvec& right)
{
    if (right.sz != sz)	{
	it->error(3,form("Different ucvec sizes in OP= (%d OP= %d)",
	    sz, right.sz));
	}
    it->Unique();
    mov(&it->r->v[offset],right.r->v,sz);
    return(*this);
}
Subucvec& Subucvec::operator=(unsigned char right)
{
    it->Unique();
    set(&it->r->v[offset],right,sz);
    return(*this);
}
void ucvec::set_size(int s)
{
    if (s<0) error(4,"set_size: bad new ucvec size");
    if (s > r->allocsz) {
	ucvec_Rep *newrep = new_ucvec_Rep(s);
	mov(newrep->v,r->v,sz);
	r->Dec();
	r = newrep;
	}
    sz = s;
}
GPT ucvec::sethandler(GPT a)
{
    GPT oo = handler;
    handler = a;
    return oo;
}
ostream& operator<<(ostream& s,const ucvec& it)
{
    s << "[ ";
    if (it.sz)
	s << it.r->v[0];
    for (int i=1;i<it.sz;i++)
	s << " " << it.r->v[i];
    s << "]";
    return(s);
}
istream& operator>>(istream& s,ucvec& it)
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
ostream& ucvec::BinaryWrite(ostream& s) const
{
    if (sz)
	s.write((char *)r->v,sizeof(r->v[0])*sz);
    return s;
}
istream& ucvec::BinaryRead(istream &s,int nelem)
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
int equal(const ucvec& left, const ucvec& right)
{
    if (right.size() != left.size())
	return 0;
    for (int i=0;i<right.size();i++)
	if (left.r->v[i] != right.r->v[i])
	    return 0;
    return 1;
}
unsigned char dot(const ucvec& left, const ucvec& right)
{
    if (right.sz != left.sz)
	left.error(3,form("Different ucvec sizes in dot (%d and %d)",
	    left.sz, right.sz));
    unsigned char result=0;
    for (int i=0;i<left.sz;i++) result += left.r->v[i]*right.r->v[i];
    return(result);
}
/**//**/
 cvec::cvec(const ucvec& a)
 {
     sz = a.size();
     origin = a.orig();
     r = new_cvec_Rep(sz);
     for (int i=0;i<sz;i++)
 	r->v[i] = (char)a.GetElem(i);
 }
 svec::svec(const ucvec& a)
 {
     sz = a.size();
     origin = a.orig();
     r = new_svec_Rep(sz);
     for (int i=0;i<sz;i++)
 	r->v[i] = (short)a.GetElem(i);
 }
 ivec::ivec(const ucvec& a)
 {
     sz = a.size();
     origin = a.orig();
     r = new_ivec_Rep(sz);
     for (int i=0;i<sz;i++)
 	r->v[i] = (int)a.GetElem(i);
 }
 fvec::fvec(const ucvec& a)
 {
     sz = a.size();
     origin = a.orig();
     r = new_fvec_Rep(sz);
     for (int i=0;i<sz;i++)
 	r->v[i] = (float)a.GetElem(i);
 }
 dvec::dvec(const ucvec& a)
 {
     sz = a.size();
     origin = a.orig();
     r = new_dvec_Rep(sz);
     for (int i=0;i<sz;i++)
 	r->v[i] = (double)a.GetElem(i);
 }
 fcxvec::fcxvec(const ucvec& a)
 {
     sz = a.size();
     origin = a.orig();
     r = new_fcxvec_Rep(sz);
     for (int i=0;i<sz;i++)
 	r->v[i] = (scomplex)a.GetElem(i);
 }
 dcxvec::dcxvec(const ucvec& a)
 {
     sz = a.size();
     origin = a.orig();
     r = new_dcxvec_Rep(sz);
     for (int i=0;i<sz;i++)
 	r->v[i] = (complex)a.GetElem(i);
 }
