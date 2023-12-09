#ident "@(#) /sable/sdb/ra/sblib/error/s.error.C"
/*      Copyright (c) 1989,1990,1991 AT&T - All Rights Reserved */

#include <sblib.h>

static const int NSYSERR = 93;
static Error_message system_errors[NSYSERR] = {
{ /* 0 */
   "ERROR0", MM_SOFT|MM_RECOVER|MM_OPSYS, MM_ERROR,
   "Error 0", },
{ /* 1 */
   "EPERM", MM_SOFT|MM_RECOVER|MM_OPSYS, MM_ERROR,
   "Not owner", },
{ /* 2 */
   "ENOENT", MM_SOFT|MM_RECOVER|MM_OPSYS, MM_ERROR,
   "No such file or directory", },
{ /* 3 */
   "ESRCH", MM_SOFT|MM_RECOVER|MM_OPSYS, MM_ERROR,
   "No such process", },
{ /* 4 */
   "EINTR", MM_SOFT|MM_RECOVER|MM_OPSYS, MM_ERROR,
   "Interrupted system call", },
{ /* 5 */
   "EIO", MM_SOFT|MM_RECOVER|MM_OPSYS, MM_ERROR,
   "I/O error", },
{ /* 6 */
   "ENXIO", MM_SOFT|MM_RECOVER|MM_OPSYS, MM_ERROR,
   "No such device or address", },
{ /* 7 */
   "E2BIG", MM_SOFT|MM_RECOVER|MM_OPSYS, MM_ERROR,
   "Arg list too long", },
{ /* 8 */
   "ENOEXEC", MM_SOFT|MM_RECOVER|MM_OPSYS, MM_ERROR,
   "Exec format error", },
{ /* 9 */
   "EBADF", MM_SOFT|MM_RECOVER|MM_OPSYS, MM_ERROR,
   "Bad file number",  },
{ /* 10 */
   "ECHILD", MM_SOFT|MM_RECOVER|MM_OPSYS, MM_ERROR,
   "No child processes", },
{ /* 11 */
   "EAGAIN", MM_SOFT|MM_RECOVER|MM_OPSYS, MM_ERROR,
   "No more processes", },
{ /* 12 */
   "ENOMEM", MM_SOFT|MM_RECOVER|MM_OPSYS, MM_ERROR,
   "Not enough space", },
{ /* 13 */
   "EACCES", MM_SOFT|MM_RECOVER|MM_OPSYS, MM_ERROR,
   "Permission denied", },
{ /* 14 */
   "EFAULT", MM_SOFT|MM_RECOVER|MM_OPSYS, MM_ERROR,
   "Bad address", },
{ /* 15 */
   "ENOTBLK", MM_SOFT|MM_RECOVER|MM_OPSYS, MM_ERROR,
   "Block device required", },
{ /* 16 */
   "EBUSY", MM_SOFT|MM_RECOVER|MM_OPSYS, MM_ERROR,
   "Device busy", },
{ /* 17 */
   "EEXIST", MM_SOFT|MM_RECOVER|MM_OPSYS, MM_ERROR,
   "File exists", },
{ /* 18 */
   "EXDEV", MM_SOFT|MM_RECOVER|MM_OPSYS, MM_ERROR,
   "Cross-device link", },
{ /* 19 */
   "ENODEV", MM_SOFT|MM_RECOVER|MM_OPSYS, MM_ERROR,
   "No such device", },
{ /* 20 */
   "ENOTDIR", MM_SOFT|MM_RECOVER|MM_OPSYS, MM_ERROR,
   "Not a directory", },
{ /* 21 */
   "EISDIR", MM_SOFT|MM_RECOVER|MM_OPSYS, MM_ERROR,
   "Is a directory", },
{ /* 22 */
   "EINVAL", MM_SOFT|MM_RECOVER|MM_OPSYS, MM_ERROR,
   "Invalid argument", },
{ /* 23 */
   "ENFILE", MM_SOFT|MM_RECOVER|MM_OPSYS, MM_ERROR,
   "File table overflow", },
{ /* 24 */
   "EMFILE", MM_SOFT|MM_RECOVER|MM_OPSYS, MM_ERROR,
   "Too many open files", 
   "Report this to the System Administrator" },
{ /* 25 */
   "ENOTTY", MM_SOFT|MM_RECOVER|MM_OPSYS, MM_ERROR,
   "Not a typewriter", },
{ /* 26 */
   "ETXTBSY", MM_SOFT|MM_RECOVER|MM_OPSYS, MM_ERROR,
   "Text file busy", },
{ /* 27 */
   "EFBIG", MM_SOFT|MM_RECOVER|MM_OPSYS, MM_ERROR,
   "File too large", },
{ /* 28 */
   "ENOSPC", MM_SOFT|MM_RECOVER|MM_OPSYS, MM_ERROR,
   "No space left on device", },
{ /* 29 */
   "ESPIPE", MM_SOFT|MM_RECOVER|MM_OPSYS, MM_ERROR,
   "Illegal seek", },
{ /* 30 */
   "EROFS", MM_SOFT|MM_RECOVER|MM_OPSYS, MM_ERROR,
   "Read-only file system", },
{ /* 31 */
   "EMLINK", MM_SOFT|MM_RECOVER|MM_OPSYS, MM_ERROR,
   "Too many links", },
{ /* 32 */
   "EPIPE", MM_SOFT|MM_RECOVER|MM_OPSYS, MM_ERROR,
   "Broken pipe", },
{ /* 33 */
   "EDOM", MM_SOFT|MM_RECOVER|MM_OPSYS, MM_ERROR,
   "Argument out of domain", },
{ /* 34 */
   "ERANGE", MM_SOFT|MM_RECOVER|MM_OPSYS, MM_ERROR,
   "Result too large", },
{ /* 35 */
   "ENOMSG", MM_SOFT|MM_RECOVER|MM_OPSYS, MM_ERROR,
   "No message of desired type", },
{ /* 36 */
   "EIDRM", MM_SOFT|MM_RECOVER|MM_OPSYS, MM_ERROR,
   "Identifier removed", },
{ /* 37 */
   "ECHRNG", MM_SOFT|MM_RECOVER|MM_OPSYS, MM_ERROR,
   "Channel number out of range", },
{ /* 38 */
   "EL2NSYNC", MM_SOFT|MM_RECOVER|MM_OPSYS, MM_ERROR,
   "Level 2 not synchronized", },
{ /* 39 */
   "EL3HLT", MM_SOFT|MM_RECOVER|MM_OPSYS, MM_ERROR,
   "Level 3 halted", },
{ /* 40 */
   "EL3RST", MM_SOFT|MM_RECOVER|MM_OPSYS, MM_ERROR,
   "Level 3 reset", },
{ /* 41 */
   "ELNRNG", MM_SOFT|MM_RECOVER|MM_OPSYS, MM_ERROR,
   "Link number out of range", },
{ /* 42 */
   "EUNATCH", MM_SOFT|MM_RECOVER|MM_OPSYS, MM_ERROR,
   "Protocol driver not attached", },
{ /* 43 */
   "ENOCSI", MM_SOFT|MM_RECOVER|MM_OPSYS, MM_ERROR,
   "No CSI structure available", },
{ /* 44 */
   "EL2HLT", MM_SOFT|MM_RECOVER|MM_OPSYS, MM_ERROR,
   "Level 2 halted", },
{ /* 45 */
   "EDEADLK", MM_SOFT|MM_RECOVER|MM_OPSYS, MM_ERROR,
   "Deadlock situation detected/avoided", },
{ /* 46 */
   "ENOLCK", MM_SOFT|MM_RECOVER|MM_OPSYS, MM_ERROR,
   "No record locks available", },
{ /* 47 */
   "ERROR47", MM_SOFT|MM_RECOVER|MM_OPSYS, MM_ERROR,
   "Error 47", },
{ /* 48 */
   "ERROR48", MM_SOFT|MM_RECOVER|MM_OPSYS, MM_ERROR,
   "Error 48", },
{ /* 49 */
   "ERROR49", MM_SOFT|MM_RECOVER|MM_OPSYS, MM_ERROR,
   "Error 49", },
{ /* 50 */
   "EBADE", MM_SOFT|MM_RECOVER|MM_OPSYS, MM_ERROR,
   "Bad exchange descriptor", },
{ /* 51 */
   "EBADR", MM_SOFT|MM_RECOVER|MM_OPSYS, MM_ERROR,
   "Bad request descriptor", },
{ /* 52 */
   "EXFULL", MM_SOFT|MM_RECOVER|MM_OPSYS, MM_ERROR,
   "Message tables full", },
{ /* 53 */
   "ENOINO", MM_SOFT|MM_RECOVER|MM_OPSYS, MM_ERROR,
   "Inode table overflow", },
{ /* 54 */
   "EBADRQC", MM_SOFT|MM_RECOVER|MM_OPSYS, MM_ERROR,
   "Bad request code", },
{ /* 55 */
   "EBADSLT", MM_SOFT|MM_RECOVER|MM_OPSYS, MM_ERROR,
   "Invalid slot", },
{ /* 56 */
   "EDEADLOCK", MM_SOFT|MM_RECOVER|MM_OPSYS, MM_ERROR,
   "File locking deadlock", },
{ /* 57 */
   "EBFONT", MM_SOFT|MM_RECOVER|MM_OPSYS, MM_ERROR,
   "Bad font file format", },
{ /* 58 */
   "ERROR58", MM_SOFT|MM_RECOVER|MM_OPSYS, MM_ERROR,
   "Error 58", },
{ /* 59 */
   "ERROR59", MM_SOFT|MM_RECOVER|MM_OPSYS, MM_ERROR,
   "Error 59", },
{ /* 60 */
   "ENOSTR", MM_SOFT|MM_RECOVER|MM_OPSYS, MM_ERROR,
   "Not a stream device", },
{ /* 61 */
   "ENODATA", MM_SOFT|MM_RECOVER|MM_OPSYS, MM_ERROR,
   "No data available", },
{ /* 62 */
   "ETIME", MM_SOFT|MM_RECOVER|MM_OPSYS, MM_ERROR,
   "Timer expired", },
{ /* 63 */
   "ENOSR", MM_SOFT|MM_RECOVER|MM_OPSYS, MM_ERROR,
   "Out of stream resources", },
{ /* 64 */
   "ENONET", MM_SOFT|MM_RECOVER|MM_OPSYS, MM_ERROR,
   "Machine is not on the network", },
{ /* 65 */
   "ENOPKG", MM_SOFT|MM_RECOVER|MM_OPSYS, MM_ERROR,
   "Package not installed", },
{ /* 66 */
   "EREMOTE", MM_SOFT|MM_RECOVER|MM_OPSYS, MM_ERROR,
   "Object is remote", },
{ /* 67 */
   "ENOLINK", MM_SOFT|MM_RECOVER|MM_OPSYS, MM_ERROR,
   "Link has been severed", },
{ /* 68 */
   "EADV", MM_SOFT|MM_RECOVER|MM_OPSYS, MM_ERROR,
   "Advertise error", },
{ /* 69 */
   "ESRMNT", MM_SOFT|MM_RECOVER|MM_OPSYS, MM_ERROR,
   "Srmount error", },
{ /* 70 */
   "ECOMM", MM_SOFT|MM_RECOVER|MM_OPSYS, MM_ERROR,
   "Communication error on send", },
{ /* 71 */
   "EPROTO", MM_SOFT|MM_RECOVER|MM_OPSYS, MM_ERROR,
   "Protocol error", },
{ /* 72 */
   "ERROR72", MM_SOFT|MM_RECOVER|MM_OPSYS, MM_ERROR,
   "Error 72", },
{ /* 73 */
   "ERROR73", MM_SOFT|MM_RECOVER|MM_OPSYS, MM_ERROR,
   "Error 73", },
{ /* 74 */
   "EMULTIHOP", MM_SOFT|MM_RECOVER|MM_OPSYS, MM_ERROR,
   "Multihop attempted", },
{ /* 75 */
   "ERROR75", MM_SOFT|MM_RECOVER|MM_OPSYS, MM_ERROR,
   "Error 75", },
{ /* 76 */
   "ERROR76", MM_SOFT|MM_RECOVER|MM_OPSYS, MM_ERROR,
   "Error 76", },
{ /* 77 */
   "EDOTDOT", MM_SOFT|MM_RECOVER|MM_OPSYS, MM_ERROR,
   "Not a data message", },
{ /* 78 */
   "ERROR78", MM_SOFT|MM_RECOVER|MM_OPSYS, MM_ERROR,
   "Error 78", },
{ /* 79 */
   "EBADMSG", MM_SOFT|MM_RECOVER|MM_OPSYS, MM_ERROR,
   "Error 79", },
{ /* 80 */
   "ENOTUNIQ", MM_SOFT|MM_RECOVER|MM_OPSYS, MM_ERROR,
   "Name not unique on network", },
{ /* 81 */
   "EBADFD", MM_SOFT|MM_RECOVER|MM_OPSYS, MM_ERROR,
   "File descriptor in bad state", },
{ /* 82 */
   "EREMCHG", MM_SOFT|MM_RECOVER|MM_OPSYS, MM_ERROR,
   "Remote address changed", },
{ /* 83 */
   "ELIBACC", MM_SOFT|MM_RECOVER|MM_OPSYS, MM_ERROR,
   "Can not access a needed shared library", },
{ /* 84 */
   "ELIBBAD", MM_SOFT|MM_RECOVER|MM_OPSYS, MM_ERROR,
   "Accessing a corrupted shared library", },
{ /* 85 */
   "ELIBSCN", MM_SOFT|MM_RECOVER|MM_OPSYS, MM_ERROR,
   ".lib section in a.out corrupted", },
{ /* 86 */
   "ELIBMAX", MM_SOFT|MM_RECOVER|MM_OPSYS, MM_ERROR,
   "Attempting to link in more shared libraries than system limit", },
{ /* 87 */
   "ELIBEXEC", MM_SOFT|MM_RECOVER|MM_OPSYS, MM_ERROR,
   "Can not exec a shared library directly", },
          /* not an errno error - added in */
{ /* 88 */
   "NO_FREE_STORE", MM_SOFT|MM_NRECOV|MM_OPSYS, MM_HALT,
   "Out of Free Store" },
{ /* 89 */
   "UNEXPECTED_ERROR", MM_SOFT|MM_NRECOV|MM_UTIL, MM_HALT,
   "This should not have happened",
   "Please Report this to the Developers" },
{ /* 90 */
   "NULL_POINTER", MM_SOFT|MM_NRECOV|MM_UTIL, MM_HALT,
   "A NULL pointer ((char *)0) was passed where a valid pointer was expected" },
{ /* 91 */
   "TRACE", MM_SOFT|MM_RECOVER|MM_APPL, MM_INFO,
   "trace message.",
   "No action is necessary." },
{ /* 92 */
   "NULL_STRING", MM_SOFT|MM_NRECOV|MM_UTIL, MM_HALT,
   "A NULL string (\"\") was passed where a non-NULL string was expected" }
   };
