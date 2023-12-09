static char vector_sccsid[]="%Z%%M% %I% %E% %U% bst";
 /*
 * Vector library
 * Brent Townshend (bst@alice)
 * AT&T Bell Laboratories
 * MH 2D-554 (201)582-4111
 *
 */
#include <stream.h>
#include <ucvec.h>
#include <cvec.h>
#include <svec.h>
#include <ivec.h>
#include <fvec.h>
#include <dvec.h>
#include <fcxvec.h>
#include <dcxvec.h>
 cvec abs(const cvec &x)
 {
     cvec result(x.origin,x.origin+x.sz-1);
     for (int i=0;i<x.sz;i++)
 	result.r->v[i] = (x.r->v[i]>0)?x.r->v[i]:-x.r->v[i];
     return(result);
 }
 cvec min(const cvec& left, const cvec& right)
 {
     if (right.sz != left.sz)
 	    left.error(3,form("Different cvec sizes in min (%d min %d)",
 		left.sz, right.sz));
     cvec result(left.sz);
     for (int i=0;i<left.sz;i++)
 	result.r->v[i] = left.r->v[i] < right.r->v[i] ? left.r->v[i]: right.r->v[i];
     return(result);
 }

 cvec min(const cvec& left, char right)
 {
     cvec result(left.origin,left.origin+left.sz-1);
     for (int i=0;i<left.sz;i++)
 	result.r->v[i] = left.r->v[i] < right ? left.r->v[i]: right;
     return(result);
 }

 cvec min(char left,const cvec& right)
 {
     cvec result(right.origin,right.origin+right.sz-1);
     for (int i=0;i<right.sz;i++)
 	result.r->v[i] = left < right.r->v[i] ? left : right.r->v[i];
     return(result);
 }
 cvec max(const cvec& left, const cvec& right)
 {
     if (right.sz != left.sz)
 	    left.error(3,form("Different cvec sizes in max (%d max %d)",
 		left.sz, right.sz));
     cvec result(left.sz);
     for (int i=0;i<left.sz;i++)
 	result.r->v[i] = left.r->v[i] > right.r->v[i] ? left.r->v[i]: right.r->v[i];
     return(result);
 }

 cvec max(const cvec& left, char right)
 {
     cvec result(left.origin,left.origin+left.sz-1);
     for (int i=0;i<left.sz;i++)
 	result.r->v[i] = left.r->v[i] > right ? left.r->v[i]: right;
     return(result);
 }

 cvec max(char left,const cvec& right)
 {
     cvec result(right.origin,right.origin+right.sz-1);
     for (int i=0;i<right.sz;i++)
 	result.r->v[i] = left > right.r->v[i] ? left : right.r->v[i];
     return(result);
 }
 char max(const cvec &x)
 {
     if (x.sz == 0) x.error(3,"Attempt to calculate max of length 0 cvec");
     char result=x.r->v[0];
     for (int i=1;i<x.sz;i++)
 	if(x.r->v[i]>result)result=x.r->v[i];
     return(result);
 }
 char min(const cvec &x)
 {
     if (x.sz == 0) x.error(3,"Attempt to calculate min of length 0 cvec");
     char result=x.r->v[0];
     for (int i=1;i<x.sz;i++)
 	if(x.r->v[i]<result)result=x.r->v[i];
     return(result);
 }
 char sum(const cvec &x)
 {
     if (x.sz == 0) x.error(3,"Attempt to calculate sum of length 0 cvec");
     char result=x.r->v[0];
     for (int i=1;i<x.sz;i++)
 	result+=x.r->v[i];
     return(result);
 }
 char prod(const cvec &x)
 {
     if (x.sz == 0) x.error(3,"Attempt to calculate prod of length 0 cvec");
     char result=x.r->v[0];
     for (int i=1;i<x.sz;i++)
 	result*=x.r->v[i];
     return(result);
 }

 cvec operator+(const cvec& left, const cvec& right)
 {
     if (right.sz != left.sz)
 	    left.error(3,form("Different cvec sizes in operator+ (%d operator+ %d)",
 		left.sz, right.sz));
     cvec result(left.sz);
     for (int i=0;i<left.sz;i++)
 	result.r->v[i] = left.r->v[i] + right.r->v[i];
     return(result);
 }

 cvec operator+(char left,const cvec& right)
 {
     cvec result(right.origin,right.origin+right.sz-1);
     for (int i=0;i<right.sz;i++)
 	result.r->v[i] = left + right.r->v[i];
     return(result);
 }

 cvec operator+(const cvec &left,char right)
 {
     cvec result(left.origin,left.origin+left.sz-1);
     for (int i=0;i<left.sz;i++)
 	result.r->v[i] = left.r->v[i] + right;
     return(result);
 }



 cvec& cvec::operator+=(const cvec& right)
 {
     if (right.sz != sz)
 	    error(3,form("Different cvec sizes in operator+= (%d operator+= %d)",
 		sz, right.sz));
     Unique();
     for (int i=0;i<sz;i++)
 	r->v[i] += right.r->v[i];
     return(*this);
 }

 cvec& cvec::operator+=(char right)
 {
     Unique();
     for (int i=0;i<sz;i++)
 	r->v[i] += right;
     return(*this);
 }

 Subcvec& Subcvec::operator+=(const cvec& right)
 {
     if (right.sz != sz)
 	    right.error(3,form("Different cvec sizes in operator+= (%d operator+= %d)",
 		sz, right.sz));
     it->Unique();
     for (int i=0;i<sz;i++)
 	it->r->v[i+offset] += right.r->v[i];
     return(*this);
 }

 Subcvec& Subcvec::operator+=(char right)
 {
     it->Unique();
     for (int i=0;i<sz;i++)
 	it->r->v[i+offset] += right;
     return(*this);
 }


 cvec operator-(const cvec& left, const cvec& right)
 {
     if (right.sz != left.sz)
 	    left.error(3,form("Different cvec sizes in operator- (%d operator- %d)",
 		left.sz, right.sz));
     cvec result(left.sz);
     for (int i=0;i<left.sz;i++)
 	result.r->v[i] = left.r->v[i] - right.r->v[i];
     return(result);
 }

 cvec operator-(char left,const cvec& right)
 {
     cvec result(right.origin,right.origin+right.sz-1);
     for (int i=0;i<right.sz;i++)
 	result.r->v[i] = left - right.r->v[i];
     return(result);
 }

 cvec operator-(const cvec &left,char right)
 {
     cvec result(left.origin,left.origin+left.sz-1);
     for (int i=0;i<left.sz;i++)
 	result.r->v[i] = left.r->v[i] - right;
     return(result);
 }



 cvec& cvec::operator-=(const cvec& right)
 {
     if (right.sz != sz)
 	    error(3,form("Different cvec sizes in operator-= (%d operator-= %d)",
 		sz, right.sz));
     Unique();
     for (int i=0;i<sz;i++)
 	r->v[i] -= right.r->v[i];
     return(*this);
 }

 cvec& cvec::operator-=(char right)
 {
     Unique();
     for (int i=0;i<sz;i++)
 	r->v[i] -= right;
     return(*this);
 }

 Subcvec& Subcvec::operator-=(const cvec& right)
 {
     if (right.sz != sz)
 	    right.error(3,form("Different cvec sizes in operator-= (%d operator-= %d)",
 		sz, right.sz));
     it->Unique();
     for (int i=0;i<sz;i++)
 	it->r->v[i+offset] -= right.r->v[i];
     return(*this);
 }

 Subcvec& Subcvec::operator-=(char right)
 {
     it->Unique();
     for (int i=0;i<sz;i++)
 	it->r->v[i+offset] -= right;
     return(*this);
 }


 cvec operator/(const cvec& left, const cvec& right)
 {
     if (right.sz != left.sz)
 	    left.error(3,form("Different cvec sizes in operator/ (%d operator/ %d)",
 		left.sz, right.sz));
     cvec result(left.sz);
     for (int i=0;i<left.sz;i++)
 	result.r->v[i] = left.r->v[i] / right.r->v[i];
     return(result);
 }

 cvec operator/(char left,const cvec& right)
 {
     cvec result(right.origin,right.origin+right.sz-1);
     for (int i=0;i<right.sz;i++)
 	result.r->v[i] = left / right.r->v[i];
     return(result);
 }

 cvec operator/(const cvec &left,char right)
 {
     cvec result(left.origin,left.origin+left.sz-1);
     for (int i=0;i<left.sz;i++)
 	result.r->v[i] = left.r->v[i] / right;
     return(result);
 }



 cvec& cvec::operator/=(const cvec& right)
 {
     if (right.sz != sz)
 	    error(3,form("Different cvec sizes in operator/= (%d operator/= %d)",
 		sz, right.sz));
     Unique();
     for (int i=0;i<sz;i++)
 	r->v[i] /= right.r->v[i];
     return(*this);
 }

 cvec& cvec::operator/=(char right)
 {
     Unique();
     for (int i=0;i<sz;i++)
 	r->v[i] /= right;
     return(*this);
 }

 Subcvec& Subcvec::operator/=(const cvec& right)
 {
     if (right.sz != sz)
 	    right.error(3,form("Different cvec sizes in operator/= (%d operator/= %d)",
 		sz, right.sz));
     it->Unique();
     for (int i=0;i<sz;i++)
 	it->r->v[i+offset] /= right.r->v[i];
     return(*this);
 }

 Subcvec& Subcvec::operator/=(char right)
 {
     it->Unique();
     for (int i=0;i<sz;i++)
 	it->r->v[i+offset] /= right;
     return(*this);
 }


 cvec operator*(const cvec& left, const cvec& right)
 {
     if (right.sz != left.sz)
 	    left.error(3,form("Different cvec sizes in operator* (%d operator* %d)",
 		left.sz, right.sz));
     cvec result(left.sz);
     for (int i=0;i<left.sz;i++)
 	result.r->v[i] = left.r->v[i] * right.r->v[i];
     return(result);
 }

 cvec operator*(char left,const cvec& right)
 {
     cvec result(right.origin,right.origin+right.sz-1);
     for (int i=0;i<right.sz;i++)
 	result.r->v[i] = left * right.r->v[i];
     return(result);
 }

 cvec operator*(const cvec &left,char right)
 {
     cvec result(left.origin,left.origin+left.sz-1);
     for (int i=0;i<left.sz;i++)
 	result.r->v[i] = left.r->v[i] * right;
     return(result);
 }



 cvec& cvec::operator*=(const cvec& right)
 {
     if (right.sz != sz)
 	    error(3,form("Different cvec sizes in operator*= (%d operator*= %d)",
 		sz, right.sz));
     Unique();
     for (int i=0;i<sz;i++)
 	r->v[i] *= right.r->v[i];
     return(*this);
 }

 cvec& cvec::operator*=(char right)
 {
     Unique();
     for (int i=0;i<sz;i++)
 	r->v[i] *= right;
     return(*this);
 }

 Subcvec& Subcvec::operator*=(const cvec& right)
 {
     if (right.sz != sz)
 	    right.error(3,form("Different cvec sizes in operator*= (%d operator*= %d)",
 		sz, right.sz));
     it->Unique();
     for (int i=0;i<sz;i++)
 	it->r->v[i+offset] *= right.r->v[i];
     return(*this);
 }

 Subcvec& Subcvec::operator*=(char right)
 {
     it->Unique();
     for (int i=0;i<sz;i++)
 	it->r->v[i+offset] *= right;
     return(*this);
 }

 cvec operator-(const cvec &x)
 {
     cvec result(x.origin,x.origin+x.sz-1);
     for (int i=0;i<x.sz;i++)
 	result.r->v[i] = -x.r->v[i];
     return(result);
 }

 cvec operator&(const cvec& left, const cvec& right)
 {
     if (right.sz != left.sz)
 	    left.error(3,form("Different cvec sizes in operator& (%d operator& %d)",
 		left.sz, right.sz));
     cvec result(left.sz);
     for (int i=0;i<left.sz;i++)
 	result.r->v[i] = left.r->v[i] & right.r->v[i];
     return(result);
 }

 cvec operator&(char left,const cvec& right)
 {
     cvec result(right.origin,right.origin+right.sz-1);
     for (int i=0;i<right.sz;i++)
 	result.r->v[i] = left & right.r->v[i];
     return(result);
 }

 cvec operator&(const cvec &left,char right)
 {
     cvec result(left.origin,left.origin+left.sz-1);
     for (int i=0;i<left.sz;i++)
 	result.r->v[i] = left.r->v[i] & right;
     return(result);
 }



 cvec& cvec::operator&=(const cvec& right)
 {
     if (right.sz != sz)
 	    error(3,form("Different cvec sizes in operator&= (%d operator&= %d)",
 		sz, right.sz));
     Unique();
     for (int i=0;i<sz;i++)
 	r->v[i] &= right.r->v[i];
     return(*this);
 }

 cvec& cvec::operator&=(char right)
 {
     Unique();
     for (int i=0;i<sz;i++)
 	r->v[i] &= right;
     return(*this);
 }

 Subcvec& Subcvec::operator&=(const cvec& right)
 {
     if (right.sz != sz)
 	    right.error(3,form("Different cvec sizes in operator&= (%d operator&= %d)",
 		sz, right.sz));
     it->Unique();
     for (int i=0;i<sz;i++)
 	it->r->v[i+offset] &= right.r->v[i];
     return(*this);
 }

 Subcvec& Subcvec::operator&=(char right)
 {
     it->Unique();
     for (int i=0;i<sz;i++)
 	it->r->v[i+offset] &= right;
     return(*this);
 }


 cvec operator^(const cvec& left, const cvec& right)
 {
     if (right.sz != left.sz)
 	    left.error(3,form("Different cvec sizes in operator^ (%d operator^ %d)",
 		left.sz, right.sz));
     cvec result(left.sz);
     for (int i=0;i<left.sz;i++)
 	result.r->v[i] = left.r->v[i] ^ right.r->v[i];
     return(result);
 }

 cvec operator^(char left,const cvec& right)
 {
     cvec result(right.origin,right.origin+right.sz-1);
     for (int i=0;i<right.sz;i++)
 	result.r->v[i] = left ^ right.r->v[i];
     return(result);
 }

 cvec operator^(const cvec &left,char right)
 {
     cvec result(left.origin,left.origin+left.sz-1);
     for (int i=0;i<left.sz;i++)
 	result.r->v[i] = left.r->v[i] ^ right;
     return(result);
 }



 cvec& cvec::operator^=(const cvec& right)
 {
     if (right.sz != sz)
 	    error(3,form("Different cvec sizes in operator^= (%d operator^= %d)",
 		sz, right.sz));
     Unique();
     for (int i=0;i<sz;i++)
 	r->v[i] ^= right.r->v[i];
     return(*this);
 }

 cvec& cvec::operator^=(char right)
 {
     Unique();
     for (int i=0;i<sz;i++)
 	r->v[i] ^= right;
     return(*this);
 }

 Subcvec& Subcvec::operator^=(const cvec& right)
 {
     if (right.sz != sz)
 	    right.error(3,form("Different cvec sizes in operator^= (%d operator^= %d)",
 		sz, right.sz));
     it->Unique();
     for (int i=0;i<sz;i++)
 	it->r->v[i+offset] ^= right.r->v[i];
     return(*this);
 }

 Subcvec& Subcvec::operator^=(char right)
 {
     it->Unique();
     for (int i=0;i<sz;i++)
 	it->r->v[i+offset] ^= right;
     return(*this);
 }

 cvec operator~(const cvec &x)
 {
     cvec result(x.origin,x.origin+x.sz-1);
     for (int i=0;i<x.sz;i++)
 	result.r->v[i] = ~x.r->v[i];
     return(result);
 }

 cvec operator|(const cvec& left, const cvec& right)
 {
     if (right.sz != left.sz)
 	    left.error(3,form("Different cvec sizes in operator| (%d operator| %d)",
 		left.sz, right.sz));
     cvec result(left.sz);
     for (int i=0;i<left.sz;i++)
 	result.r->v[i] = left.r->v[i] | right.r->v[i];
     return(result);
 }

 cvec operator|(char left,const cvec& right)
 {
     cvec result(right.origin,right.origin+right.sz-1);
     for (int i=0;i<right.sz;i++)
 	result.r->v[i] = left | right.r->v[i];
     return(result);
 }

 cvec operator|(const cvec &left,char right)
 {
     cvec result(left.origin,left.origin+left.sz-1);
     for (int i=0;i<left.sz;i++)
 	result.r->v[i] = left.r->v[i] | right;
     return(result);
 }



 cvec& cvec::operator|=(const cvec& right)
 {
     if (right.sz != sz)
 	    error(3,form("Different cvec sizes in operator|= (%d operator|= %d)",
 		sz, right.sz));
     Unique();
     for (int i=0;i<sz;i++)
 	r->v[i] |= right.r->v[i];
     return(*this);
 }

 cvec& cvec::operator|=(char right)
 {
     Unique();
     for (int i=0;i<sz;i++)
 	r->v[i] |= right;
     return(*this);
 }

 Subcvec& Subcvec::operator|=(const cvec& right)
 {
     if (right.sz != sz)
 	    right.error(3,form("Different cvec sizes in operator|= (%d operator|= %d)",
 		sz, right.sz));
     it->Unique();
     for (int i=0;i<sz;i++)
 	it->r->v[i+offset] |= right.r->v[i];
     return(*this);
 }

 Subcvec& Subcvec::operator|=(char right)
 {
     it->Unique();
     for (int i=0;i<sz;i++)
 	it->r->v[i+offset] |= right;
     return(*this);
 }

 ivec operator==(const cvec& left, const cvec& right)
 {
     if (right.size() != left.sz)
 	left.error(3,form("Different cvec sizes in operator== (%d operator== %d)",
 	    left.sz, right.size()));
     ivec result(left.sz);
     for (int i=0;i<left.sz;i++)
 	result[i] = left.r->v[i] == right.r->v[i];
     return(result);
 }

 ivec operator==(const cvec& left, char right)
 {
     ivec result(left.sz);
     for (int i=0;i<left.sz;i++)
 	result[i] = left.r->v[i] == right;
     return(result);
 }

 ivec operator==(char left,const cvec& right)
 {
     ivec result(right.size());
     for (int i=0;i<right.size();i++)
 	result[i] = left == right.r->v[i];
     return(result);
 }
 ivec operator!=(const cvec& left, const cvec& right)
 {
     if (right.size() != left.sz)
 	left.error(3,form("Different cvec sizes in operator!= (%d operator!= %d)",
 	    left.sz, right.size()));
     ivec result(left.sz);
     for (int i=0;i<left.sz;i++)
 	result[i] = left.r->v[i] != right.r->v[i];
     return(result);
 }

 ivec operator!=(const cvec& left, char right)
 {
     ivec result(left.sz);
     for (int i=0;i<left.sz;i++)
 	result[i] = left.r->v[i] != right;
     return(result);
 }

 ivec operator!=(char left,const cvec& right)
 {
     ivec result(right.size());
     for (int i=0;i<right.size();i++)
 	result[i] = left != right.r->v[i];
     return(result);
 }
 ivec operator>=(const cvec& left, const cvec& right)
 {
     if (right.size() != left.sz)
 	left.error(3,form("Different cvec sizes in operator>= (%d operator>= %d)",
 	    left.sz, right.size()));
     ivec result(left.sz);
     for (int i=0;i<left.sz;i++)
 	result[i] = left.r->v[i] >= right.r->v[i];
     return(result);
 }

 ivec operator>=(const cvec& left, char right)
 {
     ivec result(left.sz);
     for (int i=0;i<left.sz;i++)
 	result[i] = left.r->v[i] >= right;
     return(result);
 }

 ivec operator>=(char left,const cvec& right)
 {
     ivec result(right.size());
     for (int i=0;i<right.size();i++)
 	result[i] = left >= right.r->v[i];
     return(result);
 }
 ivec operator>(const cvec& left, const cvec& right)
 {
     if (right.size() != left.sz)
 	left.error(3,form("Different cvec sizes in operator> (%d operator> %d)",
 	    left.sz, right.size()));
     ivec result(left.sz);
     for (int i=0;i<left.sz;i++)
 	result[i] = left.r->v[i] > right.r->v[i];
     return(result);
 }

 ivec operator>(const cvec& left, char right)
 {
     ivec result(left.sz);
     for (int i=0;i<left.sz;i++)
 	result[i] = left.r->v[i] > right;
     return(result);
 }

 ivec operator>(char left,const cvec& right)
 {
     ivec result(right.size());
     for (int i=0;i<right.size();i++)
 	result[i] = left > right.r->v[i];
     return(result);
 }
 ivec operator<=(const cvec& left, const cvec& right)
 {
     if (right.size() != left.sz)
 	left.error(3,form("Different cvec sizes in operator<= (%d operator<= %d)",
 	    left.sz, right.size()));
     ivec result(left.sz);
     for (int i=0;i<left.sz;i++)
 	result[i] = left.r->v[i] <= right.r->v[i];
     return(result);
 }

 ivec operator<=(const cvec& left, char right)
 {
     ivec result(left.sz);
     for (int i=0;i<left.sz;i++)
 	result[i] = left.r->v[i] <= right;
     return(result);
 }

 ivec operator<=(char left,const cvec& right)
 {
     ivec result(right.size());
     for (int i=0;i<right.size();i++)
 	result[i] = left <= right.r->v[i];
     return(result);
 }
 ivec operator<(const cvec& left, const cvec& right)
 {
     if (right.size() != left.sz)
 	left.error(3,form("Different cvec sizes in operator< (%d operator< %d)",
 	    left.sz, right.size()));
     ivec result(left.sz);
     for (int i=0;i<left.sz;i++)
 	result[i] = left.r->v[i] < right.r->v[i];
     return(result);
 }

 ivec operator<(const cvec& left, char right)
 {
     ivec result(left.sz);
     for (int i=0;i<left.sz;i++)
 	result[i] = left.r->v[i] < right;
     return(result);
 }

 ivec operator<(char left,const cvec& right)
 {
     ivec result(right.size());
     for (int i=0;i<right.size();i++)
 	result[i] = left < right.r->v[i];
     return(result);
 }
