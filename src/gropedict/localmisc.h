/* localmisc */

/* miscellaneous stuff which essentially every program wants! */
/* last modified %G% version %I% */


/* revision history:

	= 1998-02-15, Dave Morano

	This code was started to make life easier on the outside
	(outside of Lucent Technologies).  This file largely contains
	those things (defines) that I have found to be either useful or
	problematic in the past.


*/

/* Copyright © 1998 David Morano.  All rights reserved. */

#ifndef	LOCALMISC_INCLUDE
#define	LOCALMISC_INCLUDE	1


#include	<envstandards.h>	/* MUST be first to configure */

#include	<sys/types.h>
#include	<sys/param.h>
#include	<sys/socket.h>
#include	<limits.h>


#ifndef	va_begin
#define	va_begin	va_start
#endif
#ifndef	va_get
#define	va_get		va_arg
#endif

#ifdef	TRUE
#undef	TRUE
#undef	FALSE
#endif

#define	TRUE		1
#define	FALSE		0

#ifdef	YES
#undef	YES
#undef	NO
#endif

#define	YES		1
#define	NO		0

#ifdef	OK
#undef	OK
#undef	BAD
#endif

#define	OK		0
#define	BAD		-1


#ifndef	MIN
#define	MIN(a,b)	(((a) < (b)) ? (a) : (b))
#endif

#ifndef	MAX
#define	MAX(a,b)	(((a) > (b)) ? (a) : (b))
#endif

#ifndef	UMIN
#define	UMIN(a,b)	(((unsigned long) (a)) < ((unsigned long) (b))) \
				 ? (a) : (b))
#endif

#ifndef	UMAX
#define	UMAX(a,b)	((((unsigned long) (a)) > ((unsigned long) (b))) \
				? (a) : (b))
#endif

#ifndef	ABS
#define	ABS(a)		(((a) < 0) ? (- (a)) : (a))
#endif

#ifndef	LEQUIV
#define	LEQUIV(a,b)	(((a) && (b)) || ((! (a)) && (! (b))))
#endif

#ifndef	LXOR
#define	LXOR(a,b)	(((a) && (! (b))) || ((! (a)) && (b)))
#endif

#ifndef	BCEIL
#define	BCEIL(v,m)	(((v) + ((m) - 1)) & (~ ((m) - 1)))
#endif

#ifndef	BFLOOR
#define	BFLOOR(v,m)	((v) & (~ ((m) - 1)))
#endif

#ifndef	CEILINT
#define	CEILINT(v)	BCEIL((v),sizeof(int))
#endif

#ifndef	CMSG_SPACE
#define	CMSG_SPACE(len)	(CEILINT(sizeof(struct cmsghdr)) + CEILINT(len))
#endif

#ifndef	CMSG_LEN
#define	CMSG_LEN(len)	(CEILINT(sizeof(struct cmsghdr)) + (len))
#endif

#ifndef	PF_LOCAL
#ifdef	PF_UNIX
#define	PF_LOCAL	PF_UNIX
#else
#define	PF_LOCAL	0
#endif
#endif

#ifndef	AF_LOCAL
#ifdef	AF_UNIX
#define	AF_LOCAL	AF_UNIX
#else
#define	AF_LOCAL	0
#endif
#endif

/* basic scalar types */

#ifndef	CHAR
#define	CHAR		char
#endif

#ifndef	BYTE
#define	BYTE		char
#endif

#ifndef	SHORT
#define	SHORT		short
#endif

#ifndef	INT
#define	INT		int
#endif

#ifndef	LONGLONG
#undef	S1
#define	S1	defined(OSNAME_Darwin) && (OSNAME_Darwin > 0)
#undef	S2
#define	S2	defined(OSNAME_IRIX) && (OSNAME_IRIX > 0)
#undef	S3
#define	S3	defined(OSNAME_SunOS) && (OSNAME_SunOS > 0)
#define	F	S1 || S2 || S3
#if	F
#define	LONGLONG	long long
#else
#define	LONGLONG	long
#endif /* (whether implementation has 'long long' or not) */
#undef	S1
#undef	S2
#undef	S3
#undef	F
#endif

