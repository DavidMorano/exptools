#ident "@(#) /sable/sdb/ra/rel/relation/s.combine.C"
/*      Copyright (c) 1989,1991 AT&T - All Rights Reserved */

#include <relation.h>

Combine_attributes::Combine_attributes(Relation &major,Relation &minor)
{
Degree_t i=0,j=0,k=0;
info = new struct combined_info[major.degree()+minor.degree()];
for ( i=0; i < major.degree(); i++ )
   {
   info[i].which = MAJOR;
   info[i].length = major.intension.attr_info[i].a->domain.length;
   info[i].attr = major.intension.attr_info[i].a;
   info[i].major_offset = major.intension.attr_info[i].offset;
   }
for ( j=0; j < minor.degree(); j++ )
   {
   if ( (k=major.intension.index(minor.intension.attr_info[j].a->aname))
                      != NULLINDEX )
      {
      info[k].which = BOTH;
      info[k].minor_offset = minor.intension.attr_info[j].offset;
      }
   else            // join needs to know about the minor attributes as well
      {
      info[i].which = MINOR;
      info[i].length = minor.intension.attr_info[j].a->domain.length;
      info[i].attr = minor.intension.attr_info[j].a;
      info[i++].minor_offset = minor.intension.attr_info[j].offset;
      }
   }
degree = i;
if ( minor.cardinality() < major.cardinality() )
   {
   build = MINOR; check = MAJOR;
   build_cardinality = minor.cardinality();
   build_size = minor.intension.tuple_size;
   }
else
   {
   build = MAJOR; check = MINOR;
   build_cardinality = major.cardinality();
   build_size = major.intension.tuple_size;
   }
hash = new Tuple_Hash(build_cardinality);
}

Hashindex Combine_attributes::hash_index(Tuple * tuple,Which which)
{
Hashindex rc=0;
Degree_t i=0;
Which w;
for (i=0;(i<degree)&&((w=info[i].which)!=MINOR);i++)
   if ( w == BOTH )
      {
      Dlength offset = which==MAJOR?info[i].major_offset:info[i].minor_offset;
      rc = hash->hash(((char *)(tuple->data))+offset,info[i].length,rc);
      }
return  rc;
}

Boolean_t Combine_attributes::hash_match(Tuple *build_tuple,Tuple *check_tuple)
{
char *bo=(char *)0, *co=(char *)0;
Degree_t i=0;
Which which;
for (i=0;(i<degree)&&((which=info[i].which)!=MINOR);i++)
   if ( which == BOTH )
      {
      if ( build == MAJOR )
         {
         bo = (char *)(build_tuple->data) + info[i].major_offset;
         co = (char *)(check_tuple->data) + info[i].minor_offset;
         }
      else
         {
         bo = (char *)(build_tuple->data) + info[i].minor_offset;
         co = (char *)(check_tuple->data) + info[i].major_offset;
         }
      if ( memcmp(bo,co,info[i].length) )
            return FALSE;
      }
return TRUE;
}

Boolean_t Combine_attributes::build_hash(Tuple * tuple)
{
if ( tuple->size != build_size )
   return relerr.error(R_BAD_TUPLE,__FILE__,__LINE__);
return hash->insert(tuple,hash_index(tuple,build));
}

Extension * Combine_attributes::check_hash(Tuple * tuple)
{
Extension *ext = new WS_Extension;
ext->item_size = build_size;
Hashindex mask = hash->size() - 1;
for (Hashindex i=hash_index(tuple,check); hash->table[i]; i = (i+1)&mask )
   if ( hash_match(hash->table[i],tuple) )
      (*ext) += hash->table[i]; 
return ext;
}

ostream &operator<<(ostream &o,Combine_attributes &c)
{
o << "Degree " << c.degree << " build " << chr(c.build)
                  << " check " << chr(c.check) << "\n";
for ( int i=0; i < c.degree; i++ )
   o << chr(c.info[i].which) << " " << c.info[i].length <<
      " " << c.info[i].major_offset << " " << c.info[i].minor_offset
          << " " << *c.info[i].attr;
return o;
}

Combine_attributes::~Combine_attributes()
{
delete info;
delete hash;
}
