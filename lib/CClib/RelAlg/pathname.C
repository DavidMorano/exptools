#ident "@(#) /sable/sdb/ra/sblib/pathname/s.pathname.C"
/*     Copyright (c) 1990, 1991 AT&T - All Rights Reserved     */

#include <sblib.h>

char *basename(const char *path, char *buffer)
{
/*  NOTE:
**    DO NOT USE THE Trace or TraceStmt macros in the basename function!!!
**    Trace & TraceStmt use basename() and you will recurse for a long time.
*/
char *lastSlash=(char *)0;

if ( (path != (char *)0) && (buffer != (char *)0) )
   {
   if ( lastSlash = strrchr(path,'/') )
      strcpy(buffer,lastSlash+1);
   else
      strcpy(buffer,path);
   return buffer;
   }
else
   return (char *)0;
}

char *dirname(const char *path, char *buffer)
{
const char *lastSlash=(const char *)0;
int len=0;

if ( (path != (char *)0) && (buffer != (char *)0) )
   {
   if ( lastSlash = (const char *)strrchr(path,'/') )
      {
      len = lastSlash - path;
      strNcpy(buffer,path,len+1);
      return buffer;
      }
   else
      {
      buffer[0] = '.';
      buffer[1] = NULL;
      }
   return buffer;
   }
else
   return (char *)0;
}
