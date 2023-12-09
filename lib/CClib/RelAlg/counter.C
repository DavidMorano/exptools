#ident "@(#) /sable/sdb/ra/sblib/counter/s.counter.C"
/*      Copyright (c) 1989, 1991 AT&T - All Rights Reserved       */

#include <sblib.h>

static const int NPCERR=1;
static Error_message pc_errors[NPCERR] = {
{ /* 0 */
   "BAD_PERSISTENT_COUNTER",
   MM_SOFT|MM_NRECOV|MM_APPL, MM_HALT,
   "\007Unable to correctly read from Persistent_Counter",
   "Let Mail Server Processes create the Persistent_counter file."
   }
};
Error pcerr(pc_errors,NPCERR);

Persistent_Counter::Persistent_Counter(const char * file,
                   Int_t mod,Int_t init) : modulus(mod)
{
filename = strdup(file);
if ( (fd = open(filename,O_RDWR|O_CREAT|O_EXCL,0600)) != -1 )
   {
   while ( errno=0,(write(fd,&init,sizeof(Int_t)) != sizeof(Int_t)) )
      if ( errno != EINTR )
         { syserr.error(errno,__FILE__,__LINE__,filename); abort(); }
   }
else while ( errno=0,((fd = open(filename,O_RDWR,0600)) == -1) )
   if ( errno != EINTR )
      { syserr.error(errno,__FILE__,__LINE__,filename); abort(); }
if ( fd < 3 )
   {
   int tmpFd = fd;
   if ( (fd=fcntl(fd, F_DUPFD, 3)) < 3 )
      {
      syserr.error(errno,__FILE__,__LINE__,form("Failed to dup %s",filename) );
      abort();
      }
   if ( close(tmpFd) == -1 )
      {
      syserr.error(errno,__FILE__,__LINE__,
         form("Failed to close file descriptor %d, file %s.",tmpFd,filename) );
      abort();
      }
   }
}

Persistent_Counter::~Persistent_Counter()
{
if (filename)
   {
   free ((void *)filename);
   filename = (char *) 0;
   }
while ( errno=0,(close(fd) == -1) )
   if ( errno != EINTR )
      { syserr.error(errno,__FILE__,__LINE__,filename); abort(); }
}

Int_t Persistent_Counter::current_value()
{
Int_t counter=0;
while ( errno=0,(lseek(fd,0,SEEK_SET) == -1) )
   if ( errno != EINTR )
      { syserr.error(errno,__FILE__,__LINE__,filename); abort(); }
while ( errno=0,(read(fd,&counter,sizeof(Int_t)) != sizeof(Int_t)) )
   if ( errno != EINTR )
      { syserr.error(errno,__FILE__,__LINE__,filename); abort(); }
return counter;
}

Int_t Persistent_Counter::operator++()
{
Int_t counter=0;
lock();
while ( errno=0,(read(fd,&counter,sizeof(Int_t)) != sizeof(Int_t)) )
   if ( errno != EINTR )
      { 
      pcerr.error(PC_BAD_PERSISTENT_COUNTER,__FILE__,__LINE__,filename);
      abort(); 
      }
if ( modulus )
   counter %= modulus;
counter += 1;
while ( errno=0,(lseek(fd,0,SEEK_SET) == -1) )
   if ( errno != EINTR )
      { syserr.error(errno,__FILE__,__LINE__,filename); abort(); }
while ( errno=0,(write(fd,&counter,sizeof(Int_t)) != sizeof(Int_t)) )
   if ( errno != EINTR )
      { syserr.error(errno,__FILE__,__LINE__,filename); abort(); }
unlock();
return counter;
}

Int_t Persistent_Counter::operator=(Int_t n)
{
lock();
while ( errno=0,(write(fd,&n,sizeof(Int_t)) != sizeof(Int_t)) )
   if ( errno != EINTR )
      { syserr.error(errno,__FILE__,__LINE__,filename); abort(); }
unlock();
return n;
}

void Persistent_Counter::lock()
{
while ( errno=0,(lseek(fd,0,SEEK_SET) == -1) )
   if ( errno != EINTR )
      { syserr.error(errno,__FILE__,__LINE__,filename); abort(); }

int preserveAlarm = alarm(30); /* check for starvation */
if ( lockf(fd,F_LOCK,0) == -1 )
   { syserr.error(errno,__FILE__,__LINE__,filename); abort(); }
alarm(preserveAlarm);
}

void Persistent_Counter::unlock()
{
while ( errno=0,(lseek(fd,0,SEEK_SET) == -1) )
   if ( errno != EINTR )
      { syserr.error(errno,__FILE__,__LINE__,filename); abort(); }
while ( errno=0,(lockf(fd,F_ULOCK,0) == -1) )
   if ( errno != EINTR )
      { syserr.error(errno,__FILE__,__LINE__,filename); abort(); }
}