Error syserr(system_errors,NSYSERR); /* errno errors + some others*/

char *command="";

long TRACELEVEL = atol(getenv("TRACELEVEL") ? getenv("TRACELEVEL") : "0");
char *TRACEFILE = strdup(getenv("TRACEFILE") ? getenv("TRACEFILE") : "all");

const char *MAILER="/usr/bin/mailx"; /* mail command used for MM_MAIL errors */

const int NPRINT_ERROR_TO = 4;
/* The ordering of printErrorToStrings array must match the value of the
** print_error_to constants below.
** E.g. MM_STDERR equals 8, binary 1000, so bit three (0-based) is on, which
** corresponds to  "stderr" being the fourth string in printErrorToStrings.
*/
static const int MM_COMMAND=1, MM_CONSOLE=2, MM_MAIL=4, MM_STDERR=8;
static char *printErrorToStrings[NPRINT_ERROR_TO]
         = { "command","console","mail","stderr" };

const int NVERBOSITY = 5;
/* The Ordering of verbose_strings array must match the value of the verbosity
** constants specified below.
** E.g. MM_TAG equals 4, binary 0100, so bit two (0-based) is on, which
** corresponds to  "tag" being the third string in verbose_strings.
** VERBOSE is short hand for specifying all bits on.
*/
static const int MM_SEVERITY=1, MM_LABEL=2, MM_TAG=4, MM_TEXT=8, MM_ACTION=16;
static char *verbose_strings[NVERBOSITY]
         = { "severity","label","tag","text","action" };
