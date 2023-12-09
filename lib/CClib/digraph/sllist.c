/*
			AT&T - PROPRIETARY
	THIS DOCUMENT CONTAINS PROPRIETARY INFORMATION OF
	AT&T AND IS NOT TO BE DISCLOSED OR USED EXCEPT IN
	ACCORDANCE WITH APPLICABLE AGREEMENTS.

		Copyright (c) 1988 AT&T
		Unpublished & Not for Publication
		All Rights Reserved
*/

#ident "libsfmac:sllist.c 1.1 1/18/89"
#ident "@(#)libsfmac:sllist.c	1.1"


/**

.File Name
	sllist.c

.Author
	M. T. Emanuel

.Date Created
	Nov. 19, 1988

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
#include "general.h"

/*	Unit Header Files					*/
#include "sllist.h"

/*	Constant Definitions					*/

/*	Macro Definitions and inlines				*/

/*	Typedefs, Structure and Union Declarations		*/

/*	External Variable Declarations				*/

/*	Global Variable Definitions Outside of this File	*/

/*	Global Variable Definitions Restricted to this File	*/

/*	Declarations of Functions External to this File		*/

/*	Declarations of Functions Defined in this File		*/


/**

.Name
	sllist()

.Library Name
	libsfmac

.Description
	this is the constructor for an sllist.
	It creates an empty header link.

.Preconditions

.Constraints

.Side Effects

.Return Values

.Notes

.See Also

**/

/*	Begin Synopsis	*/
sllist::sllist()
/* 	End Synopsis 	*/
{
	if(this == (sllist*)NULL)
		return;

	next = (sllist *)NULL;
	obj = (void *)NULL;
}

/**

.Name
	sllist - constructor

.Library Name
	libsfmac

.Description
	This constructor will take a pointer to an oldlist and
	create a new list with the contents of the old list.

.Preconditions

.Constraints

.Side Effects

.Return Values

.Notes

.See Also

**/

/*	Begin Synopsis	*/
sllist::sllist(sllist *oldlist)
/*	End Synopsis	*/
{
	sllist *tmp;

	tmp = oldlist->ptr_copy();
	if(tmp == (sllist*)NULL)
	    return;

	this->next = tmp->next;
	obj = (void *)NULL;

}
/**

.Name
	sllist - constructor

.Library Name
	libsfmac

.Description
	this function is the constructor for an sllist.
	It takes a reference to list.

.Preconditions

.Constraints

.Side Effects

.Return Values

.Notes

.See Also

**/

/*	Begin Synopsis	*/
sllist::sllist(sllist &oldlist)
/*	End Synopsis	*/
{
	sllist *tmp;
	
	tmp = oldlist.ptr_copy();

	if(tmp != (sllist *)NULL)
	{
		next = tmp->next;
	}
	else
	{
	   next = (sllist*)NULL;
	}

	obj = (void *)NULL;

}

/**

.Name
	sllist destructor

.Library Name
	libsfmac

.Description
	this is the destructor of the sllist class

.Preconditions

.Constraints

.Side Effects

.Return Values

.Notes

.See Also

**/

/*	Begin Synopsis	*/
sllist::~sllist()
/*	End Synopsis	*/
{

	if(next)
		delete next;

}

/**

.Name
	append()

.Library Name
	libsfmac

.Description
	 this function will add the specified object
	 at the end of the list

.Preconditions

.Constraints

.Side Effects
	a new object is added to the list.

.Return Values
	SUCCESS - object added
	ERROR - object not added

.Notes

.See Also

**/

/*	Begin Synopsis	*/
int
sllist::append(void *new_obj)
/*	End Synopsis	*/
{
	sllist *new_link, *cur;

	if(new_obj == (sllist*)NULL)
		return(ERROR);

	if((new_link = new sllist) == (sllist *)NULL)
		return(ERROR);

	new_link->obj = new_obj;
	
	cur = this;
	while(cur->next != (sllist *)NULL)
	{
		cur = cur->next;
	}
	
	cur->next = new_link;
	return(SUCCESS);
}

/**

.Name
	remove()

.Library Name
	libsfmac

.Description
 	this function will delete the specified object
 	from the list

.Preconditions

.Constraints

.Side Effects
	a link is removed from the list.

.Return Values
	SUCCESS - if the object
	 	  was removed

	ERROR - if the object was not found in the list

.Notes

.See Also

**/

/*	Begin Synopsis	*/
int
sllist::remove(void *del_obj)
/* 	End Synopsis */
{
	sllist *cur, *tmp;
	cur = this;

	if((is_empty()) == TRUE)
		return(ERROR);

	while(cur->next != (sllist *)NULL)
	{
		if(cur->next->obj == del_obj)
		{
			tmp = cur->next;
			cur->next = cur->next->next;
			tmp->next = (sllist *)NULL;
			delete tmp;
			return(SUCCESS);
		}
		cur = cur->next;
	}

	return(ERROR);
}


