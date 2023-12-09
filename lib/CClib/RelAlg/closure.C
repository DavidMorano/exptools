#ident "@(#) /sable/sdb/ra/rel/relation/s.closure.C"
/*      Copyright (c) 1989,1991 AT&T - All Rights Reserved */

#include <relation.h>
#define MAXJOINS 26
Relation & Relation::operator*(Intension &i)      // transitive closure
{
Usage l_usage = usage; usage = LVALUE;
int x=0,li=0,ri=0;
Intension *o_int = new Intension, &O_int = *o_int;
Intension *l_int = new Intension, &L_int = *l_int;
Intension *r_int = new Intension, &R_int = *r_int;
Attribute *nattrs[MAXJOINS];
O_int.use(); L_int.use(); R_int.use();
char *join_name = "__joinA";
for ( x=0; x < i.degree; x++,join_name[6]++ )
   {
   if ( x == MAXJOINS ) 
      {
      relerr.error(R_CLOSURE_TOO_BIG,__FILE__,__LINE__);
      return *this;
      }
   if ( (li = intension.index(i.attr_info[x].a->aname)) == NULLINDEX )
      {
      relerr.error(R_NO_ATTRIBUTE,__FILE__,__LINE__,
         i.attr_info[x].a->aname.name);
      return *this;
      }
   if ( (ri = intension.index(*i.attr_info[x].old_nm)) == NULLINDEX )
      {
      relerr.error(R_NO_ATTRIBUTE,__FILE__,__LINE__,
         i.attr_info[x].old_nm->name);
      return *this;
      }
   (void)(O_int / *intension.attr_info[li].a / *intension.attr_info[ri].a);
   nattrs[x] = new Attribute(join_name,intension.attr_info[li].a->domain);
   (void)(L_int / *nattrs[x] / *intension.attr_info[ri].a);
   L_int.attr_info[2*x].old_nm = &(i.attr_info[x].a->aname);
   (void)(R_int / *intension.attr_info[li].a / *nattrs[x]);
   R_int.attr_info[2*x+1].old_nm = i.attr_info[x].old_nm;
   }
Relation *result = new Relation(O_int);
Relation &Result = *result;
Relation Outnew(O_int);
Relation Orig(O_int);

Orig = (*this)[O_int];
Outnew = Orig;
Result = Orig;
x=0;
while (Result.cardinality()>x)
   {
   x = Result.cardinality();
   Outnew = (Outnew[L_int]&Orig[R_int])[O_int];
   Result += Outnew; 
   }
delete l_int;
delete r_int;
for ( x=0; x < i.degree; x++ ) delete nattrs[x];
usage = l_usage;
destroy_rvalue();
i.done();
O_int.done();           // only remaining reference is Result
Result.usage = RVALUE;  // change it from Relation to expression
return Result;
}
