#ident "@(#) /sable/sdb/ra/sblib/file/s.file.C"
/*      Copyright (c) 1989,1990,1991 AT&T - All Rights Reserved     */

#include <sblib.h>

/*
** Boolean_t create_file(char *filename)
**   --  valid filename is a pointer to a character string
**   --  returns TRUE if open with O_RDWR, O_CREAT, and O_EXCL flags
**       set succeeds, FALSE if open fails.
*/
Boolean_t create_file(char *filename)
{
int cfd;
if ( (cfd=open(filename,O_RDWR|O_CREAT|O_EXCL,0660)) == -1 )
   return syserr.error(errno,__FILE__,__LINE__,filename);
close(cfd);
return TRUE;
}

void fileTrace(char *tag)
{
int i;
struct stat statBuf;
char openfiles[21];
memset(openfiles,'\0',21);
for ( i=0; i < 20; i++ )
   {
   if ( fstat(i,&statBuf) == 0 )
      {
      openfiles[i] = 'O';
      syserr.error(TRACE,__FILE__,__LINE__,
            form("file desc %d:  dev %x inumber %d rdev %x",
            i,statBuf.st_dev,statBuf.st_ino,statBuf.st_rdev));
      }
   else
      openfiles[i] = 'C';
   }
syserr.error(TRACE,__FILE__,__LINE__,form("%s: %s",tag,openfiles));
}
