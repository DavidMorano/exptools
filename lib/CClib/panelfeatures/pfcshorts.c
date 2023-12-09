
/**************************************************************************/
/* PANELFEATURES Package    Release:  1.0    Release Date: 1/15/89        */
/*                          Provider: J. D. Iorio  (speedy!jdi)           */
/**************************************************************************/
/*
*	pfcshorts.c -
*
* A collection of Misc support routines for the curses terminal driver for use
* in conjunction with the panelfeature package in ALMMS:
*
*	COPYRIGHT AT&T 1988
*
*	History:
*		J. D. Iorio	7/5/88	created
*
*/

#include <stream.h>
#include <curses.h>
#include "pfcfunc.h"
#include "pfcglobals.h"

/*************************************************************************/


int xtoi( char c)
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

void logo(char *cp)
{

	char *to, *from;
	int i;

	from = cp;

	for (i=0, to=Logo1; *from != ';'; from++)
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
	
	for (i=0, to=Logo2; *from != ';'; from++)
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
	
	for (; *from != ';'; from++); // skip logo3 for curses
	from++;

	for (i=0, to=Logodate; *from != ';'; from++)
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

	// ignore bitblit for logo icon for the curses version

	pfscr_logo_draw();
}

/*************************************************************************/
