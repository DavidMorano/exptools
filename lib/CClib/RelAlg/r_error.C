#ident "@(#) /sable/sdb/ra/rel/r_error/s.r_error.C"
/*      Copyright (c) 1989, 1990, 1991 AT&T - All Rights Reserved     */

#include <relation.h>
const int NRELERR=37;
static Error_message relation_errors[NRELERR] = {
{ // 0
   "R_BAD_ASSIGNMENT",
   MM_SOFT|MM_NRECOV|MM_UTIL, MM_HALT,
   "Assignment does not have matching attributes",
   "Project or otherwise manipulate the right until it matches the left" },
{ // 1
   "R_READONLY_RELATION",
   MM_SOFT|MM_NRECOV|MM_UTIL, MM_HALT,
   "Attempt to add a tuple to a read only ASCII relation",
   "PROGRAMMER:  Copy to a new relation or open it read-write" },
{ // 2
   "R_NOT_FLOAT_ATTRIBUTE",
   MM_SOFT|MM_NRECOV|MM_UTIL, MM_HALT,
   "Attribute is not a Float_t",
   "PROGRAMMER:  Use an appropriate data value for the attribute type" },
{ // 3
   "R_NOT_INT_ATTRIBUTE",
   MM_SOFT|MM_NRECOV|MM_UTIL, MM_HALT,
   "Attribute is not an Int_t",
   "PROGRAMMER:  Use an appropriate data value for the attribute type"},
{ // 4
   "R_NOT_STRING_ATTRIBUTE",
   MM_SOFT|MM_NRECOV|MM_UTIL, MM_HALT,
   "Attribute is not a String",
   "PROGRAMMER:  Use an appropriate data value for the attribute type" },
{ // 5
   "R_MIXED_DOMAINS",
   MM_SOFT|MM_NRECOV|MM_UTIL, MM_HALT,
   "Must use the same domain",
   "PROGRAMMER:  Use the same domain name, type and length" },
{ // 6
   "R_NOT_FLOAT_DOMAIN",
   MM_SOFT|MM_NRECOV|MM_UTIL, MM_HALT,
   "Domain is not a Float_t",
   "PROGRAMMER:  Use an appropriate data value for the domain type" },
{ // 7
   "R_NOT_INT_DOMAIN",
   MM_SOFT|MM_NRECOV|MM_UTIL, MM_HALT,
   "Domain is not an Int_t",
   "PROGRAMMER:  Use an appropriate data value for the domain type" },
{ // 8
   "R_NOT_STRING_DOMAIN",
   MM_SOFT|MM_NRECOV|MM_UTIL, MM_HALT,
   "Domain is not a String",
   "PROGRAMMER:  Use an appropriate data value for the domain type" },
{ // 9
   "R_UNKNOWN_EXTENSION_SIZE",
   MM_SOFT|MM_NRECOV|MM_UTIL, MM_HALT,
   "Extension of unknown size",
   "PROGRAMMER:  Extension size must be set before first use" },
{ // 10
   "R_HASH_OVERFLOW",
   MM_SOFT|MM_NRECOV|MM_UTIL, MM_HALT,
   "Hash table overflow" ,
   "PROGRAMMER:  Cardinality of a relation is probably corrupted" },
{ // 11
   "R_BAD_CLOSURE",
   MM_SOFT|MM_NRECOV|MM_UTIL, MM_HALT,
   "Join between differing domains",
   "PROGRAMMER: Joined attributes must have same domain name as well as type"
},
{ // 12
   "R_CLOSURE_TOO_BIG",
   MM_SOFT|MM_NRECOV|MM_UTIL, MM_HALT,
   "Too many join fields",
   "PROGRAMMER: Join on fewer fields or reimplement the closure operation" },
{ // 13
   "R_NO_ATTRIBUTE",
   MM_SOFT|MM_NRECOV|MM_UTIL, MM_HALT,
   "The Relation does not contain the Attribute",
   "PROGRAMMER: Check the Relation definition" },
{ // 14
   "R_WRONG_CARDINALITY",
   MM_SOFT|MM_NRECOV|MM_UTIL, MM_HALT,
   "Queue empty but cardinality is positive",
   "PROGRAMMER: Queue was corrupted" },
{ // 15
   "R_REPEATED_ATTRIBUTE",
   MM_SOFT|MM_NRECOV|MM_UTIL, MM_HALT,
   "An attribute name was repeated",
   "PROGRAMMER: Attribute names must be unique within a relation" },
{ // 16
   "R_TOO_MANY_ATTRIBUTES",
   MM_SOFT|MM_NRECOV|MM_UTIL, MM_HALT,
   "Too many attributes",
   "PROGRAMMER:  Use fewer attributes" },
{ // 17
   "R_BAD_UNION",
   MM_SOFT|MM_NRECOV|MM_UTIL, MM_HALT,
   "Union requires the same attributes in the same order",
   "PROGRAMMER:  Project one side to the correct attributes & order" },
{ // 18
   "R_ZERO_QBUCKET",
   MM_SOFT|MM_NRECOV|MM_UTIL, MM_HALT,
   "Zero size Qbucket",
   "PROGRAMMER: Check size specification on queue constructor" },
{ // 19
   "R_LINE_TOO_LONG",
   MM_SOFT|MM_NRECOV|MM_UTIL, MM_HALT,
   "Line in file too long",
   "PROGRAMMER: Check for missing newlines or binary when ASCII was expected"
},
{ // 20
   "R_NO_NEWLINE",
   MM_SOFT|MM_NRECOV|MM_UTIL, MM_HALT,
   "Tuple must be newline terminated",
   "PROGRAMMER:  Terminate the tuple with a newline" },
{ // 21
   "R_INVALID_OPERATION",
   MM_SOFT|MM_NRECOV|MM_UTIL, MM_HALT,
   "Operation not available for this type of relation",
   "PROGRAMMER:  Use a different relation derived class" },
{ // 22
   "R_BITMASK_MISMATCH",
   MM_SOFT|MM_NRECOV|MM_UTIL, MM_HALT,
   "Bitmasks of unequal length were combined",
   "PROGRAMMER:  Combine masks within a single relation" },
{ // 23
   "R_ILLEGAL_INDEX",
   MM_SOFT|MM_NRECOV|MM_UTIL, MM_HALT,
   "Illegal extension index",
   "PROGRAMMER:  Index is zero-based and should be less than cardinality" },
{ // 24
   "R_READONLY_EXTENSION",
   MM_SOFT|MM_NRECOV|MM_UTIL, MM_HALT,
   "Attempt to write to read only extension",
   "PROGRAMMER: Copy to a writable extension or make this extension writable" },
{ // 25
   "R_BAD_TUPLE",
   MM_SOFT|MM_NRECOV|MM_UTIL, MM_HALT,
   "Null Tuple pointer, wrong Tuple size, or zero references to Tuple",
   "PROGRAMMER: Make sure Tuple pointer is properly assigned and shared" },
{ // 26
   "R_TUPLE_SHARED",
   MM_SOFT|MM_NRECOV|MM_UTIL, MM_HALT,
   "Tuple is shared",
   "PROGRAMMER: Can't modify shared tuple. Call Tuple_new and copy data" },
{ // 27
   "R_IN_WALK",
   MM_SOFT|MM_NRECOV|MM_UTIL, MM_HALT,
   "Illegal operation while in a walk",
   "PROGRAMMER: Don't do this operation between startwalk and endwalk" },
{ // 28
   "R_NOT_IN_WALK",
   MM_SOFT|MM_NRECOV|MM_UTIL, MM_HALT,
   "Illegal operation outside of a walk",
   "PROGRAMMER: Don't do this operation except between startwalk and endwalk" },
{ // 29
   "R_INVALID_LENGTH",
   MM_SOFT|MM_NRECOV|MM_UTIL, MM_HALT,
   "An invalid length was specified for a Domain",
   "PROGRAMMER: use sizeof(Int_t) for INT, sizeof(Float_t) for FLOAT, pos number for STRING" },
{ // 30
   "R_TOO_MANY_DONES",
   MM_SOFT|MM_NRECOV|MM_UTIL, MM_HALT,
   "A Tuple or Intension done() was called when no references were left",
   "PROGRAMMER: Don't use done() unless you have created or shared the object" },
{ // 31
   "R_KEY_VIOLATION",
   MM_SOFT|MM_RECOVER|MM_UTIL, MM_WARNING,
   "The Relation contains two Tuples with the same key",
   "Relation::constrain() operator returns a Relation that eliminates duplicates" },
{ // 32
   "R_CONSTRAINT_FAILED",
   MM_SOFT|MM_RECOVER|MM_UTIL, MM_WARNING,
   "A Tuple value failed the Constraint", },
{ // 33
   "R_APPEND_FAILED",
   MM_SOFT|MM_RECOVER|MM_UTIL, MM_WARNING,
   "Failed attempt to append a Tuple to Relation ", 
   "PROGRAMMER:  Look for a failed constraint." },
{ // 34
   "R_DESTROYED_IN_WALK",
   MM_SOFT|MM_RECOVER|MM_UTIL, MM_WARNING,
   "Relation object destroyed while in a walk",
   "PROGRAMMER: End the walk before destroying or passing out of scope" },
{ // 35
   "R_TRIGGER_FAILED",
   MM_SOFT|MM_RECOVER|MM_UTIL, MM_WARNING,
   "The Trigger Function returned FALSE for a Tuple value", },
{ // 36
   "R_MIXED_INTENSIONS",
   MM_SOFT|MM_NRECOV|MM_UTIL, MM_HALT,
   "The Intension argument does not match this relation's Intension", }
   };
Error relerr(relation_errors,NRELERR); // errno errors
