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
 svec abs(const svec &x)
 {
     svec result(x.origin,x.origin+x.sz-1);
     for (int i=0;i<x.sz;i++)
 	result.r->v[i] = (x.r->v[i]>0)?x.r->v[i]:-x.r->v[i];
     return(result);
 }
 svec min(const svec& left, const svec& right)
 {
     if (right.sz != left.sz)
 	    left.error(3,form("Different svec sizes in min (%d min %d)",
 		left.sz, right.sz));
     svec result(left.sz);
     for (int i=0;i<left.sz;i++)
 	result.r->v[i] = left.r->v[i] < right.r->v[i] ? left.r->v[i]: right.r->v[i];
     return(result);
 }

 svec min(const svec& left, short right)
 {
     svec result(left.origin,left.origin+left.sz-1);
     for (int i=0;i<left.sz;i++)
 	result.r->v[i] = left.r->v[i] < right ? left.r->v[i]: right;
     return(result);
 }

 svec min(short left,const svec& right)
 {
     svec result(right.origin,right.origin+right.sz-1);
     for (int i=0;i<right.sz;i++)
 	result.r->v[i] = left < right.r->v[i] ? left : right.r->v[i];
     return(result);
 }
 svec max(const svec& left, const svec& right)
 {
     if (right.sz != left.sz)
 	    left.error(3,form("Different svec sizes in max (%d max %d)",
 		left.sz, right.sz));
     svec result(left.sz);
     for (int i=0;i<left.sz;i++)
 	result.r->v[i] = left.r->v[i] > right.r->v[i] ? left.r->v[i]: right.r->v[i];
     return(result);
 }

 svec max(const svec& left, short right)
 {
     svec result(left.origin,left.origin+left.sz-1);
     for (int i=0;i<left.sz;i++)
 	result.r->v[i] = left.r->v[i] > right ? left.r->v[i]: right;
     return(result);
 }

 svec max(short left,const svec& right)
 {
     svec result(right.origin,right.origin+right.sz-1);
     for (int i=0;i<right.sz;i++)
 	result.r->v[i] = left > right.r->v[i] ? left : right.r->v[i];
     return(result);
 }
 short max(const svec &x)
 {
     if (x.sz == 0) x.error(3,"Attempt to calculate max of length 0 svec");
     short result=x.r->v[0];
     for (int i=1;i<x.sz;i++)
 	if(x.r->v[i]>result)result=x.r->v[i];
     return(result);
 }
 short min(const svec &x)
 {
     if (x.sz == 0) x.error(3,"Attempt to calculate min of length 0 svec");
     short result=x.r->v[0];
     for (int i=1;i<x.sz;i++)
 	if(x.r->v[i]<result)result=x.r->v[i];
     return(result);
 }
 short sum(const svec &x)
 {
     if (x.sz == 0) x.error(3,"Attempt to calculate sum of length 0 svec");
     short result=x.r->v[0];
     for (int i=1;i<x.sz;i++)
 	result+=x.r->v[i];
     return(result);
 }
 short prod(const svec &x)
 {
     if (x.sz == 0) x.error(3,"Attempt to calculate prod of length 0 svec");
     short result=x.r->v[0];
     for (int i=1;i<x.sz;i++)
 	result*=x.r->v[i];
     return(result);
 }

 svec operator+(const svec& left, const svec& right)
 {
     if (right.sz != left.sz)
 	    left.error(3,form("Different svec sizes in operator+ (%d operator+ %d)",
 		left.sz, right.sz));
     svec result(left.sz);
     for (int i=0;i<left.sz;i++)
 	result.r->v[i] = left.r->v[i] + right.r->v[i];
     return(result);
 }

 svec operator+(short left,const svec& right)
 {
     svec result(right.origin,right.origin+right.sz-1);
     for (int i=0;i<right.sz;i++)
 	result.r->v[i] = left + right.r->v[i];
     return(result);
 }

 svec operator+(const svec &left,short right)
 {
     svec result(left.origin,left.origin+left.sz-1);
     for (int i=0;i<left.sz;i++)
 	result.r->v[i] = left.r->v[i] + right;
     return(result);
 }



 svec& svec::operator+=(const svec& right)
 {
     if (right.sz != sz)
 	    error(3,form("Different svec sizes in operator+= (%d operator+= %d)",
 		sz, right.sz));
     Unique();
     for (int i=0;i<sz;i++)
 	r->v[i] += right.r->v[i];
     return(*this);
 }

 svec& svec::operator+=(short right)
 {
     Unique();
     for (int i=0;i<sz;i++)
 	r->v[i] += right;
     return(*this);
 }

 Subsvec& Subsvec::operator+=(const svec& right)
 {
     if (right.sz != sz)
 	    right.error(3,form("Different svec sizes in operator+= (%d operator+= %d)",
 		sz, right.sz));
     it->Unique();
     for (int i=0;i<sz;i++)
 	it->r->v[i+offset] += right.r->v[i];
     return(*this);
 }

 Subsvec& Subsvec::operator+=(short right)
 {
     it->Unique();
     for (int i=0;i<sz;i++)
 	it->r->v[i+offset] += right;
     return(*this);
 }


 svec operator-(const svec& left, const svec& right)
 {
     if (right.sz != left.sz)
 	    left.error(3,form("Different svec sizes in operator- (%d operator- %d)",
 		left.sz, right.sz));
     svec result(left.sz);
     for (int i=0;i<left.sz;i++)
 	result.r->v[i] = left.r->v[i] - right.r->v[i];
     return(result);
 }

 svec operator-(short left,const svec& right)
 {
     svec result(right.origin,right.origin+right.sz-1);
     for (int i=0;i<right.sz;i++)
 	result.r->v[i] = left - right.r->v[i];
     return(result);
 }

 svec operator-(const svec &left,short right)
 {
     svec result(left.origin,left.origin+left.sz-1);
     for (int i=0;i<left.sz;i++)
 	result.r->v[i] = left.r->v[i] - right;
     return(result);
 }



 svec& svec::operator-=(const svec& right)
 {
     if (right.sz != sz)
 	    error(3,form("Different svec sizes in operator-= (%d operator-= %d)",
 		sz, right.sz));
     Unique();
     for (int i=0;i<sz;i++)
 	r->v[i] -= right.r->v[i];
     return(*this);
 }

 svec& svec::operator-=(short right)
 {
     Unique();
     for (int i=0;i<sz;i++)
 	r->v[i] -= right;
     return(*this);
 }

 Subsvec& Subsvec::operator-=(const svec& right)
 {
     if (right.sz != sz)
 	    right.error(3,form("Different svec sizes in operator-= (%d operator-= %d)",
 		sz, right.sz));
     it->Unique();
     for (int i=0;i<sz;i++)
 	it->r->v[i+offset] -= right.r->v[i];
     return(*this);
 }

 Subsvec& Subsvec::operator-=(short right)
 {
     it->Unique();
     for (int i=0;i<sz;i++)
 	it->r->v[i+offset] -= right;
     return(*this);
 }


 svec operator/(const svec& left, const svec& right)
 {
     if (right.sz != left.sz)
 	    left.error(3,form("Different svec sizes in operator/ (%d operator/ %d)",
 		left.sz, right.sz));
     svec result(left.sz);
     for (int i=0;i<left.sz;i++)
 	result.r->v[i] = left.r->v[i] / right.r->v[i];
     return(result);
 }

 svec operator/(short left,const svec& right)
 {
     svec result(right.origin,right.origin+right.sz-1);
     for (int i=0;i<right.sz;i++)
 	result.r->v[i] = left / right.r->v[i];
     return(result);
 }

 svec operator/(const svec &left,short right)
 {
     svec result(left.origin,left.origin+left.sz-1);
     for (int i=0;i<left.sz;i++)
 	result.r->v[i] = left.r->v[i] / right;
     return(result);
 }



 svec& svec::operator/=(const svec& right)
 {
     if (right.sz != sz)
 	    error(3,form("Different svec sizes in operator/= (%d operator/= %d)",
 		sz, right.sz));
     Unique();
     for (int i=0;i<sz;i++)
 	r->v[i] /= right.r->v[i];
     return(*this);
 }

 svec& svec::operator/=(short right)
 {
     Unique();
     for (int i=0;i<sz;i++)
 	r->v[i] /= right;
     return(*this);
 }

 Subsvec& Subsvec::operator/=(const svec& right)
 {
     if (right.sz != sz)
 	    right.error(3,form("Different svec sizes in operator/= (%d operator/= %d)",
 		sz, right.sz));
     it->Unique();
     for (int i=0;i<sz;i++)
 	it->r->v[i+offset] /= right.r->v[i];
     return(*this);
 }

 Subsvec& Subsvec::operator/=(short right)
 {
     it->Unique();
     for (int i=0;i<sz;i++)
 	it->r->v[i+offset] /= right;
     return(*this);
 }


 svec operator*(const svec& left, const svec& right)
 {
     if (right.sz != left.sz)
 	    left.error(3,form("Different svec sizes in operator* (%d operator* %d)",
 		left.sz, right.sz));
     svec result(left.sz);
     for (int i=0;i<left.sz;i++)
 	result.r->v[i] = left.r->v[i] * right.r->v[i];
     return(result);
 }

 svec operator*(short left,const svec& right)
 {
     svec result(right.origin,right.origin+right.sz-1);
     for (int i=0;i<right.sz;i++)
 	result.r->v[i] = left * right.r->v[i];
     return(result);
 }

 svec operator*(const svec &left,short right)
 {
     svec result(left.origin,left.origin+left.sz-1);
     for (int i=0;i<left.sz;i++)
 	result.r->v[i] = left.r->v[i] * right;
     return(result);
 }



 svec& svec::operator*=(const svec& right)
 {
     if (right.sz != sz)
 	    error(3,form("Different svec sizes in operator*= (%d operator*= %d)",
 		sz, right.sz));
     Unique();
     for (int i=0;i<sz;i++)
 	r->v[i] *= right.r->v[i];
     return(*this);
 }

 svec& svec::operator*=(short right)
 {
     Unique();
     for (int i=0;i<sz;i++)
 	r->v[i] *= right;
     return(*this);
 }

 Subsvec& Subsvec::operator*=(const svec& right)
 {
     if (right.sz != sz)
 	    right.error(3,form("Different svec sizes in operator*= (%d operator*= %d)",
 		sz, right.sz));
     it->Unique();
     for (int i=0;i<sz;i++)
 	it->r->v[i+offset] *= right.r->v[i];
     return(*this);
 }

 Subsvec& Subsvec::operator*=(short right)
 {
     it->Unique();
     for (int i=0;i<sz;i++)
 	it->r->v[i+offset] *= right;
     return(*this);
 }

 svec operator-(const svec &x)
 {
     svec result(x.origin,x.origin+x.sz-1);
     for (int i=0;i<x.sz;i++)
 	result.r->v[i] = -x.r->v[i];
     return(result);
 }

 svec operator&(const svec& left, const svec& right)
 {
     if (right.sz != left.sz)
 	    left.error(3,form("Different svec sizes in operator& (%d operator& %d)",
 		left.sz, right.sz));
     svec result(left.sz);
     for (int i=0;i<left.sz;i++)
 	result.r->v[i] = left.r->v[i] & right.r->v[i];
     return(result);
 }

 svec operator&(short left,const svec& right)
 {
     svec result(right.origin,right.origin+right.sz-1);
     for (int i=0;i<right.sz;i++)
 	result.r->v[i] = left & right.r->v[i];
     return(result);
 }

 svec operator&(const svec &left,short right)
 {
     svec result(left.origin,left.origin+left.sz-1);
     for (int i=0;i<left.sz;i++)
 	result.r->v[i] = left.r->v[i] & right;
     return(result);
 }



 svec& svec::operator&=(const svec& right)
 {
     if (right.sz != sz)
 	    error(3,form("Different svec sizes in operator&= (%d operator&= %d)",
 		sz, right.sz));
     Unique();
     for (int i=0;i<sz;i++)
 	r->v[i] &= right.r->v[i];
     return(*this);
 }

 svec& svec::operator&=(short right)
 {
     Unique();
     for (int i=0;i<sz;i++)
 	r->v[i] &= right;
     return(*this);
 }

 Subsvec& Subsvec::operator&=(const svec& right)
 {
     if (right.sz != sz)
 	    right.error(3,form("Different svec sizes in operator&= (%d operator&= %d)",
 		sz, right.sz));
     it->Unique();
     for (int i=0;i<sz;i++)
 	it->r->v[i+offset] &= right.r->v[i];
     return(*this);
 }

 Subsvec& Subsvec::operator&=(short right)
 {
     it->Unique();
     for (int i=0;i<sz;i++)
 	it->r->v[i+offset] &= right;
     return(*this);
 }


 svec operator^(const svec& left, const svec& right)
 {
     if (right.sz != left.sz)
 	    left.error(3,form("Different svec sizes in operator^ (%d operator^ %d)",
 		left.sz, right.sz));
     svec result(left.sz);
     for (int i=0;i<left.sz;i++)
 	result.r->v[i] = left.r->v[i] ^ right.r->v[i];
     return(result);
 }

 svec operator^(short left,const svec& right)
 {
     svec result(right.origin,right.origin+right.sz-1);
     for (int i=0;i<right.sz;i++)
 	result.r->v[i] = left ^ right.r->v[i];
     return(result);
 }

 svec operator^(const svec &left,short right)
 {
     svec result(left.origin,left.origin+left.sz-1);
     for (int i=0;i<left.sz;i++)
 	result.r->v[i] = left.r->v[i] ^ right;
     return(result);
 }



 svec& svec::operator^=(const svec& right)
 {
     if (right.sz != sz)
 	    error(3,form("Different svec sizes in operator^= (%d operator^= %d)",
 		sz, right.sz));
     Unique();
     for (int i=0;i<sz;i++)
 	r->v[i] ^= right.r->v[i];
     return(*this);
 }

 svec& svec::operator^=(short right)
 {
     Unique();
     for (int i=0;i<sz;i++)
 	r->v[i] ^= right;
     return(*this);
 }

 Subsvec& Subsvec::operator^=(const svec& right)
 {
     if (right.sz != sz)
 	    right.error(3,form("Different svec sizes in operator^= (%d operator^= %d)",
 		sz, right.sz));
     it->Unique();
     for (int i=0;i<sz;i++)
 	it->r->v[i+offset] ^= right.r->v[i];
     return(*this);
 }

 Subsvec& Subsvec::operator^=(short right)
 {
     it->Unique();
     for (int i=0;i<sz;i++)
 	it->r->v[i+offset] ^= right;
     return(*this);
 }

 svec operator~(const svec &x)
 {
     svec result(x.origin,x.origin+x.sz-1);
     for (int i=0;i<x.sz;i++)
 	result.r->v[i] = ~x.r->v[i];
     return(result);
 }

 svec operator|(const svec& left, const svec& right)
 {
     if (right.sz != left.sz)
 	    left.error(3,form("Different svec sizes in operator| (%d operator| %d)",
 		left.sz, right.sz));
     svec result(left.sz);
     for (int i=0;i<left.sz;i++)
 	result.r->v[i] = left.r->v[i] | right.r->v[i];
     return(result);
 }

 svec operator|(short left,const svec& right)
 {
     svec result(right.origin,right.origin+right.sz-1);
     for (int i=0;i<right.sz;i++)
 	result.r->v[i] = left | right.r->v[i];
     return(result);
 }

 svec operator|(const svec &left,short right)
 {
     svec result(left.origin,left.origin+left.sz-1);
     for (int i=0;i<left.sz;i++)
 	result.r->v[i] = left.r->v[i] | right;
     return(result);
 }



 svec& svec::operator|=(const svec& right)
 {
     if (right.sz != sz)
 	    error(3,form("Different svec sizes in operator|= (%d operator|= %d)",
 		sz, right.sz));
     Unique();
     for (int i=0;i<sz;i++)
 	r->v[i] |= right.r->v[i];
     return(*this);
 }

 svec& svec::operator|=(short right)
 {
     Unique();
     for (int i=0;i<sz;i++)
 	r->v[i] |= right;
     return(*this);
 }

 Subsvec& Subsvec::operator|=(const svec& right)
 {
     if (right.sz != sz)
 	    right.error(3,form("Different svec sizes in operator|= (%d operator|= %d)",
 		sz, right.sz));
     it->Unique();
     for (int i=0;i<sz;i++)
 	it->r->v[i+offset] |= right.r->v[i];
     return(*this);
 }

 Subsvec& Subsvec::operator|=(short right)
 {
     it->Unique();
     for (int i=0;i<sz;i++)
 	it->r->v[i+offset] |= right;
     return(*this);
 }

 ivec operator==(const svec& left, const svec& right)
 {
     if (right.size() != left.sz)
 	left.error(3,form("Different svec sizes in operator== (%d operator== %d)",
 	    left.sz, right.size()));
     ivec result(left.sz);
     for (int i=0;i<left.sz;i++)
 	result[i] = left.r->v[i] == right.r->v[i];
     return(result);
 }

 ivec operator==(const svec& left, short right)
 {
     ivec result(left.sz);
     for (int i=0;i<left.sz;i++)
 	result[i] = left.r->v[i] == right;
     return(result);
 }

 ivec operator==(short left,const svec& right)
 {
     ivec result(right.size());
     for (int i=0;i<right.size();i++)
 	result[i] = left == right.r->v[i];
     return(result);
 }
 ivec operator!=(const svec& left, const svec& right)
 {
     if (right.size() != left.sz)
 	left.error(3,form("Different svec sizes in operator!= (%d operator!= %d)",
 	    left.sz, right.size()));
     ivec result(left.sz);
     for (int i=0;i<left.sz;i++)
 	result[i] = left.r->v[i] != right.r->v[i];
     return(result);
 }

 ivec operator!=(const svec& left, short right)
 {
     ivec result(left.sz);
     for (int i=0;i<left.sz;i++)
 	result[i] = left.r->v[i] != right;
     return(result);
 }

 ivec operator!=(short left,const svec& right)
 {
     ivec result(right.size());
     for (int i=0;i<right.size();i++)
 	result[i] = left != right.r->v[i];
     return(result);
 }
 ivec operator>=(const svec& left, const svec& right)
 {
     if (right.size() != left.sz)
 	left.error(3,form("Different svec sizes in operator>= (%d operator>= %d)",
 	    left.sz, right.size()));
     ivec result(left.sz);
     for (int i=0;i<left.sz;i++)
 	result[i] = left.r->v[i] >= right.r->v[i];
     return(result);
 }

 ivec operator>=(const svec& left, short right)
 {
     ivec result(left.sz);
     for (int i=0;i<left.sz;i++)
 	result[i] = left.r->v[i] >= right;
     return(result);
 }

 ivec operator>=(short left,const svec& right)
 {
     ivec result(right.size());
     for (int i=0;i<right.size();i++)
 	result[i] = left >= right.r->v[i];
     return(result);
 }
 ivec operator>(const svec& left, const svec& right)
 {
     if (right.size() != left.sz)
 	left.error(3,form("Different svec sizes in operator> (%d operator> %d)",
 	    left.sz, right.size()));
     ivec result(left.sz);
     for (int i=0;i<left.sz;i++)
 	result[i] = left.r->v[i] > right.r->v[i];
     return(result);
 }

 ivec operator>(const svec& left, short right)
 {
     ivec result(left.sz);
     for (int i=0;i<left.sz;i++)
 	result[i] = left.r->v[i] > right;
     return(result);
 }

 ivec operator>(short left,const svec& right)
 {
     ivec result(right.size());
     for (int i=0;i<right.size();i++)
 	result[i] = left > right.r->v[i];
     return(result);
 }
 ivec operator<=(const svec& left, const svec& right)
 {
     if (right.size() != left.sz)
 	left.error(3,form("Different svec sizes in operator<= (%d operator<= %d)",
 	    left.sz, right.size()));
     ivec result(left.sz);
     for (int i=0;i<left.sz;i++)
 	result[i] = left.r->v[i] <= right.r->v[i];
     return(result);
 }

 ivec operator<=(const svec& left, short right)
 {
     ivec result(left.sz);
     for (int i=0;i<left.sz;i++)
 	result[i] = left.r->v[i] <= right;
     return(result);
 }

 ivec operator<=(short left,const svec& right)
 {
     ivec result(right.size());
     for (int i=0;i<right.size();i++)
 	result[i] = left <= right.r->v[i];
     return(result);
 }
 ivec operator<(const svec& left, const svec& right)
 {
     if (right.size() != left.sz)
 	left.error(3,form("Different svec sizes in operator< (%d operator< %d)",
 	    left.sz, right.size()));
     ivec result(left.sz);
     for (int i=0;i<left.sz;i++)
 	result[i] = left.r->v[i] < right.r->v[i];
     return(result);
 }

 ivec operator<(const svec& left, short right)
 {
     ivec result(left.sz);
     for (int i=0;i<left.sz;i++)
 	result[i] = left.r->v[i] < right;
     return(result);
 }

 ivec operator<(short left,const svec& right)
 {
     ivec result(right.size());
     for (int i=0;i<right.size();i++)
 	result[i] = left < right.r->v[i];
     return(result);
 }
