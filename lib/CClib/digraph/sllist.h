#ifndef SLLIST_H

#define SLLIST_H 


/*
			AT&T - PROPRIETARY
	THIS DOCUMENT CONTAINS PROPRIETARY INFORMATION OF
	AT&T AND IS NOT TO BE DISCLOSED OR USED EXCEPT IN
	ACCORDANCE WITH APPLICABLE AGREEMENTS.
	
		Copyright (c) 1988 AT&T
		Unpublished & Not for Publication
		All Rights Reserved
*/

#ident	"libsfmac:sllist.h 1.1 1/18/89"
#ident	"@(#)libsfmac:sllist.h	1.1"


/**

.File Name
	sllist.h

.Author
	M. T. Emanuel

.Date Created
	Oct. 10, 1988

.Description

.Constraints

.Notes

.See Also

.Standards
This file conforms to the Dept. 54141 C Coding Standards.
Extensions have been made for C++.

**/


/*	System Header Files					*/

/*	Project Header Files					*/

/*	Symbolic Constant Definitions				*/

/*	Macro Definitions					*/

/*	Constant Variable Definitions				*/

/*	Typedefs, Structure and Union Declarations		*/

/*	External Variable Declarations				*/

/*	Function Declarations					*/

class sllist {

	virtual sllist *ptr_copy();

protected:
	sllist *next;
	void *obj;
	int add_link(sllist *);
public:

	sllist();
	sllist(sllist *oldlist);
	sllist(sllist &oldlist);
	~sllist();
	void *operator[](int);
	void *car();
	void *nth(int index);
	void* pop();
	sllist *cdr();
	sllist *cddr();
	sllist *nthcdr(int index);
	virtual sllist *concat(sllist *list2);
	sllist *copy();
	int remove(void *new_object);
	int append(void *new_object);
	int insert(void *new_object, int index);
	int push(void *new_object);
	int exist(void *object);
	virtual int replace(int, void*);
	int is_empty();
	int length();

};

inline void*
sllist::operator[](int index)
{
	return(nth(index));
}

inline sllist*
sllist::cddr()
{
	return(nthcdr(2));
}

inline sllist *
sllist::cdr()
{
	return(nthcdr(1));
}

#endif
