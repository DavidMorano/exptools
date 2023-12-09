/*
			AT&T - PROPRIETARY
	THIS DOCUMENT CONTAINS PROPRIETARY INFORMATION OF
	AT&T AND IS NOT TO BE DISCLOSED OR USED EXCEPT IN
	ACCORDANCE WITH APPLICABLE AGREEMENTS.

		Copyright (c) 1988 AT&T
		Unpublished & Not for Publication
		All Rights Reserved
*/

#ident "libsfmac:int_sllist.c 1.1 1/18/89"
#ident "@(#)libsfmac:int_sllist.c	1.1"


/**

.File Name
	int_sllist.c

.Author
	M. T. Emanuel

.Date Created
	Oct. 10, 1988

.Description

.Constraints

.Notes

.See Also

.Standards
This file conforms to the Dept. 54141 C Coding Standards
with modifications for the SUN environment and C++.

**/


/*	System Header Files					*/
#include <stdio.h>

/*	Project Header Files					*/

/*	Unit Header Files					*/

/*	Constant Definitions					*/

/*	Macro Definitions and inlines				*/

/*	Typedefs, Structure and Union Declarations		*/

/*	External Variable Declarations				*/

/*	Global Variable Definitions Outside of this File	*/

/*	Global Variable Definitions Restricted to this File	*/

/*	Declarations of Functions External to this File		*/

/*	Declarations of Functions Defined in this File		*/


#include "int_sllist.h"
#include "general.h"

// list constructor, creates an empty list
int_sllist::int_sllist()
{
	next = (int_sllist *)NULL;
	obj = NULL;
}

// list constructor, initializes list to old list
int_sllist::int_sllist(int_sllist *oldlist)
{
	int_sllist *tmp;

	tmp = oldlist->ptr_copy();
	this->next = tmp->next;
	obj = NULL;

}

// list constructor, initializes list to old list
int_sllist::int_sllist(int_sllist &oldlist)
{

	int_sllist *tmp;

	tmp = oldlist.ptr_copy();
	if(tmp != (int_sllist*)NULL)
	{
		next = tmp->next;
	}
	else
	{
		next = (int_sllist*)NULL;
	}
	obj = NULL;

}

// list destructor
int_sllist::~int_sllist()
{

	if(next)
		delete next;

}

// this function will add the specified object
// at the end of the list
int
int_sllist::append(int new_int)
{
	int_sllist *new_link, *cur;

	if((new_link = new int_sllist) == (int_sllist *)NULL)
	    return(ERROR);
		
	new_link->obj = new_int;

	
	cur = this;
	while(cur->next != (int_sllist *)NULL)
	{
		cur = cur->next;
	}
	
	cur->next = new_link;
	return(SUCCESS);
}

// this function will delete the specified object
// from the list

int
int_sllist::remove(int new_int)
{
	int_sllist *cur, *tmp;
	cur = this;

	if((is_empty()) == TRUE)
		return(ERROR);

	while(cur->next != (int_sllist*)NULL)
	{
		if(cur->next->obj == new_int)
		{
			tmp = cur->next;
			cur->next = cur->next->next;
			tmp->next = (int_sllist*)NULL;
			delete tmp;
			return(SUCCESS);
		}
		cur = cur->next;
	}

	return(ERROR);
}


// this function will insert the specified object
// at the index position
int
int_sllist::insert(int new_int, int index)
{
	int_sllist *new_link, *cur, *tmp_ptr;
	int i = 0;

	cur = this;
	if(cur == (int_sllist *)NULL)
		return(ERROR);

	while((cur->next != (int_sllist *)NULL) && (i < index))
	{
		cur = cur->next;
		i++;
	}
	if((i == index) && ((new_link = new int_sllist)) != (int_sllist*)NULL)
	{
		tmp_ptr = cur->next;
		new_link = new int_sllist;
		new_link->obj = new_int;
		cur->next = new_link;
		cur = cur->next;
		cur->next = tmp_ptr;

	}
	else
	{
		return(ERROR);
	}
	return(SUCCESS);
}

