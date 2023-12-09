
/**************************************************************************/
/* PANELFEATURES Package    Release:  1.0    Release Date: 1/15/89        */
/*                          Provider: J. D. Iorio  (speedy!jdi)           */
/**************************************************************************/
/*
*	gishorts.c -
*
* A collection of Misc support routines for the 630 terminal driver for use
* in conjunction with the panelfeature package in ALMMS:
*
*	void hostcmd(char) main command interpreter
*
*	node *nodeload() will parse input text from the host
*		 to myallocate and build a panelfeature tree
*
*	void clearnode(*root) will myfree a panelfeature tree
*
*
*/

#include <dmd.h>
#include "gi.h"
#include "giwindow.h"

/********************************************************************/


extern Bitmap *JEDI;
extern char *logo1, *logo2, *logo3, *logodate;

void warn();
extern char *alloc();

extern void screen_logo_draw();

/*************************************************************************/


char *myalloc(n)
int n;
{
	char *ptr;
	int i;

	ptr = (char *)alloc(n+5);
	*ptr = (char)0;
	ptr++;
	for (i=0; i<4; i++)
	{
		if(((long)ptr % 4) == 0)
			break;
		*ptr = (char)i;
		ptr++;
	}

	return(ptr);
}

void myfree(ptr)
char *ptr;
{
	int i;

	ptr--;
	for(i=(int)*ptr; i>0; i--)
		ptr--;
	free(ptr);
}

int xtoi(c)
char c;
{
	switch(c)
	{
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		return((int)(c-'0'));
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
		return((int)(c-'A')+10);
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
		return((int)(c-'a')+10);
	default:
		return(0);
	}
}

void logo(cp)
char *cp;
{

	char *to, *from;
	int i;

	from = cp;

	for (i=0, to=logo1; *from != ';'; from++)
	{
		if(i<6)
		{
			*to = *from;
			to++;
			i++;
		}	
	}
	*to = '\0';
	from++;
	
	for (i=0, to=logo2; *from != ';'; from++)
	{
		if(i<10)
		{
			*to = *from;
			to++;
			i++;
		}	
	}
	*to = '\0';
	from++;
	
	for (i=0, to=logo3; *from != ';'; from++)
	{
		if(i<10)
		{
			*to = *from;
			to++;
			i++;
		}	
	}
	*to = '\0';
	from++;

	for (i=0, to=logodate; *from != ';'; from++)
	{
		if(i<4)
		{
			*to = *from;
			to++;
			i++;
		}	
	}
	*to = '\0';
	from++;

	to = (char *)(JEDI->base);
	
	for (i=0; i<384; i++) 
	{
		*to = xtoi(*from) << 4;
		from++;
		*to += xtoi(*from);
		from++;
		to++;
	}


	screen_logo_draw();
}

void break_line(msg)
char *msg;
{

#define WINLEN 60
#define WINLINE 6

	char *cp;
	char *bp, *ep, *next, *temp, hold;
	int i, j;
	Rectangle r;

	r = raddp(SCR_MSGBOX,Pt(0,0));
	r.origin.x += 4;
	r.origin.y += 4;
	

	if (strcmp(msg, ERASE_MESSAGE) == 0)
		return;

    /* remove the parity bit */
	for (cp=msg; *cp != '\0'; cp++)
	{
		if(*cp > (char)0x80)
		{
			*cp &= (char)0x7f;
		}
		if((*cp == '\n') || (*cp == '\r'))
			*cp = '\0';
	}

	if (strcmp(msg, ERASE_MESSAGE) == 0)
		return;


    /* place each line of text */

	ep=msg;
	j = 0;

	while (ep <= cp)
	{
	    bp=ep;

	    /* get a line segment */
	    for(i=0, ep++; (ep<=cp)&&(i<WINLEN); i++, ep++)
	    {
		if(*ep == '~')  /* force newline */
			break;
	    }
	    temp = ep;

	    /* backup until we hit a logical break point */
	    while((*ep != '~') && (*ep != ' ') && (*ep != ';') &&
		(*ep != ',') && (*ep != '-') && (*ep != '\0'))
	    {
		ep--;
		if(ep == bp)	/* if we dont find a good break point */
		{
			ep = temp;
			break;
		}
	    }
	    next = ep + 1;

	    /* print the line segment */
	    if((*ep != '~') && (*ep != ' ') && (*ep != '\0'))
	    {
		ep++;
	    }

	    hold = *ep;
	    *ep = '\0';
	    
	    string(&mediumfont, bp, &display, r.origin, F_STORE);

	    r.origin.y += 18;
	    *ep = hold;
	    ep = next;

	    j++;
	    if(j == WINLINE)	/* limit line count */
		break;
	}
}

void warn(msg)
char *msg;
{
	texture(&display,inset(SCR_MSGBOX,3),&T_white,F_STORE);
	
	break_line(msg);
/*
	sleep(240);
*/
	ringbell();
	bttns(1);
	bttns(0);
	texture(&display,inset(SCR_MSGBOX,3),&T_white,F_STORE);
	
}

void sendhost(msg)
char *msg;
{
	char *cp;
	
	for(cp=msg; *cp!='\0'; cp++)
		sendchar(*cp);

	sendchar('\n');
}

void askmsg(msg)
char *msg;
{
	char *cp, *chp;
	char choices[100];
	int found, keyin;

	texture(&display,inset(SCR_MSGBOX,3),&T_white,F_STORE);
	
	break_line(msg);

	/* parse out the choices */
	for(cp=msg; *cp != '\0'; cp++);
	for(cp-=2, chp=choices; *cp != '('; cp--)
	{
		if (*cp != '|')
		{
			*chp++ = (char)toupper((int)*cp);
			*chp++ = (char)tolower((int)*cp);
		}
	}
	*chp = '\0';

	for(found=0; found==0; )
	{
		ringbell();
		/* get a response from the keyboard */
		while((keyin=kbdchar()) == -1)
			sleep(2);

		for(chp=choices; (found==0)&&(*chp != '\0'); chp++)
		{
			if(*chp == (char)(keyin&0x7f))
			{
				found = 1;
				choices[0] = (char)tolower(keyin);
				choices[1] = '\0';
				sendhost(choices);
			}
		}
	}
	texture(&display,inset(SCR_MSGBOX,3),&T_white,F_STORE);
	
}

void inform(msg)
char *msg;
{
	texture(&display,inset(SCR_MSGBOX,3),&T_white,F_STORE);

	break_line(msg);
}


/*************************************************************************/
