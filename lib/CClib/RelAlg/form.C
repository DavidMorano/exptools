#ident "@(#) /sable/sdb/ra/sblib/form/s.form.C"
/*       Copyright (c) 1989, 1990, 1991 AT&T - All Rights Reserved */

#include <sblib.h>

const int NFORMERR=5;
static Error_message form_errors[NFORMERR] = {
{/* 0 */
 "CANT_SUBWIN", MM_SOFT|MM_UTIL, MM_HALT,
 "Unable to create subwindow",
 "PROGRAMMER: probably dynamic allocation failure" },
{/* 1 */
 "GETCH_ERROR", MM_SOFT|MM_UTIL, MM_ERROR,
 "Error occurred while reading input through curses" },
{/* 2 */
 "INVALID_FIELD", MM_SOFT|MM_UTIL, MM_ERROR,
 "Field number out of range",
 "PROGRAMMER: Make sure field number specified is between 0 and nitems-1" },
{/* 3 */
 "TOO_FEW_COLUMNS", MM_SOFT|MM_UTIL, MM_HALT,
 "Not enough columns in window to print form in RECORD format",
 "PROGRAMMER: Create wider window or shorten length of longest field/caption"},
{/* 4 */
 "WINDOW_TOO_SMALL", MM_SOFT|MM_UTIL, MM_HALT,
 "Not enough rows and/or columns in window to produce form with its overhead",
 "PROGRAMMER: Create a larger window or split into multiple forms" }
   };
Error formerr(form_errors,NFORMERR);

void Form::edit_file(WINDOW *basewin, char *filename) const
{
int fd = -1;
struct stat statBuf;
if ( ((fd = open(filename,O_RDONLY)) == -1)
   || (fstat(fd,&statBuf) == -1)  ) 
   {
   error(form("Not able to edit %s.",filename) );
   beep();
   return;
   }
close(fd);
clear_labels();
endwin();
switch(fork())
   {
CHILD:
   close(2);
   fcntl(0,F_DUPFD,2); /* must change stderr back to terminal */
   if ( (statBuf.st_mode&S_IFMT) == S_IFDIR )
      {
      chdir(filename);
      fprintf(stderr,
         "Starting shell in %s.  Type 'exit<RETURN>' to return to mlServer\n",
         filename);
      fflush(stderr);
      execl("/bin/sh","/bin/sh","-pi",0);
      syserr.error(errno,__FILE__,__LINE__, "'/bin/sh' did not execute.");
      }
   else
      {
      execl("/usr/bin/vi","/usr/bin/vi",filename,0);
      syserr.error(errno,__FILE__,__LINE__,
           form("'/usr/bin/vi %s' did not execute.",filename) );
      }
   exit(errno);
PARENT: 
   do errno=0; /* we don't care about exit status */
   while ( (wait((int *)0)==-1) && (errno==EINTR) );
   init_screen(); 
   touchwin(basewin); message(); set_labels(); wrefresh(basewin); break;
FORKERR:
   init_screen(); 
   touchwin(basewin); message();
   error("form.C:  Fork failed."); set_labels(); wrefresh(basewin); break;
   }
}

