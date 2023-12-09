#ifndef INT_SLLIST_H

/*
			AT&T - PROPRIETARY
	THIS DOCUMENT CONTAINS PROPRIETARY INFORMATION OF
	AT&T AND IS NOT TO BE DISCLOSED OR USED EXCEPT IN
	ACCORDANCE WITH APPLICABLE AGREEMENTS.
	
		Copyright (c) 1988 AT&T
		Unpublished & Not for Publication
		All Rights Reserved
*/

#ident	"libsfmac:int_sllist.h 1.1 1/18/89"
#ident	"@(#)libsfmac:int_sllist.h	1.1"


/**

.File Name
	int_sllist.h

.Author
	M. T. Emanuel

.Date Created
	Oct 10, 1988

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


#define INT_SLLIST_H

class int_sllist {

	int_sllist *next;
	int obj;
	int_sllist *ptr_copy();

public:

	int_sllist();
	int_sllist(int_sllist *oldlist);
	int_sllist(int_sllist &oldlist);
	~int_sllist();

	void *operator[](int);
	void *car();
	void *nth(int index);
	void* pop();

	int_sllist *cdr();
	int_sllist *cddr();
	int_sllist *nthcdr(int index);
	int_sllist *copy();

	int remove(int new_int);
	int append(int new_int);
	int insert(int new_int, int index);
	int push(int new_int);

	int is_empty();
	int length();
	int exist(int number);
	int_sllist *concat(int_sllist *list2);

};

inline void*
int_sllist::operator[](int index)
{
	return(nth(index));
}

inline int_sllist*
int_sllist::cddr()
{
	return(nthcdr(2));
}

inline int_sllist *
int_sllist::cdr()
{
	return(nthcdr(1));
}

#endif
