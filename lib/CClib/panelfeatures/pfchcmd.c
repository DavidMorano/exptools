
/**************************************************************************/
/* PANELFEATURES Package    Release:  1.0    Release Date: 1/15/89        */
/*                          Provider: J. D. Iorio  (speedy!jdi)           */
/**************************************************************************/
/*
*	pfchcmd.c -
*
* A collection of host command processing routines for the curses driver
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

#include <stream.h>
#include <curses.h>
#include <string.h>
#include "pfc.h"
#include "pfcdef.h"
#include "pfcglobals.h"
#include "pfcfunc.h"

/********************************************************************/

char *gethline();
struct node *nodeload();
void clearnode( struct node *);
struct node *findname(struct node *, char *);
struct node *gofindname(struct node *, char *);
void chg_name( struct node *);
void chg_label( struct node *);
void chg_axis( struct node *);
void chg_value( struct node *);
void chg_attrib( struct node *);
void upd_display( struct node *);
void upd_ascdisp( struct node *, char *);
void clr_display( struct node *);
/*
	void tilenode();
	void sizenode();
*/


void sendhost(char *msg)
{
	(*hostwrite) << msg << "\n";
	(*hostwrite).flush();
}


/*************************************************************************/
void hostcmd(struct node **root, char cmd)
{
	char *buf;

	cmd &= (char)0x7f;

    /* read the rest of the line to a nl and discard */
	buf = gethline();		
	if (buf == (char *) NULL)
		return;

    /* perform the action routine for the command */
	switch(cmd)
	{
	case LOAD:
		if(currentnode != NULLNP)
		{
			clearnode(*root);
		}
		currentnode = NULLNP;
		*root = nodeload();
		currentnode = (*root)->child[0];
		togglenode = (*root)->child[0];
		pfscr_node_draw();
		break;

	case CLEAR:
		if(*root == NULLNP)
			break;
		clearnode(*root);
		currentnode = NULLNP;
		wclear(actionbox);
		wrefresh(actionbox);
		break;

	case CHANGE_NAME:
		if(*root == NULLNP)
			break;
		chg_name(*root);
		break;

	case CHANGE_VALUE:
		if(*root == NULLNP)
			break;
		chg_value(*root);
		break;

	case CHANGE_LABEL:
		if(*root == NULLNP)
			break;
		chg_label(*root);
		break;

	case CHANGE_AXIS:
		if(*root == NULLNP)
			break;
		chg_axis(*root);
		break;

	case UPDATE_DISPLAY:
		if(*root == NULLNP)
			break;
		upd_display(*root);
		break;

	case CLEAR_DISPLAY:
		if(*root == NULLNP)
			break;
		clr_display(*root);
		break;

	case WARN_MESSAGE:
		warn(buf);
		break;

	case INFO_MESSAGE:
		inform(buf);
		break;

	case LOAD_LOGO:
		logo(buf);
		break;
	
	case MOUSE_GO:
		mouse_alive = TRUE;
		mvwaddstr(dividebox,0,MSGBOXW,"____");
		wmove(actionbox,currentnode->curs_y,
				currentnode->curs_x);
		wnoutrefresh(dividebox);
		wnoutrefresh(actionbox);
		doupdate();
		break;

	case MOUSE_STOP:
		mouse_alive = FALSE;
		wattron(dividebox,A_REVERSE);
		mvwaddstr(dividebox,0,MSGBOXW,"BUSY");
		wattroff(dividebox,A_REVERSE);
		wmove(actionbox,currentnode->curs_y,
				currentnode->curs_x);
		wnoutrefresh(dividebox);
		wnoutrefresh(actionbox);
		doupdate();
		break;

	case CHANGE_ATTRIB:
		if(*root == NULLNP)
			break;
		chg_attrib(*root);
		break;

	case TERMINATE:
		/* exit to regular terminal emulator */
		pfc_exit(*root);
		break;

	default:
		sprintf(lbuf,"Invalid host command {%c[%02x]%s}", cmd, cmd,buf);
		warn(lbuf);
	}
	return;
}

