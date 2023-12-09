#ident "@(#) /sable/sdb/ra/rel/extension/s.ws_ext.C"
/*      Copyright (c) 1989, 1991 AT&T - All Rights Reserved */

#include <relation.h>

Boolean_t WS_Extension::truncate()
{
List_item *item=(List_item *)0;
if ( Extension::truncate() )
   {
   while ( item = list.pop() )
      {
      ((Tuple *)(item->data))->done();
      delete item;
      }
   nitems = 0;
   return TRUE;
   }
else return FALSE;
}

WS_Extension::WS_Extension()
{
walk_item = (List_item *) 0;
walk_tuple = (Tuple *) 0;
}

WS_Extension::~WS_Extension()
{
if ( this->walking )  // Warning message not printed. Msg appeared with almost
   {                  // every error which is a bit too often.
   /* relerr.error(R_DESTROYED_IN_WALK,__FILE__,__LINE__); */
   this->endwalk();
   }
truncate();
delete walk_item;
if ( walk_tuple ) walk_tuple->done();
}

Boolean_t WS_Extension::startwalk()
{
if ( Extension::startwalk() )
   { 
   walk_tuple = (Tuple *) 0;
   walk_item = (List_item *)0;
   return list.startwalk();
   }
else return FALSE;
}

Tuple * WS_Extension::walk()
{
if ( Extension::walk() )
   {
   if ( walk_tuple )
      {
      walk_tuple->done();
      walk_tuple = (Tuple *) 0;
      }
   if ( walk_item = list.walk() )
      {
      walk_tuple = (Tuple *)walk_item->data;
      walk_tuple->share();     /* Set the tuple's count to 1 to be consistent */
      }                        /* with bf_ext and af_ext. */
   return walk_tuple;
   }
else return (Tuple *) 0;
}

Boolean_t WS_Extension::operator=(Tuple *t)
{
if ( Extension::operator=(t) && walk_item )
   {
   ((Tuple *)walk_item->data)->done();
   t->share();
   walk_item->data = t;
   return TRUE;
   }
else return FALSE;
}

Boolean_t WS_Extension::endwalk()
{
if ( Extension::endwalk() )
   { walk_item = (List_item *)0; return list.endwalk(); }
else return FALSE;
}

Boolean_t WS_Extension::operator+=(Tuple *t)
{
List_item *item;
if ( Extension::operator+=(t) )
   {
   t->share();
   if ( (item=list.itemize(t)) && list.append(item) )
      {
      nitems++;
      return TRUE;
      }
   else { t->done(); return FALSE; }
   }
else return FALSE;
}