static const int VERBOSE=MM_SEVERITY | MM_LABEL | MM_TAG | MM_TEXT | MM_ACTION;

/*                         Error::Error
** 
**  Initialize various class members and verify that the list of error
**  messages is not NULL.
**
**  OUTCOMES:
**    1. When errlist is NULL
**        a. abort()
**        b. When you return from abort() (i.e. SIGABRT is trapped)
**             exit non-zero
**    2. Initialize non-static class members
**    3. When this is the first Error object created
**           initialize static class members
**    4. When this is a subsequent Error object
**           do NOT re-initialize static members
*/
Error::Error(const Error_message *const errlist,const unsigned nerrs)
      : errorList(errlist), maxErrs(nerrs)
{
static Error_message nullErrListErr =
   { "E_NULL_ERRLIST", MM_SOFT|MM_NRECOV|MM_UTIL, MM_HALT,
     "NULL errlist parameter",
     "PROGRAMMER: look at call to constructor Error::Error" };

if( errlist == (Error_message *) NULL)          /* abort if errlist is NULL */
   {
   char *lbl = newLabel(__FILE__,__LINE__);
   writeError(&nullErrListErr,stderr,VERBOSE,lbl,"Error constructor failed");
   delete lbl;
   abort();
   exit(111);
   }
if (!initialized++)
   staticInitializer();
errno = -1;
}

