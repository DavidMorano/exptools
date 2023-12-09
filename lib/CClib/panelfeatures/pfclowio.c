
/**************************************************************************/
/* PANELFEATURES Package    Release:  1.0    Release Date: 1/15/89        */
/*                          Provider: J. D. Iorio  (speedy!jdi)           */
/**************************************************************************/
/**************************************************************************
//  PFCLOWIO.c
//
//	Low level I/O stuff for "panelfeatures curses" coded in C for now
//		(not C++)
//	to manipulate the UNIX I/O and pipe interfaces.
//
//	copyright  1988 AT&T
//
//	history:
//	J. D. Iorio	6/30/88	created C version 
**************************************************************************/
#include <stdio.h>
#include <fcntl.h>
#include <termio.h>


/*////////////////////////////////////////////////////////////////*/
	struct termio pfsavetty;       /* global hook for restoral */

	int pfhost_read;			/* host connections */
	int pfhost_write;
/*////////////////////////////////////////////////////////////////*/

void pfsetup_term()
{
	struct termio mtty;

	/* disable echo */
	setbuf(stdout, NULL);
	ioctl(fileno(stdin), TCGETA, &mtty);
	ioctl(fileno(stdin), TCGETA, &pfsavetty);
	mtty.c_lflag &= ~(ISIG | ICANON | ECHO);
	mtty.c_cc[VMIN] = 0;
	mtty.c_cc[VTIME] = 0;
	ioctl(fileno(stdin), TCSETAW, &mtty);
}

void pfreset_term()
{

	/* restore original configuration */
	ioctl(fileno(stdin), TCSETAW, &pfsavetty);
}



void pfsetup_pipe(in,out)
{
	int flags;

	pfhost_read = in;
	pfhost_write = out;


	flags = fcntl(in,F_GETFL, 0 );
	flags |= O_NDELAY;
	fcntl(in, F_SETFL, flags);

}

int pfkeychar()
{
	char c;
	if(read(fileno(stdin), &c, 1) != 0)
		return((int)c&0x7f);
	else
		return(NULL);
}
int pfhostchar()
{
	extern int errno;
	char c;
	int i;
	if((i=read(pfhost_read, &c, 1)) == 1)
	{
		return((c&0x7f));
	}
	else if (i== -1)
	{
		/*
		fprintf(stderr,"readhost got %d, errno is %d\n",i,errno);
		*/
		return(NULL);
	}
	else
		return(NULL);
}

