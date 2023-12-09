#ident "@(#) /sable/sdb/ra/sblib/string/s.string.C"
/*      Copyright (c) 1991 AT&T - All Rights Reserved              */

#include <sblib.h>

/*              split()
**
** The from string has 0 or more newlines.  Consider each newline terminated
** substring as a logical line and the final substring as a logical line.
** Each logical line must be split into lineLen or less, inserting newlines
** as it is copied over to the to string.
** The lineSeparator is the word wrap character and the preserveSeparator
** flag tells whether to keep the separator in addition to the newline.
**
** The split() function returns the number of lines added to the fromString.
** 
*/
int split(const char *fromStr, char *toStr, int lineLen,
          char lineSeparator, Boolean_t preserveSeparator)
    {
    char *buffer = strdup(fromStr);
    int addedLines = 0, offset=0;
    char *start = buffer, *logEnd, *physEnd, *next, save;

    if (toStr)
       toStr[0] = '\0';
    else return -1;
    if ( !fromStr ) return -1;
    if ( lineLen < 1 ) return -1;

    do {
       if ( next=strchr(start,'\n') )
          {
          physEnd = next - 1;
          *next = '\0'; /* for now */
          }
       else physEnd = start + strlen(start);
       while ( strlen(start) > lineLen )
          {
          save = start[lineLen+1];
          start[lineLen+1] = '\0';
          if ( (logEnd=strrchr(start,lineSeparator)) && (logEnd!=start) )
             {
             offset += sprintf(toStr+offset,"%.*s\n",logEnd-start,start);
             if ( preserveSeparator ) logEnd--;
             }
          else
             {
             logEnd = start+lineLen-1;
             offset += sprintf(toStr+offset,"%.*s\n",lineLen,start);
             }
          start[lineLen+1] = save;
          start = logEnd+1;
          addedLines++;
          }
       offset += sprintf(toStr+offset,"%s",start);
       if ( next )
          {
          start = next + 1;
          offset += sprintf(toStr+offset,"\n");
          }
       }
    while ( next );
    free(buffer);
    return addedLines;
    }

char *canonSpan(const char *fromStr,char *toStr,
                char spanChar,unsigned canLength)
{
if ( !fromStr || !toStr ) return (char *)0;

char prevChar='\0';
const char *cursor=(char *)0;
int offset = 0;

for ( cursor=fromStr; *cursor; prevChar=*cursor,cursor++ )
   if ( *cursor == spanChar )
      {
      if ( prevChar != spanChar )
         {
         memset(toStr+offset,spanChar,canLength);
         offset += canLength;
         }
      /* else inside a span so do nothing */
      }
   else toStr[offset++] = *cursor; /* just copy it */
toStr[offset] = '\0';
return toStr;
}

#if !sun
char *strstr(const char *str,const char *subStr)
{
int i,j;
for ( i=0; str[i]; i++ )
   {
   for ( j=0; str[i+j] && (str[i+j] == subStr[j]); j++ )
      ;
   if ( subStr[j] == '\0' )
      return (char *)(str + i);
   }
return (char *)0;
}
#endif

/*  Use local time and order date YY/MM/DD for sorting purposes */
void format_time(char *date, char *tod, time_t clocktime)
    {
    if ( clocktime == 0 )
       clocktime = time((long *)0);
    struct tm *ltm = localtime(&clocktime);
    if ( date )
       sprintf(date,"%02d/%02d/%02d",ltm->tm_year,ltm->tm_mon+1,ltm->tm_mday);
    if ( tod )
       sprintf(tod, "%02d:%02d:%02d",ltm->tm_hour,ltm->tm_min,ltm->tm_sec);
    }
