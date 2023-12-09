#ident "@(#) /sable/sdb/ra/rel/domain/s.constr.C"
/*      Copyright (c) 1989,1991 AT&T - All Rights Reserved */

#include <relation.h>

Constraint::Constraint(const Op o,const Constraint *const c) : op(o)
{ //            !
domain = c->domain;
left = (Constraint *) 0;
right.c = c;
domain->constraint = this;
}

Constraint::Constraint(const Op o,const Constraint *const l,
                                 const Constraint *const c) : op(o)
{ //            &&, ||
if ( (domain = l->domain) != c->domain )
   { relerr.error(R_MIXED_DOMAINS,__FILE__,__LINE__); abort(); }
left = l;
right.c = c;
domain->constraint = this;
}

Constraint::Constraint(const Op o,const Domain *const d,
                                         const Int_t i) : op(o)
{ //            ==, !=, <=, >=, <, > 
domain = (Domain *)d;
left = (Constraint *) 0;
right.i = i;
domain->constraint = this;
}

Constraint::Constraint(const Op o,const Domain *const d,
                                       const Float_t f) : op(o)
{ //            ==, !=, <=, >=, <, > 
domain = (Domain *)d;
left = (Constraint *) 0;
right.f = f;
domain->constraint = this;
}

Constraint::Constraint(const Op o,const Domain *const d,
                                  const char *const  s) : op(o)
{ //            ==, !=, <=, >=, <, > 
domain = (Domain *)d;
left = (Constraint *) 0;
if ( s ) right.s = s;
else right.s = EMPTY_STRING;
domain->constraint = this;
}

Constraint::Constraint(const Op o,const Domain *const d,
                                const Pattern *const r) : op(o)
{ //            ==, !=
domain = (Domain *)d;
left = (Constraint *) 0;
right.r = r;
domain->constraint = this;
}

Constraint::~Constraint()
{
switch(op)
   {
case AND: case OR: delete left; // fall through
case NOT: delete right.c; break;
case EQ: case NE: case LE: case GE: 
case LT: case GT: case MATCH: case NOMATCH: break;
default: syserr.error(UNEXPECTED_ERROR, __FILE__, __LINE__); abort();
   }
}

Constraint & Constraint::operator&&(const Constraint &r) const
{
return *(Constraint *)new Constraint(AND,this,&r);
}

Constraint & Constraint::operator||(const Constraint &r) const
{
return *(Constraint *)new Constraint(OR,this,&r);
}

Constraint & Constraint::operator!() const
{
return *(Constraint *)new Constraint(NOT,this);
}
