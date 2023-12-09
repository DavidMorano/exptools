#ident "@(#) /sable/sdb/ra/rel/relation/s.join.C"
/*      Copyright (c) 1989,1991 AT&T - All Rights Reserved */

#include <relation.h>

Relation & Relation::operator&(Relation &r)
{
Usage l_usage = usage, r_usage = r.usage;
usage = r.usage = LVALUE; // protect within the function
Extension *re=(Extension *)0;
Relation &l = *this, *build, *check;
Tuple *build_tuple=(Tuple *)0, *check_tuple=(Tuple *)0,
   **major_tuple=(Tuple **)0, **minor_tuple=(Tuple **)0;
Intension *out_intension = new Intension;
Combine_attributes comb(l,r);
for ( Degree_t i=0; i < comb.degree; i++ )
   (void) ((*out_intension) / (*comb.info[i].attr));
Relation * out = new Relation(*out_intension);
if ( comb.build == MAJOR )
   {
   major_tuple = &build_tuple;
   minor_tuple = &check_tuple;
   build = &l;
   check = &r;
   }
else
   {
   major_tuple = &check_tuple;
   minor_tuple = &build_tuple;
   build = &r;
   check = &l;
   }
for ( build->startwalk(); build_tuple = build->walk(); )
      comb.build_hash(build_tuple);
build->endwalk();
for ( check->startwalk(); check_tuple = check->walk(); )
   {
   re = comb.check_hash(check_tuple);
   for ( re->startwalk(); build_tuple = re->walk(); )
      {
      Tuple *new_tuple = Tuple_new(out_intension->tuple_size);
      if ( (build_tuple->flags&T_CONSTRAINED)
                 && (check_tuple->flags&T_CONSTRAINED) )
         new_tuple->flags |= T_CONSTRAINED;
      for ( i=0; i < comb.degree; i++ )
         switch(comb.info[i].which)
            {
         case MAJOR:
         case BOTH:
            memcpy((char *)(new_tuple->data)+out_intension->attr_info[i].offset,
               ((char *)((*major_tuple)->data))+comb.info[i].major_offset,
               comb.info[i].length);
               break;
         case MINOR:
            memcpy((char *)(new_tuple->data)+out_intension->attr_info[i].offset,
               ((char *)((*minor_tuple)->data))+comb.info[i].minor_offset,
               comb.info[i].length);
            }
       (*out) += new_tuple;
       new_tuple->done();
       }     
   re->endwalk();
   delete re;
   }
check->endwalk();
l.usage = l_usage; r.usage = r_usage;
l.destroy_rvalue(); r.destroy_rvalue();
out->usage = RVALUE;    // change it from Relation to expression
return *out;
}
