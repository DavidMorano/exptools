/*ident	"@(#)C++env:incl-master/proto-headers/regexp.h	1.1" */

#ifndef __REGEXP_H
#define __REGEXP_H

/*	@(#)regexp.h 1.7 88/02/07 SMI; from S5R2 1.2	*/

#include <ctype.h>

#define	CBRA	2
#define	CCHR	4
#define	CDOT	8
#define	CCL	12
#define	CDOL	20
#define	CCEOF	22
#define	CKET	24
#define	CBRC	28
#define	CLET	30
#define	CBACK	36

#define	STAR	01
#define RNGE	03

#define	NBRA	9

#define PLACE(c)	ep[c >> 3] |= bittab[c & 07]
#define ISTHERE(c)	(ep[c >> 3] & bittab[c & 07])
#define ecmp(s1, s2, n)	(!strncmp(s1, s2, n))

static char	*braslist[NBRA];
static char	*braelist[NBRA];
static int	ebra;
int	sed, nbra;
char	*loc1, *loc2, *locs;
static int	nodelim;

int	circf;
static int	low;
static int	size;

static char	bittab[] = { 1, 2, 4, 8, 16, 32, 64, 128 };

/*ARGSUSED*/
char *
compile(instring, ep, endbuf, seof)
register char *ep;
char *instring, *endbuf;
{
	INIT	/* Dependent declarations and initializations */
	register c;
	register eof = seof;
	char *lastep;
	int cclcnt;
	char bracket[NBRA], *bracketp;
	int closed;
	int neg;
	int lc;
	int i, cflg;

	if((c = GETC()) == eof || c == '\n') {
		if(c == '\n') {
			UNGETC(c);
			nodelim = 1;
		}
		if(*ep == 0 && !sed)
			ERROR(41);
		RETURN(ep);
	}
	bracketp = bracket;
	circf = closed = nbra = ebra = 0;
	lastep = 0;
	if(c == '^')
		circf++;
	else
		UNGETC(c);
	while(1) {
		if(ep >= endbuf)
			ERROR(50);
		c = GETC();
		if(c == eof) {
			if(bracketp != bracket)
				ERROR(42);
			*ep++ = CCEOF;
			RETURN(ep);
		}
		if(c != '*' && ((c != '\\') || (PEEKC() != '{')))
			lastep = ep;
		switch(c) {

		case '.':
			*ep++ = CDOT;
			continue;

		case '\0':
		case '\n':
			if(!sed) {
				if(bracketp != bracket)
					ERROR(42);
				UNGETC(c);
				*ep++ = CCEOF;
				nodelim = 1;
				RETURN(ep);
			}
			else ERROR(36);
		case '*':
			if(lastep == 0 || *lastep == CBRA || *lastep == CKET
			    || *lastep == CBRC || *lastep == CLET)
				goto defchar;
			*lastep |= STAR;
			continue;

		case '$':
			if(PEEKC() != eof && PEEKC() != '\n' && PEEKC() != '\0')
				goto defchar;
			*ep++ = CDOL;
			continue;

		case '[':
			if(&ep[17] >= endbuf)
				ERROR(50);

			*ep++ = CCL;
			lc = 0;
			for(i = 0; i < 16; i++)
				ep[i] = 0;

			neg = 0;
			if((c = GETC()) == '^') {
				neg = 1;
				c = GETC();
			}

			do {
				if(c == '\0' || c == '\n')
					ERROR(49);
				if(c == '-' && lc != 0) {
					if((c = GETC()) == ']') {
						PLACE('-');
						break;
					}
					if(sed && c == '\\') {
						switch(PEEKC()) {

						case 'n':
							(void) GETC();
							c = '\n';
							break;

						case '\\':
							(void) GETC();
							c = '\\';
							break;
						}
					}
					while(lc < c) {
						PLACE(lc);
						lc++;
					}
				} else if(sed && c == '\\') {
					switch(PEEKC()) {

					case 'n':
						(void) GETC();
						c = '\n';
						break;

					case '\\':
						(void) GETC();
						c = '\\';
						break;
					}
				}
				lc = c;
				PLACE(c);
			} while((c = GETC()) != ']');
			if(neg) {
				for(cclcnt = 0; cclcnt < 16; cclcnt++)
					ep[cclcnt] ^= -1;
				ep[0] &= 0376;
			}

			ep += 16;

			continue;

		case '\\':
			switch(c = GETC()) {

			case '<':
				*ep++ = CBRC;
				continue;

			case '>':
				*ep++ = CLET;
				continue;

			case '(':
				if(nbra >= NBRA)
					ERROR(43);
				*bracketp++ = nbra;
				*ep++ = CBRA;
				*ep++ = nbra++;
				continue;

			case ')':
				if(bracketp <= bracket || ++ebra != nbra)
					ERROR(42);
				*ep++ = CKET;
				*ep++ = *--bracketp;
				closed++;
				continue;

			case '{':
				if(lastep == (char *) 0)
					goto defchar;
				*lastep |= RNGE;
				cflg = 0;
			nlim:
				c = GETC();
				i = 0;
				do {
					if('0' <= c && c <= '9')
						i = 10 * i + c - '0';
					else
						ERROR(16);
				} while(((c = GETC()) != '\\') && (c != ','));
				if(i > 255)
					ERROR(11);
				*ep++ = i;
				if(c == ',') {
					if(cflg++)
						ERROR(44);
					if((c = GETC()) == '\\')
						*ep++ = 255;
					else {
						UNGETC(c);
						goto nlim;
						/* get 2'nd number */
					}
				}
				if(GETC() != '}')
					ERROR(45);
				if(!cflg)	/* one number */
					*ep++ = i;
				else if((ep[-1] & 0377) < (ep[-2] & 0377))
					ERROR(46);
				continue;

			case '\n':
				ERROR(36);

			case 'n':
				if(sed)
					c = '\n';
				goto defchar;

			default:
				if(c >= '1' && c <= '9') {
					if((c -= '1') >= closed)
						ERROR(25);
					*ep++ = CBACK;
					*ep++ = c;
					continue;
				}
			}
	/* Drop through to default to use \ to turn off special chars */

		defchar:
		default:
			lastep = ep;
			*ep++ = CCHR;
			*ep++ = c;
		}
	}
	/*NOTREACHED*/
}

