#ident "@(#) /sable/sdb/ra/rel/relation/s.bfRel.C"
/*      Copyright (c) 1989, 1990, 1991 AT&T - All Rights Reserved */

#include <relation.h>

Boolean_t BF_Relation::truncate()
{
Boolean_t triggerRc=TRUE;
if ( triggerFunc )
   {
   extension.startwalk();
   while ( (oldTuple=extension.walk()) && 
           (triggerRc=(*triggerFunc)(oldTuple,(Tuple *)0)) )
      ;
   extension.endwalk();
   }
if ( triggerRc==FALSE )
   return relerr.error(R_TRIGGER_FAILED,__FILE__,__LINE__,"truncate");
else return extension.truncate();
}

Tuple *BF_Relation::walk()
{
if ( oldTuple ) oldTuple->done();
while ((oldTuple=extension.walk()) && walk_predicate 
            && !evaluate(oldTuple,*walk_predicate))
   ;
if ( oldTuple ) oldTuple->share();
return oldTuple;
}

void BF_Relation::startwalk(Predicate &p)
{
oldTuple = (Tuple *)0;
Relation::startwalk(p);
}
void BF_Relation::startwalk()
{
oldTuple = (Tuple *)0;
Relation::startwalk();
}
void BF_Relation::endwalk()
{
if ( oldTuple ) oldTuple->done();
Relation::endwalk();
}

Boolean_t BF_Relation::operator=(Tuple *tuple)
{
Boolean_t rc=FALSE;
if ( triggerFunc && !(*triggerFunc)(oldTuple,tuple) )
   rc = relerr.error(R_TRIGGER_FAILED,__FILE__,__LINE__,"operator=");
else if ( (tuple->flags&T_CONSTRAINED) || constrain(tuple) )
   rc = extension = tuple;
if ( rc )
   {
   if ( afterFunc )
      (*afterFunc)(oldTuple,tuple);
   oldTuple->done();
   oldTuple = tuple; /* done() is the responsibility of bf_ext */
   oldTuple->share(); /* keep a hold on this for future triggers */
   }
return rc;
}

Boolean_t BF_Relation::operator+=(Tuple *tuple)
{
Boolean_t rc=FALSE;
if ( triggerFunc && !(*triggerFunc)((Tuple *)0,tuple) )
   rc = relerr.error(R_TRIGGER_FAILED,__FILE__,__LINE__,"operator+=");
else if ( (tuple->flags&T_CONSTRAINED) || constrain(tuple) )
   rc = extension += tuple;
else rc = FALSE;
if ( rc )
   if ( afterFunc )
      (*afterFunc)(oldTuple,tuple);
return rc;
}
