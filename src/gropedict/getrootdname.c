/* getrootdname */

/* try to find a program root by looking up a domain name */
/* last modified %G% version %I% */


#define	CF_DEBUGS	0		/* compile-time debug print-outs */


/* revision history:

	= 2003-10-01, Dave Morano

	This is a hack from numerous previous hacks (not enumerated here).
	This is a new version of this hack that is entirely different
	(much simpler).


*/

/* Copyright © 2003 David Morano.  All rights reserved. */

/**************************************************************************

	This subroutine will try to find a program root file-path based
	on a specified domain name.

	This is really a hard-compiled database for some SHELL builtin
	programs.  This is generally only used when all else fails
	(no environment, et cetera).

	Synopsis:

	int getrootdname(buf,buflen,prname,domain)
	char		buf[] ;
	int		buflen ;
	const char	prname[] ;
	const char	domain[] ;

	Arguments:

	buf		supplied buffer to receive the program-root
	buflen		length of supplied buffer
	prname		program-root distribution name to lookup
	domain		supplied domain-name to look up

	Returns:

	>=0		length of found program-root directory
	<0		couldn't find and program-root


*****************************************************************************/


#include	<envstandards.h>	/* MUST be first to configure */

#include	<sys/types.h>
#include	<sys/param.h>
#include	<sys/stat.h>
#include	<limits.h>
#include	<signal.h>
#include	<unistd.h>
#include	<fcntl.h>
#include	<stdlib.h>
#include	<string.h>
#include	<time.h>

#include	<vsystem.h>
#include	<ids.h>
#include	<getax.h>
#include	<getxusername.h>

#include	"localmisc.h"



/* local defines */

#undef	COMMENT

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

#ifndef	SWDFNAME
#define	SWDFNAME	".swd"
#endif

#define	HOMEBASEDNAME	"add-on"
#define	PRNAME		"LOCAL"

#define	DMODE		(X_OK | R_OK)

#ifndef	VARHOME
#define	VARHOME		"HOME"
#endif

#ifndef	VARDOMAIN
#define	VARDOMAIN	"DOMAIN"
#endif

#define	SUBINFO		struct subinfo



/* external subroutines */

extern int	sncpy1(char *,int,const char *) ;
extern int	sncpy2(char *,int,const char *,const char *) ;
extern int	sncpy3(char *,int,const char *,const char *,const char *) ;
extern int	sncpylc(char *,int,const char *) ;
extern int	sncpyuc(char *,int,const char *) ;
extern int	mkpath1(char *,const char *) ;
extern int	mkpath2(char *,const char *,const char *) ;
extern int	mkpath3(char *,const char *,const char *,const char *) ;
extern int	mknpath1(char *,int,const char *) ;
extern int	mknpath2(char *,int,const char *,const char *) ;
extern int	mknpath3(char *,int,const char *,const char *,const char *) ;
extern int	matstr(const char **,const char *,int) ;
extern int	sfshrink(const char *,int,const char **) ;
extern int	nleadstr(const char *,const char *,int) ;
extern int	strnlen(const char *,int) ;
extern int	permid(IDS *,struct stat *,int) ;
extern int	haslc(const char *,int) ;
extern int	hasuc(const char *,int) ;

extern char	*strwcpy(char *,const char *,int) ;


/* external variables */


/* local structures */

struct subinfo_flags {
	uint	ids : 1 ;
} ;

struct subinfo {
	IDS		id ;
	const char	*domain ;		/* caller specified argument */
	const char	*prname ;		/* caller specified argument */
	const char	*dname ;
	struct subinfo_flags	init, open ;
	char		dbuf[MAXNAMELEN + 1] ;
} ;

struct domainbase {
	const char	*domain ;
	const char	*basedname ;
} ;

struct prmap {
	const char	*prname ;
	const char	*dname ;
} ;


/* forward references */

static int subinfo_start(SUBINFO *,const char *,const char *) ;
static int subinfo_checkid(SUBINFO *) ;
static int subinfo_dirok(SUBINFO *,const char *,int) ;
static int subinfo_finish(SUBINFO *) ;

static int subinfo_domain(SUBINFO *,char *,int) ;
static int subinfo_user(SUBINFO *,char *,int) ;
static int subinfo_prmap(SUBINFO *,char *,int) ;
static int subinfo_home(SUBINFO *,char *,int) ;

static int	istermrs(int) ;


/* local variables */

static int	(*tries[])(SUBINFO *,char *,int) = {
	subinfo_domain,
	subinfo_user,
	subinfo_prmap,
	subinfo_home,
	NULL
} ;

static const struct prmap	prmaps[] = {
	{ "root", "/" },
	{ "usr", "/usr" },
	{ "xpg4", "/usr/xpg4" },
	{ "xpg6", "/usr/xpg6" },
	{ "dt", "/usr/dt" },
	{ "ccs", "/usr/ccs" },
	{ "openwin", "/usr/openwin" },
	{ "extra", "/usr/extra" },
	{ "preroot", "/usr/preroot" },
	{ NULL, NULL }
} ;

