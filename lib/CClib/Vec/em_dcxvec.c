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
     for (int i=0;i<left.sz;i++)
 	result.r->v[i] = left.r->v[i] + right.r->v[i];
     return(result);
 }

 dcxvec operator+(complex left,const dcxvec& right)
 {
     dcxvec result(right.origin,right.origin+right.sz-1);
     for (int i=0;i<right.sz;i++)
 	result.r->v[i] = left + right.r->v[i];
     return(result);
 }

 dcxvec operator+(const dcxvec &left,complex right)
 {
     dcxvec result(left.origin,left.origin+left.sz-1);
     for (int i=0;i<left.sz;i++)
 	result.r->v[i] = left.r->v[i] + right;
     return(result);
 }



 dcxvec& dcxvec::operator+=(const dcxvec& right)
 {
     if (right.sz != sz)
 	    error(3,form("Different dcxvec sizes in operator+= (%d operator+= %d)",
 		sz, right.sz));
     Unique();
     for (int i=0;i<sz;i++)
 	r->v[i] += right.r->v[i];
     return(*this);
 }

 dcxvec& dcxvec::operator+=(complex right)
 {
     Unique();
     for (int i=0;i<sz;i++)
 	r->v[i] += right;
     return(*this);
 }

 Subdcxvec& Subdcxvec::operator+=(const dcxvec& right)
 {
     if (right.sz != sz)
 	    right.error(3,form("Different dcxvec sizes in operator+= (%d operator+= %d)",
 		sz, right.sz));
     it->Unique();
     for (int i=0;i<sz;i++)
 	it->r->v[i+offset] += right.r->v[i];
     return(*this);
 }

 Subdcxvec& Subdcxvec::operator+=(complex right)
 {
     it->Unique();
     for (int i=0;i<sz;i++)
 	it->r->v[i+offset] += right;
     return(*this);
 }


 dcxvec operator-(const dcxvec& left, const dcxvec& right)
 {
     if (right.sz != left.sz)
 	    left.error(3,form("Different dcxvec sizes in operator- (%d operator- %d)",
 		left.sz, right.sz));
     dcxvec result(left.sz);
     for (int i=0;i<left.sz;i++)
 	result.r->v[i] = left.r->v[i] - right.r->v[i];
     return(result);
 }

 dcxvec operator-(complex left,const dcxvec& right)
 {
     dcxvec result(right.origin,right.origin+right.sz-1);
     for (int i=0;i<right.sz;i++)
 	result.r->v[i] = left - right.r->v[i];
     return(result);
 }

 dcxvec operator-(const dcxvec &left,complex right)
 {
     dcxvec result(left.origin,left.origin+left.sz-1);
     for (int i=0;i<left.sz;i++)
 	result.r->v[i] = left.r->v[i] - right;
     return(result);
 }



 dcxvec& dcxvec::operator-=(const dcxvec& right)
 {
     if (right.sz != sz)
 	    error(3,form("Different dcxvec sizes in operator-= (%d operator-= %d)",
 		sz, right.sz));
     Unique();
     for (int i=0;i<sz;i++)
 	r->v[i] -= right.r->v[i];
     return(*this);
 }

 dcxvec& dcxvec::operator-=(complex right)
 {
     Unique();
     for (int i=0;i<sz;i++)
 	r->v[i] -= right;
     return(*this);
 }

 Subdcxvec& Subdcxvec::operator-=(const dcxvec& right)
 {
     if (right.sz != sz)
 	    right.error(3,form("Different dcxvec sizes in operator-= (%d operator-= %d)",
 		sz, right.sz));
     it->Unique();
     for (int i=0;i<sz;i++)
 	it->r->v[i+offset] -= right.r->v[i];
     return(*this);
 }

 Subdcxvec& Subdcxvec::operator-=(complex right)
 {
     it->Unique();
     for (int i=0;i<sz;i++)
 	it->r->v[i+offset] -= right;
     return(*this);
 }


 dcxvec operator/(const dcxvec& left, const dcxvec& right)
 {
     if (right.sz != left.sz)
 	    left.error(3,form("Different dcxvec sizes in operator/ (%d operator/ %d)",
 		left.sz, right.sz));
     dcxvec result(left.sz);
     for (int i=0;i<left.sz;i++)
 	result.r->v[i] = left.r->v[i] / right.r->v[i];
     return(result);
 }

 dcxvec operator/(complex left,const dcxvec& right)
 {
     dcxvec result(right.origin,right.origin+right.sz-1);
     for (int i=0;i<right.sz;i++)
 	result.r->v[i] = left / right.r->v[i];
     return(result);
 }

 dcxvec operator/(const dcxvec &left,complex right)
 {
     dcxvec result(left.origin,left.origin+left.sz-1);
     for (int i=0;i<left.sz;i++)
 	result.r->v[i] = left.r->v[i] / right;
     return(result);
 }



 dcxvec& dcxvec::operator/=(const dcxvec& right)
 {
     if (right.sz != sz)
 	    error(3,form("Different dcxvec sizes in operator/= (%d operator/= %d)",
 		sz, right.sz));
     Unique();
     for (int i=0;i<sz;i++)
 	r->v[i] /= right.r->v[i];
     return(*this);
 }

 dcxvec& dcxvec::operator/=(complex right)
 {
     Unique();
     for (int i=0;i<sz;i++)
 	r->v[i] /= right;
     return(*this);
 }

 Subdcxvec& Subdcxvec::operator/=(const dcxvec& right)
 {
     if (right.sz != sz)
 	    right.error(3,form("Different dcxvec sizes in operator/= (%d operator/= %d)",
 		sz, right.sz));
     it->Unique();
     for (int i=0;i<sz;i++)
 	it->r->v[i+offset] /= right.r->v[i];
     return(*this);
 }

 Subdcxvec& Subdcxvec::operator/=(complex right)
 {
     it->Unique();
     for (int i=0;i<sz;i++)
 	it->r->v[i+offset] /= right;
     return(*this);
 }


 dcxvec operator*(const dcxvec& left, const dcxvec& right)
 {
     if (right.sz != left.sz)
 	    left.error(3,form("Different dcxvec sizes in operator* (%d operator* %d)",
 		left.sz, right.sz));
     dcxvec result(left.sz);
     for (int i=0;i<left.sz;i++)
 	result.r->v[i] = left.r->v[i] * right.r->v[i];
     return(result);
 }

 dcxvec operator*(complex left,const dcxvec& right)
 {
     dcxvec result(right.origin,right.origin+right.sz-1);
     for (int i=0;i<right.sz;i++)
 	result.r->v[i] = left * right.r->v[i];
     return(result);
 }

 dcxvec operator*(const dcxvec &left,complex right)
 {
     dcxvec result(left.origin,left.origin+left.sz-1);
     for (int i=0;i<left.sz;i++)
 	result.r->v[i] = left.r->v[i] * right;
     return(result);
 }



 dcxvec& dcxvec::operator*=(const dcxvec& right)
 {
     if (right.sz != sz)
 	    error(3,form("Different dcxvec sizes in operator*= (%d operator*= %d)",
 		sz, right.sz));
     Unique();
     for (int i=0;i<sz;i++)
 	r->v[i] *= right.r->v[i];
     return(*this);
 }

 dcxvec& dcxvec::operator*=(complex right)
 {
     Unique();
     for (int i=0;i<sz;i++)
 	r->v[i] *= right;
     return(*this);
 }

 Subdcxvec& Subdcxvec::operator*=(const dcxvec& right)
 {
     if (right.sz != sz)
 	    right.error(3,form("Different dcxvec sizes in operator*= (%d operator*= %d)",
 		sz, right.sz));
     it->Unique();
     for (int i=0;i<sz;i++)
 	it->r->v[i+offset] *= right.r->v[i];
     return(*this);
 }

 Subdcxvec& Subdcxvec::operator*=(complex right)
 {
     it->Unique();
     for (int i=0;i<sz;i++)
 	it->r->v[i+offset] *= right;
     return(*this);
 }

 dcxvec operator-(const dcxvec &x)
 {
     dcxvec result(x.origin,x.origin+x.sz-1);
     for (int i=0;i<x.sz;i++)
 	result.r->v[i] = -x.r->v[i];
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
    for (int i=0;i<sz;i++) r->v[i] = right;
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
    for (int i=0;i<sz;i++) it->r->v[i+offset] = right;
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