Form::Form(struct field *fieldlist,unsigned ni,char *heading,FORMTYPE type,
   WINDOW *b) : nitems(ni),fields(fieldlist),
                base(b?b:newwin(NUMROWS(stdscr),NUMCOLS(stdscr),0,0))
{
unsigned column=0, lcaption=0;
int largest=0,sum=0,i=0;
char *dashes=0;
int *maxlengths = new int[nitems?nitems:1];
struct field *fptr=0;
if ( !fieldlist || !ni )
   { syserr.error(NULL_POINTER,__FILE__,__LINE__); abort(); }
if ( !base )
   { syserr.error(NULL_POINTER,__FILE__,__LINE__); abort(); }
typedef WINDOW *PWINDOW;
subwindows = new PWINDOW[nitems?nitems:1];
touchwin(base); werase(base);
int total_rows = NUMROWS(base) - 3;        /* minus errwin, msgwin */
int total_columns = NUMCOLS(base);

if (!(msgwin=subwin(base,1,total_columns,BOTTOMROW(base),LEFTCOL(base))) )
   { formerr.error(F_CANT_SUBWIN,__FILE__,__LINE__); abort(); }
if (!(errwin=subwin(base,2,total_columns,TOPROW(base),LEFTCOL(base))) )
   { formerr.error(F_CANT_SUBWIN,__FILE__,__LINE__); abort(); }

/* Print the header if one is supplied */
int row = 2;
if (heading)
   {
   mvwprintw(base,row,(total_columns-strlen(heading))/2,"%s",heading);
   row += 2;
   total_rows -= 2;
   }

/* Find out if all fields will fit on one line.  */
for (i=0,fptr=fields; i<nitems; i++,fptr++)
   {
   maxlengths[i] = MAX(fptr->length, strlen(fptr->caption));
   sum += maxlengths[i] + 1;
   largest=MAX(largest,maxlengths[i]);
   }                /* Last field does need blank space, don't decrement sum */

/* dashes underlining a TABLE or indicating field length on a RECORD */
dashes = new char[largest+1];
(void) memset(dashes,'-',(int) largest);

/* Format as a TABLE if possible */
if ((sum <= total_columns) && (type == TABLE))
   {
   /* Two rows for captions */
   total_rows -= 2;
   if (total_rows < 1)
      { formerr.error(F_WINDOW_TOO_SMALL,__FILE__,__LINE__); abort(); }

   /* Center the table */
   column = ( total_columns - sum ) / 2;

   for (i=0,fptr=fields; i<nitems; i++,fptr++)
      {
      /*  set up caption */
      mvwprintw(base,row,column,"%-s ",fptr->caption);
      dashes[maxlengths[i]] = '\0';
      mvwprintw(base,row+1,column,"%s ",dashes);
      dashes[maxlengths[i]] = '-';

      /*  set up subwindow */
      if ( !(subwindows[i] = subwin(base,total_rows,fptr->length+1,
              row+2+TOPROW(base), column+LEFTCOL(base))) )
         { formerr.error(F_CANT_SUBWIN,__FILE__,__LINE__); abort(); }

      /* set up data area */
      fptr->data = new char[fptr->length+1];
      column += maxlengths[i]+1;
      }

   delete dashes;
   delete maxlengths;
   _capacity = total_rows;
   return;
   }

largest = 0;
for (i=0,fptr=fields; i<nitems; i++,fptr++)
   {
   lcaption = strlen(fptr->caption);
   if ((lcaption + 4 + fptr->length) > total_columns)
      { formerr.error(F_TOO_FEW_COLUMNS,__FILE__,__LINE__); abort(); }
   largest = MAX(largest,lcaption);
   }

if (nitems < total_rows/2)     /* Can fit one entry per line */
   {
   for (i=0,fptr=fields; i<nitems; i++,fptr++)
      {
      mvwprintw(base,row,column," %*s: ",largest,fptr->caption);
      if ( !(subwindows[i] = subwin(base,1,fptr->length+1,
             row+TOPROW(base),largest + column + 3 +LEFTCOL(base))) )
         { formerr.error(F_CANT_SUBWIN,__FILE__,__LINE__); abort(); }
      fptr->data = new char[fptr->length+1];
      row += 2;
      }
   delete dashes;
   delete maxlengths;
   _capacity = 1;
   return;
   }

/* last chance - get it on there any old way */
column = 0;
for ( i=0,fptr=fields; i<nitems; i++,fptr++ )
   {
   lcaption = strlen(fptr->caption);
   if ((column+fptr->length+lcaption+4) >= total_columns)
      {
      row += 1; /* single space to cram in more */
      column = 0;
      }
   if ( row >= total_rows-1 )
      { formerr.error(F_WINDOW_TOO_SMALL,__FILE__,__LINE__); abort(); }
   mvwprintw(base,row,column," %s: ",fptr->caption);
   column += lcaption + 3;
   if ( !(subwindows[i] = subwin(base,1,fptr->length+1,
         row+TOPROW(base),column+LEFTCOL(base))) )
      { formerr.error(F_CANT_SUBWIN,__FILE__,__LINE__); abort(); }
   fptr->data = new char[fptr->length+1];
   column += fptr->length + 1;
   }
delete dashes;
delete maxlengths;
_capacity = 1;
return;
}