/*                      Error::~Error()
**
**  OUTCOMES:
**   1. When initialized is greater than 0
**        decrement initialized,
**        do not deallocate or close anything.
**   2. When initialized is 0 or less
**        deallocate and close static pointers
*/
Error::~Error()
{
if (--initialized <= 0)
   {
   if (mailUsers)
      {
      free(mailUsers);
      mailUsers = (char *) 0;
      }
   if (console_device)
      {
      delete console_device;
      console_device = (char *)0;
      }
   if (errorCmdPipe)
      {
      pclose(errorCmdPipe);
      errorCmdPipe = (FILE *)0;
      }
   fclose(console);
   }
}

/*                      Error::staticInitializer()
**
**   Initialize the various static Error class members.
**
**  OUTCOMES:
**    1. Initialize the IFS environment variable to space, tab & newline.
**    2. When the environment does specify where errors are to be printed
**          set printing to the specified places.
**    3. When the environment specifies invalid print locations,
**          ignore the invalid locations.
**    4. When the environment does NOT specify where errors are to be printed
**          set printing to stderr.
**    5. When command printing is specified:
**          a. When the error command is not in the environment
**                generate no error command error,
**                remove command printing and continue.
**          b. When the error command does not begin with a slash
**                specify bad error command error and exit.
**          c. When opening of error command fails,
**                invoke perror() and exit
**          d. When the error command is opened,
**                initialize the command verbosity variable.
**    6. When console printing is specified:
**          a. When console device name is in the environment
**                save its value for printing
**          b. When console device name is not in the environment
**                set the default name to "/dev/console"
**          c. When the console device is not openable
**                generate NO_CONSOLE and exit.
**          d. When console device is not writeable
**                invoke perror() and exit
**          e. When console device has a file descriptor less than 3
**                change it to be 3 or higher
**          f. When the console device is open
**                Turn the console device file descriptor into a FILE ptr &
**                initialize the console device verbosity variable.
**    7. When mail printing is specified:
**          initialize the list of mail users to the current user &
**          initialize the mail verbosity variable
**    8. When stderr printing is specified:
**          initialize the standard error verbosity variable
*/
void Error::staticInitializer()
{
char *delim=(char *)0, *envValue=(char *)0, *item=(char *)0, *string=(char *)0;

static const char *const IFS = "IFS= \t\n";
putenv(IFS);               /* to protect popens from hacking games with IFS */

printErrorTo = 0;
if ( envValue=getenv("PRINT_ERROR_TO") )
   {      /* turn on bits corresponding to strings found in PRINT_ERROR_TO */
   string = strdup(envValue);
   char *addrToFree = string;
   for ( delim = ":"; item=strtok(string,delim); string=NULL )
      for ( int i=0; i < NPRINT_ERROR_TO; i++ )
         if ( strcmp(item,printErrorToStrings[i]) == LEXEQ )
            printErrorTo |= (1 << i);
   free(addrToFree);
   }
if (printErrorTo == 0)
   printErrorTo = MM_STDERR;      /* default if not set from environment */

char *lbl = newLabel(__FILE__,__LINE__);
if (printErrorTo & MM_COMMAND)
   {
   if ( (errorCmdStr=getenv("ERRORCMD")) )
      {
      if (errorCmdStr[0] != '/')
         {
         static Error_message badErrCmdListErr =
            { "E_BAD_ERRCMD", MM_SOFT|MM_NRECOV|MM_UTIL, MM_HALT,
              "ERRORCMD is not a fully qualified pathname",
              "PROGRAMMER: ERRORCMD must be a fully qualified pathname"
            };
         writeError(&badErrCmdListErr,stderr,VERBOSE,lbl
                           ,form("ERRORCMD is '%s'.",errorCmdStr));
         abort();
         exit(112);
         }
      if ((errorCmdPipe = popen(errorCmdStr,"w")) == NULL)
         {
         perror("Error::staticInitializer: popen() failure:");
         abort();
         exit(113);
         }
      else
         cmdverb = getverb("CMDVERB");
      }
   else                      /* ERRORCMD not in the environment */
      {
      static Error_message noErrCmdListErr =
         { "E_NO_ERRCMD", MM_SOFT|MM_NRECOV|MM_UTIL, MM_INFO,
           "'command' specified in PRINT_ERROR_TO, but no ERRORCMD specified.",
           "PROGRAMMER: set and export ERRORCMD, or take out 'command'"
         };
       writeError(&noErrCmdListErr,stderr,VERBOSE,lbl
                        ,"Execution will continue with 'command' turned off");
      printErrorTo &= ~MM_COMMAND;  /* turn off printing to the command */
      if (printErrorTo == 0)
         printErrorTo = MM_STDERR;   /* default to stderr if nothing else set */
      }
   }

if (printErrorTo & MM_CONSOLE)
   {
   if ( string=getenv("CONSOLE_DEV") )
      {
      console_device = new char[strlen(string) +1];
      strcpy(console_device, string);
      }
   else              
      {
      console_device = new char[strlen("/dev/console") +1];
      strcpy(console_device, "/dev/console");
      }
   unsigned preserveAlarm = alarm(10);      /* Necessary if console_device */
   otrap = sigset(SIGALRM,&Error::errexit); /* is turned off or unplugged. */
   int tmpFd=-1;
   if ( (tmpFd = open(console_device, O_WRONLY)) < 3 )
      {                       /* Want to avoid stdin, stdout, and stderr. */
      if (tmpFd < 0)
         {
         perror("Error::staticInitializer: open() failure:");
         abort();
         exit(114);
         }
      int preserveFd = tmpFd;
      if ( (tmpFd = fcntl(tmpFd, F_DUPFD, 3)) < 3 )
         {
         perror("Error::staticInitializer: fcntl() failure:");
         abort();
         exit(115);
         }
      close(preserveFd);
      }
   console = fdopen(tmpFd, "w");
   setbuf(console,(char *)0);
   converb = getverb("CONVERB");
   sigset(SIGALRM,otrap);
   alarm(preserveAlarm);
   }

if (printErrorTo & MM_MAIL)
   {
   mailUsers = strdup(getpwuid(getuid())->pw_name);
   mailverb = getverb("MAILVERB");
   }

if (printErrorTo & MM_STDERR)
   stderrverb = getverb("STDERRVERB");

delete lbl;
lbl = (char *)0;
}

