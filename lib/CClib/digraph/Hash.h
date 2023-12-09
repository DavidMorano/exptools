#ifndef	HASH_H
#define	HASH_H

/*
			AT&T - PROPRIETARY
	THIS DOCUMENT CONTAINS PROPRIETARY INFORMATION OF
	AT&T AND IS NOT TO BE DISCLOSED OR USED EXCEPT IN
	ACCORDANCE WITH APPLICABLE AGREEMENTS.
	
		Copyright (c) 1988 AT&T
		Unpublished & Not for Publication
		All Rights Reserved
*/

#ident	"libsfmac:Hash.h 1.2 1/27/89"
#ident	"@(#)libsfmac:Hash.h	1.2"


/**

.File Name
	Hash.h
.Author
	Joe Eccles
.Date Created
	October, 1988
.Description
	Revised definition for hash table class.
.Constraints

.Notes

.See Also

.Standards
This file conforms to the Dept. 54141 C Coding Standards.
Extensions have been added for C++

**/


/*	System Header Files					*/

#include <String.h>

/*	Project Header Files					*/

#include "general.h"

/*	Constant Definitions					*/

#define HASH_EXAMINE	(1<<2)		/* currently in exhash()	*/

/*	Macro and Inline Definitions				*/

/*	Typedefs, Structure and Union Declarations		*/

typedef int (*BUCKET_FUNC)(const String&, const void*); /* Map function */

/*	Class definitions					*/

class Stringbucket			/* hash bucket			*/
{
public:
	Stringbucket();
	Stringbucket(Stringbucket&);
	Stringbucket*	next;		/* next bucket in list		*/
	String		name;		/* name				*/
	void*		value;		/* value			*/
};

class Hash			/* hash table information	*/
{
public:
	Hash(unsigned int tsize, const String& tname,
				const void* terror=(void *)0);
	Hash(Hash& oldtable);
	~Hash();
	Hash*	resize(unsigned int size);
	void*	get(const String& name);
	Bool	put(const String& name, const void* value);
	int	rm(const String& name);
	void	apply(BUCKET_FUNC);
	int	length();
	void	dump();
private:
	Stringbucket**	table;		/* actual hash table		*/
	unsigned int	size;		/* size of table		*/
	void*		error;		/* lookup error return value	*/
	unsigned int	flags;		/* flags: see HASH_*		*/
	String		lastname;	/* most recent hash name	*/
	unsigned int	lastindex;	/* most recent hash index	*/
	Stringbucket*	lastbucket;	/* most recent hash bucket	*/
	int		chains;		/* number of bucket chains	*/
	String		name;		/* hash table name		*/
	int		accesses;	/* number of accesses		*/
	int		buckets;	/* number of buckets		*/
	int		collisions;	/* number of collisions		*/
	unsigned int HASH(const String&);
};


/*	External Variable Declarations				*/

/*	Function Declarations					*/

/*	Inline Functions					*/
inline int
Hash::length()
{
	return buckets;
}

#endif
