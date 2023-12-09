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
 scomplex sum(const fcxvec &x)
 {
     if (x.sz == 0) x.error(3,"Attempt to calculate sum of length 0 fcxvec");
     scomplex result=x.r->v[0];
     for (int i=1;i<x.sz;i++)
 	result+=x.r->v[i];
     return(result);
 }
 scomplex prod(const fcxvec &x)
 {
     if (x.sz == 0) x.error(3,"Attempt to calculate prod of length 0 fcxvec");
     scomplex result=x.r->v[0];
     for (int i=1;i<x.sz;i++)
 	result*=x.r->v[i];
     return(result);
 }

 fcxvec operator+(const fcxvec& left, const fcxvec& right)
 {
     if (right.sz != left.sz)
 	    left.error(3,form("Different fcxvec sizes in operator+ (%d operator+ %d)",
 		left.sz, right.sz));
     fcxvec result(left.sz);
     for (int i=0;i<left.sz;i++)
 	result.r->v[i] = left.r->v[i] + right.r->v[i];
     return(result);
 }

 fcxvec operator+(scomplex left,const fcxvec& right)
 {
     fcxvec result(right.origin,right.origin+right.sz-1);
     for (int i=0;i<right.sz;i++)
 	result.r->v[i] = left + right.r->v[i];
     return(result);
 }

 fcxvec operator+(const fcxvec &left,scomplex right)
 {
     fcxvec result(left.origin,left.origin+left.sz-1);
     for (int i=0;i<left.sz;i++)
 	result.r->v[i] = left.r->v[i] + right;
     return(result);
 }



 fcxvec& fcxvec::operator+=(const fcxvec& right)
 {
     if (right.sz != sz)
 	    error(3,form("Different fcxvec sizes in operator+= (%d operator+= %d)",
 		sz, right.sz));
     Unique();
     for (int i=0;i<sz;i++)
 	r->v[i] += right.r->v[i];
     return(*this);
 }

 fcxvec& fcxvec::operator+=(scomplex right)
 {
     Unique();
     for (int i=0;i<sz;i++)
 	r->v[i] += right;
     return(*this);
 }

 Subfcxvec& Subfcxvec::operator+=(const fcxvec& right)
 {
     if (right.sz != sz)
 	    right.error(3,form("Different fcxvec sizes in operator+= (%d operator+= %d)",
 		sz, right.sz));
     it->Unique();
     for (int i=0;i<sz;i++)
 	it->r->v[i+offset] += right.r->v[i];
     return(*this);
 }

 Subfcxvec& Subfcxvec::operator+=(scomplex right)
 {
     it->Unique();
     for (int i=0;i<sz;i++)
 	it->r->v[i+offset] += right;
     return(*this);
 }


 fcxvec operator-(const fcxvec& left, const fcxvec& right)
 {
     if (right.sz != left.sz)
 	    left.error(3,form("Different fcxvec sizes in operator- (%d operator- %d)",
 		left.sz, right.sz));
     fcxvec result(left.sz);
     for (int i=0;i<left.sz;i++)
 	result.r->v[i] = left.r->v[i] - right.r->v[i];
     return(result);
 }

 fcxvec operator-(scomplex left,const fcxvec& right)
 {
     fcxvec result(right.origin,right.origin+right.sz-1);
     for (int i=0;i<right.sz;i++)
 	result.r->v[i] = left - right.r->v[i];
     return(result);
 }

 fcxvec operator-(const fcxvec &left,scomplex right)
 {
     fcxvec result(left.origin,left.origin+left.sz-1);
     for (int i=0;i<left.sz;i++)
 	result.r->v[i] = left.r->v[i] - right;
     return(result);
 }



 fcxvec& fcxvec::operator-=(const fcxvec& right)
 {
     if (right.sz != sz)
 	    error(3,form("Different fcxvec sizes in operator-= (%d operator-= %d)",
 		sz, right.sz));
     Unique();
     for (int i=0;i<sz;i++)
 	r->v[i] -= right.r->v[i];
     return(*this);
 }

 fcxvec& fcxvec::operator-=(scomplex right)
 {
     Unique();
     for (int i=0;i<sz;i++)
 	r->v[i] -= right;
     return(*this);
 }

 Subfcxvec& Subfcxvec::operator-=(const fcxvec& right)
 {
     if (right.sz != sz)
 	    right.error(3,form("Different fcxvec sizes in operator-= (%d operator-= %d)",
 		sz, right.sz));
     it->Unique();
     for (int i=0;i<sz;i++)
 	it->r->v[i+offset] -= right.r->v[i];
     return(*this);
 }

 Subfcxvec& Subfcxvec::operator-=(scomplex right)
 {
     it->Unique();
     for (int i=0;i<sz;i++)
 	it->r->v[i+offset] -= right;
     return(*this);
 }


 fcxvec operator/(const fcxvec& left, const fcxvec& right)
 {
     if (right.sz != left.sz)
 	    left.error(3,form("Different fcxvec sizes in operator/ (%d operator/ %d)",
 		left.sz, right.sz));
     fcxvec result(left.sz);
     for (int i=0;i<left.sz;i++)
 	result.r->v[i] = left.r->v[i] / right.r->v[i];
     return(result);
 }

 fcxvec operator/(scomplex left,const fcxvec& right)
 {
     fcxvec result(right.origin,right.origin+right.sz-1);
     for (int i=0;i<right.sz;i++)
 	result.r->v[i] = left / right.r->v[i];
     return(result);
 }

 fcxvec operator/(const fcxvec &left,scomplex right)
 {
     fcxvec result(left.origin,left.origin+left.sz-1);
     for (int i=0;i<left.sz;i++)
 	result.r->v[i] = left.r->v[i] / right;
     return(result);
 }



 fcxvec& fcxvec::operator/=(const fcxvec& right)
 {
     if (right.sz != sz)
 	    error(3,form("Different fcxvec sizes in operator/= (%d operator/= %d)",
 		sz, right.sz));
     Unique();
     for (int i=0;i<sz;i++)
 	r->v[i] /= right.r->v[i];
     return(*this);
 }

 fcxvec& fcxvec::operator/=(scomplex right)
 {
     Unique();
     for (int i=0;i<sz;i++)
 	r->v[i] /= right;
     return(*this);
 }

 Subfcxvec& Subfcxvec::operator/=(const fcxvec& right)
 {
     if (right.sz != sz)
 	    right.error(3,form("Different fcxvec sizes in operator/= (%d operator/= %d)",
 		sz, right.sz));
     it->Unique();
     for (int i=0;i<sz;i++)
 	it->r->v[i+offset] /= right.r->v[i];
     return(*this);
 }

 Subfcxvec& Subfcxvec::operator/=(scomplex right)
 {
     it->Unique();
     for (int i=0;i<sz;i++)
 	it->r->v[i+offset] /= right;
     return(*this);
 }


 fcxvec operator*(const fcxvec& left, const fcxvec& right)
 {
     if (right.sz != left.sz)
 	    left.error(3,form("Different fcxvec sizes in operator* (%d operator* %d)",
 		left.sz, right.sz));
     fcxvec result(left.sz);
     for (int i=0;i<left.sz;i++)
 	result.r->v[i] = left.r->v[i] * right.r->v[i];
     return(result);
 }

 fcxvec operator*(scomplex left,const fcxvec& right)
 {
     fcxvec result(right.origin,right.origin+right.sz-1);
     for (int i=0;i<right.sz;i++)
 	result.r->v[i] = left * right.r->v[i];
     return(result);
 }

 fcxvec operator*(const fcxvec &left,scomplex right)
 {
     fcxvec result(left.origin,left.origin+left.sz-1);
     for (int i=0;i<left.sz;i++)
 	result.r->v[i] = left.r->v[i] * right;
     return(result);
 }



 fcxvec& fcxvec::operator*=(const fcxvec& right)
 {
     if (right.sz != sz)
 	    error(3,form("Different fcxvec sizes in operator*= (%d operator*= %d)",
 		sz, right.sz));
     Unique();
     for (int i=0;i<sz;i++)
 	r->v[i] *= right.r->v[i];
     return(*this);
 }

 fcxvec& fcxvec::operator*=(scomplex right)
 {
     Unique();
     for (int i=0;i<sz;i++)
 	r->v[i] *= right;
     return(*this);
 }

 Subfcxvec& Subfcxvec::operator*=(const fcxvec& right)
 {
     if (right.sz != sz)
 	    right.error(3,form("Different fcxvec sizes in operator*= (%d operator*= %d)",
 		sz, right.sz));
     it->Unique();
     for (int i=0;i<sz;i++)
 	it->r->v[i+offset] *= right.r->v[i];
     return(*this);
 }

 Subfcxvec& Subfcxvec::operator*=(scomplex right)
 {
     it->Unique();
     for (int i=0;i<sz;i++)
 	it->r->v[i+offset] *= right;
     return(*this);
 }

 fcxvec operator-(const fcxvec &x)
 {
     fcxvec result(x.origin,x.origin+x.sz-1);
     for (int i=0;i<x.sz;i++)
 	result.r->v[i] = -x.r->v[i];
     return(result);
 }
 ivec operator==(const fcxvec& left, const fcxvec& right)
 {
     if (right.size() != left.sz)
 	left.error(3,form("Different fcxvec sizes in operator== (%d operator== %d)",
 	    left.sz, right.size()));
     ivec result(left.sz);
     for (int i=0;i<left.sz;i++)
 	result[i] = left.r->v[i] == right.r->v[i];
     return(result);
 }

 ivec operator==(const fcxvec& left, scomplex right)
 {
     ivec result(left.sz);
     for (int i=0;i<left.sz;i++)
 	result[i] = left.r->v[i] == right;
     return(result);
 }

 ivec operator==(scomplex left,const fcxvec& right)
 {
     ivec result(right.size());
     for (int i=0;i<right.size();i++)
 	result[i] = left == right.r->v[i];
     return(result);
 }
 ivec operator!=(const fcxvec& left, const fcxvec& right)
 {
     if (right.size() != left.sz)
 	left.error(3,form("Different fcxvec sizes in operator!= (%d operator!= %d)",
 	    left.sz, right.size()));
     ivec result(left.sz);
     for (int i=0;i<left.sz;i++)
 	result[i] = left.r->v[i] != right.r->v[i];
     return(result);
 }

 ivec operator!=(const fcxvec& left, scomplex right)
 {
     ivec result(left.sz);
     for (int i=0;i<left.sz;i++)
 	result[i] = left.r->v[i] != right;
     return(result);
 }

 ivec operator!=(scomplex left,const fcxvec& right)
 {
     ivec result(right.size());
     for (int i=0;i<right.size();i++)
 	result[i] = left != right.r->v[i];
     return(result);
 }
 fvec real(const fcxvec& a)
 {
     fvec result(a.orig(),a.orig()+a.size()-1);
     for (int i=0;i<a.size();i++)
 	result[i+a.orig()] = real(a.GetElem(i));
     return result;
 }
 fvec imag(const fcxvec& a)
 {
     fvec result(a.orig(),a.orig()+a.size()-1);
     for (int i=0;i<a.size();i++)
 	result[i+a.orig()] = imag(a.GetElem(i));
     return result;
 }
 fvec arg(const fcxvec& a)
 {
     fvec result(a.orig(),a.orig()+a.size()-1);
     for (int i=0;i<a.size();i++)
 	result[i+a.orig()] = arg(a.GetElem(i));
     return result;
 }
 fvec abs(const fcxvec& a)
 {
     fvec result(a.orig(),a.orig()+a.size()-1);
     for (int i=0;i<a.size();i++)
 	result[i+a.orig()] = abs(a.GetElem(i));
     return result;
 }
 fvec norm(const fcxvec& a)
 {
     fvec result(a.orig(),a.orig()+a.size()-1);
     for (int i=0;i<a.size();i++)
 	result[i+a.orig()] = norm(a.GetElem(i));
     return result;
 }
 fcxvec conj(const fcxvec& a)
 {
     fcxvec result(a.origin,a.origin+a.sz-1);
     for (int i=0;i<a.sz;i++)
 	result.r->v[i] = conj(a.r->v[i]);
     return result;
 }
