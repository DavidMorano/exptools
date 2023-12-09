# @(#)quickinfo.sh	1.4
# This works only with ksh. We NEED to use the "print -r" used below instead of using "echo",
# which tries to interpret escape sequences.
while read name rest
do
	print -r "$rest" |
	dbadd quickinfo $name
done <<"</FoO ThE bAr/>"
ACS_BBSS	curses.h:#define ACS_BBSS (acs_map['k'])
ACS_BLOCK	curses.h:#define ACS_BLOCK (acs_map['0']) /* solid square block */
ACS_BOARD	curses.h:#define ACS_BOARD (acs_map['h']) /* board of squares */
ACS_BSBS	curses.h:#define ACS_BSBS (acs_map['q'])
ACS_BSSB	curses.h:#define ACS_BSSB (acs_map['l'])
ACS_BSSS	curses.h:#define ACS_BSSS (acs_map['w'])
ACS_BTEE	curses.h:#define ACS_BTEE ACS_SSBS
ACS_BULLET	curses.h:#define ACS_BULLET (acs_map['~']) /* bullet */
ACS_CKBOARD	curses.h:#define ACS_CKBOARD (acs_map['a']) /* checker board (stipple) */
ACS_DARROW	curses.h:#define ACS_DARROW (acs_map['.']) /* arrow pointing down */
ACS_DEGREE	curses.h:#define ACS_DEGREE (acs_map['f']) /* degree symbol */
ACS_DIAMOND	curses.h:#define ACS_DIAMOND (acs_map['`']) /* diamond */
ACS_HLINE	curses.h:#define ACS_HLINE ACS_BSBS
ACS_LANTERN	curses.h:#define ACS_LANTERN (acs_map['i']) /* lantern symbol */
ACS_LARROW	curses.h:#define ACS_LARROW (acs_map[',']) /* arrow pointing left */
ACS_LLCORNER	curses.h:#define ACS_LLCORNER ACS_SSBB
ACS_LRCORNER	curses.h:#define ACS_LRCORNER ACS_SBBS
ACS_LTEE	curses.h:#define ACS_LTEE ACS_SSSB
ACS_PLMINUS	curses.h:#define ACS_PLMINUS (acs_map['g']) /* plus/minus */
ACS_PLUS	curses.h:#define ACS_PLUS ACS_SSSS
ACS_RARROW	curses.h:#define ACS_RARROW (acs_map['+']) /* arrow pointing right */
ACS_RTEE	curses.h:#define ACS_RTEE ACS_SBSS
ACS_S1	curses.h:#define ACS_S1 (acs_map['o']) /* scan line 1 */
ACS_S9	curses.h:#define ACS_S9 (acs_map['s']) /* scan line 9 */
ACS_SBBS	curses.h:#define ACS_SBBS (acs_map['j'])
ACS_SBSB	curses.h:#define ACS_SBSB (acs_map['x'])
ACS_SBSS	curses.h:#define ACS_SBSS (acs_map['u'])
ACS_SSBB	curses.h:#define ACS_SSBB (acs_map['m'])
ACS_SSBS	curses.h:#define ACS_SSBS (acs_map['v'])
ACS_SSSB	curses.h:#define ACS_SSSB (acs_map['t'])
ACS_SSSS	curses.h:#define ACS_SSSS (acs_map['n'])
ACS_TTEE	curses.h:#define ACS_TTEE ACS_BSSS
ACS_UARROW	curses.h:#define ACS_UARROW (acs_map['-']) /* arrow pointing up */
ACS_ULCORNER	curses.h:#define ACS_ULCORNER ACS_BSSB
ACS_URCORNER	curses.h:#define ACS_URCORNER ACS_BBSS
ACS_VLINE	curses.h:#define ACS_VLINE ACS_SBSB
ARG_MAX	limits.h:#define ARG_MAX 5120 /* max length of arguments to exec */
A_ALTCHARSET	curses.h:#define A_ALTCHARSET 000100000000L
A_ATTRIBUTES	curses.h:#define A_ATTRIBUTES 037777600000L /* 0xFFFF0000 */
A_BLINK	curses.h:#define A_BLINK 000002000000L
A_BOLD	curses.h:#define A_BOLD 000010000000L
A_CHARTEXT	curses.h:#define A_CHARTEXT 000000177777L /* 0x0000FFFF */
A_DIM	curses.h:#define A_DIM 000004000000L
A_INVIS	curses.h:#define A_INVIS 000020000000L
A_NORMAL	curses.h:#define A_NORMAL 000000000000L
A_PROTECT	curses.h:#define A_PROTECT 000040000000L
A_REVERSE	curses.h:#define A_REVERSE 000001000000L
A_STANDOUT	curses.h:#define A_STANDOUT 000000200000L
A_UNDERLINE	curses.h:#define A_UNDERLINE 000000400000L
B0	sys/termio.h:#define B0 0
B110	sys/termio.h:#define B110 0000003
B1200	sys/termio.h:#define B1200 0000011
B134	sys/termio.h:#define B134 0000004
B150	sys/termio.h:#define B150 0000005
B1800	sys/termio.h:#define B1800 0000012
B19200	sys/termio.h:#define B19200 0000016
B200	sys/termio.h:#define B200 0000006
B2400	sys/termio.h:#define B2400 0000013
B300	sys/termio.h:#define B300 0000007
B38400	sys/termio.h:#define B38400 0000017
B4800	sys/termio.h:#define B4800 0000014
B50	sys/termio.h:#define B50 0000001
B600	sys/termio.h:#define B600 0000010
B75	sys/termio.h:#define B75 0000002
B9600	sys/termio.h:#define B9600 0000015
BITS	values.h:#define BITS(type) (BITSPERBYTE * (int)sizeof(type))
BITSPERBYTE	values.h:#define BITSPERBYTE 8
BRKINT	sys/termio.h:#define BRKINT 0000002
BS0	sys/termio.h:#define BS0 0
BS1	sys/termio.h:#define BS1 0020000
BSDLY	sys/termio.h:#define BSDLY 0020000
BUFSIZ	stdio.h:#define BUFSIZ ???? 1024
CBACK	regexp.h:#define CBACK 36
CBAUD	sys/termio.h:#define CBAUD 0000017
CBRA	regexp.h:#define CBRA 2
CCEOF	regexp.h:#define CCEOF 22
CCHR	regexp.h:#define CCHR 4
CCL	regexp.h:#define CCL 12
CDLIMIT	sys/param.h:#define CDLIMIT (1L<<11) /* default max write address */
CDOL	regexp.h:#define CDOL 20
CDOT	regexp.h:#define CDOT 8
CHAR_BIT	limits.h:#define CHAR_BIT 8 /* # of bits in a "char" */
CHAR_MAX	limits.h:#define CHAR_MAX 255 /* max integer value of a "char" */
CHAR_MIN	limits.h:#define CHAR_MIN 0 /* min integer value of a "char" */
CHILD_MAX	limits.h:#define CHILD_MAX 25 /* max # of processes per user id */
CKET	regexp.h:#define CKET 24
CLK_TCK	limits.h:#define CLK_TCK 100 /* # of clock ticks per second */
CLOCAL	sys/termio.h:#define CLOCAL 0004000
CR0	sys/termio.h:#define CR0 0
CR1	sys/termio.h:#define CR1 0001000
CR2	sys/termio.h:#define CR2 0002000
CR3	sys/termio.h:#define CR3 0003000
CRDLY	sys/termio.h:#define CRDLY 0003000
CREAD	sys/termio.h:#define CREAD 0000200
CS5	sys/termio.h:#define CS5 0
CS6	sys/termio.h:#define CS6 0000020
CS7	sys/termio.h:#define CS7 0000040
CS8	sys/termio.h:#define CS8 0000060
CSIZE	sys/termio.h:#define CSIZE 0000060
CSTOPB	sys/termio.h:#define CSTOPB 0000100
CUR	term.h:#define CUR cur_term->
CURB	term.h:#define CURB cur_bools->
CURN	term.h:#define CURN cur_nums->
CURS	term.h:#define CURS cur_strs->
CXCL	regexp.h:#define CXCL 16
C_DEFUNCT	sys/jioctl.h:#define C_DEFUNCT 6 /* Send terminate signal to proc. group */
C_DELETE	sys/jioctl.h:#define C_DELETE 4 /* Delete layer process group */
C_EXIT	sys/jioctl.h:#define C_EXIT 5 /* Exit */
C_NEW	sys/jioctl.h:#define C_NEW 2 /* Create new layer process group */
C_RESHAPE	sys/jioctl.h:#define C_RESHAPE 8 /* Layer has been reshaped */
C_RUN	sys/jioctl.h:#define C_RUN 9 /* Run command in layer */
C_SENDCHAR	sys/jioctl.h:#define C_SENDCHAR 1 /* Send character to layer process */
C_SENDNCHARS	sys/jioctl.h:#define C_SENDNCHARS 7 /* Send several characters to layer proc. */
C_UNBLK	sys/jioctl.h:#define C_UNBLK 3 /* Unblock layer process */
DBL_DIG	limits.h:#define DBL_DIG 15 /* digits of precision of a "double" */
DBL_MAX	limits.h:#define DBL_MAX 1.79769313486231470e+308 /*max decimal value of a "double"*/
DBL_MIN	limits.h:#define DBL_MIN 4.94065645841246544e-324 /*min decimal value of a "double"*/
DEBUG	macros.h:#define DEBUG(variable,type) fprintf(stderr,"variable = %type\n",variable)
DEFAULT	strselect.h:#define DEFAULT } else WoRD(/)WoRD(*) WoRD(*)WoRD(/) {
DIOC	sys/ioctl.h:#define DIOC ('d'<<8)
DIOCGETB	sys/ioctl.h:#define DIOCGETB (DIOC|2)
DIOCGETC	sys/ioctl.h:#define DIOCGETC (DIOC|1)
DIOCSETE	sys/ioctl.h:#define DIOCSETE (DIOC|3)
DMAXEXP	values.h:#define DMAXEXP ((1 << _DEXPLEN - 1) - 1 + _IEEE)
DMAXPOWTWO	values.h:#define DMAXPOWTWO ((double)(1L << BITS(long) - 2) * \
DMINEXP	values.h:#define DMINEXP (-(DMAXEXP + DSIGNIF - _HIDDENBIT - 3))
DSIGNIF	values.h:#define DSIGNIF (BITS(double) - _DEXPLEN + _HIDDENBIT - 1)
E2BIG	sys/errno.h:#define E2BIG 7 /* Arg list too long */
EACCES	sys/errno.h:#define EACCES 13 /* Permission denied */
EADV	sys/errno.h:#define EADV 68 /* advertise error */
EAGAIN	sys/errno.h:#define EAGAIN 11 /* No more processes */
EBADE	sys/errno.h:#define EBADE 50 /* invalid exchange */
EBADF	sys/errno.h:#define EBADF 9 /* Bad file number */
EBADFD	sys/errno.h:#define EBADFD 81 /* f.d. invalid for this operation */
EBADMSG	sys/errno.h:#define EBADMSG 77 /* trying to read unreadable message */
EBADR	sys/errno.h:#define EBADR 51 /* invalid request descriptor */
EBADRQC	sys/errno.h:#define EBADRQC 54 /* invalid request code */
EBADSLT	sys/errno.h:#define EBADSLT 55 /* invalid slot */
EBFONT	sys/errno.h:#define EBFONT 57 /* bad font file fmt */
EBUSY	sys/errno.h:#define EBUSY 16 /* Mount device busy */
ECHILD	sys/errno.h:#define ECHILD 10 /* No children */
ECHO	sys/termio.h:#define ECHO 0000010
ECHOE	sys/termio.h:#define ECHOE 0000020
ECHOK	sys/termio.h:#define ECHOK 0000040
ECHONL	sys/termio.h:#define ECHONL 0000100
ECHRNG	sys/errno.h:#define ECHRNG 37 /* Channel number out of range */
ECOMM	sys/errno.h:#define ECOMM 70 /* Communication error on send */
EDEADLK	sys/errno.h:#define EDEADLK 45 /* Deadlock condition. */
EDEADLOCK	sys/errno.h:#define EDEADLOCK 56 /* file locking deadlock error */
EDOM	sys/errno.h:#define EDOM 33 /* Math arg out of domain of func */
EDOTDOT	sys/errno.h:#define EDOTDOT 76 /* Cross mount point (not really error)*/
EEXIST	sys/errno.h:#define EEXIST 17 /* File exists */
EFAULT	sys/errno.h:#define EFAULT 14 /* Bad address */
EFBIG	sys/errno.h:#define EFBIG 27 /* File too large */
EIDRM	sys/errno.h:#define EIDRM 36 /* Identifier removed */
EINTR	sys/errno.h:#define EINTR 4 /* interrupted system call */
EINVAL	sys/errno.h:#define EINVAL 22 /* Invalid argument */
EIO	sys/errno.h:#define EIO 5 /* I/O error */
EISDIR	sys/errno.h:#define EISDIR 21 /* Is a directory */
EL2HLT	sys/errno.h:#define EL2HLT 44 /* Level 2 halted */
EL2NSYNC	sys/errno.h:#define EL2NSYNC 38 /* Level 2 not synchronized */
EL3HLT	sys/errno.h:#define EL3HLT 39 /* Level 3 halted */
EL3RST	sys/errno.h:#define EL3RST 40 /* Level 3 reset */
ELIBACC	sys/errno.h:#define ELIBACC 83 /* Can't access a needed shared lib. */
ELIBBAD	sys/errno.h:#define ELIBBAD 84 /* Accessing a corrupted shared lib. */
ELIBEXEC	sys/errno.h:#define ELIBEXEC 87 /* Attempting to exec a shared library. */
ELIBMAX	sys/errno.h:#define ELIBMAX 86 /* Attempting to link in too many libs. */
ELIBSCN	sys/errno.h:#define ELIBSCN 85 /* .lib section in a.out corrupted. */
ELNRNG	sys/errno.h:#define ELNRNG 41 /* Link number out of range */
EMFILE	sys/errno.h:#define EMFILE 24 /* Too many open files */
EMLINK	sys/errno.h:#define EMLINK 31 /* Too many links */
EMULTIHOP	sys/errno.h:#define EMULTIHOP 74 /* multihop attempted */
ENDSEL	strselect.h:#define ENDSEL } WoRD(/)WoRD(*) WoRD(*)WoRD(/) }
ENFILE	sys/errno.h:#define ENFILE 23 /* File table overflow */
ENOANO	sys/errno.h:#define ENOANO 53 /* no anode */
ENOCSI	sys/errno.h:#define ENOCSI 43 /* No CSI structure available */
ENODATA	sys/errno.h:#define ENODATA 61 /* no data (for no delay io) */
ENODEV	sys/errno.h:#define ENODEV 19 /* No such device */
ENOENT	sys/errno.h:#define ENOENT 2 /* No such file or directory */
ENOEXEC	sys/errno.h:#define ENOEXEC 8 /* Exec format error */
ENOLCK	sys/errno.h:#define ENOLCK 46 /* No record locks available. */
ENOLINK	sys/errno.h:#define ENOLINK 67 /* the link has been severed */
ENOMEM	sys/errno.h:#define ENOMEM 12 /* Not enough core */
ENOMSG	sys/errno.h:#define ENOMSG 35 /* No message of desired type */
ENONET	sys/errno.h:#define ENONET 64 /* Machine is not on the network */
ENOPKG	sys/errno.h:#define ENOPKG 65 /* Package not installed */
ENOSPC	sys/errno.h:#define ENOSPC 28 /* No space left on device */
ENOSR	sys/errno.h:#define ENOSR 63 /* out of streams resources */
ENOSTR	sys/errno.h:#define ENOSTR 60 /* Device not a stream */
ENOTBLK	sys/errno.h:#define ENOTBLK 15 /* Block device required */
ENOTDIR	sys/errno.h:#define ENOTDIR 20 /* Not a directory */
ENOTTY	sys/errno.h:#define ENOTTY 25 /* Not a typewriter */
ENOTUNIQ	sys/errno.h:#define ENOTUNIQ 80 /* given log. name not unique */
ENXIO	sys/errno.h:#define ENXIO 6 /* No such device or address */
EOF	stdio.h:#define EOF (-1)
EPERM	sys/errno.h:#define EPERM 1 /* Not super-user */
EPIPE	sys/errno.h:#define EPIPE 32 /* Broken pipe */
EPROTO	sys/errno.h:#define EPROTO 71 /* Protocol error */
ERANGE	sys/errno.h:#define ERANGE 34 /* Math result not representable */
EREMCHG	sys/errno.h:#define EREMCHG 82 /* Remote address changed */
EREMOTE	sys/errno.h:#define EREMOTE 66 /* The object is remote */
EROFS	sys/errno.h:#define EROFS 30 /* Read only file system */
ERRABORT	macros.h:#define ERRABORT() _error() { abort(); }
ESPIPE	sys/errno.h:#define ESPIPE 29 /* Illegal seek */
ESRCH	sys/errno.h:#define ESRCH 3 /* No such process */
ESRMNT	sys/errno.h:#define ESRMNT 69 /* srmount error */
ETIME	sys/errno.h:#define ETIME 62 /* timer expired */
ETXTBSY	sys/errno.h:#define ETXTBSY 26 /* Text file busy */
EUNATCH	sys/errno.h:#define EUNATCH 42 /* Protocol driver not attached */
EXDEV	sys/errno.h:#define EXDEV 18 /* Cross-device link */
EXFULL	sys/errno.h:#define EXFULL 52 /* exchange full */
EXTA	sys/termio.h:#define EXTA 0000016
EXTB	sys/termio.h:#define EXTB 0000017
FAPPEND	sys/file.h:#define FAPPEND 0x08
FCHR_MAX	limits.h:#define FCHR_MAX 1048576 /* max size of a file in bytes */
FCREAT	sys/file.h:#define FCREAT 0x100
FEOF	ldfcn.h:#define FEOF(ldptr) feof(IOPTR(ldptr))
FERROR	ldfcn.h:#define FERROR(ldptr) ferror(IOPTR(ldptr))
FEXCL	sys/file.h:#define FEXCL 0x400
FF0	sys/termio.h:#define FF0 0
FF1	sys/termio.h:#define FF1 0100000
FFDLY	sys/termio.h:#define FFDLY 0100000
FGETC	ldfcn.h:#define FGETC(ldptr) fgetc(IOPTR(ldptr))
FGETS	ldfcn.h:#define FGETS(s,n,ldptr) fgets(s,n,IOPTR(ldptr))
FILENO	ldfcn.h:#define FILENO(ldptr) fileno(IOPTR(ldptr))
FIOCLEX	sgtty.h:#define FIOCLEX (('f'<<8)|1)
FIONCLEX	sgtty.h:#define FIONCLEX (('f'<<8)|2)
FLT_DIG	limits.h:#define FLT_DIG 7 /* digits of precision of a "float" */
FLT_MAX	limits.h:#define FLT_MAX 3.40282346638528860e+38 /*max decimal value of a "float" */
FLT_MIN	limits.h:#define FLT_MIN 1.40129846432481707e-45 /*min decimal value of a "float" */
FMASK	sys/file.h:#define FMASK 0x7f /* FMASK should be disjoint from FNET */
FMAXEXP	values.h:#define FMAXEXP ((1 << _FEXPLEN - 1) - 1 + _IEEE)
FMAXPOWTWO	values.h:#define FMAXPOWTWO ((float)(1L << FSIGNIF - 1))
FMINEXP	values.h:#define FMINEXP (-(FMAXEXP + FSIGNIF - _HIDDENBIT - 3))
FNDELAY	sys/file.h:#define FNDELAY 0x04
FNET	sys/file.h:#define FNET 0x80 /* needed by 3bnet */
FOPEN	sys/file.h:#define FOPEN 0xffffffff
FP_CLEAR	ieeefp.h:#define FP_CLEAR 0 /* exception has not occurred */
FP_DISABLE	ieeefp.h:#define FP_DISABLE 0 /* exception will be ignored */
FP_ENABLE	ieeefp.h:#define FP_ENABLE 1 /* exception will cause SIGFPE */
FP_SET	ieeefp.h:#define FP_SET 1 /* exception has occurred */
FP_X_DZ	ieeefp.h:#define FP_X_DZ 0x02 /* divide-by-zero exception */
FP_X_IMP	ieeefp.h:#define FP_X_IMP 0x01 /* imprecise (loss of precision)*/
FP_X_INV	ieeefp.h:#define FP_X_INV 0x10 /* invalid operation exception */
FP_X_OFL	ieeefp.h:#define FP_X_OFL 0x08 /* overflow exception */
FP_X_UFL	ieeefp.h:#define FP_X_UFL 0x04 /* underflow exception */
FRCACH	sys/file.h:#define FRCACH 0x20 /* Used for file and record locking cache*/
FREAD	ldfcn.h:#define FREAD(p,s,n,ldptr) fread(p,s,n,IOPTR(ldptr))
FSEEK	ldfcn.h:#define FSEEK(ldptr,o,p) fseek(IOPTR(ldptr),(p==BEGINNING)?(OFFSET(ldptr)+o):o,p)
FSIGNIF	values.h:#define FSIGNIF (BITS(float) - _FEXPLEN + _HIDDENBIT - 1)
FSYNC	sys/file.h:#define FSYNC 0x10
FTELL	ldfcn.h:#define FTELL(ldptr) ftell(IOPTR(ldptr))
FTRUNC	sys/file.h:#define FTRUNC 0x200
FTW_D	ftw.h:#define FTW_D 1 /* directory */
FTW_DNR	ftw.h:#define FTW_DNR 2 /* directory without read permission */
FTW_F	ftw.h:#define FTW_F 0 /* file */
FTW_NS	ftw.h:#define FTW_NS 3 /* unknown type, stat failed */
FWRITE	ldfcn.h:#define FWRITE(p,s,n,ldptr) fwrite(p,s,n,IOPTR(ldptr))
F_ALLOCSP	sys/fcntl.h:#define F_ALLOCSP 10 /* reserved */
F_CHKFL	sys/fcntl.h:#define F_CHKFL 8 /* Check legality of file flag changes */
F_DUPFD	sys/fcntl.h:#define F_DUPFD 0 /* Duplicate fildes */
F_FREESP	sys/fcntl.h:#define F_FREESP 11 /* reserved */
F_GETFD	sys/fcntl.h:#define F_GETFD 1 /* Get fildes flags */
F_GETFL	sys/fcntl.h:#define F_GETFL 3 /* Get file flags */
F_GETLK	sys/fcntl.h:#define F_GETLK 5 /* Get file lock */
F_LOCK	unistd.h:#define F_LOCK 1 /* Lock a region for exclusive use */
F_OK	unistd.h:#define F_OK 0 /* Test for existence of File */
F_RDLCK	sys/fcntl.h:#define F_RDLCK 01
F_SETFD	sys/fcntl.h:#define F_SETFD 2 /* Set fildes flags */
F_SETFL	sys/fcntl.h:#define F_SETFL 4 /* Set file flags */
F_SETLK	sys/fcntl.h:#define F_SETLK 6 /* Set file lock */
F_SETLKW	sys/fcntl.h:#define F_SETLKW 7 /* Set file lock and wait */
F_TEST	unistd.h:#define F_TEST 3 /* Test a region for other processes locks */
F_TLOCK	unistd.h:#define F_TLOCK 2 /* Test and lock a region for exclusive use */
F_ULOCK	unistd.h:#define F_ULOCK 0 /* Unlock a previously locked region */
F_UNLCK	sys/fcntl.h:#define F_UNLCK 03
F_WRLCK	sys/fcntl.h:#define F_WRLCK 02
Freeend	libPW/xalloc.c:	extern char * Freeend;
GETC	ldfcn.h:#define GETC(ldptr) getc(IOPTR(ldptr))
GETNaNPC	nan.h:#define GETNaNPC(dval) (((dnan *)&(dval))->inf_parts.bits << 12 | \
GETW	ldfcn.h:#define GETW(ldptr) getw(IOPTR(ldptr))
HIBITI	values.h:#define HIBITI (1 << BITS(int) - 1)
HIBITL	values.h:#define HIBITL (1L << BITS(long) - 1)
HIBITS	values.h:#define HIBITS ((short)(1 << BITS(short) - 1))
HUGE	math.h:#define HUGE MAXFLOAT
HUGE_VAL	limits.h:#define HUGE_VAL 3.40282346638528860e+38 /*error value returned by Math lib*/
HUPCL	sys/termio.h:#define HUPCL 0002000
HZ	sys/param.h:#define HZ 100 /* 100 ticks/second of the clock */
H_PREC	values.h:#define H_PREC (DSIGNIF % 2 ? (1L << DSIGNIF/2) * M_SQRT2 : 1L << DSIGNIF/2)
ICANON	sys/termio.h:#define ICANON 0000002
ICRNL	sys/termio.h:#define ICRNL 0000400
IGNBRK	sys/termio.h:#define IGNBRK 0000001
IGNCR	sys/termio.h:#define IGNCR 0000200
IGNPAR	sys/termio.h:#define IGNPAR 0000004
IGN_PID	sys/flock.h:#define IGN_PID 2 /* ignore epid when cleaning locks */
INLCR	sys/termio.h:#define INLCR 0000100
INOFLCK	sys/flock.h:#define INOFLCK 1 /* Inode is locked when reclock() is called. */
INPCK	sys/termio.h:#define INPCK 0000020
INP_QSIZE	term.h:#define INP_QSIZE 32
INT_MAX	limits.h:#define INT_MAX 2147483647 /* max decimal value of an "int" */
INT_MIN	limits.h:#define INT_MIN -2147483648 /* min decimal value of an "int" */
IPC_ALLOC	sys/ipc.h:#define IPC_ALLOC 0100000 /* entry currently allocated */
IPC_CREAT	sys/ipc.h:#define IPC_CREAT 0001000 /* create entry if key doesn't exist */
IPC_EXCL	sys/ipc.h:#define IPC_EXCL 0002000 /* fail if key exists */
IPC_NOWAIT	sys/ipc.h:#define IPC_NOWAIT 0004000 /* error if request must wait */
IPC_PRIVATE	sys/ipc.h:#define IPC_PRIVATE (key_t)0 /* private key */
IPC_RMID	sys/ipc.h:/* #define IPC_RMID 0 /* remove identifier */
IPC_SET	sys/ipc.h:#define IPC_SET 1 /* set options */
IPC_STAT	sys/ipc.h:#define IPC_STAT 2 /* get options */
ISIG	sys/termio.h:#define ISIG 0000001
ISTHERE	regexp.h:#define ISTHERE(c) (ep[c >> 3] & bittab[c & 07])
ISTRIP	sys/termio.h:#define ISTRIP 0000040
IUCLC	sys/termio.h:#define IUCLC 0001000
IXANY	sys/termio.h:#define IXANY 0004000
IXOFF	sys/termio.h:#define IXOFF 0010000
IXON	sys/termio.h:#define IXON 0002000
IsINF	nan.h:#define IsINF(X) (((dnan *)&(X))->inf_parts.bits == 0 && \
IsNAN	nan.h:#define IsNAN(X) 0
IsNANorINF	nan.h:#define IsNANorINF(X) (((dnan *)&(X))->nan_parts.exponent == 0x7ff)
IsNegNAN	nan.h:#define IsNegNAN(X) (((dnan *)&(X))->nan_parts.sign == 1)
IsPINF	nan.h:#define IsPINF(X) 0
IsPosNAN	nan.h:#define IsPosNAN(X) (((dnan *)&(X))->nan_parts.sign == 0)
JAGENT	sys/jioctl.h:#define JAGENT (JTYPE|9) /* control for both directions */
JBOOT	sys/jioctl.h:#define JBOOT (JTYPE|1)
JMPX	sys/jioctl.h:#define JMPX (JTYPE|3)
JTERM	sys/jioctl.h:#define JTERM (JTYPE|2)
JTIMO	sys/jioctl.h:#define JTIMO (JTYPE|4) /* Timeouts in seconds */
JTIMOM	sys/jioctl.h:#define JTIMOM (JTYPE|6) /* Timeouts in millisecs */
JTRUN	sys/jioctl.h:#define JTRUN (JTYPE|10) /* send runlayer command to layers*/
JTYPE	sys/jioctl.h:#define JTYPE ('j'<<8)
JWINSIZE	sys/jioctl.h:#define JWINSIZE (JTYPE|5)
JZOMBOOT	sys/jioctl.h:#define JZOMBOOT (JTYPE|7)
KEY_A1	curses.h:#define KEY_A1 0534 /* Upper left of keypad */
KEY_A3	curses.h:#define KEY_A3 0535 /* Upper right of keypad */
KEY_B2	curses.h:#define KEY_B2 0536 /* Center of keypad */
KEY_BACKSPACE	curses.h:#define KEY_BACKSPACE 0407 /* Sent by backspace key */
KEY_BEG	curses.h:#define KEY_BEG 0542 /* beg(inning) key */
KEY_BREAK	curses.h:#define KEY_BREAK 0401 /* break key (unreliable) */
KEY_BTAB	curses.h:#define KEY_BTAB 0541 /* Back tab key */
KEY_C1	curses.h:#define KEY_C1 0537 /* Lower left of keypad */
KEY_C3	curses.h:#define KEY_C3 0540 /* Lower right of keypad */
KEY_CANCEL	curses.h:#define KEY_CANCEL 0543 /* cancel key */
KEY_CATAB	curses.h:#define KEY_CATAB 0526 /* Sent by clear-all-tabs key. */
KEY_CLEAR	curses.h:#define KEY_CLEAR 0515 /* Sent by clear screen or erase key. */
KEY_CLOSE	curses.h:#define KEY_CLOSE 0544 /* close key */
KEY_COMMAND	curses.h:#define KEY_COMMAND 0545 /* cmd (command) key */
KEY_COPY	curses.h:#define KEY_COPY 0546 /* copy key */
KEY_CREATE	curses.h:#define KEY_CREATE 0547 /* create key */
KEY_CTAB	curses.h:#define KEY_CTAB 0525 /* Sent by clear-tab key */
KEY_DC	curses.h:#define KEY_DC 0512 /* Sent by delete character key. */
KEY_DL	curses.h:#define KEY_DL 0510 /* Sent by delete line key. */
KEY_DOWN	curses.h:#define KEY_DOWN 0402 /* Sent by terminal down arrow key */
KEY_EIC	curses.h:#define KEY_EIC 0514 /* Sent by rmir or smir in insert mode. */
KEY_END	curses.h:#define KEY_END 0550 /* end key */
KEY_ENTER	curses.h:#define KEY_ENTER 0527 /* Enter/send (unreliable) */
KEY_EOL	curses.h:#define KEY_EOL 0517 /* Sent by clear-to-end-of-line key. */
KEY_EOS	curses.h:#define KEY_EOS 0516 /* Sent by clear-to-end-of-screen key. */
KEY_EXIT	curses.h:#define KEY_EXIT 0551 /* exit key */
KEY_F	curses.h:#define KEY_F(n) (KEY_F0+(n)) /* Space for 64 function keys is reserved. */
KEY_F0	curses.h:#define KEY_F0 0410 /* function key f0. */
KEY_FIND	curses.h:#define KEY_FIND 0552 /* find key */
KEY_HELP	curses.h:#define KEY_HELP 0553 /* help key */
KEY_HOME	curses.h:#define KEY_HOME 0406 /* Sent by home key. */
KEY_IC	curses.h:#define KEY_IC 0513 /* Sent by ins char/enter ins mode key. */
KEY_IL	curses.h:#define KEY_IL 0511 /* Sent by insert line. */
KEY_LEFT	curses.h:#define KEY_LEFT 0404 /* Sent by terminal left arrow key */
KEY_LL	curses.h:#define KEY_LL 0533 /* Sent by home-down key */
KEY_MARK	curses.h:#define KEY_MARK 0554 /* mark key */
KEY_MAX	curses.h:#define KEY_MAX 0777 /* Maximum curses key */
KEY_MESSAGE	curses.h:#define KEY_MESSAGE 0555 /* message key */
KEY_MIN	curses.h:#define KEY_MIN 0401 /* Minimum curses key */
KEY_MOVE	curses.h:#define KEY_MOVE 0556 /* move key */
KEY_NEXT	curses.h:#define KEY_NEXT 0557 /* next object key */
KEY_NPAGE	curses.h:#define KEY_NPAGE 0522 /* Sent by next-page key */
KEY_OPEN	curses.h:#define KEY_OPEN 0560 /* open key */
KEY_OPTIONS	curses.h:#define KEY_OPTIONS 0561 /* options key */
KEY_PPAGE	curses.h:#define KEY_PPAGE 0523 /* Sent by previous-page key */
KEY_PREVIOUS	curses.h:#define KEY_PREVIOUS 0562 /* previous object key */
KEY_PRINT	curses.h:#define KEY_PRINT 0532 /* print or copy */
KEY_REDO	curses.h:#define KEY_REDO 0563 /* redo key */
KEY_REFERENCE	curses.h:#define KEY_REFERENCE 0564 /* ref(erence) key */
KEY_REFRESH	curses.h:#define KEY_REFRESH 0565 /* refresh key */
KEY_REPLACE	curses.h:#define KEY_REPLACE 0566 /* replace key */
KEY_RESET	curses.h:#define KEY_RESET 0531 /* reset or hard reset (unreliable) */
KEY_RESTART	curses.h:#define KEY_RESTART 0567 /* restart key */
KEY_RESUME	curses.h:#define KEY_RESUME 0570 /* resume key */
KEY_RIGHT	curses.h:#define KEY_RIGHT 0405 /* Sent by terminal right arrow key */
KEY_SAVE	curses.h:#define KEY_SAVE 0571 /* save key */
KEY_SBEG	curses.h:#define KEY_SBEG 0572 /* shifted beginning key */
KEY_SCANCEL	curses.h:#define KEY_SCANCEL 0573 /* shifted cancel key */
KEY_SCOMMAND	curses.h:#define KEY_SCOMMAND 0574 /* shifted command key */
KEY_SCOPY	curses.h:#define KEY_SCOPY 0575 /* shifted copy key */
KEY_SCREATE	curses.h:#define KEY_SCREATE 0576 /* shifted create key */
KEY_SDC	curses.h:#define KEY_SDC 0577 /* shifted delete char key */
KEY_SDL	curses.h:#define KEY_SDL 0600 /* shifted delete line key */
KEY_SELECT	curses.h:#define KEY_SELECT 0601 /* select key */
KEY_SEND	curses.h:#define KEY_SEND 0602 /* shifted end key */
KEY_SEOL	curses.h:#define KEY_SEOL 0603 /* shifted clear line key */
KEY_SEXIT	curses.h:#define KEY_SEXIT 0604 /* shifted exit key */
KEY_SF	curses.h:#define KEY_SF 0520 /* Sent by scroll-forward/down key */
KEY_SFIND	curses.h:#define KEY_SFIND 0605 /* shifted find key */
KEY_SHELP	curses.h:#define KEY_SHELP 0606 /* shifted help key */
KEY_SHOME	curses.h:#define KEY_SHOME 0607 /* shifted home key */
KEY_SIC	curses.h:#define KEY_SIC 0610 /* shifted input key */
KEY_SLEFT	curses.h:#define KEY_SLEFT 0611 /* shifted left arrow key */
KEY_SMESSAGE	curses.h:#define KEY_SMESSAGE 0612 /* shifted message key */
KEY_SMOVE	curses.h:#define KEY_SMOVE 0613 /* shifted move key */
KEY_SNEXT	curses.h:#define KEY_SNEXT 0614 /* shifted next key */
KEY_SOPTIONS	curses.h:#define KEY_SOPTIONS 0615 /* shifted options key */
KEY_SPREVIOUS	curses.h:#define KEY_SPREVIOUS 0616 /* shifted prev key */
KEY_SPRINT	curses.h:#define KEY_SPRINT 0617 /* shifted print key */
KEY_SR	curses.h:#define KEY_SR 0521 /* Sent by scroll-backward/up key */
KEY_SREDO	curses.h:#define KEY_SREDO 0620 /* shifted redo key */
KEY_SREPLACE	curses.h:#define KEY_SREPLACE 0621 /* shifted replace key */
KEY_SRESET	curses.h:#define KEY_SRESET 0530 /* soft (partial) reset (unreliable) */
KEY_SRIGHT	curses.h:#define KEY_SRIGHT 0622 /* shifted right arrow */
KEY_SRSUME	curses.h:#define KEY_SRSUME 0623 /* shifted resume key */
KEY_SSAVE	curses.h:#define KEY_SSAVE 0624 /* shifted save key */
KEY_SSUSPEND	curses.h:#define KEY_SSUSPEND 0625 /* shifted suspend key */
KEY_STAB	curses.h:#define KEY_STAB 0524 /* Sent by set-tab key */
KEY_SUNDO	curses.h:#define KEY_SUNDO 0626 /* shifted undo key */
KEY_SUSPEND	curses.h:#define KEY_SUSPEND 0627 /* suspend key */
KEY_UNDO	curses.h:#define KEY_UNDO 0630 /* undo key */
KEY_UP	curses.h:#define KEY_UP 0403 /* Sent by terminal up arrow key */
KILLFPE	nan.h:#define KILLFPE() (void) kill(getpid(), 8)
KILLNaN	nan.h:#define KILLNaN(X) if (NaN(X)) KILLFPE()
LDCHG	sys/termio.h:#define LDCHG (LDIOC|2)
LDCLOSE	sys/termio.h:#define LDCLOSE (LDIOC|1)
LDGETT	sys/termio.h:#define LDGETT (LDIOC|8)
LDIOC	sys/termio.h:#define LDIOC ('D'<<8)
LDOPEN	sys/termio.h:#define LDOPEN (LDIOC|0)
LDSETT	sys/termio.h:#define LDSETT (LDIOC|9)
LINK_MAX	limits.h:#define LINK_MAX 1000 /* max # of links to a single file */
LIOC	sys/ioctl.h:#define LIOC ('l'<<8)
LIOCGETP	sys/ioctl.h:#define LIOCGETP (LIOC|1)
LIOCGETS	sys/ioctl.h:#define LIOCGETS (LIOC|5)
LIOCSETP	sys/ioctl.h:#define LIOCSETP (LIOC|2)
LIOCSETS	sys/ioctl.h:#define LIOCSETS (LIOC|6)
LN_MAXDOUBLE	values.h:#define LN_MAXDOUBLE (M_LN2 * DMAXEXP)
LN_MINDOUBLE	values.h:#define LN_MINDOUBLE (M_LN2 * (DMINEXP - 1))
LOBLK	sys/termio.h:#define LOBLK 0040000
LONG_MAX	limits.h:#define LONG_MAX 2147483647 /* max decimal value of a "long" */
LONG_MIN	limits.h:#define LONG_MIN -2147483648 /* min decimal value of a "long" */
L_ctermid	stdio.h:#define L_ctermid 9
L_cuserid	stdio.h:#define L_cuserid 9
L_tmpnam	stdio.h:#define L_tmpnam (sizeof(P_tmpdir) + 15)
Lastbrk	libPW/xalloc.c:	extern unsigned Lastbrk;
MAXBEXP	values.h:#define MAXBEXP DMAXEXP /* for backward compatibility */
MAXDOUBLE	values.h:#define MAXDOUBLE ???? 1.79769313486231470e+308
MAXFLOAT	values.h:#define MAXFLOAT ???? ((float)1.701411733192644299e+38)
MAXINT	values.h:#define MAXINT (~HIBITI)
MAXLINK	sys/param.h:#define MAXLINK 1000 /* max links */
MAXLONG	values.h:#define MAXLONG (~HIBITL)
MAXPID	sys/param.h:#define MAXPID 30000 /* max process id */
MAXPOWTWO	values.h:#define MAXPOWTWO DMAXPOWTWO /* for backward compatibility */
MAXSHORT	values.h:#define MAXSHORT ((short)~HIBITS)
MAXSIG	sys/signal.h:#define MAXSIG 32 /* size of u_signal[], NSIG-1 <= MAXSIG*/
MAXUID	sys/param.h:#define MAXUID 60000 /* max user id */
MINBEXP	values.h:#define MINBEXP DMINEXP /* for backward compatibility */
MINDOUBLE	values.h:#define MINDOUBLE ???? (0.01 * 2.938735877055718770e-37)
MINFLOAT	values.h:#define MINFLOAT ???? ((float)1.40129846432481707e-45)
M_1_PI	math.h:#define M_1_PI 0.31830988618379067154
M_2_PI	math.h:#define M_2_PI 0.63661977236758134308
M_2_SQRTPI	math.h:#define M_2_SQRTPI 1.12837916709551257390
M_E	math.h:#define M_E 2.7182818284590452354
M_GRAIN	malloc.h:#define M_GRAIN 3 /* set number of sizes mapped to one, for
M_KEEP	malloc.h:#define M_KEEP 4 /* retain contents of block after a free until
M_LN10	math.h:#define M_LN10 2.30258509299404568402
M_LN2	values.h:#define M_LN2 0.69314718055994530942
M_LOG10E	math.h:#define M_LOG10E 0.43429448190325182765
M_LOG2E	math.h:#define M_LOG2E 1.4426950408889634074
M_MXFAST	malloc.h:#define M_MXFAST 1 /* set size of blocks to be fast */
M_NLBLKS	malloc.h:#define M_NLBLKS 2 /* set number of block in a holding block */
M_PI	values.h:#define M_PI 3.14159265358979323846
M_PI_2	math.h:#define M_PI_2 1.57079632679489661923
M_PI_4	math.h:#define M_PI_4 0.78539816339744830962
M_SQRT1_2	math.h:#define M_SQRT1_2 0.70710678118654752440
M_SQRT2	values.h:#define M_SQRT2 1.41421356237309504880
NAME_MAX	limits.h:#define NAME_MAX 14 /* max # of characters in a file name */
NBRA	regexp.h:#define NBRA 9
NCARGS	sys/param.h:#define NCARGS 5120 /* # characters in exec arglist */
NCC	sys/termio.h:#define NCC 8
NCCL	regexp.h:#define NCCL 40
NL0	sys/termio.h:#define NL0 0
NL1	sys/termio.h:#define NL1 0000400
NLDLY	sys/termio.h:#define NLDLY 0000400
NOFILE	sys/param.h:#define NOFILE 20
NOFILES_MAX	sys/param.h:#define NOFILES_MAX 100
NOFILES_MIN	sys/param.h:#define NOFILES_MIN 20
NOFLSH	sys/termio.h:#define NOFLSH 0000200
NONBLANK	macros.h:#define NONBLANK(p) while (*p==' ' || *p=='\t') p++
NSIG	sys/signal.h:#define NSIG 23 /* The valid signal number is from 1 to NSIG-1 */
NULL	stdio.h:#define NULL 0
NZERO	sys/param.h:#define NZERO 20
NaN	nan.h:#define NaN(X) (((dnan *)&(X))->nan_parts.exponent == 0x7ff)
OCRNL	sys/termio.h:#define OCRNL 0000010
OFDEL	sys/termio.h:#define OFDEL 0000200
OFILL	sys/termio.h:#define OFILL 0000100
OLCUC	sys/termio.h:#define OLCUC 0000002
ONLCR	sys/termio.h:#define ONLCR 0000004
ONLRET	sys/termio.h:#define ONLRET 0000040
ONOCR	sys/termio.h:#define ONOCR 0000020
OPEN_MAX	limits.h:#define OPEN_MAX 20 /* max # of files a process can have open */
OPOST	sys/termio.h:#define OPOST 0000001
O_APPEND	sys/fcntl.h:#define O_APPEND 010 /* append (writes guaranteed at the end) */
O_CREAT	sys/fcntl.h:#define O_CREAT 00400 /* open with file create (uses third open arg)*/
O_EXCL	sys/fcntl.h:#define O_EXCL 02000 /* exclusive open */
O_NDELAY	sys/fcntl.h:#define O_NDELAY 04 /* Non-blocking I/O */
O_RDONLY	sys/fcntl.h:#define O_RDONLY 0
O_RDWR	sys/fcntl.h:#define O_RDWR 2
O_SYNC	sys/fcntl.h:#define O_SYNC 020 /* synchronous write option */
O_TRUNC	sys/fcntl.h:#define O_TRUNC 01000 /* open with truncation */
O_WRONLY	sys/fcntl.h:#define O_WRONLY 1
P754_NOFAULT	ieeefp.h:#define P754_NOFAULT 1
PARENB	sys/termio.h:#define PARENB 0000400
PARMRK	sys/termio.h:#define PARMRK 0000010
PARODD	sys/termio.h:#define PARODD 0001000
PASS_MAX	limits.h:#define PASS_MAX 8 /* max # of characters in a password */
PATH_MAX	limits.h:#define PATH_MAX 256 /* max # of characters in a path name */
PCATCH	sys/param.h:#define PCATCH 0400
PIDLE	sys/param.h:#define PIDLE 127
PID_MAX	limits.h:#define PID_MAX 30000 /* max value for a process ID */
PINOD	sys/param.h:#define PINOD 10
PIPE_BUF	limits.h:#define PIPE_BUF 5120 /* max # bytes atomic in write to a pipe */
PIPE_MAX	limits.h:#define PIPE_MAX 5120 /* max # bytes written to a pipe in a write */
PLACE	regexp.h:#define PLACE(c) ep[c >> 3] |= bittab[c & 07]
PMASK	sys/param.h:#define PMASK 0177
PMEM	sys/param.h:#define PMEM 0
PNOSTOP	sys/param.h:#define PNOSTOP 01000
PPIPE	sys/param.h:#define PPIPE 26
PRIBIO	sys/param.h:#define PRIBIO 20
PROGTTY	term.h:#define PROGTTY (cur_term->Nttyb)
PSLEP	sys/param.h:#define PSLEP 39
PSWP	sys/param.h:#define PSWP 0
PUSER	sys/param.h:#define PUSER 60
PWAIT	sys/param.h:#define PWAIT 30
PZERO	sys/param.h:#define PZERO 25
P_tmpdir	stdio.h:#define P_tmpdir "/usr/tmp/"
RCV1EN	sys/termio.h:#define RCV1EN 0010000
REWIND	ldfcn.h:#define REWIND(ldptr) rewind(IOPTR(ldptr))
RNGE	regexp.h:#define RNGE 03
RSTR	macros.h:#define RSTR(name,place) name = place;}
R_OK	unistd.h:#define R_OK 4 /* Test for Read permission */
SAVE	macros.h:#define SAVE(name,place) { int place = name;
SCCSID	macros.h:#define SCCSID(arg) static char Sccsid[]="arg"
SECDAY	sys/clock.h:#define SECDAY (24*SECHR) /* seconds/day */
SECHR	sys/clock.h:#define SECHR (60*60) /* seconds/hr */
SECYR	sys/clock.h:#define SECYR (365*SECDAY) /* seconds/common year */
SEEK_CUR	unistd.h:#define SEEK_CUR 1 /* Set file pointer to current plus "offset" */
SEEK_END	unistd.h:#define SEEK_END 2 /* Set file pointer to EOF plus "offset" */
SEEK_SET	unistd.h:#define SEEK_SET 0 /* Set file pointer to "offset" */
SETBUF	ldfcn.h:#define SETBUF(ldptr,b) setbuf(IOPTR(ldptr),b)
SETFLCK	sys/flock.h:#define SETFLCK 2 /* Set a file lock. */
SHELLTTY	term.h:#define SHELLTTY (cur_term->Ottyb)
SHRT_MAX	limits.h:#define SHRT_MAX 32767 /* max decimal value of a "short" */
SHRT_MIN	limits.h:#define SHRT_MIN -32768 /* min decimal value of a "short" */
SIGABRT	sys/signal.h:#define SIGABRT 6 /* used by abort, replace SIGIOT in the future */
SIGALRM	sys/signal.h:#define SIGALRM 14 /* alarm clock */
SIGBUS	sys/signal.h:#define SIGBUS 10 /* bus error */
SIGCLD	sys/signal.h:#define SIGCLD 18 /* death of a child */
SIGDEFER	sys/signal.h:#define SIGDEFER 0x100
SIGEMT	sys/signal.h:#define SIGEMT 7 /* EMT instruction */
SIGFPE	sys/signal.h:#define SIGFPE 8 /* floating point exception */
SIGHOLD	sys/signal.h:#define SIGHOLD 0x200
SIGHUP	sys/signal.h:#define SIGHUP 1 /* hangup */
SIGIGNORE	sys/signal.h:#define SIGIGNORE 0x800
SIGILL	sys/signal.h:#define SIGILL 4 /* illegal instruction (not reset when caught)*/
SIGINT	sys/signal.h:#define SIGINT 2 /* interrupt (rubout) */
SIGIOT	sys/signal.h:#define SIGIOT 6 /* IOT instruction */
SIGKILL	sys/signal.h:#define SIGKILL 9 /* kill (cannot be caught or ignored) */
SIGPAUSE	sys/signal.h:#define SIGPAUSE 0x1000
SIGPHONE	sys/signal.h:#define SIGPHONE 21*/ /* handset, line status change */
SIGPIPE	sys/signal.h:#define SIGPIPE 13 /* write on a pipe with no one to read it */
SIGPOLL	sys/signal.h:#define SIGPOLL 22 /* pollable event occured */
SIGPWR	sys/signal.h:#define SIGPWR 19 /* power-fail restart */
SIGQUIT	sys/signal.h:#define SIGQUIT 3 /* quit (ASCII FS) */
SIGRELSE	sys/signal.h:#define SIGRELSE 0x400
SIGSEGV	sys/signal.h:#define SIGSEGV 11 /* segmentation violation */
SIGSYS	sys/signal.h:#define SIGSYS 12 /* bad argument to system call */
SIGTERM	sys/signal.h:#define SIGTERM 15 /* software termination signal from kill */
SIGTRAP	sys/signal.h:#define SIGTRAP 5 /* trace trap (not reset when caught) */
SIGUSR1	sys/signal.h:#define SIGUSR1 16 /* user defined signal 1 */
SIGUSR2	sys/signal.h:#define SIGUSR2 17 /* user defined signal 2 */
SIGWIND	sys/signal.h:#define SIGWIND 20*/ /* window change */
SIG_DFL	sys/signal.h:#define SIG_DFL (void(*)())0
SIG_ERR	sys/signal.h:#define SIG_ERR (void(*)())-1
SIG_HOLD	sys/signal.h:#define SIG_HOLD (void(*)())2
SIG_IGN	sys/signal.h:#define SIG_IGN (void (*)())1
SLPFLCK	sys/flock.h:#define SLPFLCK 4 /* Wait if blocked. */
SSPEED	sys/termio.h:#define SSPEED 7 /* default speed: 300 baud */
STAR	regexp.h:#define STAR 01
STD_BLK	limits.h:#define STD_BLK 1024 /* # bytes in a physical I/O block */
STROFFSET	ldfcn.h:#define STROFFSET(ldptr) (HEADER(ldptr).f_symptr + HEADER(ldptr).f_nsyms * 18) /* 18 == SYMESZ */
STRSELECT	strselect.h:#define STRSELECT(a) { char *STRSeLeCT; STRSeLeCT = a; WoRD(/)WoRD(*)
SYS_NMLN	limits.h:#define SYS_NMLN 9 /* # of chars in uname-returned strings */
S_ENFMT	sys/stat.h:#define S_ENFMT S_ISGID /* record locking enforcement flag */
S_IEXEC	sys/stat.h:#define S_IEXEC 00100 /* execute/search permission, owner */
S_IFBLK	sys/stat.h:#define S_IFBLK 0060000 /* block special */
S_IFCHR	sys/stat.h:#define S_IFCHR 0020000 /* character special */
S_IFDIR	sys/stat.h:#define S_IFDIR 0040000 /* directory */
S_IFIFO	sys/stat.h:#define S_IFIFO 0010000 /* fifo */
S_IFMT	sys/stat.h:#define S_IFMT 0170000 /* type of file */
S_IFREG	sys/stat.h:#define S_IFREG 0100000 /* regular */
S_IREAD	sys/stat.h:#define S_IREAD 00400 /* read permission, owner */
S_IRGRP	sys/stat.h:#define S_IRGRP 00040 /* read permission: group */
S_IROTH	sys/stat.h:#define S_IROTH 00004 /* read permission: other */
S_IRUSR	sys/stat.h:#define S_IRUSR 00400 /* read permission: owner */
S_IRWXG	sys/stat.h:#define S_IRWXG 00070 /* read, write, execute: group */
S_IRWXO	sys/stat.h:#define S_IRWXO 00007 /* read, write, execute: other */
S_IRWXU	sys/stat.h:#define S_IRWXU 00700 /* read, write, execute: owner */
S_ISGID	sys/stat.h:#define S_ISGID 02000 /* set group id on execution */
S_ISUID	sys/stat.h:#define S_ISUID 04000 /* set user id on execution */
S_ISVTX	sys/stat.h:#define S_ISVTX 01000 /* save swapped text even after use */
S_IWGRP	sys/stat.h:#define S_IWGRP 00020 /* write permission: group */
S_IWOTH	sys/stat.h:#define S_IWOTH 00002 /* write permission: other */
S_IWRITE	sys/stat.h:#define S_IWRITE 00200 /* write permission, owner */
S_IWUSR	sys/stat.h:#define S_IWUSR 00200 /* write permission: owner */
S_IXGRP	sys/stat.h:#define S_IXGRP 00010 /* execute permission: group */
S_IXOTH	sys/stat.h:#define S_IXOTH 00001 /* execute permission: other */
S_IXUSR	sys/stat.h:#define S_IXUSR 00100 /* execute permission: owner */
TAB0	sys/termio.h:#define TAB0 0
TAB1	sys/termio.h:#define TAB1 0004000
TAB2	sys/termio.h:#define TAB2 0010000
TAB3	sys/termio.h:#define TAB3 0014000
TABDLY	sys/termio.h:#define TABDLY 0014000
TCDSET	sys/termio.h:#define TCDSET (TIOC|32)
TCFLSH	sys/termio.h:#define TCFLSH (TIOC|7)
TCGETA	sys/termio.h:#define TCGETA (TIOC|1)
TCSBRK	sys/termio.h:#define TCSBRK (TIOC|5)
TCSETA	sys/termio.h:#define TCSETA (TIOC|2)
TCSETAF	sys/termio.h:#define TCSETAF (TIOC|4)
TCSETAW	sys/termio.h:#define TCSETAW (TIOC|3)
TCXONC	sys/termio.h:#define TCXONC (TIOC|6)
TERM_D40	sys/termio.h:#define TERM_D40 5 /* TTY Mod 40/1 */
TERM_D42	sys/termio.h:#define TERM_D42 7 /* TTY Mod 40/2B */
TERM_H45	sys/termio.h:#define TERM_H45 6 /* Hewlitt-Packard 45 */
TERM_NONE	sys/termio.h:#define TERM_NONE 0 /* tty */
TERM_TEC	sys/termio.h:#define TERM_TEC 1 /* TEC Scope */
TERM_TEX	sys/termio.h:#define TERM_TEX 4 /* Tektronix 4023 */
TERM_V10	sys/termio.h:#define TERM_V10 3 /* DEC VT100 */
TERM_V61	sys/termio.h:#define TERM_V61 2 /* DEC VT61 */
TIOC	sys/termio.h:#define TIOC ('T'<<8)
TIOCEXCL	sgtty.h:#define TIOCEXCL (('t'<<8)|13)
TIOCGETP	sgtty.h:#define TIOCGETP (('t'<<8)|8)
TIOCHPCL	sgtty.h:#define TIOCHPCL (('t'<<8)|2)
TIOCNXCL	sgtty.h:#define TIOCNXCL (('t'<<8)|14)
TIOCSETP	sgtty.h:#define TIOCSETP (('t'<<8)|9)
TM_ANL	sys/termio.h:#define TM_ANL 0002 /* auto newline on column 80 */
TM_CECHO	sys/termio.h:#define TM_CECHO 0010 /* echo terminal cursor control */
TM_CINVIS	sys/termio.h:#define TM_CINVIS 0020 /* do not send esc seq to user */
TM_LCF	sys/termio.h:#define TM_LCF 0004 /* last col of last row special */
TM_NONE	sys/termio.h:#define TM_NONE 0000 /* use default flags */
TM_SET	sys/termio.h:#define TM_SET 0200 /* must be on to set/res flags */
TM_SNL	sys/termio.h:#define TM_SNL 0001 /* special newline flag */
TTYTYPE	sys/termio.h:#define TTYTYPE (TIOC|8)
UID_MAX	limits.h:#define UID_MAX 60000 /* max value for a user or group ID */
UNGETC	ldfcn.h:#define UNGETC(c,ldptr) ungetc(c,IOPTR(ldptr))
USE_PID	sys/flock.h:#define USE_PID 1 /* use epid when cleaning locks */
USI_MAX	limits.h:#define USI_MAX 4294967295 /* max decimal value of an "unsigned" */
USXALLOC	macros.h:#define USXALLOC() char *alloc(n) {return((char *)xalloc((unsigned)n));} free(n) char *n; {xfree(n);} char *malloc(n) unsigned n; {int p; p=xalloc(n); return((char *)(p != -1?p:0));}
VEOF	sys/termio.h:#define VEOF 4
VEOL	sys/termio.h:#define VEOL 5
VEOL2	sys/termio.h:#define VEOL2 6
VERASE	sys/termio.h:#define VERASE 2
VINTR	sys/termio.h:#define VINTR 0
VKILL	sys/termio.h:#define VKILL 3
VMIN	sys/termio.h:#define VMIN 4
VQUIT	sys/termio.h:#define VQUIT 1
VSWTCH	sys/termio.h:#define VSWTCH 7
VT0	sys/termio.h:#define VT0 0
VT1	sys/termio.h:#define VT1 0040000
VTDLY	sys/termio.h:#define VTDLY 0040000
VTIME	sys/termio.h:#define VTIME 5
WHEN	strselect.h:#define WHEN(a) } else WoRD(/)WoRD(*) WoRD(*)WoRD(/) \
WHEN2	strselect.h:#define WHEN2(a1,a2) } else WoRD(/)WoRD(*) WoRD(*)WoRD(/)\
WHEN3	strselect.h:#define WHEN3(a1,a2,a3) } else WoRD(/)WoRD(*) WoRD(*)WoRD(/)\
WHENN	strselect.h:#define WHENN(a) } else WoRD(/)WoRD(*) WoRD(*)WoRD(/)\
WHENN2	strselect.h:#define WHENN2(a1,a2) } else WoRD(/)WoRD(*) WoRD(*)WoRD(/)\
WHENN3	strselect.h:#define WHENN3(a1,a2,a3) } else WoRD(/)WoRD(*) WoRD(*)WoRD(/)\
WORD_BIT	limits.h:#define WORD_BIT 32 /* # of bits in a "word" or "int" */
W_OK	unistd.h:#define W_OK 2 /* Test for Write permission */
WoRD	strselect.h:#define WoRD(x)x
XCASE	sys/termio.h:#define XCASE 0000004
XMT1EN	sys/termio.h:#define XMT1EN 0020000
X_EPS	values.h:#define X_EPS (1.0/H_PREC)
X_OK	unistd.h:#define X_OK 1 /* Test for eXecute permission */
X_PLOSS	values.h:#define X_PLOSS ((double)(long)(M_PI * H_PREC))
X_TLOSS	values.h:#define X_TLOSS (M_PI * DMAXPOWTWO)
_B	ctype.h:#define _B 0100 /* Blank */
_C	ctype.h:#define _C 040 /* Control character */
_DEXPLEN	values.h:#define _DEXPLEN 11
_HIDDENBIT	values.h:#define _HIDDENBIT 1
_IEEE	values.h:#define _IEEE 1
_IOFBF	stdio.h:#define _IOFBF 0000
_IOLBF	stdio.h:#define _IOLBF 0100
_IONBF	stdio.h:#define _IONBF 0004
_L	ctype.h:#define _L 02 /* Lower case */
_N	ctype.h:#define _N 04 /* Numeral (digit) */
_NFILE	stdio.h:#define _NFILE 20
_P	ctype.h:#define _P 020 /* Punctuation */
_S	ctype.h:#define _S 010 /* Spacing character */
_STANDOUT	curses.h:#define _STANDOUT A_STANDOUT /* for compatability with old curses */
_U	ctype.h:#define _U 01 /* Upper case */
_X	ctype.h:#define _X 0200 /* heXadecimal digit */
__advance	libPW/regex.c:	int __advance (lp, ep) char *lp, *ep; { int ret; return ret; }
__cclass	libPW/regex.c:	int __cclass (set, ac, af) char *set; { int ret; return ret; }
__execute	libPW/regex.c:	int __execute (addrc,addrl) char *addrc,*addrl; { int ret; return ret; }
__getrnge	libPW/regex.c:	int __getrnge (i,j,k) int *i,*j; char *k; { int ret; return ret; }
__rpop	libPW/regcmp.c:	int __rpop () { int ret; return ret; }
__rpush	libPW/regcmp.c:	int __rpush (ptr) char *ptr; { int ret; return ret; }
__size	libPW/regcmp.c:	int __size (strg) char *strg; { int ret; return ret; }
__xpop	libPW/regex.c:	int __xpop (i) int i; { int ret; return ret; }
__xpush	libPW/regex.c:	int __xpush (i,p) int i; char *p; { int ret; return ret; }
_assert	libc ASSERT(3X):	void _assert (a, f, n) char *a, *f; {}
_bufend	stdio.h:#define _bufend(p) _bufendtab[(p)->_file]
_bufendtab	libc STDIO(3S):	extern unsigned char *_bufendtab[_NFILE];
_bufsiz	stdio.h:#define _bufsiz(p) (_bufend(p) - (p)->_base)
_ctype	libc CTYPE(3C):	char _ctype [129];
_exit	libc EXIT(2):	void _exit (s) {}
_filbuf	libc VPRINTF(3S):	int _filbuf (f) FILE *f; { return (0); }
_flsbuf	libc VPRINTF(3S):	int _flsbuf (c, f) FILE *f; { return (c); }
_iob	libc STDIO(3S):	extern FILE _iob[_NFILE];
_tolower	libc CONV(3C):ctype.h:#define _tolower(c) ((_ctype + 258)[c])
_toupper	libc CONV(3C):ctype.h:#define _toupper(c) ((_ctype + 258)[c])
a64l	libc A64L(3C):	long a64l (s) char *s; { return (0L); }
abort	libc ABORT(3C):	int abort () { return (0); }
abs	libc ABS(3C):	int abs (i) { return (i); }
abspath	libPW/abspath.c:	char * abspath (p) char *p; { char *ret; return ret; }
access	libc ACCESS(2):	int access (f, m) char *f; { return (m); }
acct	libc ACCT(2):	int acct (f) char *f; { return (0); }
acos	libm TRIG(3M):	double acos (x) double x; { return (x); }
acs_chars	term.h:#define acs_chars CURS strs2._acs_chars
addch	curses.h:#define addch(ch) waddch(stdscr, ch)
addchnstr	curses.h:#define addchnstr(str,n) waddchnstr(stdscr,str,n)
addchstr	curses.h:#define addchstr(str) waddchstr(stdscr,str)
addnstr	curses.h:#define addnstr(s,n) waddnstr(stdscr,s,n)
addstr	curses.h:#define addstr(str) waddstr(stdscr, str)
alarm	libc ALARM(2):	unsigned alarm (s) unsigned s; { return (s); }
allocldptr	libld/allocldptr.c:	LDFILE * allocldptr () { LDFILE *ret; return ret; }
allprint	libl/allprint.c:	int allprint (c) char c; { int ret; return ret; }
any	libPW/any.c:	int any (c,s) char c, *s; { int ret; return ret; }
anystr	libPW/anystr.c:	int anystr (s1, s2) char *s1, *s2; { int ret; return ret; }
arc	libplot/arc.c:	int arc (xi,yi,x0,y0,x1,y1) { int ret; return ret; }
asctime	libc CTIME(3C):	char * asctime (t) struct tm *t; { return (""); }
asin	libm TRIG(3M):	double asin (x) double x; { return (x); }
assert	assert.h:#define assert(EX) if (EX) ; else _assert("EX", __FILE__, __LINE__)
atan	libm TRIG(3M):	double atan (x) double x; { return (x); }
atan2	libm TRIG(3M):	double atan2 (x, y) double x, y; { return (x); }
atof	libc STRTOD(3C):	double atof (s) char *s; { return (0.0); }
atoi	libc STRTOL(3C):	int atoi (s) char *s; { return (0); }
atol	libc STRTOL(3C):	long atol (s) char *s; { return (0L); }
attroff	curses.h:#define attroff(at) wattroff(stdscr,at)
attron	curses.h:#define attron(at) wattron(stdscr,at)
attrset	curses.h:#define attrset(at) wattrset(stdscr,at)
auto_left_margin	term.h:#define auto_left_margin CUR _b1
auto_right_margin	term.h:#define auto_right_margin CUR _b2
back_tab	term.h:#define back_tab CUR _Vr2_Astrs._s1
balbrk	libPW/bal.c:	int balbrk (str,open,clos,end) char *str,*open,*clos,*end; { int ret; return ret; }
baudrate	libcurses/baudrate.c:	int baudrate () { int ret; return ret; }
beehive_glitch	term.h:#define beehive_glitch no_esc_ctlc
beep	curses.h:libcurses/beep.c:	int beep () { int ret; return ret; }
bell	term.h:#define bell CUR _Vr2_Astrs._s2
bkgd	curses.h:#define bkgd(c) wbkgd(stdscr,c)
bkgdset	curses.h:#define bkgdset(c) wbkgdset(stdscr,c)
border	curses.h:#define border(lc,rc,tc,bc) wborder(stdscr,lc,rc,tc,bc)
box	curses.h, libplot/box.c:int box (win, vert, hor) WINDOW *win; chtype vert, hor; { int ret; return ret; }, int box (x0, y0, x1, y1) { int ret; return ret; }
brk	libc BRK(2):	int brk (e) char *e; { return (0); }
bsearch	libc BSEARCH(3C):	char * bsearch (k, b, n, w, c) char *k, *b; unsigned n, w; int (*c)(); { return (k); }
calloc	libc MALLOC(3C):	char * calloc (n, e) unsigned n, e; { return (""); }
carriage_return	term.h:#define carriage_return CUR _Vr2_Astrs._s3
cat	libPW/cat.c:	/* VARARGS1 */ char * cat (dest) char *dest; { char *ret; return ret; }
cbreak	libcurses/cbreak.c:	int cbreak () { int ret; return ret; }
ceil	libm FLOOR(3M):	double ceil (x) double x; { return (x); }
ceol_standout_glitch	term.h:#define ceol_standout_glitch CUR _b4
change_scroll_region	term.h:#define change_scroll_region CUR _Vr2_Astrs._s4
char_padding	term.h:#define char_padding CURS strs2._char_padding
chdir	libc CHDIR(2):	int chdir (s) char *s; { return (0); }
chmod	libc CHMOD(2):	int chmod (s, m) char *s; { return (m); }
chown	libc CHOWN(2):	int chown (s, o, g) char *s; { return (o); }
chroot	libc CHROOT(2):	int chroot (p) char *p; { return (0); }
circle	libplot/circle.c:	int circle (x,y,r) { int ret; return ret; }
clean_up	libPW/clean.c:	int clean_up () { int ret; return ret; }
clear	curses.h:#define clear() wclear(stdscr)
clear_all_tabs	term.h:#define clear_all_tabs CUR _Vr2_Astrs._s5
clear_margins	term.h:#define clear_margins CURS strs3._clear_margins
clear_screen	term.h:#define clear_screen CUR _Vr2_Astrs._s6
clearerr	stdio.h:libc FERROR(3S):	void clearerr (f) FILE *f; {}
clearok	curses.h:libcurses/clearok.c:	int clearok (win,bf) WINDOW *win; int bf; { int ret; return ret; }
clock	libc CLOCK(3C):	long clock () { return (0L); }
close	libc CLOSE(2):	int close (f) { return (f); }
closepl	libplot/close.c:	int closepl () { int ret; return ret; }
closevt	libplot/close.c:	int closevt () { int ret; return ret; }
clr_bol	term.h:#define clr_bol CURS strs3._clr_bol
clr_eol	term.h:#define clr_eol CUR _Vr2_Astrs._s7
clr_eos	term.h:#define clr_eos CUR _Vr2_Astrs._s8
clrtobot	curses.h:#define clrtobot() wclrtobot(stdscr)
clrtoeol	curses.h:#define clrtoeol() wclrtoeol(stdscr)
column_address	term.h:#define column_address CUR _Vr2_Astrs._s9
columns	term.h:#define columns CUR _c1
command_character	term.h:#define command_character CUR _Vr2_Astrs._s10
compare	macros.h:#define compare(str1,str2) strcmp(str1,str2)
cont	libplot/cont.c:	int cont (xi,yi) { int ret; return ret; }
copy	macros.h:#define copy(srce,dest) cat(dest,srce,0)
cos	libm TRIG(3M):	double cos (x) double x; { return (x); }
cosh	libm SINH(3M):	double cosh (x) double x; { return (x); }
creat	libc CREAT(2):	int creat (s, m) char *s; { return (m); }
create_window	term.h:#define create_window CURS strs3._create_window
crmode	curses.h:libcurses/crmode.c:	int crmode () { int ret; return ret; }
crypt	libc CRYPT(3C):	char * crypt (k, s) char *k, *s; { return (k); }
ctermid	libc CTERMID(3S):	char * ctermid (s) char *s; { return (s); }
ctime	libc CTIME(3C):	char * ctime (t) long *t; { return (""); }
curdir	libPW/curdir.c:	int curdir (name) char name[]; { int ret; return ret; }
cursor_address	term.h:#define cursor_address CUR _Vr2_Astrs._s11
cursor_down	term.h:#define cursor_down CUR _Vr2_Astrs._s12
cursor_home	term.h:#define cursor_home CUR _Vr2_Astrs._s13
cursor_invisible	term.h:#define cursor_invisible CUR _Vr2_Astrs._s14
cursor_left	term.h:#define cursor_left CUR _Vr2_Astrs._s15
cursor_mem_address	term.h:#define cursor_mem_address CUR _Vr2_Astrs._s16
cursor_normal	term.h:#define cursor_normal CUR _Vr2_Astrs._s17
cursor_right	term.h:#define cursor_right CUR _Vr2_Astrs._s18
cursor_to_ll	term.h:#define cursor_to_ll CUR _Vr2_Astrs._s19
cursor_up	term.h:#define cursor_up CUR _Vr2_Astrs._s20
cursor_visible	term.h:#define cursor_visible CUR _Vr2_Astrs._s21
cuserid	libc CUSERID(3S):	char * cuserid (s) char *s; { return (s); }
daylight	libc CTIME(3C):	extern int daylight;
def_prog_mode	libcurses/def_prog.c:	int def_prog_mode () { int ret; return ret; }
def_shell_mode	libcurses/def_shell.c:	int def_shell_mode () { int ret; return ret; }
del_curterm	term.h:#define del_curterm delterm
delay_output	libcurses/naps.c:	int delay_output (ms) int ms; { int ret; return ret; }
delch	curses.h:#define delch() wdelch(stdscr)
delete_character	term.h:#define delete_character CUR _Vr2_Astrs._s22
delete_line	term.h:#define delete_line CUR _Vr2_Astrs._s23
deleteln	curses.h:#define deleteln() wdeleteln(stdscr)
delwin	libcurses/delwin.c:	int delwin (win) WINDOW *win; { int ret; return ret; }
dest_tabs_magic_smso	term.h:#define dest_tabs_magic_smso CUR _b18
dial	libc DIAL(3C):	int dial (c) CALL c; { return (0); }
dial_phone	term.h:#define dial_phone CURS strs3._dial_phone
dis_status_line	term.h:#define dis_status_line CUR _Vr2_Astrs._s24
dismaus	libc MAUS(2) PDP-11 IPC:	int dismaus (s) char *s; { return (0); }
display_clock	term.h:#define display_clock CURS strs3._display_clock
dname	libPW/dname.c:	char * dname (p) char *p; { char *ret; return ret; }
dot	libplot/dot.c:	int dot (xi,yi,dx,n,pat) int pat[]; { int ret; return ret; }
down_half_line	term.h:#define down_half_line CUR _Vr2_Astrs._s25
draino	libcurses/draino.c:	int draino (ms) int ms; { int ret; return ret; }
drand48	libc DRAND48(3C):	double drand48 () { return (0.0); }
dup	libc DUP(2):	int dup (f) { return (f); }
eat_newline_glitch	term.h:#define eat_newline_glitch CUR _b5
echo	curses.h:libcurses/echo.c:	int echo () { int ret; return ret; }
echochar	curses.h:#define echochar(ch) wechochar(stdscr, ch)
ecmp	regexp.h:#define ecmp(s1, s2, n) (!strncmp(s1, s2, n))
ecvt	libc ECVT(3C):	char * ecvt (v, n, d, s) double v; int *d, *s; { return (""); }
edata	libc END(3C):	extern int edata;
ena_acs	term.h:#define ena_acs CURS strs2._ena_acs
enabmaus	libc MAUS(2) PDP-11 IPC:	char * enabmaus (m) { return (""); }
encrypt	libc CRYPT(3C):	void encrypt (b, e) char *b; {}
end	libc END(3C):	extern int end;
endgrent	libc GETGRENT(3C):	void endgrent () {}
endpwent	libc GETPWENT(3C):	void endpwent () {}
endwin	libcurses/endwin.c:	int endwin () { int ret; return ret; }
enter_alt_charset_mode	term.h:#define enter_alt_charset_mode CUR _Vr2_Astrs._s26
enter_am_mode	term.h:#define enter_am_mode CURS strs2._entr_am_mode
enter_blink_mode	term.h:#define enter_blink_mode CUR _Vr2_Astrs._s27
enter_bold_mode	term.h:#define enter_bold_mode CUR _Vr2_Astrs._s28
enter_ca_mode	term.h:#define enter_ca_mode CUR _Vr2_Astrs._s29
enter_delete_mode	term.h:#define enter_delete_mode CUR _Vr2_Astrs._s30
enter_dim_mode	term.h:#define enter_dim_mode CUR _Vr2_Astrs._s31
enter_insert_mode	term.h:#define enter_insert_mode CUR _Vr2_Astrs._s32
enter_protected_mode	term.h:#define enter_protected_mode CUR _Vr2_Astrs._s34
enter_reverse_mode	term.h:#define enter_reverse_mode CUR _Vr2_Astrs._s35
enter_secure_mode	term.h:#define enter_secure_mode CUR _Vr2_Astrs._s33
enter_standout_mode	term.h:#define enter_standout_mode CUR _Vr2_Astrs._s36
enter_underline_mode	term.h:#define enter_underline_mode CUR _Vr2_Astrs._s37
enter_xon_mode	term.h:#define enter_xon_mode CURS strs2._entr_xon_mode
environ	libc EXEC(2):	extern char **environ;
equal	macros.h:#define equal(str1,str2) !strcmp(str1,str2)
erand48	libc DRAND48(3C):	double erand48 (x) unsigned short x[3]; { return (0.0); }
erase	curses.h, libplot/erase.c:	int erase () { int ret; return ret; }
erase_chars	term.h:#define erase_chars CUR _Vr2_Astrs._s38
erase_overstrike	term.h:#define erase_overstrike CUR _b6
erasechar	libcurses/erasechar.c:	char erasechar () { char ret; return ret; }
erf	libm ERF(3M):	double erf (x) double x; { return (x); }
erfc	libm ERF(3M):	double erfc (x) double x; { return (x); }
errno	libc PERROR(3C):	extern int errno;
etext	libc END(3C):	extern int etext;
execl	libc EXEC(2):	/*VARARGS1*/ int execl (f, a) char *f, *a; { return (0); }
execle	libc EXEC(2):	/*VARARGS1*/ int execle (f, a, e) char *f, *a, *e[]; { return (0); }
execlp	libc EXEC(2):	/*VARARGS1*/ int execlp (f, a) char *f, *a; { return (0); }
execv	libc EXEC(2):	int execv (s, v) char *s, *v[]; { return (0); }
execve	libc EXEC(2):	int execve (f, a, e) char *f, *a[], *e[]; { return (0); }
execvp	libc EXEC(2):	int execvp (s, v) char *s, *v[]; { return (0); }
exists	macros.h:#define exists(file) (stat(file,&Statbuf)<0 ? 0:Statbuf.st_mode)
exit	libc EXIT(2):	void exit (s) {}
exit_alt_charset_mode	term.h:#define exit_alt_charset_mode CUR _Vr2_Astrs._s39
exit_am_mode	term.h:#define exit_am_mode CURS strs2._exit_am_mode
exit_attribute_mode	term.h:#define exit_attribute_mode CUR _Vr2_Astrs._s40
exit_ca_mode	term.h:#define exit_ca_mode CUR _Vr2_Astrs._s41
exit_delete_mode	term.h:#define exit_delete_mode CUR _Vr2_Astrs._s42
exit_insert_mode	term.h:#define exit_insert_mode CUR _Vr2_Astrs._s43
exit_standout_mode	term.h:#define exit_standout_mode CUR _Vr2_Astrs._s44
exit_underline_mode	term.h:#define exit_underline_mode CUR _Vr2_Astrs._s45
exit_xon_mode	term.h:#define exit_xon_mode CURS strs2._exit_xon_mode
exp	libm EXP(3M):	double exp (x) double x; { return (x); }
fabs	libm FLOOR(3M):	double fabs (x) double x; { return (x); }
fatal	libPW/fatal.c:	int fatal (msg) char *msg; { int ret; return ret; }
fclose	libc FCLOSE(3S):	int fclose (f) FILE *f; { return (0); }
fcntl	libc FCNTL(2):	int fcntl (f, c, a) { return (f); }
fcvt	libc ECVT(3C):	char * fcvt (v, n, d, s) double v; int *d, *s; { return (""); }
fdfopen	libPW/fdfopen.c:	FILE * fdfopen (fd, mode) int fd, mode; { FILE *ret; return ret; }
fdopen	libc FOPEN(3S):	FILE * fdopen (f, t) char *t; { return (stdin); }
feof	stdio.h:libc FERROR(3S):	int feof (f) FILE *f; { return (0); }
ferror	stdio.h:libc FERROR(3S):	int ferror (f) FILE *f; { return (0); }
fflush	libc FCLOSE(3S):	int fflush (f) FILE *f; { return (0); }
fgetc	libc GETC(3S):	int fgetc (f) FILE *f; { return (0); }
fgetgrent	libc GETGRENT(3C):	struct group * fgetgrent (f) FILE *f; { struct group x; return (&x); }
fgetpwent	libc GETPWENT(3C):	struct passwd * fgetpwent (f) FILE *f; { struct passwd x; return (&x); }
fgets	libc GETS(3S):	char * fgets (s, n, f) char *s; FILE *f; { return (s); }
fileno	stdio.h:libc FERROR(3S):	int fileno (f) FILE *f; { return (0); }
fixterm	term.h:libcurses/fixterm.c:	int fixterm () { int ret; return ret; }
flash	curses.h:libcurses/flash.c:	int flash () { int ret; return ret; }
flash_hook	term.h:#define flash_hook CURS strs3._flash_hook
flash_screen	term.h:#define flash_screen CUR _Vr2_Astrs._s46
floor	libm FLOOR(3M):	double floor (x) double x; { return (x); }
flushinp	libcurses/flushinp.c:	int flushinp () { int ret; return ret; }
fmod	libm FLOOR(3M):	double fmod (x, y) double x, y; { return (x); }
fopen	libc FOPEN(3S):	FILE * fopen (f, t) char *f, *t; { return (stdin); }
fork	libc FORK(2):	int fork () { return (0); }
form_feed	term.h:#define form_feed CUR _Vr2_Astrs._s47
fp_except	ieeefp.h:#define fp_except int
fprintf	libc PRINTF(3S):	/*VARARGS2 PRINTFLIKE2*/ int fprintf (f, s) FILE *f; char *s; { return (0); }
fputc	libc PUTC(3S):	int fputc (c, f) FILE *f; { return (c); }
fputs	libc PUTS(3S):	int fputs (s, f) char *s; FILE *f; { return (0); }
fread	libc FREAD(3S):	int fread (b, s, n, f) char *b; FILE *f; { return (n); }
free	libc MALLOC(3C):	void free (s) char *s; {}
freeldptr	libld/freeldptr.c:	int freeldptr (ldptr) LDFILE *ldptr; { int ret; return ret; }
freemaus	libc MAUS(2) PDP-11 IPC:	int freemaus (m) { return (m); }
freopen	libc FOPEN(3S):	FILE * freopen (f, t, s) char *f, *t; FILE *s; { return (s); }
frexp	libc FREXP(3C):	double frexp (x, e) double x; int *e; { return (x); }
from_status_line	term.h:#define from_status_line CUR _Vr2_Astrs._s48
fscanf	libc SCANF(3S):	/*VARARGS2 SCANFLIKE2*/ int fscanf (f, s) FILE *f; char *s; { return (0); }
fseek	libc FSEEK(3S):	int fseek (f, o, p) FILE *f; long o; { return (p); }
fstat	libc STAT(2):	int fstat (f, b) struct stat *b; { return (f); }
ftell	libc FSEEK(3S):	long ftell (f) FILE *f; { return (0L); }
ftok	libc STDIPC(3C):	key_t ftok (s, i) char *s; { return ((key_t)0); }
ftw	libc FTW(3C):	int ftw (p, f, d) char *p; int (*f)(); { return (d); }
fwrite	libc FREAD(3S):	int fwrite (b, s, n, f) char *b; FILE *f; { return (n); }
gamma	libm GAMMA(3M):	double gamma (x) double x; { return (x); }
garbagedlines	curses.h:#define garbagedlines wredrawln
garbagedwin	curses.h:#define garbagedwin redrawwin
gcvt	libc ECVT(3C):	char * gcvt (v, n, b) double v; char *b; { return (b); }
generic_type	term.h:#define generic_type CUR _b7
getattrs	curses.h:#define getattrs(win) ((win)->_attrs)
getbegx	curses.h:#define getbegx(win) ((win)->_begx)
getbegy	curses.h:#define getbegy(win) ((win)->_begy)
getbegyx	curses.h:#define getbegyx(win,y,x) ((y) = getbegy(win), (x) = getbegx(win))
getbkgd	curses.h:#define getbkgd(win) ((win)->_bkgd)
getc	stdio.h:libc GETC(3S):	int getc (f) FILE *f; { return (0); }
getch	curses.h:#define getch() wgetch(stdscr)
getchar	stdio.h:libc GETC(3S):	int getchar () { return (0); }
getcurx	curses.h:#define getcurx(win) ((win)->_curx)
getcury	curses.h:#define getcury(win) ((win)->_cury)
getcwd	libc GETCWD(3C):	char * getcwd (b, s) char *b; { return (b); }
getegid	libc GETUID(2):	int getegid () { return (0); }
getenv	libc GETENV(3C):	char * getenv (n) char *n; { return (n); }
geteuid	libc GETUID(2):	int geteuid () { return (0); }
getgid	libc GETUID(2):	int getgid () { return (0); }
getgrent	libc GETGRENT(3C):	struct group * getgrent () { static struct group x; return (&x); }
getgrgid	libc GETGRENT(3C):	struct group * getgrgid (g) { static struct group x; return (&x); }
getgrnam	libc GETGRENT(3C):	struct group * getgrnam (n) char *n; { static struct group x; return (&x); }
getlogin	libc GETLOGIN(3C):	char * getlogin () { return (""); }
getmaus	libc MAUS(2) PDP-11 IPC:	int getmaus (p, o) char *p; { return (o); }
getmaxx	curses.h:#define getmaxx(win) ((win)->_maxx)
getmaxy	curses.h:#define getmaxy(win) ((win)->_maxy)
getmaxyx	curses.h:#define getmaxyx(win,y,x) ((y) = getmaxy(win), (x) = getmaxx(win))
getopt	libc GETOPT(3C):	int getopt (c, v, o) char **v, *o; { return (c); }
getparx	curses.h:#define getparx(win) ((win)->_parx)
getpary	curses.h:#define getpary(win) ((win)->_pary)
getparyx	curses.h:#define getparyx(win,y,x) ((y) = getpary(win), (x) = getparx(win))
getpass	libc GETPASS(3C):	char * getpass (s) char *s; { return (s); }
getpgrp	libc GETPID(2):	int getpgrp () { return (0); }
getpid	libc GETPID(2):	int getpid () { return (0); }
getppid	libc GETPID(2):	int getppid () { return (0); }
getpw	libc GETPW(3C):	int getpw (u, b) char *b; { return (u); }
getpwent	libc GETPWENT(3C):	struct passwd * getpwent () { static struct passwd x; return (&x); }
getpwnam	libc GETPWENT(3C):	struct passwd * getpwnam (n) char *n; { static struct passwd x; return (&x); }
getpwuid	libc GETPWENT(3C):	struct passwd * getpwuid (u) { static struct passwd x; return (&x); }
gets	libc GETS(3S):	char * gets (s) char *s; { return (s); }
getsh	libcurses/setupterm.c:	int getsh (p) char *p; { int ret; return ret; }
getstr	curses.h:#define getstr(str) wgetstr(stdscr, str)
getsyx	curses.h:#define getsyx(y,x) _getsyx(&(y),&(x))
gettmode	curses.h:libcurses/gettmode.c:	int gettmode () { int ret; return ret; }
getuid	libc GETUID(2):	int getuid () { return (0); }
getw	libc GETC(3S):	int getw (f) FILE *f; { return (0); }
getyx	curses.h:#define getyx(win,y,x) ((y) = getcury(win), (x) = getcurx(win))
giveup	libPW/giveup.c:	int giveup (dump) { int ret; return ret; }
gmtime	libc CTIME(3C):	struct tm * gmtime (c) long *c; { static struct tm x; return (&x); }
goto_window	term.h:#define goto_window CURS strs3._goto_window
gsignal	libc SSIGNAL(3C):	int gsignal (s) { return (s); }
halfdelay	curses.h:#define halfdelay(tens) ttimeout((tens)*100)
hangup	term.h:#define hangup CURS strs3._hangup
hard_copy	term.h:#define hard_copy CUR _b8
hard_cursor	term.h:#define hard_cursor CURB _hard_cursor
has_ic	libcurses/has_ic.c:	int has_ic () { int ret; return ret; }
has_il	libcurses/has_il.c:	int has_il () { int ret; return ret; }
has_meta_key	term.h:#define has_meta_key CUR _b9
has_status_line	term.h:#define has_status_line CUR _b10
hcreate	libc HSEARCH(3C):	int hcreate (n) unsigned n; { return (0); }
hdestroy	libc HSEARCH(3C):	void hdestroy () {}
hline	curses.h:#define hline(c,num) whline(stdscr,c,num)
hsearch	libc HSEARCH(3C):	ENTRY * hsearch (i, a) ENTRY i; ACTION a; { return (&i); }
hypot	libm HYPOT(3M):	double hypot (x, y) double x, y; { return (x); }
idcok	curses.h:#define idcok(win,bf) ((win)->_use_idc = ((bf) ? TRUE : FALSE))
idlok	libcurses/idlok.c:	int idlok (win,bf) WINDOW *win; int bf; { int ret; return ret; }
imatch	libPW/imatch.c:	int imatch (prefix,string) char *prefix, *string; { int ret; return ret; }
inch	curses.h:#define inch() winch(stdscr)
inchnstr	curses.h:#define inchnstr(str,n) winchnstr(stdscr,str,n)
inchstr	curses.h:#define inchstr(str) winchstr(stdscr,str)
index	libPW/index.c:	int index (as1,as2) char *as1,*as2; { int ret; return ret; }
init_1string	term.h:#define init_1string CUR _Vr2_Astrs._s49
init_2string	term.h:#define init_2string CUR _Vr2_Astrs._s50
init_3string	term.h:#define init_3string CUR _Vr2_Astrs._s51
init_file	term.h:#define init_file CUR _Vr2_Astrs._s52
init_prog	term.h:#define init_prog CUR _Vr2_Bstrs._s139
init_tabs	term.h:#define init_tabs CUR _c2
initscr	libcurses/initscr.c:	WINDOW * initscr () { WINDOW * ret; return ret; }
innstr	curses.h:#define innstr(str,n) winnstr(stdscr,(str),(n))
insch	curses.h:#define insch(c) winsch(stdscr,c)
insdelln	curses.h:#define insdelln(id) winsdelln(stdscr,id)
insert_character	term.h:#define insert_character CUR _Vr2_Astrs._s53
insert_line	term.h:#define insert_line CUR _Vr2_Astrs._s54
insert_null_glitch	term.h:#define insert_null_glitch CUR _b11
insert_padding	term.h:#define insert_padding CUR _Vr2_Astrs._s55
insertln	curses.h:#define insertln() winsertln(stdscr)
insnstr	curses.h:#define insnstr(s,n) winsnstr(stdscr,s,n)
insstr	curses.h:#define insstr(s) winsstr(stdscr,s)
instr	curses.h:#define instr(str) winstr(stdscr,(str))
intrflush	curses.h:libcurses/intrflush.c:	int intrflush (win,bf) WINDOW *win; int bf; { int ret; return ret; }
ioctl	libc IOCTL(2):	/*VARARGS2*/ int ioctl (f, r, a) { return (f); }
is_linetouched	curses.h:#define is_linetouched(win,line) ((((line) >= (win)->_maxy) || ((line) < 0)) ? ERR : (((win)->_firstch[(line)] == _INFINITY) ? FALSE : TRUE))
is_wintouched	curses.h:#define is_wintouched(win) ((win)->_flags & _WINCHANGED)
isalnum	libc CTYPE(3C):ctype.h:#define isalnum(c) ((_ctype + 1)[c] & (_U | _L | _N))
isalpha	libc CTYPE(3C):ctype.h:#define isalpha(c) ((_ctype + 1)[c] & (_U | _L))
isascii	libc CTYPE(3C):ctype.h:#define isascii(c) (!((c) & ~0177))
isatty	libc TTYNAME(3C):	int isatty (f) { return (f); }
iscntrl	libc CTYPE(3C):ctype.h:#define iscntrl(c) ((_ctype + 1)[c] & _C)
isdigit	libc CTYPE(3C):ctype.h:#define isdigit(c) ((_ctype + 1)[c] & _N)
isgraph	libc CTYPE(3C):ctype.h:#define isgraph(c) ((_ctype + 1)[c] & (_P | _U | _L | _N))
islower	libc CTYPE(3C):ctype.h:#define islower(c) ((_ctype + 1)[c] & _L)
isnanf	ieeefp.h:#define isnanf(x) (((*(int *)&(x) & 0x7f800000L)==0x7f800000L)&& \
isprint	libc CTYPE(3C):ctype.h:#define isprint(c) ((_ctype + 1)[c] & (_P | _U | _L | _N | _B))
ispunct	libc CTYPE(3C):ctype.h:#define ispunct(c) ((_ctype + 1)[c] & _P)
isspace	libc CTYPE(3C):ctype.h:#define isspace(c) ((_ctype + 1)[c] & _S)
isupper	libc CTYPE(3C):ctype.h:#define isupper(c) ((_ctype + 1)[c] & _U)
isxdigit	libc CTYPE(3C):ctype.h:#define isxdigit(c) ((_ctype + 1)[c] & _X)
j0	libm BESSEL(3M):	double j0 (x) double x; { return (x); }
j1	libm BESSEL(3M):	double j1 (x) double x; { return (x); }
jn	libm BESSEL(3M):	double jn (n, x) double x; { return (x); }
jrand48	libc DRAND48(3C):	long jrand48 (x) unsigned short x[3]; { return (0L); }
key_a1	term.h:#define key_a1 CUR _Vr2_Bstrs._s140
key_a3	term.h:#define key_a3 CUR _Vr2_Bstrs._s141
key_b2	term.h:#define key_b2 CUR _Vr2_Bstrs._s142
key_backspace	term.h:#define key_backspace CUR _Vr2_Astrs._s56
key_beg	term.h:#define key_beg CURS strs2._ky_beg
key_btab	term.h:#define key_btab CURS strs2._ky_btab
key_c1	term.h:#define key_c1 CUR _Vr2_Bstrs._s143
key_c3	term.h:#define key_c3 CUR _Vr2_Bstrs._s144
key_cancel	term.h:#define key_cancel CURS strs2._ky_cancel
key_catab	term.h:#define key_catab CUR _Vr2_Astrs._s57
key_clear	term.h:#define key_clear CUR _Vr2_Astrs._s58
key_close	term.h:#define key_close CURS strs2._ky_close
key_command	term.h:#define key_command CURS strs2._ky_command
key_copy	term.h:#define key_copy CURS strs2._ky_copy
key_create	term.h:#define key_create CURS strs2._ky_create
key_ctab	term.h:#define key_ctab CUR _Vr2_Astrs._s59
key_dc	term.h:#define key_dc CUR _Vr2_Astrs._s60
key_dl	term.h:#define key_dl CUR _Vr2_Astrs._s61
key_down	term.h:#define key_down CUR _Vr2_Astrs._s62
key_eic	term.h:#define key_eic CUR _Vr2_Astrs._s63
key_end	term.h:#define key_end CURS strs2._ky_end
key_enter	term.h:#define key_enter CURS strs2._ky_enter
key_eol	term.h:#define key_eol CUR _Vr2_Astrs._s64
key_eos	term.h:#define key_eos CUR _Vr2_Astrs._s65
key_exit	term.h:#define key_exit CURS strs2._ky_exit
key_f0	term.h:#define key_f0 CUR _Vr2_Astrs._s66
key_f1	term.h:#define key_f1 CUR _Vr2_Astrs._s67
key_f10	term.h:#define key_f10 CUR _Vr2_Astrs._s68
key_f11	term.h:#define key_f11 CURS strs3._ky_f11
key_f12	term.h:#define key_f12 CURS strs3._ky_f12
key_f13	term.h:#define key_f13 CURS strs3._ky_f13
key_f14	term.h:#define key_f14 CURS strs3._ky_f14
key_f15	term.h:#define key_f15 CURS strs3._ky_f15
key_f16	term.h:#define key_f16 CURS strs3._ky_f16
key_f17	term.h:#define key_f17 CURS strs3._ky_f17
key_f18	term.h:#define key_f18 CURS strs3._ky_f18
key_f19	term.h:#define key_f19 CURS strs3._ky_f19
key_f2	term.h:#define key_f2 CUR _Vr2_Astrs._s69
key_f20	term.h:#define key_f20 CURS strs3._ky_f20
key_f21	term.h:#define key_f21 CURS strs3._ky_f21
key_f22	term.h:#define key_f22 CURS strs3._ky_f22
key_f23	term.h:#define key_f23 CURS strs3._ky_f23
key_f24	term.h:#define key_f24 CURS strs3._ky_f24
key_f25	term.h:#define key_f25 CURS strs3._ky_f25
key_f26	term.h:#define key_f26 CURS strs3._ky_f26
key_f27	term.h:#define key_f27 CURS strs3._ky_f27
key_f28	term.h:#define key_f28 CURS strs3._ky_f28
key_f29	term.h:#define key_f29 CURS strs3._ky_f29
key_f3	term.h:#define key_f3 CUR _Vr2_Astrs._s70
key_f30	term.h:#define key_f30 CURS strs3._ky_f30
key_f31	term.h:#define key_f31 CURS strs3._ky_f31
key_f32	term.h:#define key_f32 CURS strs3._ky_f32
key_f33	term.h:#define key_f33 CURS strs3._ky_f33
key_f34	term.h:#define key_f34 CURS strs3._ky_f34
key_f35	term.h:#define key_f35 CURS strs3._ky_f35
key_f36	term.h:#define key_f36 CURS strs3._ky_f36
key_f37	term.h:#define key_f37 CURS strs3._ky_f37
key_f38	term.h:#define key_f38 CURS strs3._ky_f38
key_f39	term.h:#define key_f39 CURS strs3._ky_f39
key_f4	term.h:#define key_f4 CUR _Vr2_Astrs._s71
key_f40	term.h:#define key_f40 CURS strs3._ky_f40
key_f41	term.h:#define key_f41 CURS strs3._ky_f41
key_f42	term.h:#define key_f42 CURS strs3._ky_f42
key_f43	term.h:#define key_f43 CURS strs3._ky_f43
key_f44	term.h:#define key_f44 CURS strs3._ky_f44
key_f45	term.h:#define key_f45 CURS strs3._ky_f45
key_f46	term.h:#define key_f46 CURS strs3._ky_f46
key_f47	term.h:#define key_f47 CURS strs3._ky_f47
key_f48	term.h:#define key_f48 CURS strs3._ky_f48
key_f49	term.h:#define key_f49 CURS strs3._ky_f49
key_f5	term.h:#define key_f5 CUR _Vr2_Astrs._s72
key_f50	term.h:#define key_f50 CURS strs3._ky_f50
key_f51	term.h:#define key_f51 CURS strs3._ky_f51
key_f52	term.h:#define key_f52 CURS strs3._ky_f52
key_f53	term.h:#define key_f53 CURS strs3._ky_f53
key_f54	term.h:#define key_f54 CURS strs3._ky_f54
key_f55	term.h:#define key_f55 CURS strs3._ky_f55
key_f56	term.h:#define key_f56 CURS strs3._ky_f56
key_f57	term.h:#define key_f57 CURS strs3._ky_f57
key_f58	term.h:#define key_f58 CURS strs3._ky_f58
key_f59	term.h:#define key_f59 CURS strs3._ky_f59
key_f6	term.h:#define key_f6 CUR _Vr2_Astrs._s73
key_f60	term.h:#define key_f60 CURS strs3._ky_f60
key_f61	term.h:#define key_f61 CURS strs3._ky_f61
key_f62	term.h:#define key_f62 CURS strs3._ky_f62
key_f63	term.h:#define key_f63 CURS strs3._ky_f63
key_f7	term.h:#define key_f7 CUR _Vr2_Astrs._s74
key_f8	term.h:#define key_f8 CUR _Vr2_Astrs._s75
key_f9	term.h:#define key_f9 CUR _Vr2_Astrs._s76
key_find	term.h:#define key_find CURS strs2._ky_find
key_help	term.h:#define key_help CURS strs2._ky_help
key_home	term.h:#define key_home CUR _Vr2_Astrs._s77
key_ic	term.h:#define key_ic CUR _Vr2_Astrs._s78
key_il	term.h:#define key_il CUR _Vr2_Astrs._s79
key_left	term.h:#define key_left CUR _Vr2_Astrs._s80
key_ll	term.h:#define key_ll CUR _Vr2_Astrs._s81
key_mark	term.h:#define key_mark CURS strs2._ky_mark
key_message	term.h:#define key_message CURS strs2._ky_message
key_move	term.h:#define key_move CURS strs2._ky_move
key_next	term.h:#define key_next CURS strs2._ky_next
key_npage	term.h:#define key_npage CUR _Vr2_Astrs._s82
key_open	term.h:#define key_open CURS strs2._ky_open
key_options	term.h:#define key_options CURS strs2._ky_options
key_ppage	term.h:#define key_ppage CUR _Vr2_Astrs._s83
key_previous	term.h:#define key_previous CURS strs2._ky_previous
key_print	term.h:#define key_print CURS strs2._ky_print
key_redo	term.h:#define key_redo CURS strs2._ky_redo
key_reference	term.h:#define key_reference CURS strs2._ky_reference
key_refresh	term.h:#define key_refresh CURS strs2._ky_refresh
key_replace	term.h:#define key_replace CURS strs2._ky_replace
key_restart	term.h:#define key_restart CURS strs2._ky_restart
key_resume	term.h:#define key_resume CURS strs2._ky_resume
key_right	term.h:#define key_right CUR _Vr2_Astrs._s84
key_save	term.h:#define key_save CURS strs2._ky_save
key_sbeg	term.h:#define key_sbeg CURS strs2._ky_sbeg
key_scancel	term.h:#define key_scancel CURS strs2._ky_scancel
key_scommand	term.h:#define key_scommand CURS strs2._ky_scommand
key_scopy	term.h:#define key_scopy CURS strs2._ky_scopy
key_screate	term.h:#define key_screate CURS strs2._ky_screate
key_sdc	term.h:#define key_sdc CURS strs2._ky_sdc
key_sdl	term.h:#define key_sdl CURS strs2._ky_sdl
key_select	term.h:#define key_select CURS strs2._ky_select
key_send	term.h:#define key_send CURS strs2._ky_send
key_seol	term.h:#define key_seol CURS strs2._ky_seol
key_sexit	term.h:#define key_sexit CURS strs2._ky_sexit
key_sf	term.h:#define key_sf CUR _Vr2_Astrs._s85
key_sfind	term.h:#define key_sfind CURS strs2._ky_sfind
key_shelp	term.h:#define key_shelp CURS strs2._ky_shelp
key_shome	term.h:#define key_shome CURS strs2._ky_shome
key_sic	term.h:#define key_sic CURS strs3._ky_sic
key_sleft	term.h:#define key_sleft CURS strs3._ky_sleft
key_smessage	term.h:#define key_smessage CURS strs3._ky_smessage
key_smove	term.h:#define key_smove CURS strs3._ky_smove
key_snext	term.h:#define key_snext CURS strs3._ky_snext
key_soptions	term.h:#define key_soptions CURS strs3._ky_soptions
key_sprevious	term.h:#define key_sprevious CURS strs3._ky_sprevious
key_sprint	term.h:#define key_sprint CURS strs3._ky_sprint
key_sr	term.h:#define key_sr CUR _Vr2_Astrs._s86
key_sredo	term.h:#define key_sredo CURS strs3._ky_sredo
key_sreplace	term.h:#define key_sreplace CURS strs3._ky_sreplace
key_sright	term.h:#define key_sright CURS strs3._ky_sright
key_srsume	term.h:#define key_srsume CURS strs3._ky_srsume
key_ssave	term.h:#define key_ssave CURS strs3._ky_ssave
key_ssuspend	term.h:#define key_ssuspend CURS strs3._ky_ssuspend
key_stab	term.h:#define key_stab CUR _Vr2_Astrs._s87
key_sundo	term.h:#define key_sundo CURS strs3._ky_sundo
key_suspend	term.h:#define key_suspend CURS strs2._ky_suspend
key_undo	term.h:#define key_undo CURS strs2._ky_undo
key_up	term.h:#define key_up CUR _Vr2_Astrs._s88
keypad	libcurses/keypad.c:	int keypad (win,bf) WINDOW *win; int bf; { int ret; return ret; }
keypad_local	term.h:#define keypad_local CUR _Vr2_Astrs._s89
keypad_xmit	term.h:#define keypad_xmit CUR _Vr2_Astrs._s90
kill	libc KILL(2):	int kill (i, s) { return (i); }
killchar	libcurses/killchar.c:	char killchar () { char ret; return ret; }
l3tol	libc L3TOL(3C):	void l3tol (l, c, n) long *l; char *c; {}
l64a	libc A64L(3C):	char * l64a (l) long l; { return (""); }
lab_f0	term.h:#define lab_f0 CUR _Vr2_Astrs._s91
lab_f1	term.h:#define lab_f1 CUR _Vr2_Astrs._s92
lab_f10	term.h:#define lab_f10 CUR _Vr2_Astrs._s93
lab_f2	term.h:#define lab_f2 CUR _Vr2_Astrs._s94
lab_f3	term.h:#define lab_f3 CUR _Vr2_Astrs._s95
lab_f4	term.h:#define lab_f4 CUR _Vr2_Astrs._s96
lab_f5	term.h:#define lab_f5 CUR _Vr2_Astrs._s97
lab_f6	term.h:#define lab_f6 CUR _Vr2_Astrs._s98
lab_f7	term.h:#define lab_f7 CUR _Vr2_Astrs._s99
lab_f8	term.h:#define lab_f8 CUR _Vr2_Astrs._s100
lab_f9	term.h:#define lab_f9 CUR _Vr2_Bstrs._s101
label	libplot/label.c:	int label (s) char *s; { int ret; return ret; }
label_format	term.h:#define label_format CURS strs3._labl_format
label_height	term.h:#define label_height CURN _labl_height
label_off	term.h:#define label_off CURS strs2._labl_off
label_on	term.h:#define label_on CURS strs2._labl_on
label_width	term.h:#define label_width CURN _labl_width
lcong48	libc DRAND48(3C):	void lcong48 (p) unsigned short p[7]; {}
ldaclose	libld/ldaclose.c:	int ldaclose (ldptr) LDFILE *ldptr; { int ret; return ret; }
ldahread	libld/ldahread.c:	int ldahread (ldptr, arhead) LDFILE *ldptr; ARCHDR *arhead; { int ret; return ret; }
ldaopen	libld/ldaopen.c:	LDFILE * ldaopen (filename, oldptr) char *filename; LDFILE *oldptr; { LDFILE *ret; return ret; }
ldclose	libld/ldclose.c:	int ldclose (ldptr) LDFILE *ldptr; { int ret; return ret; }
ldexp	libc FREXP(3C):	double ldexp (v, e) double v; { return (v); }
ldfhread	libld/ldfhread.c:	int ldfhread (ldptr, filehead) LDFILE *ldptr; FILHDR *filehead; { int ret; return ret; }
ldgetname	libld/ldgetname.c:	char * ldgetname (ldptr, symentry) register LDFILE *ldptr; register SYMENT *symentry; { char *ret; return ret; }
ldlinit	libld/ldlread.c:	int ldlinit (ldptr, fcnindx) LDFILE *ldptr; long fcnindx; { int ret; return ret; }
ldlitem	libld/ldlread.c:	int ldlitem (ldptr, linenum, linent) LDFILE *ldptr; unsigned short linenum; LINENO *linent; { int ret; return ret; }
ldlread	libld/ldlread.c:	int ldlread (ldptr, fcnindx, linenum, linent) LDFILE *ldptr; long fcnindx; unsigned short linenum; LINENO *linent; { int ret; return ret; }
ldlseek	libld/ldlseek.c:	int ldlseek (ldptr, sectnum) LDFILE *ldptr; unsigned short sectnum; { int ret; return ret; }
ldnlseek	libld/ldnlseek.c:	int ldnlseek (ldptr, sectname) LDFILE *ldptr; char *sectname; { int ret; return ret; }
ldnrseek	libld/ldnrseek.c:	int ldnrseek (ldptr, sectname) LDFILE *ldptr; char *sectname; { int ret; return ret; }
ldnshread	libld/ldnshread.c:	int ldnshread (ldptr, sectname, secthdr) LDFILE *ldptr; char *sectname; SCNHDR *secthdr; { int ret; return ret; }
ldnsseek	libld/ldnsseek.c:	int ldnsseek (ldptr, sectname) LDFILE *ldptr; char *sectname; { int ret; return ret; }
ldohseek	libld/ldohseek.c:	int ldohseek (ldptr) LDFILE *ldptr; { int ret; return ret; }
ldopen	libld/ldopen.c:	LDFILE * ldopen (filename, ldptr) char *filename; LDFILE *ldptr; { LDFILE *ret; return ret; }
ldrseek	libld/ldrseek.c:	int ldrseek (ldptr, sectnum) LDFILE *ldptr; unsigned short sectnum; { int ret; return ret; }
ldshread	libld/ldshread.c:	int ldshread (ldptr, sectnum, secthdr) LDFILE *ldptr; unsigned short sectnum; SCNHDR *secthdr; { int ret; return ret; }
ldsseek	libld/ldsseek.c:	int ldsseek (ldptr, sectnum) LDFILE *ldptr; unsigned short sectnum; { int ret; return ret; }
ldtbindex	libld/ldtbindex.c:	long ldtbindex (ldptr) LDFILE *ldptr; { long ret; return ret; }
ldtbread	libld/ldtbread.c:	int ldtbread (ldptr, symnum, symentry) LDFILE *ldptr; long symnum; SYMENT *symentry; { int ret; return ret; }
ldtbseek	libld/ldtbseek.c:	int ldtbseek (ldptr) LDFILE *ldptr; { int ret; return ret; }
leaveok	curses.h:libcurses/leaveok.c:	int leaveok (win,bf) WINDOW *win; int bf; { int ret; return ret; }
length	macros.h:#define length(str) strlen(str)
lfind	libc LSEARCH(3C):	char * lfind (k, b, n, w, c) char *k, *b; unsigned *n, w; int (*c)(); { return (k); }
line	libplot/line.c:	int line (x0,y0,x1,y1) { int ret; return ret; }
linemod	libplot/linmod.c:	int linemod (s) char *s; { int ret; return ret; }
lines	term.h:#define lines CUR _c3
lines_of_memory	term.h:#define lines_of_memory CUR _c4
link	libc LINK(2):	int link (a, b) char *a, *b; { return (0); }
localtime	libc CTIME(3C):	struct tm * localtime (c) long *c; { static struct tm x; return (&x); }
lockit	libPW/lockit.c:	int lockit (lockfile,count,pid) char *lockfile; unsigned count; unsigned pid; { int ret; return ret; }
log	libm EXP(3M):	double log (x) double x; { return (x); }
log10	libm EXP(3M):	double log10 (x) double x; { return (x); }
logname	libPW/logname.c:	char * logname () { char *ret; return ret; }
longjmp	libc SETJMP(3C):	void longjmp (e, v) jmp_buf e; {}
longname	libcurses/longname.c:	char * longname () { char * ret; return ret; }
lrand48	libc DRAND48(3C):	long lrand48 () { return (0L); }
lsearch	libc LSEARCH(3C):	char * lsearch (k, b, n, w, c) char *k, *b; unsigned *n, w; int (*c)(); { return (k); }
lseek	libc LSEEK(2):	long lseek (f, o, w) long o; { return (o); }
ltol3	libc L3TOL(3C):	void ltol3 (c, l, n) char *c; long *l; {}
m_addch	libcurses/m_addch.c:	int m_addch (c) chtype c; { int ret; return ret; }
m_addstr	libcurses/m_addstr.c:	int m_addstr (str) char *str; { int ret; return ret; }
m_clear	libcurses/m_clear.c:	int m_clear () { int ret; return ret; }
m_erase	libcurses/m_erase.c:	int m_erase () { int ret; return ret; }
m_initscr	libcurses/miniinit.c:	WINDOW * m_initscr () { WINDOW * ret; return ret; }
m_move	libcurses/m_move.c:	int m_move (row, col) int row, col; { int ret; return ret; }
m_refresh	libcurses/m_refresh.c:	int m_refresh () { int ret; return ret; }
m_tstp	libcurses/m_tstp.c:	int m_tstp () { int ret; return ret; }
magic_cookie_glitch	term.h:#define magic_cookie_glitch CUR _c5
makenew	libcurses/makenew.c:	WINDOW * makenew (num_lines, num_cols, begy, begx) int num_lines, num_cols, begy, begx; { WINDOW * ret; return ret; }
mallinfo	libmalloc MALLOC(3X):	struct mallinfo mallinfo () { struct mallinfo s; return (s); }
malloc	libc MALLOC(3C):	char * malloc (s) unsigned s; { return (""); }
mallopt	libmalloc MALLOC(3X):	int mallopt (cmd, value) int cmd, value; { return cmd+value; }
matherr	libm MATHERR(3M):	int matherr (p) struct exception *p; { return (0); }
max	macros.h:#define max(a,b) (a<b ? b : a)
max_attributes	term.h:#define max_attributes CURN _max_attributes
maximum_windows	term.h:#define maximum_windows CURN _maximum_windows
memccpy	libc MEMORY(3C):	char * memccpy (a, b, c, n) char *a, *b; { return (a); }
memchr	libc MEMORY(3C):	char * memchr (s, c, n) char *s; { return (s); }
memcmp	libc MEMORY(3C):	int memcmp (a, b, n) char *a, *b; { return (n); }
memcpy	libc MEMORY(3C):	char * memcpy (a, b, n) char *a, *b; { return (a); }
memory_above	term.h:#define memory_above CUR _b12
memory_below	term.h:#define memory_below CUR _b13
memset	libc MEMORY(3C):	char * memset (s, c, n) char *s; { return (s); }
meta	curses.h:libcurses/meta.c:	int meta (win,bf) WINDOW *win; int bf; { int ret; return ret; }
meta_off	term.h:#define meta_off CUR _Vr2_Bstrs._s102
meta_on	term.h:#define meta_on CUR _Vr2_Bstrs._s103
min	macros.h:#define min(a,b) (a>b ? b : a)
mknod	libc MKNOD(2):	int mknod (n, m, d) char *n; { return (m); }
mktemp	libc MKTEMP(3C):	char * mktemp (t) char *t; { return (t); }
modf	libc FREXP(3C):	double modf (v, i) double v, *i; { return (v); }
monitor	libc MONITOR(3C):	void monitor (l, h, b, s, n) int (*l)(), (*h)(); WORD *b; {}
mount	libc MOUNT(2):	int mount (s, d, r) char *s, *d; { return (r); }
move	curses.h, libPW/move.c, libplot/move.c:curses.h:#define move(y, x) wmove(stdscr, y, x), char * move (a,b,n) char *a, *b; int n; { char *ret; return ret; }, int move (xi,yi) { int ret; return ret; }
move_insert_mode	term.h:#define move_insert_mode CUR _b14
move_standout_mode	term.h:#define move_standout_mode CUR _b15
mrand48	libc DRAND48(3C):	long mrand48 () { return (0L); }
msgctl	libc MSGCTL(2):	int msgctl (m, c, b) struct msqid_ds *b; { return (m); }
msgget	libc MSGGET(2):	int msgget (k, m) key_t k; { return (m); }
msgrcv	libc MSGOP(2):	int msgrcv (q, p, s, t, f) struct msgbuf *p; long t; { return (q); }
msgsnd	libc MSGOP(2):	int msgsnd (q, p, s, f) struct msgbuf *p; { return (q); }
mvaddch	curses.h:#define mvaddch(y,x,ch) mvwaddch(stdscr,y,x,ch)
mvaddchnstr	curses.h:#define mvaddchnstr(y,x,str,n) mvwaddchnstr(stdscr,y,x,str,n)
mvaddchstr	curses.h:#define mvaddchstr(y,x,str) mvwaddchstr(stdscr,y,x,str)
mvaddnstr	curses.h:#define mvaddnstr(y,x,s,n) mvwaddnstr(stdscr,y,x,s,n)
mvaddstr	curses.h:#define mvaddstr(y,x,str) mvwaddstr(stdscr,y,x,str)
mvdelch	curses.h:#define mvdelch(y,x) mvwdelch(stdscr,y,x)
mvgetch	curses.h:#define mvgetch(y,x) mvwgetch(stdscr,y,x)
mvgetstr	curses.h:#define mvgetstr(y,x,str) mvwgetstr(stdscr,y,x,str)
mvhline	curses.h:#define mvhline(y,x,c,num) mvwhline(stdscr,y,x,c,num)
mvinch	curses.h:#define mvinch(y,x) mvwinch(stdscr,y,x)
mvinchnstr	curses.h:#define mvinchnstr(y,x,str,n) mvwinchnstr(stdscr,y,x,str,n)
mvinchstr	curses.h:#define mvinchstr(y,x,str) mvwinchstr(stdscr,y,x,str)
mvinnstr	curses.h:#define mvinnstr(y,x,str,n) mvwinnstr(stdscr,y,x,(str),(n))
mvinsch	curses.h:#define mvinsch(y,x,c) mvwinsch(stdscr,y,x,c)
mvinsnstr	curses.h:#define mvinsnstr(y,x,s,n) mvwinsnstr(stdscr,y,x,s,n)
mvinsstr	curses.h:#define mvinsstr(y,x,s) mvwinsstr(stdscr,y,x,s)
mvinstr	curses.h:#define mvinstr(y,x,str) mvwinstr(stdscr,y,x,(str))
mvprintw	libcurses/mvprintw.c:	/* VARARGS3 */ int mvprintw (y, x, fmt) int y, x; char *fmt; { int ret; return ret; }
mvscanw	libcurses/mvscanw.c:	/* VARARGS3 */ int mvscanw (y, x, fmt) int y, x; char *fmt; { int ret; return ret; }
mvvline	curses.h:#define mvvline(y,x,c,num) mvwvline(stdscr,y,x,c,num)
mvwaddch	curses.h:#define mvwaddch(win,y,x,ch) (wmove(win,y,x)==ERR?ERR:waddch(win,ch))
mvwaddchnstr	curses.h:#define mvwaddchnstr(win,y,x,str,n) (wmove(win,y,x)==ERR?ERR:waddchnstr(win,str,n))
mvwaddchstr	curses.h:#define mvwaddchstr(win,y,x,str) (wmove(win,y,x)==ERR?ERR:waddchstr(win,str))
mvwaddnstr	curses.h:#define mvwaddnstr(win,y,x,s,n) (wmove(win,y,x)==ERR?ERR:waddnstr(win,s,n))
mvwaddstr	curses.h:#define mvwaddstr(win,y,x,str) (wmove(win,y,x)==ERR?ERR:waddstr(win,str))
mvwdelch	curses.h:#define mvwdelch(win,y,x) (wmove(win,y,x)==ERR?ERR:wdelch(win))
mvwgetch	curses.h:#define mvwgetch(win,y,x) (wmove(win,y,x)==ERR?ERR:wgetch(win))
mvwgetstr	curses.h:#define mvwgetstr(win,y,x,str) (wmove(win,y,x)==ERR?ERR:wgetstr(win,str))
mvwhline	curses.h:#define mvwhline(win,y,x,c,num) (wmove(win,y,x)==ERR?ERR:whline(win,c,num))
mvwin	libcurses/mvwin.c:	int mvwin (win, by, bx) WINDOW *win; int by, bx; { int ret; return ret; }
mvwinch	curses.h:#define mvwinch(win,y,x) (wmove(win,y,x)==ERR?(chtype) ERR:winch(win))
mvwinchnstr	curses.h:#define mvwinchnstr(win,y,x,str,n) (wmove(win,y,x)==ERR?ERR:winchnstr(win,str,n))
mvwinchstr	curses.h:#define mvwinchstr(win,y,x,str) (wmove(win,y,x)==ERR?ERR:winchstr(win,str))
mvwinnstr	curses.h:#define mvwinnstr(win,y,x,str,n) (wmove(win,y,x)==ERR?ERR:winnstr(win,str,n))
mvwinsch	curses.h:#define mvwinsch(win,y,x,c) (wmove(win,y,x)==ERR?ERR:winsch(win,c))
mvwinsnstr	curses.h:#define mvwinsnstr(win,y,x,s,n) (wmove(win,y,x)==ERR?ERR:winsnstr(win,s,n))
mvwinsstr	curses.h:#define mvwinsstr(win,y,x,s) (wmove(win,y,x)==ERR?ERR:winsstr(win,s))
mvwinstr	curses.h:#define mvwinstr(win,y,x,str) (wmove(win,y,x)==ERR?ERR:winstr(win,str))
mvwprintw	libcurses/mvwprintw.c:	/* VARARGS4 */ int mvwprintw (win, y, x, fmt) WINDOW *win; int y, x; char *fmt; { int ret; return ret; }
mvwscanw	libcurses/mvwscanw.c:	/* VARARGS4 */ int mvwscanw (win, y, x, fmt) WINDOW *win; int y, x; char *fmt; { int ret; return ret; }
mvwvline	curses.h:#define mvwvline(win,y,x,c,num) (wmove(win,y,x)==ERR?ERR:wvline(win,c,num))
mylock	libPW/lockit.c:	int mylock (lockfile,pid) char *lockfile; unsigned pid; { int ret; return ret; }
napms	libcurses/naps.c:	int napms (ms) int ms; { int ret; return ret; }
needs_xon_xoff	term.h:#define needs_xon_xoff CURB _needs_xon_xoff
newline	term.h:#define newline CUR _Vr2_Bstrs._s104
newpad	libcurses/newpad.c:	WINDOW * newpad (nlines, ncols) int nlines; { WINDOW * ret; return ret; }
newterm	curses.h:libcurses/newterm.c:	SCREEN * newterm (type, outfd, infd) char *type; FILE *outfd, *infd; { SCREEN * ret; return ret; }
newwin	libcurses/newwin.c:	WINDOW * newwin (nlines, ncols, by, bx) int nlines, ncols, by, bx; { WINDOW * ret; return ret; }
nice	libc NICE(2):	int nice (i) { return (i); }
nl	curses.h:libcurses/nl.c:	int nl () { int ret; return ret; }
nlist	libc NLIST(3C):	int nlist (f, n) char *f; struct nlist *n; { return (0); }
no_esc_ctlc	term.h:#define no_esc_ctlc CUR _b3
no_pad_char	term.h:#define no_pad_char CURB _no_pad_char
nocbreak	libcurses/nocbreak.c:	int nocbreak () { int ret; return ret; }
nocrmode	libcurses/nocrmode.c:curses.h:#define nocrmode nocbreak
nodelay	curses.h:libcurses/nodelay.c:	int nodelay (win,bf) WINDOW *win; int bf; { int ret; return ret; }
noecho	curses.h:libcurses/noecho.c:	int noecho () { int ret; return ret; }
non_dest_scroll_region	term.h:#define non_dest_scroll_region CURB _non_dest_scroll_region
non_rev_rmcup	term.h:#define non_rev_rmcup CURB _non_rev_rmcup
nonl	curses.h:libcurses/nonl.c:	int nonl () { int ret; return ret; }
noqiflush	curses.h:#define noqiflush() _setqiflush(FALSE)
noraw	libcurses/noraw.c:	int noraw () { int ret; return ret; }
notimeout	curses.h:#define notimeout(win,bf) ((win)->_notimeout = ((bf) ? TRUE : FALSE))
nrand48	libc DRAND48(3C):	long nrand48 (x) unsigned short x[3]; { return (0L); }
num_labels	term.h:#define num_labels CURN _num_labels
numeric	macros.h:#define numeric(c) (c >= '0' && c <= '9')
onelock	libPW/lockit.c:	int onelock (pid,tempfile,lockfile) unsigned pid; char *tempfile; char *lockfile; { int ret; return ret; }
open	libc OPEN(2):	/*VARARGS2*/ int open (f, o, m) char *f; { return (o); }
openpl	libplot/open.c:	int openpl () { int ret; return ret; }
openvt	libplot/open.c:	int openvt () { int ret; return ret; }
optarg	libc GETOPT(3C):	extern char *optarg;
opterr	libc GETOPT(3C):	extern int opterr;
optind	libc GETOPT(3C):	extern int optind;
optopt	libc GETOPT(3C):	extern int optopt; /*undocumented */
over_strike	term.h:#define over_strike CUR _b16
overlay	curses.h:libcurses/overlay.c:	int overlay (win1, win2) WINDOW *win1, *win2; { int ret; return ret; }
overwrite	curses.h:libcurses/overwrite.c:	int overwrite (win1, win2) WINDOW *win1, *win2; { int ret; return ret; }
pad_char	term.h:#define pad_char CUR _Vr2_Bstrs._s105
padding_baud_rate	term.h:#define padding_baud_rate CUR _c6
parm_dch	term.h:#define parm_dch CUR _Vr2_Bstrs._s106
parm_delete_line	term.h:#define parm_delete_line CUR _Vr2_Bstrs._s107
parm_down_cursor	term.h:#define parm_down_cursor CUR _Vr2_Bstrs._s108
parm_ich	term.h:#define parm_ich CUR _Vr2_Bstrs._s109
parm_index	term.h:#define parm_index CUR _Vr2_Bstrs._s110
parm_insert_line	term.h:#define parm_insert_line CUR _Vr2_Bstrs._s111
parm_left_cursor	term.h:#define parm_left_cursor CUR _Vr2_Bstrs._s112
parm_right_cursor	term.h:#define parm_right_cursor CUR _Vr2_Bstrs._s113
parm_rindex	term.h:#define parm_rindex CUR _Vr2_Bstrs._s114
parm_up_cursor	term.h:#define parm_up_cursor CUR _Vr2_Bstrs._s115
patoi	libPW/patoi.c:	int patoi (s) char *s; { int ret; return ret; }
patol	libPW/patol.c:	long patol (s) char *s; { long ret; return ret; }
pause	libc PAUSE(2):	int pause () { return (0); }
pclose	libc POPEN(3S):	int pclose (f) FILE *f; { return (0); }
perror	libc PERROR(3C):	void perror (s) char *s; {}
pipe	libc PIPE(2):	int pipe (f) int f[2]; { return (0); }
pkey_key	term.h:#define pkey_key CUR _Vr2_Bstrs._s116
pkey_local	term.h:#define pkey_local CUR _Vr2_Bstrs._s117
pkey_xmit	term.h:#define pkey_xmit CUR _Vr2_Bstrs._s118
plab_norm	term.h:#define plab_norm CURS strs2._plab_norm
plock	libc PLOCK(2):	int plock (o) { return (o); }
pnoutrefresh	libcurses/pnoutrfrsh.c:	int pnoutrefresh (pad, pminrow, pmincol, sminrow, smincol, smaxrow, smaxcol) WINDOW *pad; int pminrow, pmincol, sminrow, smincol, smaxrow, smaxcol; { int ret; return ret; }
point	libplot/point.c:	int point (xi,yi) { int ret; return ret; }
pop	libPW/abspath.c:	char pop (stktop) char **stktop; { char ret; return ret; }
popen	libc POPEN(3S):	FILE * popen (c, t) char *c, *t; { return (stdin); }
pow	libm EXP(3M):	double pow (x, y) double x, y; { return (x); }
prefresh	libcurses/prefresh.c:	int prefresh (pad, pminrow, pmincol, sminrow, smincol, smaxrow, smaxcol) WINDOW *pad; int pminrow, pmincol, sminrow, smincol, smaxrow, smaxcol; { int ret; return ret; }
print_screen	term.h:#define print_screen CUR _Vr2_Bstrs._s119
printable	libl/allprint.c:	int printable (c) int c; { int ret; return ret; }
printf	libc PRINTF(3S):	/*VARARGS1 PRINTFLIKE1*/ int printf (s) char *s; { return (0); }
printw	libcurses/printw.c:	/* VARARGS1 */ int printw (fmt) char *fmt; { int ret; return ret; }
profil	libc PROFIL(2):	void profil (b, s, o, i) char *b; {}
prtr_non	term.h:#define prtr_non CUR _Vr2_Bstrs._s145
prtr_off	term.h:#define prtr_off CUR _Vr2_Bstrs._s120
prtr_on	term.h:#define prtr_on CUR _Vr2_Bstrs._s121
prtr_silent	term.h:#define prtr_silent CURB _prtr_silent
ptrace	libc PTRACE(2):	int ptrace (r, i, a, d) { return (r); }
pulse	term.h:#define pulse CURS strs3._pulse
push	libPW/abspath.c:	int push (chrptr,stktop) char **chrptr; char **stktop; { int ret; return ret; }
putc	libc PUTC(3S):stdio.h:#define putc(x, p) (--(p)->_cnt < 0 ? _flsbuf((unsigned char) (x), (p)) : (int) (*(p)->_ptr++ = (unsigned char) (x)))
putchar	libc PUTC(3S):stdio.h:#define putchar(x) putc((x), stdout)
putenv	libc PUTENV(3C):	int putenv (s) char *s; { return (0); }
putp	libcurses/putp.c:	int putp (str) char *str; { int ret; return ret; }
putpwent	libc PUTPWENT(3C):	int putpwent (s, f) struct passwd *s; FILE *f; { return (0); }
puts	libc PUTS(3S):	int puts (s) char *s; { return (0); }
putsi	libplot/putsi.c:	int putsi (a) { int ret; return ret; }
putw	libc PUTC(3S):	int putw (w, f) FILE *f; { return (w); }
qiflush	curses.h:#define qiflush() _setqiflush(TRUE)
qsort	libc QSORT(3C):	void qsort (b, n, w, c) char *b; unsigned n, w; int (*c)(); {}
quick_dial	term.h:#define quick_dial CURS strs3._quick_dial
rand	libc RAND(3C):	int rand () { return (0); }
raw	libcurses/raw.c:	int raw () { int ret; return ret; }
read	libc READ(2):	int read (f, b, n) char *b; unsigned n; { return (f); }
realloc	libc MALLOC(3C):	char * realloc (s, n) char *s; unsigned n; { return (s); }
redrawwin	curses.h:#define redrawwin(win) wredrawln((win),0,(win)->_maxy)
refresh	curses.h:#define refresh() wrefresh(stdscr)
regcmp	libPW/regcmp.c:	/* VARARGS */ char * regcmp (string1) char *string1; { char *ret; return ret; }
regex	libPW/regex.c:	/* VARARGS2 */ char * regex (re, subject) char *re, *subject; { char *ret; return ret; }
remove	macros.h:#define remove(file) xunlink(file)
remove_clock	term.h:#define remove_clock CURS strs3._remove_clock
rename	libPW/rename.c:	int rename (oldname,newname) char *oldname, *newname; { int ret; return ret; }
repeat	libPW/repeat.c:	char * repeat (result,str,repfac) char *result, *str; unsigned repfac; { char *ret; return ret; }
repeat_char	term.h:#define repeat_char CUR _Vr2_Bstrs._s122
repl	libPW/repl.c:	char * repl (str,old,new) char *str; char old,new; { char *ret; return ret; }
req_for_input	term.h:#define req_for_input CURS strs3._req_for_input
reset_1string	term.h:#define reset_1string CUR _Vr2_Bstrs._s123
reset_2string	term.h:#define reset_2string CUR _Vr2_Bstrs._s124
reset_3string	term.h:#define reset_3string CUR _Vr2_Bstrs._s125
reset_file	term.h:#define reset_file CUR _Vr2_Bstrs._s126
reset_prog_mode	libcurses/reset_prog.c:	int reset_prog_mode () { int ret; return ret; }
reset_shell_mode	libcurses/resetshell.c:	int reset_shell_mode () { int ret; return ret; }
resetterm	libcurses/resetterm.c:curses.h:#define resetterm reset_shell_mode
resetty	libcurses/resetty.c:	int resetty () { int ret; return ret; }
restartterm	libcurses/restarttrm.c:	int restartterm (term, filenum, errret) char *term; int filenum; int *errret; { int ret; return ret; }
restore_cursor	term.h:#define restore_cursor CUR _Vr2_Bstrs._s127
rewind	libc FSEEK(3S):	void rewind (f) FILE *f; {}
rewinddir	dirent.h:#define rewinddir( dirp ) seekdir( dirp, 0L )
row_address	term.h:#define row_address CUR _Vr2_Bstrs._s128
satoi	libPW/satoi.c:	char * satoi (p,ip) char *p; int *ip; { char *ret; return ret; }
save_cursor	term.h:#define save_cursor CUR _Vr2_Bstrs._s129
saveterm	libcurses/saveterm.c:curses.h:#define saveterm def_prog_mode
savetty	libcurses/savetty.c:	int savetty () { int ret; return ret; }
sbrk	libc BRK(2):	char * sbrk (i) { return (""); }
scanf	libc SCANF(3S):	/*VARARGS1 SCANFLIKE1*/ int scanf (s) char *s; { return (0); }
scanw	libcurses/scanw.c:	/* VARARGS1 */ int scanw (fmt) char *fmt; { int ret; return ret; }
scr_init	curses.h:#define scr_init(file) _scr_all(file,0)
scr_restore	curses.h:#define scr_restore(file) _scr_all(file,1)
scr_set	curses.h:#define scr_set(file) _scr_all(file,2)
screen	libcurses/miniinit.c:	SCREEN * m_newterm (type, outfd, infd) char *type; FILE *outfd, *infd; { SCREEN * ret; return ret; }
scrl	curses.h:#define scrl(n) wscrl(stdscr,n)
scroll	curses.h:libcurses/scroll.c:	int scroll (win) WINDOW *win; { int ret; return ret; }
scroll_forward	term.h:#define scroll_forward CUR _Vr2_Bstrs._s130
scroll_reverse	term.h:#define scroll_reverse CUR _Vr2_Bstrs._s131
scrollok	curses.h:libcurses/scrollok.c:	int scrollok (win,bf) WINDOW *win; int bf; { int ret; return ret; }
select	libcurses/select.c:	int select (nfds, prfds, pwfds, pefds, timeout) int nfds; int *prfds, *pwfds, *pefds; struct _timeval *timeout; { int ret; return ret; }
semctl	libc SEMCTL(2):	/*VARARGS3*/ int semctl (i, n, c, a) union semun a; { return (i); }
semget	libc SEMGET(2):	int semget (k, n, s) key_t k; { return (n); }
semop	libc SEMOP(2):	int semop (i, o, n) struct sembuf *o; { return (i); }
semun	libc SEMCTL(2):	union semun { int val; struct semid_ds *buf; ushort *array; };
set_attributes	term.h:#define set_attributes CUR _Vr2_Bstrs._s132
set_clock	term.h:#define set_clock CURS strs3._set_clock
set_curterm	term.h:#define set_curterm setcurterm
set_left_margin	term.h:#define set_left_margin CURS strs3._set_left_margin
set_right_margin	term.h:#define set_right_margin CURS strs3._set_right_margin
set_tab	term.h:#define set_tab CUR _Vr2_Bstrs._s133
set_term	curses.h:libcurses/set_term.c:	SCREEN * set_term (new) SCREEN *new; { SCREEN * ret; return ret; }
set_window	term.h:#define set_window CUR _Vr2_Bstrs._s134
setbuf	libc SETBUF(3S):	void setbuf (f, b) FILE *f; char *b; {}
setgid	libc SETUID(2):	int setgid (g) { return (g); }
setgrent	libc GETGRENT(3C):	void setgrent () {}
setjmp	libc SETJMP(3C):	int setjmp (e) jmp_buf e; { return (0); }
setkey	libc CRYPT(3C):	void setkey (k) char *k; {}
setpgrp	libc SETPGRP(2):	int setpgrp () { return (0); }
setpwent	libc GETPWENT(3C):	void setpwent () {}
setscrreg	curses.h:#define setscrreg(t,b) wsetscrreg(stdscr, t, b)
setsig	libPW/setsig.c:	int setsig () { int ret; return ret; }
setsig1	libPW/setsig.c:	int setsig1 (sig) int sig; { int ret; return ret; }
setterm	libcurses/setterm.c:curses.h:#define setterm(name) setupterm((name),1,(char*)NULL)
setuid	libc SETUID(2):	int setuid (u) { return (u); }
setupterm	libcurses/setupterm.c:	int setupterm (term, filenum, errret) char *term; int filenum; int *errret; { int ret; return ret; }
setvbuf	libc SETBUF(3S):	int setvbuf (f, t, b, s) FILE *f; char *b; { return (t); }
sgetl	libld/sgetl.c:	long sgetl (buffer) register char *buffer; { long ret; return ret; }
shmat	libc SHMOP(2):	char * shmat (i, a, f) char *a; { return (a); }
shmctl	libc SHMCTL(2):	int shmctl (s, c, b) struct shmid_ds *b; { return (s); }
shmdt	libc SHMOP(2):	int shmdt (a) char *a; { return (0); }
shmget	libc SHMGET(2):	int shmget (k, s, f) key_t k; { return (s); }
short	libc DRAND48(3C):	unsigned short * seed48 (s) unsigned short s[3]; { return (s); }
signal	libc SIGNAL(2): void (* signal (s, a))() void (*a)(); { return (a); }
signgam	libm GAMMA(3M):	extern int signgam;
sin	libm TRIG(3M):	double sin (x) double x; { return (x); }
sinh	libm SINH(3M):	double sinh (x) double x; { return (x); }
size	macros.h:#define size(str) (strlen(str) + 1)
sleep	libc SLEEP(3C):	unsigned sleep (n) unsigned n; { return (n); }
slk_init	curses.h:#define slk_init(f) slk_start(((f == 0) ? 3 : 2),NULL)
sname	libPW/sname.c:	char * sname (s) char *s; { char *ret; return ret; }
space	libplot/space.c:	int space (x0,y0,x1,y1) { int ret; return ret; }
sprint	libl/allprint.c:	int sprint (s) char *s; { int ret; return ret; }
sprintf	libc PRINTF(3S):	/*VARARGS2 PRINTFLIKE2*/ int sprintf (p, s) char *p, *s; { return (0); }
sputl	libld/sputl.c:	int sputl (w, buffer) register long w; register char *buffer; { int ret; return ret; }
sqrt	libm EXP(3M):	double sqrt (x) double x; { return (x); }
srand	libc RAND(3C):	void srand (s) unsigned s; {}
srand48	libc DRAND48(3C):	void srand48 (s) long s; {}
sscanf	libc SCANF(3S):	/*VARARGS2 SCANFLIKE2*/ int sscanf (p, s) char *p, *s; { return (0); }
ssignal	libc SSIGNAL(3C):	int (* ssignal (s, a))() int (*a)(); { return (a); }
standend	curses.h:#define standend() wstandend(stdscr)
standout	curses.h:#define standout() wstandout(stdscr)
stat	libc STAT(2):	int stat (s, b) char *s; struct stat *b; { return (0); }
status_line_esc_ok	term.h:#define status_line_esc_ok CUR _b17
stderr	stdio.h:#define stderr (&_iob[2])
stdin	stdio.h:#define stdin (&_iob[0])
stdout	stdio.h:#define stdout (&_iob[1])
stime	libc STIME(2):	int stime (t) long *t; { return (0); }
strcat	libc STRING(3C):	char * strcat (a, b) char *a, *b; { return (a); }
strchr	libc STRING(3C):	char * strchr (a, b) char *a, b; { return (a); }
strcmp	libc STRING(3C):	int strcmp (a, b) char *a, *b; { return (0); }
strcpy	libc STRING(3C):	char * strcpy (a, b) char *a, *b; { return (a); }
strcspn	libc STRING(3C):	int strcspn (a, b) char *a, *b; { return (0); }
strend	libPW/strend.c:	char * strend (p) char *p; { char *ret; return ret; }
strlen	libc STRING(3C):	int strlen (s) char *s; { return (0); }
strncat	libc STRING(3C):	char * strncat (a, b, n) char *a, *b; { return (a); }
strncmp	libc STRING(3C):	int strncmp (a, b, n) char *a, *b; { return (n); }
strncpy	libc STRING(3C):	char * strncpy (a, b, n) char *a, *b; { return (a); }
strpbrk	libc STRING(3C):	char * strpbrk (a, b) char *a, *b; { return (a); }
strrchr	libc STRING(3C):	char * strrchr (a, b) char *a, b; { return (a); }
strspn	libc STRING(3C):	int strspn (a, b) char *a, *b; { return (0); }
strtod	libc STRTOD(3C):	double strtod (s, t) char *s, **t; { return (0.0); }
strtok	libc STRING(3C):	char * strtok (a, b) char *a, *b; { return (a); }
strtol	libc STRTOL(3C):	long strtol (s, t, b) char *s, **t; { return (0L); }
subpad	curses.h:#define subpad(win,nl,nc,by,bx) derwin((win),(nl),(nc),(by),(bx))
substr	libPW/substr.c:	char * substr (as, aresult, origin, len) char *as, *aresult; int origin; unsigned len; { char *ret; return ret; }
subwin	curses.h:libcurses/subwin.c:	WINDOW * subwin (orig, num_lines, num_cols, begy, begx) WINDOW *orig; int num_lines, num_cols, begy, begx; { WINDOW * ret; return ret; }
swab	libc SWAB(3C):	void swab (f, t, n) char *f, *t; {}
switmaus	libc MAUS(2) PDP-11 IPC:	char * switmaus (m, s) char *s; { return (s); }
sync	libc SYNC(2):	void sync () {}
syncok	curses.h:#define syncok(win,bf) ((win)->_parent?(win)->_sync=(bf):ERR)
sys3b	libc SYS3B(2) (3B20 and 3B5 only):	/*VARARGS2*/ void sys3b (c, a, b) {}
sys_errlist	libc PERROR(3C):	extern char * sys_errlist [1];
sys_nerr	libc PERROR(3C):	extern int sys_nerr;
syscall	libc SYSCALL(3S):	/* UNDOCUMENTED (not for general use) */ /*VARARGS3*/ int syscall (n, r, s, a) { return (n); }
system	libc SYSTEM(3S):	int system (s) char *s; { return (0); }
tab	term.h:#define tab CUR _Vr2_Bstrs._s135
tan	libm TRIG(3M):	double tan (x) double x; { return (x); }
tanh	libm SINH(3M):	double tanh (x) double x; { return (x); }
tdelete	libc TSEARCH(3C):	char * tdelete (k, r, c) char *k, **r; int (*c)(); { return (k); }
teleray_glitch	term.h:#define teleray_glitch dest_tabs_magic_smso
tell	libc VPRINTF(3S):	long tell (f) { return (0L); }
tempnam	libc TMPNAM(3S):	char * tempnam (d, s) char *d, *s; { return (d); }
tfind	libc TSEARCH(3C):	char * tfind (k, r, c) char *k, **r; int (*c)(); { return (k); }
tgetent	libcurses/tgetent.c:	int tgetent (bp, name) char *bp, *name; { int ret; return ret; }
tgetflag	libcurses/tgetflag.c:	int tgetflag (id) char *id; { int ret; return ret; }
tgetnum	libcurses/tgetnum.c:	int tgetnum (id) char *id; { int ret; return ret; }
tgetstr	libcurses/tgetstr.c:	char * tgetstr (id, area) char *id, *area; { char * ret; return ret; }
tgoto	libcurses/tgoto.c:	char * tgoto (cap, col, row) char *cap; int col, row; { char * ret; return ret; }
tilde_glitch	term.h:#define tilde_glitch CUR _b19
time	libc TIME:	long time (t) long *t; { return (0L);}
timeout	curses.h:#define timeout(tm) wtimeout(stdscr,tm)
times	libc TIMES(2):	long times (b) struct tms *b; { return (0L); }
timezone	libc CTIME(3C):	extern long timezone;
tmpfile	libc TMPFILE(3S):	FILE * tmpfile () { return (stdin); }
tmpnam	libc TMPNAM(3S):	char * tmpnam (s) char *s; { return (s); }
to_status_line	term.h:#define to_status_line CUR _Vr2_Bstrs._s136
toascii	libc CONV(3C):ctype.h:#define toascii(c) ((c) & 0177)
tolower	libc CONV(3C):	int tolower (i) { return (i); }
tone	term.h:#define tone CURS strs3._tone
touchline	curses.h:#define touchline(win,y,n) wtouchln((win),(y),(n),TRUE)
touchwin	curses.h:libcurses/touchwin.c:	int touchwin (win) WINDOW *win; { int ret; return ret; }
toupper	libc CONV(3C):	int toupper (i) { return (i); }
tparm	libcurses/tparm.c:	/* VARARGS1 */ char * tparm (instring) char *instring; { char * ret; return ret; }
tputs	libcurses/tputs.c:	int tputs (cp, affcnt, outc) char *cp; int affcnt; int (*outc)(); { int ret; return ret; }
traceoff	libcurses/traceonoff.c:	int traceoff () { int ret; return ret; }
traceon	libcurses/traceonoff.c:	int traceon () { int ret; return ret; }
transparent_underline	term.h:#define transparent_underline CUR _b20
trnslat	libPW/trnslat.c:	char * trnslat (str,old,new,result) char *str; char *old, *new, *result; { char *ret; return ret; }
tsearch	libc TSEARCH(3C):	char * tsearch (k, r, c) char *k, **r; int (*c)(); { return (k); }
ttyname	libc TTYNAME(3C):	char * ttyname (f) { return (""); }
ttyslot	libc VPRINTF(3S):	int ttyslot () { return (0); }
twalk	libc TSEARCH(3C):	void twalk (r, f) char *r; void (*f)(); {}
typeahead	libcurses/typeahead.c:	int typeahead (fd) int fd; { int ret; return ret; }
tzname	libc CTIME(3C):	extern char *tzname[2];
tzset	libc CTIME(3C):	void tzset () {}
ulimit	libc ULIMIT(2):	daddr_t ulimit (c, n) daddr_t n; { return (n); }
umask	libc UMASK(2):	int umask (c) { return (c); }
umount	libc UMOUNT(2):	int umount (s) char *s; { return (0); }
uname	libc UNAME(2):	int uname (n) struct utsname *n; { return (0); }
unctrl	unctrl.h:#define unctrl(ch) (_unctrl[(unsigned) ch])
underline_char	term.h:#define underline_char CUR _Vr2_Bstrs._s137
undial	libc DIAL(3C):	void undial (f) {}
ungetc	libc UNGETC(3S):	int ungetc (c, f) FILE *f; { return (c); }
unlink	libc UNLINK(2):	int unlink (s) char *s; { return (0); }
unlockit	libPW/lockit.c:	int unlockit (lockfile,pid) char *lockfile; unsigned pid; { int ret; return ret; }
untouchwin	curses.h:#define untouchwin(win) wtouchln((win),0,((win)->_maxy),FALSE)
up_half_line	term.h:#define up_half_line CUR _Vr2_Bstrs._s138
user0	term.h:#define user0 CURS strs3._user0
user1	term.h:#define user1 CURS strs3._user1
user2	term.h:#define user2 CURS strs3._user2
user3	term.h:#define user3 CURS strs3._user3
user4	term.h:#define user4 CURS strs3._user4
user5	term.h:#define user5 CURS strs3._user5
user6	term.h:#define user6 CURS strs3._user6
user7	term.h:#define user7 CURS strs3._user7
user8	term.h:#define user8 CURS strs3._user8
user9	term.h:#define user9 CURS strs3._user9
userdir	libPW/userdir.c:	char * userdir (uid) int uid; { char *ret; return ret; }
userexit	libPW/userexit.c:	int userexit (code) { int ret; return ret; }
username	libPW/username.c:	char * username (uid) int uid; { char *ret; return ret; }
ustat	libc USTAT(2):	int ustat (d, b) struct ustat *b; { return (d); }
utime	libc UTIME(2):	int utime (f, t) char *f; struct { time_t x, y; } *t; { return (0); }
va_arg	varargs.h:#define va_arg(list, mode) ((mode *)(list += sizeof(mode)))[-1]
va_dcl	varargs.h:#define va_dcl int va_alist;
va_end	varargs.h:#define va_end(list)
va_start	varargs.h:#define va_start(list) list = (char *) &va_alist
verify	libPW/verify.c:	int verify (astr1,str2) char *astr1; char *str2; { int ret; return ret; }
vfprintf	libc VPRINTF(3S):	int vfprintf (f, s, v) FILE *f; char *s; va_list v; { return (0); }
vidattr	libcurses/vidattr.c:	int vidattr (newmode) int newmode; { int ret; return ret; }
vidputs	libcurses/vidputs.c:	int vidputs (newmode, outc) int newmode; int (*outc)(); { int ret; return ret; }
virtual_terminal	term.h:#define virtual_terminal CUR _c7
vldldptr	libld/vldldptr.c:	int vldldptr (ldptr) LDFILE *ldptr; { int ret; return ret; }
vline	curses.h:#define vline(c,num) wvline(stdscr,c,num)
vprintf	libc VPRINTF(3S):	int vprintf (s, v) char *s; va_list v; { return (0); }
vsprintf	libc VPRINTF(3S):	int vsprintf (p, s, v) char *p, *s; va_list v; { return (0); }
waddch	libcurses/addch.c:	int waddch (win, c) WINDOW *win; chtype c; { int ret; return ret; }
waddchstr	curses.h:#define waddchstr(win,str) waddchnstr((win),(str),-1)
waddstr	curses.h:libcurses/addstr.c:	int waddstr (win,str) WINDOW *win; char *str; { int ret; return ret; }
wait	libc WAIT(2):	int wait (s) int *s; { return (0); }
wait_tone	term.h:#define wait_tone CURS strs3._wait_tone
wattroff	curses.h:libcurses/wattroff.c:	int wattroff (win, attrs) WINDOW *win; int attrs; { int ret; return ret; }
wattron	curses.h:libcurses/wattron.c:	int wattron (win, attrs) WINDOW *win; int attrs; { int ret; return ret; }
wattrset	curses.h:libcurses/wattrset.c:	int wattrset (win, attrs) WINDOW *win; int attrs; { int ret; return ret; }
wbkgdset	curses.h:#define wbkgdset(win,c) (((win)->_attrs = (((win)->_attrs & ~((win)->_bkgd & A_ATTRIBUTES)) | (c & A_ATTRIBUTES))), ((win)->_bkgd = (c)))
wclear	curses.h:libcurses/clear.c:	int wclear (win) WINDOW *win; { int ret; return ret; }
wclrtobot	libcurses/clrtobot.c:	int wclrtobot (win) WINDOW *win; { int ret; return ret; }
wclrtoeol	libcurses/clrtoeol.c:	int wclrtoeol (win) WINDOW *win; { int ret; return ret; }
wdelch	libcurses/delch.c:	int wdelch (win) WINDOW *win; { int ret; return ret; }
wdeleteln	curses.h:libcurses/deleteln.c:	int wdeleteln (win) WINDOW *win; { int ret; return ret; }
werase	curses.h:libcurses/erase.c:	int werase (win) WINDOW *win; { int ret; return ret; }
wgetch	libcurses/getch.c:	int wgetch (win) WINDOW *win; { int ret; return ret; }
wgetstr	libcurses/getstr.c:	int wgetstr (win,str) WINDOW *win; char *str; { int ret; return ret; }
width_status_line	term.h:#define width_status_line CUR _c8
winch	curses.h:#define winch(win) ((win)->_y[(win)->_cury][(win)->_curx])
winchstr	curses.h:#define winchstr(win,str) winchnstr((win),str,((win)->_maxx - (win)->_curx))
winsch	libcurses/insch.c:	int winsch (win, c) WINDOW *win; chtype c; { int ret; return ret; }
winsertln	curses.h:libcurses/insertln.c:	int winsertln (win) WINDOW *win; { int ret; return ret; }
winsstr	curses.h:#define winsstr(win,str) winsnstr((win),(str),-1)
winstr	curses.h:#define winstr(win,str) winnstr((win),str,((win)->_maxx - (win)->_curx))
wmove	libcurses/move.c:	int wmove (win, y, x) WINDOW *win; int y, x; { int ret; return ret; }
wnoutrefresh	libcurses/wnoutrfrsh.c:	int wnoutrefresh (win) WINDOW *win; { int ret; return ret; }
wprintw	libcurses/wprintw.c:	/* VARARGS2 */ int wprintw (win, fmt) WINDOW *win; char *fmt; { int ret; return ret; }
wrefresh	libcurses/wrefresh.c:	int wrefresh (win) WINDOW *win; { int ret; return ret; }
write	libc WRITE(2):	int write (f, b, n) char *b; unsigned n; { return (f); }
wscanw	libcurses/wscanw.c:	/* VARARGS2 */ int wscanw (win, fmt) WINDOW *win; char *fmt; { int ret; return ret; }
wstandend	curses.h:libcurses/wstandend.c:	int wstandend (win) WINDOW *win; { int ret; return ret; }
wstandout	curses.h:libcurses/wstandout.c:	int wstandout (win) WINDOW *win; { int ret; return ret; }
wtimeout	curses.h:#define wtimeout(win,tm) ((win)->_delay = (tm))
xalloc	libPW/xalloc.c:	int xalloc (asize) unsigned asize; { int ret; return ret; }
xcreat	libPW/xcreat.c:	int xcreat (name,mode) char *name; int mode; { int ret; return ret; }
xfcreat	macros.h:#define xfcreat(file,mode) fdfopen(xcreat(file,mode),1)
xfopen	macros.h:#define xfopen(file,mode) fdfopen(xopen(file,mode),mode)
xfree	libPW/xalloc.c:	int xfree (aptr) char *aptr; { int ret; return ret; }
xfreeall	libPW/xalloc.c:	int xfreeall () { int ret; return ret; }
xlink	libPW/xlink.c:	int xlink (f1,f2) char *f1, *f2; { int ret; return ret; }
xmsg	libPW/xmsg.c:	int xmsg (file,func) char *file, *func; { int ret; return ret; }
xoff_character	term.h:#define xoff_character CURS strs2._xoff_character
xon_character	term.h:#define xon_character CURS strs2._xon_character
xon_xoff	term.h:#define xon_xoff CUR _b21
xopen	libPW/xopen.c:	int xopen (name,mode) char name[]; int mode; { int ret; return ret; }
xpipe	libPW/xpipe.c:	int xpipe (t) int *t; { int ret; return ret; }
xunlink	libPW/xunlink.c:	int xunlink (f) char *f; { int ret; return ret; }
xwrite	libPW/xwrite.c:	int xwrite (fildes,buffer,nbytes) char *buffer; { int ret; return ret; }
y0	libm BESSEL(3M):	double y0 (x) double x; { return (x); }
y1	libm BESSEL(3M):	double y1 (x) double x; { return (x); }
yn	libm BESSEL(3M):	double yn (n, x) double x; { return (x); }
yyerror	liby/libzer.c:	int yyerror ( s ) char *s; { int ret; return ret; }
yyless	libl/yyless.c:	int yyless (x) { int ret; return ret; }
yyracc	libl/reject.c:	int yyracc (m) { int ret; return ret; }
yyreject	libl/reject.c:	int yyreject () { int ret; return ret; }
yywrap	libl/yywrap.c:	int yywrap () { int ret; return ret; }
zero	libPW/zero.c:	char * zero (p,n) char *p; int n; { char *ret; return ret; }
zeropad	libPW/zeropad.c:	char * zeropad (str) char *str; { char *ret; return ret; }
</FoO ThE bAr/>
