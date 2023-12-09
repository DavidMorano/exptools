#ident "@(#) /sable/sdb/ra/rel/IValue/s.IValue.C"
/*      Copyright (c) 1991 AT&T - All Rights Reserved        */

#include <relation.h>

/*              IntensionValue::IntensionValue()
**
**      The constructors initialize various members of the IntensionValue.
**
** OUTCOMES:
**    void
*/
IntensionValue::IntensionValue(Intension &i) : intension(i)
    {
    Trace(1,"Entering IntensionValue::IntensionValue(Intension)")
    TraceStmt(2,cerr<<"i = "<<i<<"\n";cerr.flush());
    intension.use();
    tuple = (Tuple *)0;
    for ( int a=0; a < NATTR; a++ )
       avs[a] = (AttributeValue *)0;
    Trace(1,"Returning from IntensionValue::IntensionValue(Intension)")
    }
IntensionValue::IntensionValue(Attribute &a) :
                                    intension((*(Intension *)new Intension)/a)
    {
    Trace(1,"Entering IntensionValue::IntensionValue(Attribute)")
    TraceStmt(2,cerr<<"a = "<<a<<"\n";cerr.flush());
    intension.use();
    tuple = (Tuple *)0;
    for ( int a=0; a < NATTR; a++ )
       avs[a] = (AttributeValue *)0;
    Trace(1,"Returning from IntensionValue::IntensionValue(Attribute)")
    }

/*                 IntensionValue::~IntensionValue()
**
**      Clean up anything that was allocated.
**
** OUTCOMES:
**    void
*/
IntensionValue::~IntensionValue()
    {
    Trace(1,"Entering IntensionValue::~IntensionValue()")
    if ( tuple )
       tuple->done();
    intension.done();
    for ( int a=0; a < NATTR; a++ )
       if ( avs[a] )
          delete avs[a]; /* as opposed to delete [a] avs */
    Trace(1,"Returning from IntensionValue::~IntensionValue()")
    }

/*             IntensionValue::exclusiveTuple()
**
**      Make this IntensionValue's tuple exclusively referenced
**      by this IntensionValue.
**
**   OUTCOMES:
**     1. When this IntensionValue's tuple is not shared
**           do nothing
**     2. When this IntensionValue doesn't have a tuple
**           get a new tuple
**     3. When this IntensionValue's tuple is shared with other objects
**           get a new tuple
**     4. When requested to save the shared tuple's data
**           copy the shared tuple's data into the new tuple
*/
void IntensionValue::exclusiveTuple(Boolean_t saveData)
    {
    Tuple *newTuple = (Tuple *)0;

    Trace(1,form("Entering IntensionValue::exclusiveTuple(%d)",saveData))
    if ( tuple )
       {
       if (tuple->count > 1)
          {                      /* there are other references to this tuple */
          newTuple = Tuple_new(tuple->size);
          if (saveData)
             memcpy(newTuple->data,tuple->data,tuple->size);
          tuple->done();               /* we need our own for updating */
          tuple = newTuple;
          }
    /* else  we have the only reference to this tuple. So just use it */
       }
    else                                        /* get brand new tuple */
       tuple = Tuple_new(intension.tuple_size);
    Trace(1,"Returning from IntensionValue::exclusiveTuple(Boolean_t)")
    }

/*                         IntensionValue::operator=()
**
** The assignment operators assign the new Tuple or data value
** to the IntensionValue's tuple.
**
** OUTCOMES: operator =(void *)
**    1. When the Tuple is the wrong size
**          R_BAD_TUPLE (unexpected)
**    2. Otherwise update the tuple & return TRUE
*/
Boolean_t IntensionValue::operator=(void *v)
    {
    Trace(1,form("Entering IntensionValue::operator=(void *v = %s)",v))
    exclusiveTuple(FALSE);
    if ( tuple->size != intension.tuple_size )
       return relerr.error(R_BAD_TUPLE,__FILE__,__LINE__);
    *tuple = v;                                        /* update the tuple */
    Trace(1,"Returning TRUE from IntensionValue::operator=(void *)")
    return TRUE;
    }
