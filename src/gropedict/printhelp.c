/* printhelp */

/* print out a help file if we have one */


#define	CF_DEBUGS	0		/* non-switchable debug print-outs */


/* revision history:

	= 1997-11-01, Dave Morano

	The subroutine was written to get some common code for the
	printing of help files.


*/

/* Copyright © 1997 David Morano.  All rights reserved. */

/******************************************************************************

	This subroutine will search for a program helpfile and print it
	out (by default to STDOUT).  A root filename is supplied (usually
	'help') but along with a program root.  The "standard" places
	within the program root directory tree are scanned for the help
	file.

	Synopsis:

	int printhelp(fp,pr,searchname,helpfname)
	void		*fp ;
	const char	pr[] ;
	const char	searchname[] ;
	const char	helpfname[] ;

	Arguments:

	fp		open file pointer (BIO)
	pr		program root directory path
	searchname	program search name
	helpfname	program help filename

	Returns:

	>=0		OK
	<0		error


******************************************************************************/


#undef	CF_SFIO
#if	defined(SFIO) || (defined(KSHBUILTIN) && (KSHBUILTIN > 0))
#define	CF_SFIO	1
#else
#define	CF_SFIO	0
#endif

#if	CF_SFIO
#include	<shell.h>
#endif

#include	<envstandards.h>	/* MUST be first to configure */

#include	<sys/types.h>
#include	<sys/param.h>
#include	<sys/stat.h>
#include	<signal.h>
#include	<unistd.h>
#include	<stdlib.h>
#include	<string.h>
#include	<ctype.h>
#include	<time.h>

#include	<vsystem.h>
#include	<vecstr.h>
#include	<bfile.h>

#include	"localmisc.h"



/* local defines */

#undef	COMMENT

#ifndef	HELPSCHEDFNAME
#define	HELPSCHEDFNAME	"etc/printhelp.filesched"
#endif

#ifndef	HELPFNAME
#define	HELPFNAME	"help"
#endif

#ifndef	LIBDNAME
#define	LIBDNAME	"lib"
#endif

#ifndef	DEBUGFNAME
#define	DEBUGFNAME	"printhelp.deb"
#endif



/* external subroutines */

extern int	mkpath2(char *,const char *,const char *) ;
extern int	perm(const char *,uid_t,gid_t,gid_t *,int) ;
extern int	permsched(const char **,vecstr *,const char *,int,char *,int) ;
extern int	vecstr_envadd(vecstr *,const char *,const char *,int) ;
extern int	vecstr_envset(vecstr *,const char *,const char *,int) ;
extern int	vecstr_loadfile(VECSTR *,int,const char *) ;


/* local variables */

static const char	*schedule[] = {
	"%r/%l/%n/%n.%f",
	"%r/%l/%n/%f",
	"%r/share/help/%n.%f",
	"%r/share/help/%n",
	"/usr/extra/share/help/%n.%f",
	"/usr/extra/share/help/%n",
	"%r/%l/help/%n.%f",
	"%r/%l/help/%n",
	"%r/%l/%n.%f",
	"%r/%n.%f",
	"%n.%f",
	NULL
} ;


/* exported subroutines */


