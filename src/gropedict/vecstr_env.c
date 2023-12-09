/* vecstr_env */

/* environment-type string handling */


#define	CF_DEBUGS	0		/* compile-time debug print-outs */
#define	CF_SNCPY	1		/* use 'sncpyx(3dam)' */


/* revision history:

	= 1998-03-01, Dave Morano

	This module was originally written.


*/

/* Copyright © 1998 David Morano.  All rights reserved. */

/******************************************************************************

	This subroutine extends the VECSTR object to add a key-value
	pair to the vector list.  Key-value pairs are two strings
	(the key and the value) joined with an intervening equal sign
	character ('=').  Duplicate entries are checked for (after all,
	this was originally intended for environment variables) and
	are not added if already present.

	Synopsis:

	int vecstr_envadd(op,kp,vp,vl)
	vecstr		*op ;
	const char	*kp ;
	const char	*vp ;
	int		vl ;

	Arguments:

	op		vecstr string to add to
	kp		pointer to key string
	vp		pointer to value string
	bl		length of value string

	Returns:

	>=0		OK
	<0		error


******************************************************************************/


#include	<envstandards.h>	/* MUST be first to configure */

#include	<sys/types.h>
#include	<sys/param.h>
#include	<limits.h>
#include	<stdlib.h>
#include	<string.h>

#include	<vsystem.h>
#include	<vecstr.h>
#include	<char.h>

#if	(! CF_SNCPY)
#include	<sbuf.h>
#endif

#include	"localmisc.h"



/* local defines */

#undef	COMMENT

#ifndef	KEYBUFLEN
#define	KEYBUFLEN	120
#endif



/* external subroutines */

extern int	sncpy2(char *,int,const char *,const char *) ;
extern int	sncpy3(char *,int,const char *,const char *,const char *) ;
extern int	snwcpy(char *,int,const char *,int) ;
extern int	vstrkeycmp(char **,char **) ;

extern char	*strnpbrk(const char *,int,const char *) ;
extern char	*strnchr(const char *,int,int) ;
extern char	*strwcpy(char *,const char *,int) ;


/* external variables */


/* local structures */


/* forward references */

static int vecstr_addwithin(VECSTR *,const char *,int) ;


/* local variables */


/* exported subroutines */


/* add a key=value string pair to the environment list */
int vecstr_envadd(op,kp,vp,vl)
vecstr		*op ;
const char	*kp ;
const char	*vp ;
int		vl ;
{
	int	rs ;
	int	i = INT_MAX ;


	if (op == NULL)
	    return SR_FAULT ;

	if (op->va == NULL)
	    return SR_NOTOPEN ;

	if (kp == NULL)
	    return SR_FAULT ;

	rs = vecstr_finder(op,kp,vstrkeycmp,NULL) ;

	if (rs == SR_NOTFOUND) {
	    rs = vecstr_addkeyval(op,kp,-1,vp,vl) ;
	    i = rs ;
	}

	return (rs >= 0) ? i : rs ;
}
/* end subroutine (vecstr_envadd) */


/* load a series of key=value pairs */
int vecstr_envadds(op,s,slen)
VECSTR		*op ;
const char	s[] ;
int		slen ;
{
	int	rs = SR_OK ;
	int	sl, cl ;
	int	c = 0 ;

	const char	*sp ;

	char	*cp, *tp ;


	if (op == NULL)
	    return SR_FAULT ;

	if (op->va == NULL)
	    return SR_NOTOPEN ;

	if (s == NULL)
	    return SR_FAULT ;

	if (slen <= 0)
	    slen = strlen(s) ;

#if	CF_DEBUGS
	debugprintf("vecstr_envadds: entered >%t<\n",
	    s,strnlen(s,sl)) ;
#endif

	sp = s ;
	sl = slen ;
	while ((tp = strnpbrk(sp,sl," \t\r\n,")) != NULL) {

	    cp = (char *) sp ;
	    cl = tp - sp ;
	    if (cl > 0) {

	        rs = vecstr_addwithin(op,cp,cl) ;
	        if (rs < 0)
	            break ;

	        if (rs > 0)
	            c += 1 ;

	    } /* end if */

	    sl -= ((tp + 1) - sp) ;
	    sp = (tp + 1) ;

	} /* end while */

	if ((rs >= 0) && (sl > 0)) {

	    rs = vecstr_addwithin(op,sp,sl) ;
	    if (rs > 0)
	        c += 1 ;

	} /* end if */

#if	CF_DEBUGS
	debugprintf("vecstr_envadds: ret rs=%d c=%u\n",rs,c) ;
#endif

	return (rs >= 0) ? c : rs ;
}
/* end subroutine (vecstr_envadds) */


