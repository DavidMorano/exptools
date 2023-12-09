
/**************************************************************************/
/* PANELFEATURES Package    Release:  1.0    Release Date: 1/15/89        */
/*                          Provider: J. D. Iorio  (speedy!jdi)           */
/**************************************************************************/
/**************************************************************************
//  LOWIO.c
//
//	Low level I/O stuff for almms coded in C for now
//		(not C++)
//	to manipulate the UNIX I/O interface.
//	May need modifications for pipes to X-windows...
//
//	copyright  1988 AT&T
//
//	history:
//	J. D. Iorio	4/15/88	created C version
**************************************************************************/
#include <stdio.h>
#include <fcntl.h>
#include <termio.h>
#include "giproto.h"

extern int TERMTYPE;		/* type of terminal for graphics connection */

int detect_brk_cmd();		/* interactive **BREAK** command ? */
void set_term_almms();		/* set no ECHO */
void reset_term_almms();	/* reset to ECHO */

extern void mouse_active();

void set_term_almms()
{
	struct termio mtty;

	/* disable echo */
	setbuf(stdout, NULL);
	ioctl(fileno(stdin), TCGETA, &mtty);
	mtty.c_lflag &= ~ECHO;
	ioctl(fileno(stdin), TCSETAW, &mtty);
}

void reset_term_almms()
{
	struct termio mtty;

	/* disable echo */
	setbuf(stdout, NULL);
	ioctl(fileno(stdin), TCGETA, &mtty);
	mtty.c_lflag |= ECHO;
	ioctl(fileno(stdin), TCSETAW, &mtty);
}

int detect_brk_cmd()
{
#define BRKLEN 12
	int i;
	int rcode;
	char str[BRKLEN];
	struct termio tty;
	struct termio savetty;


 /* setup no delay on input... check for stdin or pipe to graphics */
	if(TERMTYPE == ATT630)
	{
		ioctl(fileno(stdin), TCGETA, &tty);
		ioctl(fileno(stdin), TCGETA, &savetty);

		tty.c_lflag &= ~(ISIG | ICANON | ECHO);
		tty.c_cc[VMIN] = 0;
		tty.c_cc[VTIME] = 0;

		ioctl(fileno(stdin), TCSETAW, &tty);
	}
	else
	{
		i = fcntl(fileno(stdin),F_GETFL,0);
		i |= O_NDELAY;
		fcntl(fileno(stdin), F_SETFL, i);
	}


  /* parse a message if there */
	rcode = 0;

	for(i=0; i<BRKLEN; i++)
		str[i] = '\0';

	if(read(fileno(stdin), str, 10) != 0)
	{
		for(i=0; i<BRKLEN; i++)
		{
			if(str[i] == '\n')
			{
				str[i] = '\0';
				break;
			}
		}
		if(strcmp(str,"**BREAK**") == 0)
		{
			rcode = 1;	
			mouse_active();
		}
	}


 /* restore input mode ...  check for stdin or pipe to graphics */
	if(TERMTYPE == ATT630)
	{
		ioctl(fileno(stdin), TCSETAW, &savetty);
	}
	else
	{
		i = fcntl(fileno(stdin),F_GETFL,0);
		i &= ~O_NDELAY;
		fcntl(fileno(stdin), F_SETFL, i);
	}

	return(rcode);
}
