/* proginfo */

/* program information */


#define	CF_DEBUGS	0		/* non-switchable debug print-outs */
#define	CF_RMEXT	1		/* remove extension */


/* revision history:

	= 1998-03-17, Dave Morano

	I enhanced this somewhat from my previous version.

*/

/* Copyright © 1998 David Morano.  All rights reserved. */

/******************************************************************************

	This group of subroutines help find and set from variables
	for program start-up type functions.


******************************************************************************/


#include	<envstandards.h>	/* MUST be first to configure */

#include	<sys/types.h>
#include	<sys/param.h>
#include	<stdlib.h>
#include	<string.h>

#include	<vsystem.h>
#include	<vecstr.h>

#include	"localmisc.h"
#include	"defs.h"



/* local defines */

#undef	COMMENT

#ifndef	NODENAMELEN
#define	NODENAMELEN	257
#endif

#define	NOPROGNAME	"NP"

#ifndef	VAREXECFNAME
#define	VAREXECFNAME	"_EF"
#endif

#ifndef	VARUNDER
#define	VARUNDER	"_"
#endif



/* external subroutines */

extern int	sncpy1(char *,int,const char *) ;
extern int	mkpath1(char *,const char *) ;
extern int	mkpath2(char *,const char *,const char *) ;
extern int	mkpath2w(char *,const char *,const char *,int) ;
extern int	sfdirname(const char *,int,const char **) ;
extern int	sfbasename(const char *,int,const char **) ;
extern int	strnlen(const char *,int) ;
extern int	matstr(const char **,const char *,int) ;
extern int	getnodename(char *,int) ;
extern int	getpwd(char *,int) ;
extern int	getev(const char **,const char *,int,const char **) ;
extern int	hasprintbad(const char *,int) ;

#if	CF_DEBUGS || CF_DEBUG
extern int	debugprintf(const char *,...) ;
#endif

extern char	*strwcpy(char *,const char *,int) ;
extern char	*strnchr(const char *,int,int) ;
extern char	*strnrchr(const char *,int,int) ;


/* forward references */

int	proginfo_setentry(struct proginfo *,const char **,const char *,int) ;
int	proginfo_setprogname(struct proginfo *,const char *) ;
int	proginfo_getpwd(struct proginfo *,char *,int) ;
int	proginfo_pwd(struct proginfo *) ;

static int proginfo_setdefnames(struct proginfo *) ;
static int proginfo_setdefen(struct proginfo *) ;
static int proginfo_setdefdn(struct proginfo *) ;
static int proginfo_setdefpn(struct proginfo *) ;

#ifdef	COMMENT
static int proginfo_pntrybn(struct proginfo *,const char *) ;
static int proginfo_pntryen(struct proginfo *,const char *) ;
#endif

static int	rmext(const char *,int) ;
static int	hasourbad(const char *,int) ;


/* local variables */

#if	CF_RMEXT
static const char	*exts[] = {
	"x",
	"s5",
	"s5u",
	"us5",
	"s4",
	"aout",
	"elf",
	"ksh",
	"sh",
	"ksh93",
	"csh",
	"osf",
	NULL
} ;
#endif /* CF_RMEXT */


/* exported subroutines */


int proginfo_init(pip,envv,argz,version)
struct proginfo	*pip ;
char		*envv[] ;
const char	argz[] ;
const char	version[] ;
{
	int	rs ;
	int	opts ;


	if (pip == NULL)
	    return SR_FAULT ;

	memset(pip,0,sizeof(struct proginfo)) ;

	pip->envv = (const char **) envv ;

	opts = (VECSTR_OCONSERVE | VECSTR_OREUSE | VECSTR_OSWAP) ;
	rs = vecstr_start(&pip->stores,10,opts) ;
	if (rs < 0)
	    goto bad0 ;

/* save the current PWD at invocation */

	rs = proginfo_pwd(pip) ;

/* set the program dirname and basename */

	if ((rs >= 0) && (argz != NULL))
	    rs = proginfo_setprogname(pip,argz) ;

	if (rs >= 0)
	    rs = proginfo_setdefnames(pip) ;

/* set the program version */

	if ((rs >= 0) && (version != NULL))
	    rs = proginfo_setentry(pip,&pip->version,version,-1) ;

/* are we bad? */

	if (rs < 0)
	    goto bad1 ;

ret0:
	return rs ;

/* bad stuff */
bad1:
	vecstr_finish(&pip->stores) ;

bad0:
	goto ret0 ;
}
/* end subroutine (proginfo_init) */