/*                  Error::getverb()
**
**     Get the specified variable from the environment and parse
**     it for the verbosity strings.  Return the verbosity to the
**     calling function.
**
**   OUTCOMES:
**     1. When the specified variable is not in the environment or is NULL
**           return a verbosity of everything.
**     2. When the specified variable is in the environment
**           a. convert the verbosity strings to bits
**           b. ignore invalid verbosity strings
**           c. ignore duplication of verbosity strings
**           d. return the specified verbosity bits, or 
**           e. When all of the verbosity strings are invalid
**                 return a verbosity of everything
*/
int Error::getverb(char *verb)
{
char *delim=(char *)0, *envValue=(char *)0, *item=(char *)0, *string=(char *)0;
int rc=0;

      /* turn on bits corresponding to verbose strings in verb */
if ( envValue=getenv(verb) )
   {
   string = strdup(envValue);
   char *addrToFree = string;
   for ( delim = ":"; item=strtok(string,delim); string=NULL )
      for ( int i=0; i < NVERBOSITY; i++ )
         if ( strcmp(item,verbose_strings[i]) == LEXEQ )
            rc |= (1 << i);
   free(addrToFree);
   }
return (rc ? rc : VERBOSE);
}

/*                     Error::error
**
**   Generate the specified error message based on the initialized statics.
**   The arguments file, line & suffix are assumed to be valid
**
**  OUTCOMES:
**   1. When specified error number is known
**        initialize the error message to the error message.
**   2. When specified error number is not known
**        initialize the error message to be the unknown error message.
**   3. Print the error to the specified location(s).
**   4. When the error specifies HALT
**        abort & exit non-zero
**   5. Otherwise
**        return FALSE.
*/
Boolean_t Error::error(const unsigned errnum, const char *file,
                       const unsigned line,   const char *suffix)
{
static Error_message unknown_error =
   { "E_UNKNOWN_ERROR", MM_SOFT|MM_RECOVER|MM_UTIL, MM_ERROR,
     "Unknown error number specified",
     "PROGRAMMER: look at call to Error::error()" };

errno = (int) errnum;
lasterr = this;

Error_message *errorMsg;
if ( errno < maxErrs )
   errorMsg = (Error_message *) &errorList[errno];
else
   errorMsg = &unknown_error;

char *lbl = newLabel(file,line);

if ( printErrorTo & MM_STDERR )
   writeError(errorMsg,stderr,stderrverb,lbl,suffix);

if ( printErrorTo & MM_CONSOLE)
   writeError(errorMsg,console,converb,lbl,suffix);

if ( printErrorTo & MM_MAIL )
   {
   FILE *mailerFp;
   if ( (mailerFp = popen(form("%s %s",MAILER,mailUsers),"w")) == NULL )
      {
      perror("Error::error: popen() failed");
      fprintf(stderr,"popen failed to open \"%s %s\"",MAILER,mailUsers);
      }
   else
      writeError(errorMsg,mailerFp,mailverb,lbl,suffix);
   pclose(mailerFp);
   }

if ( printErrorTo & MM_COMMAND)
   {
   SIG_PF previousTrap = sigset(SIGPIPE,&Error::pipeTrap);
   writeError(errorMsg,errorCmdPipe,cmdverb,lbl,suffix);
   sigset (SIGPIPE,previousTrap);
   }

if ( errorMsg->severity & MM_HALT )
   {
   abort();
   exit(116);
   }

delete lbl;                                 /* clean up */
lbl = (char *)0;
return FALSE;
}

