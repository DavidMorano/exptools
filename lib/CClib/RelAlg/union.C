#ident "@(#) /sable/sdb/ra/rel/relation/s.union.C"
/*      Copyright (c) 1989,1991 AT&T - All Rights Reserved */

#include <relation.h>

Relation & Relation::operator+(Relation &r)
{
Usage l_usage=usage, r_usage = r.usage;
usage = r.usage = LVALUE;
Extension *re=(Extension *)0;
Relation &l = *this, *build, *check;
Tuple *build_tuple=(Tuple *)0, *check_tuple=(Tuple *)0;
if ( (l.intension) != (r.intension) )
   { relerr.error(R_BAD_UNION,__FILE__,__LINE__); return *this; }
Combine_attributes comb(l,r); // major relation is arbitrary
Relation * out = new Relation(intension);
if ( comb.build == MAJOR ) // hash left side relation
   {
   build = &l;
   check = &r;
   }
else
   {
   build = &r;
   check = &l;
   }

for ( build->startwalk(); build_tuple=build->walk(); )
   {
   comb.build_hash(build_tuple);
   (*out) += build_tuple;
   }
build->endwalk();
for ( check->startwalk(); check_tuple=check->walk(); )
   {
   re = comb.check_hash(check_tuple);
   if ( re->cardinality() == 0 )
      *out += check_tuple;
   delete re;
   }
check->endwalk();
l.usage = l_usage; r.usage = r_usage;
l.destroy_rvalue();
r.destroy_rvalue();
out->usage = RVALUE;    // change it from Relation to expression
return *out;
}
