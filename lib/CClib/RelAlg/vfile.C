#ident "@(#) /sable/sdb/ra/sblib/vfd/s.vfile.C"
/*        Copyright (c) 1989,1991 AT&T All Rights Reserved */

#include <sblib.h>

void Vfile::close()
{
if ( _file ) fflush(_file);
if ( _fd )   Vfd::close();          /* alt. ((Vfd *)this)->close() */
if ( _file ) (void) fclose(_file);  /* error but the FILE * gets deallocated */
_file = (FILE *)0;
}

Vfile::Vfile(const char *const name,const char *const mode) : Vfd (name)
{
strncpy(openmode,mode,2);
openmode[2] = '\0';
switch(mode[0])
   {
case 'r': openflags = O_CREAT| ( (mode[1]=='+') ? O_RDWR : O_RDONLY ); break;
case 'w': openflags = O_CREAT|O_TRUNC| ((mode[1]=='+')?O_RDWR:O_WRONLY); break;
case 'a': openflags = O_CREAT|O_APPEND| ((mode[1]=='+')?O_RDWR:O_WRONLY); break;
default: syserr.error(EACCES,__FILE__,__LINE__); abort();
   }
_file = (FILE *)0;
/* The file is not opened at this point because if children are forked */
/* there is a potential conflict of sharing internal UNIX table entries. */
}

Vfile::~Vfile()
{
Vfile::close();
}

FILE * Vfile::file()
{
if ( !_file )    /* if a NULL file porinter */
   { 
   Vfd::fd(); 
   if ( _fd != -1 )
      {
      if ( (_file=fdopen(_fd,openmode)) != (FILE *) 0 )
         setbuf(_file,(char *)0); 
      else           /* _file == NULL */
         {
         syserr.error(EMFILE,__FILE__,__LINE__,
                      "UNIX tuneable NOFILES does not match stdio _NFILES");
         abort();
         }
      }
   }
return _file;
}
