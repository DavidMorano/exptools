#ident "@(#) /sable/sdb/ra/rel/relation/s.rConstr.C"
/*      Copyright (c) 1989,1991 AT&T - All Rights Reserved */

#include <relation.h>

#define ERROR(ERRNUM) { relerr.error(ERRNUM,__FILE__,__LINE__); abort(); }

Relation & Relation::constrain()
{
Usage l_usage = usage; usage = LVALUE;
Tuple *item=(Tuple *)0;
Relation *output = new Relation(intension), &Output = *output;
Tuple_Hash hash((Hashindex)cardinality());
Hashindex hash_index,start_index,mask=hash.size()-1;
Dlength keylength=0;
if ( intension.key_degree )
   keylength = intension.attr_info[intension.key_degree].offset;
else keylength = intension.tuple_size;
if ( cardinality() )
   {
   for ( startwalk(); item=walk(); )
{
cerr << "item: " << item;
Output += item;
}
/*
      {
      if ( constrain(item) == FALSE )
         continue;
      start_index = hash_index = hash.hash((char *)(item->data),keylength);
      while ( hash.table[hash_index] )
         {  // find empty slot or collide & replace
         if ( memcmp((char *)(hash.table[hash_index]->data),
                (char *)(item->data),keylength) == 0 )
            { // collision
            relerr.error(R_KEY_VIOLATION,__FILE__,__LINE__);
            hash.table[hash_index]->done();
            break; // new item will replace the current one
            }
         hash_index = (hash_index+1) & mask;
         if ( hash_index == start_index )
            { relerr.error(R_HASH_OVERFLOW,__FILE__,__LINE__); break; }
         }

      hash.table[hash_index] = item;
      item->share();
      }
   endwalk();
   for ( start_index=0; start_index < hash.size(); start_index++ )
      if ( hash.table[start_index] )
         { Output += hash.table[start_index]; hash.table[start_index]->done(); }
*/
   }
usage = l_usage;
destroy_rvalue();
Output.usage = RVALUE;  // change it from Relation to expression
return Output;
}