static const struct domainbase domains[] = {
	{ "rightcore.com", "/usr/add-on" },
	{ "rightcore.org", "/usr/add-on" },
	{ "ece.neu.edu", "/home/student/dmorano/add-on" },
	{ "clearresearch.org", "/usr/add-on" },
	{ "christian-update.org", "/usr/add-on" },
	{ NULL, NULL }
} ;

static const int	termrs[] = {
	SR_FAULT,
	SR_INVALID,
	SR_NOMEM,
	SR_NOANODE,
	SR_BADFMT,
	SR_NOSPC,
	SR_NOSR,
	SR_NOBUFS,
	SR_BADF,
	SR_OVERFLOW,
	SR_RANGE,
	0
} ;


/* exported subroutines */


int getrootdname(buf,buflen,prname,domain)
char		buf[] ;
int		buflen ;
const char	prname[] ;
const char	domain[] ;
{
	SUBINFO	si ;

	int	rs ;
	int	i ;


	if (buf == NULL)
	    return SR_FAULT ;

	if (buflen < 0)
	    buflen = MAXPATHLEN ;

	if ((prname == NULL) || (prname[0] == '\0'))
	    prname = PRNAME ;

	buf[0] = '\0' ;
	rs = subinfo_start(&si,prname,domain) ;
	if (rs < 0)
	    goto ret0 ;

	rs = SR_NOTDIR ;
	for (i = 0 ; tries[i] != NULL ; i += 1) {

	    rs = (*tries[i])(&si,buf,buflen) ;

	    if ((rs > 0) || istermrs(rs))
		break ;

	} /* end for */

	if (rs == 0)
	    rs = SR_NOTFOUND ;

/* clean up and get out */

	subinfo_finish(&si) ;

#if	CF_DEBUGS
	debugprintf("getrootdname: ret rs=%d\n",rs) ;
	debugprintf("getrootdname: buf=%s\n",buf) ;
#endif

ret0:
	return rs ;
}
/* end subroutine (getrootdname) */


/* local subroutines */


static int subinfo_start(sip,prname,domain)
SUBINFO		*sip ;
const char	prname[] ;
const char	domain[] ;
{
	int	rs = SR_OK ;


	memset(sip,0,sizeof(SUBINFO)) ;

	sip->prname = prname ;
	sip->domain = domain ;
	sip->dname = prname ;
	if (hasuc(prname,-1)) {
	    rs = sncpylc(sip->dbuf,MAXNAMELEN,prname) ;
	    sip->dname = sip->dbuf ;
	}

	return rs ;
}
/* end subroutine (subinfo_start) */


static int subinfo_finish(sip)
SUBINFO		*sip ;
{


	if (sip->open.ids)
	    ids_free(&sip->id) ;

	sip->open.ids = FALSE ;
	return SR_OK ;
}
/* end subroutine (subinfo_finish) */


static int subinfo_checkid(sip)
SUBINFO		*sip ;
{
	int	rs = SR_OK ;


	if (! sip->init.ids) {

	    sip->init.ids = TRUE ;
	    rs = ids_load(&sip->id) ;

	    if (rs >= 0)
	        sip->open.ids = TRUE ;

	}

	return (rs >= 0) ? sip->open.ids : rs ;
}
/* end subroutine (subinfo_checkid) */


static int subinfo_dirok(sip,dname,mode)
SUBINFO		*sip ;
const char	dname[] ;
int		mode ;
{
	struct stat	sb ;

	int	rs ;


	rs = u_stat(dname,&sb) ;

	if (rs >= 0) {

	    subinfo_checkid(sip) ;

	    rs = SR_NOTDIR ;
	    if (S_ISDIR(sb.st_mode) && sip->open.ids)
	        rs = permid(&sip->id,&sb,mode) ;

	}

	return rs ;
}
/* end subroutine (subinfo_dirok) */


static int subinfo_user(sip,buf,buflen)
SUBINFO		*sip ;
char		buf[] ;
int		buflen ;
{
	struct passwd	pw ;

	struct stat	sb ;

	int	rs ;
	int	bl ;
	int	rlen = 0 ;

	char	pwbuf[PWBUFLEN + 1] ;
	char	tmpfname[MAXPATHLEN + 1] ;


	rs = getpw_name(&pw,pwbuf,PWBUFLEN,sip->dname) ;
	if (rs >= 0)
	    rs = mkpath2(tmpfname,pw.pw_dir,SWDFNAME) ;

	if ((rs >= 0) && ((rs = u_lstat(tmpfname,&sb)) >= 0)) {

	    rs = SR_NOTFOUND ;
	    if (S_ISLNK(sb.st_mode)) {

	        rs = u_readlink(tmpfname,buf,buflen) ;
		bl = rs ;
		rlen = rs ;
	        if (rs >= 0) {

		    buf[bl] = '\0' ;
	            if ((bl == 1) && (buf[0] == '.')) {

	                rs = mknpath1(buf,buflen,pw.pw_dir) ;
		        rlen = rs ;

		    } else if ((bl > 0) && (buf[0] != '/')) {

			char	tmpbuf[MAXPATHLEN + 1] ;
			mkpath1(tmpbuf,buf) ;
	                rs = mknpath2(buf,buflen,pw.pw_dir,tmpbuf) ;
		        rlen = rs ;

		    } else if (bl == 0)
			rs = SR_NOTFOUND ;

		    if (rs >= 0)
	        	rs = subinfo_dirok(sip,buf,DMODE) ;

	        } /* end if (read link) */

	    } /* end if (symbolic link) */

	} /* end if (have SWD directory entry) */

ret0:
	return (rs >= 0) ? rlen : rs ;
}
/* end subroutine (subinfo_user) */


