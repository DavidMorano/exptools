#ident "@(#) /sable/sdb/ra/rel/extension/s.ext.C"
/*      Copyright (c) 1989,1991 AT&T - All Rights Reserved */

#include <relation.h>

ostream &operator<<(ostream &o,Extension &e)
{
Tuple *t=(Tuple *)0;
for ( e.startwalk(); t = e.walk(); )
   o << t;
e.endwalk();
return o;
}

Extension::Extension()
{
item_size = nitems = 0; walking = FALSE;
}
unsigned Extension::cardinality()
{
if ( !item_size )
   { relerr.error(R_UNKNOWN_EXTENSION_SIZE,__FILE__,__LINE__); abort(); }
return nitems;
}
Boolean_t Extension::startwalk()
{
if ( !item_size )
   return relerr.error(R_UNKNOWN_EXTENSION_SIZE,__FILE__,__LINE__);
else if ( walking ) 
   return relerr.error(R_IN_WALK,__FILE__,__LINE__);
else { walking = TRUE; return TRUE; }
}
Tuple * Extension::walk()
{
if ( !walking )
   return (Tuple *) relerr.error(R_NOT_IN_WALK,__FILE__,__LINE__);
else return (Tuple *)TRUE;
}
Boolean_t Extension::operator=(Tuple *t)
{
if ( !t )
   return relerr.error(R_BAD_TUPLE,__FILE__,__LINE__);
else if ( !walking )
   return relerr.error(R_NOT_IN_WALK,__FILE__,__LINE__);
else return TRUE;
}
Boolean_t Extension::endwalk()
{
if ( !walking )
   return relerr.error(R_NOT_IN_WALK,__FILE__,__LINE__);
else { walking = FALSE; return TRUE; }
}
Boolean_t Extension::truncate()
{
if ( walking )
   return relerr.error(R_IN_WALK,__FILE__,__LINE__);
else return TRUE;
}
Boolean_t Extension::operator+=(Tuple *tuple)
{
if ( !item_size )
   return relerr.error(R_UNKNOWN_EXTENSION_SIZE,__FILE__,__LINE__);
else if ( !tuple )
   return relerr.error(R_BAD_TUPLE,__FILE__,__LINE__);
else return TRUE;
}
