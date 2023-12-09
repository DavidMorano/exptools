#ident "@(#) /sable/sdb/ra/rel/attribute/s.attribut.C"
/*      Copyright (c) 1989,1991 AT&T - All Rights Reserved */

#include <relation.h>

ostream & operator<<(ostream &s,const Attribute &a)
{
s << "aname: " << a.aname << a.domain;
return s;
}

Attribute::Attribute(const char *const n, const Domain &d) : domain(d)
{
aname=n;
}

#undef ERROR
#define ERROR(ERRNUM) { relerr.error(ERRNUM,__FILE__,__LINE__); abort(); }

Predicate & Attribute::operator==(const Int_t i) const
{
if ( domain.type != INT )
   ERROR(R_NOT_INT_ATTRIBUTE)
return *(Predicate *)new Predicate(EQ,this,i); 
}

Predicate & Attribute::operator!=(const Int_t i) const
{
if ( domain.type != INT )
   ERROR(R_NOT_INT_ATTRIBUTE)
return *(Predicate *)new Predicate(NE,this,i); 
}

Predicate & Attribute::operator<=(const Int_t i) const
{
if ( domain.type != INT )
   ERROR(R_NOT_INT_ATTRIBUTE)
return *(Predicate *)new Predicate(LE,this,i); 
}

Predicate & Attribute::operator>=(const Int_t i) const
{
if ( domain.type != INT )
   ERROR(R_NOT_INT_ATTRIBUTE)
return *(Predicate *)new Predicate(GE,this,i); 
}

Predicate & Attribute::operator<(const Int_t i) const
{
if ( domain.type != INT )
   ERROR(R_NOT_INT_ATTRIBUTE)
return *(Predicate *)new Predicate(LT,this,i); 
}

Predicate & Attribute::operator>(const Int_t i) const
{
if ( domain.type != INT )
   ERROR(R_NOT_INT_ATTRIBUTE)
return *(Predicate *)new Predicate(GT,this,i); 
}

Predicate & Attribute::operator==(const Float_t f) const
{
if ( domain.type != FLOAT )
   ERROR(R_NOT_FLOAT_ATTRIBUTE)
return *(Predicate *)new Predicate(EQ,this,f); 
}

Predicate & Attribute::operator!=(const Float_t f) const
{
if ( domain.type != FLOAT )
   ERROR(R_NOT_FLOAT_ATTRIBUTE)
return *(Predicate *)new Predicate(NE,this,f); 
}

Predicate & Attribute::operator<=(const Float_t f) const
{
if ( domain.type != FLOAT )
   ERROR(R_NOT_FLOAT_ATTRIBUTE)
return *(Predicate *)new Predicate(LE,this,f); 
}

Predicate & Attribute::operator>=(const Float_t f) const
{
if ( domain.type != FLOAT )
   ERROR(R_NOT_FLOAT_ATTRIBUTE)
return *(Predicate *)new Predicate(GE,this,f); 
}

Predicate & Attribute::operator<(const Float_t f) const
{
if ( domain.type != FLOAT )
   ERROR(R_NOT_FLOAT_ATTRIBUTE)
return *(Predicate *)new Predicate(LT,this,f); 
}

Predicate & Attribute::operator>(const Float_t f) const
{
if ( domain.type != FLOAT )
   ERROR(R_NOT_FLOAT_ATTRIBUTE)
return *(Predicate *)new Predicate(GT,this,f); 
}

Predicate & Attribute::operator==(const char *const s) const
{
if ( domain.type != STRING )
   ERROR(R_NOT_STRING_ATTRIBUTE)
return *(Predicate *)new Predicate(EQ,this,s); 
}

Predicate & Attribute::operator!=(const char *const s) const
{
if ( domain.type != STRING )
   ERROR(R_NOT_STRING_ATTRIBUTE)
return *(Predicate *)new Predicate(NE,this,s); 
}

Predicate & Attribute::operator<=(const char *const s) const
{
if ( domain.type != STRING )
   ERROR(R_NOT_STRING_ATTRIBUTE)
return *(Predicate *)new Predicate(LE,this,s); 
}

Predicate & Attribute::operator>=(const char *const s) const
{
if ( domain.type != STRING )
   ERROR(R_NOT_STRING_ATTRIBUTE)
return *(Predicate *)new Predicate(GE,this,s); 
}

Predicate & Attribute::operator<(const char *const s) const
{
if ( domain.type != STRING )
   ERROR(R_NOT_STRING_ATTRIBUTE)
return *(Predicate *)new Predicate(LT,this,s); 
}

Predicate & Attribute::operator>(const char *const s) const
{
if ( domain.type != STRING )
   ERROR(R_NOT_STRING_ATTRIBUTE)
return *(Predicate *)new Predicate(GT,this,s); 
}

Predicate & Attribute::operator==(const Attribute &a) const
{
if ( this->domain != a.domain )
   ERROR(R_MIXED_DOMAINS)
return *(Predicate *)new Predicate(EQ,this,&a); 
}

Predicate & Attribute::operator!=(const Attribute &a) const
{
if ( this->domain != a.domain )
   ERROR(R_MIXED_DOMAINS)
return *(Predicate *)new Predicate(NE,this,&a); 
}

Predicate & Attribute::operator<=(const Attribute &a) const
{
if ( this->domain != a.domain )
   ERROR(R_MIXED_DOMAINS)
return *(Predicate *)new Predicate(LE,this,&a); 
}

Predicate & Attribute::operator>=(const Attribute &a) const
{
if ( this->domain != a.domain )
   ERROR(R_MIXED_DOMAINS)
return *(Predicate *)new Predicate(GE,this,&a); 
}

Predicate & Attribute::operator<(const Attribute &a) const
{
if ( this->domain != a.domain )
   ERROR(R_MIXED_DOMAINS)
return *(Predicate *)new Predicate(LT,this,&a); 
}

Predicate & Attribute::operator>(const Attribute &a) const
{
if ( this->domain != a.domain )
   ERROR(R_MIXED_DOMAINS)
return *(Predicate *)new Predicate(GT,this,&a); 
}

Predicate & Attribute::operator==(const Pattern &r) const
{
if ( domain.type != STRING )
   ERROR(R_NOT_STRING_ATTRIBUTE)
return *(Predicate *)new Predicate(MATCH,this,&r); 
}

Predicate & Attribute::operator!=(const Pattern &r) const
{
if ( domain.type != STRING )
   ERROR(R_NOT_STRING_ATTRIBUTE)
return *(Predicate *)new Predicate(NOMATCH,this,&r); 
}