/* set an entry */
int proginfo_setentry(pip,epp,v,vlen)
struct proginfo	*pip ;
const char	**epp ;
const char	v[] ;
int		vlen ;
{
	int	rs = SR_OK ;
	int	oi, i ;
	int	vnlen = 0 ;

	const char	*cp ;


	if (pip == NULL)
	    return SR_FAULT ;

	if (epp == NULL)
	    return SR_INVALID ;

/* find existing entry for later deletion */

	oi = -1 ;
	if (*epp != NULL)
	    oi = vecstr_findaddr(&pip->stores,*epp) ;

/* add the new entry */

	if (v != NULL) {

	    vnlen = strnlen(v,vlen) ;

#if	CF_DEBUGS
	    debugprintf("proginfo_setentry: vlen=%u v=>%t<\n",
		vnlen,v,vnlen) ;
#endif

	    rs = vecstr_add(&pip->stores,v,vnlen) ;
	    i = rs ;
	    if (rs >= 0) {

	        rs = vecstr_get(&pip->stores,i,&cp) ;
	        if (rs >= 0)
	            *epp = cp ;

	    } /* end if (added new entry) */

	} /* end if (had a new entry) */

/* delete the old entry if we had one */

	if ((rs >= 0) && (oi >= 0))
	    vecstr_del(&pip->stores,oi) ;

	return (rs >= 0) ? vnlen : rs ;
}
/* end subroutine (proginfo_setentry) */


int proginfo_free(pip)
struct proginfo	*pip ;
{
	int	rs ;


	if (pip == NULL)
	    return SR_FAULT ;

#if	CF_DEBUGS
	proginfo_storelists(pip,"freeing") ;
	rs = vecstr_finish(&pip->stores) ;
	debugprintf("proginfo_free: ret\n") ;
#else
	rs = vecstr_finish(&pip->stores) ;
#endif

	return rs ;
}
/* end subroutine (proginfo_free) */


#if	CF_DEBUGS
int proginfo_storelists(pip,s)
struct proginfo	*pip ;
const char	s[] ;
{
	VECSTR	*vsp = &pip->stores ;
	int	i ;
	const char	*cp ;
	if (s != NULL)
	debugprintf("proginfo_storelists: s=>%s<\n",s) ;
	debugprintf("proginfo_storelists: vi=%u\n",vsp->i) ;
	for (i = 0 ; vecstr_get(vsp,i,&cp) >= 0 ; i += 1) {
		if (cp == NULL) continue ;
		debugprintf("proginfo_storelists: s[%u](%p)\n",i,cp) ;
		debugprintf("proginfo_storelists: s[%u]=>%s<\n",i,cp) ;
	}
	debugprintf("proginfo_storelists: done\n") ;
	return vsp->i ;
}
/* end subroutine (proginfo_storelists) */
#endif /* CF_DEBUGS */


int proginfo_version(pip,v)
struct proginfo	*pip ;
const char	v[] ;
{
	int	rs ;


	if (pip == NULL)
	    return SR_FAULT ;

	rs = proginfo_setentry(pip,&pip->version,v,-1) ;

	return rs ;
}
/* end subroutine (proginfo_version) */


int proginfo_banner(pip,v)
struct proginfo	*pip ;
const char	v[] ;
{
	int	rs ;


	if (pip == NULL)
	    return SR_FAULT ;

	rs = proginfo_setentry(pip,&pip->banner,v,-1) ;

	return rs ;
}
/* end subroutine (proginfo_banner) */


int proginfo_searchname(pip,var,value)
struct proginfo	*pip ;
const char	var[] ;
const char	value[] ;
{
	int	rs = SR_OK ;
	int	cl = -1 ;

	const char	*cp = NULL ;


	if (pip == NULL)
	    return SR_FAULT ;

	if ((cp == NULL) && (value != NULL)) {
	    cp = value ;
	}

	if ((cp == NULL) && (var != NULL)) {
	    cp = getenv(var) ;
	    if (hasourbad(cp,-1) || ((cp != NULL) && (cp[0] == '\0')))
		cp = NULL ;
	}

	if ((cp == NULL) && (pip->progname != NULL)) {
	    const char	*tp ;
	    cp = pip->progname ;
	    if ((tp = strrchr(cp,'.')) != NULL)
		cl = (tp - cp) ;
	}

	if ((rs >= 0) && (cp != NULL))
	    rs = proginfo_setentry(pip,&pip->searchname,cp,cl) ;

	return rs ;
}
/* end subroutine (proginfo_searchname) */


