#ident "@(#) /sable/sdb/ra/rel/relation/s.halfjoin.C"
/*      Copyright (c) 1989,1991 AT&T - All Rights Reserved */

#include <relation.h>

Relation & Relation::operator^(Relation &r)
{
Usage l_usage = usage, r_usage = r.usage;
usage = r.usage = LVALUE; // protect within the function
Extension *re=(Extension *)0;
Relation &l = *this;
Tuple *build_tuple=(Tuple *)0, *check_tuple=(Tuple *)0;
Combine_attributes comb(r,l);
Relation * out = new Relation(r.intension);
if ( comb.build == MINOR ) // hash left hand relation
   {
   for ( l.startwalk(); build_tuple=l.walk(); )
      comb.build_hash(build_tuple);
   l.endwalk();
   for ( r.startwalk(); check_tuple=r.walk(); )
      {
      re = comb.check_hash(check_tuple);
      if ( re->cardinality() )
         (*out) += check_tuple;
      delete re;
      }
   r.endwalk();
   }
else // ( comb.build == MAJOR ) // hash the right hand relation
   {
   Dlength size = r.intension.tuple_size;
   for ( r.startwalk(); build_tuple=r.walk(); )
      {
      build_tuple->flags &= ~T_MARK;
      comb.build_hash(build_tuple);
      }
   r.endwalk();
   for ( l.startwalk(); check_tuple=l.walk(); )
      {
      re = comb.check_hash(check_tuple);
      for ( re->startwalk(); build_tuple=re->walk(); )
         if ( !(build_tuple->flags&T_MARK) )
            {
            build_tuple->flags |= T_MARK; // don't add it twice
            (*out) += build_tuple;
            }
      re->endwalk();
      delete re;
      }
   l.endwalk();
   }
l.usage = l_usage;
l.destroy_rvalue();
r.usage = r_usage;
r.destroy_rvalue();
out->usage = RVALUE;
return *out;
}
