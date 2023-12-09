/* vecstr_loadfile */

/* load strings from a file */
/* version %I% last modified %G% */


#define	CF_DEBUGS	0		/* compile-time debug print-outs */
#define	CF_FILEBUF	1		/* use FILEBUF object */


/* revision history:

	= 1998-09-10, Dave Morano

	This module was originally written.


*/

/* Copyright © 1998 David Morano.  All rights reserved. */

/*****************************************************************************

	This subroutine will read (process) a file and put all of the
	strings found into the string (supplied) list, consisting of
	a VECSTR object.

	Synopsis:

	int vecstr_loadfile(vsp,fu,fname)
	vecstr		*vsp ;
	int		fu ;
	const char	fname[] ;

	Arguments:

	vsp		pointer to VECSTR object
	fu		flag specifying uniqueness
	fname		file to load

	Returns:

	>=0		number of elements loaded
	<0		error

	Notes:

	Why use FILEBUF over BIO?  Yes, FILEBUF is a tiny bit more
	lightweight than BIO -- on a good day.	But the real reason may be
	so that we don't need to load BIO in code very deep in a software
	stack if we don't need it -- like deep inside loadable modules.
	Anyway, just a thought!

	Why are we using FIELD as opposed to 'nextfield()' or something
	similar?  Because our sematics are to process quoted strings
	as a single VECSTR entry!


*****************************************************************************/


#include	<envstandards.h>	/* MUST be first to configure */

#include	<sys/types.h>
#include	<sys/param.h>
#include	<sys/stat.h>
#include	<fcntl.h>
#include	<unistd.h>
#include	<stdlib.h>
#include	<string.h>

#include	<vsystem.h>
#include	<vecstr.h>
#include	<field.h>
#include	<filebuf.h>
#include	<bfile.h>

#include	"localmisc.h"



/* local defines */

#undef	COMMENT

#ifndef	LINEBUFLEN
#ifdef	LINE_MAX
#define	LINEBUFLEN	MAX(LINE_MAX,2048)
#else
#define	LINEBUFLEN	2048
#endif
#endif

#ifndef	FD_STDIN
#define	FD_STDIN	0
#endif

#define	TO_READ		-1		/* read timeout */



/* external subroutines */

extern int	vecstr_adduniq(vecstr *,const char *,int) ;
extern int	vstrcmp(char **,char **) ;

#if	CF_DEBUGS
extern int	debugprintf(const char *,...) ;
extern int	strlinelen(const char *,int,int) ;
#endif


/* external variables */


/* forward references */


/* local structures */


/* local variables */

static const uchar	fterms[32] = {
	0x00, 0x04, 0x00, 0x00,
	0x08, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00
} ;


/* exported subroutines */


#if	CF_FILEBUF

static int vecstr_loadfd(VECSTR *,int,int) ;


int vecstr_loadfile(vsp,fu,fname)
vecstr		*vsp ;
int		fu ;
const char	fname[] ;
{
	int	rs = SR_OK ;
	int	fd = -1 ;
	int	c = 0 ;
	int	f_opened = FALSE ;


	if (fname == NULL)
	    return SR_FAULT ;

	if (fname[0] == '\0')
	    return SR_INVALID ;

/* try to open it */

	fd = FD_STDIN ;
	if (strcmp(fname,"-") != 0) {
	    rs = uc_open(fname,O_RDONLY,0666) ;
	    fd = rs ;
	    f_opened = (rs >= 0) ;
	}

	if (rs < 0)
	    goto ret0 ;

	rs = vecstr_loadfd(vsp,fu,fd) ;
	c = rs ;

	if (f_opened && (fd >= 0))
	    u_close(fd) ;

ret0:
	return (rs >= 0) ? c : rs ;
}
/* end subroutine (vecstr_loadfile) */


