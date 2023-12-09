#ident "@(#) /sable/sdb/ra/sblib/random/s.roll.C"
/*      Copyright (c) 1991 AT&T - All Rights Reserved */

#include <sblib.h>

unsigned long roll(unsigned long sides)
{
static Boolean_t firstPass = TRUE;

if (firstPass)
   {
   srand48(time((long *)  NULL));
   firstPass = FALSE;
   }
return ((unsigned long) (lrand48() % sides));
}