/* set program directory and program name (dirname and basename) */
int proginfo_setprogname(pip,ap)
struct proginfo	*pip ;
const char	ap[] ;
{
	int	rs = SR_OK ;
	int	al ;
	int	dl, bl ;

	const char	*dp, *bp ;


	if (ap == NULL)
	    return SR_FAULT ;

	al = strlen(ap) ;

#if	CF_DEBUGS
	debugprintf("proginfo_setprogname: argz=%t\n",ap,al) ;
#endif

	while ((al > 0) && (ap[al-1] == '/'))
	    al -= 1 ;

/* set a program dirname? */

	if ((dl = sfdirname(ap,al,&dp)) > 0) {

	    int		f_parent = FALSE ;
	    int		f_pwd = FALSE ;
	    int		f = FALSE ;


#if	CF_DEBUGS
	debugprintf("proginfo_setprogname: dirname=%t\n",dp,dl) ;
#endif

	    if (dp[0] == '.') {

	        f_pwd = (strcmp(dp,".") == 0) ;

	        if (! f_pwd)
	            f_parent = (strcmp(dp,"..") == 0) ;

	        f = f_pwd || f_parent ;
	    }

	    if (f) {

	        if (pip->pwd == NULL)
	            rs = proginfo_pwd(pip) ;

	        if (rs >= 0) {

	            if (f_pwd) {

	                dp = pip->pwd ;
	                dl = pip->pwdlen ;

	            } else {

	                dl = sfdirname(pip->pwd,pip->pwdlen,&dp) ;

	            }

	            rs = proginfo_setentry(pip,&pip->progdname,dp,dl) ;

	        }

	    } /* end if (PWD or parent) */

	} /* end if (have a dirname) */

/* set a program basename? */

	if (rs >= 0) {

	    bl = sfbasename(ap,al,&bp) ;

	    if ((bp != NULL) && (bl > 0)) {
		if ((bl = rmext(bp,bl)) == 0) {
		    bp = NOPROGNAME ;
		    bl = -1 ;
		}
	    }

	    if ((bp != NULL) && (bl > 0)) {
		if (hasourbad(bp,bl)) {
		    bp = NULL ;
		    bl = 0 ;
		}
	    }

	    if ((bp != NULL) && (bl > 0) && (bp[0] == '-')) {
		pip->f.progdash = TRUE ;
		bp += 1 ;
		bl -= 1 ;
	    }

#if	CF_DEBUGS
	debugprintf("proginfo_setprogname: progname=%t\n",bp,bl) ;
#endif

	    if ((bp != NULL) && (bl != 0))
	        rs = proginfo_setentry(pip,&pip->progname,bp,bl) ;

	} /* end if (basename) */

	return rs ;
}
/* end subroutine (proginfo_setprogname) */


/* try to divine a program-root from the program directory name */
int proginfo_rootprogdname(pip)
struct proginfo	*pip ;
{
	int	rs = SR_NOENT ;
	int	bl, rl ;
	int	f ;

	const char	*bp, *rp ;
	const char	*cp ;


	if (pip->pr != NULL)
	    return strlen(pip->pr) ;

	if (pip->progdname == NULL)
	    return SR_NOENT ;

	bl = sfbasename(pip->progdname,-1,&bp) ;

	f = ((bl == 3) && (strncmp(bp,"bin",bl) == 0)) ;

	if (! f)
	    f = ((bl == 4) && (strncmp(bp,"sbin",bl) == 0)) ;

	if (f) {

	    rs = sfdirname(pip->progdname,-1,&rp) ;
	    rl = rs ;
	    if ((rl == 0) || ((rl > 0) && (*rp != '/'))) {

	        int	pl, ml ;

	        char	buf[MAXPATHLEN + 1] ;


	        if ((rs = proginfo_getpwd(pip,buf,MAXPATHLEN)) > 0) {

	            pl = rs ;
	            if ((pl < MAXPATHLEN) && (rl > 0))
	                buf[pl++] = '/' ;

	            ml = MIN(rl,(MAXPATHLEN - pl)) ;
	            cp = strwcpy((buf + pl),rp,ml) ;

	            rs = proginfo_setentry(pip,&pip->pr,buf,(cp - buf)) ;

	        } /* end if */

	    } else
	        rs = proginfo_setentry(pip,&pip->pr,rp,rl) ;

	} /* end if (got one) */