/************************************************************************/
void upd_ascdisp(struct node *n, char *buf)
{


	struct node *hold;
	char *bpt, *ept;
	int temp;
	char tempc[9];
	int i, j, k;

	bpt = buf;
	if(strncmp(bpt,"!!HOME!!",8) == 0)
	{
	    n->curs_x = 0;
	    n->curs_y = 0;
	    n->current_item = 0;
	}
	else if(strncmp(bpt,"!!MOVE!!",8) == 0)
	{
		/* read x,y coords */
	    bpt += 8;
	    for (ept=bpt; *ept!=';'; ept++);
	    *ept = '\0';
	    n->curs_x = atoi(bpt);

	    ept++;
	    for (bpt=ept; *ept!=';'; ept++);
	    *ept = '\0';
	    n->curs_y = atoi(bpt);

		/* compute the offset */
	    if((n->curs_x>=n->numvalues) || (n->curs_y>=n->maxnumvalues))
	    {
		warn(form("range error - ASCII display MOVE: %s", n->name));
			/* home the cursor */
	    	n->curs_x = 0;
	    	n->curs_y = 0;
	        n->current_item = 0;
	    }

	}
	else if(strncmp(bpt,"!!TRAP!!",8) == 0)
	{

	
	    hold = currentnode;
	    currentnode = n;
	    temp = n->current_item;
	    n->current_item = n->curs_y - 12;

	    for(ept=tempc, j=0; j<8; )
	    {

		if( (i = pfkeychar()) != NULL)
	    	{
			(*hostwrite).put((char)i);
			(*hostwrite).flush();
			continue;
	    	}
		else if( (i = pfhostchar()) != NULL)
	    	{
			i &= 0x7f;
			*ept = (char)i;
			ept++;
			j++;

		    // look for termination 
			if(((j==1) && ((char)i == '!'))
			    || ((j==2) && ((char)i == '!'))
			    || ((j==3) && ((char)i == 'U'))
			    || ((j==4) && ((char)i == 'N'))
			    || ((j==5) && ((char)i == 'T'))
			    || ((j==6) && ((char)i == 'R'))
			    || ((j==7) && ((char)i == '!'))
			    || ((j==8) && ((char)i == '!')))
			{
				continue;
			}

		    // else go process the text

	    	}
		else   // no characters to process
		{
			continue;
		}




	    
			// place each character on window 
		for (i=0; i<j; i++)
		{

		  // process special characters
	    	    if((n->curs_x >= n->numvalues) || (tempc[i] == (char)0x0a))
		    {
			// wrap around to next line
	      	        n->curs_x = 0;
	      	        n->curs_y += 1;
	    		n->current_item = n->curs_y - 12;
	    		pfscr_node_draw();
		    }
	    	    if ((tempc[i] == (char)0x0d) || (tempc[i] == (char)0x0a))
		    {
	      	        n->curs_x = 0;
			ept = tempc;
			j = 0;
		        continue;
		    }

	    	    if (tempc[i] == (char)0x07)
		    {
			beep();
		        continue;
		    }
	    	    if (tempc[i] == (char)0x08)
		    {
			if(n->curs_x > 0)
			{
	    			n->curs_x--;
			}
		        continue;
		    }
	    	    if (tempc[i] == (char)0x09)
		    {
			n->curs_x += (8 - n->curs_x%8);
		        continue;
		    }



		
 		    // while past bottom line, scroll
	    	    while(n->curs_y >= n->maxnumvalues)
	    	    {
	      	    	bpt = n->image[0];
			    /* scroll */
	      	    	for(k=1; k<n->maxnumvalues; k++)
	      	    	{
			    	n->image[k-1] = n->image[k];
	      	    	}
	      	    	n->image[k-1] = bpt;
	      	    	n->curs_y = k-1;
	      		for(k=0; k<n->numvalues; k++)
	      		{
				n->image[n->curs_y][k] = ' ';
	      		}
	    	    }
		

		    // place the text 
		    n->image[n->curs_y][n->curs_x] = tempc[i];
		    // recompute the cursor
		    n->curs_x++;
		}

		ept = tempc;
		j = 0;
	    }

	    n->current_item = n->curs_y - 12;
	    pfscr_node_draw();

	    // wait for termination after UNTRAP
	    while( (char)i != '\n')
	    {
		while((i = pfhostchar()) == NULL);
	    }

	    currentnode = hold;
	    n->current_item=temp;
	    pfscr_node_draw();
		
	}
	else if((strncmp(bpt,"!!CLRS!!",8) == 0)||
		(strncmp(bpt,"!!CLRL!!",8) == 0))
	{
		/* blank any partial line */
	    for(j=n->curs_x; j<n->numvalues-1; j++)
		n->image[n->curs_y][j] = ' ';
	    n->image[n->curs_y][n->numvalues-1] = '\0';


		/* blank rest of lines in object if needed */
	    if(strncmp(bpt,"!!CLRS!!",8) == 0)
	    {
		for(i=n->curs_y+1; i<n->maxnumvalues; i++)
		{
		    for(j=0; j<n->numvalues-1; j++)
			n->image[i][j] = ' ';
	    	    n->image[i][n->numvalues-1] = '\0';
		}
	    }
	}
	else   /* add a string */
	{
 		/* while past bottom line, scroll */
	    while(n->curs_y >= n->maxnumvalues)
	    {
	      ept = n->image[0];
		/* scroll */
	      for(j=1; j<n->maxnumvalues; j++)
	      {
		n->image[j-1] = n->image[j];
	      }
	      n->image[j-1] = ept;
	      n->curs_x = 0;
	      n->curs_y = j-1;
	      for(j=0; j<n->numvalues; j++)
	      {
		n->image[n->curs_y][j] = ' ';
	      }
	    }
		
		/* place the text */
	    for( ; *bpt != '\0'; bpt++)
	    {
		if(*bpt == (char)0x0d)
		{
			n->curs_x = 0;
		}
		else if(*bpt == (char)0x0a)
		{
			n->curs_y++;
		}
		else if(*bpt == (char)0x07)
		{
			beep();
		}
		else if(*bpt < (char)0x20)
		{
			continue;
		}
		else
		{
		    n->image[(n->curs_y)][(n->curs_x)] = *bpt;
		    n->curs_x++;
		    if(n->curs_x == n->numvalues)
			break;
		}
	    }

	    /* re compute the cursor */
	    n->curs_x = 0;
	    n->curs_y++;
		
		
	}

	if((currentnode == n) || (currentnode == n->parent))
		pfscr_node_draw();
}
/*************************************************************************/
void upd_display(struct node *root)
{
	char *buf, *bpt, *ept;
	struct node *n;
	float v;
	int i, j, next;

    /* get the data line from the host */
	buf = gethline();

    /* parse the official name */
	bpt = buf;
	for (ept=bpt; *ept != ';'; ept++);
	*ept = '\0';

    /* find the node */
	if ((n = findname(root,bpt)) == NULLNP)
	{
		sprintf(lbuf,"cannot find name - upd_display {%s}", bpt);
		warn(lbuf);
		return;
	}

	if(n->type == ASCDISP)
	{
		ept++;
		upd_ascdisp(n,ept);
		return;
	}

	/* read in the new data */
	bpt = ept;
	
		/* shift the data if needed */
	if(n->numvalues == n->maxnumvalues)
	{
		for(i=1; i<n->maxnumvalues; i++)
		{
			for(j=0; j<n->numdim; j++)
				n->data[j][i-1] = n->data[j][i];
		}
		n->numvalues--;
		n->current_item--;
	}
	next = n->numvalues;

		/* read the data */
	for(i=0; i<n->numdim; i++)
	{
		bpt++;
		v=(float)atof(bpt);
		n->data[i][next] = v;
		for( ; *bpt!=';'; bpt++);
	}
	n->numvalues++;
	if(n->numvalues <= 10)
		n->current_item = 0;
	else
		n->current_item ++;

	if((currentnode == n) || (currentnode == n->parent))
		pfscr_node_draw();
}
/*************************************************************************/
void clr_display(struct node *root)
{
	char *buf, *bpt, *ept;
	struct node *n;

    /* get the data line from the host */
	buf = gethline();

    /* parse the official name */
	bpt = buf;
	for (ept=bpt; *ept != ';'; ept++);
	*ept = '\0';

    /* find the node */
	if ((n = findname(root,bpt)) == NULLNP)
	{
		sprintf(lbuf,"cannot find name - clr_display {%s}", bpt);
		warn(lbuf);
		return;
	}

	n->numvalues = 0;
	n->current_item = 0;

	if((currentnode == n) || (currentnode == n->parent))
		pfscr_node_draw();
}
/*************************************************************************/
void chg_attrib( struct node *root)
{
	char *buf, *bpt, *ept;
	struct node *n;

    /* get the data line from the host */
	buf = gethline();

    /* parse the official name */
	bpt = buf;
	for (ept=bpt; *ept != ';'; ept++);
	*ept = '\0';

    /* find the node */
	if ((n = findname(root,bpt)) == NULLNP)
	{
		sprintf(lbuf,"cannot find name - chg_attrib {%s}", bpt);
		warn(lbuf);
		return;
	}

    /* read in the new attribute */
	bpt = ept+1;
	n->attribute = atoi(bpt);
	for (; *bpt!=';'; bpt++);

	if((currentnode == n) || (currentnode == n->parent))
		pfscr_node_draw();

}
/*************************************************************************/
void chg_value( struct node *root)
{
	char *buf, *bpt, *ept, *tpt;
	struct node *n;
	float v;
	int i;

    /* get the data line from the host */
	buf = gethline();

    /* parse the official name */
	bpt = buf;
	for (ept=bpt; *ept != ';'; ept++);
	*ept = '\0';

    /* find the node */
	if ((n = findname(root,bpt)) == NULLNP)
	{
		sprintf(lbuf,"cannot find name - chg_value {%s}", bpt);
		warn(lbuf);
		return;
	}

    /* read in the new values */
	bpt = ept+1;
	n->numvalues = atoi(bpt);
	for (; *bpt!=';'; bpt++);

    /* read in the new values */
	if(n->type != ASCKNOB)
	{
	    for(i=0; i<n->numvalues; i++)
	    {
		bpt++;
		v = (float)atof(bpt);
		n->value[i] = v;
		for (; *bpt!=';'; bpt++);
	    }
	}
	else
	{
		tpt = n->labels[2];
		for (bpt++; *bpt!=';'; bpt++)
		{
			*tpt = *bpt;
			tpt++;
		}
		*tpt = '\0';
	}

	if(n->attribute & A_JUSTSET)
	{
		/* if just interactively set, don't re-draw */
		n->attribute &= ~A_JUSTSET;
		return;
	}


	if((currentnode == n) || (currentnode == n->parent))
		pfscr_node_draw();

}
/*************************************************************************/
void chg_label(struct node *root)
{
	char *buf, *bpt, *ept, *tpt;
	struct node *n;
	int i;

    /* get the data line from the host */
	buf = gethline();

    /* parse the official name */
	bpt = buf;
	for (ept=bpt; *ept != ';'; ept++);
	*ept = '\0';

    /* find the node */
	if ((n = findname(root,bpt)) == NULLNP)
	{
		sprintf(lbuf,"cannot find name - chg_label {%s}", bpt);
		warn(lbuf);
		return;
	}


    /* change the labels */
	for(i=0; i<n->numdim; i++)
	{
		for(ept++, bpt=ept; *ept != ';'; ept++);
		*ept = '\0';

		if( (tpt = new char[(strlen(bpt)+1)]) == 0)
		{
			warn(form("can't allocate label - chg_label {%s}",
				bpt));
			return;
		}
		strcpy(tpt,bpt);
		delete n->labels[i];
		n->labels[i] = tpt;
	}


	if((currentnode == n) || (currentnode == n->parent))
		pfscr_node_draw();
}
/*************************************************************************/
void chg_axis(struct node *root)
{
	char *buf, *bpt, *ept, *temp;
	struct node *n;
	float v;
	int i;

    /* get the data line from the host */
	buf = gethline();

    /* parse the official name */
	bpt = buf;
	for (ept=bpt; *ept != ';'; ept++);
	*ept = '\0';

    /* find the node */
	if ((n = findname(root,bpt)) == NULLNP)
	{
		sprintf(lbuf,"cannot find name - chg_axis {%s}", bpt);
		warn(lbuf);
		return;
	}

    /* clear all values */
	n->numvalues = 0;

    /* change each dimension */
	for(i=0; i<n->numdim; i++)
	{
		bpt = ept;

	    /* parse the max and min values */
		bpt++;
		v = (float)atof(bpt);
		n->dmin[i] = v;
		for( ; *bpt != ';'; bpt++);
		
		bpt++;
		v = (float)atof(bpt);
		n->dmax[i] = v;
		for( ; *bpt != ';'; bpt++);
		
	    /* get the format and the label */
		for(bpt++, ept=bpt; *ept != ';'; ept++);
		*ept = '\0';
		temp = n->dfmt[i];
		if( (n->dfmt[i] = new char[(strlen(bpt)+1)]) == 0)
		{
			warn(form("can't allocate format - chg_axis {%s}",
				bpt));
			n->dfmt[i] = temp;
			return;
		}
		delete temp;
		strcpy(n->dfmt[i],bpt);


		for(ept++, bpt=ept; *ept != ';'; ept++);
		*ept = '\0';
		temp = n->labels[i];
		if( (n->labels[i] = new char[(strlen(bpt)+1)]) == 0)
		{
			warn(form("can't allocate labels - chg_axis {%s}",
				bpt));
			n->labels[i] = temp;
			return;
		}
		delete temp;
		strcpy(n->labels[i],bpt);


		for(ept++, bpt=ept; *ept != ';'; ept++);
		*ept = '\0';
		temp = n->dscalelab[i];
		if( (n->dscalelab[i] = new char[(strlen(bpt)+1)]) == 0)
		{
			warn(form("can't allocate scalelabels - chg_axis {%s}",
				bpt));
			n->dscalelab[i] = temp;
			return;
		}
		delete temp;
		strcpy(n->dscalelab[i],bpt);


	}

	if((currentnode == n) || (currentnode == n->parent))
		pfscr_node_draw();
}
/*************************************************************************/
void chg_name(struct node *root)
{
	char *buf, *bpt, *ept, *tpt;
	struct node *n;

    /* get the data line from the host */
	buf = gethline();

    /* parse the official name */
	bpt = buf;
	for (ept=bpt; *ept != ';'; ept++);
	*ept = '\0';

    /* find the node */
	if ((n = findname(root,bpt)) == NULLNP)
	{
		sprintf(lbuf,"cannot find name - chg_name {%s}", bpt);
		warn(lbuf);
		return;
	}


    /* change the name */
	for(ept++, bpt=ept; *ept != ';'; ept++);
	*ept = '\0';

	if( (tpt = new char[(strlen(bpt)+1)]) == 0)
	{
		warn(form("can't allocate name - chg_name {%s}",
			bpt));
		return;
	}
	strcpy(tpt,bpt);
	delete n->name;
	n->name = tpt;

	if((currentnode == n) || (currentnode == n->parent))
		pfscr_node_draw();
}
/*************************************************************************/
struct node *findname(struct node *root, char *s)
{
	struct node *n;
	char *bp, *ep;

