#ident "@(#) /sable/sdb/ra/rel/domain/s.domain.C"
/*      Copyright (c) 1989,1991 AT&T - All Rights Reserved */

#include <relation.h>

Sized_string Domain::build_constraint_string(const Constraint *const c) const
{
Sized_string str,lstr,rstr;
int orig=0;
if ( !c )
   { str.length=1; str.string=new char[1]; str.string[0]='\0'; return str; }
switch(c->op)
   {
case AND:
   lstr = build_constraint_string(c->left);
   rstr = build_constraint_string(c->right.c);
   str.length = lstr.length+rstr.length+6; str.string = new char[str.length];
   sprintf(str.string,"%s and %s",lstr.string,rstr.string);
   delete lstr.string; delete rstr.string; return str;
case OR:
   lstr = build_constraint_string(c->left);
   rstr = build_constraint_string(c->right.c);
   str.length = lstr.length+rstr.length+5; str.string = new char[str.length];
   sprintf(str.string,"%s or %s",lstr.string,rstr.string);
   delete lstr.string; delete rstr.string; return str;
case NOT:
   rstr = build_constraint_string(c->right.c);
   str.length = rstr.length+5; str.string = new char[str.length];
   sprintf(str.string,"not %s",rstr.string);
   delete rstr.string; return str;
default:
   switch(type)
      {
   case INT: // a maximum string length of 20 should be enough for a long
      orig = rstr.length = 20;
      rstr.string = new char[orig]; 
      rstr.length = sprintf(rstr.string,"%li",(long)c->right.i);
      break;
   case FLOAT: // a maximum string length of 20 should be enough for a double
      orig = rstr.length = 20;
      rstr.string = new char[orig]; 
      rstr.length = sprintf(rstr.string,"%lf",(double)c->right.f);
      break;
   case STRING:
      orig = rstr.length = strlen(c->right.s)+1;
      rstr.string = new char[orig];
      rstr.length = sprintf(rstr.string, "%s", c->right.s);
      break;
   default: syserr.error(UNEXPECTED_ERROR,__FILE__,__LINE__); abort();
      }
   if ( rstr.length > orig ) 
      { syserr.error(UNEXPECTED_ERROR, __FILE__, __LINE__); abort(); }
   switch(c->op)
      {
   case EQ:  // strlen("equal to ") + 1 = 10
      str.length = rstr.length+10; str.string = new char[str.length];
      sprintf(str.string, "equal to %s", rstr.string); break;
   case NE:  // strlen("not equal to ") + 1 = 14
      str.length = rstr.length+14; str.string = new char[str.length];
      sprintf(str.string,"not equal to %s",rstr.string); break;
   case LE:  // strlen("less than or equal to ") + 1 = 23
      str.length = rstr.length+23; str.string = new char[str.length];
      sprintf(str.string,"less than or equal to %s",rstr.string); break;
   case GE:  // strlen("greater than or equal to ") + 1 = 26
      str.length = rstr.length+26; str.string = new char[str.length];
      sprintf(str.string,"greater than or equal to %s",rstr.string); break;
   case GT:  // strlen("greater than ") + 1 = 14
      str.length = rstr.length+14; str.string = new char[str.length];
      sprintf(str.string,"greater than %s",rstr.string); break;
   case LT:  // strlen("less than ") + 1 = 11
      str.length = rstr.length+11; str.string = new char[str.length];
      sprintf(str.string,"less than %s",rstr.string); break;
   case MATCH:  // strlen("of pattern ") + 1 = 12
      str.length = strlen(c->right.r->pattern_string())+12;
      str.string = new char[str.length];
      sprintf(str.string,"of pattern %s",c->right.r->pattern_string()); break;
   case NOMATCH:  // strlen("not of pattern ") + 1 = 16
      str.length = strlen(c->right.r->pattern_string())+16;
      str.string = new char[str.length];
      sprintf(str.string,"not of pattern %s",c->right.r->pattern_string());
      break;
   default: syserr.error(UNEXPECTED_ERROR,__FILE__,__LINE__); abort();
      }
   delete rstr.string; return str;
   }
/* return should never be executed and is here to remove a compiler warning */
syserr.error(UNEXPECTED_ERROR,__FILE__,__LINE__); abort(); return str;
}

