/*
			AT&T - PROPRIETARY
	THIS DOCUMENT CONTAINS PROPRIETARY INFORMATION OF
	AT&T AND IS NOT TO BE DISCLOSED OR USED EXCEPT IN
		ACCORDANCE WITH APPLICABLE AGREEMENTS.

			Copyright (c) 1987 AT&T
		Unpublished & Not for Publication
			All Rights Reserved
*/

#ident "libsfmac:SHash.c 1.3 1/30/89"
#ident "@(#)libsfmac:SHash.c	1.3"

/*
 * SHash class definition
 *
 * Based on the hash table routines written by
 * G. S. Fowler
 * AT&T Bell Laboratories
 *
 */

#include "SHash.h"

inline StringPair::StringPair()
{
}

inline StringPair::StringPair(StringPair& old)
{
	name = old.name;
	value = old.value;
}

inline unsigned int
SHash::HASH(const String& n)
{
	int i = n.hashval()%size;

	if (i < 0)
		i += size;
	return (unsigned int)i;
}

/*
 * "Real" Constructor
 * create a new hash table
 */
void
SHash::CNSTRTR(	unsigned int	tsize,		// Hash table size
		const String&	tname,			// Hash table name
		const String&	terror)		// Error return value
{
	register StringPair	**b;

	size = tsize;
	table = new StringPair* [size];
	flags = 0;
	error = terror;
	b = table;
	while (tsize--) *b++ = (StringPair*)0;
	chains = 0;
	if (!tname.is_empty()) {
		name = tname;
	} else {
		name = "unnamed";
	}
	accesses = 0;
	buckets = 0;
	collisions = 0;
}

/* Constructor for "copying" */
SHash::SHash(SHash& old)
{
	register StringPair	*bucket;

	size = old.size;
	name = old.name;
	error = old.error;
	table = new StringPair* [size];
	for (int j=0; j < size; j++)
		table[j] = (StringPair*)0;
	chains = 0;
	collisions = 0;
	accesses = 0;
	flags = 0;
	buckets = 0;
	for (unsigned int i=0; i <size; i++) {
		for (bucket = old.table[i]; bucket; bucket = bucket->next) {
			put(bucket->name, bucket->value);
		}
	}
}

/*
 * remove a hash table
 */
/*	Destructor */
SHash::~SHash()
{
	register unsigned int	i=size;
	register StringPair	*k;
	register StringPair	**b = table;
	while (i--) {
		for (k = *b++; k; k = k->next) {
			delete k;
		}
	}
	delete[size] table;
}


SHash*
SHash::resize(unsigned int newsize)
{
	unsigned int	oldsize = size;
	register StringPair	*bucket;
	register StringPair	**savetable = table,
				**oldtable = table;

	if (newsize <= 0 || (newsize == oldsize)) {
		return this;
	}
	if (!(table = new StringPair* [newsize])) {
		table = oldtable;
		return(this);
	}
	size = newsize;
	for (int j=0; j < newsize; j++)
		table[j] = (StringPair*)0;
	chains = 0;
	collisions = 0;
	accesses = 0;
	buckets = 0;
	for (unsigned int i=0; i <oldsize; i++) {
		for (bucket = oldtable[i]; bucket; bucket = bucket->next) {
			put(bucket->name, bucket->value);
			delete bucket;
		}
	}
	delete[oldsize] savetable;
	return(this);
}


/*
 * walk through a hash table
 */

void
SHash::apply(SPAIR_FUNC func)
{
	register unsigned int	i;
	register StringPair	**b, *k;

	b = table;
	i = size;
	flags |= HASH_EXAMINE;	// Inhibit reshuffling of chained buckets
	while (i--) {
		for (k = *b++; k; k = k->next)
			if (k->value != error &&
					(*func)(k->name, k->value)) {
				flags &= ~HASH_EXAMINE;
				return;
			}
	}
	flags &= ~HASH_EXAMINE;
}

String
SHash::get(const String& name)
{
	register StringPair	*b, *p;

	accesses++;
	lastbucket = (StringPair*)0;
	lastindex = HASH(name);
	for (p = (StringPair*)0, b = table[lastindex]; b; p = b, b = b->next)
	{
		if (b->name == name) {
			lastbucket = b;
			if (p && !(flags & HASH_EXAMINE))
			{
				/*
			 	 * move this bucket to the front of the list
			 	 * this places the popular names near the front
			 	 */
				p->next = b->next;
				b->next = table[lastindex];
				table[lastindex] = b;
			}
			return(b->value);
		} else {
			collisions++;
		}
	}
	return(error);
}

/*
 * Puthash 
 */
Bool
SHash::put(const String& name, const String& value)
{
	if (!name.is_empty())
		(void)get(name);	// Only interested in lastbucket ptr.
	else {
		accesses++;		// Used last accessed bucket
	}
	register StringPair *b=lastbucket;
	if (!lastbucket) {	// Not already there.
		if (!(b = new StringPair))
			return(false);
		if (!(b->next = table[lastindex]))
			chains++;
		table[lastindex] = lastbucket = b;
		// Make copy of the key
		b->name = name;
		buckets++;
	}
	b->value = value;
	return(true);
}

int
SHash::rm(const String& name)
{
	register StringPair*	b;

	if (!name.is_empty()) {
		(void)get(name);	// Interested in bucket, not value
	} else {
		accesses++;		// Use last accessed bucket
	}
	if (b = lastbucket) {
		buckets--;
		if (!(table[lastindex] = b->next))
			chains--;
		delete b;
		return 1;
	}
	return 0;
}

/*
 * dump hash table accounting info
 * if p is 0 then dump all tables
 */

#include <iostream.h>

void
SHash::dump()
{
	cerr << "Dump of SHash table: " << name << "\n";
	cerr << "=================================\n";
	cerr << "Size = " << size << "\t" << "Entries = " << buckets << "\t";
	cerr << "Accesses = " << accesses << "\t" <<
				"Collisions: = " << collisions << "\n";
	cerr << "Chains: = " << chains << "\n";
	cerr << "Contents:\n";
	register StringPair	**b = table;
	for (register unsigned int i=0; i<size; i++) {
		register StringPair	*k= *b++;
		for ( ; k; k = k->next) {
			cerr << "(" << i << ") " << k->name << "\t" <<
					k->value << "\n";
		}
	}
	cerr.flush();
}