	n = root;

	for (ep=s; *ep != '\0'; ep++)
	{
	    /* parse off one segment of the name */
		for(bp=ep; (*ep!='\0') && (*ep != '!'); ep++);

	    /* if last segment ... */
		if (*ep == '\0')
		{
			n = gofindname(n,bp);
			return(n);
		}
		else
		{
		    /* go find the intermediate node */
			*ep = '\0';
			if ((n = gofindname(n,bp)) == NULLNP)
				return(n);
		}
	}
}

/*************************************************************************/
struct node *gofindname(struct node *root, char *s)
{
	int i;
	struct node *n;

    /* is it this node ? */
	if (strcmp(root->oname, s) == 0)
		return(root);

    /* go check children */
	for (i=0; i<root->numchildren; i++)
	{
		if ((n = gofindname(root->child[i],s)) != NULLNP)
			return(n);
	}

    /* not in this sub-tree */
	return(NULLNP);
}
/*************************************************************************/
void printnode(struct node *n)
{
	int i,k;

	
	cerr << form("\nofficialname: <<%s>> username: (%s) ",n->oname, n->name);
	cerr << form("nch: %d w: %d mw: %d st: %d  dim: %d\n",
		n->numchildren, n->numvalues,
		n->maxnumvalues, n->style, n->numdim);

    /* now get rid of our stuff */
	switch (n->type)
	{
	case PANEL:
		break;
	case CLUSTER:
		break;
	case ASCDISP:
		break;
	case DISPLAY:
		for (k=0; k<n->numdim; k++)
			cerr << form("mn: %f mx: %f fmt: %s lab: %s\n",
				n->dmin[k],n->dmax[k],n->dfmt[k],n->labels[k]);
		cerr << form("DATA:");
		for (i=0; i<n->numvalues; i++)
		{
			for(k=0; k<n->numdim; k++)
				cerr << form("	%f",n->data[k][i]);
			cerr << form("\n");
		}
		break;
	case FWINT:
	case VWINT:
	case FWFLT:
	case VWFLT:
		cerr << form("mn: %f mx: %f\n", n->min, n->max);
		for (k=0; k<n->numvalues; k++)
			cerr << form("val %d: %f\n",k,n->value[k]);
		break;
	case ASCKNOB:
		for (k=0; k<3; k++)
			cerr << form("%s\n",n->labels[k]);
		break;
	case ENUM:
		cerr << form("mn: %f mx: %f\n", n->min, n->max);
		for (k=0; k<n->numdim; k++)
			cerr << form("labels[%d]: %s\n",k, n->labels[k]);
		for (k=0; k<n->numvalues; k++)
			cerr << form("val %d: %f\n",k,n->value[k]);
		break;
	default:
		warn("unknown type in printnode");
	}

}
/*************************************************************************/
void clearnode( struct node *n)
{
	int i;


    /* get rid of all children first */
	if (n->numchildren != 0)
	{
		for(i=0; i<n->numchildren; i++)
			clearnode(n->child[i]);
	}

    /* delete common stuff */

	delete n->name;
	delete n->fmt;
	delete n->oname;

    /* now get rid of our stuff */
	switch (n->type)
	{
	case PANEL:
		delete n->child;
		break;
	case CLUSTER:
		delete n->child;
		break;
	case DISPLAY:
		for(i=0; i<n->numdim; i++)
		{
			delete n->dfmt[i];
			delete n->data[i];
			delete n->labels[i];
			delete n->dscalelab[i];
		}
		delete n->dscalelab;
		delete n->data;
		delete n->dfmt;
		delete n->labels;
		delete n->dmin;
		delete n->dmax;
		break;
	case FWINT:
	case VWINT:
	case FWFLT:
	case VWFLT:
		delete n->scalelab;
		delete n->value;
		break;
	case ASCDISP:
		delete n->value;
		delete n->dmin;
		delete n->dmax;
		for(i=0; i<n->maxnumvalues; i++)
			delete n->image[i];
		delete n->image;
		break;
	case ASCKNOB:
		delete n->labels[0];
		delete n->labels[1];
		delete n->labels[2];
		delete n->labels;
		break;
	case ENUM:
		for(i=0; i<n->numdim; i++)
		{
			delete n->labels[i];
		}
		delete n->value;
		break;
	default:
		warn("unknown type in clearnode");
	}

    /* delete the node itself */
	delete n;

}