static int subinfo_domain(sip,buf,buflen)
SUBINFO		*sip ;
char		buf[] ;
int		buflen ;
{
	int	rs = SR_NOTDIR ;
	int	dlen, i ;
	int	m ;
	int	rlen = 0 ;

	char	dname[MAXHOSTNAMELEN + 1] ;

	const char	*dnp ;
	const char	*bnp ;


	if (sip->domain == NULL)
	    sip->domain = getenv(VARDOMAIN) ;

	if ((sip->domain == NULL) || (sip->domain[0] == '\0'))
	    return SR_NOTDIR ;

/* perform any necessary cleanup (needed because of NIS+ crap) */

	dnp = sip->domain ;
	dlen = strlen(sip->domain) ;

	while ((dlen > 0) && (sip->domain[dlen - 1] == '.'))
	    dlen -= 1 ;

	if (dlen <= 0)
	    goto ret0 ;

	rs = SR_OK ;
	if (hasuc(dnp,dlen)) {
	    rs = sncpylc(dname,MAXHOSTNAMELEN,dnp) ;
	    dnp = dname ;
	}

	if (rs < 0)
	    goto ret0 ;

/* do the lookup (this is a full string match) */

	rs = SR_NOTFOUND ;
	for (i = 0 ; domains[i].domain != NULL ; i += 1) {

	    m = nleadstr(domains[i].domain,dnp,dlen) ;

	    if ((m > 0) && (domains[i].domain[m] == '\0') && (m == dlen))
	        break ;

	} /* end for */

	bnp = domains[i].basedname ;
	if ((domains[i].domain != NULL) && (bnp != NULL)) {

	    rs = mknpath2(buf,buflen,bnp,sip->dname) ;
	    rlen = rs ;
	    if (rs >= 0)
	        rs = subinfo_dirok(sip,buf,DMODE) ;

	} /* end if (got a domain match) */

ret0:
	return (rs >= 0) ? rlen : rs ;
}
/* end subroutine (subinfo_domain) */


static int subinfo_home(sip,buf,buflen)
SUBINFO		*sip ;
char		buf[] ;
int		buflen ;
{
	struct passwd	pw ;

	int	rs = SR_NOTDIR ;
	int	rs1 ;
	int	rlen = 0 ;

	char	pwbuf[PWBUFLEN + 1] ;
	const char	*cp ;


	if ((cp = getenv(VARHOME)) == NULL) {

	    rs1 = getpwusername(&pw,pwbuf,PWBUFLEN,-1) ;
	    if (rs1 >= 0)
		cp = pw.pw_dir ;

	} /* end if */

	if (cp != NULL) {

	    rs = mknpath3(buf,buflen,cp,HOMEBASEDNAME,sip->dname) ;
	    rlen = rs ;
	    if (rs >= 0)
	        rs = subinfo_dirok(sip,buf,DMODE) ;

	} /* end if (got a HOME directory) */

	return (rs >= 0) ? rlen : rs ;
}
/* end subroutine (subinfo_home) */


static int subinfo_prmap(sip,buf,buflen)
SUBINFO		*sip ;
char		buf[] ;
int		buflen ;
{
	int	rs = SR_OK ;
	int	i ;
	int	m ;
	int	rlen = 0 ;


	rs = SR_NOTFOUND ;
	for (i = 0 ; prmaps[i].prname != NULL ; i += 1) {

	    m = nleadstr(prmaps[i].prname,sip->dname,-1) ;

	    if ((m > 0) &&
	        (prmaps[i].prname[m] == '\0') && (sip->dname[m] == '\0'))
	        break ;

	} /* end for */

	if (prmaps[i].prname != NULL) {
	    rs = sncpy1(buf,buflen,prmaps[i].dname) ;
	    rlen = rs ;
	    if (rs >= 0)
	        rs = subinfo_dirok(sip,buf,DMODE) ;
	}

ret0:
	return (rs >= 0) ? rlen : rs ;
}
/* end subroutine (subinfo_prmap) */


static int istermrs(rs)
int	rs ;
{
	int	i ;
	int	f = FALSE ;


	for (i = 0 ; termrs[i] != 0 ; i += 1) {
	    f = (rs == termrs[i]) ;
	    if (f)
		break ;
	} /* end if */

	return f ;
}
/* end subroutine (istermrs) */



