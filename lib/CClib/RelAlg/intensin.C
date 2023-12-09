#ident "@(#) /sable/sdb/ra/rel/intension/s.intensin.C"
/*      Copyright (c) 1989,1990,1991 AT&T - All Rights Reserved   */

#include <relation.h>

ostream &operator<<(ostream &s, const Intension &i)
{
s << "Degree: " << i.degree << " Key_degree: " << i.key_degree
        << " Tuple_size: " << i.tuple_size << " Tuple_align: " << i.tuple_align
        << " Reference count: " << i.ref_cnt << "\n";
for ( Degree_t x=0; x < i.degree; x++ )
   s << " offset: " << i.attr_info[x].offset << " old_nm: "
        << *(i.attr_info[x].old_nm) << " " << *(i.attr_info[x].a);
return s;
}

Degree_t Intension::index(const Aname attr_nm) const
{
for (Degree_t i=0; i < degree; i++)
   if ( attr_info[i].a->aname == attr_nm ) return i;
return NULLINDEX;
}

Boolean_t Intension::constrain(Tuple *const t) const
{
const Domain *d;
if ( !t || (t->size != tuple_size) )
   return relerr.error(R_BAD_TUPLE,__FILE__,__LINE__);
for ( Degree_t x=0; x < degree; x++ )
   {
   d = &(attr_info[x].a->domain);
   void *ptr = (void *) ((Dlength)t->data + attr_info[x].offset);
   if ( d->constraint && !d->test_constraint(ptr, d->constraint))
      { /* there is a constraint and it failed */
      switch(d->type)
         {
      case STRING: relerr.error(R_CONSTRAINT_FAILED,__FILE__,__LINE__,
         form("%s\nInstead attribute %s was <%s>",d->constraint_string(),
                    attr_info[x].a->aname.name,ptr));
         break;
      case FLOAT: relerr.error(R_CONSTRAINT_FAILED,__FILE__,__LINE__,
         form("%s\nInstead attribute %s was <%f>",d->constraint_string(),
                   attr_info[x].a->aname.name,(float)(*(Float_t *)ptr)));
         break;
      case INT: relerr.error(R_CONSTRAINT_FAILED,__FILE__,__LINE__,
         form("%s\nInstead attribute %s was <%d>",d->constraint_string(),
                   attr_info[x].a->aname.name,(int)(*(Int_t *)ptr)));
         break;
      }
      t->flags &= ~T_CONSTRAINED;
      return FALSE;
      }
   }
t->flags |= T_CONSTRAINED;
return TRUE;
}

Boolean_t Intension::operator==(const Intension &r) const
{       /* must be same attributes in same order */
if ( &r == this ) return TRUE;
if ( degree != r.degree ) return FALSE;
for ( Degree_t i=0; i < degree; i++ )
   if ( (attr_info[i].a->domain != r.attr_info[i].a->domain)
        || (attr_info[i].a->aname != r.attr_info[i].a->aname) )
      return FALSE;
return TRUE;
}

Intension &Intension::operator/(const Attribute &a)
{
/*
**   Version 2.0 of the C++ compiler issues warning statements for Int_t_align,
**   Float_t_align and String_t_align.  The statements claim that these
**   variables are defined but not used.  The variables are used in the
**   switch statement of the operator/() function.
**
**   Referencing these variables outside the switch statement made the
**   warnings go away.  The references were taken out because we feel the
**   problem is with the compiler, not the operator/() function.
*/
struct align_Int_t { char x; Int_t align; }; /* Int_t boundary alignment. */
static Dlength Int_t_align = (Dlength) &(((struct align_Int_t *)0)->align);

struct align_Float_t { char x; Float_t align; }; /* Float_t boundary alignment*/
static Dlength Float_t_align = (Dlength) &(((struct align_Float_t *)0)->align);

struct align_String_t { char x; char align[1]; }; /* char boundary alignment. */
static Dlength String_t_align = (Dlength)&(((struct align_String_t *)0)->align);
/*    C++ does not complain about the & in front of the align array
**    in the String_t.  The result is the same with and without the &.
*/

struct align_struct_t { char x; };   /* structure boundary alignment. */
static Dlength struct_align = sizeof(struct align_struct_t);

Dlength hole,attribute_align;
if ( index(a.aname) != NULLINDEX )
   {
   relerr.error(R_REPEATED_ATTRIBUTE,__FILE__,__LINE__,a.aname.name);
   return *this;
   }
if ( degree >= NATTR) 
   {
   relerr.error(R_TOO_MANY_ATTRIBUTES,__FILE__,__LINE__,a.aname.name);
   return *this;
   }
attr_info[degree].a = &a;           /* Initialize attribute pointer.       */
switch(a.domain.type)               /* Initialize attribute's offset based */
   {                                /* on attribute's boundary alignment.  */
case INT: attribute_align = Int_t_align; break;
case FLOAT: attribute_align = Float_t_align; break;
case STRING: attribute_align = String_t_align; break;
default: syserr.error(UNEXPECTED_ERROR,__FILE__,__LINE__); abort();
   }
tuple_align = max(attribute_align,max(struct_align,tuple_align));
switch (degree)
   {
case 0: attr_info[degree].offset = 0; break;
default: 
   Dlength offset = attr_info[degree-1].offset +
                                           attr_info[degree-1].a->domain.length;
   if ( hole=offset%attribute_align ) offset += attribute_align - hole;
   attr_info[degree].offset = offset;
   break;
   }
attr_info[degree].old_nm = (Aname *) NULL; /* Initialize attribute's old name */
tuple_size = attr_info[degree++].offset + a.domain.length;
/* make sure this is alligned so that it can be used for an array of tuples */
if ( hole=tuple_size%tuple_align ) tuple_size += tuple_align - hole;
return *this;
}

Intension::Intension()
{
key_degree = degree = (Degree_t) 0;
tuple_align = tuple_size = (Dlength) 0;
ref_cnt = 0;
}

void Intension::use()
{
ref_cnt++;
}

void Intension::done()
{
if ( !ref_cnt )
   relerr.error(R_TOO_MANY_DONES,__FILE__,__LINE__);
else if ( --ref_cnt == 0 )
   delete this;
}

Boolean_t Intension::operator!=(const Intension &r) const
{
if ( &r == this ) return FALSE;
return !((*this) == r);
}

Intension &Intension::operator%(const Attribute &a)  // key delimiter
{                                                          
key_degree = degree;
return *this / a;
}

Intension &Intension::operator*(const Attribute &a)  // rename
{
if (  a.domain != attr_info[degree-1].a->domain )
   { relerr.error(R_MIXED_DOMAINS,__FILE__,__LINE__); return *this; }
attr_info[degree-1].old_nm = &a.aname;
return *this;
}

Intension &operator%(const Attribute &l,const Attribute &r)
{
Intension *This = new Intension;
return (*This)/l%r;
}

Intension &operator/(const Attribute &l,const Attribute &r)
{
Intension *This = new Intension;
return (*This)/l/r;
}

Intension &operator*(const Attribute &l,const Attribute &r)
{
Intension *This = new Intension;
This->use();
return (*This)/l*r;
}
