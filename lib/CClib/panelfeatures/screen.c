
/**************************************************************************/
/* PANELFEATURES Package    Release:  1.0    Release Date: 1/15/89        */
/*                          Provider: J. D. Iorio  (speedy!jdi)           */
/**************************************************************************/
/*******************************************************************
* This file contains all of the misc. functions associated with ALMMS
* that support the panelfeatures package but are not directly related
* to the pf objects.
*******************************************************************/
#include <stream.h>
#include <string.h>
#include "screen.h"
#include "giproto.h"
#include "proto.h"
#include "pf.h"
#include <fcntl.h>

#define INTERACTMSG 4,75,52,1
#define ERRORMSG 3,75,56,1
extern int Usermode;
extern int OrigUsermode;

extern proto_stream pout;

extern void set_term_almms();		/* set no ECHO */
extern void reset_term_almms();	 	/* reset to ECHO */

///////////////////////////////////////
int TERMTYPE = ATT630;			/* global terminal type for I/O */
int stdinhold, stdouthold;
///////////////////////////////////////

void begin_PF()
{
	extern int system( char *);
	extern char *getenv(char *);
	void mouse_inactive();

	char *ttytype;
	char *pathname;
	char pfcmdbuf[100];

	OrigUsermode = Usermode;
	if (Usermode == INTERACTIVE)
	{

 	// get the terminal type
	    if( (ttytype=getenv("PFTERM")) == NULL)
	    {
	    	ttytype=getenv("TERM");
	    }
	    if( (pathname=getenv("PFPATH")) == NULL)
	    {
		cout << "Environment Variable : PFPATH not set\n";
		exit(-1);
	    }


	// if 630, spawn the terminal resident graphics driver
	    if (((strcmp(ttytype,"630")) == 0)
	    	|| ((strcmp(ttytype,"630MTG")) == 0)
//ZZZZZZZZ
|| ((strcmp(ttytype,"PDBUG")) == 0)
	    	|| ((strcmp(ttytype,"ATT630")) == 0))
	    {
if ((strcmp(ttytype,"PDBUG")) == 0)
TERMTYPE = PDBUG;
else
		TERMTYPE = ATT630;
		sprintf(pfcmdbuf,"dmdld %s/gialmms", pathname);
		if(system(pfcmdbuf) != 0)
		{
			abort();
		}
	        set_term_almms();

	    }


	// if debug requested, no filter process, print ASCII raw
	    else if ((strcmp(ttytype,"DBUG")) == 0)
		TERMTYPE = DBUG;

	// else assume a curses interface
	    else /* assume curses interface */
	    {
		int pid;
		int pipein;
		int pipeout;
		int status;
		char ain[5];
		char aout[5];
		char p_to_gi[100];
		char p_from_gi[100];
		extern int errno;

		TERMTYPE = CURSES;

		/* create pipe names */
		sprintf(p_to_gi,"%s/P_to_gi",pathname);
		sprintf(p_from_gi,"%s/P_from_gi",pathname);

		
		/* spawn process */
		if ((pid = fork()) == -1)
		{
			cerr << "Fatal Error creating curses filter process ";
			cerr << errno << "\n";
			abort();
		}
		else if (pid == 0)
		{
			// success and this is child process
			/* child process changes to curses filter
			   after connecting pipe ends */

			if((pipein=open(p_to_gi,O_RDONLY|O_NDELAY)) == -1)
			{
			   cerr << "Fatal Error: open PIPE from host proc. ";
			   cerr << errno << "\n";
			   abort();
			}

			if((pipeout=open(p_from_gi,O_WRONLY)) == -1)
			{
			   cerr << "Fatal Error: open PIPE to host proc. ";
			   cerr << errno << "\n";
			   abort();
			}


			sprintf(ain,"%d", pipein);
			sprintf(aout,"%d", pipeout);

			sprintf(pfcmdbuf,"%s/pfcmain",pathname);
			execl( pfcmdbuf, "pfcmain", ain, aout, 0 );
			// if return from execl, then it failed
			cerr << "Fatal Error:  EXECL curses filter process ";
			cerr << errno << "\n";
			exit(2);
		}
		else
		{
			/* success and this is the PF host process */
			/* be a plumber, connect the pipes to cout cin
			   so that communications is transparent */

			if((pipein=open(p_from_gi,O_RDONLY)) == -1)
			{
			   cerr << "Fatal Error: open PIPE from GI proc. ";
			   cerr << errno << "\n";
			   abort();
			}

			if((pipeout=open(p_to_gi,O_WRONLY)) == -1)
			{
			   cerr << "Fatal Error: open PIPE to GI proc. ";
			   cerr << errno << "\n";
			   abort();
			}

			if((stdinhold = dup(0)) <= 0)
			{
				cerr <<
				  "Fatal Error saving stdin ";
				cerr << errno << "\n";
				abort();
			}

			if(close(0) != 0)
			{
			    cerr << "Fatal Error: CLOSE 0 " << errno <<"\n";
			    abort();
			}
			if((status = dup(pipein)) != 0)
			{
				cerr <<
				  "Fatal Error soldering PIPE from filter ";
				cerr << errno << "\n";
				abort();
			}
			if((stdouthold = dup(1)) <= 0)
			{
				cerr <<
				  "Fatal Error saving stdout ";
				cerr << errno << "\n";
				abort();
			}

			if(close(1) != 0)
			{
			    cerr << "Fatal Error: CLOSE 1 " << errno <<"\n";
			    abort();
			}
			if((status = dup(pipeout)) != 1)
			{
				cerr <<
				  "Fatal Error soldering PIPE to filter ";
				cerr << errno << "\n";
				abort();
			}
		}
	    }
	    mouse_inactive();
	
	}

	sleep(1);			/* timing for 630 terminal */
}

