#ident "@(#) /sable/sdb/ra/rel/relation/s.formRel.C"
/*      Copyright (c) 1989, 1990, 1991 AT&T - All Rights Reserved */

#include <relation.h>

const int LSTR_FLOAT = 20;
const int LSTR_INT = 10;

Form_Relation::Form_Relation(Intension &i,char *h,WINDOW *w) : Relation (i)
{
struct field *fields = new struct field[i.degree];
for ( int x = 0; x < i.degree; x++ )
   {
   fields[x].caption = i.attr_info[x].a->aname.name;
   switch(i.attr_info[x].a->domain.type)
      {         /* STRING substracts one from length for final NULL byte */
   case STRING: fields[x].length = i.attr_info[x].a->domain.length-1; break;
   case FLOAT: fields[x].length = LSTR_FLOAT; break;
   case INT: fields[x].length = LSTR_INT; break;
      }
   }
form = new Form(fields,i.degree,h,TABLE,w);
current_input = FALSE;
}

Form_Relation::Form_Relation(Attribute &a,char *h,WINDOW *w) : Relation (a)
{
struct field *fields = new struct field;
fields->caption = a.aname.name;
switch(a.domain.type)
   {
case STRING: fields->length = a.domain.length; break;
case FLOAT: fields->length = LSTR_FLOAT; break;
case INT: fields->length = LSTR_INT; break;
   }
form = new Form(fields,1,h,TABLE,w);
current_input = FALSE;
}

void Form_Relation::input()
{
Tuple *t;
row=0;
while ( form->input(row) && (t=form2tuple()) )
   {
   this->Relation::operator+=(t);
   row += ((row%4)==2)?2:1;
   if ( row >= form->capacity() )
      row = 0;
   }
current_input = TRUE;
row=0;
}

Tuple *Form_Relation::form2tuple()
{
int nerrors=0;
char *cp=(char *)0;
Boolean_t valid=FALSE;
Tuple *rc = Tuple_new(intension.tuple_size);
union { char *s; Float_t *f; Int_t *i; } ip;
for ( int i=0; i < degree(); i++ )
   {
   ip.s = (char *)(rc->data) + intension.attr_info[i].offset;
   const Domain *domain = &(intension.attr_info[i].a->domain);
   nerrors=0;
   do {
      valid = TRUE;
      if ( nerrors++ >= 3 )
         { formerr.error(F_INVALID_FIELD,__FILE__,__LINE__); abort(); }
      switch(domain->type)
         {
      case FLOAT:
         *(ip.f) = (Float_t) strtod(form->fields[i].data,&cp);
         if ( (cp==form->fields[i].data) ||
              !domain->test_constraint((void *)ip.f,domain->constraint) )
            valid = FALSE;
          break;
      case INT:
         *(ip.i) = (Int_t) strtol(form->fields[i].data,&cp,10);
         if ( (cp==form->fields[i].data) ||
              !domain->test_constraint((void *)ip.i,domain->constraint) )
            valid = FALSE;
          break;
      case STRING:
         strncpy(ip.s,form->fields[i].data,domain->length);
         if ( !domain->test_constraint((void *)ip.s,domain->constraint) )
            valid = FALSE;
         }
      if ( !valid )
         {
         char *errstring = domain->constraint_string();
         form->error(errstring);
         delete errstring;
         if ( !form->reread(i,row) )
            { rc->done(); return (Tuple *)0; }
         }
      }
   while ( !valid );
   }
rc->flags |= T_CONSTRAINED;
return rc;
}

void Form_Relation::tuple2form(Tuple *t)
{
union { char *s; Float_t *f; Int_t *i; } ip;
for ( int i=0; i < degree(); i++ )
   {
   ip.s = (char *)(t->data) + intension.attr_info[i].offset;
   switch(intension.attr_info[i].a->domain.type)
      {
   case FLOAT:
      sprintf(form->fields[i].data,"%*-f",LSTR_FLOAT,(float)*(ip.f)); break;
   case INT:
      sprintf(form->fields[i].data,"%*-i",LSTR_INT,(int)*(ip.i)); break;
   case STRING:
      strncpy(form->fields[i].data,ip.s,
           intension.attr_info[i].a->domain.length);
      }
   }
return;
}

