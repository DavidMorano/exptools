#ident "@(#) /sable/sdb/ra/sblib/pattern/s.pattern.C"
/*      Copyright (c) 1989, 1991 AT&T - All Rights Reserved   */

#include <sblib.h>

const int NPTRNERR=3;
static Error_message pattern_errors[NPTRNERR] = {
{ "BAD_ASSIGNMENT_TEST", MM_SOFT|MM_UTIL, MM_ERROR, 
  "Unexpected error: could not regcmp assignment_test", 
  "PROGRAMMER: The assignment test pattern must be changed and recompiled" },
{ "PATTERN_ASSIGNMENT", MM_SOFT|MM_UTIL, MM_ERROR, 
  "Assignment not allowed in pattern",
  "PROGRAMMER: The pattern contains $ assignments that are not allowed" },
{ "BAD_PATTERN", MM_SOFT|MM_UTIL, MM_ERROR, 
  "Invalid pattern", "PROGRAMMER: This pattern will not pass regcmp(3X)" }
   };
Error ptrn_err(pattern_errors,NPTRNERR);

#undef ERROR
#define ERROR(ERRNUM) { ptrn_err.error(ERRNUM,__FILE__,__LINE__); return; }


Pattern::Pattern(const char *const pattern) 
{
if ( !assignment_test ) // if first call to Pattern::Pattern
   if ( (assignment_test = regcmp("[)]\$[0-9]",(char *)0)) == (char *) 0 )
      ERROR(P_BAD_ASSIGNMENT_TEST)
if ( regex(assignment_test,pattern) )
   ERROR(P_PATTERN_ASSIGNMENT)
if ( (expr = regcmp(pattern,(char *)0)) == (char *) 0 )
   ERROR(P_BAD_PATTERN)
_pattern_string = strdup(pattern);
}

Pattern::~Pattern() 
{
if(expr) free(expr); 
if(_pattern_string) free(_pattern_string);
}

Boolean_t Pattern::match(const char *const string) const
{
if ( string && regex(expr,string) )
   return TRUE;
else 
   return FALSE;
}
