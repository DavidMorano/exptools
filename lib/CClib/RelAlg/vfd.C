#ident "@(#) /sable/sdb/ra/sblib/vfd/s.vfd.C"
/*        Copyright (c) 1989,1990,1991 AT&T All Rights Reserved   */

#include <sblib.h>

Link2 Vfd::freelist;
const int Vfd::max_fd = 6;

void Vfd::close()
{
if ( _fd != -1 )
   {
   if ( (offset = lseek(_fd,0L,SEEK_CUR)) == -1 )
      syserr.error(errno,__FILE__,__LINE__,filename); 
   ::close(_fd);
   _fd = -1;
   count--;
   }
}

Boolean_t Vfd::open()
{
if ( _fd != -1 ) return TRUE;
else if ( count >= max_fd ) 
   {
   errno = EMFILE;
   return FALSE;
   }
else if ( (_fd = ::open(filename,openflags,0666)) != -1 )
   {
    if ( _fd < 3 ) /* DON'T OPEN STDIN, STDOUT OR STDERR! Don't want errors */
       {           /* mixed in with our data. */
       int tempfd = _fd;
       if ( (_fd = fcntl(_fd,F_DUPFD,3)) < 3 )
          return FALSE; /* move to 1st available after 3 */
       ::close(tempfd);
       }
   if ( fcntl(_fd,F_SETFD,1) == -1 ) /* set close-on-exec flag */
      { syserr.error(errno,__FILE__,__LINE__,filename); abort(); }
   count++;
   openflags &= ~O_TRUNC; /* turn off truncate after 1st open */
   if ( lseek(_fd,offset,SEEK_SET) != offset )  /* reset offset */
      { syserr.error(errno,__FILE__,__LINE__,filename); return FALSE; }
   else return TRUE;
   }
else return FALSE;
}

Vfd::Vfd(const char *name,const int flags) 
    : filename(name?strdup(name):strdup(tmpnam((char *)0)))
{
openflags = flags;
if( name )
   unlink_flag = FALSE;
else { unlink_flag = TRUE; openflags |= O_CREAT; }
freelist_item = (List_item *)0;
_fd = -1;
offset = 0L;
available = TRUE;
}

Vfd::~Vfd()
{
if ( unlink_flag ) 
   unlink(filename);
/* free((void *)filename); */
free((char *)filename);
if ( freelist_item ) { freelist.remove(freelist_item); delete freelist_item; }
Vfd::close();
}

int Vfd::fd()
{
List_item *front = (List_item *)0;
Vfd *front_file = (Vfd *)0;
if ( _fd != -1 )
   { if (freelist_item) freelist.remove(freelist_item); }
else if ( Vfd::open() == FALSE )
   if ( errno ==  EMFILE)
      if ( front = freelist.pop() )
         {
         front_file = (Vfd *)front->data;
         front_file->close();
         front_file->freelist_item = (List_item *)0;
         delete front;        /* but not front_file! */
         if ( !Vfd::open() )
            { syserr.error(errno,__FILE__,__LINE__,filename); return -1; }
         }
      else { syserr.error(EMFILE,__FILE__,__LINE__,filename); return -1; }
   else { syserr.error(errno,__FILE__,__LINE__,filename); return -1; }
/*else Vfd::open succeeded */
if ( available )
   {
   if ( !freelist_item ) freelist_item = freelist.itemize(this);
   freelist.append(freelist_item);
   }
return _fd;
}
      
void Vfd::notavail()
{
available = FALSE;
if (freelist_item)
   { 
   freelist.remove(freelist_item); delete freelist_item; 
   freelist_item = (List_item *)0; 
   }
}

void Vfd::avail()
{
available = TRUE;
if ( (_fd != -1) && !freelist_item )
   freelist.push(freelist_item=freelist.itemize(this));
}
