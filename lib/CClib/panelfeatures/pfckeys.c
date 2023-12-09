
/**************************************************************************/
/* PANELFEATURES Package    Release:  1.0    Release Date: 1/15/89        */
/*                          Provider: J. D. Iorio  (speedy!jdi)           */
/**************************************************************************/

/*
*	pfckeys.c -
*
*	A collection of support routines to allow for
*	reconfiguration of the keyboard command keys and
*	on-line help facilities for PANELFEATURES/curses.
*
*	COPYRIGHT AT&T 1988
*
*	History:
*		J. D. Iorio 	7/12/88		created.
*
*
*	void keyconfig(); - reads ~HOME/.pfckeys file for key definitions
*
*	void keyhelp(char nodetype)- supplies help for the selected node
*/

#include <stream.h>
#include <string.h>
#include <curses.h>
#include "pfc.h"
#include "pfcdef.h"
#include "pfcfunc.h"
#include "pfcglobals.h"

/////////////////////////////////////
void showhelp(WINDOW *w, int flag);
/////////////////////////////////////

////////////////////////////////////////////////////////////////////
// void knob_message(node *n)
//
// this function sends a setup message to the host process with the
// current settings of the specified node.  The host process will
// pass the input string directly to the set_up() function
////////////////////////////////////////////////////////////////////
void knob_message(node *n)
{
	char *cp, *hp;
	int j,k;
	struct node *m;

	/* get the closest panel above */
	for (m=n->parent; m->type != PANEL; m=m->parent);

	if (m->parent != NULL)
	{
		sprintf(lbuf,"%s; ",m->name);
		for(cp=lbuf; *cp != '\0'; cp++);
	}
	else
		cp = lbuf;

	/* add the knob command */
	sprintf(cp,"%s = ",n->name);
	for(j=0; j<n->numvalues; j++)
	{
		hp = cp;
		for(cp=hp; *cp != '\0'; cp++);

		if(n->type == ENUM)
		{
			k=(int)n->value[j];
			sprintf(cp," %s\\\n",n->labels[k]);
		}
		else if (n->type == ASCKNOB)
		{
			sprintf(cp," %s\\\n",n->labels[2]);
		}
		else
		{
			sprintf(cp," %f\\\n",n->value[j]);
		}
	}

	for(cp=hp; *cp != '\0'; cp++);
	*cp = ';';
	cp++;
	*cp = '\0';

	sendhost(lbuf);

	if(n->type != ASCKNOB)
		n->attribute |= A_JUSTSET;
}

/////////////////////////////////////////////////////////////////////////
// float get_key_num()
//
//  this function reads the keyboard for a number from the user
//
/////////////////////////////////////////////////////////////////////////
float get_key_num()
{
	float f;
	int j,k,tx,ty;
	char *cp;

	for(j=0,cp=lbuf; j<MYBUFSIZE; j++)
	{
		while((k = pfkeychar()) == NULL);
		if((k == '\n') || (k == '\r'))
		{
			*cp = '\0';
			break;
		}
		else if (k == 0x08)
		{
			if(cp == lbuf)
				continue;

			cp--;
			getyx(actionbox,ty,tx);
			wmove(actionbox,ty,tx-1);
			waddch(actionbox,'_');
			wmove(actionbox,ty,tx-1);
			wrefresh(actionbox);
			
		}
		else
		{
			*cp = (char)k;
			waddch(actionbox,*cp);
			wrefresh(actionbox);
			cp++;
		}
		
	}

	sscanf(lbuf,"%f",&f);
	return(f);
}

