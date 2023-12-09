/* main */

/* main subroutine for the GROPE directory arranger program */
/* version %I% last modified %G% */


#define	CF_DEBUGS	0		/* compile-time debug print-outs */
#define	CF_DEBUG	0		/* run-time debug print-outs */
#define	CF_GETEXECNAME	1		/* use 'getexecname(3c)' */


/* revision history:

	= 1998-09-01, Dave Morano

	This program was originally written.


*/

/* Copyright © 1998 David Morano.  All rights reserved. */

/*****************************************************************************

	This is part of the program to rebuilt the dictionary files
	for the EXPTOOLS 'GROPE' program.


*****************************************************************************/


#include	<envstandards.h>	/* MUST be first to configure */

#include	<sys/types.h>
#include	<sys/param.h>
#include	<sys/socket.h>
#include	<netinet/in.h>
#include	<arpa/inet.h>
#include	<unistd.h>
#include	<stdlib.h>
#include	<fcntl.h>
#include	<time.h>
#include	<dirent.h>
#include	<string.h>
#include	<ctype.h>
#include	<netdb.h>
#include	<ftw.h>

#include	<vsystem.h>
#include	<bfile.h>
#include	<field.h>
#include	<logfile.h>
#include	<userinfo.h>
#include	<bitops.h>
#include	<varsub.h>
#include	<exitcodes.h>
#include	<mallocstuff.h>

#include	"localmisc.h"
#include	"config.h"
#include	"defs.h"
#include	"configfile.h"
#include	"dictfiles.h"



/* local defines */

#define	MAXARGINDEX	100
#define	MAXARGGROUPS	(MAXARGINDEX/8 + 1)
#define	NUMNAMES	12
#define	NAMEBUFLEN	(NUMNAMES * MAXPATHLEN)

#ifndef	BUFLEN
#define	BUFLEN		((8 * 1024) + NAMEBUFLEN)
#endif



/* external subroutines */

extern int	sncpy1(char *,int,const char *) ;
extern int	mkpath1(char *,const char *) ;
extern int	mkpath2(char *,const char *,const char *) ;
extern int	mkfnamesuf(char *,const char *,const char *) ;
extern int	matstr(const char **,const char *,int) ;
extern int	matostr(const char **,int,const char *,int) ;
extern int	cfdeci(const char *,int,int *) ;
extern int	getnodedomain(char *,char *) ;
extern int	logfile_userinfo(LOGFILE *,USERINFO *,time_t,
			const char *,const char *) ;

extern int	proginfo_setpiv(struct proginfo *,const char *,
			const struct pivars *) ;
extern int	printhelp(void *,const char *,const char *,const char *) ;
extern int	process(struct proginfo *,DICTFILES *,const char *) ;
extern int	varsub_subbuf(), varsub_merge() ;
extern int	expander() ;

extern char	*timestr_log(time_t,char *) ;


/* externals variables */


/* forward references */

static int	usage(struct proginfo *) ;

static char	*filereadable() ;


/* local global variabes */


/* local structures */


/* local variables */

static const char *argopts[] = {
	"TMPDIR",
	"VERSION",
	"VERBOSE",
	"ROOT",
	"LOGFILE",
	"CONFIG",
	"GETDICTDIR",
	"HELP",
	NULL
} ;

enum argopts {
	argopt_tmpdir,
	argopt_version,
	argopt_verbose,
	argopt_root,
	argopt_logfile,
	argopt_config,
	argopt_getdict,
	argopt_help,
	argopt_overlast
} ;

static const struct pivars	initvars = {
	VARPROGRAMROOT1,
	VARPROGRAMROOT2,
	VARPROGRAMROOT3,
	PROGRAMROOT,
	VARPRNAME
} ;

static const struct mapex	mapexs[] = {
	{ SR_NOENT, EX_NOUSER },
	{ SR_AGAIN, EX_TEMPFAIL },
	{ SR_DEADLK, EX_TEMPFAIL },
	{ SR_NOLCK, EX_TEMPFAIL },
	{ SR_TXTBSY, EX_TEMPFAIL },
	{ SR_ACCESS, EX_NOPERM },
	{ SR_REMOTE, EX_PROTOCOL },
	{ SR_NOSPC, EX_TEMPFAIL },
	{ 0, 0 }
} ;


