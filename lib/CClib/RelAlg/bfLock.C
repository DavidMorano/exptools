#ident "@(#) /sable/sdb/ra/rel/relation/s.bfLock.C"
/*      Copyright (c) 1991 AT&T - All Rights Reserved */

#include <relation.h>

#define FALSEreturn  { abort(); exit(errno); }
/*               LockBF::LockBF()
**
**   Obtain the specified lock on the specified relation.
**   
**  OUTCOMES:
**    1. When the relation is already locked
**         wait for the lock.
**    2. When fcntl() fails
**         abort().
*/
LockBF::LockBF(BF_Relation &rel,int lockType)
    {
    bfe = (BF_Extension *)&rel.extension;
    fLock.l_whence = 0;
    fLock.l_start = fLock.l_len = 0L;
    fLock.l_type = lockType;
    bfe->fd->notavail();
Sc( fcntl(bfe->fd->fd(),F_SETLKW,(int)&fLock),                               -1)
    }

/*           LockBF::~LockBF()
**
**  Release the lock on the relation.
**
**  OUTCOMES:
**    1. When fcntl() fails
**         abort().
*/
LockBF::~LockBF()
    {
    fLock.l_type = F_UNLCK;
Sc( fcntl(bfe->fd->fd(),F_SETLKW,(int)&fLock),                               -1)
    bfe->fd->avail();
    }