step(p1, p2)
register char *p1, *p2;
{
	register c;

	/*
	 * Save the beginning of the string in "loc1", so that "advance"
	 * knows when it's looking at the first character of the string;
	 * it needs this to implement \<.
	 */
	loc1 = p1;
	if(circf)
		return(advance(p1, p2));
	/* fast check for first character */
	if(*p2 == CCHR) {
		c = p2[1];
		do {
			if(*p1 != c)
				continue;
			if(advance(p1, p2)) {
				loc1 = p1;
				return(1);
			}
		} while(*p1++);
		return(0);
	}
		/* regular algorithm */
	do {
		if(advance(p1, p2)) {
			loc1 = p1;
			return(1);
		}
	} while(*p1++);
	return(0);
}

advance(lp, ep)
register char *lp, *ep;
{
	register char *curlp;
	int c;
	char *bbeg;
	int ct;

	while(1) {
		switch(*ep++) {

		case CCHR:
			if(*ep++ == *lp++)
				continue;
			return(0);
	
		case CDOT:
			if(*lp++)
				continue;
			return(0);
	
		case CDOL:
			if(*lp == 0)
				continue;
			return(0);
	
		case CCEOF:
			loc2 = lp;
			return(1);
	
		case CCL:
			c = *lp++ & 0177;
			if(ISTHERE(c)) {
				ep += 16;
				continue;
			}
			return(0);
		case CBRA:
			braslist[*ep++] = lp;
			continue;
	
		case CKET:
			braelist[*ep++] = lp;
			continue;
	
		case CCHR | RNGE:
			c = *ep++;
			getrnge(ep);
			while(low--)
				if(*lp++ != c)
					return(0);
			curlp = lp;
			while(size--) 
				if(*lp++ != c)
					break;
			if(size < 0)
				lp++;
			ep += 2;
			goto star;
	
		case CDOT | RNGE:
			getrnge(ep);
			while(low--)
				if(*lp++ == '\0')
					return(0);
			curlp = lp;
			while(size--)
				if(*lp++ == '\0')
					break;
			if(size < 0)
				lp++;
			ep += 2;
			goto star;
	
		case CCL | RNGE:
			getrnge(ep + 16);
			while(low--) {
				c = *lp++ & 0177;
				if(!ISTHERE(c))
					return(0);
			}
			curlp = lp;
			while(size--) {
				c = *lp++ & 0177;
				if(!ISTHERE(c))
					break;
			}
			if(size < 0)
				lp++;
			ep += 18;		/* 16 + 2 */
			goto star;
	
		case CBACK:
			bbeg = braslist[*ep];
			ct = braelist[*ep++] - bbeg;
	
			if(ecmp(bbeg, lp, ct)) {
				lp += ct;
				continue;
			}
			return(0);
	
		case CBACK | STAR:
			bbeg = braslist[*ep];
			ct = braelist[*ep++] - bbeg;
			curlp = lp;
			while(ecmp(bbeg, lp, ct))
				lp += ct;
	
			while(lp >= curlp) {
				if(advance(lp, ep))	return(1);
				lp -= ct;
			}
			return(0);
	
	
		case CDOT | STAR:
			curlp = lp;
			while(*lp++);
			goto star;
	
		case CCHR | STAR:
			curlp = lp;
			while(*lp++ == *ep);
			ep++;
			goto star;
	
		case CCL | STAR:
			curlp = lp;
			do {
				c = *lp++ & 0177;
			} while(ISTHERE(c));
			ep += 16;
			goto star;
	
		star:
			if(--lp == curlp) {
				continue;
			}

			if(*ep == CCHR) {
				c = ep[1];
				do {
					if(*lp != c)
						continue;
					if(advance(lp, ep))
						return(1);
				} while(lp-- > curlp);
				return(0);
			}

			if(*ep == CBACK) {
				c = *(braslist[ep[1]]);
				do {
					if(*lp != c)
						continue;
					if(advance(lp, ep))
						return(1);
				} while(lp-- > curlp);
				return(0);
			}

			do {
				if(lp == locs)
					break;
				if(advance(lp, ep))
					return(1);
			} while(lp-- > curlp);
			return(0);

#define	uletter(c)	(isalpha(c) || (c) == '_')
		case CBRC:
			if(lp == loc1)
				continue;
			if(uletter(*lp) || isdigit(*lp))
				if(!uletter(lp[-1]) && !isdigit(lp[-1]))
					continue;
			return(0);

		case CLET:
			if(!uletter(*lp) && !isdigit(*lp))
				continue;
			return(0);
#undef uletter
		}
	}
	/*NOTREACHED*/
}

static
getrnge(str)
register char *str;
{
	register int sizecode;

	low = *str++ & 0377;
	sizecode = *str & 0377;
	if (sizecode == 255)
		size = 20000;
	else
		size = sizecode - low;
}
 


#endif

