
/**************************************************************************/
/* PANELFEATURES Package    Release:  1.0    Release Date: 1/15/89        */
/*                          Provider: J. D. Iorio  (speedy!jdi)           */
/**************************************************************************/
////////////////////////////////////////////////////////////////////////////
// pfcmain.c
//
//	this is the main program file for the Panelfeatures "CURSES"
// 	type interface filter process.  Invocation is done by the
//	begin_PF() function of PANELFEATURES host process (screen.c)
//	with pipes established in the environment that connect the
//	host cout to resource {argv[1]} and cin to resource {argv[2]}
//
//	this process inserts itself as a filter between those pipes 
//	and the terminal cout/cin connections and changes protocol
//	requests to curses actions
//
//	History:
//		created		6/30/88		J. D. Iorio
//
////////////////////////////////////////////////////////////////////////////////
//	Copyright  ATT 1988
///////////////////////////////////////////////////////////////////////////////

#include <stream.h>
#include <curses.h>

#include "pfc.h"
#include "pfcdef.h"
#include "pfcfunc.h"
#include "pfcglobdef.h"


// extern void clearnode(struct node *);

main (int argc, char *argv[])
{

	struct node *root;

	int  k, h;
	
////////////////////////////////////////////////////////////////////
// initialization sequence
////////////////////////////////////////////////////////////////////
	

	// establish the pipe fittings
	if (argc != 3)
	{
		cerr << "PFCURSES: arg count " << argc <<" is not 3\n";
		exit(101);
	}


	pfsetup_pipe(atoi(argv[1]), atoi(argv[2]));

	hostread = new istream(atoi(argv[1]));
	hostwrite = new ostream(atoi(argv[2]));

	// setup curses window
	initscr();

	pfsetup_term();

	clear();


	// is screen suitable for this program

	if ((LINES < 24) || (COLS < 80))
	{
		cerr << "PFCURSES: Minimum screen supported is 80x24\n";
		endwin();
		exit(100);
	}
	
	pfscr_init_com();
	pfscr_logo_draw();

	keyconfig();

// inform("a sample help screen for clusters");
// keyhelp(PANEL);


////////////////////////////////////////////////////////////////////
// main execution loop
////////////////////////////////////////////////////////////////////
	while(1)
	{
		if((k = pfkeychar()) != NULL)
		{
			if((k&0x7f)=='Q')
				pfc_exit(root);

			keycmd(root,k);
		}
		if((h = pfhostchar()) != NULL)
		{

			hostcmd(&root,(char)(h & 0x7f));

		}
	}
}







////////////////////////////////////////////////////////////////////
// cleanup sequence
////////////////////////////////////////////////////////////////////

void pfc_exit(struct node *root)
{
	clearnode(root);
	clear();
/*
	wclear(actionbox);
	wclear(dividebox);
	wclear(namebox);
	wclear(logobox);
	wclear(msgbox);
	wrefresh(actionbox);
	wrefresh(dividebox);
	wrefresh(namebox);
	wrefresh(logobox);
	wrefresh(msgbox);
*/
	touchwin(stdscr);
	refresh();
	endwin();
	
	exit(0);
}
