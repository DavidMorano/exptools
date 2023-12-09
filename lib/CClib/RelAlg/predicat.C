#ident "@(#) /sable/sdb/ra/rel/attribute/s.predicat.C"
/*      Copyright (c) 1989, 1990, 1991 AT&T - All Rights Reserved */

#include <relation.h>

ostream & operator<<(ostream &o,const Predicate &p)
{
switch(p.op)
   {
case AND: o << "&&(" << *p.left.p << "," << *p.right.p << ")"; break;
case OR:  o << "||(" << *p.left.p << "," << *p.right.p << ")"; break;
case NOT: o << "!("  << *p.right.p << ")"; break;
case EQ:  o << "==(" ; goto printright;
case NE:  o << "!=(" ; goto printright;
case LE:  o << "<=(" ; goto printright;
case LT:  o << "<("  ; goto printright;
case GE:  o << ">=(" ; goto printright;
case GT:  o << ">("  ; goto printright;
printright:
   o << (const Aname &) p.left.a->aname << ",";
   switch(p.compare_to)
      {
   case ATTRIBUTE: o << (const Aname &) p.right.a->aname; break;
   case DATA:
      switch(p.left.a->domain.type)
         {
      case INT:    o << p.right.i; break;
      case FLOAT:  o << p.right.f; break;
      case STRING: o << p.right.s; break;
         }
      }
   o << ")";
   break;
case MATCH: o<< "==(" << (const Aname &) p.left.a->aname << ","
             << p.right.r->pattern_string() << ")";
case NOMATCH: o<< "!=(" << (const Aname &) p.left.a->aname << ","
               << p.right.r->pattern_string() << ")";
   }
return o;
}

Predicate::Predicate(const Op o, const Predicate *p) :
                                               compare_to(PREDICATE),  op(o)
{//   !
left.p = (Predicate *) 0; right.p = p;
}

Predicate::Predicate(const Op o, const Predicate *l, const Predicate *r):
                                               compare_to(PREDICATE), op(o)
{//   &&, ||
left.p = l; right.p = r;
}

Predicate::Predicate(const Op o, const Attribute *a, const Attribute *r):
                                               compare_to(ATTRIBUTE), op(o)
{// ==, !=, <=, >=, <, >
left.a = a; right.a = r;
}

Predicate::Predicate(const Op o, const Attribute *a, const Int_t i):
                                               compare_to(DATA), op(o)
{// ==, !=, <=, >=, <, >
left.a = a; right.i = i;
}

Predicate::Predicate(const Op o, const Attribute *a, const Float_t f):
                                               compare_to(DATA), op(o)
{// ==, !=, <=, >=, <, >
left.a = a; right.f = f;
}

Predicate::Predicate(const Op o, const Attribute *a, const char *s):
                                               compare_to(DATA), op(o)
{// ==, !=, <=, >=, <, >
if (!s) {syserr.error(NULL_POINTER,__FILE__,__LINE__); abort();}
left.a = a; right.s = s;
}

Predicate::Predicate(const Op o, const Attribute *a, const Pattern *r):
                                               compare_to(PATTERN), op(o)
{// MATCH, NOMATCH
left.a = a; right.r = r;
}

Predicate::~Predicate()
{
switch(op)
   {
case AND: case OR: delete left.p; // fall through
case NOT: delete right.p; break;
case EQ: case NE: case LE: case GE: 
case LT: case GT: case MATCH: case NOMATCH: break;
default: syserr.error(UNEXPECTED_ERROR, __FILE__, __LINE__); abort();
   }
}

Predicate & Predicate::operator&&(const Predicate &r) const
{
return *(Predicate *)new Predicate(AND,this,&r);
}

Predicate & Predicate::operator||(const Predicate &r) const
{
return *(Predicate *)new Predicate(OR,this,&r);
}

Predicate & Predicate::operator!() const
{
return *(Predicate *)new Predicate(NOT,this);
}
