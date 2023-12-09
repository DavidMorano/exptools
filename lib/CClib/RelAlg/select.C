#ident "@(#) /sable/sdb/ra/rel/relation/s.select.C"
/*      Copyright (c) 1989, 1990,1991 AT&T - All Rights Reserved */

#include <relation.h>

Boolean_t Relation::evaluate(Tuple * tuple,const Predicate &p)
{
Degree_t index=0;
union { Int_t *i; Float_t *f; const char *s; const Pattern *r; void *v; }
   left,right;
if (p.compare_to != PREDICATE)
   {
   if ( (index=intension.index(p.left.a->aname)) == NULLINDEX )
      return relerr.error(R_NO_ATTRIBUTE,__FILE__,__LINE__,
             p.left.a->aname.name);
   left.v = (char *)(tuple->data)+intension.attr_info[index].offset;
   switch(p.compare_to)
      {
   case PATTERN:
      right.r = p.right.r; break;
   case ATTRIBUTE:
      if ( (index=intension.index(p.right.a->aname)) == NULLINDEX )
         return relerr.error(R_NO_ATTRIBUTE,__FILE__,__LINE__,
                p.right.a->aname.name);
      right.v = (char *)(tuple->data)+intension.attr_info[index].offset;
      break;
   case DATA:
      switch(intension.attr_info[index].a->domain.type)
         {
      case INT: right.i = &p.right.i; break;
      case FLOAT: right.f = &p.right.f; break;
      case STRING: right.s = p.right.s; break;
         }
      break;
   case PREDICATE: return syserr.error(UNEXPECTED_ERROR,__FILE__,__LINE__);
      }
   }
switch(p.op)
   {
case AND: 
   if ( evaluate(tuple,*p.left.p) ) 
      return evaluate(tuple,*p.right.p);
   else return FALSE;
case OR: 
   if ( evaluate(tuple,*p.left.p) ) 
      return TRUE;
   else return evaluate(tuple,*p.right.p);
case NOT: 
   return evaluate(tuple,*p.right.p)?FALSE:TRUE;
case EQ: 
   switch(intension.attr_info[index].a->domain.type)
      {
   case INT: if ( *(left.i) == *(right.i) ) return TRUE; else return FALSE;
   case FLOAT: if ( *(left.f) == *(right.f) ) return TRUE; else return FALSE;
   case STRING:
      if ( strncmp(left.s,right.s,intension.attr_info[index].a->domain.length)
                                == 0 )
         return TRUE;
      else return FALSE;
      }
   break;
case NE: 
   switch(intension.attr_info[index].a->domain.type)
      {
   case INT: if ( *(left.i) != *(right.i) ) return TRUE; else return FALSE;
   case FLOAT: if ( *(left.f) != *(right.f) ) return TRUE; else return FALSE;
   case STRING:
      if ( strncmp(left.s,right.s,intension.attr_info[index].a->domain.length)
                                != 0 )
         return TRUE;
      else return FALSE;
      }
   break;
case LE: 
   switch(intension.attr_info[index].a->domain.type)
      {
   case INT: if ( *(left.i) <= *(right.i) ) return TRUE; else return FALSE;
   case FLOAT: if ( *(left.f) <= *(right.f) ) return TRUE; else return FALSE;
   case STRING:
      if ( strncmp(left.s,right.s,intension.attr_info[index].a->domain.length)
                               <= 0 )
         return TRUE;
      else return FALSE;
      }
   break;
case GE: 
   switch(intension.attr_info[index].a->domain.type)
      {
   case INT: if ( *(left.i) >= *(right.i) ) return TRUE; else return FALSE;
   case FLOAT: if ( *(left.f) >= *(right.f) ) return TRUE; else return FALSE;
   case STRING:
      if ( strncmp(left.s,right.s,intension.attr_info[index].a->domain.length)
                               >= 0 )
         return TRUE;
      else return FALSE;
      }
   break;
case LT: 
   switch(intension.attr_info[index].a->domain.type)
      {
   case INT: if ( *(left.i) < *(right.i) ) return TRUE; else return FALSE;
   case FLOAT: if ( *(left.f) < *(right.f) ) return TRUE; else return FALSE;
   case STRING:
      if (strncmp(left.s,right.s,intension.attr_info[index].a->domain.length)<0)
         return TRUE;
      else return FALSE;
      }
   break;
case GT: 
   switch(intension.attr_info[index].a->domain.type)
      {
   case INT: if ( *(left.i) > *(right.i) ) return TRUE; else return FALSE;
   case FLOAT: if ( *(left.f) > *(right.f) ) return TRUE; else return FALSE;
   case STRING:
      if (strncmp(left.s,right.s,intension.attr_info[index].a->domain.length)>0)
         return TRUE;
      else return FALSE;
      }
   break;
case MATCH:
   if ( right.r->match(left.s) )
      return TRUE;
   else return FALSE;
case NOMATCH:
   if ( right.r->match(left.s) )
      return FALSE;
   else return TRUE;
   }
}

Relation & Relation::operator[](Predicate &p)
{
Usage l_usage = usage; 
usage = LVALUE;  
Tuple * tuple=(Tuple *)0;
Relation * out = new Relation(intension);
for ( startwalk(); tuple = walk(); )
   if (evaluate(tuple,p))
      *out += tuple;
endwalk();
usage = l_usage;
destroy_rvalue();
out->usage = RVALUE;    /* change it from Relation to expression */
return *out;
}