/*************************************************************************/
struct node* nodeload()
{
	int done, i;
	char *buf;
	struct node *newnode;
	struct node *nodestack[MAXNODESTACK];
	int stacktop;
	struct node *pparse(char *);
	struct node *cparse(char *);
	struct node *dparse(char *);
	struct node *kparse(char *);
	struct node *akparse(char *);
	struct node *adparse(char *);
	struct node *eparse(char *);

	for (stacktop = 0, done = 0; done == 0; )
	{
	    /* read a line from the host */
		buf=gethline();

	    /* call the proper parsing routine */
		switch(buf[0]) 
		{
		case  TERMINATE:
			if (stacktop != 1)
			{
				warn("stack error in nodeload");
			}
			done = 1;
			break;
		case  PANEL:
			newnode = pparse(buf); 
			stacktop--;
			if (stacktop < 0)
			{
			    warn("stack underflow in nodeload (panel)");
			}
			newnode->child[0] = nodestack[stacktop];
			newnode->child[0]->parent = newnode;
			nodestack[stacktop++] = newnode;
			break;
		case  CLUSTER:
			newnode = cparse(buf); 
			for(i=0; i<newnode->numchildren; i++)
			{
				stacktop--;
				if (stacktop < 0)
				{
				  warn("stack underflow in nodeload (cluster)");
				  break;
				}
				newnode->child[i] = nodestack[stacktop];
				newnode->child[i]->parent = newnode;
			}
			nodestack[stacktop++] = newnode;
			break;
		case  DISPLAY:
			newnode = dparse(buf); 
			nodestack[stacktop++] = newnode;
			break;
		case  FWINT:
		case  VWINT:
		case  FWFLT:
		case  VWFLT:
			newnode = kparse(buf); 
			nodestack[stacktop++] = newnode;
			break;
		case  ASCKNOB:
			newnode = akparse(buf); 
			nodestack[stacktop++] = newnode;
			break;
		case  ASCDISP:
			newnode = adparse(buf); 
			nodestack[stacktop++] = newnode;
			break;
		case  ENUM:
			newnode = eparse(buf); 
			nodestack[stacktop++] = newnode;
			break;
		default:
			warn("bad type in nodeload");
		}

		newnode->showflag |= SHOW_ALL;
	
	}
	return(nodestack[0]);

}

