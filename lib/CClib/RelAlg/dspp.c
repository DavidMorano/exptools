#ident "@(#) /sable/sdb/ra/s.dspp.c"
/*      Copyright (c) 1990,1991 AT&T - All Rights Reserved */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define STARTMACRO "\\*("
#define C2I(C) ( islower(C)?(C)-'a':isupper(C)?(C)-'A'+26:-1 )

char * index(str,subStr)
char *str,*subStr;
{
char *startMatch;
int i;
for ( startMatch = str; *startMatch; startMatch++ )
   {
   for ( i=0; subStr[i] && (startMatch[i] == subStr[i]); i++ )
      ;
   if ( subStr[i] == '\0' )
      return startMatch;
   }
return (char *)0;
}

static char *macros[52][52];

char *expand(line)
char *line;
{
char buffer[BUFSIZ];
char *linePtr=line, *bufPtr=buffer, *newPtr, *macPtr;
int macLen;
while ( newPtr = index(linePtr,STARTMACRO) )
      {
      newPtr[0] = '\0';
      strcpy(bufPtr,linePtr);
      bufPtr += newPtr - linePtr;
      if ( isalpha(newPtr[3]) && isalpha(newPtr[4]) )
         {
         macPtr = macros[C2I(newPtr[3])][C2I(newPtr[4])];
         if ( !macPtr )
            {
            fprintf(stderr,"dspp: assuming mm defines \\*(%c%c.\n",
                       newPtr[3],newPtr[4]);
            macPtr="";
            }
         newPtr += 5;
         }
      else
         {
         macPtr = STARTMACRO;
         newPtr += 3;
         }
      macLen = strlen(macPtr);
      if ( (bufPtr+macLen-buffer) > BUFSIZ )
         {
         fprintf(stderr,"Line too long: %s%s",buffer,macPtr);
         exit(__LINE__);
         }
      strcpy(bufPtr,macPtr);
      bufPtr += macLen;
      linePtr = newPtr;
      }
if ( (bufPtr+strlen(linePtr)-buffer) > BUFSIZ )
   {
   fprintf(stderr,"Line too long: %s%s",buffer,linePtr);
   exit(__LINE__);
   }
strcpy(bufPtr,linePtr);
return strdup(buffer);
}

main()
{
char line[BUFSIZ];
char *linePtr, *endPtr;
while ( fgets(line,BUFSIZ,stdin) )
   {
   if ( (line[0]=='.') && (line[1]=='d') && (line[2]=='s')
         && isspace(line[3]) && isalpha(line[4]) && isalpha(line[5]) )
      {
      linePtr = expand(line+7);
      endPtr = linePtr + strlen(linePtr) -1;
      if ( (endPtr >= linePtr) && (*endPtr == '\n') )
         *endPtr = '\0';
      macros[C2I(line[4])][C2I(line[5])] = linePtr;
      }
   else
      {
      fputs(linePtr=expand(line),stdout);
      free(linePtr);
      }
   }
}