// this function will insert the specified object
// at the index position index base is 0 
// placed at the 0th posistion in the list
int
sllist::insert(void *new_obj, int index)
{
	sllist *new_link, *cur, *tmp_ptr;
	int i = 0;

	cur = this;
	if(cur == (sllist *)NULL)
		return(ERROR);

	while((cur->next != (sllist *)NULL) && (i < index))
	{
		cur = cur->next;
		i++;
	}
	if((i == index) && ((new_link = new sllist)) != (sllist *)NULL)
	{
		tmp_ptr = cur->next;
		new_link->obj = new_obj;
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

sllist *
sllist::ptr_copy()
{
	sllist *cur, *new_list, *new_link, *beg;

	cur = this;

	if((new_list = new sllist) == (sllist *)NULL)
		return((sllist*)NULL);

	beg = new_list;

	if((cur = cur->next) == (sllist *)NULL)
		return(beg);

	while(cur != (sllist *)NULL)
	{
		if((new_link = new sllist) == (sllist *)NULL)
                {
			delete beg;
			return((sllist*)NULL);
		}

		new_link->obj = cur->obj;
		cur = cur->next;
		new_list->next = new_link;
		new_list = new_list->next;
	}
	return(beg);
}

int
sllist::is_empty()
{

	if(this == (sllist *)NULL || next == (sllist *) NULL)
	{
		return(TRUE);
	}
	else
	{
		return(FALSE);
	}
}

sllist*
sllist::nthcdr(int index)
{
	sllist *cur;
	int i;

	cur = this;
	
	if(cur == (sllist *)NULL)
		return((sllist *)NULL);

	for(i = 0; i < index && cur->next != (sllist *)NULL; i++)
	{
		cur = cur->next;
	}
	
	if(cur->next  == (sllist *)NULL)
		return((sllist *)NULL);
	else
		return(cur);
}
	
int
sllist::push(void *new_obj)
{
	sllist *new_link, *cur, *tmp_ptr;
	int i = 0;

	cur = this;

	// hold 1 on
	tmp_ptr = cur->next;

	// create new link
	if((new_link = new sllist) == (sllist*)NULL)
		return(ERROR);

	new_link->obj = new_obj;

	cur->next = new_link;
	cur = cur->next;
	cur->next = tmp_ptr;
	return(SUCCESS);
}

void *
sllist::pop()
{
	sllist *tmp;
	void *ret_obj;

	if((this == (sllist *)NULL) || next == (sllist*)NULL)
		return((void *)NULL);

	ret_obj = next->obj;

	tmp = next;
 	if(next->next != (sllist*)NULL)
		next = next->next;
	else 
		next = (sllist*)NULL;

	tmp->next = (sllist *)NULL;
	delete tmp;

	return(ret_obj);
}

void *
sllist::nth(int index)
{
	sllist *cur;
	int i = 0;

	cur = this;
	if(cur == (sllist*)NULL)
		return((void *)NULL);

	for(i = 0;(cur != (sllist *)NULL) && (i <= index); i++)
	{
		cur = cur->next;
	}
	i--;

	if(i == index && cur != (sllist*)NULL)
	{
		return(cur->obj);
	}
	else
	{
		return((void *)NULL);
	}
}

int
sllist::length()
{
	sllist *cur;
	int i;

	cur = this;

	if(cur == (sllist *)NULL|| next == (sllist*)NULL)
		return(0);

	cur = cur->next;
	for(i = 0 ; cur != (sllist *)NULL; i ++, cur = cur->next)
		;

	return(i);
}

void *
sllist::car()
{
	
	if((this == (sllist *)NULL) || next == (sllist*)NULL)
		return((void *)NULL);
	return(next->obj);
}

int 
sllist::exist(void *object)
{
	sllist *cur;

	cur = this;
	
	if(cur == (sllist*)NULL)
	   	return(FALSE);
	else
		cur = cur->next;

	while(cur != (sllist *)NULL)
	{
		if(cur->obj == object)
			return(TRUE);
		cur = cur->next;
	}
	return(FALSE);
}

sllist *
sllist::concat(sllist *list2)
{
	sllist *tmp_list, *tmp_list2, *beg, *tmp;


	if((tmp_list = ptr_copy()) == (sllist *)NULL)
	{
		if((tmp_list = new sllist) == (sllist *)NULL)
			return((sllist *)NULL);
	}
	beg = tmp_list;

	if((tmp_list2 = list2->ptr_copy()) == (sllist*)NULL)
	{
		return(beg);
	}
	else
	{
		tmp = tmp_list2;
		tmp_list2 = tmp_list2->next;
		tmp->next = (sllist *)NULL;
		delete tmp;
	}

	while(tmp_list->next != (sllist *)NULL)
	{
		tmp_list = tmp_list->next;
	}
	tmp_list->next = tmp_list2;

	return(beg);
}

sllist *
sllist::copy()
{
	return(ptr_copy());
}

int 
sllist::add_link(sllist *newlink)
{
	
	sllist *cur;
	
  	if(newlink == (sllist *)NULL)
	{
		return(ERROR);
	}

	cur = this;
	while(cur->next != (sllist *)NULL)
	{
		cur = cur->next;
	}
	
	cur->next = newlink;
	return(SUCCESS);
}

/**

.Name

.Library Name

.Description

.Preconditions

.Constraints

.Side Effects

.Return Values

.Notes

.See Also

**/

/*	Begin Synopsis	*/
int
sllist::replace(int loc, void *robj)
{
	sllist *cur;
	int index = 0;

	cur = this;

	while((cur != (sllist*)NULL) && (index < loc))
	{
		cur = cur->next;
		index++;
	}

	if(cur == (sllist*)NULL)
	{
		return(ERROR);
	}

	if(cur->next == (sllist*)NULL)
	{
		return(ERROR);
	}
	else
	{
		cur->next->obj = robj;
		return(SUCCESS);
	}
}

	
