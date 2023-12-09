#ident "@(#) /sable/sdb/ra/rel/relation/s.plusEq.C"
/*      Copyright (c) 1991 AT&T - All Rights Reserved */

#include <relation.h>

Boolean_t Relation::operator+=(Relation &r)
{
Usage l_usage=usage, r_usage = r.usage;
usage = r.usage = LVALUE;
Extension *re=(Extension *)0;
Relation &l = *this;
Tuple *build_tuple=(Tuple *)0, *check_tuple=(Tuple *)0;
if ( (l.intension) != (r.intension) )
   { relerr.error(R_BAD_UNION,__FILE__,__LINE__); return FALSE; }
Combine_attributes comb(l,r);
if ( comb.build == MAJOR ) /* hash left side relation */
   {
   for ( l.startwalk(); build_tuple=l.walk(); )
      comb.build_hash(build_tuple);
   l.endwalk();
   for ( r.startwalk(); check_tuple=r.walk(); )
      {
      re = comb.check_hash(check_tuple);
      if ( re->cardinality() == 0 )
         l += check_tuple;
      delete re;
      }
   r.endwalk();
   }
else /* hash right side relation */
   {
   int rcard = 0;
   typedef Tuple *PTuple;
   Tuple **tuple_array = new PTuple[r.cardinality()?r.cardinality():1];
   for ( r.startwalk(); build_tuple = r.walk(); )
      {
      build_tuple->flags &= ~T_MARK; /* remove old T_MARK */
      tuple_array[rcard++] = build_tuple;
      comb.build_hash(build_tuple); /* comb will share the tuple */
      }
   r.endwalk();
   for ( l.startwalk(); check_tuple = l.walk(); )
      if (re = comb.check_hash(check_tuple))
         {
         for (re->startwalk(); build_tuple= re->walk(); )
            build_tuple->flags |= T_MARK; /* mark the tuple */
         re->endwalk();
         delete re;
         }
   l.endwalk();
   for ( int i=0; i < rcard; i++ )
      if ( !(tuple_array[i]->flags&T_MARK) )
          l += tuple_array[i];
   delete [] tuple_array;
   }
l.usage = l_usage; r.usage = r_usage;
r.destroy_rvalue();
return TRUE;
}
