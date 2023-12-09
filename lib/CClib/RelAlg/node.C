#ident "@(#) /sable/sdb/ra/sblib/node/s.node.C"
/*      Copyright (c) 1991 AT&T - All Rights Reserved          */

#include <sblib.h>

Link1_stack Node::dirsToRemove;

/*                     _chown()
**
**  OUTCOMES:
**    1. if chown(2) fails
**          Return errno
**    2. if chown(2) is successfull
**          Return 0
*/
#undef  FALSEreturn
#define FALSEreturn { \
                    Trace(1,form("Returning errno=%d from _chown()",errno)) \
                    return errno; \
                    }
int _chown(char *name, struct stat *nmStatPtr, int type)
{
    Trace(1,form("Entering _chown(), name = %s, type = %d",name,type))
    (void) nmStatPtr; (void) type;              /* keep compiler quite */
    NPNScheck(name)
Sc( chown(name,Node::userId,Node::groupId)                                  ,-1)
    Trace(1,"Returning 0 from _chown()")
    return(0);
}

define(errorCases,        /* `switch error cases for _copy & _link & _remove' */
       case FTW_DNR: errno = EPERM; SYSreturn break;     /* dir not readable */
       case FTW_NS : SYSreturn break;                    /* stat(2) failed */
       default:
          syserr.error(UNEXPECTED_ERROR,__FILE__,__LINE__,form("type=%d",type));
          break;
)

/* _copyLink(copy|link,FTW_F code) */
define(_copyLink,
`#undef  FALSEreturn
#define FALSEreturn { \
                    Trace(1,form("Returning errno=%d from _$1()",errno)) \
                    return errno; \
                    }
int _$1(char *name, struct stat *nmStatPtr, int type)
    {
    Trace(1,form("Entering _$1(), name = %s, type = %d",name,type))
    (void) nmStatPtr;      /* keep compiler quiet */
    NPNScheck(name);
    const char *fullToNodeNm = (char *)0;
    int sourceNodeLen = strlen(Node::sourceNode);
    if ( *(name+sourceNodeLen) == NULL )
       fullToNodeNm = Node::toNode;
    else
       fullToNodeNm = form("%s/%s",Node::toNode, name+sourceNodeLen);

    switch (type)
       {
       case FTW_F:                      /* regular file */
          {
          struct stat destinationStatBuf;
          if ( stat(fullToNodeNm,&destinationStatBuf) == -1 )
             {
             if ( errno != ENOENT )
                SYSreturn;
             }
          else    /* destination exists, check file type */
             {
             if ( (destinationStatBuf.st_mode & S_IFMT) != S_IFREG )
                {
                syserr.error(EEXIST,__FILE__,__LINE__,
                  form("%s is a file, but %s exists and is not a regular file.",
                                                            name,fullToNodeNm));
                FALSEreturn
                }
             else          /* destination exists as a regular file, remove it */
Sc(             unlink(fullToNodeNm)                                        ,-1)
             }
          $2
          }
          break;
       case FTW_D:                      /* readable directory */
          if ( mkdir(fullToNodeNm,0777) == -1 )
             {
             if (errno == EEXIST)
                {
                struct stat destinationStatBuf;
Sc(             stat(fullToNodeNm,&destinationStatBuf)                      ,-1)
                if ( (destinationStatBuf.st_mode & S_IFMT) != S_IFDIR )
                   {
                   syserr.error(EEXIST,__FILE__,__LINE__,form(
                      "%s is a directory, but %s exists and is not a directory."
                      ,name,fullToNodeNm));
                   FALSEreturn
                   }
                /* else, destination already exists as a directory, continue */
                }
             else
                SYSreturn
             }
          break;
       errorCases
       }
    Trace(1,"Returning 0 from _$1()")
    return(0);
    }'
)
/*                     _copy()
**
**  OUTCOMES:
**    1. When source name is a NULL Pointer
**         generate NULL_POINTER error.
**    2. When the file type is not File or Directory
**        generate an error &
**        return errno.
**    3. if copy of the file or mkdir(2) fail
**          Return errno
**    4. Otherwise return 0
*/
_copyLink(copy,
         `int nBytesR=0, nBytesW=0;
          char buffer[BUFSIZ];
          Vfd source(name,O_RDONLY);
          Vfd destination(fullToNodeNm,O_WRONLY|O_CREAT|O_TRUNC);
          while ( (nBytesR = read(source.fd(), buffer, BUFSIZ)) > 0 )
             {
             if ( (nBytesW=write(destination.fd(),buffer,nBytesR)) != nBytesR )
                {
                if (nBytesW >= 0)
                   errno = EFBIG;
                SYSreturn
                }
             }
          if (nBytesR < 0)
             SYSreturn'
)

