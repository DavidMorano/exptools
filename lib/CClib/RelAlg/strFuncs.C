#ident "@(#) /sable/sdb/ra/rel/relation/s.strFuncs.C"
/*      Copyright (c) 1991 AT&T - All Rights Reserved */

#include <relation.h>

/*                            Relation::string()
**
**  Turn the entire relation into a string, with the tuples and
**  attributes separated by the specified strings.
**
**   OUTCOMES:
**     1. When there is a heading
**          put it in the static buffer followed by a newline.
**     2. When the tuple or attribute Separator is a NULL pointer
**          generate NULL_POINTER error
**     3. When the tuple or attribute separator is a NULL string
**          use it as a NULL string.
**     4. When there is space in the static buffer,
**          copy the tuple data into the static buffer
**     5. When there is NOT enough space in the static buffer,
**          skip the remaining tuples' data and
**          terminate static buffer with "...%s\0" where %s is tupleSeparator
**     6. return the buffer.
*/
char * Relation::string(const char *tupleSeparator, const char *attrSeparator,
                        const char *heading)
{
    Boolean_t overFlow=FALSE;
    static char buffer[BUFSIZ]; buffer[0] = '\0';
    Int_t nullByte=0;
    Tuple *tuple=(Tuple *)0;
    Usage r_usage = usage; usage = LVALUE;    /* protect within the function */
    char *lastpos=(char *)0, *cursor=buffer;
    int attrSepLen=strlen(attrSeparator), tupleSepLen=strlen(tupleSeparator);
    int i=0, maxTupleLen=0;

    if ( (!tupleSeparator) || (!attrSeparator) )
       return (char *) syserr.error(NULL_POINTER,__FILE__,__LINE__);

    lastpos = buffer + BUFSIZ - tupleSepLen - 4 /* ...\0 */;

    if (heading)
       nullByte += sprintf(&buffer[nullByte],"%s\n",heading);

    for ( i=0; i<intension.degree; i++ )        /* calculate max tuple size */
       {
       maxTupleLen += attrSepLen;
       switch(intension.attr_info[i].a->domain.type)
          {
          case STRING: maxTupleLen += intension.attr_info[i].a->domain.length;
                       break;
          case INT:    maxTupleLen += intension.integerLen; break;
          case FLOAT:  maxTupleLen += intension.floatLen; break;
          }
       }
    maxTupleLen += tupleSepLen;

    for ( startwalk(); (tuple=walk()) && !overFlow; )
       {
       if ( (&buffer[nullByte] + maxTupleLen) < lastpos )
          {
          nullByte += intension.tuple2line(tuple,attrSeparator,
                                       &buffer[nullByte],FALSE,tupleSeparator);
          }
       else
          {
          sprintf(&buffer[nullByte],"...%s",tupleSeparator);
          overFlow = TRUE;
          }
       }
    endwalk();
    usage = r_usage;
    destroy_rvalue();
    return buffer;
}

/*                    Relation::appendString()
**
**   The string is parsed into one or more tuples which are added
**   to this relation.
**
**   OUTCOMES:
**     1. Add the tuples to this relation, ignoring duplicates 
**        a. When a NULL pointer or string is passwd
**             add a NULLed tuple to the relation
**        b. When a character is both a tuple & attribute separator, 
**             use it as a tuple separator. 
**        c. When tuple separators are contiguous 
**             treat them as one tuple separator. 
**        d. When attribute separators are contiguous 
**             treat them as individual separators,
**             defaulting the value of the attribute to NULL. 
**        e. When there are fewer Attributes in the string than in the Relation 
**             default the rest of the Attributes to NULL. 
**        f. When there are more Attributes in the string than in the Relation
**             ignore the extras. 
**        g. When the Attribute separator is NULL ('\0'), 
**             use any sequence of tabs & spaces as an Attribute separator
**     2. If all additions are successful 
**          return TRUE 
**     3. Otherwise return FALSE
*/
#undef FALSEreturn
#define FALSEreturn { if (localStr) free(localStr); return FALSE; }
#define ADDTUPLE(LINE)     { \
                       Fc( tuple = intension.line2tuple(LINE,attrSeparator) ) \
                       Fc( This += tuple                                    ) \
                           tuple->done();                                     \
                           }
Boolean_t Relation::appendString(const char *str, const char *tupleSeparator,
                                 char attrSeparator)
{
    Relation &This = *this;
    Tuple *tuple=(Tuple *)0;
    char *localStr=(char *)0, *tupleBeg=(char *)0, *separatorLoc=(char *)0;
    char saveCh='\0';
    int tupleLen=0;

    if ( (str == (char *)0) || (str[0] == '\0') )
       ADDTUPLE(str)                              /* add NULLed tuple */
    else
       {                                         /* add tuple(s) with values */
       tupleBeg = localStr = strdup(str);
       /* handle tuple separator at the beginning of the string */
       if ( (separatorLoc=strpbrk(localStr,tupleSeparator)) == localStr)
          {
          tupleBeg = localStr + strspn(localStr,tupleSeparator);
          separatorLoc = strpbrk(tupleBeg,tupleSeparator);
          }
       for( ; separatorLoc; separatorLoc = strpbrk(tupleBeg,tupleSeparator) )
          {
          saveCh = *(separatorLoc);
          *(separatorLoc) = '\0';
          ADDTUPLE(tupleBeg)
          tupleLen = strlen(tupleBeg);
          *(separatorLoc) = saveCh;
          tupleBeg += tupleLen + strspn(separatorLoc,tupleSeparator);
          }
       /* handle last tuple if string did not end with a tuple separator */
       if ( *(tupleBeg) != '\0' )
          ADDTUPLE(tupleBeg)
       free(localStr);
       }
    return TRUE;
}