	return rs ;
}
/* end subroutine (proginfo_rootprogdname) */


/* set program root */
int proginfo_setroot(pip,pr,prlen)
struct proginfo	*pip ;
const char	pr[] ;
int		prlen ;
{
	int	rs = SR_OK ;

	char	tmpdname[MAXPATHLEN + 1] ;


	if (pr == NULL)
	    return SR_FAULT ;

	if (prlen == 0)
	    return SR_INVALID ;

	if (pr[0] != '/') {
	    rs = proginfo_pwd(pip) ;
	    if (rs >= 0) {
	        rs = mkpath2w(tmpdname,pip->pwd,pr,prlen) ;
		prlen = rs ;
	        pr = tmpdname ;
	    }
	}

	if (rs >= 0)
	    rs = proginfo_setentry(pip,&pip->pr,pr,prlen) ;

	return rs ;
}
/* end subroutine (proginfo_setroot) */


/* set the program execution filename */
int proginfo_setexecname(pip,enp)
struct proginfo	*pip ;
const char	*enp ;
{
	int	rs = SR_OK ;
	int	enl ;


	if (enp == NULL)
	    return SR_FAULT ;

	if (pip->progename != NULL)
	    goto ret0 ;

	enl = strlen(enp) ;

	while ((enl > 0) && (enp[enl-1] == '/'))
	    enl -=1 ;

/* set the program execution name (only do this once) */

	if (enl > 0)
	    rs = proginfo_setentry(pip,&pip->progename,enp,enl) ;

ret0:
	return rs ;
}
/* end subroutine (proginfo_setexecname) */


/* ensure (set) that the current PWD is set */
int proginfo_pwd(pip)
struct proginfo	*pip ;
{
	int	rs = SR_OK ;
	int	pwdlen = 0 ;


	if (pip->pwd == NULL) {

	    char	pwdname[MAXPATHLEN + 1] ;


	    rs = getpwd(pwdname,MAXPATHLEN) ;
	    pwdlen = rs ;
	    if (rs >= 0) {
	        pip->pwdlen = pwdlen ;
	        rs = proginfo_setentry(pip,&pip->pwd,pwdname,pwdlen) ;
	    }
	}

	return (rs >= 0) ? pip->pwdlen : rs ;
}
/* end subroutine (proginfo_pwd) */


/* ensure (set) nodename */
int proginfo_nodename(pip)
struct proginfo	*pip ;
{
	int	rs = SR_OK ;
	int	nnlen = 0 ;


	if (pip->nodename == NULL) {

	    char	nodename[NODENAMELEN + 1] ;


	    rs = getnodename(nodename,NODENAMELEN) ;
	    nnlen = rs ;
	    if (rs >= 0)
	        rs = proginfo_setentry(pip,&pip->nodename,
			nodename,nnlen) ;

	} else
	    nnlen = strlen(pip->nodename) ;

	return (rs >= 0) ? nnlen : rs ;
}
/* end subroutine (proginfo_nodename) */


int proginfo_getename(pip,buf,buflen)
struct proginfo	*pip ;
char		buf[] ;
int		buflen ;
{
	int	rs = SR_OK ;


	if (pip == NULL)
	    return SR_FAULT ;

	if (buf == NULL)
	    return SR_FAULT ;

	buf[0] = '\0' ;
	if (pip->progename == NULL)
	    rs = proginfo_setdefen(pip) ;

	if (rs >= 0) {
	    rs = SR_NOENT ;
	    if (pip->progename != NULL)
	        rs = sncpy1(buf,buflen,pip->progename) ;
	}

	return rs ;
}
/* end subroutine (proginfo_getename) */


/* get the PWD when it was first set */
int proginfo_getpwd(pip,buf,buflen)
struct proginfo	*pip ;
char		buf[] ;
int		buflen ;
{
	int	rs = SR_OK ;


	if (pip == NULL)
	    return SR_FAULT ;

	if (buf == NULL)
	    return SR_FAULT ;

	buf[0] = '\0' ;
	if (pip->pwd == NULL)
	    rs = proginfo_pwd(pip) ;

	if (rs >= 0) {
	    rs = SR_OVERFLOW ;
	    if (buflen >= pip->pwdlen)
	        rs = sncpy1(buf,buflen,pip->pwd) ;
	}

	return rs ;
}
/* end subroutine (proginfo_getpwd) */


