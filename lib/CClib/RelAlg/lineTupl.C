#ident "@(#) /sable/sdb/ra/rel/intension/s.lineTupl.C"
/*      Copyright (c) 1989, 1991 AT&T - All Rights Reserved  */

#include <relation.h>

const int Intension::integerLen = 10;
const int Intension::floatLen = 15;

/*                      Intension::line2tuple()
**
**   line2tuple() converts a string of characters into a tuple
**   and returns that tuple to the calling function.
**   The calling function is responsible for deleting the new tuple.
**
**   OUTCOMES:
**      1. When Tuple_new fails
**            return a NULL tuple pointer
**      2. When line to be parsed is a NULL pointer or a NULL string
**            return tuple with all fields set to NULL
**      4. When line to be parsed has more data fields than attributes
**            ignore the extra data fields
**      5. When line to be parsed has fewer data fields than attributes
**            default missing fields to NULL
**      6. For Each Attribute:
**           copy the data from the character string into the tuple
**      7. After copies are completed 
**           return the tuple
*/
Tuple *Intension::line2tuple(const char *line, char attrSep)
    {
    Tuple *tuple = Tuple_new(tuple_size);
    if (!tuple)
       return (Tuple *)0;

    if ( (line == (char *)0) || (line[0] == NULL) )
       return tuple;

    char *tmpline=strdup(line), *remdr=tmpline, *field=(char *)0,
         *offset=(char *)0;

    for ( Degree_t x=0; x<degree; x++ )      /* for each attribute */
       {
       if ( attrSep == '\0' )
          {                   /* default is 1 or more whitespace characters */
          field = strtok(remdr,"\t ");
          remdr = (char *) 0;
          }
       else
          {
          field = remdr;
          if ( remdr = strchr(remdr,attrSep) )
             *(remdr++) = '\0';
          }
       offset = (char *)(tuple->data) + attr_info[x].offset;
       switch(attr_info[x].a->domain.type)
          {
          case INT:
             *(Int_t *)(offset) = (Int_t) atol(field);
             break;
          case FLOAT:
             *(Float_t *)(offset) = (Float_t) atof(field);
             break;
          case STRING:
             strNcpy(offset,field,attr_info[x].a->domain.length);
             break;
          }
       }
    free(tmpline);
    return tuple;
    }

/*                  Intension::tuple2line()
**
** Turn the Tuple into a string, delimiting the attributes of the
** tuple with the attribute separator string.  If requested, produce fixed
** length records.  The string is put into the buffer area provided by the
** application.
**
**  OUTCOMES:
**    1. When the buffer for returning the data is NULL
**         NULL_POINTER error
**    2. When any of the const char * arguments are NULL
**         NULL_POINTER error
**    3. When incoming tuple is NULL
**         set the first byte of the return buffer to NULL
**         and return 0
**    4. copy each attribute from the tuple to the application buffer,
**       delimiting them with the attribute separator.
**    5. If fixed length attributes are required, integers and floating
**       point numbers will be right justified, and strings will be
**       left justified.
**    6. Add the specified string terminator.
**    7. Null terminate the string and return it.
*/
Int_t Intension::tuple2line(Tuple *tuple, const char *attrSep, char *line,
                           Boolean_t fixedLen, const char *terminator)
{
unsigned int minLen = 0;
Int_t nullByte = 0;
char *offset = (char *) 0;

if (!line)
   return syserr.error(NULL_POINTER,__FILE__,__LINE__,"line");

if (!attrSep)
   return syserr.error(NULL_POINTER,__FILE__,__LINE__,"attrSep");

if (!terminator)
   return syserr.error(NULL_POINTER,__FILE__,__LINE__,"terminator");

if (!tuple)
   {
   line[0] = '\0';
   return 0;
   }

for ( Degree_t x=0; x < degree; x++ )     /* for each attribute */
   {
   offset = (char *)(tuple->data) + attr_info[x].offset;
   switch(attr_info[x].a->domain.type)
      {
   case INT:
      minLen = fixedLen ? integerLen : 0;
      nullByte += sprintf(&line[nullByte],"%-*ld%s",minLen,
                                    (long)*(Int_t *)offset,attrSep);
      break;
   case FLOAT:
      minLen = fixedLen ? floatLen : 0;
      nullByte += sprintf(&line[nullByte],"%-*.2lf%s",minLen,
                                  (double)*(Float_t *)offset,attrSep);
      break;
   case STRING:
      minLen = fixedLen ? attr_info[x].a->domain.length : 0;
      nullByte += sprintf(&line[nullByte],"%*s%s",minLen,offset,attrSep);
      break;
      }
   }

nullByte -= strlen(attrSep);           /* overwrite extra attribute separator */
nullByte += sprintf(&line[nullByte],"%s",terminator);
return nullByte;
}