Form::~Form()
{
int i=0;
struct field *fptr=0;
if ( msgwin )
   delwin(msgwin);
else syserr.error(UNEXPECTED_ERROR,__FILE__,__LINE__);
if ( errwin )
   delwin(errwin);
else syserr.error(UNEXPECTED_ERROR,__FILE__,__LINE__);
if ( !subwindows )
   syserr.error(UNEXPECTED_ERROR,__FILE__,__LINE__);
for (i=0,fptr=fields; i<nitems; i++,fptr++)
   {
   if ( subwindows[i] )
      delwin(subwindows[i]);
   else syserr.error(UNEXPECTED_ERROR,__FILE__,__LINE__);
   if ( fptr->data )
      delete fptr->data;
   else syserr.error(UNEXPECTED_ERROR,__FILE__,__LINE__);
   }
delete subwindows;
werase(base);
}

void Form::display(unsigned row) const
{
struct field *fptr=0;
int i=0;
if ( row >= _capacity )
   { formerr.error(F_WINDOW_TOO_SMALL,__FILE__,__LINE__); abort(); }
for (i=0,fptr=fields; i<nitems; i++,fptr++)
   {
   if ( !fptr->data || !subwindows || !subwindows[i] )
      { syserr.error(UNEXPECTED_ERROR,__FILE__,__LINE__); abort(); }
   if (wmove(subwindows[i],row,0) == ERR)
      { syserr.error(UNEXPECTED_ERROR,__FILE__,__LINE__); abort(); }
   wclrtoeol(subwindows[i]);
   wprintw(subwindows[i],"%-s",fptr->data);
   }
frefresh();
}

Boolean_t Form::input(unsigned row) const
{
struct field *fptr=0;
int i=0, rc=0;
char data[512]; data[0] = '\0';
if ( row >= _capacity )
   { formerr.error(F_WINDOW_TOO_SMALL,__FILE__,__LINE__); abort(); }
set_labels();
for (i=0,fptr=fields; i<nitems; i++,fptr++)
   {
   if ( !fptr->data || !subwindows || !subwindows[i] )
      { syserr.error(UNEXPECTED_ERROR,__FILE__,__LINE__); abort(); }
   fptr->data[0] = '\0';
   if (wmove(subwindows[i],row,0) == ERR)
      { syserr.error(UNEXPECTED_ERROR,__FILE__,__LINE__); abort(); }
   wclrtoeol(subwindows[i]);
   }
touchwin(base); wnoutrefresh(base);
for (i=0,fptr=&fields[i]; i<nitems; i++,fptr++)
   {
   wnoutrefresh(subwindows[i]);
   rc = wgets(data,fptr->length+1,subwindows[i]);
   if ( data[0] )
      (void) strcpy(fptr->data,data);
   else
      {
      wmove(subwindows[i],row,0);
      wprintw(subwindows[i],"%-s",fptr->data);
      wnoutrefresh(subwindows[i]);
      }
   switch(rc)
      {
   CASE_QUIT: case -1: clear_labels(); return FALSE;
   CASE_SAVE: clear_labels(); return TRUE;
   CASE_PREVIOUS:
      if ( i ) i -= 2; else i = -1;
      fptr = &fields[i]; 
      break;
   CASE_EDIT_FILE:
      edit_file(base,fptr->data);
      if ( i>0 ) i -= 1; else i = -1;
      fptr = &fields[i];
      break;
   default: ;
      }
   }
clear_labels();
return TRUE;
}

