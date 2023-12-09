#ident "@(#) /sable/sdb/ra/rel/relation/s.output.C"
/*      Copyright (c) 1989,1990,1991 AT&T - All Rights Reserved */

#include <relation.h>

ostream & operator<<(ostream &s,Relation &r)
{
Usage r_usage = r.usage;
Tuple *tuple=(Tuple *)0;
const char *attrSep=" ", *tupleSep="\n";
char *heading=(char *)0;
int attrSepLen=strlen(attrSep), degree=r.degree(), i=0, maxTupleLen=0;
int maxHeadingLength=0, *headingLengths = new int[degree];

r.usage = LVALUE;                       /* protect within the function */

for ( i=0; i < degree; i++ )            /* output attribute headings */
   {
   maxTupleLen += attrSepLen;
   heading = r.intension.attr_info[i].a->aname.name;
   switch(r.intension.attr_info[i].a->domain.type)
      {
   case STRING:
      headingLengths[i]=MAX(strlen(heading),
                           r.intension.attr_info[i].a->domain.length);
      maxTupleLen += r.intension.attr_info[i].a->domain.length;
      break;
   case INT:
      headingLengths[i]=MAX(strlen(heading),r.intension.integerLen);
      maxTupleLen += r.intension.integerLen;
      break;
   case FLOAT:
      headingLengths[i]=MAX(strlen(heading),r.intension.floatLen);
      maxTupleLen += r.intension.floatLen;
      break;
      }
   maxHeadingLength = MAX(maxHeadingLength,headingLengths[i]);
   s << str(heading,headingLengths[i]) << attrSep;
   }
s << tupleSep;
maxTupleLen += strlen(tupleSep);                /* for the Tuple separator */

char *dashes = new char[maxHeadingLength+2];    /* output the heading */
memset(dashes,'-',maxHeadingLength+1);
dashes[maxHeadingLength+1] = '\0';
for ( i=0; i < degree; i++ )
   {
   dashes[headingLengths[i]] = '\0';
   s << dashes << attrSep;
   dashes[headingLengths[i]] = '-';
   }
s << tupleSep;
delete dashes;
delete headingLengths;

char *line = new char[maxTupleLen+1];
for ( r.startwalk(); tuple=r.walk(); )
   {
   r.intension.tuple2line(tuple,attrSep,line);
   s << line;
   }
r.endwalk();
r.usage = r_usage;
r.destroy_rvalue();
delete line;
return s;
}