Boolean_t Form_Relation::operator=(Relation &r)
{
int page=0;
row=0;
Tuple *t=(Tuple *)0;
if ( intension != r.intension )
   return relerr.error(R_BAD_ASSIGNMENT,__FILE__,__LINE__);
extension.truncate();
r.startwalk();
do {
   for ( row=0; (row<form->capacity())&&(t=r.walk()); row += ((row%4)==2)?2:1 )
      {
      tuple2form(t);
      form->display(row);
      }
   if ( row == 0 ) /* nothing was displayed */
      {
      if ( page == 0 )
         {
         beep();
         form->prompt("No records to display.  Press any key to return. ");
         }
      }
   else if ( toupper(form->prompt("Continue[y/n]? ")) != 'Y' )
      break;
   page++;
   }
while ( t );
r.endwalk();
row=0;
return TRUE;
}
Predicate * Form_Relation::criteria()
{
Predicate *rc = (Predicate *)0, *eqpred = (Predicate *)0;
char *cp=(char *)0;
Boolean_t valid=FALSE;
typedef Pattern *PATTERN_P;
int i=0;
Float_t fval;
Int_t ival;
form->message("Please enter search fields, if any.");
if ( form->input() )
   {
   form->message();
   for ( i=0; i < degree(); i++ )
      {
      if ( form->fields[i].data[0] )
         {
         const Domain *domain = &(intension.attr_info[i].a->domain);
         do {
         valid = TRUE;
         switch(domain->type)
            {
         case FLOAT:
            fval = (Float_t) strtod(form->fields[i].data,&cp);
            if ( (cp==form->fields[i].data) ||
                 !domain->test_constraint((void *)&fval,domain->constraint) )
               valid = FALSE;
             else eqpred = &(*(intension.attr_info[i].a) == fval);
             break;
         case INT:
            ival = (Int_t) strtol(form->fields[i].data,&cp,10);
            if ( (cp==form->fields[i].data) ||
                 !domain->test_constraint((void *)&ival,domain->constraint) )
               valid = FALSE;
            else eqpred = &(*(intension.attr_info[i].a) == ival);
            break;
         case STRING:
            Pattern *pval = new Pattern(form->fields[i].data);
            eqpred = &(*(intension.attr_info[i].a) == *pval);
                 /* no place to deallocate - this won't get garbage collected */
            }
         if ( !valid )
            {
            char *errstring = domain->constraint_string();
            form->error(errstring);
            delete errstring;
            form->reread(i,row);  /* test_constraint will print message */
            }
         else if ( rc )
            rc = &(*rc && *eqpred);
         else rc = eqpred;
            }
         while ( !valid );
         }
      }
   }
return rc;
}

Relation &Form_Relation::filter(Relation &r,char *prompt_string)
{
Relation *out = new Relation(intension), &Out = *out;
Out.usage = RVALUE;
if ( r.intension != intension )
   return Out;
Usage l_usage = usage, r_usage = r.usage;
usage = r.usage = LVALUE;
Tuple *t = (Tuple *)0;
r.startwalk();
while ( t = r.walk() )
   {
   tuple2form(t);
   form->display();
   char answer = toupper(form->prompt(prompt_string));
   if ( answer == 'Y' )
      Out += t;
   else if ( answer == 'Q' )
      break;
   /* else NO */
   }
r.endwalk();
usage = l_usage; r.usage = r_usage;
return Out;
}

Form_Relation::~Form_Relation()
{
struct field *fptr = form->fields;
delete form;
delete fptr;
}

int Form_Relation::cardinality()
{
if ( current_input )
   return extension.cardinality();
input();
return extension.cardinality();
}

void Form_Relation::startwalk()
{
if ( !current_input )
   input();
Relation::startwalk();
}

void Form_Relation::startwalk(Predicate &p)
{
if ( !current_input )
   input();
Relation::startwalk(p);
}

void Form_Relation::endwalk()
{
Relation::endwalk();
extension.truncate();
current_input = FALSE;
}

Boolean_t Form_Relation::operator=(Tuple *t)
{
tuple2form(t);
form->display();
form->prompt();
return TRUE;
}

Tuple *const Form_Relation::update(Tuple *t)
{
row=0;
tuple2form(t);
if ( form->update(0,intension.key_degree) )
   return form2tuple();
else return (Tuple *)0;
}
Boolean_t Form_Relation::operator+=(Tuple *t)
{
(void) t;
return relerr.error(R_INVALID_OPERATION,__FILE__,__LINE__);
}
Boolean_t Form_Relation::operator+=(Relation &r)
{
r.destroy_rvalue();
return relerr.error(R_INVALID_OPERATION,__FILE__,__LINE__);
}
Boolean_t Form_Relation::operator-=(Relation &r)
{
r.destroy_rvalue();
return relerr.error(R_INVALID_OPERATION,__FILE__,__LINE__);
}