#ifndef	LONG
#undef	S1
#define	S1	defined(OSNAME_Darwin) && (OSNAME_Darwin > 0)
#undef	S2
#define	S2	defined(OSNAME_IRIX) && (OSNAME_IRIX > 0)
#undef	S3
#define	S3	defined(OSNAME_SunOS) && (OSNAME_SunOS > 0)
#define	F1	defined(LONGLONG)
#define	F	F1 || S1 || S2 || S3
#if	F
#define	LONG	long long
#else
#define	LONG	long
#endif /* (whether implementation has 'long long' or not) */
#undef	S1
#undef	S2
#undef	S3
#undef	F
#endif

#ifndef	SCHAR
#define	SCHAR		signed char
#endif

#ifndef	UCHAR
#define	UCHAR		unsigned char
#endif

#ifndef	USHORT
#define	USHORT		unsigned short
#endif

#ifndef	UINT
#define	UINT		unsigned int
#endif

#ifndef	ULONG
#define	ULONG		unsigned LONG
#endif

#ifndef	ULONGLONG
#define	ULONGLONG	unsigned LONGLONG
#endif


#if	defined(OSNAME_Darwin) && defined(OSNUM) && (OSNUM <= 7)
#if	(! defined(_POSIX_SOURCE))
#ifndef	TYPEDEF_USHORT
#define	TYPEDEF_USHORT	1
#endif
#ifndef	TYPEDEF_UINT
#define	TYPEDEF_UINT	1
#endif
#endif /* (! defined(_POSIX_SOURCE)) */
#endif /* defined(OSNAME_Darwin) */



#if	(! defined(__EXTENSIONS__)) && (! defined(P_MYID))
#if	defined(_POSIX_C_SOURCE) || defined(_XOPEN_SOURCE)
#if	(! defined(IRIX)) || (! defined(_SYS_BSD_TYPEDEFS_H))

#ifndef	TYPEDEFS_UNSIGNED
#define	TYPEDEFS_UNSIGNED	1

#ifndef	TYPEDEF_USHORT
#define	TYPEDEF_USHORT	1
typedef unsigned short	ushort ;
#endif

#ifndef	TYPEDEF_UINT
#define	TYPEDEF_UINT	1
typedef unsigned int	uint ;
#endif

#ifndef	TYPEDEF_ULONG
#define	TYPEDEF_ULONG	1
typedef unsigned long	ulong ;
#endif

#endif /* TYPEDEFS_UNSIGNED */

#endif
#endif
#endif


/* do it again! */

#if	(! defined(TYPEDEFS_UNSIGNED)) && (! defined(P_MYID))
#if	(! defined(IRIX)) || (! defined(_SYS_BSD_TYPEDEFS_H))

#ifndef	TYPEDEFS_UNSIGNED
#define	TYPEDEFS_UNSIGNED	1

#ifndef	TYPEDEF_USHORT
#define	TYPEDEF_USHORT	1
typedef unsigned short	ushort ;
#endif

#ifndef	TYPEDEF_UINT
#define	TYPEDEF_UINT	1
typedef unsigned int	uint ;
#endif

#ifndef	TYPEDEF_ULONG
#define	TYPEDEF_ULONG	1
typedef unsigned long	ulong ;
#endif

#endif /* TYPEDEFS_UNSIGNED */

#endif
#endif



#ifndef	TYPEDEF_SCHAR
#define	TYPEDEF_SCHAR	1
typedef signed char	schar ;
#endif /* TYPEDEF_SCHAR */


#ifndef	TYPEDEF_UCHAR
#define	TYPEDEF_UCHAR	1
typedef unsigned char	uchar ;
#endif /* TYPEDEF_UCHAR */


#ifndef	TYPEDEF_LONG64
#define	TYPEDEF_LONG64	1
typedef LONG		long64 ;
#endif /* TYPEDEF_LONG64 */