/*              Error::writeError
**
**   Print the error message, to the file pointer, based on the verbosity.
**
**  OUTCOMES:
**    1. When the verbosity includes a portion of the error message,
**       and that portion is available,
**          print that portion of the error message.
**    2. When the verbosity includes a portion of the error message,
**       and that portion is NOT available,
**          leave off that portion of the error message.
*/
void Error::writeError(const Error_message *errMsg, FILE *fp, int verb,
                       const char *label, const char *suffix)
{
const int NSEVERITY = 5;
/* The order of this array MUST match the SEVERITY constants in error.dd
** E.g. MM_NOSEV equals 1, binary 0001, so bit zero is on, which corresponds
** to "tag" being the first string in verbose_strings.
*/
static char *severity_strings[NSEVERITY]
        = { "No Severity","Halt","Error","Warning","Information" };
int severityIndex=0;
for ( severityIndex = NSEVERITY-1;   /* calculate index into severity_strings */
      severityIndex && !( errMsg->severity & (1<<severityIndex) );
      severityIndex-- )
   ; /* severityIndex becomes severity level string (highest if more than 1) */

char *separator="";
Boolean_t newline = FALSE;
if ( (verb & MM_TAG) && errMsg->tag && errMsg->tag[0] )
   {
   fprintf(fp,"%s",errMsg->tag);
   separator = " - ";
   newline = TRUE;
   }
if ( verb & MM_SEVERITY ) 
   {
   fprintf(fp,"%s%s",separator,severity_strings[severityIndex]);
   newline = TRUE;
   }
if (newline)
   fprintf(fp,"\n");

if ( verb & MM_LABEL )
   {
   if (label && label[0])
      fprintf(fp,"%s\n",label);
   if (errorId && errorId[0])
      fprintf(fp,"<%s>\n",errorId);
   }

if ( verb & MM_TEXT )
   {
   if (errMsg->text && errMsg->text[0])
      fprintf(fp,"%s\n",errMsg->text);
   if (suffix && suffix[0])
      fprintf(fp,"<%s>\n",suffix);
   }

if ( (verb & MM_ACTION) && errMsg->action && errMsg->action[0] )
   fprintf(fp,"TO FIX: %s\n",errMsg->action);

fprintf(fp,"\n");                            /* blank line after error msg */
fflush(fp);
}