int printhelp(fp,pr,searchname,helpfname)
void		*fp ;
const char	pr[] ;
const char	searchname[] ;
const char	helpfname[] ;
{
	vecstr	svars ;

	bfile	outfile, helpfile ;

	int	rs = SR_OK ;
	int	rs1 ;
	int	f_open = TRUE ;

	const char	**spp ;

	char	tmpfname[MAXPATHLEN + 1] ;
	char	*fname ;


#if	CF_DEBUGS
#if	CF_SFIO
	debugprintf("printhelp: SFIO=on\n") ;
#else
	debugprintf("printhelp: SFIO=off\n") ;
#endif
#endif

	if ((helpfname == NULL) || (helpfname[0] == '\0'))
	    helpfname = HELPFNAME ;

#if	CF_SFIO
	if (fp == NULL) {

#if	CF_DEBUGS
	debugprintf("printhelp: no output file handle (SFIO mode)\n") ;
#endif

	    rs = SR_INVALID ;
		goto ret0 ;
	}
#endif /* CF_SFIO */

#if	CF_DEBUGS
	debugprintf("printhelp: pr=%s\n",pr) ;
	debugprintf("printhelp: searchname=%s\n",searchname) ;
	debugprintf("printhelp: helpfname=%s\n",helpfname) ;
#endif

	fname = (char *) helpfname ;
	rs = SR_NOTFOUND ;
	if ((pr != NULL) && (helpfname[0] != '/')) {

#if	CF_DEBUGS
	    debugprintf("printhelp: partial fname=%s\n",helpfname) ;
#endif

	    if (strchr(helpfname,'/') != NULL) {

	        rs = mkpath2(tmpfname,pr,helpfname) ;

	        if (rs >= 0)
	            rs = u_access(tmpfname,R_OK) ;

#if	CF_DEBUGS
	        debugprintf("printhelp: partial rs=%d helpfname=%s\n",
			rs,tmpfname) ;
#endif

		if (rs >= 0)
		    fname = tmpfname ;

	    } /* end if */

	    if (rs < 0) {

	        vecstr	hs ;

	        int	opts ;
	        int	f_hs = FALSE ;


#if	CF_DEBUGS
	        debugprintf("printhelp: full fname=%s\n",helpfname) ;
#endif

/* first see if there is a "help schedule" in the ETC directory */

	        spp = schedule ;
	        rs = mkpath2(tmpfname,pr,HELPSCHEDFNAME) ;

	        if (rs >= 0)
	            rs = perm(tmpfname,-1,-1,NULL,R_OK) ;

	        if (rs >= 0) {

	            opts = VECSTR_OCOMPACT ;
	            rs1 = vecstr_start(&hs,15,opts) ;
	            f_hs = (rs1 >= 0) ;
	            if (rs1 >= 0) {

	                rs1 = vecstr_loadfile(&hs,FALSE,tmpfname) ;

	                if (rs1 >= 0)
	                    vecstr_getvec(&hs,&spp) ;

	            }

	        } /* end if (could access) */

/* create the values for the file schedule searching and find the file */

	        if ((rs = vecstr_start(&svars,6,0)) >= 0) {

	            if (pr != NULL)
	                vecstr_envadd(&svars,"r",pr,-1) ;

	            vecstr_envadd(&svars,"l",LIBDNAME,-1) ;

	            if (searchname != NULL)
	                vecstr_envadd(&svars,"n",searchname,-1) ;

/* OK, do the look-up */

	            rs1 = permsched(spp,&svars,helpfname,R_OK,
	                tmpfname,MAXPATHLEN) ;

	            if ((rs1 < 0) && (spp != schedule))
	                rs1 = permsched(schedule,&svars,helpfname,R_OK,
	                    tmpfname,MAXPATHLEN) ;

#if	CF_DEBUGS
	            debugprintf("printhelp: permsched() rs=%d tmpfname=%s\n",
	                rs,tmpfname) ;
#endif

	            if (rs1 > 0)
	                fname = tmpfname ;

	            vecstr_finish(&svars) ;

	        } /* end if (schedule variables) */

	        if (f_hs)
	            vecstr_finish(&hs) ;

	    } /* end if (error) */

	} /* end if (searching for file) */

#if	CF_DEBUGS
	debugprintf("printhelp: attempt_open rs=%d fname=%s\n",rs,fname) ;
#endif

	if (rs >= 0) {

	    if (fp == NULL) {
	        fp = &outfile ;
	        rs = bopen(&outfile,BFILE_STDOUT,"dw",0666) ;
	        f_open = (rs >= 0) ;
	    }

	    if ((rs >= 0) &&
	        ((rs = bopen(&helpfile,fname,"r",0666)) >= 0)) {

#if	CF_SFIO
	        {
	            int	len ;


	            while ((rs = bread(&helpfile,tmpfname,MAXPATHLEN)) > 0) {

	                len = rs ;
	                rs = sfwrite(fp,tmpfname,len) ;

#if	CF_DEBUGS
	                debugprintf("printhelp: sfwrite() rs=%d\n",rs) ;
#endif

	                if (rs < 0)
	                    break ;

	            } /* end while */

	        } /* end block */

#else /* CF_SFIO */

	        rs = bcopyblock(&helpfile,fp,-1) ;

#endif /* CF_SFIO */

	        bclose(&helpfile) ;

	    } /* end if (opened helpfile) */

#if	CF_SFIO
	    sfsync(fp) ;
#else
	    if (f_open)
	        bclose(fp) ;
#endif

	} /* end if (found a help file) */

ret0:

#if	CF_DEBUGS
	debugprintf("printhelp: ret rs=%d\n",rs) ;
#endif

	return rs ;
}
/* end subroutine (printhelp) */



