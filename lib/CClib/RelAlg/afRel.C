#ident "@(#) /sable/sdb/ra/rel/relation/s.afRel.C"
/*      Copyright (c) 1989,1990,1991 AT&T - All Rights Reserved */

#include <relation.h>

Tuple *const AF_Relation::walk()
    { /* AF_Relations get a copy of the tuple from line2tuple(), so AF_Relation
      ** has to make sure old walk_tuples are deallocated.
      */
    char *dataPtr=(char *)0;
    Tuple *line;
    if ( walk_tuple )
       {
       walk_tuple->done();
       walk_tuple = (Tuple *) 0;
       }
    int dataLen;
    while ( line = extension.walk() )
       {
       dataPtr = (char *)line->data;
       if ( (dataLen = strlen(dataPtr)) <= 0)
          syserr.error(UNEXPECTED_ERROR,__FILE__,__LINE__);
       dataPtr[dataLen-1] = '\0';                 /* eliminate the newline */
       if ( (walk_tuple=intension.line2tuple(dataPtr,delim[0])) == (Tuple *)0 )
          syserr.error(UNEXPECTED_ERROR,__FILE__,__LINE__);
       if (!walk_predicate || evaluate(walk_tuple,*walk_predicate))
          return walk_tuple;
       else if (walk_tuple)
          {
          walk_tuple->done();
          walk_tuple = (Tuple *)0;
          }
       }
    return walk_tuple;
    }

AF_Relation::AF_Relation(Intension &i,const char *f,char d,Fileperm perm)
        : Relation (i,new AF_Extension(f,perm))
{
delim[0] = d;
delim[1] = '\0';
walk_tuple = (Tuple *)0;
extension.item_size = BUFSIZ;
}

AF_Relation::AF_Relation(Attribute &a,const char *f,char d,Fileperm perm)
        : Relation (a,new AF_Extension(f,perm))
{
delim[0] = d;
delim[1] = '\0';
walk_tuple = (Tuple *)0;
extension.item_size = BUFSIZ;
}

void AF_Relation::endwalk()
{
if ( walk_tuple )
   {
   walk_tuple->done();
   walk_tuple = (Tuple *) 0;
   }
extension.endwalk();
}

Boolean_t AF_Relation::operator=(Tuple *tuple)
{
Tuple *line = Tuple_new(extension.item_size);
Boolean_t rc;
if ( intension.tuple2line(tuple,delim,(char *)line->data,FALSE) )
   {
   rc = (extension = line);
   line->done();
   }
else rc = FALSE;
return rc;
}

Boolean_t AF_Relation::operator+=(Tuple *tuple)
{
Tuple *line = Tuple_new(extension.item_size);
Boolean_t rc;
if ( intension.tuple2line(tuple,delim,(char *)line->data,FALSE) )
   {
   rc = (extension += line);
   line->done();
   }
else rc = FALSE;
return rc;
}