/* exported subroutines */


int main(argc,argv,envv)
int	argc ;
char	*argv[] ;
char	*envv[] ;
{
	struct proginfo	pi, *pip = &pi ;

	USERINFO	u ;

	CONFIGFILE	cf ;

	DICTFILES	dics ;

	varsub		vsh_e, vsh_d ;

	bfile		errfile ;
	bfile		outfile, *ofp = &outfile ;

	int	argr, argl, aol, akl, avl, kwi ;
	int	ai, ai_max, ai_pos ;
	int	argvalue = -1 ;
	int	pan ;
	int	rs, rs1, i, j, l ;
	int	loglen = -1 ;
	int	l2 ;
	int	ex = EX_INFO ;
	int	f_optminus, f_optplus, f_optequal ;
	int	f_version = FALSE ;
	int	f_usage = FALSE ;
	int	f_help = FALSE ;
	int	f_getdict = FALSE ;
	int	f ;

	char	*argp, *aop, *akp, *avp ;
	char	argpresent[MAXARGGROUPS] ;
	char	buf[BUFLEN + 1] ;
	char	buf2[BUFLEN + 1] ;
	char	userbuf[USERINFO_LEN + 1] ;
	char	nodename[NODENAMELEN + 1], domainname[MAXHOSTNAMELEN + 1] ;
	char	tmpfname[MAXPATHLEN + 1] ;
	char	timebuf[TIMEBUFLEN + 1] ;
	char	*pr = NULL ;
	char	*searchname = NULL ;
	char	*configfname = NULL ;
	char	*logfname = NULL ;
	char	*dictdname = NULL ;
	char	*outfname = NULL ;
	char	*cp ;


#if	CF_DEBUGS || CF_DEBUG
	if ((cp = getenv(VARDEBUGFNAME)) == NULL) {
	    if ((cp = getenv(VARDEBUGFD1)) == NULL)
	        cp = getenv(VARDEBUGFD2) ;
	}
	if (cp != NULL)
		debugopen(cp) ;
	debugprintf("main: starting\n") ;
#endif /* CF_DEBUGS */

	rs = proginfo_init(pip,envv,argv[0],VERSION) ;
	if (rs < 0) {
	    ex = EX_OSERR ;
	    goto ret0 ;
	}

	proginfo_banner(pip,BANNER) ;

	if ((cp = getenv(VARERRORFNAME)) != NULL) {
	    rs = bopen(&errfile,cp,"wca",0666) ;
	} else
	    rs = bopen(&errfile,BFILE_STDERR,"dwca",0666) ;
	if (rs >= 0) {
	    pip->efp = &errfile ;
	    bcontrol(&errfile,BC_LINEBUF,0) ;
	}

/* initialize */

	pip->verboselevel = 1 ;

/* start parsing the arguments */

	rs = SR_OK ;
	for (ai = 0 ; ai < MAXARGGROUPS ; ai += 1) 
		argpresent[ai] = 0 ;

	ai = 0 ;
	ai_max = 0 ;
	ai_pos = 0 ;
	argr = argc - 1 ;
	while ((rs >= 0) && (argr > 0)) {

	    argp = argv[++ai] ;
	    argr -= 1 ;
	    argl = strlen(argp) ;

	    f_optminus = (*argp == '-') ;
	    f_optplus = (*argp == '+') ;
	    if ((argl > 1) && (f_optminus || f_optplus)) {

	        if (isdigit(argp[1])) {

	                rs = cfdeci((argp + 1),(argl - 1),&argvalue) ;

	        } else if (argp[1] == '-') {

	            ai_pos = ai ;
	            break ;

	        } else {

	            aop = argp + 1 ;
	            akp = aop ;
	            aol = argl - 1 ;
	            f_optequal = FALSE ;
	            if ((avp = strchr(aop,'=')) != NULL) {
	                f_optequal = TRUE ;
	                akl = avp - aop ;
	                avp += 1 ;
	                avl = aop + argl - 1 - avp ;
	                aol = akl ;
	            } else {
	                avp = NULL ;
	                avl = 0 ;
	                akl = aol ;
	            }

/* do we have a keyword match or should we assume only key letters? */

	            if ((kwi = matostr(argopts,2,akp,akl)) >= 0) {

	                    switch (kwi) {

	                    case argopt_tmpdir:
	                        if (f_optequal) {

	                            f_optequal = FALSE ;
	                            if (avl) 
					pip->tmpdname = avp ;

	                        } else {

	                            if (argr <= 0) {
					rs = SR_INVALID ;
					break ;
				    }

	                            argp = argv[++ai] ;
	                            argr -= 1 ;
	                            argl = strlen(argp) ;

	                            if (argl) 
					pip->tmpdname = argp ;

	                        }

	                        break ;

/* version */
	                    case argopt_version:
				f_version = TRUE ;
	                        if (f_optequal) 
					rs = SR_INVALID ;

	                        break ;

/* verbose mode */
	                    case argopt_verbose:
	                        pip->verboselevel = 1 ;
	                        break ;

/* program root */
	                    case argopt_root:
	                        if (f_optequal) {

	                            f_optequal = FALSE ;
	                            if (avl) 
					pip->pr = avp ;

	                        } else {

	                            if (argr <= 0) {
					rs = SR_INVALID ;
					break ;
				    }

	                            argp = argv[++ai] ;
	                            argr -= 1 ;
	                            argl = strlen(argp) ;

	                            if (argl) 
					pip->pr = argp ;

	                        }

	                        break ;

/* configuration file */
	                    case argopt_config:
	                        if (f_optequal) {

	                            f_optequal = FALSE ;
	                            if (avl) 
					configfname = avp ;

	                        } else {

	                            if (argr <= 0) {
					rs = SR_INVALID ;
					break ;
				    }

	                            argp = argv[++ai] ;
	                            argr -= 1 ;
	                            argl = strlen(argp) ;

	                            if (argl) 
					configfname = argp ;

	                        }

	                        break ;

/* log file */
	                    case argopt_logfile:
	                        if (f_optequal) {

	                            f_optequal = FALSE ;
	                            if (avl) 
					logfname = avp ;

	                        } else {

	                            if (argr <= 0) {
					rs = SR_INVALID ;
					break ;
				    }

	                            argp = argv[++ai] ;
	                            argr -= 1 ;
	                            argl = strlen(argp) ;

	                            if (argl) 
					logfname = argp ;

	                        }

	                        break ;

/* get the dictionary directory */
	                    case argopt_getdict:
	                        f_getdict = TRUE ;
	                        break ;

/* print out the help */
	                    case argopt_help:
	                        f_help = TRUE ;
	                        break ;

/* handle all keyword defaults */
	                    default:
				rs = SR_INVALID ;
	                        bprintf(pip->efp,
					"%s: option (%s) not supported\n",
	                            pip->progname,akp) ;

	                    } /* end switch */

	                } else {

	                    while (akl--) {

				int	kc = (*akp & 0xff) ;
	                        switch (kc) {

/* debug */
	                        case 'D':
	                            pip->debuglevel = 1 ;
	                            if (f_optequal) {

	                                f_optequal = FALSE ;
	                                if (avl > 0)
	                                    rs = cfdec(avp,avl,
						&pip->debuglevel) ;

	                            }

	                            break ;

/* version */
	                        case 'V':
	                            f_version = TRUE ;
	                            break ;

/* configuration file */
	                        case 'C':
	                            if (argr <= 0) {
					rs = SR_INVALID ;
					break ;
				    }

	                            argp = argv[++ai] ;
	                            argr -= 1 ;
	                            argl = strlen(argp) ;

	                            if (argl) 
					configfname = argp ;

	                            break ;

/* dictionary directory */
	                        case 'd':
	                        case 'l':
	                            if (argr <= 0) {
					rs = SR_INVALID ;
					break ;
				    }

	                            argp = argv[++ai] ;
	                            argr -= 1 ;
	                            argl = strlen(argp) ;

	                            if (argl) 
					dictdname = argp ;

	                            break ;

/* verbose mode */
	                        case 'v':
	                            pip->verboselevel += 1 ;
	                            break ;

	                        case '?':
	                            f_usage = TRUE ;
					break ;

	                        default:
					rs = SR_INVALID ;
	                            bprintf(pip->efp,
					"%s: unknown option - %c\n",
	                                pip->progname,*aop) ;

	                        } /* end switch */

	                        akp += 1 ;
				if (rs < 0)
					break ;

	                } /* end while */

	            } /* end if (individual option key letters) */

	        } /* end if (digits or progopts) */

	    } else {

	        if (ai >= MAXARGINDEX)
	            break ;

	        BSET(argpresent,ai) ;
	        ai_max = ai ;

	    } /* end if (key letter/word or positional) */

	    ai_pos = ai ;

	} /* end while (all command line argument processing) */

	if (rs < 0)
	    goto badarg ;

#if	CF_DEBUGS
	    debugprintf("main: debuglevel=%u\n",pip->debuglevel) ;
#endif

#if	CF_DEBUG
	if (DEBUGLEVEL(2))
	    debugprintf("main: finished parsing arguments\n") ;
#endif

	if (f_version)
	    bprintf(pip->efp,"%s: version %s\n",
	        pip->progname,VERSION) ;

	if (pip->debuglevel > 0) {
	    bprintf(pip->efp,"%s: debuglevel=%u\n",
	        pip->progname,pip->debuglevel) ;
	    bflush(pip->efp) ;
	}

	rs = proginfo_setpiv(pip,pr,&initvars) ;

	if (rs >= 0)
	    rs = proginfo_searchname(pip,VARSEARCHNAME,searchname) ;

	if (rs < 0) {
	    ex = EX_OSERR ;
	    goto retearly ;
	}

#if	CF_DEBUG
	if (DEBUGLEVEL(2))
	    debugprintf("main: pr=%s\n",pip->pr) ;
#endif

	if (pip->debuglevel > 0) {

	    bprintf(pip->efp,"%s: pr=%s\n",
	        pip->progname,pip->pr) ;

	    bprintf(pip->efp,"%s: sn=%s\n",
	        pip->progname,pip->searchname) ;

	} /* end if */

/* get our program mode */

#ifdef	COMMENT
	if (pmspec == NULL)
	    pmspec = pip->searchname ;

	pip->progmode = matstr(progmodes,pmspec,-1) ;

	if (pip->progmode < 0)
	    pip->progmode = progmode_filesize ;

#if	CF_DEBUG
	if (DEBUGLEVEL(4)) {
	    if (pip->progmode >= 0)
	        debugprintf("main: progmode=%s(%u)\n",
	            progmodes[pip->progmode],pip->progmode) ;
	    else
	        debugprintf("main: progmode=NONE\n") ;
	}
#endif /* CF_DEBUG */
#endif /* COMMENT */

	if (f_usage)
	    usage(pip) ;

/* help file */

	if (f_help)
	    printhelp(NULL,pip->pr,pip->searchname,HELPFNAME) ;

	if (f_help || f_version || f_usage)
	    goto retearly ;


	ex = EX_OK ;

/* check a few more things */

	if (pip->tmpdname == NULL)
	    pip->tmpdname = getenv(VARTMPDNAME) ;

	if (pip->tmpdname == NULL)
	    pip->tmpdname = TMPDNAME ;

/* get some host/user information */

	rs = userinfo(&u,userbuf,USERINFO_LEN) ;

	if (rs < 0) {
	    ex = EX_NOUSER ;
	    goto retearly ;
	}

	pip->pid = u.pid ;
	pip->username = u.username ;
	pip->nodename = u.nodename ;
	pip->domainname = u.domainname ;
	pip->logid = u.logid ;

/* find a configuration file if we have one */

#if	CF_DEBUG
	if (DEBUGLEVEL(2))
		debugprintf(
	    "main: checking for configuration file\n") ;
#endif

/* search locally */

	if ((configfname == NULL) || (configfname[0] == '\0'))
	    configfname = filereadable(tmpfname,
	        NULL,ETCDIR1,CONFIGFNAME1) ;

	if (configfname == NULL)
	    configfname = filereadable(tmpfname,
	        NULL,ETCDIR1,CONFIGFNAME2) ;

	if (configfname == NULL)
	    configfname = filereadable(tmpfname,
	        NULL,ETCDIR2,CONFIGFNAME1) ;

	if (configfname == NULL) {

	    configfname = CONFIGFNAME1 ;
	    if (u_access(configfname,R_OK) < 0)
	        configfname = NULL ;

	}

	if (configfname == NULL) {

	    configfname = CONFIGFNAME2 ;
	    if (u_access(configfname,R_OK) < 0)
	        configfname = NULL ;

	}

/* search in our program root area */

	if ((configfname == NULL) || (configfname[0] == '\0'))
	    configfname = filereadable(tmpfname,
	        pip->pr,ETCDIR1,CONFIGFNAME1) ;

	if (configfname == NULL)
	    configfname = filereadable(tmpfname,
	        pip->pr,ETCDIR1,CONFIGFNAME2) ;

	if (configfname == NULL)
	    configfname = filereadable(tmpfname,
	        pip->pr,ETCDIR2,CONFIGFNAME1) ;

/* read in the configuration file if we have one */

	if (u_access(configfname,R_OK) >= 0) {

#if	CF_DEBUG
	    if (DEBUGLEVEL(2))
		debugprintf("main: we have a configuration file \"%s\"\n",
	        configfname) ;
#endif

	    rs = configfile_start(&cf,configfname) ;

		if (rs < 0)
	        goto badconfig ;

#if	CF_DEBUG
	    if (DEBUGLEVEL(2))
		debugprintf("main: we have a good configuration file\n") ;
#endif

#if	CF_DEBUG
	    if (pip->debuglevel > 1) debugprintf(
	        "main: varsub_start d\n") ;
#endif

	    varsub_start(&vsh_d,0) ;

#if	CF_DEBUG
	    if (DEBUGLEVEL(2))
		debugprintf("main: varsub_start e\n") ;
#endif

	    varsub_start(&vsh_e,0) ;

#if	CF_DEBUG
	    if (DEBUGLEVEL(2))
		debugprintf("main: varsub_load\n") ;
#endif

	    varsub_loadenv(&vsh_e,(const char **) envv) ;


	    if ((cf.logfname != NULL) && (logfname == NULL)) {

#if	CF_DEBUG
	    if (DEBUGLEVEL(2))
	            debugprintf("main: CF logfilename=%s\n",cf.logfname) ;
#endif

	        if (((l = varsub_subbuf(&vsh_d,&vsh_e,cf.logfname,
	            -1,buf,BUFLEN)) > 0) &&
	            ((l2 = expander(pip,buf,l,buf2,BUFLEN)) > 0)) {

	            logfname = mallocstrw(buf2,l2) ;

	        }

#if	CF_DEBUG
	    if (DEBUGLEVEL(2))
	            debugprintf("main: processed CF logfilename=%s\n",logfname) ;
#endif

	        cf.logfname = NULL ;

	    } /* end if (configuration file log filename) */

	    if ((cf.root != NULL) && (pip->pr == NULL)) {

#if	CF_DEBUG
	    if (DEBUGLEVEL(2))
	            debugprintf("main: CF pr=%s\n",
				cf.root) ;
#endif

	        if (((l = varsub_subbuf(&vsh_d,&vsh_e,cf.root,
	            -1,buf,BUFLEN)) > 0) &&
	            ((l2 = expander(pip,buf,l,buf2,BUFLEN)) > 0)) {

	            pip->pr = mallocstrw(buf2,l2) ;

	        }

	        cf.root = NULL ;

	    }

#ifdef	COMMENT
	    if ((cf.dictionary != NULL) && (pip->dictdname == NULL)) {

#if	CF_DEBUG
	    if (DEBUGLEVEL(2))
	            debugprintf("main: processing dictionary \n") ;
#endif

	        if (((l = varsub_subbuf(&vsh_d,&vsh_e,cf.dictionary,
	            -1,buf,BUFLEN)) > 0) &&
	            ((l2 = expander(pip,buf,l,buf2,BUFLEN)) > 0)) {

	            pip->dictdname = mallocstrw(buf2,l2) ;

	        }

	        cf.dictionary = NULL ;

	    }
#endif /* COMMENT */

#ifdef	COMMENT
	    if ((cf.prefix != NULL) && (pip->prefix == NULL)) {

#if	CF_DEBUG
	    if (DEBUGLEVEL(2))
	            debugprintf("main: CF prefix=%s\n",
			cf.prefix) ;
#endif

	        if (((l = varsub_subbuf(&vsh_d,&vsh_e,cf.prefix,
	            -1,buf,BUFLEN)) > 0) &&
	            ((l2 = expander(pip,buf,l,buf2,BUFLEN)) > 0)) {

#if	CF_DEBUG
	    if (DEBUGLEVEL(2))
	                debugprintf("main: 1 CF subed and expanded prefix=%W\n",
				buf2,l2) ;
#endif

	            pip->prefix = mallocstrw(buf2,l2) ;

	        }

	        cf.prefix = NULL ;

#if	CF_DEBUG
	    if (DEBUGLEVEL(2))
	            debugprintf("main: 2 CF processing prefix=%s\n",
			pip->prefix) ;
#endif

	    } /* end if (prefix) */
#endif /* COMMENT */

#ifdef	COMMENT
	    if ((cf.helpfile != NULL) && (pip->helpfname == NULL)) {

#if	CF_DEBUG
	    if (DEBUGLEVEL(2))
	            debugprintf("main: CF helpfile=%s\n",cf.helpfile) ;
#endif

	        if (((l = varsub_subbuf(&vsh_d,&vsh_e,cf.helpfile,
	            -1,buf,BUFLEN)) > 0) &&
	            ((l2 = expander(pip,buf,l,buf2,BUFLEN)) > 0)) {

#if	CF_DEBUG
	    if (DEBUGLEVEL(2))
	                debugprintf("main: helpfile subed and expanded\n") ;
#endif

	            pip->helpfname = mallocstrw(buf2,l2) ;

	        }

	        cf.helpfile = NULL ;

	    } /* end if (helpfile) */
#endif /* COMMENT */

#if	CF_DEBUG
	    if (DEBUGLEVEL(2))
	        debugprintf("main: processing CF loglen\n") ;
#endif

	    if ((cf.loglen >= 0) && (loglen < 0)) {

	        loglen = cf.loglen ;

	    }

#if	CF_DEBUG
	    if (DEBUGLEVEL(2))
	        debugprintf("main: processing CF freeing data structures\n") ;
#endif

	    varsub_finish(&vsh_d) ;

	    varsub_finish(&vsh_e) ;

#if	CF_DEBUG
	    if (DEBUGLEVEL(2))
	        debugprintf("main: processing CF free\n") ;
#endif

	    configfile_finish(&cf) ;

	} /* end if (accessed the configuration file) */

#if	CF_DEBUG
	    if (DEBUGLEVEL(2))
		debugprintf("main: finished with any configfile stuff\n") ;
#endif

#if	CF_DEBUG
	    if (DEBUGLEVEL(2))
	    debugprintf("main: final pr=%s\n",pip->pr) ;
#endif

/* check program parameters */

#if	CF_DEBUG
	    if (DEBUGLEVEL(2))
		debugprintf("main: checking program parameters\n") ;
#endif

	if ((pip->tmpdname == NULL) || (pip->tmpdname[0] == '\0')) {

	    if ((cp = getenv("TMPDIR")) != NULL)
	        pip->tmpdname = cp ;

	    else
	        pip->tmpdname = TMPDNAME ;

	} /* end if (tmpdname) */

/* clean up the dictionary path as we may have it */

	if ((dictdname == NULL) || (dictdname[0] == '\0'))
	    dictdname = DICTDNAME ;

	rs = u_access(dictdname,(W_OK | X_OK | R_OK)) ;

	if ((rs < 0) && (dictdname[0] != '/')) {

	    mkpath2(tmpfname,
	        pip->pr,dictdname) ;

	    if ((rs = u_access(tmpfname,(W_OK | X_OK | R_OK))) >= 0)
	        dictdname = tmpfname ;

	} /* end if */

	if (rs < 0) 
		goto baddictionary ;

	mkpath1(pip->dictdname,dictdname) ;

#if	CF_DEBUG
	    if (DEBUGLEVEL(2))
	    debugprintf("main: dictionary=%s\n",pip->dictdname) ;
#endif

	if (pip->debuglevel > 0)
	    bprintf(pip->efp,"%s: dictionary=%s\n",
	        pip->progname,pip->dictdname) ;

/* do we have a prefix string for the dictionary files ? */

#if	CF_DEBUG
	    if (DEBUGLEVEL(2))
	    debugprintf("main: 0 prefix=%s\n",pip->prefix) ;
#endif

	if ((pip->prefix == NULL) || (pip->prefix[0] == '\0'))
	    pip->prefix = PREFIX ;

#if	CF_DEBUG
	    if (DEBUGLEVEL(2))
	    debugprintf("main: 1 prefix=%s\n",pip->prefix) ;
#endif

/* do we have an activity log file ? */

#if	CF_DEBUG
	    if (DEBUGLEVEL(2))
	    debugprintf("main: 0 logfname=%s\n",logfname) ;
#endif

	rs = SR_NOENT ;
	if ((logfname == NULL) || (logfname[0] == '\0'))
	    logfname = LOGFNAME ;

	if ((logfname[0] == '/') || (u_access(logfname,W_OK) >= 0))
	    rs = logfile_open(&pip->lh,logfname,0666,pip->logid) ;

#if	CF_DEBUG
	    if (DEBUGLEVEL(2))
	    debugprintf("main: 1 logfname=%s rs=%d\n",logfname,rs) ;
#endif

	if ((rs < 0) && (logfname[0] != '/')) {

	    mkpath2(tmpfname, pip->pr,logfname) ;

	    rs = logfile_open(&pip->lh,tmpfname,0666,pip->logid) ;

#if	CF_DEBUG
	    if (DEBUGLEVEL(2))
	        debugprintf("main: 2 logfname=%s rs=%d\n",tmpfname,rs) ;
#endif

	} /* end if (we tried to open another log file) */

	if (rs >= 0) {

	    pip->open.log = TRUE ;
	    if (loglen < 0) loglen = LOGSIZE ;

	    logfile_checksize(&pip->lh,loglen) ;

	    logfile_userinfo(&pip->lh,&u,
	        pip->daytime,pip->searchname,pip->version) ;

	    logfile_printf(&pip->lh,"dictionary dir=%s\n",
	        pip->dictdname) ;

	} /* end if (we have a log file or not) */

/* print out the dictionary directory if requested */

	if (f_getdict) {

#if	CF_DEBUG
	    if (DEBUGLEVEL(2))
	        debugprintf("main: getdict\n") ;
#endif

	    if (outfname == NULL)
	        rs = bopen(ofp,BFILE_STDOUT,"dwct",0666) ;

	    else
	        rs = bopen(ofp,outfname,"wct",0666) ;

	    if (rs >= 0) {

	        bprintf(ofp,"%s\n",pip->dictdname) ;

	        bclose(ofp) ;

	    }

	} /* end if (printing out the dictionary directory path) */

/* initialize the output files */

#if	CF_DEBUG
	    if (DEBUGLEVEL(2))
	        debugprintf("main: dictfiles_open() \n") ;
#endif

	rs = dictfiles_open(&dics,NOUTFILES,pip->dictdname,pip->prefix) ;

#if	CF_DEBUG
	    if (DEBUGLEVEL(2))
	        debugprintf("main: dictfiles_open() rs=%d\n",rs) ;
#endif

	if (rs < 0) {

		switch (rs) {

		case SR_INPROGRESS:
		ex = EX_UNAVAILABLE ;
		break ;

		default:
		ex = EX_SOFTWARE ;

		} /* end switch */

		goto done ;
	}

/* process the positional arguments */

#if	CF_DEBUG
	if (DEBUGLEVEL(2))
		debugprintf(
	    "main: checking for positional arguments\n") ;
#endif

	pan = 0 ;

	for (ai = 1 ; ai < argc ; ai += 1) {

	    f = (ai <= ai_max) && BTST(argpresent,ai) ;
	    f = f || (ai > ai_pos) ;
	    if (! f) continue ;

	    cp = argv[ai] ;
	    pan += 1 ;
	        rs = process(pip,&dics,cp) ;

		if (rs < 0) {

	            if (*cp == '-') 
			cp = "*stdinput*" ;

	            bprintf(pip->efp,"%s: error processing input file (%d)\n",
	                pip->progname,rs) ;

	            bprintf(pip->efp,"%s: file=%s\n",
	                pip->progname,cp) ;

	        }

	} /* end for (processing positional arguments) */

	if ((rs >= 0) && (pan == 0)) {

	    cp = "-" ;
	    pan += 1 ;
	        rs = process(pip,&dics,cp) ;

		if (rs < 0) {

	            if (*cp == '-') 
			cp = "*stdinput*" ;

	            bprintf(pip->efp,"%s: error processing input file (%d)\n",
	                pip->progname,rs) ;

	            bprintf(pip->efp,"%s: file=%s\n",
	                pip->progname,cp) ;

	        }

	} /* end if */

/* close the output files */

	rs1 = dictfiles_close(&dics) ;

#if	CF_DEBUG
	if (DEBUGLEVEL(2))
	debugprintf("main: dictfiles_close() rs=%d\n",rs1) ;
#endif

	if (rs >= 0)
		rs = rs1 ;

#ifdef	COMMENT
	    bprintf(pip->efp,"%s: %d file(s) used simultaneously\n",
	        pip->progname,rs1) ;
#endif

#ifdef	COMMENT
	    j = 0 ;
	    for (i = 0 ; i < 256 ; i += 1) {

	        if (outtable[i]->letter != '\0')
	            j += 1 ;

	    } /* end for */

	    bprintf(pip->efp,"%s: %u files written\n",
	        pip->progname,j) ;
#endif /* COMMENT */

#if	CF_DEBUG
	if (DEBUGLEVEL(2))
	debugprintf("main: exiting rs=%d \n",rs) ;
#endif

/* we are done */
done:
	ex = (rs >= 0) ? EX_OK : EX_DATAERR ;

	if (pip->open.log)
	    logfile_close(&pip->lh) ;

	if ((configfname != NULL) && (configfname[0] != '\0'))
	    configfile_finish(&cf) ;

/* return */
retearly:
	if (pip->debuglevel > 0)
	    bprintf(pip->efp,"%s: exiting ex=%u\n",
		pip->progname,ex) ;

ret2:
	bclose(pip->efp) ;

ret1:
	proginfo_free(pip) ;

ret0:
	return ex ;

/* bad stuff */
badarg:
	ex = EX_USAGE ;
	bprintf(pip->efp,"%s: invalid argument specified (%d)\n",
	    pip->progname,rs) ;

	usage(pip) ;

	goto retearly ;

badconfig:
	bprintf(pip->efp,
	    "%s: error (%d) in configuration file starting at line %d\n",
	    pip->progname,rs,cf.badline) ;

	goto retearly ;

baddictionary:
	bprintf(pip->efp,
	    "%s: could not access dictionary, dir=%s (%d)\n",
	    pip->progname,pip->dictdname,rs) ;

	goto retearly ;

}
/* end subroutine (main) */