static int vecstr_loadfd(vsp,fu,fd)
VECSTR		*vsp ;
int		fu ;
int		fd ;
{
	struct stat	sb ;

	FIELD	fsb ;

	FILEBUF	loadfile, *lfp = &loadfile ;

	int	rs ;
	int	opts ;
	int	len ;
	int	fl ;
	int	to ;
	int	c = 0 ;

	const char	*fp ;

	char	linebuf[LINEBUFLEN + 1] ;


	rs = u_fstat(fd,&sb) ;
	if (rs < 0)
	    goto ret0 ;

	opts = 0 ;
	to = -1 ;
	if (! S_ISREG(sb.st_mode)) {
	    if (S_ISDIR(sb.st_mode)) {
		rs = SR_ISDIR ;
		goto ret0 ;
	    }
	    to = TO_READ ;
	    opts |= FILEBUF_ONET ;
	}

	rs = filebuf_start(lfp,fd,0L,0,opts) ;
	if (rs < 0)
	    goto ret0 ;

	while ((rs = filebuf_readline(lfp,linebuf,LINEBUFLEN,to)) > 0) {

	    len = rs ;
	    if (linebuf[len - 1] == '\n')
		len -= 1 ;

	    if ((len == 0) || (linebuf[0] == '#'))
		continue ;

#if	CF_DEBUGS
	debugprintf("vecstr_loadfile: line=>%t<\n",
		linebuf,strlinelen(linebuf,len,60)) ;
#endif

	    if ((rs = field_start(&fsb,linebuf,len)) >= 0) {

	        while ((fl = field_get(&fsb,fterms,&fp)) >= 0) {

#if	CF_DEBUGS
	debugprintf("vecstr_loadfile: f=>%t<\n",
		fp,strlinelen(fp,fl,70)) ;
#endif

	            if (fl > 0) {

			if (fu) {
	                    rs = vecstr_adduniq(vsp,fp,fl) ;

			} else
	                    rs = vecstr_add(vsp,fp,fl) ;

	                if (rs < 0)
	                    break ;

	                if (rs != INT_MAX)
	                    c += 1 ;

	            } /* end if (got one) */

	            if (fsb.term == '#')
	                break ;

	        } /* end while (fields) */

	        field_finish(&fsb) ;

	    } /* end if (fields) */

	    if (rs < 0)
		break ;

	} /* end while (reading lines) */

	filebuf_finish(lfp) ;

ret0:
	return (rs >= 0) ? c : rs ;
}
/* end subroutine (vecstr_loadfd) */

#else /* CF_FILEBUF */

int vecstr_loadfile(vsp,fu,fname)
vecstr		*vsp ;
int		fu ;
const char	fname[] ;
{
	FIELD	fsb ;

	bfile	loadfile, *lfp = &loadfile ;

	int	rs ;
	int	len ;
	int	fl ;
	int	c = 0 ;

	char	linebuf[LINEBUFLEN + 1] ;
	char	*fp ;


	if (fname == NULL)
	    return SR_FAULT ;

	if (fname[0] == '\0')
	    return SR_INVALID ;

/* try to open it */

	if (strcmp(fname,"-") != 0) {
	    rs = bopen(lfp,fname,"r",0666) ;
	} else
	    rs = bopen(lfp,BFILE_STDIN,"dr",0666) ;

	if (rs < 0)
	    goto ret0 ;

	while ((rs = breadline(lfp,linebuf,LINEBUFLEN)) > 0) {

	    len = rs ;
	    if (linebuf[len - 1] == '\n')
		len -= 1 ;

	    if ((len == 0) || (linebuf[0] == '#'))
		continue ;

#if	CF_DEBUGS
	debugprintf("vecstr_loadfile: line=>%t<\n",
		linebuf,strlinelen(linebuf,len,60)) ;
#endif

	    if ((rs = field_start(&fsb,linebuf,len)) >= 0) {

	        while ((fl = field_get(&fsb,fterms,&fp)) >= 0) {

#if	CF_DEBUGS
	debugprintf("vecstr_loadfile: f=>%t<\n",
		fp,strlinelen(fp,fl,70)) ;
#endif

	            if (fl > 0) {

			if (fu) {
	                    rs = vecstr_adduniq(vsp,fp,fl) ;

			} else
	                    rs = vecstr_add(vsp,fp,fl) ;

	                if (rs < 0)
	                    break ;

	                if (rs != INT_MAX)
	                    c += 1 ;

	            } /* end if (got one) */

	            if (fsb.term == '#')
	                break ;

	        } /* end while (fields) */

	        field_finish(&fsb) ;

	    } /* end if (fields) */

	    if (rs < 0)
		break ;

	} /* end while (reading lines) */

	bclose(lfp) ;

ret0:
	return (rs >= 0) ? c : rs ;
}
/* end subroutine (vecstr_loadfile) */

#endif /* CF_FILEBUF */