/*******************************************************/
/* GETHLINE */
char *gethline()
{
#define HBUFSIZE 1024
	static char hbuf[HBUFSIZE];
	char *bp;
	int c;
	int sz;
	int done;

	for (sz = 0,done=0,bp=hbuf; done == 0; )
	{
		if( (c = pfhostchar()) == -1)
			continue;

		c &= (char)0x7f;

		*bp = (char)c;
		
		if ( *bp == '\n' )
			done = 1;

		else
		{
			bp++;
			if (sz++ == HBUFSIZE)
			{
				warn("line too long - gethline");
			}
		}
		
	}
	*bp = '\0';
	return(hbuf);
}

/*******************************************************/
struct node *comparse( char *buf)
{
	char *bpt;
	char *ept;
	struct node *n;

    /* create a node */
	if( (n = new node) == NULLNP )
	{
		sprintf(lbuf,"cannot alloc node - comparse {%s}", buf);
		warn(lbuf);
		return(NULLNP);
	}


    /* save the type */
	n->type = buf[0];

    /* initialize some stuff for drawing */
	n->current_item = 0;

    /* parse the name */
	bpt = buf;
	bpt++;
	for (ept=bpt; *ept != ';'; ept++);
	*ept = '\0';
	if( (n->name = new char[(strlen(bpt)+1)]) == 0)
	{
		sprintf(lbuf,"cannot alloc name - comparse {%s}", bpt);
		warn(lbuf);
		delete n;
		return(NULLNP);
	}
	strcpy(n->name, bpt);

    /* parse the officialname */
	ept++;
	for (bpt=ept; *ept != ';'; ept++);
	*ept = '\0';
	if( (n->oname = new char[(strlen(bpt)+1)]) == 0)
	{
		sprintf(lbuf,"cannot alloc officialname - comparse {%s}", bpt);
		warn(lbuf);
		delete n->name;
		delete n;
		return(NULLNP);
	}
	strcpy(n->oname, bpt);

