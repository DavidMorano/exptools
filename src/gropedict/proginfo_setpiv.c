/* proginfo_setpiv */

/* utility for KSH built-in commands */
/* last modified %G% version %I% */


#define	CF_DEBUG	0		/* switchable at invocation */
#define	CF_GETEXECNAME	1		/* user 'getexecname(3c)' */


/* revision history:

	= 1998-03-01, Dave Morano

	This subroutine was originally written.


*/

/* Copyright © 1998 David Morano.  All rights reserved. */

/**************************************************************************

	This subroutine is used for acquiring (setting) the program-root
	for KSH built-in commands.

	Synopsis:

	int proginfo_setpiv(pip,pr,vars)
	struct proginfo	*pip ;
	const char	pr[] ;
	struct pivars	*vars ;

	Returns:

	>=0	length of PR
	<0	error


*****************************************************************************/


#include	<envstandards.h>	/* MUST be first to configure */

#include	<sys/types.h>
#include	<sys/param.h>
#include	<limits.h>
#include	<signal.h>
#include	<unistd.h>
#include	<fcntl.h>
#include	<stdlib.h>
#include	<string.h>

#include	<vsystem.h>

#include	"localmisc.h"
#include	"defs.h"



/* local defines */

#undef	COMMENT

#ifndef	BUFLEN
#define	BUFLEN		2048
#endif

#ifndef	DEBUGLEVEL
#define	DEBUGLEVEL(n)	(pip->debuglevel >= (n))
#endif



/* external subroutines */

extern int	sncpy2(char *,int,const char *,const char *) ;
extern int	sncpy3(char *,int,const char *,const char *,const char *) ;
extern int	mkpath2(char *,const char *,const char *) ;
extern int	mkpath3(char *,const char *,const char *,const char *) ;
extern int	sfshrink(const char *,int,char **) ;
extern int	cfdeci(const char *,int,int *) ;
extern int	cfdecui(const char *,int,uint *) ;
extern int	getnodedomain(char *,char *) ;

extern int	getrootdname(char *,int,const char *,const char *) ;

extern char	*strwcpy(char *,const char *,int) ;


/* external variables */


/* local structures */


/* forward references */


/* local variables */


/* exported subroutines */


int proginfo_setpiv(pip,pr,vars)
struct proginfo	*pip ;
const char	pr[] ;
struct pivars	*vars ;
{
	int	rs = SR_OK ;
	int	rs1 ;
	int	f = TRUE ;

	uid_t	uid = getuid() ;


	if (pr == NULL) {

	    pr = getenv(vars->vpr1) ;

	    if (pr == NULL)
	        pr = getenv(vars->vpr2) ;

	    if (pr == NULL)
	        pr = getenv(vars->vpr3) ;

	    if ((pr == NULL) && (uid >= 100)) {

		char	nodename[MAXNAMELEN + 1] ;
		char	domainname[MAXHOSTNAMELEN + 1] ;
		char	rootdname[MAXPATHLEN + 1] ;


		if ((rs1 = getnodedomain(nodename,domainname)) >= 0) {

		    proginfo_setentry(pip,&pip->nodename,nodename,-1) ;

		    proginfo_setentry(pip,&pip->domainname,domainname,-1) ;

	            rs1 = getrootdname(rootdname,MAXPATHLEN,
			vars->vprname, domainname) ;

#if	CF_DEBUG
	if (DEBUGLEVEL(3))
	debugprintf("proginfo_setpiv: getrootdname() rs=%d rootdname=%s\n",
			rs1,rootdname) ;
#endif

		    if (rs1 > 0)
	  	        proginfo_setroot(pip,rootdname,rs1) ;

		} /* end if (getnodedomain) */

	    } /* end if (guess program root from domain name) */

/* try to see if a path was given at invocation */

	    if ((pr == NULL) && (pip->pr == NULL) && 
		(pip->progdname != NULL)) {

	        rs = proginfo_rootprogdname(pip) ;

	    } /* end if (set program root from rootprogdname) */

/* do the special thing */

#if	CF_GETEXECNAME && defined(OSNAME_SunOS) && (OSNAME_SunOS > 0)
	    if ((pr == NULL) && (pip->pr == NULL)) {

	        const char	*pp ;


	        pp = getexecname() ;

#if	CF_DEBUG
	if (DEBUGLEVEL(3))
	debugprintf("proginfo_setpiv: getexecname() pp=%s\n",pp) ;
#endif

	        if (pp != NULL)
	            rs = proginfo_setexecname(pip,pp) ;

	    }
#endif /* SOLARIS */

	} /* end if (getting a program root) */

#if	CF_DEBUG
	if (DEBUGLEVEL(3))
	debugprintf("proginfo_setpiv: mid pr=%s\n",pr) ;
#endif

	if ((rs >= 0) && (pip->pr == NULL)) {

	    if (pr == NULL) {
	        pr = vars->pr ;
		f = FALSE ;
	    }

	    rs = proginfo_setroot(pip,pr,-1) ;

	} /* end if */

#if	CF_DEBUG
	if (DEBUGLEVEL(3))
	debugprintf("proginfo_setpiv: ret rs=%d f=%u pr=%s\n",
		rs,f,pip->pr) ;
#endif

	return (rs >= 0) ? f : rs ;
}
/* end subroutine (proginfo_setpiv) */