Boolean_t Domain::test_constraint(const void *v,const Constraint *const c) const
{
int result;
union { Int_t *i; Float_t *f; char *s; Pattern *r; void *v; } left;
if ( !c ) return TRUE;
left.v = v;
switch(c->op)
   {
case AND:
   if ( test_constraint(v,c->left) ) return test_constraint(v,c->right.c);
   else return FALSE;
case OR:
   if ( test_constraint(v,c->left) ) return TRUE;
   else return test_constraint(v,c->right.c);
case NOT:
   if ( test_constraint(v,c->right.c) ) return FALSE; else return TRUE;
default:
   switch(type)
      {
   case INT: if (*(left.i) == c->right.i)     result = 0;
               else if (*(left.i) > c->right.i) result = 1;
               else                             result = -1; break;
   case FLOAT: if (*(left.f) == c->right.f)     result = 0;
               else if (*(left.f) > c->right.f) result = 1;
               else                             result = -1; break;
   case STRING: result = strncmp(left.s,c->right.s,length); break;
   default: syserr.error(UNEXPECTED_ERROR,__FILE__,__LINE__); abort();
      }
   }
switch(c->op)
   {
case EQ: if ( result == 0 ) return TRUE; else return FALSE;
case NE: if ( result != 0 ) return TRUE; else return FALSE;
case LE: if ( result <= 0 ) return TRUE; else return FALSE;
case GE: if ( result >= 0 ) return TRUE; else return FALSE;
case GT: if ( result > 0 ) return TRUE; else return FALSE;
case LT: if ( result < 0 ) return TRUE; else return FALSE;
case MATCH: if ( c->right.r->match(left.s) ) return TRUE; else return FALSE;
case NOMATCH: if ( c->right.r->match(left.s) ) return FALSE; else return TRUE;
default: syserr.error(UNEXPECTED_ERROR,__FILE__,__LINE__); abort();
   }
/* return should never be executed and is here to remove a compiler warning */
syserr.error(UNEXPECTED_ERROR,__FILE__,__LINE__); abort(); return FALSE;
}

ostream & operator<<(ostream &s,const Domain &d)
{
s << " dname: " << d.name << " type: "
        << chr(d.type) << " length: " << d.length << "\n";
return s;
}

Boolean_t Domain::operator==(const Domain &d) const
{
return ((name==d.name)&&(type==d.type)&&(length==d.length))?TRUE:FALSE;
}

Boolean_t Domain::operator!=(const Domain &d) const
{
return ((name==d.name)&&(type==d.type)&&(length==d.length))?FALSE:TRUE;
}

Domain::Domain(const char *const n,const Dtype t,const Dlength l)
       : type(t),length(t==STRING?l:(t==INT?sizeof(Int_t):sizeof(Float_t)))
{
if ( !length  || (l != length) ) 
   { relerr.error(R_INVALID_LENGTH,__FILE__,__LINE__); abort(); }
name = n;
constraint = (Constraint *)0;
}

Domain::~Domain()
{
if ( constraint ) delete constraint;
}

char * Domain::constraint_string() const
{
Sized_string substring = build_constraint_string(constraint);
/* strlen(" must be a  ") + strlen("character string ") + 1 = 30 */
char *string = new char[substring.length+LNAME+30];
sprintf(string,"%s must be a %s %s",name.name,
   (type==FLOAT)
      ? "decimal number"
      : ((type==INT)
         ? "whole number"
         : "character string"),
  substring.string);
delete substring.string;
return string;
}

Boolean_t Domain::constrain(const char *s, Boolean_t print) const
{
if ( type != STRING ) 
   { relerr.error(R_NOT_STRING_DOMAIN,__FILE__,__LINE__); return FALSE; }
else if (constraint)
   {
   if ( !s ) s = EMPTY_STRING;
   if ( (strlen(s)<length) && test_constraint((const void *)s,constraint) )
      return TRUE;
   else if (print)
      {
      char *cs = constraint_string();
      relerr.error(R_CONSTRAINT_FAILED,__FILE__,__LINE__,cs);
      delete cs;
      return FALSE;
      }
   else return FALSE;
   }
else return TRUE;
}

Boolean_t Domain::constrain(const Int_t i, Boolean_t print) const
{
if ( type != INT ) 
   { relerr.error(R_NOT_INT_DOMAIN,__FILE__,__LINE__); return FALSE; }
else if (constraint)
   if ( test_constraint((const void *)&i,constraint) )
      return TRUE;
   else if (print)
      {
      char *cs = constraint_string();
      relerr.error(R_CONSTRAINT_FAILED,__FILE__,__LINE__,cs);
      delete cs;
      return FALSE;
      }
   else return FALSE;
else return TRUE;
}

Boolean_t Domain::constrain(const Float_t f, Boolean_t print) const
{
if ( type != FLOAT ) 
   { relerr.error(R_NOT_FLOAT_DOMAIN,__FILE__,__LINE__); return FALSE; }
else if (constraint)
   if ( test_constraint((const void *)&f,constraint) )
      return TRUE;
   else if (print)
      {
      char *cs = constraint_string();
      relerr.error(R_CONSTRAINT_FAILED,__FILE__,__LINE__,cs);
      delete cs;
      return FALSE;
      }
   else return FALSE;
else return TRUE;
}

Constraint & Domain::operator==(const Int_t i)
{
if ( type != INT ) 
   { relerr.error(R_NOT_INT_DOMAIN,__FILE__,__LINE__); abort(); }
Constraint &p = *(Constraint *)new Constraint(EQ,this,i); return p;
}

Constraint & Domain::operator!=(const Int_t i)
{
if ( type != INT ) 
   { relerr.error(R_NOT_INT_DOMAIN,__FILE__,__LINE__); abort(); }
Constraint &p = *(Constraint *)new Constraint(NE,this,i); return p;
}