    /* parse the labeling format */
	ept++;
	for (bpt=ept; *ept != ';'; ept++);
	*ept = '\0';
	if( (n->fmt = new char[(strlen(bpt)+1)]) == 0)
	{
		sprintf(lbuf,"cannot alloc format - comparse {%s}", bpt);
		warn(lbuf);
		delete n->oname;
		delete n->name;
		delete n;
		return(NULLNP);
	}
	strcpy(n->fmt, bpt);

    /* parse attributes */
	ept++;
	n->attribute = atoi(ept);
	for (; *ept!=';'; ept++);
	*ept = '\0';

    /* parse numchildren */
	ept++;
	n->numchildren = atoi(ept);
	for (; *ept!=';'; ept++);
	*ept = '\0';

    /* parse numvalues */
	ept++;
	n->numvalues = atoi(ept);
	for (; *ept!=';'; ept++);
	*ept = '\0';

    /* parse maxnumvalues */
	ept++;
	n->maxnumvalues = atoi(ept);

	return(n);
}
	

/*******************************************************/
struct node *pparse(char *buf)
{
	struct node *n;

    /* create a node */
	if( (n=comparse(buf)) == NULLNP )
	{
		warn("cannot alloc memory - pparse");
		return(NULLNP);
	}

    /* myallocate storage for children */
	if( (n->child = new node *[1]) == 0)
	{
		sprintf(lbuf,"cannot alloc child ptr - pparse {%s}", n->name);
		warn(lbuf);
		delete n->oname;
		delete n->name;
		delete n;
		return(NULLNP);
	}

    /* done parsing */
	return(n);

}

/*******************************************************/
struct node *cparse( char *buf)
{
	struct node *n;

    /* create a node */
	if( (n=comparse(buf)) == NULLNP )
	{
		warn("cannot alloc memory - cparse");
		return(NULLNP);
	}

    /* myallocate storage for children */
	if( (n->child = new node *[n->numchildren]) == 0)
	{
		sprintf(lbuf,"cannot alloc child ptr - cparse {%s}", n->name);
		warn(lbuf);
		delete n->oname;
		delete n->name;
		delete n;
		return(NULLNP);
	}

    /* done parsing */
	return(n);

}

/*******************************************************/
struct node *dparse(char *buf)
{
	char *bpt;
	char *ept;
	struct node *n;
	int i, j;
	float v;

    /* create a node */
	if( (n=comparse(buf)) == NULLNP )
	{
		warn("cannot myalloc memory - dparse");
		return(NULLNP);
	}

    /* skip over the common data in buffer */
	for (bpt=buf; *bpt!=';'; bpt++);

    /* parse the style */
	bpt++;
	n->style = atoi(bpt);
	for (; *bpt!=';'; bpt++);

    /* parse the numdimensions */
	bpt++;
	n->numdim = atoi(bpt);
	for (; *bpt!=';'; bpt++);

    /* myallocate storage */
	if( (n->dfmt = new char *[n->numdim]) == 0)
	{
		sprintf(lbuf,"cannot alloc dfmt - dparse {%s}", buf);
		warn(lbuf);
		delete n->fmt;
		delete n->oname;
		delete n->name;
		delete n;
		return(NULLNP);
	}
	if( (n->dmin = new float [n->numdim]) == 0)
	{
		sprintf(lbuf,"cannot alloc dmin - dparse {%s}", buf);
		warn(lbuf);
		delete n->dfmt;
		delete n->fmt;
		delete n->oname;
		delete n->name;
		delete n;
		return(NULLNP);
	}
	if( (n->dmax = new float [n->numdim]) == 0)
	{
		sprintf(lbuf,"cannot alloc max - dparse {%s}", buf);
		warn(lbuf);
		delete n->dmin;
		delete n->dfmt;
		delete n->fmt;
		delete n->oname;
		delete n->name;
		delete n;
		return(NULLNP);
	}
	if( (n->data = new float *[n->numdim]) == 0)
	{
		sprintf(lbuf,"cannot alloc data - dparse {%s}", buf);
		warn(lbuf);
		delete n->dmax;
		delete n->dmin;
		delete n->dfmt;
		delete n->fmt;
		delete n->oname;
		delete n->name;
		delete n;
		return(NULLNP);
	}
	if( (n->labels = new char *[n->numdim]) == 0)
	{
		sprintf(lbuf,"cannot myalloc labels - dparse {%s}", buf);
		warn(lbuf);
		delete n->data;
		delete n->dmax;
		delete n->dmin;
		delete n->dfmt;
		delete n->fmt;
		delete n->oname;
		delete n->name;
		delete n;
		return(NULLNP);
	}
	if( (n->dscalelab = new char *[n->numdim]) == 0)
	{
		sprintf(lbuf,"cannot myalloc scalelabels - dparse {%s}", buf);
		warn(lbuf);
		delete n->labels;
		delete n->data;
		delete n->dmax;
		delete n->dmin;
		delete n->dfmt;
		delete n->fmt;
		delete n->oname;
		delete n->name;
		delete n;
		return(NULLNP);
	}

