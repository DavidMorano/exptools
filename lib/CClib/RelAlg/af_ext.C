#ident "@(#) /sable/sdb/ra/rel/extension/s.af_ext.C"
/*      Copyright (c) 1989, 1990,1991 AT&T - All Rights Reserved         */

/*   THESE COMMENTS WERE TAKEN FROM af_ext.ct; THEY HAVE NOT BEEN CHECKED
**   Vfile *AF_Extension::fptr
**      -- valid fptr is a non-NULL pointer to a valid Vfile.
**      -- fptr is assumed valid.
**   Vfile *AF_Extension::temp_fptr
**      -- valid temp_fptr is a non-NULL pointer to a valid Vfile.
**      -- temp_fptr is assumed valid.
**   char * AF_Extension::open_flags
**      -- valid open_flags is a legal flag value for fopen(3C)
**      -- open_flags is passed through to Vfile.
**   Tuple * AF_Extension::walk_tuple
**      -- valid walk_tuple is NULL or a pointer to a valid Tuple.
**      -- walk_tuple is assumed valid.
**
**   AF_Extension::AF_Extension(const char *file,Fileperm perm)
**      -- valid file is NULL or a non-NULL pointer to a character string.
**      -- file is passed through to Vfile.
**      -- otherwise file is assumed valid.
**      -- valid perm is any valid Fileperm.
**      -- perm is assumed valid.
**
**   Boolean_t AF_Extension::startwalk()
**   Boolean_t AF_Extension::endwalk()
**   Boolean_t AF_Extension::truncate()
**      -- return is any valid Boolean_t.
**
**   Tuple * AF_Extension::walk()
**      -- return is NULL or a valid Tuple * contained in the AF_Extension.
**
**   Boolean_t AF_Extension::operator=(Tuple *t)
**      -- return is any valid Boolean_t.
**      -- valid t is a non-NULL pointer to a valid Tuple.
**      -- t is passed through to Extension::operator=.
**
**   Boolean_t AF_Extension::operator+=(Tuple*t)
**      -- return is any valid Boolean_t.
**      -- valid t is a non-NULL pointer to a valid Tuple.
**      -- t is passed through to Extension::operator+=.
*/

#include <relation.h>

unsigned AF_Extension::cardinality()
{
const unsigned HIGHVAL= (~0)>>1;
relerr.errno = HIGHVAL;
(void) Extension::cardinality();
if ( relerr.errno != HIGHVAL ) return 0;
if ( !cardinality_known )
   {
   for ( startwalk(), nitems = 0; walk(); nitems++ )
      ;
   endwalk();
   cardinality_known = TRUE;
   }
return nitems;
}

Boolean_t  AF_Extension::operator=(Tuple *t)
{
if ( !Extension::operator=(t) )
   return FALSE;
if ( open_flags[1] != '+' )             // read only
   return relerr.error(R_READONLY_EXTENSION,__FILE__,__LINE__);
if ( ((char *)(t->data))[strlen((char *)(t->data))-1] != '\n' )
   return relerr.error(R_NO_NEWLINE,__FILE__,__LINE__);
if ( walk_tuple == (Tuple *) 0 )        // nothing to replace
   return FALSE;
walk_tuple->done();
walk_tuple = t;      // walk() will handle copies from here on out
walk_tuple->share();  // need to keep reference 'til next walk
if ( temp_fptr == NULL )       // first update of the walk
   { // copy preceding portion of file
   char *io_buf = new char[item_size?item_size:1];
   temp_fptr = new Vfile();
   long offset = ftell(fptr->file());
   rewind(fptr->file());
   while (fgets(io_buf,item_size,fptr->file()) && (ftell(fptr->file())<offset))
         if ( fputs(io_buf,temp_fptr->file()) == EOF ) // everything but current
            { syserr.error(errno,__FILE__,__LINE__); abort(); }
   delete io_buf;
   }
return TRUE;
}