/*                         _link()
**
**  OUTCOMES:
**    1. When source name is a NULL Pointer
**         generate NULL_POINTER error.
**    2. When the file type is not File or Directory
**        generate an error &
**        return errno.
**    3. When file type of source does not match file type of the destination
**         generate EEXIST &
**         return FALSE
**    4. When link(2) fails because the destination file exists
**         remove the existing file &
**         link over the new one.
**    5. When link(2) fails for any other reason
**         return errno.
**    6. When unlink(2) fails for any reason
**         return errno.
**    7. When mkdir(2) fails because the destination directory exists
**         do nothing &
**         return 0
**    8. When mkdir(2) fails for any other reason
**         return errno.
**    9. Otherwise
**         link the file or make the directory, and
**         return 0
*/
_copyLink(link,
         `if ( link(name,fullToNodeNm) == -1 )
                SYSreturn'
)

/*                        _remove()
**
**  OUTCOMES:
**    1. When source name is a NULL Pointer
**         generate NULL_POINTER error
**    2. When source name is an empty string
**         generate EMPTY_STRING error
**    3. if unlink(2) fails return errno
**    4. if unlink(2) is successful return 0
**    5. if the thing to be removed is a directory, save it's name.
**         It will be removed after its contents are removed.
**         return 0
**    6. Anything else is a failure, return errno.
*/
#undef  FALSEreturn
#define FALSEreturn { \
                    Trace(1,form("Returning errno=%d from _remove()",errno)) \
                    return errno; \
                    }
int _remove(char *name, struct stat *nmStatPtr, int type)
    {
    Trace(1,form("Entering _remove(), name = %s, type = %d",name,type))
    (void) nmStatPtr;      /* keep compiler quiet */
    NPNScheck(name)
    switch (type)
       {
       case FTW_F:                      /* regular file */
Sc(       unlink(name)                                                      ,-1)
          break;
       case FTW_D:                      /* readable directory */
          /*  save directory name to be removed later */
          Node::dirsToRemove.push(Node::dirsToRemove.itemize(strdup(name)));
          break;
       errorCases
       }
    Trace(1,"Returning 0 from _remove()")
    return(0);
    }

/*                      Node::Node()
**
**  OUTCOMES:
**     1. If node name argument is not accessible
**           invalidate node object and return
**     2. Otherwise store nodeName and
**           validate node object
*/
#undef  FALSEreturn
#define FALSEreturn { \
                    _valid=FALSE; \
                    Trace(1,"Returning from Node::Node(), FALSE path") \
                    return; \
                    }
Node::Node(const char *nodeName)
    {
    Trace(1,form("Entering Node::Node(), nodeName = %s",nodeName))
    _valid = FALSE;
    NPNScheck(nodeName)
    Node::nodeName = (char *)0;
Sc( stat(nodeName,&statBuf)                                                 ,-1)
    Node::nodeName = strdup(nodeName);
    _valid = TRUE;
    Trace(1,"Returning from Node::Node(), TRUE path")
    }

/*                        Node::~Node()
**
**    Deallocates any members that were dynamically allocated.
**
**  OUTCOMES:
**     1. Void
*/
Node::~Node()
    {
    Trace(1,"Entering Node::~Node()")
    List_item *dirToRemove;
    while (dirToRemove = dirsToRemove.pop())
       {
       free(dirToRemove->data);
       delete dirToRemove;
       }
    if (nodeName)
       {
       free(nodeName);
       nodeName = (char *)0;
       }
    Trace(1,"Returning from Node::~Node()")
    }

/*         Node::remove()
**
**   OUTCOMES:
**     1. if this is a valid Node && all files are removed
**          remove all of the directories, including Node
**          return TRUE
**     2. Otherwise return FALSE
*/
#undef  FALSEreturn
#define FALSEreturn { \
         _valid = FALSE; \
         Trace(1,form("Returning FALSE from Node::remove(), errno=%d",errno)) \
         return FALSE; \
         }
Boolean_t Node::remove()
    {
    Trace(1,"Entering Node::remove()")
    if ( _valid && walk(_remove) )
       {
       List_item *dirToRemove;
       while (dirToRemove = dirsToRemove.pop())
          {
Sc(       rmdir((char *)dirToRemove->data)                                  ,-1)
          free(dirToRemove->data);
          delete dirToRemove;
          }
       _valid = FALSE;
       Trace(1,"Returning TRUE from Node::remove()")
       return TRUE;
       }
    Trace(1,"Returning FALSE from Node::remove()")
    return FALSE;
    }
 
/*         Node::sameType()
**
**   OUTCOMES:
**     1. When this is not a valid Node
**          return FALSE
**     2. When the argument does not exist
**          return TRUE
**     3. When the argument and this Node have the same file type
**          return TRUE
**     4. Otherwise return FALSE
*/
#undef FALSEreturn
#define FALSEreturn { \
       Trace(1,form("Returning FALSE from Node::sameType(), errno=%d",errno)) \
       return FALSE; \
       }
Boolean_t Node::sameType(const char *toNode)
    {
    Boolean_t rc = FALSE; 
    struct stat toNodeStatBuf;
 
    Trace(1,form("Entering Node::sameType() toNode = %s",toNode))
    NPNScheck(toNode)
    if (_valid) 
       {  
       if ( stat(toNode,&toNodeStatBuf) != -1 )
          {                                     /* destination exists */ 
          if ( (toNodeStatBuf.st_mode & S_IFMT) == (statBuf.st_mode & S_IFMT) )
             rc = TRUE;
          }
       else
          {
          if (errno == ENOENT)
             rc = TRUE;         /* destination does not exist */
          else
             SYSreturn;
          }   
       }
    Trace(1,form("Returning %s from Node::sameType().",rc ? "TRUE" : "FALSE"))
    return rc;
    }

/*         Node::chown()
**
**   OUTCOMES:
**     1. if this is a valid Node
**           Save the arguments to the static data area so that
**           the function called by ftw() (via walk()) can access them.
**           Return the value returned by walk().
**     2. Otherwise return FALSE.
*/
Boolean_t Node::chown(int uid, int gid)
    {
    Trace(1,form("Entering Node::chown() uid = %d, gid = %d",uid,gid))
    if (_valid)
       {
       userId = uid;
       groupId = gid;
       Trace(1,"Returning return value from Node::walk() from Node::chown()")
       return walk(_chown);
       }
    else
       {
       Trace(1,"Returning FALSE from Node::chown()")
       return FALSE;
       }
    }

/* copyLink(copy|link) */
define(copyLink,
/*         Node::$1()
**
**   OUTCOMES:
**     1. if this is a valid Node
**           Save the arguments to the static data area so that
**           the function called by ftw() (via walk()) can access them.
**           Return the value returned by walk().
**     2. Otherwise return FALSE.
*/
Boolean_t Node::$1(const char *toNode)
    {
    Trace(1,form("Entering Node::$1() toNode = %s",toNode))
    NPNScheck(toNode)
    if (_valid && sameType(toNode))
       {
       Node::sourceNode = nodeName;
       Node::toNode = toNode;
       Trace(1,"Returning return value from Node::walk() from Node::$1()")
       return walk(_$1);
       }
    else
       {
       Trace(1,"Returning FALSE from Node::$1()")
       return FALSE;
       }
    }
)
copyLink(copy)
copyLink(link)

/*         Node::status()
**
**  OUTCOMES:
**    1. If the node is valid
**         copy the status of this node into the argument, and
**         return TRUE.
**    2. Otherwise return FALSE.
*/
Boolean_t Node::status(struct stat &buffer)
    {
    Trace(1,"Entering Node::status()")
    if (_valid)
       {
       buffer = statBuf;
       Trace(1,"Returning TRUE from Node::status()")
       return TRUE;
       }
    else
       {
       Trace(1,"Returning FALSE from Node::status()")
       return FALSE;
       }
    }

/*         Node::valid()
**
**   OUTCOMES:
**     1. return the value of the valid Node flag.
*/
Boolean_t Node::valid()
    {
    Trace(1,form("Entering & Returning from Node::valid(), valid = %d",_valid))
    return(_valid);
    }

/*         Node::walk()
**
**  OUTCOMES:
**    1. if this is a valid Node and ftw() returns zero,   return TRUE
**    2. if this is an invalid Node,                       return FALSE
**    3. if ftw() returns non-zero,                        return FALSE
*/
Boolean_t Node::walk(WALKFUNC walkFunction)
    {
    Trace(1,"Entering Node::walk()")
    if ( (_valid) && (ftw(nodeName,walkFunction,5) == 0) )
       {
       Trace(1,"Returning TRUE from Node::walk()")
       return TRUE;
       }
    else
       {
       Trace(1,"Returning FALSE from Node::walk()")
       return FALSE;
       }
    }