    /* for each dimension */
	for (i=0; i<n->numdim; i++)
	{
    	    /* parse the max and min values */
		bpt++;
		v = (float)atof(bpt);
		n->dmin[i] = v;
		for (; *bpt!=';'; bpt++);
		bpt++;
		v = (float)atof(bpt);
		n->dmax[i] = v;
		for (; *bpt!=';'; bpt++);

	    /* get the format and label */
		for (bpt++,ept=bpt; *ept != ';'; ept++);
		*ept = '\0';
		if( (n->dfmt[i] = new char[(strlen(bpt)+1)]) == 0)
		{
			sprintf(lbuf,
				"can't alloc dfmt %d - dparse {%s}",i ,bpt);
			warn(lbuf);
			for(j=0; j<i; j++)
			{
				delete n->dfmt[j];
				delete n->data[j];
				delete n->labels[j];
				delete n->dscalelab[j];
			}
			delete n->dscalelab;
			delete n->labels;
			delete n->data;
			delete n->dmax;
			delete n->dmin;
			delete n->dfmt;
			delete n->fmt;
			delete n->oname;
			delete n->name;
			delete n;
			return(NULLNP);
		}
		strcpy(n->dfmt[i], bpt);

		for (ept++,bpt = ept; *ept != ';'; ept++);
		*ept = '\0';
		if( (n->labels[i] = new char[(strlen(bpt)+1)]) == 0)
		{
			sprintf(lbuf,
				"can't alloc labels %d - dparse {%s}",i ,bpt);
			warn(lbuf);
			for(j=0; j<i; j++)
			{
				delete n->dfmt[j];
				delete n->data[j];
				delete n->labels[j];
				delete n->dscalelab[j];
			}
			delete n->dfmt[j];
			delete n->dscalelab;
			delete n->labels;
			delete n->data;
			delete n->dmax;
			delete n->dmin;
			delete n->dfmt;
			delete n->fmt;
			delete n->oname;
			delete n->name;
			delete n;
			return(NULLNP);
		}
		strcpy(n->labels[i], bpt);

		ept++;

		for (bpt = ept; *ept != ';'; ept++);
		*ept = '\0';
		if( (n->dscalelab[i] = new char[(strlen(bpt)+1)]) == 0)
		{
			sprintf(lbuf,
				"can't myalloc dsclab %d - dparse {%s}",i ,bpt);
			warn(lbuf);
			for(j=0; j<i; j++)
			{
				delete n->dfmt[j];
				delete n->data[j];
				delete n->labels[j];
				delete n->dscalelab[j];
			}
			delete n->labels[j];
			delete n->dfmt[j];
			delete n->dscalelab;
			delete n->labels;
			delete n->data;
			delete n->dmax;
			delete n->dmin;
			delete n->dfmt;
			delete n->fmt;
			delete n->oname;
			delete n->name;
			delete n;
			return(NULLNP);
		}
		strcpy(n->dscalelab[i], bpt);

		if( (n->data[i] = new float[n->maxnumvalues]) == 0)
		{
			sprintf(lbuf,
				"can't alloc data %d - dparse {%s}",i ,bpt);
			warn(lbuf);
			for(j=0; j<i; j++)
			{
				delete n->dfmt[j];
				delete n->data[j];
				delete n->labels[j];
				delete n->dscalelab[j];
			}
			delete n->dscalelab[j];
			delete n->labels[j];
			delete n->dfmt[j];
			delete n->dscalelab;
			delete n->labels;
			delete n->data;
			delete n->dmax;
			delete n->dmin;
			delete n->dfmt;
			delete n->fmt;
			delete n->oname;
			delete n->name;
			delete n;
			return(NULLNP);
		}

		bpt = ept;
	}

	n->element_width = 0;		/* indicate display initialization */

    /* done parsing */
	return(n);
	
}

/*******************************************************/
struct node *kparse(char *buf)
{
	char *bpt, *ept;
	struct node *n;
	float v;
	int i;

    /* create a node */
	if( (n=comparse(buf)) == NULLNP )
	{
		warn("cannot alloc memory - kparse");
		return(NULLNP);
	}

    /* skip over the common data in buffer */
	for (bpt=buf; *bpt!=';'; bpt++);

    /* parse the style */
	bpt++;
	n->style = atoi(bpt);
	for (; *bpt!=';'; bpt++);

    /* parse the max and min values */
	bpt++;
	n->min = (float)atof(bpt);
	for (; *bpt!=';'; bpt++);
	bpt++;
	n->max = (float)atof(bpt);
	for (; *bpt!=';'; bpt++);
	
	if( n->min >= n->max)
	{
		sprintf(lbuf,"error - knob <%s>, MIN > MAX; swapping");
		warn(lbuf);
		v = n->min;
		n->min = n->max;
		n->max = v;
	}

    /* get the scale label for the knob */
	bpt++;
	for (ept=bpt; *ept != ';'; ept++);
	*ept = '\0';

	if( (n->scalelab = new char[(strlen(bpt)+1)]) == 0)
	{
		sprintf(lbuf,"cannot alloc scale label - kparse {%s}", buf);
		warn(lbuf);
		delete n->fmt;
		delete n->oname;
		delete n->name;
		delete n;
		return(NULLNP);
	}
	strcpy(n->scalelab,bpt);
	bpt = ept;

    /* get the value(s) of the knob */
	if( (n->value = new float[n->maxnumvalues]) == 0)
	{
		sprintf(lbuf,"cannot alloc values - kparse {%s}", buf);
		warn(lbuf);
		delete n->scalelab;
		delete n->fmt;
		delete n->oname;
		delete n->name;
		delete n;
		return(NULLNP);
	}
	for(i=0; i<n->numvalues; i++)
	{
	    /* for currently set knobs */
		bpt++;
		n->value[i] = (float)atof(bpt);
		for (; *bpt!=';'; bpt++);
	}
	for(; i<n->maxnumvalues; i++)
	{
	    /* for currently inactive knobs */
		n->value[i] = n->min;
	}

    /* done parsing */
	return(n);
	
}


/*******************************************************/
struct node *adparse(char *buf)
{
	char *bpt;
	int i,j;
	struct node *n;

    /* create a node */
	if( (n=comparse(buf)) == NULLNP )
	{
		warn("cannot alloc memory - adparse");
		return(NULLNP);
	}