Boolean_t AF_Extension::endwalk()
{
if ( !Extension::endwalk() )
   return FALSE;
if ( walk_tuple )
   {
   if ( temp_fptr )
      if ( fputs((char *)(walk_tuple->data),temp_fptr->file()) == EOF )
         { syserr.error(errno,__FILE__,__LINE__); abort(); }
   walk_tuple->done();
   walk_tuple = (Tuple *) 0;
   }
if ( temp_fptr )
   { // copy rest of file then copy back to preserve inumber
   Tuple * io_tuple = Tuple_new(item_size);
   while ( fgets((char *)(io_tuple->data),item_size,fptr->file()) )
      if (fputs((char *)(io_tuple->data),temp_fptr->file()) == EOF )
         { syserr.error(errno,__FILE__,__LINE__); abort(); }
   truncate();
   rewind(temp_fptr->file());
   while ( fgets((char *)(io_tuple->data),item_size,temp_fptr->file()) )
      {
      if ( fputs((char *)(io_tuple->data),fptr->file()) == EOF ) // copy it back
         { syserr.error(errno,__FILE__,__LINE__); abort(); }
      nitems++;
      }
   io_tuple->done();
   if ( unlink(temp_fptr->filename) == -1 )
      { syserr.error(errno,__FILE__,__LINE__); abort(); }
   delete temp_fptr;
   temp_fptr = (Vfile *) 0;
   }
if ( fflush(fptr->file()) == -1 )
   { syserr.error(errno,__FILE__,__LINE__); abort(); }
struct flock s_lock;
s_lock.l_whence = SEEK_SET; s_lock.l_start = 0; s_lock.l_len = 0;
s_lock.l_type = F_UNLCK;
if ( fcntl(fptr->fd(),F_SETLKW,(int)&s_lock) == -1 )
   { syserr.error(errno,__FILE__,__LINE__,fptr->filename); abort(); }
fptr->avail();
return TRUE;
}

AF_Extension::AF_Extension(const char *file,Fileperm perm)
{
cardinality_known = FALSE;
item_size = 5120; /* use to be BUFSIZ; Mail Server is using large buffers */
temp_fptr = (Vfile *)0;
walk_tuple = (Tuple *)0;
open_flags = (perm==READWRITE) ? "r+" : "r";
fptr = new Vfile(file,open_flags);
}

AF_Extension::~AF_Extension()
{
delete fptr;
delete temp_fptr;
if ( walk_tuple ) walk_tuple->done();
}

Boolean_t AF_Extension::startwalk()
{
if ( Extension::startwalk() )
   {
   walk_tuple = (Tuple *) 0;
   if ( temp_fptr) delete temp_fptr;
   fptr->notavail();
   struct flock s_lock;
   s_lock.l_whence = SEEK_SET; s_lock.l_start = 0; s_lock.l_len = 0;
   if ( open_flags[1] == '+' ) // writable
      s_lock.l_type = F_WRLCK;
   else s_lock.l_type = F_RDLCK;
   if ( fcntl(fptr->fd(),F_SETLKW,(int)&s_lock) == -1 )
      return syserr.error(errno,__FILE__,__LINE__,fptr->filename);
   else { rewind(fptr->file()); return TRUE; }
   }
else return FALSE;
}

Tuple * AF_Extension::walk()
{
if ( Extension::walk() )
   {
   if ( walk_tuple )
      {
      if ( temp_fptr ) // making a copy
         if ( fputs((char *)walk_tuple->data,temp_fptr->file()) == EOF )
            { syserr.error(errno,__FILE__,__LINE__,fptr->filename); abort(); }
      walk_tuple->done();
      }
   walk_tuple = Tuple_new(item_size);
   char *data = (char *)(walk_tuple->data);
   if ( fgets(data,item_size,fptr->file()) )
      {
      if ( data[strlen(data)-1] != '\n' )
         (void) relerr.error(R_LINE_TOO_LONG,__FILE__,__LINE__,fptr->filename);
      }
   else    // end of file
      {
      walk_tuple->done();
      walk_tuple = (Tuple *) 0;
      }
   return walk_tuple;
   }
else return (Tuple *)0;
}

Boolean_t AF_Extension::truncate()
{
if ( Extension::truncate() )
   if ( open_flags[1] == '\0' )
      return relerr.error(R_READONLY_EXTENSION,__FILE__,__LINE__);
   else
      {
      Vfd fd(fptr->filename,O_WRONLY|O_TRUNC|O_CREAT);
      (void) fd.fd(); // opens the file & truncates it.
      nitems = 0;
      cardinality_known = TRUE;
      rewind(fptr->file());
      return TRUE;
      }
else return FALSE;
}

Boolean_t AF_Extension::operator+=(Tuple *tuple)
{
if ( Extension::operator+=(tuple) )
   if ( open_flags[1] == '\0' )
      return relerr.error(R_READONLY_EXTENSION,__FILE__,__LINE__);
   else if ( ((char *)(tuple->data))[strlen((char *)tuple->data)-1] != '\n' )
      return relerr.error(R_NO_NEWLINE,__FILE__,__LINE__);
   else
      {
      Boolean_t rc;
      long offset=ftell(fptr->file());
      if ( fseek(fptr->file(),0L,SEEK_END) != 0)
         { syserr.error(errno,__FILE__,__LINE__,fptr->filename); abort(); }
      if ( fputs((char *)tuple->data,fptr->file()) == -1 )
         rc = FALSE;
      else { nitems++; rc = TRUE; }
      if ( fseek(fptr->file(),offset,SEEK_SET) != 0 )
         { syserr.error(errno,__FILE__,__LINE__,fptr->filename); abort(); }
      return rc;
      }
else return FALSE;
}