void keycmd(struct node *root, int k)
{

	int i, j, ix, iy;
	char *cp;
	float f;


    // general keys processing
    if((int)k== KEY_HELP)
    {
	keyhelp(currentnode->type);
	return;
    }
    else if((int)k== KEY_GO)
    {
	(*hostwrite) << "**GO**\n";
	(*hostwrite).flush();
	return;
    }
    else if((int)k== KEY_EXIT)
    {
	(*hostwrite) << "**STOP**\n";
	(*hostwrite).flush();
	return;
    }
    else if((int)k== KEY_BRK)
    {
	(*hostwrite) << "**BREAK**\n";
	(*hostwrite).flush();
	return;
    }
    else if((int)k== KEY_DOC)
    {
	(*hostwrite) << "**DOC**\n";
	(*hostwrite).flush();
	return;
    }
    else
    {

	switch(currentnode->type)
	{
	case PANEL:
	case CLUSTER:

		/* determine the current item */
		i = currentnode->current_item;

    		if((int)k== KEY_OPEN) 
		{
			currentnode = currentnode->child[i];
			if(currentnode->type == PANEL)
				currentnode = currentnode->child[0];
			pfscr_node_draw();
		}
    		else if((int)k== KEY_CLOSE)
		{
			if(currentnode->parent == NULL)
			{
			    	warn("At top level already");
			}
			else
			{
				currentnode = currentnode->parent;
			}
		
			if(currentnode->type == PANEL)
			{
				if(currentnode->parent == NULL)
				{
	    				warn("At top level already");
					currentnode = currentnode->child[0];
				}
				else
	    				currentnode = currentnode->parent;
			}
			pfscr_node_draw();
		}
    		else if((int)k== KEY_NEXT)
		{
			for(j=0; j<currentnode->numchildren; j++)
			{
				i++;
				if(i== currentnode->numchildren)
					i=0;
				if(currentnode->child[i]->attribute != A_GREY)
				{
				    ix = currentnode->child[i]->orig_x;
				    iy = currentnode->child[i]->orig_y;
				    wmove(actionbox,iy,ix);
				    currentnode->curs_x = ix;
				    currentnode->curs_y = iy;
				    currentnode->current_item = i;
				    wrefresh(actionbox);
				    break;
				}
			}
		}
    		else if((int)k== KEY_PREV)
		{
			for(j=0; j<currentnode->numchildren; j++)
			{
				i--;
				if(i<0)
					i=currentnode->numchildren-1;
				if(currentnode->child[i]->attribute != A_GREY)
				{
				    ix = currentnode->child[i]->orig_x;
				    iy = currentnode->child[i]->orig_y;
				    wmove(actionbox,iy,ix);
				    currentnode->curs_x = ix;
				    currentnode->curs_y = iy;
				    currentnode->current_item = i;
				    wrefresh(actionbox);
				    break;
				}
			}
		}
		else
		{
			warn("invalid key pressed");
			return;
		}

		break;
		
	case FWINT:
	case FWFLT:
	case VWINT:
	case VWFLT:
    		if((int)k== KEY_OPEN) 
		{
		    // prompt for input
			getyx(actionbox,iy,ix);
			i = (int)currentnode->current_item;
			if( i < 0 )
			{
				waddstr(actionbox,"__");
			}
			else
			{
				waddstr(actionbox,"____________");
			}
			wmove(actionbox,iy,ix);
			wrefresh(actionbox);

		    // read the response
			f = get_key_num();

			if(i < 0)
			{
				j=(int)f;
				if((j <= 0) || (j > currentnode->maxnumvalues))
				{
				    warn("bad range - using previous value");
				}
				else
				{
				    currentnode->numvalues = j;
				}
			}
			else
			{
				if((f<currentnode->min) || (f>currentnode->max))
				{
				    warn("bad range - using previous value");
				}
				else
				{
				    currentnode->value[i] = f;
				}
			}
			
		}
    		else if((int)k== KEY_CLOSE)
		{
			// send the update message and close the node
			knob_message(currentnode);
			currentnode = currentnode->parent;
		}
    		else if((int)k== KEY_NEXT)
		{
		     // get the next answer
			i = (int)currentnode->current_item;
			i++;
			if(i >= currentnode->numvalues)
			{
			    if((currentnode->type == VWINT) ||
			       (currentnode->type == VWFLT))
				i= -1;
			    else
				i=0;
			}
			currentnode->current_item = i;

		}
    		else if((int)k== KEY_PREV)
		{
		     // get the previous answer
			i = (int)currentnode->current_item;
			i--;
			if((i < 0) && ((currentnode->type == FWINT)
					|| (currentnode->type == FWFLT)))
				i= currentnode->numvalues-1;
			if(i < -1)
				i= currentnode->numvalues-1;
			currentnode->current_item = i;
		}
		else
		{
			warn("invalid key pressed");
			return;
		}
		pfscr_node_draw();
		break;
	case ENUM:
    		if((int)k== KEY_CLOSE)
		{
			// send the update message and close the node
			knob_message(currentnode);
			currentnode = currentnode->parent;
		}
    		else if((int)k== KEY_NEXT)
		{
		     // get the next answer
			i = (int)currentnode->value[0];
			i++;
			if(i >= currentnode->numdim)
				i=0;
			currentnode->value[0] = i;

		}
    		else if((int)k== KEY_PREV)
		{
		     // get the previous answer
			i = (int)currentnode->value[0];
			i--;
			if(i < 0)
				i=currentnode->numdim-1;
			currentnode->value[0] = i;
		}
		else
		{
			warn("invalid key pressed");
			return;
		}
		pfscr_node_draw();
		break;
	case DISPLAY:
    		if((int)k== KEY_OPEN) 
		{
		}
    		else if((int)k== KEY_CLOSE)
		{
			// close the node
			currentnode = currentnode->parent;
		}
    		else if((int)k== KEY_NEXT)
		{
			// scroll the display forward in time
			i = currentnode->numvalues - currentnode->current_item;
			if(currentnode->numvalues < 10)
				currentnode->current_item = 0;
			else if((i-10) < 10)
				currentnode->current_item =
				 currentnode->numvalues - 10;
			else
				currentnode->current_item += 10;
		}
    		else if((int)k== KEY_PREV)
		{
			// scroll the display backward in time
			if(currentnode->current_item > 10)
				currentnode->current_item -= 10;
			else
				currentnode->current_item = 0;
		}
		else
		{
			warn("invalid key pressed");
			return;
		}
		pfscr_node_draw();
		break;
	case ASCKNOB:
    		if((int)k== KEY_OPEN) 
		{
			iy = 4;
			ix = 2;
			wmove(actionbox,iy,ix);

			for(j=1; j<currentnode->maxnumvalues; j++)
				waddch(actionbox,'_');
				
			wmove(actionbox,iy,ix);
			wrefresh(actionbox);

			for(j=1,cp=currentnode->labels[2];
				 j<currentnode->maxnumvalues; j++)
			{
				while((k = pfkeychar()) == NULL);
				if((k == '\n') || (k == '\r'))
				{
					*cp = '\0';
					currentnode->curs_x = 2;
					currentnode->curs_y = 4;
					break;
				}
				else if (k == 0x08)
				{
					if(cp == currentnode->labels[2])
						continue;

					cp--;
					getyx(actionbox,iy,ix);
					wmove(actionbox,iy,ix-1);
					waddch(actionbox,'_');
					wmove(actionbox,iy,ix-1);
					wrefresh(actionbox);
				}
				else
				{
					*cp = (char)k;
					waddch(actionbox,*cp);
					wrefresh(actionbox);
					cp++;
				}
		
			}
			*cp = '\0';

		}
    		else if((int)k== KEY_CLOSE)
		{
			// send the update message and close the node
			knob_message(currentnode);
			currentnode = currentnode->parent;
		}
    		else if((int)k== KEY_NEXT)
		{
		}
    		else if((int)k== KEY_PREV)
		{
		}
		else
		{
			warn("invalid key pressed");
			return;
		}
		pfscr_node_draw();
		break;
	case ASCDISP:

//ZZZZZZZZZZZZZZZ
    		if((int)k== KEY_OPEN) 
		{
		}
    		else if((int)k== KEY_CLOSE)
		{
			currentnode = currentnode->parent;
		}
    		else if((int)k== KEY_NEXT)
		{
		    if((currentnode->maxnumvalues-currentnode->current_item)>10)
		    {
			currentnode->current_item += 10;
		    }
		}
    		else if((int)k== KEY_PREV)
		{
		    if(currentnode->current_item > 10)
		    {
			currentnode->current_item -= 10;
		    }
		    else
			currentnode->current_item = 0;
		}
		else
		{
			warn("invalid key pressed");
			return;
		}

		pfscr_node_draw();
		break;
	default:
		warn("key not valid, you fool");
	}
    }
}