    /* skip over the common data in buffer */
	for (bpt=buf; *bpt!=';'; bpt++);

    /* parse the style */
	bpt++;
	n->style = atoi(bpt);
	for (; *bpt!=';'; bpt++);

    /* allocate a pad for data storage */
	n->image = new char *[n->maxnumvalues];
	for(i=0; i<n->maxnumvalues; i++)
	{
		n->image[i] = new char[n->numvalues+1];
		for(j=0; j<n->numvalues; j++)
	      	{
			n->image[i][j] = ' ';
	      	}
		n->image[i][n->maxnumvalues-1] = '\0';
	}
	

	n->curs_x = 0;
	n->curs_y = 0;
	n->current_item = 0;


    /* done parsing */
	return(n);
	
}

/*******************************************************/
struct node *akparse(char *buf)
{
	char *bpt, *ept;
	struct node *n;

    /* create a node */
	if( (n=comparse(buf)) == NULLNP )
	{
		warn("cannot alloc memory - akparse");
		return(NULLNP);
	}

    /* skip over the common data in buffer */
	for (bpt=buf; *bpt!=';'; bpt++);

    /* parse the style */
	bpt++;
	n->style = atoi(bpt);
	for (; *bpt!=';'; bpt++);


    /* allocate pointers for strings */
	if( (n->labels = new char*[3]) == 0)
	{
		sprintf(lbuf,"cannot alloc string pointers - akparse {%s}", buf);
		warn(lbuf);
		delete n->oname;
		delete n->fmt;
		delete n->name;
		delete n;
		return(NULLNP);
	}

    /* get the question for the knob */
	bpt++;
	for (ept=bpt; *ept != ';'; ept++);
	*ept = '\0';

	if( (n->labels[0] = new char[(strlen(bpt)+1)]) == 0)
	{
		sprintf(lbuf,"cannot alloc question string - akparse {%s}", buf);
		warn(lbuf);
		delete n->oname;
		delete n->labels;
		delete n->fmt;
		delete n->name;
		delete n;
		return(NULLNP);
	}
	strcpy(n->labels[0],bpt);
	bpt = ept;

    /* get the aid string for the knob */
	bpt++;
	for (ept=bpt; *ept != ';'; ept++);
	*ept = '\0';

	if( (n->labels[1] = new char[(strlen(bpt)+1)]) == 0)
	{
		sprintf(lbuf,"cannot alloc aid string - akparse {%s}", buf);
		warn(lbuf);
		delete n->oname;
		delete n->labels[0];
		delete n->labels;
		delete n->fmt;
		delete n->name;
		delete n;
		return(NULLNP);
	}
	strcpy(n->labels[1],bpt);
	bpt = ept;

    /* get the current answer for the knob */
	bpt++;
	for (ept=bpt; *ept != ';'; ept++);
	*ept = '\0';

	if( (n->labels[2] = new char[(strlen(bpt)+1)]) == 0)
	{
		sprintf(lbuf,"cannot alloc answer string - akparse {%s}", buf);
		warn(lbuf);
		delete n->oname;
		delete n->labels[0];
		delete n->labels[1];
		delete n->labels;
		delete n->fmt;
		delete n->name;
		delete n;
		return(NULLNP);
	}
	strcpy(n->labels[2],bpt);


    /* done parsing */
	return(n);
	
}

/*******************************************************/
struct node *eparse(char *buf)
{
	char *bpt;
	char *ept;
	struct node *n;
	int i,j;

    /* create a node */
	if( (n=comparse(buf)) == NULLNP )
	{
		warn("cannot myalloc memory - eparse");
		return(NULLNP);
	}

    /* skip over the common data in buffer */
	for (bpt=buf; *bpt!=';'; bpt++);

    /* parse the style */
	bpt++;
	n->style = atoi(bpt);
	for (; *bpt!=';'; bpt++);

    /* parse the number of labels*/
	bpt++;
	n->numdim = atoi(bpt);
	for (; *bpt!=';'; bpt++);

    /* get the label(s) of the knob */
	if( (n->labels = new char *[n->numdim]) == 0)
	{
		sprintf(lbuf,"cannot myalloc labelptr - eparse {%s}", buf);
		warn(lbuf);
		delete n->oname;
		delete n->fmt;
		delete n->name;
		delete n;
		return(NULLNP);
	}
	ept = bpt;
	for (i=0; i<n->numdim; i++)
	{
		for (ept++,bpt=ept; *ept != ';'; ept++);
		*ept = '\0';
		if( (n->labels[i] = new char[(strlen(bpt)+1)]) == 0)
		{
			sprintf(lbuf,"cannot alloc labels - eparse {%s}",
								 bpt);
			warn(lbuf);
			for(j=0; j<i; j++)
				delete n->labels[j];
			delete n->labels;
			delete n->oname;
			delete n->fmt;
			delete n->name;
			delete n;
			return(NULLNP);
		}
		strcpy(n->labels[i], bpt);
	}

    /* get the value(s) of the knob */
	if( (n->value = new float[n->maxnumvalues]) == 0)
	{
		sprintf(lbuf,"cannot alloc values - eparse {%s}", buf);
		warn(lbuf);
		for(j=0; j<n->numdim; j++)
			delete n->labels[j];
		delete n->labels;
		delete n->oname;
		delete n->fmt;
		delete n->name;
		delete n;
		return(NULLNP);
	}
	n->min=0;
	n->max=n->numdim-1;
	for(i=0; i<n->numvalues; i++)
	{
		ept++;
		n->value[i] = (float) atoi(ept);
		for (; *ept!=';'; ept++);
	}


    /* done parsing */
	return(n);
	
}

/*************************************************************************/