/*
** OUTCOMES: operator =(Tuple *)
**    1. When the Tuple argument is the wrong size
**          R_BAD_TUPLE.
**    2. When the Tuple has no references
**          R_BAD_TUPLE (unexpected).
**    3. When the tuple argument has a tuple
**          update the IV Tuple & return TRUE.
**    4. When the tuple argument is NULL
**          set IV Tuple to NULL & return TRUE.
*/
Boolean_t IntensionValue::operator=(Tuple *rhs)
    {
    Trace(1,"Entering IntensionValue::operator=(Tuple *)")
    TraceStmt(2,cerr<<"rhs = "<<rhs<<"\n";cerr.flush());
    if ( tuple )
       tuple->done();            /* finished using this tuple */
    if ( rhs )
       {
       if ( rhs->size != intension.tuple_size )
          return relerr.error(R_BAD_TUPLE,__FILE__,__LINE__,
                   form("rhsSize=%d,iSize=%d",rhs->size,intension.tuple_size));
       if ( rhs->count <= 0 )
          return relerr.error(R_BAD_TUPLE,__FILE__,__LINE__,"no references");
       tuple = rhs;                 /* point to the new tuple */
       tuple->share();              /* mark that we are using this tuple now */
       }
    else
       tuple = (Tuple *)0;
    TraceStmt(2,cerr<<"tuple = "<<tuple<<"\n";cerr.flush());
    Trace(1,"Returning TRUE from IntensionValue::operator=(Tuple *)")
    return TRUE;
    }

/*                         AttributeValue::operator cast()
**
**   The cast operator returns the Tuple data cast to an appropriate type.
**   Unlike the assignment and comparison operators, it will freely convert
**   to the desired type even if it isn't the same as the underlying Domain
**   type.  In general, casts should be very flexible, compares and
**   assignments inflexible.
**
** OUTCOMES:
**    1. When the tuple is NULL
**         get a new Tuple
**    2. return the tuple value as Int_t, Float_t or const char *.
*/
define(AVcastFunc,
AttributeValue::operator $1()
    {
    Trace(1,"Entering AttributeValue::operator $1()")
    if ( !iv->tuple )
       iv->tuple = Tuple_new(iv->intension.tuple_size);
    char *offset = (char *)(iv->tuple->data) + attrOffset;
    switch(attrDomain.type)
       {
    case INT: Trace(1,"Returning from AttributeValue::operator $1(), INT")
              return $2;
    case FLOAT: Trace(1,"Returning from AttributeValue::operator $1(), FLOAT")
                return $3;
    case STRING: Trace(1,"Returning from AttributeValue::operator $1(), STRING")
                 return $4;
       }
    }
)
AVcastFunc(Int_t,
         *(Int_t *)offset,
         (Int_t)*(Float_t *)offset,
         (Int_t)atol(offset))
AVcastFunc(Float_t,
         (Float_t)*(Int_t *)offset,
         *(Float_t *)offset,
         (Float_t)atof(offset))
AVcastFunc(const char *,
         form("%ld",(long)*(Int_t *)offset),
         form("%f",(double)*(Float_t *)offset),
         offset)

/*                         AttributeValue::operator=()
**
**   The assignment operator gets a new tuple if it is shared or NULL,
** then assigns the given value to the appropriate Tuple Attribute.
**
** OUTCOMES: operator=(AttributeValue &)
**   1. When the domain of the lhs is not equal to the domain of the rhs
**        R_MIXED_DOMAINS
**   2. Otherwise
**        copy the rhs AV into the lhs AV and
**        return TRUE.
*/
Boolean_t AttributeValue::operator=(AttributeValue &rhs)
    {
    char *lhsAL = (char *)0,   /* left hand side's AV's attribute location */
         *rhsAL = (char *)0;   /* right hand sides's AV's attribute location */

    Trace(1,"Entering AttributeValue::operator=(AttributeValue)")
    if ( attrDomain != rhs.attrDomain )
       return relerr.error(R_MIXED_DOMAINS,__FILE__,__LINE__);
    iv->exclusiveTuple();
    lhsAL = (char *)(iv->tuple->data) + attrOffset;
    rhsAL = (char *)(rhs.iv->tuple->data) + rhs.attrOffset;
    memcpy(lhsAL,rhsAL,attrDomain.length);
    Trace(1,"Returning TRUE from AttributeValue::operator=(AttributeValue)")
    return TRUE;
    }