Subcvec cvec::operator()(int first, int last)
{
    if ((first < origin) || (first >= origin+sz))
	error(3,form("Bad first index for cvec::subvec (%d)",first));
    if ((last < origin) || (last >= origin+sz))
	error(3,form("Bad last index for cvec::subvec (%d)",last));
    if (last < first)
	error(3,form("First index > last index in cvec::subvec (%d>%d)",
		first,last));
    return Subcvec(this, first-origin, last-first+1);
}
const Subcvec cvec::operator()(int first, int last) const
{
    if ((first < origin) || (first >= origin+sz))
	error(3,form("Bad first index for cvec::subvec (%d)",first));
    if ((last < origin) || (last >= origin+sz))
	error(3,form("Bad last index for cvec::subvec (%d)",last));
    if (last < first)
	error(3,form("First index > last index in cvec::subvec (%d>%d)",
		first,last));
    return Subcvec((cvec *)this, first-origin, last-first+1);
}
cvec& cvec::operator=(const cvec& right)
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
cvec& cvec::operator=(char right)
{
    Unique();
    for (int i=0;i<sz;i++) r->v[i] = right;
    return(*this);
}
Subcvec& Subcvec::operator=(const cvec& right)
{
    if (right.sz != sz)	{
	it->error(3,form("Different cvec sizes in OP= (%d OP= %d)",
	    sz, right.sz));
	}
    it->Unique();
    mov(&it->r->v[offset],right.r->v,sz);
    return(*this);
}
Subcvec& Subcvec::operator=(char right)
{
    it->Unique();
    for (int i=0;i<sz;i++) it->r->v[i+offset] = right;
    return(*this);
}
void cvec::set_size(int s)
{
    if (s<0) error(4,"set_size: bad new cvec size");
    if (s > r->allocsz) {
	cvec_Rep *newrep = new_cvec_Rep(s);
	mov(newrep->v,r->v,sz);
	r->Dec();
	r = newrep;
	}
    sz = s;
}
GPT cvec::sethandler(GPT a)
{
    GPT oo = handler;
    handler = a;
    return oo;
}
ostream& operator<<(ostream& s,const cvec& it)
{
    s << "[ ";
    if (it.sz)
	s << it.r->v[0];
    for (int i=1;i<it.sz;i++)
	s << " " << it.r->v[i];
    s << "]";
    return(s);
}
istream& operator>>(istream& s,cvec& it)
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
ostream& cvec::BinaryWrite(ostream& s) const
{
    if (sz)
	s.write((char *)r->v,sizeof(r->v[0])*sz);
    return s;
}
istream& cvec::BinaryRead(istream &s,int nelem)
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
int equal(const cvec& left, const cvec& right)
{
    if (right.size() != left.size())
	return 0;
    for (int i=0;i<right.size();i++)
	if (left.r->v[i] != right.r->v[i])
	    return 0;
    return 1;
}
char dot(const cvec& left, const cvec& right)
{
    if (right.sz != left.sz)
	left.error(3,form("Different cvec sizes in dot (%d and %d)",
	    left.sz, right.sz));
    char result=0;
    for (int i=0;i<left.sz;i++) result += left.r->v[i]*right.r->v[i];
    return(result);
}
/**//**/
 ucvec::ucvec(const cvec& a)
 {
     sz = a.size();
     origin = a.orig();
     r = new_ucvec_Rep(sz);
     for (int i=0;i<sz;i++)
 	r->v[i] = (unsigned char)a.GetElem(i);
 }
 svec::svec(const cvec& a)
 {
     sz = a.size();
     origin = a.orig();
     r = new_svec_Rep(sz);
     for (int i=0;i<sz;i++)
 	r->v[i] = (short)a.GetElem(i);
 }
 ivec::ivec(const cvec& a)
 {
     sz = a.size();
     origin = a.orig();
     r = new_ivec_Rep(sz);
     for (int i=0;i<sz;i++)
 	r->v[i] = (int)a.GetElem(i);
 }
 fvec::fvec(const cvec& a)
 {
     sz = a.size();
     origin = a.orig();
     r = new_fvec_Rep(sz);
     for (int i=0;i<sz;i++)
 	r->v[i] = (float)a.GetElem(i);
 }
 dvec::dvec(const cvec& a)
 {
     sz = a.size();
     origin = a.orig();
     r = new_dvec_Rep(sz);
     for (int i=0;i<sz;i++)
 	r->v[i] = (double)a.GetElem(i);
 }
 fcxvec::fcxvec(const cvec& a)
 {
     sz = a.size();
     origin = a.orig();
     r = new_fcxvec_Rep(sz);
     for (int i=0;i<sz;i++)
 	r->v[i] = (scomplex)a.GetElem(i);
 }
 dcxvec::dcxvec(const cvec& a)
 {
     sz = a.size();
     origin = a.orig();
     r = new_dcxvec_Rep(sz);
     for (int i=0;i<sz;i++)
 	r->v[i] = (complex)a.GetElem(i);
 }