/*                Error::errFile
**
**  Associate file descriptor 2 with the filename in the argument.
**  Open the file for appending & creation.
** 
**  OUTCOMES:
**    1. When the open fails
**         generate a ::errno error and return FALSE
**    2. When open is successful
**         change the file descriptor to 2 with fcntl
**    3. When fcntl fails
**         generate UNEXPECTED_ERROR and return FALSE
**    4. Otherwise
**         return TRUE
*/
Boolean_t Error::errFile(const char *err_file)
{
int fd=-1;
::errno=0;
if ( (fd=open(err_file, O_WRONLY|O_APPEND|O_CREAT, 0666)) == -1 )
   return syserr.error(::errno,__FILE__,__LINE__,err_file);
else if (fd != 2)
   {                 /* open could have given us anything */
   ::errno=0;
   close(2);
   int preservefd = fd;
   if ( (fd = fcntl(fd,F_DUPFD,2)) != 2)
      {
      close(preservefd);
      return syserr.error(UNEXPECTED_ERROR,__FILE__,__LINE__,
                       form("fcntl returned %d, should have returned 2",fd));
      }
   else
      close(preservefd);
   }
return TRUE;
}

/*               Error::identifier
**
**  OUTCOMES:
**    1. When static error identifier has a value
**         deallocate it & set static identifier to NULL.
**    2. When the error identifier argument is NULL
**         set static error identifier to NULL
**    3. When the error identifier argument is not NULL
**         assign its value to the static error identifier
*/
void Error::identifier(const char *errId)
{
   if (errorId)
      {
      free (errorId);
      errorId = (char *)0;
      }
   if (errId)
      errorId = strdup(errId);
}

/*                           Error::mailTo
**
**   Associate the list of users in the argument with the static list
**   of mail users.
**
** OUTCOMES:
**   1. When the list of addressees is a NULL Pointer
**        generate the NULL_POINTER error and return.
**   2. When the list of addresses is not a NULL Pointer:
**      a. When there are already some mail users on the list
**           deallocate the old list
**      b. Allocate a new list
**      c. copy the mail users into the new list
*/
void Error::mailTo(const char *addressees)
{
if (addressees)
   {
   if (mailUsers)
      {
      delete mailUsers;
      mailUsers = (char *)0;
      }
   mailUsers = new char[strlen(addressees) +1];
   strcpy(mailUsers,(char *)addressees);
   }
else
   syserr.error(NULL_POINTER,__FILE__,__LINE__);
}

