#ident "@(#) /sable/sdb/ra/sblib/list/s.list.C"
/*       Copyright (c) 1989, 1991 AT&T - All Rights Reserved   */

#include <sblib.h>

const int NLISTERR = 7;
static Error_message list_errors[NLISTERR] = {
{ // 0
   "WRONG_LIST_TYPE", MM_SOFT|MM_NRECOV|MM_UTIL, MM_HALT,
   "Item passed did not match the List derived class",
   "PROGRAMMER:  Use itemize for the List class you will be operating on" },
{ // 1
   "ON_LIST", MM_SOFT|MM_NRECOV|MM_UTIL, MM_HALT,
   "Item passed is already on a List",
   "PROGRAMMER:  Re-itemize data or remove item from existing List" },
{ // 2
   "STILL_ON_LIST", MM_SOFT|MM_NRECOV|MM_UTIL, MM_HALT,
   "Item being deleted is still on a List",
   "PROGRAMMER:  Remove item from list before deleting it" },
{ // 3
   "NOT_ON_LIST", MM_SOFT|MM_NRECOV|MM_UTIL, MM_HALT,
   "Item passed is not on the List",
   "PROGRAMMER:  make sure item is on the List before trying to remove it" },
{ // 4
   "IN_WALK", MM_SOFT|MM_NRECOV|MM_UTIL, MM_HALT,
   "Illegal operation while in a walk",
   "PROGRAMMER: Don't do this operation between startwalk and endwalk" },
{ // 5
   "NOT_IN_WALK", MM_SOFT|MM_NRECOV|MM_UTIL, MM_HALT,
   "Illegal operation outside of a walk",
   "PROGRAMMER: Don't do this operation except between startwalk and endwalk" },
{ // 6
   "NO_STARTWALK", MM_SOFT|MM_NRECOV|MM_UTIL, MM_HALT,
   "Illegal operation outside of a walk",
   "PROGRAMMER: Need corresponding startwalk" } 
};
Error listerr(list_errors,NLISTERR);

List_item::~List_item() 
{ 
data = (void *)0;
if (list) 
  { listerr.error(L_STILL_ON_LIST,__FILE__,__LINE__); abort(); } 
}

Boolean_t List::append(List_item *li)
{
if ( !li )
   { syserr.error(NULL_POINTER,__FILE__,__LINE__); return FALSE; }
else if ( li->tag != tag )
   { listerr.error(L_WRONG_LIST_TYPE,__FILE__,__LINE__); return FALSE; }
else if ( li->list )
   { listerr.error(L_ON_LIST,__FILE__,__LINE__); return FALSE; }
else { li->list = this; return TRUE; }
}

Boolean_t List::remove(List_item *li)
{
if ( !li )
   { syserr.error(NULL_POINTER,__FILE__,__LINE__); return FALSE; }
else if ( li->tag != tag )
   { listerr.error(L_WRONG_LIST_TYPE,__FILE__,__LINE__); return FALSE; }
else if ( li->list != this )
   { listerr.error(L_NOT_ON_LIST,__FILE__,__LINE__); return FALSE; }
else if ( walking )
   { listerr.error(L_IN_WALK,__FILE__,__LINE__,"(remove)"); return FALSE;}
else { li->list = (List *)0; return TRUE; }
}

Boolean_t List::push(List_item *li)
{
if ( !li )
   { syserr.error(NULL_POINTER,__FILE__,__LINE__); return FALSE; }
else if ( li->tag != tag )
   { listerr.error(L_WRONG_LIST_TYPE,__FILE__,__LINE__); return FALSE; }
else if ( li->list )
   { listerr.error(L_ON_LIST,__FILE__,__LINE__); return FALSE; }
else { li->list = this; return TRUE; }
}

List_item *List::pop()
{
if ( walking ) 
   {
   listerr.error(L_IN_WALK,__FILE__,__LINE__,"(pop)");
   return (List_item *)FALSE; 
   }
else return (List_item *) TRUE; 
}// higher level routines must set ->list of item to NULL to 
 // mark as off the list

Boolean_t List::startwalk()
{
if ( walking )
   {
   listerr.error(L_IN_WALK,__FILE__,__LINE__,"(startwalk)");
   return FALSE;
   }
else { walking = TRUE; return TRUE; }
}

List_item *List::walk()
{
if ( !walking )
   {
   listerr.error(L_NOT_IN_WALK,__FILE__,__LINE__,"(walk)");
   return (List_item *) FALSE;
   }
else return (List_item *) TRUE;
}

Boolean_t List::endwalk()
{
if ( !walking )
   {
   listerr.error(L_NO_STARTWALK,__FILE__,__LINE__);
   return FALSE;
   }
else { walking = FALSE; return TRUE; }
}