#ifndef	TYPEDEF_ULONG64
#define	TYPEDEF_ULONG64	1
typedef ULONG		ulong64 ;
#endif /* TYPEDEF_ULONG64 */



#if	defined(SYSHAS_OFFSETT) && (SYSHAS_OFFSETT > 0)
#define	TYPEDEF_OFFSETT		1
#else
#ifndef	TYPEDEF_OFFSETT
#define	TYPEDEF_OFFSETT		1
typedef long long		offset_t ;
#endif
#endif


#if	defined(SYSHAS_OFF32T) && (SYSHAS_OFF32T > 0)
#define	TYPEDEF_OFF32T		1
#else
#ifndef	TYPEDEF_OFF32T
#define	TYPEDEF_OFF32T		1
typedef int			off32_t ;
#endif /* TYPEDEF_OFF32T */
#endif


#ifndef	TYPEDEF_USTIMET
#define	TYPEDEF_USTIMET		1
typedef unsigned int		ustime_t ;
#endif

#ifndef	TYPEDEF_UTIMET
#define	TYPEDEF_UTIMET		1
#if	defined(_LP64)
typedef unsigned long		utime_t ;
#else
typedef unsigned long long	utime_t ;
#endif
#endif

#ifndef	TYPEDEF_UNIXTIMET
#define	TYPEDEF_UNIXTIMET	1
#if	defined(_LP64)
typedef long			unixtime_t ;
#else
typedef long long		unixtime_t ;
#endif
#endif



/* some limits! */

#ifndef	LONG64_MIN
#define	LONG64_MIN	(-9223372036854775807L-1LL)
#endif

#ifndef	LONG64_MAX
#define	LONG64_MAX	9223372036854775807LL
#endif

#ifndef	ULONG64_MAX
#define	ULONG64_MAX	18446744073709551615ULL
#endif

/* it would be nice if the implemenation had these */

#ifndef	SHORT_MIN
#ifdef	SHRT_MIN
#define	SHORT_MIN	SHRT_MIN
#else
#define	SHORT_MIN	(-32768)	/* min value of a "short int" */
#endif
#endif

#ifndef	SHORT_MAX
#ifdef	SHRT_MAX
#define	SHORT_MAX	SHRT_MAX
#else
#define	SHORT_MAX	32767		/* max value of a "short int" */
#endif
#endif

#ifndef	USHORT_MAX
#ifdef	USHRT_MAX
#define	USHORT_MAX	USHRT_MAX
#else
#define	USHORT_MAX	65535		/* max value of "unsigned short int" */
#endif
#endif



/* parameters */

#ifndef	NODENAMELEN
#if	defined(SYS_NMLN)
#define	NODENAMELEN	SYS_NMLN	/* must be at least 257 for SVR4! */
#else
#define	NODENAMELEN	512		/* must be at least 257 for SVR4! */
#endif
#endif

#ifndef	MAXPATHLEN
#define	MAXPATHLEN	2048
#endif

#ifndef	MAXNAMELEN
#define	MAXNAMELEN	256
#endif

#ifndef	MSGBUFLEN
#define	MSGBUFLEN	1024
#endif

#ifndef	PWBUFLEN
#define	PWBUFLEN	1024		/* _SC_GETPW_R_SIZE_MAX */
#endif

#ifndef	GRBUFLEN
#define	GRBUFLEN	7296		/* _SC_GETGR_R_SIZE_MAX */
#endif

#ifndef	PJBUFLEN
#define	PJBUFLEN	(4 * 1024)	/* Solaris project */
#endif

/* protocol entry */
#ifndef	PEBUFLEN
#define	PEBUFLEN	100
#endif

/* host entry */
#ifndef	HEBUFLEN
#define	HEBUFLEN	(8 * 1024)
#endif

/* service entry */
#ifndef	SEBUFLEN
#define	SEBUFLEN	100
#endif

/* service name */
#ifndef	SVCNAMELEN
#define	SVCNAMELEN	32
#endif

#ifndef	PASSWDLEN
#define	PASSWDLEN	32
#endif