void keyconfig()
{
	extern char *getenv(char *);

	char *home;
	char cfgfile[100];
	char name[20];
	int value;
	filebuf fb;


	KEY_HARDCOPY =	 (int)'H';
	KEY_BRK =	 (int)'B';
	KEY_DOC =	 (int)'D';
	KEY_GO =	 (int)'g';
	KEY_EXIT =	 (int)'e';
	KEY_TOGLATCH =	 (int)'r';
	KEY_TOGJUMP =	 (int)'t';
	KEY_HELP =	 (int)'?';

	KEY_NEXT =	 (int)'k';
	KEY_PREV =	 (int)'i';
	KEY_OPEN =	 (int)'l';
	KEY_CLOSE =	 (int)'j';

	KEY_CONT =	 (int)' ';
	
	home=getenv("HOME");
	sprintf(cfgfile,"%s/.pfckeys",home);

	// if user specified key definition file exists
	if (fb.open(cfgfile,input) != 0)
	{
		istream keydata(&fb);
		
		while (keydata.rdstate() == _good)
		{
			keydata >> name >> value;

			if(strcmp(name, "KEY_HARDCOPY") == 0)
				KEY_HARDCOPY = value;
			else if(strcmp(name, "KEY_BRK") == 0)
				KEY_BRK = value;
			else if(strcmp(name, "KEY_DOC") == 0)
				KEY_DOC = value;
			else if(strcmp(name, "KEY_GO") == 0)
				KEY_GO = value;
			else if(strcmp(name, "KEY_EXIT") == 0)
				KEY_EXIT = value;
			else if(strcmp(name, "KEY_TOGLATCH") == 0)
				KEY_TOGLATCH = value;
			else if(strcmp(name, "KEY_TOGJUMP") == 0)
				KEY_TOGJUMP = value;
			else if(strcmp(name, "KEY_HELP") == 0)
				KEY_HELP = value;
			else if(strcmp(name, "KEY_OPEN") == 0)
				KEY_OPEN = value;
			else if(strcmp(name, "KEY_CLOSE") == 0)
				KEY_CLOSE = value;
			else if(strcmp(name, "KEY_NEXT") == 0)
				KEY_NEXT = value;
			else if(strcmp(name, "KEY_PREV") == 0)
				KEY_PREV = value;
			else if(strcmp(name, "KEY_CONT") == 0)
				KEY_CONT = value;
			else
			{
			    sprintf(lbuf,"BAD KEY CONFIG NAME <%s>",name);
			    warn(lbuf);
			}
		}
		
	}
}

