#ident "@(#) /sable/sdb/ra/sblib/upper/s.upper.C"
#ident  "@(#) /sable/sdb/ra/sblib/upper/s.upper.C"
/*      Copyright (c) 1989,1991 AT&T - All Rights Reserved */

#include<ctype.h>
#include<malloc.h>
#include<string.h>

char * upper(const char *str)
{
static char *loc_str= (char *)0;
if ( loc_str ) free(loc_str);
loc_str = strdup(str);
for ( int i=0; loc_str[i] != '\0'; i++ )
   loc_str[i] = toupper( loc_str[i] );
return loc_str;
}

char * lower(const char *str)
{
static char *loc_str= (char *)0;
if ( loc_str ) free(loc_str);
loc_str = strdup(str);
for ( int i=0; loc_str[i] != '\0'; i++ )
   loc_str[i] = tolower( loc_str[i] );
return loc_str;
}