Subfcxvec fcxvec::operator()(int first, int last)
{
    if ((first < origin) || (first >= origin+sz))
	error(3,form("Bad first index for fcxvec::subvec (%d)",first));
    if ((last < origin) || (last >= origin+sz))
	error(3,form("Bad last index for fcxvec::subvec (%d)",last));
    if (last < first)
	error(3,form("First index > last index in fcxvec::subvec (%d>%d)",
		first,last));
    return Subfcxvec(this, first-origin, last-first+1);
}
const Subfcxvec fcxvec::operator()(int first, int last) const
{
    if ((first < origin) || (first >= origin+sz))
	error(3,form("Bad first index for fcxvec::subvec (%d)",first));
    if ((last < origin) || (last >= origin+sz))
	error(3,form("Bad last index for fcxvec::subvec (%d)",last));
    if (last < first)
	error(3,form("First index > last index in fcxvec::subvec (%d>%d)",
		first,last));
    return Subfcxvec((fcxvec *)this, first-origin, last-first+1);
}
fcxvec& fcxvec::operator=(const fcxvec& right)
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
fcxvec& fcxvec::operator=(scomplex right)
{
    Unique();
    for (int i=0;i<sz;i++) r->v[i] = right;
    return(*this);
}
Subfcxvec& Subfcxvec::operator=(const fcxvec& right)
{
    if (right.sz != sz)	{
	it->error(3,form("Different fcxvec sizes in OP= (%d OP= %d)",
	    sz, right.sz));
	}
    it->Unique();
    mov(&it->r->v[offset],right.r->v,sz);
    return(*this);
}
Subfcxvec& Subfcxvec::operator=(scomplex right)
{
    it->Unique();
    for (int i=0;i<sz;i++) it->r->v[i+offset] = right;
    return(*this);
}
void fcxvec::set_size(int s)
{
    if (s<0) error(4,"set_size: bad new fcxvec size");
    if (s > r->allocsz) {
	fcxvec_Rep *newrep = new_fcxvec_Rep(s);
	mov(newrep->v,r->v,sz);
	r->Dec();
	r = newrep;
	}
    sz = s;
}
GPT fcxvec::sethandler(GPT a)
{
    GPT oo = handler;
    handler = a;
    return oo;
}
ostream& operator<<(ostream& s,const fcxvec& it)
{
    s << "[ ";
    if (it.sz)
	s << it.r->v[0];
    for (int i=1;i<it.sz;i++)
	s << " " << it.r->v[i];
    s << "]";
    return(s);
}
istream& operator>>(istream& s,fcxvec& it)
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
ostream& fcxvec::BinaryWrite(ostream& s) const
{
    if (sz)
	s.write((char *)r->v,sizeof(r->v[0])*sz);
    return s;
}
istream& fcxvec::BinaryRead(istream &s,int nelem)
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
int equal(const fcxvec& left, const fcxvec& right)
{
    if (right.size() != left.size())
	return 0;
    for (int i=0;i<right.size();i++)
	if (left.r->v[i] != right.r->v[i])
	    return 0;
    return 1;
}
scomplex dot(const fcxvec& left, const fcxvec& right)
{
    if (right.sz != left.sz)
	left.error(3,form("Different fcxvec sizes in dot (%d and %d)",
	    left.sz, right.sz));
    scomplex result=0;
    for (int i=0;i<left.sz;i++) result += left.r->v[i]*right.r->v[i];
    return(result);
}
/**//**/
