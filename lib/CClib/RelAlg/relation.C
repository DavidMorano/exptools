#ident "@(#) /sable/sdb/ra/rel/relation/s.relation.C"
/*      Copyright (c) 1989,1990,1991 AT&T - All Rights Reserved */

#include <relation.h>

Boolean_t Relation::operator==(Relation &r)
{
Usage l_usage = usage, r_usage = r.usage;
usage = r.usage = LVALUE;
Boolean_t rc = FALSE;
Relation *expr=(Relation *)0;
if ( cardinality() != r.cardinality() ) // different size
   { rc = FALSE; goto end; }
if ( cardinality() == 0 )        // EMPTY SET - attributes don't matter
   { rc = TRUE; goto end; }
if ( degree() == r.degree() )    // same number of attributes
   {
   for ( Degree_t i=0; i < degree(); i++ )
      if ( r.intension.index(intension.attr_info[i].a->aname) ==  NULLINDEX )
         { rc = FALSE; goto end; } // different attributes
   }
else { rc = FALSE; goto end; }   // different number of attributes
expr = &( (*this)-r );           // set difference
if ( expr->cardinality() == 0 )  // no difference
   rc = TRUE;
else rc = FALSE;
expr->destroy_rvalue();
end:
usage = l_usage; r.usage = r_usage;
r.destroy_rvalue();
destroy_rvalue();
return rc;
}

Boolean_t Relation::operator<=(Relation &r) // subset
{
Usage l_usage = usage, r_usage = r.usage;
usage = r.usage = LVALUE;
Boolean_t rc = FALSE;
Relation *expr=(Relation *)0;
if ( cardinality() == 0 )            // EMPTY SET - subset of all sets
   { rc = TRUE; goto end; };
if ( cardinality()> r.cardinality()) // too large
   { rc = FALSE; goto end; };
if ( degree() == r.degree() )        // same number of attributes
   {
   for ( Degree_t i=0; i < degree(); i++ )
      if ( r.intension.index(intension.attr_info[i].a->aname) ==  NULLINDEX )
         { rc = FALSE; goto end; };     // different attributes
   }
else { rc = FALSE; goto end; };         // different number of attributes
expr = &( (*this)-r );                  // set difference
if ( expr->cardinality() == 0 )         // no difference
   rc = TRUE;
else rc = FALSE;
expr->destroy_rvalue();
end:
r.usage = r_usage; usage = l_usage;
r.destroy_rvalue();
destroy_rvalue();
return rc;
}

Boolean_t Relation::operator=(Relation &r)
{
Tuple *tuple=(Tuple *)0;
if ( &r == this ) // self assignment
   return TRUE;
if ( intension != r.intension )
   return relerr.error(R_BAD_ASSIGNMENT,__FILE__,__LINE__);
truncate();
for ( r.startwalk(); tuple = r.walk(); )
   *this += tuple;
r.endwalk();
r.destroy_rvalue();
return TRUE;
}

Tuple *Relation::walk()
{
Tuple *rc=(Tuple *)0;
while ((rc=extension.walk()) && walk_predicate && !evaluate(rc,*walk_predicate))
   ;
return rc;
}

/* Constructors and destructors */
Relation::Relation(Intension &i,Extension *e)
             : intension(i)
             , extension(e?(*e):(*(Extension *)new WS_Extension))
{
intension.use();
extension.item_size = intension.tuple_size;
usage = LVALUE;
}
Relation::Relation(Attribute &a,Extension *e)
    : intension((*(Intension *)new Intension)/a)
    , extension(e?(*e):(*(Extension *)new WS_Extension))
{
intension.use();
extension.item_size = intension.tuple_size;
usage = LVALUE;
}
Relation::~Relation()
{
intension.done();
Extension *e = &extension;
delete e;      /* compiler gets unhappy about delete &extension; */
}
void Relation::destroy_rvalue()
{
if ( usage == RVALUE ) delete this;
}

/* intension and extension functions */
int Relation::degree()
{
int rc = intension.degree;
/* destroy_rvalue(); */
return rc;
}
int Relation::cardinality()
{
int rc = extension.cardinality();
/* destroy_rvalue(); */
return rc;
}
Boolean_t Relation::constrain(Tuple *tuple)
{
Boolean_t rc = intension.constrain(tuple);
/* destroy_rvalue(); */
return rc;
}
Boolean_t Relation::operator+=(Tuple *tuple)
{
if ( (tuple->flags&T_CONSTRAINED) || constrain(tuple) )
   return extension += tuple;
else return FALSE;
}
Boolean_t Relation::operator=(Tuple *tuple)
{
if ( (tuple->flags&T_CONSTRAINED) || constrain(tuple) )
   return extension = tuple;
else return FALSE;
}

void Relation::startwalk()
{
walk_predicate = (Predicate *) 0;
extension.startwalk();
}
void Relation::startwalk(Predicate &p)
{
walk_predicate = &p;
extension.startwalk();
}
Boolean_t Relation::walk(IntensionValue &iv)
{
if ( intension != iv.intension )
   return relerr.error(R_MIXED_INTENSIONS,__FILE__,__LINE__);
iv = walk();
if ( iv.tuple )
   return TRUE;
else
   return FALSE;
}
void Relation::endwalk()
{
/* The walk_predicate was not allocated by the relation & therefore should not
** be deallocated by it.  Predicate deallocation will be handled in the future.
*/
walk_predicate = (Predicate *)0;
extension.endwalk();
}

/* Boolean_t returning */
Boolean_t Relation::operator<(Relation &r) /* proper subset */
{
Boolean_t rc;
Usage l_usage = usage, r_usage = r.usage;
usage = r_usage = LVALUE;
if ( cardinality() < r.cardinality() )
   rc = ( (*this) <= r );
else rc = FALSE;
usage = l_usage; r.usage = r_usage;
destroy_rvalue();
r.destroy_rvalue();
return rc;
}
Boolean_t Relation::operator>(Relation &r) /* proper superset */
{
return ( r < (*this) );
}
Boolean_t Relation::operator>=(Relation &r) /* superset */
{
return ( r <= (*this) );
}
Boolean_t Relation::operator!=(Relation &r)
{
return ( !( (*this)==r ) );
}
Boolean_t Relation::truncate()
{
return extension.truncate();
}

/* Relation returning */
Relation & Relation::operator[](Attribute &a)
{
Intension *ni = new Intension;
(void) ((*ni)/a);
return (*this)[*ni];
}
Relation & Relation::operator%(Predicate &p)
{
return (*this)[p];
}
/* Assignments */
Boolean_t Relation::operator-=(Relation &r)
{
return *this = *this - r;
}