Boolean_t Form::update(unsigned row,unsigned startfield) const
{
struct field *fptr=0;
int i=0, rc=0;
char data[512]; data[0] = '\0';

if ( row >= _capacity )
   { formerr.error(F_WINDOW_TOO_SMALL,__FILE__,__LINE__); abort(); }
display(row);
set_labels();
for (i=0,fptr=&fields[i]; i<nitems; i++,fptr++)
   {
   if ( wmove(subwindows[i],row,0) == ERR )
      { syserr.error(UNEXPECTED_ERROR,__FILE__,__LINE__); abort(); }
   wnoutrefresh(subwindows[i]);
   if ( i < startfield )  /* key fields */
      {
      wmove(subwindows[i],0,0); wrefresh(subwindows[i]);
      switch ( rc = wgetch(subwindows[i]) )
         {
      CASE_SAVE: clear_labels(); return TRUE;
      CASE_QUIT: case -1: clear_labels(); return FALSE;
      CASE_PREVIOUS:
         if ( i ) i -= 2; else i = -1;
         fptr = &fields[i];
         break;
      CASE_NEXT: break;
      CASE_EDIT_FILE:
         edit_file(base,fptr->data);
         if ( i>0 ) i -= 1; else i = -1;
         fptr = &fields[i];
         break;
      default: 
         error("Key fields cannot be changed.  Delete record and re-insert.");
         }
      }
   else  /* non-key fields */
      {
      rc = wgets(data,fptr->length+1,subwindows[i]);
      if ( data[0] )
         (void) strcpy(fptr->data,data);
      else
         {
         wmove(subwindows[i],row,0);
         wprintw(subwindows[i],"%-s",fptr->data);
         wnoutrefresh(subwindows[i]);
         }
      switch(rc)
         {
      CASE_SAVE: clear_labels(); return TRUE;
      CASE_QUIT: case -1: clear_labels(); return FALSE;
      CASE_NEXT: break;
      CASE_PREVIOUS:
         if ( i ) i -= 2; else i = -1;
         fptr = &fields[i];
         break;
      CASE_EDIT_FILE:
         edit_file(base,fptr->data);
         if ( i>0 ) i -= 1; else i = -1;
         fptr = &fields[i];
         break;
      default: ;
         }
      }
   }
clear_labels(); return TRUE;
}

ostream &operator<<(ostream &s,const Form &f)
{
char nrows, ncols, row, col;
for (row=0, nrows=NUMROWS(f.base); row < nrows; row++)
   {
   for (col=0, ncols=NUMCOLS(f.base); col < ncols; col++)
      s.put((char)mvwinch(f.base,row,col));
   s.put('\n');
   }
return s;
}

void Form::frefresh(WINDOW *s) const
{
touchwin(base); wnoutrefresh(base);
if (s) wnoutrefresh(s);
doupdate(); 
}

void Form::message(char *m) const
{ 
if (wmove(msgwin,0,0)==ERR)
      { syserr.error(UNEXPECTED_ERROR,__FILE__,__LINE__); abort(); }
werase(msgwin);
if ( m && m[0] ) wprintw(msgwin,m);
frefresh(msgwin);
}

int Form::prompt(char *m) const
{
int rc=0;
message(m);
switch(rc=wgetch(msgwin))
   {
CASE_QUIT: case -1: rc = -1; break;
default: waddch(msgwin,rc); break;
   }
message();
return rc;
}

void Form::error(char *e) const
{ 
if (wmove(errwin,0,0)==ERR)
      { syserr.error(UNEXPECTED_ERROR,__FILE__,__LINE__); abort(); }
werase(errwin);
if ( e && e[0] ) wprintw(errwin,e);
frefresh(errwin);
}

Boolean_t Form::reread(unsigned f,unsigned row) const
{
Boolean_t rc=0;
if ( f >= nitems )
   { formerr.error(F_INVALID_FIELD,__FILE__,__LINE__); abort(); }
if ( row >= _capacity )
   { formerr.error(F_WINDOW_TOO_SMALL,__FILE__,__LINE__); abort(); }
struct field *fptr = &fields[f];
if ( !fptr->data || !subwindows || !subwindows[f] )
      { syserr.error(UNEXPECTED_ERROR,__FILE__,__LINE__); abort(); }
if ( wmove(subwindows[f],row,0) == ERR )
      { syserr.error(UNEXPECTED_ERROR,__FILE__,__LINE__); abort(); }
frefresh(subwindows[f]);
switch(wgets(fptr->data,fptr->length+1,subwindows[f]))
   {
case -1: { formerr.error(F_GETCH_ERROR,__FILE__,__LINE__); abort(); }
CASE_QUIT: clear_labels(); rc = FALSE;
default: error(); /* remove error message */ rc = TRUE;
   }
return rc;
}

const unsigned Form::capacity() const
{
return _capacity;
}