void end_PF()
{
	int status;
	if (Usermode == INTERACTIVE)
	{
		pout << form("%c\n", GITERMINATE);
		pout.flush();

		if(TERMTYPE == CURSES)
		{
			// wait for curses process to DIE!!!
			wait(&status);

			if(close(0) != 0)
			{
			    cerr << "Fatal Error: CLOSE 0 end " << errno <<"\n";
			    abort();
			}
			if((status = dup(stdinhold)) != 0)
			{
				cerr <<
				  "Fatal Error restoring stdin ";
				cerr << errno << "\n";
				abort();
			}

			if(close(1) != 0)
			{
			    cerr << "Fatal Error: CLOSE 1 end " << errno <<"\n";
			    abort();
			}
			if((status = dup(stdouthold)) != 1)
			{
				cerr <<
				  "Fatal Error restoring stdout ";
				cerr << errno << "\n";
				abort();
			}
		}
		reset_term_almms();

	}
}
void error_exit(char *s)
{
	if (Usermode == INTERACTIVE)
	{
		if (*s != '\0')
			errormsg(s);
		mouse_active();
		end_PF();
	}
}

void errormsg( char *s)
{
	if (Usermode == INTERACTIVE)
	{
		pout << form("%c%s\n", GIWARN_MESSAGE, s);
		pout.flush();
	}
	else
	{
		cerr << form("PF ERROR: %s\n",s);
		cerr.flush();
	}

}
char askmsg(char *s, char *choice)
{
	char rbuf[5];
	char junk;

	if(Usermode == INTERACTIVE)
	{
		pout << form("%c%s~(%s)\n", GIASK_MESSAGE, s, choice);
		pout.flush();
		cin.get(rbuf,4,'\n');
		cin.get(junk);
		return(*rbuf);
	}
	else
	{
		return(*choice);
	}
}
void infomsg( char *s)
{
	if (Usermode == INTERACTIVE)
	{
		pout << form("%c%s\n", GIINFO_MESSAGE, s);
		pout.flush();
	}

}


void mouse_active()
{
	if (Usermode == INTERACTIVE)
		pout << form("%c\n", GIMOUSE_GO);
		pout.flush();
}

void mouse_inactive()
{
	if (Usermode == INTERACTIVE)
		pout << form("%c\n", GIMOUSE_STOP);
		pout.flush();
}

void interactmsg( char *s, float& x)
{
	errormsg(s);
	x = 1;
}

void loadlogo(char *title, char *stit1, char *stit2, char *date,
		char *logodata)
{
	if (Usermode == INTERACTIVE)
	{
		pout << form("%c", GILOAD_LOGO);
		pout << title << ";" << stit1 << ";";
		pout << stit2 << ";" << date << ";";
		pout << logodata;
		pout << "\n";
		pout.flush();
	}
}

