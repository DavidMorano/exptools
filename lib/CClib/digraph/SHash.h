#ifndef	SHASH_H
#define	SHASH_H

/*
			AT&T - PROPRIETARY
	THIS DOCUMENT CONTAINS PROPRIETARY INFORMATION OF
	AT&T AND IS NOT TO BE DISCLOSED OR USED EXCEPT IN
	ACCORDANCE WITH APPLICABLE AGREEMENTS.
	
		Copyright (c) 1988 AT&T
		Unpublished & Not for Publication
		All Rights Reserved
*/

#ident	"libsfmac:SHash.h 1.1 1/18/89"
#ident	"@(#)libsfmac:SHash.h	1.1"


/**

.File Name
	SHash.h
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

typedef int (*SPAIR_FUNC)(const String&, const String&); /* Map function */

/*	Class definitions					*/

class StringPair			/* hash bucket			*/
{
public:
	StringPair();
//	StringPair(StringPair&);

	StringPair*	next;		/* next bucket in list		*/
	String		name;		/* name				*/
	String		value;		/* value			*/
};

class SHash			/* hash table information	*/
{
public:
	SHash(unsigned int tsize,
		const String& tname,
		const String& terror);
	SHash(unsigned int tsize,
		const String& tname);
	SHash(unsigned int tsize);
	SHash(SHash& oldtable);
	~SHash();
	SHash*	resize(unsigned int size);
	String	get(const String& name);
	Bool	put(const String& name, const String& value);
	int	rm(const String& name);
	void	apply(SPAIR_FUNC);
	int	length();
	void	dump();
private:
	StringPair**	table;		/* actual hash table		*/
	unsigned int	size;		/* size of table		*/
	String		error;		/* lookup error return value	*/
	unsigned int	flags;		/* flags: see HASH_*		*/
	unsigned int	lastindex;	/* most recent hash index	*/
	StringPair*	lastbucket;	/* most recent hash bucket	*/
	int		chains;		/* number of bucket chains	*/
	String		name;		/* hash table name		*/
	int		accesses;	/* number of accesses		*/
	int		buckets;	/* number of buckets		*/
	int		collisions;	/* number of collisions		*/
	unsigned int HASH(const String&);
	void CNSTRTR(unsigned int tsize,	/* The REAL constructor */
		const String& tname,
		const String& terror);
};


/*	External Variable Declarations				*/

/*	Function Declarations					*/

/*	Inline Functions					*/
inline int
SHash::length()
{
	return buckets;
}

inline
SHash::SHash(unsigned int tsize,  const String& tname, const String& terror)
{
	CNSTRTR(tsize,  tname, terror);
}

inline
SHash::SHash(unsigned int tsize,  const String& tname)
{
	String terror;
	CNSTRTR(tsize,  tname, terror);
}

inline
SHash::SHash(unsigned int tsize)
{
	String tname, terror;
	CNSTRTR(tsize,  tname, terror);
}
#endif