/* local subroutines */


static int usage(pip)
struct proginfo	*pip ;
{
	int	rs ;
	int	wlen = 0 ;


	rs = bprintf(pip->efp,
	    "%s: USAGE> %s [-C <conf>] [<file(s)> ...] [-d <dictdir>] \n",
	    pip->progname,pip->progname) ;

	wlen += rs ;
	rs = bprintf(pip->efp,
	    "%s:  [-Q] [-D] [-v[=<n>]] [-HELP] [-V]\n",
	    pip->progname) ;

	wlen += rs ;
	return (rs >= 0) ? wlen : rs ;
}
/* end subroutine (usage) */


/* is a file readable */
static char *filereadable(tmpfname,dir1,dir2,fname)
char	tmpfname[], dir1[], dir2[], fname[] ;
{


	if ((dir1 != NULL) && (dir2 != NULL))
	    sprintf(tmpfname,"%s/%s/%s",
	        dir1,dir2,fname) ;

	else if (dir1 != NULL)
	    sprintf(tmpfname,"%s/%s",
	        dir1,fname) ;

	else if (dir2 != NULL)
	    sprintf(tmpfname,"%s/%s",
	        dir2,fname) ;

	else
	    strcpy(tmpfname,fname) ;

	if (u_access(tmpfname,R_OK) >= 0)
	    return tmpfname ;

	return NULL ;
}
/* end subroutine (filereadable) */



