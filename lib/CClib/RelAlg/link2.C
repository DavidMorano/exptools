#ident "@(#) /sable/sdb/ra/sblib/list/s.link2.C"
/*       Copyright (c) 1989,1990,1991 AT&T - All Rights Reserved */


#include <sblib.h>

Link2::~Link2()
{
Link2_List_item *current=0, *del_ptr=0;
for ( current=head.next; current != &head; )
   {
   del_ptr = current;
   current = current->next;
   del_ptr->list = (List *)0;
   delete del_ptr;
   }
}

Link2::Link2() : List (LINK2)
{
head.next = head.prev = &head;
cursor = (Link2_List_item *)0;
}

List_item *Link2::itemize(void *data)
{
List_item *rc = new Link2_List_item;
if (rc) rc->data = data;
return rc;
}

Boolean_t Link2::append(List_item *l)
{
Link2_List_item *li = (Link2_List_item *)l;
if ( List::append(l) )
   {
   head.prev->next = li;
   li->prev = head.prev;
   head.prev = li;
   li->next = &head;
   return TRUE;
   }
else return FALSE;
}

Boolean_t Link2::remove(List_item *l)
{
Link2_List_item *li = (Link2_List_item *)l;
if ( List::remove(l) )
   {
   li->prev->next = li->next;
   li->next->prev = li->prev;
   li->prev = li->next = (Link2_List_item *)0;
   return TRUE;
   }
else return FALSE;
}

Boolean_t Link2::push(List_item *l)
{
Link2_List_item *li = (Link2_List_item *)l;
if ( List::push(l) )
   {
   head.next->prev = li;
   li->next = head.next;
   head.next = li;
   li->prev = &head;
   return TRUE;
   }
else return FALSE;
}

List_item *Link2::pop()
{
List_item *rc = head.next;
if ( List::pop() && (rc != &head) )
   {
   if (!remove(rc)) 
     { syserr.error(UNEXPECTED_ERROR,__FILE__,__LINE__); abort(); }
   }
else 
  rc = (List_item *)0;
return rc;
}

Boolean_t Link2::startwalk()
{
if ( List::startwalk() )
   {
   cursor = head.next;
   return TRUE;
   }
else return FALSE;
}

List_item *Link2::walk()
{
List_item *rc = (List_item *) cursor;
if ( List::walk() && (cursor != &head) )
   cursor = cursor->next;
else 
   rc = (List_item *) 0;
return rc;
}

Boolean_t Link2::endwalk()
{
if ( List::endwalk() )
   {
   cursor = (Link2_List_item *)0;
   return TRUE;
   }
else return FALSE;
}
