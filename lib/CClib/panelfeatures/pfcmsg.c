
/**************************************************************************/
/* PANELFEATURES Package    Release:  1.0    Release Date: 1/15/89        */
/*                          Provider: J. D. Iorio  (speedy!jdi)           */
/**************************************************************************/


/*****************************************************************************
* PFCMSG.C
*
*	Error and information message utilities for the PANELFEATURES
*	curses type interface
*
*	void warn(char *msg)	displays a message, waits for user response
*
*	void info(char *msg)	displays a message, doesn't wait
*
*	Copyright AT&T 1988
*
*	History:
*		J. Iorio	7/3/88	created
*
******************************************************************************/

#include <stream.h>
#include <string.h>
#include <curses.h>
#include "pfc.h"
#include "pfcdef.h"
#include "pfcglobals.h"
#include "pfcfunc.h"


void break_line(WINDOW *w, char *msg)
{


	char *cp;
	char *bp, *ep, *next, *temp, hold;
	int i, j;
	


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
	    for(i=0, ep++; (ep<=cp)&&(i<MSGBOXW); i++, ep++)
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
	    
	    wmove(w,j,0);
	    wprintw(w, "%s", bp);

	    *ep = hold;
	    ep = next;

	    j++;
	    if(j == MSGBOXH)	/* limit line count */
		break;
	}
}

void warn(char *msg)
{

	werase(msgbox);
	wattron(msgbox,A_REVERSE);

	break_line(msgbox,msg);
	wrefresh(msgbox);
	beep();
	while(pfkeychar() != (char)KEY_CONT);
	wattroff(msgbox,A_REVERSE);
	werase(msgbox);

	wmove(actionbox,currentnode->curs_y,
			currentnode->curs_x);
	wnoutrefresh(msgbox);
	wnoutrefresh(actionbox);
	doupdate();

}


void inform(char *msg)
{

	werase(msgbox);
	break_line(msgbox,msg);
	wmove(actionbox,currentnode->curs_y,
			currentnode->curs_x);
	wnoutrefresh(msgbox);
	wnoutrefresh(actionbox);
	doupdate();

}
