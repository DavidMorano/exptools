#ident "@(#) /sable/sdb/ra/rel/relation/s.project.C"
/*      Copyright (c) 1989,1991 AT&T - All Rights Reserved  */

#include <relation.h>

#define ERROR(ERRNUM) { relerr.error(ERRNUM,__FILE__,__LINE__); abort(); }
Relation & Relation::operator[](Intension &new_i)
{
Usage l_usage = usage;
usage = LVALUE;
Relation *output = new Relation(new_i), &Output = *output;
Degree_t i=0, old_index=0;
Dlength *old_offsets = new Dlength[new_i.degree];
Tuple *item=(Tuple *)0, *new_item=(Tuple *)0;
Tuple_Hash hash((Hashindex)cardinality());
Hashindex hash_index,start_index,mask=hash.size()-1;

for ( i=0; i < new_i.degree; i++ ) // match up old and new attributes
   {
   if ( new_i.attr_info[i].old_nm )
      {
      if ( (old_index=intension.index(*(new_i.attr_info[i].old_nm)))
                == NULLINDEX )
         {
         relerr.error(R_NO_ATTRIBUTE,__FILE__,__LINE__,
                new_i.attr_info[i].old_nm->name);
         return Output;
         }
      }
   else if  ( (old_index=intension.index(new_i.attr_info[i].a->aname))
                == NULLINDEX )
      {
      relerr.error(R_NO_ATTRIBUTE,__FILE__,__LINE__,
             new_i.attr_info[i].a->aname.name);
      return Output;
      }
   if (intension.attr_info[old_index].a->domain == new_i.attr_info[i].a->domain)
         old_offsets[i] = intension.attr_info[old_index].offset;
   else ERROR(R_MIXED_DOMAINS) // should be caught by Intension before this
   }
if ( cardinality() )
   {
   for ( startwalk(); item=walk(); )
      {
      new_item = Tuple_new(new_i.tuple_size);
      for ( i=0; i < new_i.degree; i++ )
         memcpy((char *)(new_item->data)+new_i.attr_info[i].offset,
                (char *)(item->data)+old_offsets[i],
                new_i.attr_info[i].a->domain.length);
      start_index = hash_index = 
          hash.hash((char *)(new_item->data),new_i.tuple_size);
      while ( hash.table[hash_index] )
         {
         if ( memcmp((char *)(hash.table[hash_index]->data),
                (char *)(new_item->data),new_i.tuple_size) == 0 )
            break; // duplicate found
         hash_index = (hash_index+1) & mask;
         if ( hash_index == start_index )
            ERROR(R_HASH_OVERFLOW) // UNEXPECTED - cardinality was known
         }
      if ( hash.table[hash_index] == (Tuple *)0 ) // not a duplicate
         {
         hash.table[hash_index] = new_item;
         new_item->share();
         if ( item->flags&T_CONSTRAINED )
            new_item->flags |= T_CONSTRAINED;
         Output += new_item;
         }
      new_item->done();
      }
   endwalk();
   usage = l_usage;
   destroy_rvalue();
   }
delete old_offsets;
Output.usage = RVALUE;  // change it from Relation to expression
return Output;
}