Constraint & Domain::operator<=(const Int_t i)
{
if ( type != INT ) 
   { relerr.error(R_NOT_INT_DOMAIN,__FILE__,__LINE__); abort(); }
Constraint &p = *(Constraint *)new Constraint(LE,this,i); return p;
}

Constraint & Domain::operator>=(const Int_t i)
{
if ( type != INT ) 
   { relerr.error(R_NOT_INT_DOMAIN,__FILE__,__LINE__); abort(); }
Constraint &p = *(Constraint *)new Constraint(GE,this,i); return p;
}

Constraint & Domain::operator<(const Int_t i)
{
if ( type != INT ) 
   { relerr.error(R_NOT_INT_DOMAIN,__FILE__,__LINE__); abort(); }
Constraint &p = *(Constraint *)new Constraint(LT,this,i); return p;
}

Constraint & Domain::operator>(const Int_t i)
{
if ( type != INT ) 
   { relerr.error(R_NOT_INT_DOMAIN,__FILE__,__LINE__); abort(); }
Constraint &p = *(Constraint *)new Constraint(GT,this,i); return p;
}

Constraint & Domain::operator==(const Float_t f)
{
if ( type != FLOAT ) 
   { relerr.error(R_NOT_FLOAT_DOMAIN,__FILE__,__LINE__); abort(); }
Constraint &p = *(Constraint *)new Constraint(EQ,this,f); return p;
}

Constraint & Domain::operator!=(const Float_t f)
{
if ( type != FLOAT ) 
   { relerr.error(R_NOT_FLOAT_DOMAIN,__FILE__,__LINE__); abort(); }
Constraint &p = *(Constraint *)new Constraint(NE,this,f); return p;
}

Constraint & Domain::operator<=(const Float_t f)
{
if ( type != FLOAT ) 
   { relerr.error(R_NOT_FLOAT_DOMAIN,__FILE__,__LINE__); abort(); }
Constraint &p = *(Constraint *)new Constraint(LE,this,f); return p;
}

Constraint & Domain::operator>=(const Float_t f)
{
if ( type != FLOAT ) 
   { relerr.error(R_NOT_FLOAT_DOMAIN,__FILE__,__LINE__); abort(); }
Constraint &p = *(Constraint *)new Constraint(GE,this,f); return p;
}

Constraint & Domain::operator<(const Float_t f)
{
if ( type != FLOAT ) 
   { relerr.error(R_NOT_FLOAT_DOMAIN,__FILE__,__LINE__); abort(); }
Constraint &p = *(Constraint *)new Constraint(LT,this,f); return p;
}

Constraint & Domain::operator>(const Float_t f)
{
if ( type != FLOAT ) 
   { relerr.error(R_NOT_FLOAT_DOMAIN,__FILE__,__LINE__); abort(); }
Constraint &p = *(Constraint *)new Constraint(GT,this,f); return p;
}

Constraint & Domain::operator==(const char *s)
{
if ( type != STRING ) 
   { relerr.error(R_NOT_STRING_DOMAIN,__FILE__,__LINE__); abort(); }
Constraint &p = *(Constraint *)new Constraint(EQ,this,s); return p;
}

Constraint & Domain::operator!=(const char *s)
{
if ( type != STRING ) 
   { relerr.error(R_NOT_STRING_DOMAIN,__FILE__,__LINE__); abort(); }
Constraint &p = *(Constraint *)new Constraint(NE,this,s); return p;
}

Constraint & Domain::operator<=(const char *s)
{
if ( type != STRING ) 
   { relerr.error(R_NOT_STRING_DOMAIN,__FILE__,__LINE__); abort(); }
Constraint &p = *(Constraint *)new Constraint(LE,this,s); return p;
}

Constraint & Domain::operator>=(const char *s)
{
if ( type != STRING ) 
   { relerr.error(R_NOT_STRING_DOMAIN,__FILE__,__LINE__); abort(); }
Constraint &p = *(Constraint *)new Constraint(GE,this,s); return p;
}

Constraint & Domain::operator<(const char *s)
{
if ( type != STRING ) 
   { relerr.error(R_NOT_STRING_DOMAIN,__FILE__,__LINE__); abort(); }
Constraint &p = *(Constraint *)new Constraint(LT,this,s); return p;
}

Constraint & Domain::operator>(const char *s)
{
if ( type != STRING ) 
   { relerr.error(R_NOT_STRING_DOMAIN,__FILE__,__LINE__); abort(); }
Constraint &p = *(Constraint *)new Constraint(GT,this,s); return p;
}

Constraint & Domain::operator==(const Pattern &r)
{
if ( type != STRING ) 
   { relerr.error(R_NOT_STRING_DOMAIN,__FILE__,__LINE__); abort(); }
Constraint &p = *(Constraint *)new Constraint(MATCH,this,&r); return p;
}

Constraint & Domain::operator!=(const Pattern &r)
{
if ( type != STRING ) 
   { relerr.error(R_NOT_STRING_DOMAIN,__FILE__,__LINE__); abort(); }
Constraint &p = *(Constraint *)new Constraint(NOMATCH,this,&r); return p;
}