/*            Error::errexit
**
**  OUTCOMES:
**    1. Generate the no console error
**    2. When there are other traps stacked up
**         execute them
**    3. If the other traps return
**         exit with the signal number
*/
void Error::errexit(int signo)
{
static Error_message noConsoleDevListErr =
   { "E_NO_CONSOLE_DEV", MM_SOFT|MM_NRECOV|MM_UTIL, MM_HALT,
     "Device specified in CONSOLE_DEV is not open(2)able",
     "SYSTEM ADMINISTRATOR: check accessiblity of CONSOLE_DEV"
   };
char *lbl = newLabel(__FILE__,__LINE__);
writeError(&noConsoleDevListErr,stderr,VERBOSE,lbl,
                                      form("CONSOLE_DEV = %s",console_device));
delete lbl;
if ((otrap!=SIG_ERR) &&(otrap!=SIG_DFL) &&(otrap!=SIG_HOLD) &&(otrap!=SIG_IGN))
   (*otrap)(signo);
exit(signo);
}

/*            Error::pipeTrap
**
**  OUTCOMES:
**    1. Generate a broken pipe error
**    2. turn off printing of errors to command
**    3. set the command verbosity to 0
**    4. close the command pipe
**    5. set the name of the error command to the NULL string
*/
void Error::pipeTrap(int signo)
{
(void) signo;
static Error_message brokenPipeErr =
   { "E_BROKEN_PIPE", MM_SOFT|MM_RECOVER|MM_UTIL, MM_ERROR,
     "Closing broken ERRORCMD pipe, & turning off command printing of errors"
   };
char *lbl = newLabel(__FILE__,__LINE__);
writeError(&brokenPipeErr,stderr,VERBOSE,lbl,form("ERRORCMD = %s",errorCmdStr));
delete lbl;
printErrorTo &= ~MM_COMMAND;
cmdverb = 0;
pclose(errorCmdPipe);
errorCmdPipe = (FILE *)0;
errorCmdStr = "";
}

/*    
** timeStrLen's value is dependent on the value of formatStr. formatStr
** determines the number of characters that strftime or cftime will produce.
** timeStrLen must be that number of characters +1 for NULL. 
*/ 
char *Error::timeStr()
{
static const char *formatStr = "%D %T";
static const int timeStrLen = 18;
static char timeStr[timeStrLen];

timeStr[0] = '\0';
time_t curtime = time( (long *)0 );
#if sun
(void) strftime(timeStr, timeStrLen, formatStr, localtime(&curtime));
#else
(void) cftime(timeStr, formatStr, &curtime);
#endif
return timeStr;
}

/*              Error::newLabel()
**
**    newLabel generates the error message label.  It allocates
**    the space for the new label, but it is up to the calling function
**    to deallocate the space.  This function keeps the space calculation
**    and the static error in one place rather than sprinkled in the code.
**
**  OUTCOMES:
**    1. When the arguments are not specified,
**         use the defaults __FILE__ & __LINE__
**    2. When the calculated length does not equal the number of bytes copied
**         generate E_BAD_LENGTH error & abort & exit  (unexpected)
**    3. When the lengths are equal
**         return the newly allocated area
*/
char *Error::newLabel(const char *fileName, const unsigned line)
{
/*
**  Be sure that all of the literals in the string being sprintf'ed
**  are counted as part of lblLen.
*/
char file[fileNameLen];
(void) basename(fileName,file);
int lblLen = strlen(command) + strlen(file) + strlen(form("%d",line))
               + strlen(timeStr()) +5 /*(:)bb*/ +4 /*PID=*/ +5 /*pid*/; 
char *lbl = new char[lblLen + 1 /*NULL*/];
int sprintfRc = sprintf(lbl,"%s(%s:%d) %s PID=%d",
                                  command,file,line,timeStr(),getpid());
if ( sprintfRc > lblLen )
   {  
   static Error_message badLengthsListErr =
      { "E_BAD_LENGTH", MM_SOFT|MM_NRECOV|MM_UTIL, MM_HALT,
        "label length should be equal to sprintf return value."
        "PROGRAMMER: Be sure all the literals in the string are counted."
      }; 
   writeError(&badLengthsListErr,stderr,VERBOSE,lbl,
                   form("lblLen is %d, sprintf returned %d",lblLen,sprintfRc));
   abort();
   exit(117);
   }
return lbl;
}