Subsvec svec::operator()(int first, int last)
{
    if ((first < origin) || (first >= origin+sz))
	error(3,form("Bad first index for svec::subvec (%d)",first));
    if ((last < origin) || (last >= origin+sz))
	error(3,form("Bad last index for svec::subvec (%d)",last));
    if (last < first)
	error(3,form("First index > last index in svec::subvec (%d>%d)",
		first,last));
    return Subsvec(this, first-origin, last-first+1);
}
const Subsvec svec::operator()(int first, int last) const
{
    if ((first < origin) || (first >= origin+sz))
	error(3,form("Bad first index for svec::subvec (%d)",first));
    if ((last < origin) || (last >= origin+sz))
	error(3,form("Bad last index for svec::subvec (%d)",last));
    if (last < first)
	error(3,form("First index > last index in svec::subvec (%d>%d)",
		first,last));
    return Subsvec((svec *)this, first-origin, last-first+1);
}
svec& svec::operator=(const svec& right)
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
svec& svec::operator=(short right)
{
    Unique();
    for (int i=0;i<sz;i++) r->v[i] = right;
    return(*this);
}
Subsvec& Subsvec::operator=(const svec& right)
{
    if (right.sz != sz)	{
	it->error(3,form("Different svec sizes in OP= (%d OP= %d)",
	    sz, right.sz));
	}
    it->Unique();
    mov(&it->r->v[offset],right.r->v,sz);
    return(*this);
}
Subsvec& Subsvec::operator=(short right)
{
    it->Unique();
    for (int i=0;i<sz;i++) it->r->v[i+offset] = right;
    return(*this);
}
void svec::set_size(int s)
{
    if (s<0) error(4,"set_size: bad new svec size");
    if (s > r->allocsz) {
	svec_Rep *newrep = new_svec_Rep(s);
	mov(newrep->v,r->v,sz);
	r->Dec();
	r = newrep;
	}
    sz = s;
}
GPT svec::sethandler(GPT a)
{
    GPT oo = handler;
    handler = a;
    return oo;
}
ostream& operator<<(ostream& s,const svec& it)
{
    s << "[ ";
    if (it.sz)
	s << it.r->v[0];
    for (int i=1;i<it.sz;i++)
	s << " " << it.r->v[i];
    s << "]";
    return(s);
}
istream& operator>>(istream& s,svec& it)
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
ostream& svec::BinaryWrite(ostream& s) const
{
    if (sz)
	s.write((char *)r->v,sizeof(r->v[0])*sz);
    return s;
}
istream& svec::BinaryRead(istream &s,int nelem)
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
int equal(const svec& left, const svec& right)
{
    if (right.size() != left.size())
	return 0;
    for (int i=0;i<right.size();i++)
	if (left.r->v[i] != right.r->v[i])
	    return 0;
    return 1;
}
short dot(const svec& left, const svec& right)
{
    if (right.sz != left.sz)
	left.error(3,form("Different svec sizes in dot (%d and %d)",
	    left.sz, right.sz));
    short result=0;
    for (int i=0;i<left.sz;i++) result += left.r->v[i]*right.r->v[i];
    return(result);
}
/**//**/
 ucvec::ucvec(const svec& a)
 {
     sz = a.size();
     origin = a.orig();
     r = new_ucvec_Rep(sz);
     for (int i=0;i<sz;i++)
 	r->v[i] = (unsigned char)a.GetElem(i);
 }
 cvec::cvec(const svec& a)
 {
     sz = a.size();
     origin = a.orig();
     r = new_cvec_Rep(sz);
     for (int i=0;i<sz;i++)
 	r->v[i] = (char)a.GetElem(i);
 }
 ivec::ivec(const svec& a)
 {
     sz = a.size();
     origin = a.orig();
     r = new_ivec_Rep(sz);
     for (int i=0;i<sz;i++)
 	r->v[i] = (int)a.GetElem(i);
 }
 fvec::fvec(const svec& a)
 {
     sz = a.size();
     origin = a.orig();
     r = new_fvec_Rep(sz);
     for (int i=0;i<sz;i++)
 	r->v[i] = (float)a.GetElem(i);
 }
 dvec::dvec(const svec& a)
 {
     sz = a.size();
     origin = a.orig();
     r = new_dvec_Rep(sz);
     for (int i=0;i<sz;i++)
 	r->v[i] = (double)a.GetElem(i);
 }
 fcxvec::fcxvec(const svec& a)
 {
     sz = a.size();
     origin = a.orig();
     r = new_fcxvec_Rep(sz);
     for (int i=0;i<sz;i++)
 	r->v[i] = (scomplex)a.GetElem(i);
 }
 dcxvec::dcxvec(const svec& a)
 {
     sz = a.size();
     origin = a.orig();
     r = new_dcxvec_Rep(sz);
     for (int i=0;i<sz;i++)
 	r->v[i] = (complex)a.GetElem(i);
 }
