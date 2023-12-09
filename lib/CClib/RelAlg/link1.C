#ident "@(#) /sable/sdb/ra/sblib/list/s.link1.C"
/*       Copyright (c) 1989,1990,1991 AT&T - All Rights Reserved */


#include <sblib.h>

Link1::~Link1()
{
Link1_List_item *current=0, *del_ptr=0;
for ( current=head; current; )
   {
   del_ptr = current;
   current = current->next;
   del_ptr->list = (List *)0;
   delete del_ptr;
   }
}

Boolean_t Link1::remove(List_item *l)
{
Link1_List_item *li = (Link1_List_item *)l;
Link1_List_item *curr=0, *prev=0;
if ( !List::remove(l) ) return FALSE;
for ( prev=(Link1_List_item *)0,curr=head; curr; prev=curr,curr=curr->next )
   if ( curr == li )
      {
      if (prev)
         {
         if ( (prev->next = curr->next) == (Link1_List_item *)0 ) 
            tail = prev;
         }
      else
         {
         if ( (head = curr->next) == (Link1_List_item *)0 ) 
            tail = (Link1_List_item *)0;
         }
      li->next = (Link1_List_item *)0;
      return TRUE;
      }
// li not on this list - List::remove should have caught this!
syserr.error(UNEXPECTED_ERROR,__FILE__,__LINE__);
return FALSE;
}

Link1::Link1() : List (LINK1)
{
head = tail = cursor = (Link1_List_item *)0;
}

List_item *Link1::itemize(void *data)
{
List_item *rc = new Link1_List_item;
if ( rc ) rc->data = data;
return rc;
}

Boolean_t Link1::append(List_item *l)
{
if ( List::append(l) )
   {
   Link1_List_item *li = (Link1_List_item *)l;
   li->next = (Link1_List_item *)0;
   if ( tail )                      // items already on list
      tail->next = li;
   else 
      head = li;
   tail = li;
   return TRUE;
   }
else return FALSE;
}

Boolean_t Link1::push(List_item *l)
{
if ( List::push(l) )
   {
   Link1_List_item *li = (Link1_List_item *)l;
   li->next = (Link1_List_item *)0;
   if ( head )                      // items already on list
      li->next = head;
   else 
      tail = li;
   head = li;
   return TRUE;
   }
else return FALSE;
}

List_item *Link1::pop()
{
Link1_List_item *rc = (Link1_List_item *)0;
if ( List::pop() )
   {
   rc = head;
   if ( rc )
      {
      head = head->next;
      rc->list = (List *)0;
      rc->next = (Link1_List_item *)0;
      if ( !head ) tail = (Link1_List_item *)0;
      }
   }
return (List_item *) rc;
}

Boolean_t Link1::startwalk()
{
if ( List::startwalk() )
   {
   cursor = head;
   return TRUE;
   }
else return FALSE;
}

List_item *Link1::walk()
{
List_item *rc = (List_item *)0;
if ( List::walk() && (rc = (List_item *)cursor) )
      cursor = cursor->next;
return rc;
}

Boolean_t Link1::endwalk()
{
if ( List::endwalk() )
   {
   cursor = (Link1_List_item *)0;
   return TRUE;
   }
else return FALSE;
}
