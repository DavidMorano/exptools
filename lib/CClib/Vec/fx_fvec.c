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
 fvec abs(const fvec &x)
 {
     fvec result(x.origin,x.origin+x.sz-1);
     ::abs(result.r->v,x.r->v,x.sz);
     return(result);
 }
 fvec min(const fvec& left, const fvec& right)
 {
     if (right.sz != left.sz)
 	    left.error(3,form("Different fvec sizes in min (%d min %d)",
 		left.sz, right.sz));
     fvec result(left.sz);
     ::min(result.r->v,left.r->v,right.r->v,left.sz);
     return(result);
 }

 fvec min(float left,const fvec& right)
 {
     fvec result(right.origin,right.origin+right.sz-1);
     ::min(result.r->v,left,right.r->v,right.sz);
     return(result);
 }

 fvec min(const fvec &left,float right)
 {
     fvec result(left.origin,left.origin+left.sz-1);
     ::min(result.r->v,left.r->v,right,left.sz);
     return(result);
 }

 fvec max(const fvec& left, const fvec& right)
 {
     if (right.sz != left.sz)
 	    left.error(3,form("Different fvec sizes in max (%d max %d)",
 		left.sz, right.sz));
     fvec result(left.sz);
     ::max(result.r->v,left.r->v,right.r->v,left.sz);
     return(result);
 }

 fvec max(float left,const fvec& right)
 {
     fvec result(right.origin,right.origin+right.sz-1);
     ::max(result.r->v,left,right.r->v,right.sz);
     return(result);
 }

 fvec max(const fvec &left,float right)
 {
     fvec result(left.origin,left.origin+left.sz-1);
     ::max(result.r->v,left.r->v,right,left.sz);
     return(result);
 }

 float max(const fvec &x)
 {
     if (x.sz == 0) x.error(3,"Attempt to calculate max of length 0 fvec");
     return(::max(x.r->v,x.sz));
 }
 float min(const fvec &x)
 {
     if (x.sz == 0) x.error(3,"Attempt to calculate min of length 0 fvec");
     return(::min(x.r->v,x.sz));
 }
 float sum(const fvec &x)
 {
     if (x.sz == 0) x.error(3,"Attempt to calculate sum of length 0 fvec");
     return(::sum(x.r->v,x.sz));
 }
 float prod(const fvec &x)
 {
     if (x.sz == 0) x.error(3,"Attempt to calculate prod of length 0 fvec");
     return(::prod(x.r->v,x.sz));
 }

 fvec operator+(const fvec& left, const fvec& right)
 {
     if (right.sz != left.sz)
 	    left.error(3,form("Different fvec sizes in operator+ (%d operator+ %d)",
 		left.sz, right.sz));
     fvec result(left.sz);
     add(result.r->v,left.r->v,right.r->v,left.sz);
     return(result);
 }

 fvec operator+(float left,const fvec& right)
 {
     fvec result(right.origin,right.origin+right.sz-1);
     add(result.r->v,left,right.r->v,right.sz);
     return(result);
 }

 fvec operator+(const fvec &left,float right)
 {
     fvec result(left.origin,left.origin+left.sz-1);
     add(result.r->v,left.r->v,right,left.sz);
     return(result);
 }



 fvec& fvec::operator+=(const fvec& right)
 {
     if (right.sz != sz)
 	    error(3,form("Different fvec sizes in operator+= (%d operator+= %d)",
 		sz, right.sz));
     Unique();
     add(r->v,r->v,right.r->v,sz);
     return(*this);
 }

 fvec& fvec::operator+=(float right)
 {
     Unique();
     add(r->v,r->v,right,sz);
     return(*this);
 }

 Subfvec& Subfvec::operator+=(const fvec& right)
 {
     if (right.sz != sz)
 	    right.error(3,form("Different fvec sizes in operator+= (%d operator+= %d)",
 		sz, right.sz));
     it->Unique();
     add(&it->r->v[offset],&it->r->v[offset],right.r->v,sz);
     return(*this);
 }

 Subfvec& Subfvec::operator+=(float right)
 {
     it->Unique();
     add(&it->r->v[offset],&it->r->v[offset],right,sz);
     return(*this);
 }


 fvec operator-(const fvec& left, const fvec& right)
 {
     if (right.sz != left.sz)
 	    left.error(3,form("Different fvec sizes in operator- (%d operator- %d)",
 		left.sz, right.sz));
     fvec result(left.sz);
     sub(result.r->v,left.r->v,right.r->v,left.sz);
     return(result);
 }

 fvec operator-(float left,const fvec& right)
 {
     fvec result(right.origin,right.origin+right.sz-1);
     sub(result.r->v,left,right.r->v,right.sz);
     return(result);
 }

 fvec operator-(const fvec &left,float right)
 {
     fvec result(left.origin,left.origin+left.sz-1);
     sub(result.r->v,left.r->v,right,left.sz);
     return(result);
 }



 fvec& fvec::operator-=(const fvec& right)
 {
     if (right.sz != sz)
 	    error(3,form("Different fvec sizes in operator-= (%d operator-= %d)",
 		sz, right.sz));
     Unique();
     sub(r->v,r->v,right.r->v,sz);
     return(*this);
 }

 fvec& fvec::operator-=(float right)
 {
     Unique();
     sub(r->v,r->v,right,sz);
     return(*this);
 }

 Subfvec& Subfvec::operator-=(const fvec& right)
 {
     if (right.sz != sz)
 	    right.error(3,form("Different fvec sizes in operator-= (%d operator-= %d)",
 		sz, right.sz));
     it->Unique();
     sub(&it->r->v[offset],&it->r->v[offset],right.r->v,sz);
     return(*this);
 }

 Subfvec& Subfvec::operator-=(float right)
 {
     it->Unique();
     sub(&it->r->v[offset],&it->r->v[offset],right,sz);
     return(*this);
 }


 fvec operator/(const fvec& left, const fvec& right)
 {
     if (right.sz != left.sz)
 	    left.error(3,form("Different fvec sizes in operator/ (%d operator/ %d)",
 		left.sz, right.sz));
     fvec result(left.sz);
     div(result.r->v,left.r->v,right.r->v,left.sz);
     return(result);
 }

 fvec operator/(float left,const fvec& right)
 {
     fvec result(right.origin,right.origin+right.sz-1);
     div(result.r->v,left,right.r->v,right.sz);
     return(result);
 }

 fvec operator/(const fvec &left,float right)
 {
     fvec result(left.origin,left.origin+left.sz-1);
     div(result.r->v,left.r->v,right,left.sz);
     return(result);
 }



 fvec& fvec::operator/=(const fvec& right)
 {
     if (right.sz != sz)
 	    error(3,form("Different fvec sizes in operator/= (%d operator/= %d)",
 		sz, right.sz));
     Unique();
     div(r->v,r->v,right.r->v,sz);
     return(*this);
 }

 fvec& fvec::operator/=(float right)
 {
     Unique();
     div(r->v,r->v,right,sz);
     return(*this);
 }

 Subfvec& Subfvec::operator/=(const fvec& right)
 {
     if (right.sz != sz)
 	    right.error(3,form("Different fvec sizes in operator/= (%d operator/= %d)",
 		sz, right.sz));
     it->Unique();
     div(&it->r->v[offset],&it->r->v[offset],right.r->v,sz);
     return(*this);
 }

 Subfvec& Subfvec::operator/=(float right)
 {
     it->Unique();
     div(&it->r->v[offset],&it->r->v[offset],right,sz);
     return(*this);
 }


 fvec operator*(const fvec& left, const fvec& right)
 {
     if (right.sz != left.sz)
 	    left.error(3,form("Different fvec sizes in operator* (%d operator* %d)",
 		left.sz, right.sz));
     fvec result(left.sz);
     mul(result.r->v,left.r->v,right.r->v,left.sz);
     return(result);
 }

 fvec operator*(float left,const fvec& right)
 {
     fvec result(right.origin,right.origin+right.sz-1);
     mul(result.r->v,left,right.r->v,right.sz);
     return(result);
 }

 fvec operator*(const fvec &left,float right)
 {
     fvec result(left.origin,left.origin+left.sz-1);
     mul(result.r->v,left.r->v,right,left.sz);
     return(result);
 }



 fvec& fvec::operator*=(const fvec& right)
 {
     if (right.sz != sz)
 	    error(3,form("Different fvec sizes in operator*= (%d operator*= %d)",
 		sz, right.sz));
     Unique();
     mul(r->v,r->v,right.r->v,sz);
     return(*this);
 }

 fvec& fvec::operator*=(float right)
 {
     Unique();
     mul(r->v,r->v,right,sz);
     return(*this);
 }

 Subfvec& Subfvec::operator*=(const fvec& right)
 {
     if (right.sz != sz)
 	    right.error(3,form("Different fvec sizes in operator*= (%d operator*= %d)",
 		sz, right.sz));
     it->Unique();
     mul(&it->r->v[offset],&it->r->v[offset],right.r->v,sz);
     return(*this);
 }

 Subfvec& Subfvec::operator*=(float right)
 {
     it->Unique();
     mul(&it->r->v[offset],&it->r->v[offset],right,sz);
     return(*this);
 }

 fvec operator-(const fvec &x)
 {
     fvec result(x.origin,x.origin+x.sz-1);
     neg(result.r->v,x.r->v,x.sz);
     return(result);
 }
 ivec operator==(const fvec& left, const fvec& right)
 {
     if (right.size() != left.sz)
 	left.error(3,form("Different fvec sizes in operator== (%d operator== %d)",
 	    left.sz, right.size()));
     ivec result(left.sz);
     eq(&result[0],left.r->v,right.r->v,left.sz);
     return(result);
 }

 ivec operator==(const fvec& left, float right)
 {
     ivec result(left.sz);
     eq(&result[0],left.r->v,right,left.sz);
     return(result);
 }

 ivec operator==(float left,const fvec& right)
 {
     ivec result(right.size());
     eq(&result[0],left,right.r->v,right.sz);
     return(result);
 }
 ivec operator!=(const fvec& left, const fvec& right)
 {
     if (right.size() != left.sz)
 	left.error(3,form("Different fvec sizes in operator!= (%d operator!= %d)",
 	    left.sz, right.size()));
     ivec result(left.sz);
     ne(&result[0],left.r->v,right.r->v,left.sz);
     return(result);
 }

 ivec operator!=(const fvec& left, float right)
 {
     ivec result(left.sz);
     ne(&result[0],left.r->v,right,left.sz);
     return(result);
 }

 ivec operator!=(float left,const fvec& right)
 {
     ivec result(right.size());
     ne(&result[0],left,right.r->v,right.sz);
     return(result);
 }
 ivec operator>=(const fvec& left, const fvec& right)
 {
     if (right.size() != left.sz)
 	left.error(3,form("Different fvec sizes in operator>= (%d operator>= %d)",
 	    left.sz, right.size()));
     ivec result(left.sz);
     ge(&result[0],left.r->v,right.r->v,left.sz);
     return(result);
 }

 ivec operator>=(const fvec& left, float right)
 {
     ivec result(left.sz);
     ge(&result[0],left.r->v,right,left.sz);
     return(result);
 }

 ivec operator>=(float left,const fvec& right)
 {
     ivec result(right.size());
     ge(&result[0],left,right.r->v,right.sz);
     return(result);
 }
 ivec operator>(const fvec& left, const fvec& right)
 {
     if (right.size() != left.sz)
 	left.error(3,form("Different fvec sizes in operator> (%d operator> %d)",
 	    left.sz, right.size()));
     ivec result(left.sz);
     gt(&result[0],left.r->v,right.r->v,left.sz);
     return(result);
 }

 ivec operator>(const fvec& left, float right)
 {
     ivec result(left.sz);
     gt(&result[0],left.r->v,right,left.sz);
     return(result);
 }

 ivec operator>(float left,const fvec& right)
 {
     ivec result(right.size());
     gt(&result[0],left,right.r->v,right.sz);
     return(result);
 }
 ivec operator<=(const fvec& left, const fvec& right)
 {
     if (right.size() != left.sz)
 	left.error(3,form("Different fvec sizes in operator<= (%d operator<= %d)",
 	    left.sz, right.size()));
     ivec result(left.sz);
     le(&result[0],left.r->v,right.r->v,left.sz);
     return(result);
 }

 ivec operator<=(const fvec& left, float right)
 {
     ivec result(left.sz);
     le(&result[0],left.r->v,right,left.sz);
     return(result);
 }

 ivec operator<=(float left,const fvec& right)
 {
     ivec result(right.size());
     le(&result[0],left,right.r->v,right.sz);
     return(result);
 }
 ivec operator<(const fvec& left, const fvec& right)
 {
     if (right.size() != left.sz)
 	left.error(3,form("Different fvec sizes in operator< (%d operator< %d)",
 	    left.sz, right.size()));
     ivec result(left.sz);
     lt(&result[0],left.r->v,right.r->v,left.sz);
     return(result);
 }

 ivec operator<(const fvec& left, float right)
 {
     ivec result(left.sz);
     lt(&result[0],left.r->v,right,left.sz);
     return(result);
 }

 ivec operator<(float left,const fvec& right)
 {
     ivec result(right.size());
     lt(&result[0],left,right.r->v,right.sz);
     return(result);
 }
