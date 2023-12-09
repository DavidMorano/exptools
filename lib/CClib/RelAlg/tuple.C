#ident "@(#) /sable/sdb/ra/rel/tuple/s.tuple.C"
/*      Copyright (c) 1989,1991 AT&T - All Rights Reserved */

#include <relation.h>

ostream &operator<<(ostream &o,const Tuple *const t)
{
char *string = new char[t->size+1];
strncpy(string,(char *)(t->data),t->size);
string[t->size] = '\0';
o << "address: " << (int) t << " count: " << (int) t->count
  << " size: " << t->size << " flags: " << (int) t->flags
  << " data: " << string << "\n";
delete string;
return o;
}

Tuple::Tuple(const size_t s) :size(s),data(new char[s?s:1])
{
memset(data,'\0',s);
count = 1;
flags = 0;
}

Tuple::~Tuple()
{
delete data;
}

Tuple *Tuple_new(const size_t size)
{ // the only way to create Tuples is on the heap
return new Tuple(size);
}

Boolean_t Tuple::operator=(const void *const new_data)
{
if ( !new_data ) { syserr.error(NULL_POINTER,__FILE__,__LINE__); abort(); }
else if ( count > 1 ) 
   { relerr.error(R_TUPLE_SHARED,__FILE__,__LINE__); abort(); }
else
   {
   memcpy(data,new_data,size);
   return TRUE;
   }
}

void Tuple::share()
{
count++;
}

void Tuple::done()
{
/* It is useful to make sure that memory is deleted in all cases.
** This practice caused the R_TOO_MANY_DONES error to appear too often.
*/

/* if ( !count ) relerr.error(R_TOO_MANY_DONES,__FILE__,__LINE__); */

if ( count )
   if ( --count == 0 )
      delete this;
}