int proginfo_getenv(pip,np,nl,rpp)
struct proginfo	*pip ;
const char	*np ;
int		nl ;
const char	**rpp ;
{
	int	rs = SR_NOSYS ;


	if (pip->envv != NULL)
	    rs = getev(pip->envv,np,nl,rpp) ;

	return rs ;
}
/* end subroutine (proginfo_getenv) */


/* local subroutines */


static int proginfo_setdefnames(pip)
struct proginfo	*pip ;
{
	int	rs = SR_OK ;


	if ((pip->progdname == NULL) || (pip->progname == NULL)) {

	    rs = proginfo_setdefen(pip) ;

	    if ((rs >= 0) && (pip->progename != NULL)) {

		rs = proginfo_setdefdn(pip) ;

	        if (rs >= 0)
		    rs = proginfo_setdefpn(pip) ;

	    }

	} /* end if */

	return rs ;
}
/* end subroutine (proginfo_setdefnames) */


static int proginfo_setdefen(pip)
struct proginfo	*pip ;
{
	int	rs = SR_OK ;

	const char	*execfname = NULL ;


	if (pip->progename != NULL)
	    goto ret0 ;

#if	defined(OSNAME_SunOS) && (OSNAME_SunOS > 0)
	if ((rs >= 0) && (execfname == NULL))
	    execfname = getexecname() ;
#endif /* SOLARIS */

	if ((rs >= 0) && (execfname == NULL))
	    execfname = getenv(VAREXECFNAME) ;

	if ((rs >= 0) && (execfname == NULL))
	    execfname = getenv(VARUNDER) ;

	if ((rs >= 0) && (execfname != NULL))
	     rs = proginfo_setexecname(pip,execfname) ;

ret0:
	return rs ;
}
/* end subroutine (proginfo_setdefen) */


static int proginfo_setdefdn(pip)
struct proginfo	*pip ;
{
	int	rs = SR_OK ;
	int	cl ;

	const char	*cp ;


	if (pip->progdname != NULL)
	    goto ret0 ;

	if ((rs >= 0) && (pip->progename != NULL)) {

	    cl = sfdirname(pip->progename,-1,&cp) ;

	    if (cl > 0)
		rs = proginfo_setentry(pip,&pip->progdname,cp,cl) ;

	} /* end if */

ret0:
	return rs ;
}
/* end subroutine (proginfo_setdefdn) */


static int proginfo_setdefpn(pip)
struct proginfo	*pip ;
{
	int	rs = SR_OK ;
	int	cl ;

	const char	*cp ;


	if (pip->progname != NULL)
	    goto ret0 ;

	if ((rs >= 0) && (pip->progename != NULL)) {

	    cl = sfbasename(pip->progename,-1,&cp) ;

	    if (cl > 0) {
		cl = rmext(cp,cl) ;
	        if (cl == 0) {
		    cp = NOPROGNAME ;
		    cl = -1 ;
		}
	    }

	    if ((cp != NULL) && (cl != 0))
		rs = proginfo_setentry(pip,&pip->progdname,cp,cl) ;

	} /* end if */

ret0:
	return rs ;
}
/* end subroutine (proginfo_setdefpn) */


static int rmext(sp,sl)
const char	sp[] ;
int		sl ;
{
	const char	*tp ;
	const char	*ep ;


	if (sl < 0)
	    sl = strlen(sp) ;

	if ((tp = strnrchr(sp,sl,'.')) != NULL) {

	    ep = (tp + 1) ;
#if	CF_RMEXT
	    if (matstr(exts,ep,-1) >= 0)
	        sl = (tp - sp) ;
#else
	    sl = (tp - sp) ;
#endif /* CF_RMEXT */

	} /* end if */

	return sl ;
}
/* end subroutine (rmext) */


static int hasourbad(sp,sl)
const char	*sp ;
int		sl ;
{
	uint	sch ;

	int	f = TRUE ;


	if (sp == NULL)
	    goto ret0 ;

	f = hasprintbad(sp,sl) ;

	if (! f) {
	    int	i ;
	    if (sl < 0)
	        sl = strlen(sp) ;
	    for (i = 0 ; i < sl ; i += 1) {
	        sch = (sp[i] & 0xff) ;
	        f = (sch >= 128) ;
		if (f)
		    break ;
	    } /* end for */
	} /* end if */

ret0:
	return f ;
}
/* end subroutine (hadourbad) */



