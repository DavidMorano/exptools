/* process */

/* process the input file into the dictionary files */


#define	CF_DEBUG 	0		/* run-time debug print-outs */


/* revision history:

	= 96/03/01, Dave Morano

	This subroutine was originally written.


	= 99/02/23, Dave Morano

	I enhanced the 'process' subroutine to place all words
	that start with the same letter (upper or lowercase) into
	the SAME output dictionary file.


*/


/***********************************************************************

	This subroutine processes ... something ! :-)


	Synopsis:

	int process(gp,dp,fname)
	struct proginfo	*pip ;
	DICTFILES	*dp ;
	const char	fname[] ;


	Arguments:

	- pip		program information pointer
	- dp		pointer to DICTFILES object
	- fname		file to process


	Returns:

	>=0		OK
	<0		error code


***********************************************************************/


#include	<sys/types.h>
#include	<sys/param.h>
#include	<sys/stat.h>
#include	<unistd.h>
#include	<limits.h>
#include	<string.h>
#include	<ctype.h>

#include	<bfile.h>

#include	"localmisc.h"
#include	"config.h"
#include	"defs.h"
#include	"dictfiles.h"



/* local defines */



/* external subroutines */

extern int	mkpath2(char *,const char *,const char *) ;
extern int	isprintlatin(int) ;


/* external variables */


/* forward references */







int process(pip,dp,fname)
struct proginfo	*pip ;
DICTFILES	*dp ;
const char	fname[] ;
{
	bfile	infile, *ifp = &infile ;

	int	rs, len, l ;
	int	c ;
	int	usage = 0 ;

	char	linebuf[LINEBUFLEN + 1] ;
	char	*cp ;


#if	CF_DEBUG
	if (DEBUGLEVEL(2))
	    debugprintf("process: entered, file=%s\n",fname) ;
#endif

	if (fname[0] == '-')
	    rs = bopen(ifp,BFILE_STDIN,"dr",0666) ;

	else
	    rs = bopen(ifp,fname,"r",0666) ;

	if (rs < 0)
	    goto ret0 ;

#if	CF_DEBUG
	if (DEBUGLEVEL(2))
	    debugprintf("process: starting\n") ;
#endif

	while ((rs = breadline(ifp,linebuf,LINEBUFLEN)) > 0) {

	    len = rs ;

#if	CF_DEBUG && 0
	if (DEBUGLEVEL(2))
	        debugprintf("process: line> %t",linebuf,len) ;
#endif

	    if (linebuf[0] == '\n')
		continue ;

	    if (linebuf[len - 1] != '\n') {

	        while ((c = bgetc(ifp)),((c != BR_EOF) && (c != '\n'))) ;

	        continue ;
	    }

	    if (len > MAXWORDLEN) 
		continue ;

	    if (! isprintlatin(linebuf[0]))
		continue ;

	    c = tolower(linebuf[0] & 255) ;

	    rs = dictfiles_write(dp,c, linebuf,len) ;

	    if (rs < 0) {

#if	CF_DEBUG
	if (DEBUGLEVEL(2))
	    debugprintf("process: dictfiles_write() rs=%d\n",rs) ;
#endif

	        break ;
	    }

	} /* end while (looping reading lines) */

	bclose(ifp) ;

ret0:

#if	CF_DEBUG
	if (DEBUGLEVEL(2))
	    debugprintf("process: ret rs=%d\n",rs) ;
#endif

	return rs ;
}
/* end subroutine (process) */



/* LOCAL SUBROUTINES */



