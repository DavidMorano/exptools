#ident "@(#) /sable/sdb/ra/rel/extension/s.bf_ext.C"
/*      Copyright (c) 1989,1991 AT&T - All Rights Reserved */

#include <relation.h>

BF_Extension::BF_Extension(const char *file,Fileperm perm)
{
open_flags = (perm==READWRITE) ? O_RDWR : O_RDONLY;
fd = new Vfd(file,open_flags);
walk_tuple = (Tuple *)0;
}

BF_Extension::~BF_Extension()
{
delete fd;
if ( walk_tuple ) walk_tuple->done();
}

unsigned BF_Extension::cardinality()
{
const unsigned HIGHVAL= (~0)>>1;
relerr.errno = HIGHVAL;
(void) Extension::cardinality();
if ( relerr.errno != HIGHVAL ) return 0;
struct stat statbuf;
if ( fstat(fd->fd(),&statbuf) == -1 )
   { syserr.error(errno,__FILE__,__LINE__,fd->filename); abort(); }
return (item_size?(statbuf.st_size/item_size):0);
}

Boolean_t BF_Extension::startwalk()
{
if ( Extension::startwalk() )
   { // rewind the file
   if ( lseek(fd->fd(),0L,SEEK_SET) != 0 )
      { syserr.error(errno,__FILE__,__LINE__,fd->filename); abort(); }
   // fd->notavail(); // will be locking so remove from free list
   walk_tuple = (Tuple *) 0;
   return TRUE;
   }
else return FALSE;
}

Tuple * BF_Extension::walk()
{
if ( Extension::walk() )
   {
   if ( walk_tuple ) // previous iteration
      {
      walk_tuple->done();
      // lockf(fd->fd(),F_ULOCK,-item_size); // unlock previous record
      // need to distinguish shared vs. exclusive for READONLY opens anyway
      }
   walk_tuple = Tuple_new(item_size);
   // if ( lockf(fd->fd(),F_LOCK,item_size) == -1 )     // lock record
   //   { syserr.error(errno,__FILE__,__LINE__); abort(); }
   if ( read(fd->fd(),(char *)(walk_tuple->data),item_size) != item_size )
      {    // end of file
      walk_tuple->done();
      walk_tuple = (Tuple *) 0;
      }
   else walk_tuple->flags = T_CONSTRAINED; // data assumed to be good
   return walk_tuple;
   }
else return (Tuple *)0;
}

Boolean_t  BF_Extension::operator=(Tuple *t)
{
if ( Extension::operator=(t) )
   {
   if ( open_flags != O_RDWR )
      return relerr.error(R_READONLY_EXTENSION,__FILE__,__LINE__,fd->filename);
   if ( walk_tuple ) // in a walk with a record
      {
      lseek(fd->fd(),-item_size,SEEK_CUR); // back up
      if ( write(fd->fd(),(char *)(t->data),item_size)  != item_size )
         { syserr.error(errno,__FILE__,__LINE__,fd->filename); abort(); }
      return TRUE;
      }
   else return FALSE;
   }
else return FALSE;
}

Boolean_t BF_Extension::endwalk()
{
if ( Extension::endwalk() )
   {
   if ( walk_tuple )
      {
      // lockf(fd->fd(),F_ULOCK,-item_size); // unlock previous record
      // fd->avail(); // done with locking so return to free list
      walk_tuple->done();
      walk_tuple = (Tuple *) 0;
      }
   return TRUE;
   }
else return FALSE;
}

Boolean_t BF_Extension::truncate()
{
if ( Extension::truncate() )
   if ( open_flags != O_RDWR )
      return relerr.error(R_READONLY_EXTENSION,__FILE__,__LINE__,fd->filename);
   else
      {
      Vfd tempfd(fd->filename,O_WRONLY|O_TRUNC|O_CREAT);
      (void) tempfd.fd(); // opens the file and truncates
      return TRUE;
      }
else return FALSE;
}

Boolean_t BF_Extension::operator+=(Tuple *tuple)
{
if ( Extension::operator+=(tuple) )
   {
   if ( open_flags != O_RDWR )
      return relerr.error(R_READONLY_EXTENSION,__FILE__,__LINE__);
   else
      { // O_APPEND avoids race window between seek & write
      long offset;
      if ( (offset=lseek(fd->fd(),0,SEEK_CUR)) == -1)
         { syserr.error(errno,__FILE__,__LINE__,fd->filename); abort(); }
      if ( fcntl(fd->fd(),F_SETFL,open_flags|O_APPEND) == -1 )
         { syserr.error(errno,__FILE__,__LINE__,fd->filename); abort(); }
      if ( write(fd->fd(),(char *)(tuple->data),item_size) != item_size )
         { syserr.error(errno,__FILE__,__LINE__,fd->filename); abort(); }
      if ( fcntl(fd->fd(),F_SETFL,open_flags) == -1 )
         { syserr.error(errno,__FILE__,__LINE__,fd->filename); abort(); }
      if ( lseek(fd->fd(),offset,SEEK_SET) == -1)
         { syserr.error(errno,__FILE__,__LINE__,fd->filename); abort(); }
      return TRUE;
      }
   }
else return FALSE;
}