int numhelpkeys;

void keyshow(WINDOW *w, int val, char *text)
{
	numhelpkeys++;
	if(numhelpkeys > 10)
	{
		mvwaddstr(w,15,1,"- more -  (press CONTINUE key)");
		showhelp(w,1);

		numhelpkeys = 0;
		werase(w);
		mvwaddstr(w,1,0,"KEYBOARD COMMANDS AVAILABLE");
		mvwaddstr(w,3,0,"KEYSTROKE:    EFFECT:");
		wmove(w,4,0);
	}



	if((val > 32) && (val < 128))
	{
		waddch(w, (char)val);
		waddstr(w, "             ");
	}
	else if(val == 32)
	{
		waddstr(w, "<space>       ");
	}
	else if(val == 27)
	{
		waddstr(w, "<esc>         ");
	}
	else if(val > 127)
	{
		waddstr(w, "<crtl><shft>");
		waddch(w, (char)(val-64));
		waddstr(w, " ");
	}
	else
	{
		waddstr(w, "<crtl>");
		waddch(w, (char)(val+64));
		waddstr(w, "       ");
	}

	wprintw(w,text);
}

void keyhelp(char objtype)
{

	WINDOW *w;
	extern WINDOW *newwin(int, int, int, int);


	numhelpkeys = 0;
	w = newwin(16,75,1,0);
	werase(w);

	mvwaddstr(w,1,0,"KEYBOARD COMMANDS AVAILABLE");
	mvwaddstr(w,3,0,"KEYSTROKE:    EFFECT:");
	wmove(w,4,0);

	switch(objtype)
	{
	case PANEL:
	case CLUSTER:


		keyshow(w,KEY_CONT,"CONTINUE - Continue after messages\n");
		keyshow(w,KEY_GO,"GO - Execute a measurment sequence\n");
		keyshow(w,KEY_EXIT,"EXIT - Terminate the program\n");
		keyshow(w,KEY_BRK,"BREAK - Break the current measurement\n");
		keyshow(w,KEY_DOC,"DOC - Document the measurement machine\n");
	//	keyshow(w,KEY_HARDCOPY,"HARDCOPY - Print the entire panel\n");
	//	keyshow(w,KEY_TOGLATCH,"LATCH - Remember this node for toggle\n");
	//	keyshow(w,KEY_TOGJUMP,"TOGGLE - Toggle between here and latched node\n");
		keyshow(w,KEY_HELP,"HELP - Obtain help for the current node\n");
		keyshow(w,KEY_NEXT,"NEXT - Move cursor to next item\n");
		keyshow(w,KEY_PREV,"PREV - Move cursor to previous item\n");
		keyshow(w,KEY_OPEN,"OPEN - Open the current item\n");
		keyshow(w,KEY_CLOSE,"CLOSE - Go back up one level\n");

		break;
		
	case DISPLAY:

		keyshow(w,KEY_CONT,"CONTINUE - Continue after messages\n");
		keyshow(w,KEY_GO,"GO - Execute a measurment sequence\n");
		keyshow(w,KEY_EXIT,"EXIT - Terminate the program\n");
		keyshow(w,KEY_BRK,"BREAK - Break the current measurement\n");
		keyshow(w,KEY_DOC,"DOC - Document the measurement machine\n");
		keyshow(w,KEY_HELP,"HELP - Obtain help for the current node\n");
		keyshow(w,KEY_NEXT,"NEXT - Scroll to more recent data\n");
		keyshow(w,KEY_PREV,"PREV - Scroll to earlier data\n");
		keyshow(w,KEY_CLOSE,"CLOSE - Go back up one level\n");
		break;
		
	case FWINT:
	case FWFLT:
	case VWINT:
	case VWFLT:

		keyshow(w,KEY_CONT,"CONTINUE - Continue after messages\n");
		keyshow(w,KEY_GO,"GO - Execute a measurment sequence\n");
		keyshow(w,KEY_EXIT,"EXIT - Terminate the program\n");
		keyshow(w,KEY_BRK,"BREAK - Break the current measurement\n");
		keyshow(w,KEY_DOC,"DOC - Document the measurement machine\n");
		keyshow(w,KEY_HELP,"HELP - Obtain help for the current node\n");
		keyshow(w,KEY_NEXT,"NEXT - Move cursor to next item\n");
		keyshow(w,KEY_PREV,"PREV - Move cursor to previous item\n");
		keyshow(w,KEY_OPEN,"OPEN - Modify the current item\n");
		keyshow(w,KEY_CLOSE,"CLOSE - Send value(s), go back up one level\n");


		break;
		
	case ENUM:


		keyshow(w,KEY_CONT,"CONTINUE - Continue after messages\n");
		keyshow(w,KEY_GO,"GO - Execute a measurment sequence\n");
		keyshow(w,KEY_EXIT,"EXIT - Terminate the program\n");
		keyshow(w,KEY_BRK,"BREAK - Break the current measurement\n");
		keyshow(w,KEY_DOC,"DOC - Document the measurement machine\n");
		keyshow(w,KEY_HELP,"HELP - Obtain help for the current node\n");
		keyshow(w,KEY_NEXT,"NEXT - Move selector to next item\n");
		keyshow(w,KEY_PREV,"PREV - Move selector to previous item\n");
		keyshow(w,KEY_CLOSE,"CLOSE - Send value, go back up one level\n");
		break;
		
	case ASCKNOB:


		keyshow(w,KEY_CONT,"CONTINUE - Continue after messages\n");
		keyshow(w,KEY_GO,"GO - Execute a measurment sequence\n");
		keyshow(w,KEY_EXIT,"EXIT - Terminate the program\n");
		keyshow(w,KEY_BRK,"BREAK - Break the current measurement\n");
		keyshow(w,KEY_DOC,"DOC - Document the measurement machine\n");
		keyshow(w,KEY_HELP,"HELP - Obtain help for the current node\n");
		keyshow(w,KEY_OPEN,"OPEN - Modify the data value\n");
		keyshow(w,KEY_CLOSE,"CLOSE - Send value, go back up one level\n");
		break;
		
	case ASCDISP:


		keyshow(w,KEY_CONT,"CONTINUE - Continue after messages\n");
		keyshow(w,KEY_GO,"GO - Execute a measurment sequence\n");
		keyshow(w,KEY_EXIT,"EXIT - Terminate the program\n");
		keyshow(w,KEY_BRK,"BREAK - Break the current measurement\n");
		keyshow(w,KEY_DOC,"DOC - Document the measurement machine\n");
		keyshow(w,KEY_HELP,"HELP - Obtain help for the current node\n");
		break;
		
	default:
		warn("bad node type in keyhelp");
	}

	showhelp(w,0);

	delwin(w);
	touchwin(namebox);
	touchwin(dividebox);
	touchwin(logobox);
	touchwin(actionbox);
	touchwin(msgbox);
	wnoutrefresh(dividebox);
	wnoutrefresh(logobox);
	wnoutrefresh(namebox);
	wnoutrefresh(actionbox);
	wnoutrefresh(msgbox);
	doupdate();
}



void showhelp(WINDOW *w, int flag)
{
	if(flag == 0)
		mvwaddstr(w,15,1,"          (press CONTINUE key)");
	touchwin(w);
	wrefresh(w);
	while(pfkeychar() != (char)KEY_CONT);

}