/*
** OUTCOMES: operator=(Int_t, Float_t, const char *)
**    1. When the type of the rhs doesn't match the Domain type
**         R_NOT_<type>_ATTRIBUTE.
**    2. Get exclusive access to a tuple.
**    3. When the value passes the Domain constraint
**          assign the value to the tuple and
**          return TRUE.
**    4. Otherwise
**          return FALSE.
*/
define(assignFn,
Boolean_t AttributeValue::operator=($1 rhs)
    {
    char *attrLoc = (char *)0;

    Trace(1,"Entering AttributeValue::operator=($1)")
    if ( attrDomain.type != $2 )
       return relerr.error(R_NOT_$2_ATTRIBUTE,__FILE__,__LINE__,attrName);
    iv->exclusiveTuple();
    attrLoc = (char *)(iv->tuple->data) + attrOffset;
    if (attrDomain.constrain(rhs))
       {
       $3;
       Trace(1,"Returning TRUE from AttributeValue::operator=($1)")
       return TRUE;
       }
    Trace(1,"Returning FALSE from AttributeValue::operator=($1)")
    return FALSE;
    }
)
assignFn(Int_t, INT, *(Int_t *)attrLoc = rhs)
assignFn(Float_t, FLOAT, *(Float_t *)attrLoc = rhs)
assignFn(const char *, STRING, strNcpy(attrLoc,rhs,attrDomain.length))

/*                         AttributeValue::operator compare()
**
**   The comparison operators compare the Attribute value to the rhs
**   and return TRUE or FALSE.
**
** OUTCOMES:
**    1. When the rhs type doesn't match the Domain type
**          R_NOT_<type>_ATTRIBUTE.
**    2. When the Attribute value has the given relationship ( ==, !=, etc. )
**       to the rhs
**          return TRUE.
**    4. Otherwise
**          return FALSE.
*/
/* opFuncs(comparisonOperator,Int_t|Float_t,INT|FLOAT) */
define(opFuncs,
Boolean_t AttributeValue::operator$1($2 rhs)
    {
    char *attrLoc = (char *)0;

    Trace(1,"Entering AttributeValue::operator$1($2)")
    if ( attrDomain.type != $3 )
       return relerr.error(R_NOT_$3_ATTRIBUTE,__FILE__,__LINE__,attrName);
    if ( !iv->tuple )
       iv->tuple = Tuple_new(iv->intension.tuple_size);
    attrLoc = (char*)(iv->tuple->data) + attrOffset;
    if ( *($2 *)attrLoc $1 rhs)
       {
       Trace(1,"Returning TRUE from AttributeValue::operator$1($2)")
       return TRUE;
       }
    Trace(1,"Returning FALSE from AttributeValue::operator$1($2)")
    return FALSE;
    }
)
/* strOpFuncs(comparisonOperator) */
define(strOpFuncs,
Boolean_t AttributeValue::operator$1(const char *rhs)
    {
    char *attrLoc = (char *)0;
    Dlength attrLen = 0;

    Trace(1,"Entering AttributeValue::operator$1(const char *)")
    if ( attrDomain.type != STRING )
       return relerr.error(R_NOT_STRING_ATTRIBUTE,__FILE__,__LINE__,attrName);
    if ( !iv->tuple )
       iv->tuple = Tuple_new(iv->intension.tuple_size);
    attrLoc = (char*)(iv->tuple->data) + attrOffset;
    attrLen = attrDomain.length;
    if ( strncmp(attrLoc,rhs,attrLen) $1 0 )
       {
       Trace(1,"Returning TRUE from AttributeValue::operator$1(const char *)")
       return TRUE;
       }
    Trace(1,"Returning FALSE from AttributeValue::operator$1(const char *)")
    return FALSE;
    }
)
/* avOpFuncs(comparisonOperator) */
define(avOpFuncs,
Boolean_t AttributeValue::operator$1(AttributeValue &rhs)
    {
    Trace(1,"Entering AttributeValue::operator$1(AttributeValue &)")
    switch (rhs.attrDomain.type)
       {
       case INT: Trace(1,"Returning from AV::operator$1(AV &), INT");
                 return (*this $1 (Int_t)rhs);
       case FLOAT: Trace(1,"Returning from AV::operator$1(AV &), FLOAT");
                   return (*this $1 (Float_t)rhs);
       case STRING: Trace(1,"Returning from AV::operator$1(AV &), STRING");
                    return (*this $1 (const char *)rhs);
       }
    }
)
opFuncs(==,Int_t,INT)
opFuncs(!=,Int_t,INT)
opFuncs(<=,Int_t,INT)
opFuncs(<,Int_t,INT)
opFuncs(>=,Int_t,INT)
opFuncs(>,Int_t,INT)
opFuncs(==,Float_t,FLOAT)
opFuncs(!=,Float_t,FLOAT)
opFuncs(<=,Float_t,FLOAT)
opFuncs(<,Float_t,FLOAT)
opFuncs(>=,Float_t,FLOAT)
opFuncs(>,Float_t,FLOAT)
strOpFuncs(==)
strOpFuncs(!=)
strOpFuncs(<=)
strOpFuncs(<)
strOpFuncs(>=)
strOpFuncs(>)
avOpFuncs(==)
avOpFuncs(!=)
avOpFuncs(<=)
avOpFuncs(<)
avOpFuncs(>=)
avOpFuncs(>)