Subfvec fvec::operator()(int first, int last)
{
    if ((first < origin) || (first >= origin+sz))
	error(3,form("Bad first index for fvec::subvec (%d)",first));
    if ((last < origin) || (last >= origin+sz))
	error(3,form("Bad last index for fvec::subvec (%d)",last));
    if (last < first)
	error(3,form("First index > last index in fvec::subvec (%d>%d)",
		first,last));
    return Subfvec(this, first-origin, last-first+1);
}
const Subfvec fvec::operator()(int first, int last) const
{
    if ((first < origin) || (first >= origin+sz))
	error(3,form("Bad first index for fvec::subvec (%d)",first));
    if ((last < origin) || (last >= origin+sz))
	error(3,form("Bad last index for fvec::subvec (%d)",last));
    if (last < first)
	error(3,form("First index > last index in fvec::subvec (%d>%d)",
		first,last));
    return Subfvec((fvec *)this, first-origin, last-first+1);
}
fvec& fvec::operator=(const fvec& right)
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
fvec& fvec::operator=(float right)
{
    Unique();
    set(r->v,right,sz);
    return(*this);
}
Subfvec& Subfvec::operator=(const fvec& right)
{
    if (right.sz != sz)	{
	it->error(3,form("Different fvec sizes in OP= (%d OP= %d)",
	    sz, right.sz));
	}
    it->Unique();
    mov(&it->r->v[offset],right.r->v,sz);
    return(*this);
}
Subfvec& Subfvec::operator=(float right)
{
    it->Unique();
    set(&it->r->v[offset],right,sz);
    return(*this);
}
void fvec::set_size(int s)
{
    if (s<0) error(4,"set_size: bad new fvec size");
    if (s > r->allocsz) {
	fvec_Rep *newrep = new_fvec_Rep(s);
	mov(newrep->v,r->v,sz);
	r->Dec();
	r = newrep;
	}
    sz = s;
}
GPT fvec::sethandler(GPT a)
{
    GPT oo = handler;
    handler = a;
    return oo;
}
ostream& operator<<(ostream& s,const fvec& it)
{
    s << "[ ";
    if (it.sz)
	s << it.r->v[0];
    for (int i=1;i<it.sz;i++)
	s << " " << it.r->v[i];
    s << "]";
    return(s);
}
istream& operator>>(istream& s,fvec& it)
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
ostream& fvec::BinaryWrite(ostream& s) const
{
    if (sz)
	s.write((char *)r->v,sizeof(r->v[0])*sz);
    return s;
}
istream& fvec::BinaryRead(istream &s,int nelem)
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
int equal(const fvec& left, const fvec& right)
{
    if (right.size() != left.size())
	return 0;
    for (int i=0;i<right.size();i++)
	if (left.r->v[i] != right.r->v[i])
	    return 0;
    return 1;
}
float dot(const fvec& left, const fvec& right)
{
    if (right.sz != left.sz)
	left.error(3,form("Different fvec sizes in dot (%d and %d)",
	    left.sz, right.sz));
    return(::dot(left.r->v,right.r->v,left.sz));
}
/**//**/
 ucvec::ucvec(const fvec& a)
 {
     sz = a.size();
     origin = a.orig();
     r = new_ucvec_Rep(sz);
     for (int i=0;i<sz;i++)
 	r->v[i] = (unsigned char)a.GetElem(i);
 }
 cvec::cvec(const fvec& a)
 {
     sz = a.size();
     origin = a.orig();
     r = new_cvec_Rep(sz);
     for (int i=0;i<sz;i++)
 	r->v[i] = (char)a.GetElem(i);
 }
 svec::svec(const fvec& a)
 {
     sz = a.size();
     origin = a.orig();
     r = new_svec_Rep(sz);
     for (int i=0;i<sz;i++)
 	r->v[i] = (short)a.GetElem(i);
 }
 ivec::ivec(const fvec& a)
 {
     sz = a.size();
     origin = a.orig();
     r = new_ivec_Rep(sz);
     for (int i=0;i<sz;i++)
 	r->v[i] = (int)a.GetElem(i);
 }
 dvec::dvec(const fvec& a)
 {
     sz = a.size();
     origin = a.orig();
     r = new_dvec_Rep(sz);
     for (int i=0;i<sz;i++)
 	r->v[i] = (double)a.GetElem(i);
 }
 fcxvec::fcxvec(const fvec& a)
 {
     sz = a.size();
     origin = a.orig();
     r = new_fcxvec_Rep(sz);
     for (int i=0;i<sz;i++)
 	r->v[i] = (scomplex)a.GetElem(i);
 }
 dcxvec::dcxvec(const fvec& a)
 {
     sz = a.size();
     origin = a.orig();
     r = new_dcxvec_Rep(sz);
     for (int i=0;i<sz;i++)
 	r->v[i] = (complex)a.GetElem(i);
 }