int_sllist *
int_sllist::ptr_copy()
{
	int_sllist *cur, *new_list, *new_link, *beg;

	cur = this;

	if((new_list = new int_sllist) == (int_sllist*)NULL)
		return((int_sllist*)NULL);

	beg = new_list;

	if((cur = cur->next) == (int_sllist*)NULL)
		return(beg);

	while(cur != (int_sllist *)NULL)
	{
		if((new_link = new int_sllist) == (int_sllist*)NULL)
		{
			delete beg;
			return((int_sllist*)NULL);
		}
		new_link->obj = cur->obj;
		cur = cur->next;
		new_list->next = new_link;
		new_list = new_list->next;
	}
	return(beg);
}

int
int_sllist::is_empty()
{
	if(this == (int_sllist *)NULL || next == (int_sllist *) NULL)
	{
		return(TRUE);
	}
	else
	{
		return(FALSE);
	}
}

int_sllist*
int_sllist::nthcdr(int index)
{
	int_sllist *cur;
	int i;

	cur = this;
	
	if(cur == (int_sllist *)NULL)
		return((int_sllist *)NULL);

	for(i = 0; i < index && cur->next != (int_sllist *)NULL; i++)
	{
		cur = cur->next;
	}
	
	if(cur->next  == (int_sllist *)NULL)
		return((int_sllist *)NULL);
	else
		return(cur);
}
	
int
int_sllist::push(int new_int)
{
	int_sllist *new_link, *cur, *tmp_ptr;
	int i = 0;

	cur = this;

	// hold 1 on
	tmp_ptr = cur->next;

	// create new link
	if((new_link = new int_sllist) == (int_sllist*)NULL)
	    return(ERROR);

	new_link->obj = new_int;
	cur->next = new_link;
	cur = cur->next;
	cur->next = tmp_ptr;
	return(SUCCESS);
}

void *
int_sllist::pop()
{
	int_sllist *cur;
	int  *ret_obj;

	if((this == (int_sllist*)NULL) || (next == (int_sllist*)NULL))
	 	return((void*)NULL);

	cur = this;
	ret_obj = &(cur->next->obj);

	cur->next = cur->next->next;
	return(ret_obj);
}

void *
int_sllist::nth(int index)
{
	int_sllist *cur;
	int i = 0;

	cur = this;
	if(cur == (int_sllist*)NULL)
		return((void *)NULL);

	while((cur->next != (int_sllist *)NULL) && (i < index))
	{
		cur = cur->next;
		i++;
	}
	cur = cur->next;
	if(i == index && cur != (int_sllist *)NULL)
	{
		return(&(cur->obj));
	}
	else
	{
		return((void *)NULL);
	}
}

int
int_sllist::length()
{
	int_sllist *cur;
	int i;

	cur = this;

	if((cur == (int_sllist *)NULL) || (next == (int_sllist*)NULL))
		return(0);

	cur = cur->next;
	for(i = 0 ; cur != (int_sllist *)NULL; i ++, cur = cur->next)
		;

	return(i);
}

void *
int_sllist::car()
{
	if((this == (int_sllist *)NULL) || next == (int_sllist*)NULL)
		return((void *)NULL);
	return(&(next->obj));
}

int 
int_sllist::exist(int number)
{
	int_sllist *cur;

	cur = this;
	
	while(cur != (int_sllist *)NULL)
	{
		if(cur->obj == number)
			return(TRUE);
		cur = cur->next;
	}
	return(FALSE);
}

int_sllist *
int_sllist::concat(int_sllist *list2)
{
	int_sllist *tmp_list, *tmp_list2, *beg;


	tmp_list = ptr_copy();
	tmp_list2 = list2->ptr_copy();
	beg = tmp_list;

	while(tmp_list->next != (int_sllist *)NULL)
	{
		tmp_list = tmp_list->next;
	}
	tmp_list->next = tmp_list2->next;

	return(beg);
}

int_sllist *
int_sllist::copy()
{
	int_sllist *tmp_copy;

	tmp_copy = ptr_copy();
	return(tmp_copy);
}