/* set a key=value string pair to the environment list */
int vecstr_envset(op,kp,vp,vl)
vecstr		*op ;
const char	*kp ;
const char	*vp ;
int		vl ;
{
	int	rs, rs1 ;
	int	i ;


	if (op == NULL)
	    return SR_FAULT ;

	if (op->va == NULL)
	    return SR_NOTOPEN ;

	if (kp == NULL)
	    return SR_FAULT ;

	rs1 = vecstr_finder(op,kp,vstrkeycmp,NULL) ;
	i = rs1 ;
	if (rs1 >= 0)
	    vecstr_del(op,i) ;

	rs = vecstr_addkeyval(op,kp,-1,vp,vl) ;

	return rs ;
}
/* end subroutine (vecstr_envset) */


/* get a string value by searching on the key */
int vecstr_envget(op,kp,rpp)
vecstr		*op ;
const char	*kp ;
const char	**rpp ;
{
	int	rs = SR_OK ;
	int	vl = 0 ;

	const char	*tp ;
	const char	*rp ;


	if (op == NULL)
	    return SR_FAULT ;

	if (op->va == NULL)
	    return SR_NOTOPEN ;

	if (kp == NULL)
	    return SR_FAULT ;

	if (rpp != NULL)
	    *rpp = NULL ;

	rs = vecstr_finder(op,kp,vstrkeycmp,&rp) ;

	if (rs >= 0) {

	    if ((tp = strchr(rp,'=')) != NULL)
	        vl = strlen(tp + 1) ;

	    if (rpp != NULL) {

	        if (tp != NULL) {
	            *rpp = (tp + 1) ;
	        } else
	            *rpp = (rp + strlen(rp)) ;

	    }
	}

	return (rs >= 0) ? vl : rs ;
}
/* end subroutine (vecstr_envget) */


/* private subroutines */


static int vecstr_addwithin(op,s,slen)
VECSTR		*op ;
const char	s[] ;
int		slen ;
{
	int	rs = SR_OK ;
	int	rs1 ;
	int	kl, vl ;
	int	f_separated = FALSE ;
	int	f_added = FALSE ;

	const char	*kp, *vp ;

	char	*tp ;


	if (s == NULL)
	    return SR_FAULT ;

	if (slen < 0)
	    slen = strlen(s) ;

#if	CF_DEBUGS
	debugprintf("vecstr_addwithin: entered >%t<\n",
	    s,strnlen(s,slen)) ;
#endif

	while ((slen > 0) && CHAR_ISWHITE(*s)) {
	    s += 1 ;
	    slen -= 1 ;
	}

	while ((slen > 0) && CHAR_ISWHITE(s[slen - 1]))
	    slen -= 1 ;

	if (slen > 0) {

	    kp = s ;
	    kl = slen ;
	    vp = NULL ;
	    vl = 0 ;
	    if ((tp = strnchr(s,slen,'=')) != NULL) {

	        vp = tp + 1 ;
	        vl = (kp + kl) - vp ;
	        kl = tp - kp ;

#if	CF_DEBUGS
	        debugprintf("vecstr_addwithin: K=V vl=%d\n",vl) ;
#endif

	        while ((kl > 0) && CHAR_ISWHITE(kp[kl - 1])) {
	            f_separated = TRUE ;
	            kl -= 1 ;
	        }

	        while ((vl > 0) && CHAR_ISWHITE(*vp)) {
	            f_separated = TRUE ;
	            vp += 1 ;
	            vl -= 1 ;
	        }

	        if (kl > 0) {

	            int		f ;

	            char	keybuf[KEYBUFLEN + 1] ;


	            f = (! f_separated) || 
	                (kp[kl] == '\0') || (kp[kl] == '=') ;

	            if (! f) {

	                if (kl <= KEYBUFLEN) {

	                    strwcpy(keybuf,kp,kl) ;
	                    kp = keybuf ;

	                } else
	                    rs = SR_TOOBIG ;

	            }

	            if (rs >= 0) {

	                rs1 = vecstr_finder(op,kp,vstrkeycmp,NULL) ;

	                if (rs1 == SR_NOTFOUND) {

	                    f_added = TRUE ;
	                    if (f_separated) {
	                        rs = vecstr_addkeyval(op,kp,kl,vp,vl) ;
	                    } else
	                        rs = vecstr_add(op,s,slen) ;

	                }

	            } /* end if */

	        } /* end if (non-zero key) */

	    } /* end if (had a value even if NUL) */

	} /* end if (non-zero string) */

#if	CF_DEBUGS
	debugprintf("vecstr_addwithin: ret rs=%d\n",rs) ;
#endif

	return (rs >= 0) ? f_added : rs ;
}
/* end subroutine (vecstr_addwithin) */



