/* defs */


#ifndef	DEFS_INCLUDE
#define	DEFS_INCLUDE	1


#include	<envstandards.h>

#include	<sys/types.h>

#include	<vecstr.h>
#include	<logfile.h>
#include	<paramopt.h>
#include	<bfile.h>

#include	"localmisc.h"



#ifndef	nelem
#ifdef	nelements
#define	nelem		nelements
#else
#define	nelem(n)	(sizeof(n) / sizeof((n)[0]))
#endif
#endif

#ifndef	FD_STDIN
#define	FD_STDIN	0
#define	FD_STDOUT	1
#define	FD_STDERR	2
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
#define	PJBUFLEN	(10 * 1024)
#endif

#ifndef	PEBUFLEN
#define	PEBUFLEN	100
#endif

#ifndef	HEBUFLEN
#define	HEBUFLEN	(8 * 1024)
#endif

#ifndef	SEBUFLEN
#define	SEBUFLEN	100
#endif

#ifndef	SVCNAMELEN
#define	SVCNAMELEN	32
#endif

#ifndef	PASSWDLEN
#define	PASSWDLEN	32
#endif

#ifndef	LOGNAMELEN
#ifndef	LOGNAME_MAX
#define	LOGNAMELEN	LOGNAME_MAX
#else
#define	LOGNAMELEN	32
#endif
#endif

#ifndef	USERNAMELEN
#ifndef	LOGNAME_MAX
#define	USERNAMELEN	LOGNAME_MAX
#else
#define	USERNAMELEN	32
#endif
#endif

#ifndef	LINEBUFLEN
#ifdef	LINE_MAX
#define	LINEBUFLEN	MAX(LINE_MAX,2048)
#else
#define	LINEBUFLEN	2048
#endif
#endif

#ifndef	USERBUFLEN
#ifdef	LINE_MAX
#define	USERBUFLEN	MAX(LINE_MAX,2048)
#else
#define	USERBUFLEN	2048
#endif
#endif

#ifndef	LOGIDLEN
#define	LOGIDLEN	15
#endif

#ifndef	MAILADDRLEN
#define	MAILADDRLEN	(3 * MAXHOSTNAMELEN)
#endif

#ifndef	MSGIDLEN
#define	MSGIDLEN	(3 * MAXHOSTNAMELEN)
#endif

#ifndef	NFILE
#define	NFILE		20
#endif

#ifndef	TIMEBUFLEN
#define	TIMEBUFLEN	80
#endif

#ifndef	DEBUGLEVEL
#define	DEBUGLEVEL(n)	(pip->debuglevel >= (n))
#endif


#ifndef	BUFLEN
#define	BUFLEN		MAXPATHLEN
#endif

#define	MEGABYTE	(1024 * 1024)
#define	UNIXBLOCK	512

#define	PO_SUFFIX	"suffix"
#define	PO_OPTION	"option"



struct proginfo_flags {
	uint		progdash : 1 ;
	uint		akopts : 1 ;
	uint		aparams : 1 ;
	uint		quiet : 1 ;
	uint		log : 1 ;
	uint		stderror : 1 ;
	uint		nochange : 1 ;
	uint		print : 1 ;
	uint		suffix : 1 ;
	uint		follow : 1 ;		/* follow symbolic links */
} ;

struct proginfo {
	vecstr		stores ;
	const char	**envv ;
	char		*pwd ;
	char		*progename ;
	char		*progdname ;
	char		*progname ;
	char		*pr ;
	char		*searchname ;
	char		*version ;
	char		*banner ;
	char		*nodename ;
	char		*domainname ;
	char		*username ;
	char		*groupname ;
	char		*tmpdname ;
	char		*helpfname ;
	char		*logid ;
	char		*dictionary ;
	char		*prefix ;
	void		*efp ;
	void		*ofp ;
	struct proginfo_flags	have, f, changed, final ;
	struct proginfo_flags	open ;
	LOGFILE		lh ;
	pid_t		pid ;
	time_t		daytime ;
	uint		bytes ;
	uint		megabytes ;
	int		pwdlen ;
	int		progmode ;
	int		debuglevel ;
	int		verboselevel ;
	int		namelen ;
	int		c_files, c_processed ;
	char		dictdname[MAXPATHLEN + 1] ;
} ;

struct checkparams {
	struct proginfo	*pip ;
	PARAMOPT	*pp ;
} ;

struct grope_outfile {
	bfile		outfile ;
	int		letter ;
	int		usage ;
} ;

struct pivars {
	const char	*vpr1 ;
	const char	*vpr2 ;
	const char	*vpr3 ;
	const char	*pr ;
	const char	*vprname ;
} ;


#ifdef	__cplusplus
}
#endif

extern int proginfo_init(struct proginfo *,char **,const char *,const char *) ;
extern int proginfo_setroot(struct proginfo *,const char *,int) ;
extern int proginfo_rootprogdname(struct proginfo *) ;
extern int proginfo_rootexecname(struct proginfo *,const char *) ;
extern int proginfo_rootname(struct proginfo *) ;
extern int proginfo_setentry(struct proginfo *,char **,const char *,int) ;
extern int proginfo_version(struct proginfo *,const char *) ;
extern int proginfo_banner(struct proginfo *,const char *) ;
extern int proginfo_searchname(struct proginfo *,const char *,const char *) ;
extern int proginfo_setprogname(struct proginfo *,const char *) ;
extern int proginfo_setexecname(struct proginfo *,const char *) ;
extern int proginfo_pwd(struct proginfo *) ;
extern int proginfo_getpwd(struct proginfo *,char *,int) ;
extern int proginfo_getename(struct proginfo *,char *,int) ;
extern int proginfo_nodename(struct proginfo *) ;
extern int proginfo_free(struct proginfo *) ;

#ifdef	__cplusplus
}
#endif


#endif /* DEFS_INCLUDE */