#ifndef	USERNAMELEN
#ifndef	LOGNAME_MAX
#define	USERNAMELEN	LOGNAME_MAX
#else
#define	USERNAMELEN	32
#endif
#endif

#ifndef	GROUPNAMELEN
#ifndef	LOGNAME_MAX
#define	GROUPNAMELEN	LOGNAME_MAX
#else
#define	GROUPNAMELEN	32
#endif
#endif

#ifndef	LOGNAMELEN
#ifndef	LOGNAME_MAX
#define	LOGNAMELEN	LOGNAME_MAX
#else
#define	LOGNAMELEN	32
#endif
#endif

/* Solaris project name */
#ifndef	PROJNAMELEN
#ifndef	LOGNAME_MAX
#define	PROJNAMELEN	LOGNAME_MAX
#else
#define	PROJNAMELEN	32
#endif
#endif

#ifndef	LINEBUFLEN
#ifdef	LINE_MAX
#define	LINEBUFLEN	MAX(LINE_MAX,2048)
#else
#define	LINEBUFLEN	2048
#endif
#endif

/* timezone (zoneinfo) name */
#ifndef	TZLEN
#define	TZLEN		100
#endif

/* timezone abbreviation */
#ifndef	ZNAMELEN
#define	ZNAMELEN	8
#endif

/* log-ID (for logging) */
#ifndef	LOGIDLEN
#define	LOGIDLEN	15
#endif

/* mail address */
#ifndef	MAILADDRLEN
#define	MAILADDRLEN	(3 * MAXHOSTNAMELEN)
#endif

/* mail message ID */
#ifndef	MSGIDLEN
#define	MSGIDLEN	(3 * MAXHOSTNAMELEN)
#endif

#ifndef	NFILE
#define	NFILE		20
#endif

#ifndef	ENDIAN
#ifdef	_LITTLE_ENDIAN
#define	ENDIAN		0
#endif
#ifdef	_BIG_ENDIAN
#define	ENDIAN		1
#endif
#ifndef	ENDIAN
#if	defined(OSNAME_SunOS) && (OSNAME_SunOS > 0) && defined(__sparc)
#define	ENDIAN		1
#else
#error	"could not determine endianness of this machine"
#endif
#endif
#endif /* ENDIAN */


/* language features */

#ifndef	LANGUAGE_FOREVER
#define	LANGUAGE_FOREVER	1
#define	forever		for (;;)
#endif /* LANGUAGE_FOREVER */

#ifndef	LANGUAGE_NELEMENTS
#define	LANGUAGE_NELEMENTS	1
#ifndef	nelements
#define	nelements(n)	(sizeof(n) / sizeof((n)[0]))
#endif
#endif

#ifndef	nelem
#ifdef	nelements
#define	nelem		nelements
#else
#define	nelem(n)	(sizeof(n) / sizeof((n)[0]))
#endif
#endif

#ifndef	NULL
#define	NULL		0
#endif

#ifndef	VOID
#define	VOID		void
#endif

#ifndef	VOLATILE
#define	VOLATILE	volatile
#endif

#ifndef	CONST
#define	CONST		const
#endif


#ifndef	STRUCT_MAPEX
#define	STRUCT_MAPEX	1

struct mapex {
	int	rs, ex ;
} ;

#endif /* STRUCT_MAPEX */


#ifndef	EXTERN_MAXEX
#define	EXTERN_MAXEX	1

#ifdef	__cplusplus
extern "C" {
#endif

extern int	mapex(const struct mapex *,int) ;

#ifdef	__cplusplus
}
#endif

#endif /* EXTERN_MAXPEX */


/* names */

#ifndef	NULLFNAME
#define	NULLFNAME	"/dev/null"
#endif

#ifndef	INFNAME
#define	INFNAME		"*STDIN*"
#endif

#ifndef	OUTFNAME
#define	OUTFNAME	"*STDOUT*"
#endif

#ifndef	ERRFNAME
#define	ERRFNAME	"*STDERR*"
#endif


#ifndef	TIMEBUFLEN
#define	TIMEBUFLEN	80
#endif


#endif /* LOCALMISC_INCLUDE */



