#ident "@(#) /sable/sdb/ra/rel/relation/s.setdiff.C"
/*      Copyright (c) 1989,1991 AT&T - All Rights Reserved */

#include <relation.h>

Relation & Relation::operator-(Relation &r)
{
Usage l_usage = usage, r_usage = r.usage;
usage = r.usage = LVALUE;
Extension *re=(Extension *)0;
Relation &l = *this;
Tuple *major_tuple, *minor_tuple;
int lcard=0;
Combine_attributes comb(l,r);
Relation * out = new Relation(intension);
if ( comb.build == MAJOR ) // hash left hand relation
   {
   typedef Tuple *PTuple;
   Tuple **tuple_array = new PTuple[l.cardinality()?l.cardinality():1];
   Dlength size = l.intension.tuple_size;
   for ( l.startwalk(); major_tuple = l.walk(); )
      {
      major_tuple->flags &= ~T_MARK; // remove old T_MARK
      tuple_array[lcard++] = major_tuple;
      comb.build_hash(major_tuple); // comb will retain the tuple
      }
   l.endwalk();
   for ( r.startwalk(); minor_tuple = r.walk(); )
      if (re = comb.check_hash(minor_tuple))
         {
         for (re->startwalk(); major_tuple= re->walk(); )
            major_tuple->flags |= T_MARK; // mark the tuple
         re->endwalk();
         delete re;
         }
   r.endwalk();
   for ( int i=0; i < lcard; i++ )
      if ( !(tuple_array[i]->flags&T_MARK) )
          (*out) += tuple_array[i];
   delete [] tuple_array;
   }
else     // hash the right hand relation
   {
   for ( r.startwalk(); minor_tuple = r.walk(); )
      comb.build_hash(minor_tuple); // comb will retain the tuple
   r.endwalk();
   for ( l.startwalk(); major_tuple = l.walk(); )
      {
      re = comb.check_hash(major_tuple);
      if ( re->cardinality() == 0 )
         (*out) += major_tuple;
      delete re;
      }
   l.endwalk();
   }
l.usage = l_usage; r.usage = r_usage;
l.destroy_rvalue();
r.destroy_rvalue();
out->usage = RVALUE;     // change it from Relation to expression
return *out;
}