/*                         IntensionValue::operator cast()
**
**   The cast operators return the Tuple or Tuple data associated with
** the IntensionValue.
**
** OUTCOMES:
**    1. When tuple is NULL
**         get a new Tuple
**    2. return the tuple data
*/
define(IVcastFunc,
IntensionValue::operator $1 *()
    {
    Trace(1,"Entering IntensionValue::operator $1 *()")
    if (!tuple)
       tuple = Tuple_new(intension.tuple_size);
    Trace(1,"Returning from IntensionValue::operator $1 *()")
    return $2;
    }
)
IVcastFunc(Tuple, tuple)
IVcastFunc(const void, tuple->data)
IVcastFunc(const char,`intension.tuple2line(tuple," ",buffer,FALSE,""), buffer')

/*                         IntensionValue::operator[]()
**
**   The project operator returns the AttributeValue for the
** given Attribute.  It returns the existing AttributeValue if
** the Attribute is previously referenced, or constructs a new
** one on the first reference.
**
** OUTCOMES:
**    1. When Attribute is not in the intension
**         R_NO_ATTRIBUTE.
**    2. Otherwise
**         return the AttributeValue for the Attribute.
*/
AttributeValue & IntensionValue::operator[](Attribute &a)
    {
    Trace(1,"Entering IntensionValue::operator[](Attribute)")
    Degree_t attrIndex = intension.index(a.aname);
    if ( attrIndex == NULLINDEX )
       relerr.error(R_NO_ATTRIBUTE,__FILE__,__LINE__,a.aname.name);
    if ( !avs[attrIndex] )
       avs[attrIndex] = new AttributeValue(this,attrIndex);
    Trace(1,"Returning from IntensionValue::operator[](Attribute)")
    return *(avs[attrIndex]);
    }

/*                         AttributeValue::AttributeValue()
**
** OUTCOMES:
**    void
*/
AttributeValue::AttributeValue(IntensionValue *ivp, Degree_t attrIndex)
                  : iv(ivp), index(attrIndex),
                    attrDomain(ivp->intension.attr_info[attrIndex].a->domain),
                    attrName(ivp->intension.attr_info[attrIndex].a->aname.name),
                    attrOffset(ivp->intension.attr_info[attrIndex].offset)
{
}
