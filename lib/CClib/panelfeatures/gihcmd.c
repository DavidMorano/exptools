
/**************************************************************************/
/* PANELFEATURES Package    Release:  1.0    Release Date: 1/15/89        */
/*                          Provider: J. D. Iorio  (speedy!jdi)           */
/**************************************************************************/
/*
*	gihcmd.c -
*
* A collection of host command processing routines for the 630 terminal
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

extern struct node *currentnode;
extern struct node *togglenode;
extern char lbuf[];
extern int mouse_alive;

extern Texture16  *tweed, *busycursor, *normcursor;

extern void warn();
extern void askmsg();
extern double atof();
extern char *myalloc();
extern void myfree();

extern int proto_mode;

char *gethline();
struct node *nodeload();
void clearnode();
struct node *findname();
struct node *gofindname();
void chg_name();
void chg_label();
void chg_axis();
void chg_value();
void chg_attrib();
void upd_display();
void upd_ascdisp();
void clr_display();
void tilenode();
void sizenode();
void gi_exit();

extern void screen_curnode_draw();
extern void screen_com_draw();
extern void screen_key_draw();
extern void screen_name_draw();
extern void screen_logo_draw();
extern void window_upd_disp();
extern void window_node_draw();
extern void initwindow();

/*************************************************************************/
void hostcmd(root,cmd)
struct node **root;
char cmd;
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

		proto_mode = 1;

		currentnode = NULLNP;
		*root = nodeload();

		proto_mode = 0;

		currentnode = *root;
		togglenode = *root;
		screen_com_draw();
		screen_curnode_draw();
		break;

	case CLEAR:
		if(*root == NULLNP)
			break;
		clearnode(*root);
		currentnode = NULLNP;
		screen_com_draw();
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

	case ASK_MESSAGE:
		askmsg(buf);
		break;

	case INFO_MESSAGE:
		inform(buf);
		break;

	case LOAD_LOGO:
		logo(buf);
		break;
	
	case MOUSE_GO:
		mouse_alive = TRUE;
		cursswitch( normcursor );
		break;

	case MOUSE_STOP:
		mouse_alive = FALSE;
		cursswitch( busycursor );
		break;

	case CHANGE_ATTRIB:
		if(*root == NULLNP)
			break;
		chg_attrib(*root);
		break;

	case TERMINATE:
		/* exit to regular terminal emulator */
		gi_exit(*root);

	default:
		Sprintf(lbuf,"Invalid host command {%c[%02x]%s}", cmd, cmd,buf);
		warn(lbuf);
	}
	return;
}

/************************************************************************/
void upd_ascdisp(n, buf)
struct node *n;
char *buf;
{
	char *bpt, *ept;
	char tempc[9];
	int i, j, k;
	Rectangle tempr;
	unsigned long next_refresh;

	bpt = buf;
	if(strncmp(bpt,"!!HOME!!",8) == 0)
	{
	    AD_CXY = fPt(0,0);
	    AD_CPT = AD_CMAP.origin;
	}
	else if(strncmp(bpt,"!!MOVE!!",8) == 0)
	{
		/* read x,y coords */
	    bpt += 8;
	    for (ept=bpt; *ept!=';'; ept++);
	    *ept = '\0';
	    AD_CXY.x = atoi(bpt);

	    ept++;
	    for (bpt=ept; *ept!=';'; ept++);
	    *ept = '\0';
	    AD_CXY.y = atoi(bpt);

		/* compute the offset */
	    if((AD_CXY.x>=n->numvalues) || (AD_CXY.y>=n->maxnumvalues))
	    {
		Sprintf(lbuf,"range error - ASCII display MOVE: %s",
			n->oname);
		warn(lbuf);
			/* home the cursor */
	        AD_CXY = fPt(0,0);
	        AD_CPT = AD_CMAP.origin;
	    }
	    else
	    {
	        AD_CPT.x = AD_CMAP.origin.x + AD_CXY.x * 7;
	        AD_CPT.y = AD_CMAP.origin.y + AD_CXY.y * 14;
	    }

	}
	else if(strncmp(bpt,"!!TRAP!!",8) == 0)
	{

	    cursswitch(tweed);

	    next_refresh = realtime() + (unsigned long)30;


	    for(ept=tempc, j=0; j<8; )
	    {

	    	if((i = kbdchar()) != -1)
	    	{
			sendchar((char)i);
			continue;
	    	}
	    	else if((i = rcvchar()) != -1)
	    	{
			i &= 0x7f;
			*ept = (char)i;

		    /* trap special characters */
			k=0;
			switch(*ept)
			{
			case 0x07:		/* bell */
				ringbell();
				k=1;
				break;
			case 0x08:		/* back space */
				if(AD_CXY.x > 0)
				{
	    	    			AD_CXY.x -= 1;
	    	    			AD_CPT.x -= 7;
				}
				k=1;
				break;
			case 0x09:		/* tab */
				k = AD_CXY.x + (8 - AD_CXY.x%8);
	    	    		AD_CXY.x += k;
	    	    		AD_CPT.x += k*7;
				k=1;
				break;
			default:
				k=0;
			}
			if (k!=0)
				continue;




			ept++;
			j++;

		    /* look for termination */
			if(((j==1) && ((char)i == '!'))
			    || ((j==2) && ((char)i == '!'))
			    || ((j==3) && ((char)i == 'U'))
			    || ((j==4) && ((char)i == 'N'))
			    || ((j==5) && ((char)i == 'T'))
			    || ((j==6) && ((char)i == 'R'))
			    || ((j==7) && ((char)i == '!'))
			    || ((j==8) && ((char)i == '!')))
				continue;

	    	}
		else
		{
			if(next_refresh < realtime())
			{
    				/* is this node is on the screen */
					/* the draw it on screen */
				if(n->parent == currentnode)
				{
	    				screen_node_draw(n);
	    				next_refresh = realtime()
							 + (unsigned long)30;
				}
				else
	    			 next_refresh = realtime()+(unsigned long)60000;
			}
			 sleep(2);	/* allow kbd process */
			 continue;
		}

	    
			/* place each character on window */
		for (i=0; i<j; i++)
		{

	    	    if((AD_CXY.x >= n->numvalues) || (tempc[i] == (char)0x0d))
		    {
			/* wrap around to next line */
	      	        AD_CXY.x = 0;
	      	        AD_CXY.y += 1;
	      	        AD_CPT.x = AD_CMAP.origin.x;
	      	        AD_CPT.y = AD_CMAP.origin.y + AD_CXY.y * 14;
		    }
	    	    if ((tempc[i] == (char)0x0d) || (tempc[i] == (char)0x0a))
		    {
	      	        AD_CXY.x = 0;
	      	        AD_CPT.x = AD_CMAP.origin.x;
			ept = tempc;
			j = 0;
		        continue;
		    }
		
 		    /* while past bottom line, scroll */
	    	    while(AD_CXY.y >= n->maxnumvalues)
	    	    {
			/* scroll */
	      	        bitblt(n->image,AD_SMAP,n->image,
					AD_CMAP.origin,F_STORE);
			/* place cursor */
	      	        AD_CXY.x = 0;
	      	        AD_CXY.y -= 1;
	      	        AD_CPT.x = AD_CMAP.origin.x;
	      	        AD_CPT.y = AD_CMAP.origin.y + AD_CXY.y * 14;
			    /* blank last line */
	      	        tempr.origin.x = AD_CMAP.origin.x;
	      	        tempr.origin.y = AD_CMAP.corner.y - 14;
	      	        tempr.corner.x = AD_CMAP.corner.x;
	      	        tempr.corner.y = AD_CMAP.corner.y;
	      	        texture(n->image,tempr,&T_white,F_STORE);
	    	    }
		
	    	    *bpt = tempc[i];
	    	    *(bpt+1) = '\0';

		    /* place the text */
	    	    string(&TEXT_FONT, bpt, n->image, AD_CPT, F_STORE);
		    /* recompute the cursor */
	    	    AD_CXY.x += 1;
	    	    AD_CPT.x += 7;
		}

		ept = tempc;
		j = 0;
	    }

	    /* wait for termination after UNTRAP */
	    while( (char)i != '\n')
	    {
	    	wait(RCV);
	    	i = rcvchar();
	    }

	    cursswitch(normcursor);
		
	}
	else if((strncmp(bpt,"!!CLRS!!",8) == 0)||
		(strncmp(bpt,"!!CLRL!!",8) == 0))
	{
		/* blank any partial line */
	    if((i=AD_CXY.x) != 0)
	    {
		for(j=0; i< n->numvalues; j++,i++)
			lbuf[j] = ' ';
		lbuf[j] = '\0';
	    	string(&TEXT_FONT, lbuf, n->image, AD_CPT, F_STORE);
		j = 1;
	    }
	    else
		j = 0;

		/* blank rest of lines in object if needed */
	    if(strncmp(bpt,"!!CLRS!!",8) == 0)
	    {
	      tempr.origin.x = AD_CMAP.origin.x;
	      tempr.origin.y = AD_CMAP.origin.y + ((AD_CXY.y+j) * 14);
	      tempr.corner.x = AD_CMAP.corner.x;
	      tempr.corner.y = AD_CMAP.corner.y;
	      texture(n->image,tempr,&T_white,F_STORE);
	    }
	}
	else
	{
 		/* while past bottom line, scroll */
	    while(AD_CXY.y >= n->maxnumvalues)
	    {
		/* scroll */
	      bitblt(n->image,AD_SMAP,n->image,AD_CMAP.origin,F_STORE);
		/* place cursor */
	      AD_CXY.x = 0;
	      AD_CXY.y -= 1;
	      AD_CPT.x = AD_CMAP.origin.x;
	      AD_CPT.y = AD_CMAP.origin.y + AD_CXY.y * 14;
		/* blank last line */
	      tempr.origin.x = AD_CMAP.origin.x;
	      tempr.origin.y = AD_CMAP.corner.y - 14;
	      tempr.corner.x = AD_CMAP.corner.x;
	      tempr.corner.y = AD_CMAP.corner.y;
	      texture(n->image,tempr,&T_white,F_STORE);
	    }
		
		/* limit the new string */
	    i = n->numvalues - AD_CXY.x;
	    if (strlen(bpt) > i)
		*(bpt+i) = '\0';

		/* skip NEWLINES */
	    for(ept=bpt; ((*ept != (char)0x0d) && (*ept != (char)0x0a)); ept++);
	    *ept = '\0';

		/* place the text */
	    string(&TEXT_FONT, bpt, n->image, AD_CPT, F_STORE);
		/* recompute the cursor */
	    AD_CXY.x = 0;
	    AD_CXY.y += 1;
	    AD_CPT.x = AD_CMAP.origin.x;
	    AD_CPT.y = AD_CMAP.origin.y + AD_CXY.y * 14;
		
	}
	if(n->parent == currentnode)    /* this node is on the screen */
	    screen_node_draw(n);	/* the draw it on screen */
}
/*************************************************************************/
void upd_display(root)
struct node *root;
{
	char *buf, *bpt, *ept, *tpt;
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
		Sprintf(lbuf,"cannot find name - upd_display {%s}", bpt);
		warn(lbuf);
		return;
	}

    /* read in the new values */
	bpt = ept;

	/* if ascii display */
	if (n->type == ASCDISP)
	{
		/* process commands and data text elsewhere */
		bpt++;
		upd_ascdisp(n, bpt);
	}
	else
	{

		/* shift data if needed */
		if(n->numvalues == n->maxnumvalues)
		{
			for (i=1; i<n->maxnumvalues; i++)
			{
				for (j=0; j<n->numdim; j++)
					n->data[j][i-1] = n->data[j][i];
			}
			n->numvalues--;
		
		}
		next = n->numvalues;

		/* read the data */
		for(i=0; i<n->numdim; i++)
		{
			bpt++;
			v = (float)atof(bpt);
			n->data[i][next] = v;
			for (; *bpt!=';'; bpt++);
		}
		n->numvalues++;
		n->showflag |= SHOW_VALUE;
		window_upd_disp(n);
	}

}
/*************************************************************************/
void clr_display(root)
struct node *root;
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
		Sprintf(lbuf,"cannot find name - clr_display {%s}", bpt);
		warn(lbuf);
		return;
	}

	n->numvalues = 0;
	n->showflag |= SHOW_VALUE;
	window_node_draw(n);

}
/*************************************************************************/
void chg_attrib(root)
struct node *root;
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
		Sprintf(lbuf,"cannot find name - chg_value {%s}", bpt);
		warn(lbuf);
		return;
	}

    /* read in the new attribute */
	bpt = ept+1;
	n->attribute = atoi(bpt);
	for (; *bpt!=';'; bpt++);

	n->showflag |= SHOW_VALUE;
	window_node_draw(n);

}
/*************************************************************************/
void chg_value(root)
struct node *root;
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
		Sprintf(lbuf,"cannot find name - chg_value {%s}", bpt);
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


	n->showflag |= SHOW_VALUE;
	window_node_draw(n);

}
/*************************************************************************/
void chg_label(root)
struct node *root;
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
		Sprintf(lbuf,"cannot find name - chg_name {%s}", bpt);
		warn(lbuf);
		return;
	}

    /* change the labels */
	for (i=0; i<n->numdim; i++)
	{
		for (ept++, bpt=ept; *ept != ';'; ept++);
		*ept = '\0';
		if( (tpt = (char*)myalloc(strlen(bpt)+1)) == 0)
		{
			Sprintf(lbuf,"can't myalloc label - chg_label {%s}",
						 bpt);
			warn(lbuf);
			return;
		}
		strcpy(tpt,bpt);
		myfree(n->labels[i]);
		n->labels[i] = tpt;
	}
	n->showflag |= SHOW_LABEL;
	sizenode(n);
	bfree(n->image);
	initwindow(n);
	tilenode(n->parent);
	window_node_draw(n->parent);
	window_node_draw(n);
}
/*************************************************************************/
void chg_axis(root)
struct node *root;
{
	char *buf, *bpt, *ept, *tpt;
	char *temp;
	float v;
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
		Sprintf(lbuf,"cannot find name - chg_name {%s}", bpt);
		warn(lbuf);
		return;
	}

    /* clear all values */
	n->numvalues = 0;

    /* for each dimension */
	for (i=0; i<n->numdim; i++)
	{

		bpt = ept;
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
		temp = n->dfmt[i];
		if( (n->dfmt[i] = (char*)myalloc(strlen(bpt)+1)) == 0)
		{
			Sprintf(lbuf,
				"can't myalloc dfmt %d - chg_axis {%s}",i ,bpt);
			warn(lbuf);
			n->dfmt[i] = temp;
			return;
		}
		myfree(temp);
		strcpy(n->dfmt[i], bpt);

		for (ept++,bpt = ept; *ept != ';'; ept++);
		*ept = '\0';
		temp = n->labels[i];
		if( (n->labels[i] = (char*)myalloc(strlen(bpt)+1)) == 0)
		{
			Sprintf(lbuf,
				"can't myalloc labels %d - dparse {%s}",i ,bpt);
			warn(lbuf);
			n->labels[i] = temp;
			return;
		}
		myfree(temp);
		strcpy(n->labels[i], bpt);

		ept++;

		for (bpt = ept; *ept != ';'; ept++);
		*ept = '\0';
		temp = n->dscalelab[i];
		if( (n->dscalelab[i] = (char*)myalloc(strlen(bpt)+1)) == 0)
		{
			Sprintf(lbuf,
				"can't myalloc dsclab %d - dparse {%s}",i ,bpt);
			warn(lbuf);
			n->dscalelab[i] = temp;
			return;
		}
		myfree(temp);
		strcpy(n->dscalelab[i], bpt);

	}

/*
	sizenode(n);
	bfree(n->image);
	initwindow(n);
	tilenode(n->parent);
	window_node_draw(n->parent);
*/
	window_node_draw(n);
}
/*************************************************************************/
void chg_name(root)
struct node *root;
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
		Sprintf(lbuf,"cannot find name - chg_name {%s}", bpt);
		warn(lbuf);
		return;
	}

	

    /* try to change the name */
        /* parse the new name */
	bpt = ept+1;
	for (ept=bpt; *ept != ';'; ept++);
	*ept = '\0';

	if( (tpt = (char*)myalloc(strlen(bpt)+1)) == 0)
	{
		Sprintf(lbuf,"cannot myalloc space - chg_name {%s}", bpt);
		warn(lbuf);
		return;
	}
	strcpy(tpt,bpt);
	myfree(n->name);
	n->name = tpt;
	n->showflag |= SHOW_NAME;
	sizenode(n);
	bfree(n->image);
	initwindow(n);
	tilenode(n->parent);
	window_node_draw(n->parent);
	window_node_draw(n);
}
/*************************************************************************/
struct node *findname(root,s)
struct node *root;
char *s;
{
	int i;
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
struct node *gofindname(root,s)
struct node *root;
char *s;
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
void printnode(n)
struct node *n;
{
	int i,j,k;

	
	Lprintf("\nofficialname: <<%s>> username: (%s) ",n->oname, n->name);
	Lprintf("nch: %d w: %d mw: %d st: %d  dim: %d\n",
		n->numchildren, n->numvalues,
		n->maxnumvalues, n->style, n->numdim);

    /* now get rid of our stuff */
	switch (n->type)
	{
	case PANEL:
		break;
	case CLUSTER:
		break;
	case DISPLAY:
		for (k=0; k<n->numdim; k++)
			Lprintf("mn: %f mx: %f fmt: %s lab: %s\n",
				n->dmin[k],n->dmax[k],n->dfmt[k],n->labels[k]);
		Lprintf("DATA:");
		for (i=0; i<n->numvalues; i++)
		{
			for(k=0; k<n->numdim; k++)
				Lprintf("	%f",n->data[k][i]);
			Lprintf("\n");
		}
		break;
	case FWINT:
	case VWINT:
	case FWFLT:
	case VWFLT:
		Lprintf("mn: %f mx: %f\n", n->min, n->max);
		for (k=0; k<n->numvalues; k++)
			Lprintf("val %d: %f\n",k,n->value[k]);
		break;
	case ASCKNOB:
		for (k=0; k<3; k++)
			Lprintf("%s\n",n->labels[k]);
		break;
	case ENUM:
		Lprintf("mn: %f mx: %f\n", n->min, n->max);
		for (k=0; k<n->numdim; k++)
			Lprintf("labels[%d]: %s\n",k, n->labels[k]);
		for (k=0; k<n->numvalues; k++)
			Lprintf("val %d: %f\n",k,n->value[k]);
		break;
	default:
		warn("unknown type in printnode");
	}

}
/*************************************************************************/
void clearnode(n)
struct node *n;
{
	int i,j,k;


    /* get rid of all children first */
	if (n->numchildren != 0)
	{
		for(i=0; i<n->numchildren; i++)
			clearnode(n->child[i]);
	}

    /* get rid of any scroll bars on the window */
	if (n->window_flag & WB_HSCR)
		bfree(n->sbar[HORIZ]);
	if (n->window_flag & WB_VSCR)
		bfree(n->sbar[VERT]);
	if (n->window_flag & (WB_VSCR || WB_HSCR))
		bfree(n->sbar[RESHAPE]);

    /* now get rid of our stuff */
	switch (n->type)
	{
	case PANEL:
		myfree(n->child);
		myfree(n->name);
		myfree(n->fmt);
		myfree(n->oname);
		bfree(n->image);
		myfree(n);
		break;
	case CLUSTER:
		myfree(n->child);
		myfree(n->name);
		myfree(n->fmt);
		myfree(n->oname);
		bfree(n->image);
		myfree(n);
		break;
	case DISPLAY:
		for(i=0; i<n->numdim; i++)
		{
			myfree(n->dfmt[i]);
			myfree(n->data[i]);
			myfree(n->labels[i]);
			myfree(n->dscalelab[i]);
		}
		myfree(n->dscalelab);
		myfree(n->data);
		myfree(n->dfmt);
		myfree(n->labels);
		myfree(n->dmin);
		myfree(n->dmax);
		myfree(n->name);
		myfree(n->fmt);
		myfree(n->oname);
		bfree(n->image);
		myfree(n);
		break;
	case FWINT:
	case VWINT:
	case FWFLT:
	case VWFLT:
		myfree(n->scalelab);
		myfree(n->value);
		myfree(n->name);
		myfree(n->fmt);
		myfree(n->oname);
		bfree(n->image);
		myfree(n);
		break;
	case ASCDISP:
		myfree(n->value);
		myfree(n->dmin);
		myfree(n->dmax);
		myfree(n->name);
		myfree(n->fmt);
		myfree(n->oname);
		bfree(n->image);
		myfree(n);
		break;
	case ASCKNOB:
		myfree(n->labels[0]);
		myfree(n->labels[1]);
		myfree(n->labels[2]);
		myfree(n->labels);
		myfree(n->name);
		myfree(n->fmt);
		myfree(n->oname);
		myfree(n);
		break;
	case ENUM:
		for(i=0; i<n->numdim; i++)
		{
			myfree(n->labels[i]);
		}
		myfree(n->value);
		myfree(n->name);
		myfree(n->fmt);
		myfree(n->oname);
		bfree(n->image);
		myfree(n);
		break;
	default:
		warn("unknown type in clearnode");
	}

}



/*************************************************************************/
struct node* nodeload()
{
	int done, i;
	char *buf;
	struct node *newnode;
	struct node *nodestack[MAXNODESTACK];
	int stacktop;
	struct node *pparse();
	struct node *cparse();
	struct node *dparse();
	struct node *kparse();
	struct node *akparse();
	struct node *adparse();
	struct node *eparse();

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
			sizenode(newnode);
			initwindow(newnode);
			tilenode(newnode);
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
			sizenode(newnode);
			initwindow(newnode);
			tilenode(newnode);
			nodestack[stacktop++] = newnode;
			break;
		case  DISPLAY:
			newnode = dparse(buf); 
			sizenode(newnode);
			initwindow(newnode);
			nodestack[stacktop++] = newnode;
			break;
		case  FWINT:
		case  VWINT:
		case  FWFLT:
		case  VWFLT:
			newnode = kparse(buf); 
			sizenode(newnode);
			initwindow(newnode);
			nodestack[stacktop++] = newnode;
			break;
		case  ASCKNOB:
			newnode = akparse(buf); 
			sizenode(newnode);
			initwindow(newnode);
			nodestack[stacktop++] = newnode;
			break;
		case  ASCDISP:
			newnode = adparse(buf); 
			sizenode(newnode);
			initwindow(newnode);
			nodestack[stacktop++] = newnode;
			break;
		case  ENUM:
			newnode = eparse(buf); 
			sizenode(newnode);
			initwindow(newnode);
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
		wait(RCV);
		if( (c = rcvchar()) == -1)
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

	/* send the throttle character */
	if(proto_mode != 0)
		sendchar('\n');


	*bp = '\0';
	return(hbuf);
}

/*******************************************************/
struct node *comparse(buf)
char *buf;
{
	char *bpt;
	char *ept;
	struct node *n;

    /* create a node */
	if( (n=(struct node*)myalloc(sizeof(struct node))) == NULLNP )
	{
		Sprintf(lbuf,"cannot myalloc node - comparse {%s}", buf);
		warn(lbuf);
		return(NULLNP);
	}


    /* save the type */
	n->type = buf[0];

    /* parse the name */
	bpt = buf;
	bpt++;
	for (ept=bpt; *ept != ';'; ept++);
	*ept = '\0';
	if( (n->name = (char*)myalloc(strlen(bpt)+1)) == 0)
	{
		Sprintf(lbuf,"cannot myalloc name - comparse {%s}", bpt);
		warn(lbuf);
		myfree(n);
		return(NULLNP);
	}
	strcpy(n->name, bpt);

    /* parse the officialname */
	ept++;
	for (bpt=ept; *ept != ';'; ept++);
	*ept = '\0';
	if( (n->oname = (char*)myalloc(strlen(bpt)+1)) == 0)
	{
		Sprintf(lbuf,"cannot myalloc officialname - comparse {%s}", bpt);
		warn(lbuf);
		myfree(n->name);
		myfree(n);
		return(NULLNP);
	}
	strcpy(n->oname, bpt);

    /* parse the labeling format */
	ept++;
	for (bpt=ept; *ept != ';'; ept++);
	*ept = '\0';
	if( (n->fmt = (char*)myalloc(strlen(bpt)+1)) == 0)
	{
		Sprintf(lbuf,"cannot myalloc format - comparse {%s}", bpt);
		warn(lbuf);
		myfree(n->oname);
		myfree(n->name);
		myfree(n);
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
struct node *pparse(buf)
char *buf;
{
	char *bpt;
	struct node *n;

    /* create a node */
	if( (n=(struct node*)comparse(buf)) == NULLNP )
	{
		warn("cannot myalloc memory - pparse");
		return(NULLNP);
	}

    /* myallocate storage for children */
	if( (n->child =
	    (struct node**)myalloc(sizeof(struct node*))) == 0)
	{
		Sprintf(lbuf,"cannot myalloc child ptr - pparse {%s}", bpt);
		warn(lbuf);
		myfree(n->name);
		myfree(n);
		return(NULLNP);
	}

    /* done parsing */
	return(n);

}

/*******************************************************/
struct node *cparse(buf)
char *buf;
{
	char *bpt;
	struct node *n;

    /* create a node */
	if( (n=(struct node*)comparse(buf)) == NULLNP )
	{
		warn("cannot myalloc memory - cparse");
		return(NULLNP);
	}

    /* myallocate storage for children */
	if( (n->child =
	    (struct node**)myalloc(sizeof(struct node*)*n->numchildren)) == 0)
	{
		Sprintf(lbuf,"cannot myalloc child ptr - cparse {%s}", bpt);
		warn(lbuf);
		myfree(n->name);
		myfree(n);
		return(NULLNP);
	}

    /* done parsing */
	return(n);

}

/*******************************************************/
struct node *dparse(buf)
char *buf;
{
	char *bpt;
	char *ept;
	struct node *n;
	int i, j, k;
	float v;

    /* create a node */
	if( (n=(struct node*)comparse(buf)) == NULLNP )
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
	if( (n->dfmt = (char**)myalloc(sizeof(char*)*n->numdim)) == 0)
	{
		Sprintf(lbuf,"cannot myalloc dfmt - dparse {%s}", buf);
		warn(lbuf);
		myfree(n->fmt);
		myfree(n->oname);
		myfree(n->name);
		myfree(n);
		return(NULLNP);
	}
	if( (n->dmin = (float*)myalloc(sizeof(float)*n->numdim)) == 0)
	{
		Sprintf(lbuf,"cannot myalloc dmin - dparse {%s}", buf);
		warn(lbuf);
		myfree(n->dfmt);
		myfree(n->fmt);
		myfree(n->oname);
		myfree(n->name);
		myfree(n);
		return(NULLNP);
	}
	if( (n->dmax = (float*)myalloc(sizeof(float)*n->numdim)) == 0)
	{
		Sprintf(lbuf,"cannot myalloc max - dparse {%s}", buf);
		warn(lbuf);
		myfree(n->dmin);
		myfree(n->dfmt);
		myfree(n->fmt);
		myfree(n->oname);
		myfree(n->name);
		myfree(n);
		return(NULLNP);
	}
	if( (n->data = (float**)myalloc(sizeof(float*)*n->numdim)) == 0)
	{
		Sprintf(lbuf,"cannot myalloc data - dparse {%s}", buf);
		warn(lbuf);
		myfree(n->dmax);
		myfree(n->dmin);
		myfree(n->dfmt);
		myfree(n->fmt);
		myfree(n->oname);
		myfree(n->name);
		myfree(n);
		return(NULLNP);
	}
	if( (n->labels = (char**)myalloc(sizeof(char*)*n->numdim)) == 0)
	{
		Sprintf(lbuf,"cannot myalloc labels - dparse {%s}", buf);
		warn(lbuf);
		myfree(n->data);
		myfree(n->dmax);
		myfree(n->dmin);
		myfree(n->dfmt);
		myfree(n->fmt);
		myfree(n->oname);
		myfree(n->name);
		myfree(n);
		return(NULLNP);
	}
	if( (n->dscalelab = (char**)myalloc(sizeof(char*)*n->numdim)) == 0)
	{
		Sprintf(lbuf,"cannot myalloc scalelabels - dparse {%s}", buf);
		warn(lbuf);
		myfree(n->labels);
		myfree(n->data);
		myfree(n->dmax);
		myfree(n->dmin);
		myfree(n->dfmt);
		myfree(n->fmt);
		myfree(n->oname);
		myfree(n->name);
		myfree(n);
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
		if( (n->dfmt[i] = (char*)myalloc(strlen(bpt)+1)) == 0)
		{
			Sprintf(lbuf,
				"can't myalloc dfmt %d - dparse {%s}",i ,bpt);
			warn(lbuf);
			for(j=0; j<i; j++)
			{
				myfree(n->dfmt[j]);
				myfree(n->data[j]);
				myfree(n->labels[j]);
				myfree(n->dscalelab[j]);
			}
			myfree(n->dscalelab);
			myfree(n->data);
			myfree(n->dmax);
			myfree(n->dmin);
			myfree(n->dfmt);
			myfree(n->labels);
			myfree(n->name);
			myfree(n->fmt);
			myfree(n->oname);
			myfree(n);
			return(NULLNP);
		}
		strcpy(n->dfmt[i], bpt);

		for (ept++,bpt = ept; *ept != ';'; ept++);
		*ept = '\0';
		if( (n->labels[i] = (char*)myalloc(strlen(bpt)+1)) == 0)
		{
			Sprintf(lbuf,
				"can't myalloc labels %d - dparse {%s}",i ,bpt);
			warn(lbuf);
			for(j=0; j<i; j++)
			{
				myfree(n->dfmt[j]);
				myfree(n->data[j]);
				myfree(n->labels[j]);
				myfree(n->dscalelab[j]);
			}
			myfree(n->dfmt[j]);
			myfree(n->dscalelab);
			myfree(n->data);
			myfree(n->dmax);
			myfree(n->dmin);
			myfree(n->dfmt);
			myfree(n->labels);
			myfree(n->name);
			myfree(n->fmt);
			myfree(n->oname);
			myfree(n);
			return(NULLNP);
		}
		strcpy(n->labels[i], bpt);

		ept++;

		for (bpt = ept; *ept != ';'; ept++);
		*ept = '\0';
		if( (n->dscalelab[i] = (char*)myalloc(strlen(bpt)+1)) == 0)
		{
			Sprintf(lbuf,
				"can't myalloc dsclab %d - dparse {%s}",i ,bpt);
			warn(lbuf);
			for(j=0; j<i; j++)
			{
				myfree(n->dfmt[j]);
				myfree(n->data[j]);
				myfree(n->labels[j]);
				myfree(n->dscalelab[j]);
			}
			myfree(n->labels[j]);
			myfree(n->dfmt[j]);
			myfree(n->dscalelab);
			myfree(n->data);
			myfree(n->dmax);
			myfree(n->dmin);
			myfree(n->dfmt);
			myfree(n->labels);
			myfree(n->name);
			myfree(n->fmt);
			myfree(n->oname);
			myfree(n);
			return(NULLNP);
		}
		strcpy(n->dscalelab[i], bpt);

		if( (n->data[i]=
			(float*)myalloc(sizeof(float)*n->maxnumvalues)) == 0)
		{
			Sprintf(lbuf,
				"can't myalloc data %d - dparse {%s}",i ,bpt);
			warn(lbuf);
			for(j=0; j<i; j++)
			{
				myfree(n->dfmt[j]);
				myfree(n->data[j]);
				myfree(n->labels[j]);
				myfree(n->dscalelab[j]);
			}
			myfree(n->dfmt[j]);
			myfree(n->labels[j]);
			myfree(n->dscalelab[j]);
			myfree(n->dscalelab);
			myfree(n->data);
			myfree(n->dmax);
			myfree(n->dmin);
			myfree(n->dfmt);
			myfree(n->labels);
			myfree(n->name);
			myfree(n->fmt);
			myfree(n->oname);
			myfree(n);
			return(NULLNP);
		}

		bpt = ept;
	}

	n->element_width = 0;		/* indicate display initialization */

    /* done parsing */
	return(n);
	
}

/*******************************************************/
struct node *kparse(buf)
char *buf;
{
	char *bpt, *ept;
	struct node *n;
	float v;
	int i, j;

    /* create a node */
	if( (n=(struct node*)comparse(buf)) == NULLNP )
	{
		warn("cannot myalloc memory - kparse");
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
		Sprintf(lbuf,"error - knob <%s>, MIN > MAX; swapping");
		warn(lbuf);
		v = n->min;
		n->min = n->max;
		n->max = v;
	}

    /* get the scale label for the knob */
	bpt++;
	for (ept=bpt; *ept != ';'; ept++);
	*ept = '\0';

	if( (n->scalelab=(char *)myalloc(strlen(bpt)+1)) == 0)
	{
		Sprintf(lbuf,"cannot myalloc scale label - kparse {%s}", buf);
		warn(lbuf);
		myfree(n->name);
		myfree(n->fmt);
		myfree(n->oname);
		myfree(n);
		return(NULLNP);
	}
	strcpy(n->scalelab,bpt);
	bpt = ept;

    /* get the value(s) of the knob */
	if( (n->value=(float*)myalloc(sizeof(float)*n->maxnumvalues)) == 0)
	{
		Sprintf(lbuf,"cannot myalloc values - kparse {%s}", buf);
		warn(lbuf);
		myfree(n->scalelab);
		myfree(n->name);
		myfree(n->fmt);
		myfree(n->oname);
		myfree(n);
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

    /* allocate knob slide Bitmaps */
	i = (n->maxnumvalues + 2) * 32;
	if( ((n->knobslide).base = (Word*)myalloc(sizeof(Word)*i)) == 0)
	{
		Sprintf(lbuf,"cannot myalloc knobslide Bitmaps- kparse {%s}",
			 n->oname);
		warn(lbuf);
		myfree(n->scalelab);
		myfree(n->value);
		myfree(n->name);
		myfree(n->fmt);
		myfree(n->oname);
		myfree(n);
		return(NULLNP);
	}

    /* done parsing */
	return(n);
	
}


/*******************************************************/
struct node *adparse(buf)
char *buf;
{
	char *bpt, *ept;
	struct node *n;
	float v;
	int i, j;

    /* create a node */
	if( (n=(struct node*)comparse(buf)) == NULLNP )
	{
		warn("cannot myalloc memory - adparse");
		return(NULLNP);
	}

    /* skip over the common data in buffer */
	for (bpt=buf; *bpt!=';'; bpt++);

    /* parse the style */
	bpt++;
	n->style = atoi(bpt);
	for (; *bpt!=';'; bpt++);

    /* allocate special items for cursor tracking and scroll */
		/* AD_CXY */
	if((n->dmin = (float*)myalloc(sizeof(Point))) == 0)
	{
		Sprintf(lbuf,"cannot myalloc cursor XY tracking - adparse {%s}",
			 n->oname);
		warn(lbuf);
		myfree(n->name);
		myfree(n->fmt);
		myfree(n->oname);
		myfree(n);
		return(NULLNP);
	}
		/* AD_CPT */
	if((n->dmax = (float*)myalloc(sizeof(Point))) == 0)
	{
		Sprintf(lbuf,"cannot myalloc cursor PT tracking - adparse {%s}",
			 n->oname);
		warn(lbuf);
		myfree(n->dmin);
		myfree(n->name);
		myfree(n->fmt);
		myfree(n->oname);
		myfree(n);
		return(NULLNP);
	}
		/* AD_CMAP */
	if((n->value = (float*)myalloc(sizeof(Rectangle))) == 0)
	{
		Sprintf(lbuf,"cannot myalloc scroll region box - adparse {%s}",
			 n->oname);
		warn(lbuf);
		myfree(n->dmin);
		myfree(n->dmax);
		myfree(n->name);
		myfree(n->fmt);
		myfree(n->oname);
		myfree(n);
		return(NULLNP);
	}


    /* done parsing */
	return(n);
	
}

/*******************************************************/
struct node *akparse(buf)
char *buf;
{
	char *bpt, *ept;
	struct node *n;
	float v;
	int i, j;

    /* create a node */
	if( (n=(struct node*)comparse(buf)) == NULLNP )
	{
		warn("cannot myalloc memory - akparse");
		return(NULLNP);
	}

    /* skip over the common data in buffer */
	for (bpt=buf; *bpt!=';'; bpt++);

    /* parse the style */
	bpt++;
	n->style = atoi(bpt);
	for (; *bpt!=';'; bpt++);


    /* allocate pointers for strings */
	if( (n->labels=(char **)myalloc(sizeof(char *)*3)) == 0)
	{
		Sprintf(lbuf,"cannot myalloc string pointers - akparse {%s}", buf);
		warn(lbuf);
		myfree(n->name);
		myfree(n->fmt);
		myfree(n->oname);
		myfree(n);
		return(NULLNP);
	}

    /* get the question for the knob */
	bpt++;
	for (ept=bpt; *ept != ';'; ept++);
	*ept = '\0';

	if( (n->labels[0]=(char *)myalloc(strlen(bpt)+1)) == 0)
	{
		Sprintf(lbuf,"cannot myalloc question string - akparse {%s}", buf);
		warn(lbuf);
		myfree(n->name);
		myfree(n->fmt);
		myfree(n->oname);
		myfree(n->labels);
		myfree(n);
		return(NULLNP);
	}
	strcpy(n->labels[0],bpt);
	bpt = ept;

    /* get the aid string for the knob */
	bpt++;
	for (ept=bpt; *ept != ';'; ept++);
	*ept = '\0';

	if( (n->labels[1]=(char *)myalloc(strlen(bpt)+1)) == 0)
	{
		Sprintf(lbuf,"cannot myalloc aid string - akparse {%s}", buf);
		warn(lbuf);
		myfree(n->name);
		myfree(n->fmt);
		myfree(n->oname);
		myfree(n->labels[0]);
		myfree(n->labels);
		myfree(n);
		return(NULLNP);
	}
	strcpy(n->labels[1],bpt);
	bpt = ept;

    /* get the current answer for the knob */
	bpt++;
	for (ept=bpt; *ept != ';'; ept++);
	*ept = '\0';

	if( (n->labels[2]=(char *)myalloc(n->maxnumvalues+1)) == 0)
	{
		Sprintf(lbuf,"cannot myalloc answer string - akparse {%s}", buf);
		warn(lbuf);
		myfree(n->name);
		myfree(n->fmt);
		myfree(n->oname);
		myfree(n->labels[0]);
		myfree(n->labels[1]);
		myfree(n->labels);
		myfree(n);
		return(NULLNP);
	}
	strcpy(n->labels[2],bpt);


    /* done parsing */
	return(n);
	
}

/*******************************************************/
struct node *eparse(buf)
char *buf;
{
	char *bpt;
	char *ept;
	struct node *n;
	int i,j;

    /* create a node */
	if( (n=(struct node*)comparse(buf)) == NULLNP )
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
	if( (n->labels = (char**)myalloc(sizeof(char*)*n->numdim)) == 0)
	{
		Sprintf(lbuf,"cannot myalloc labelptr - eparse {%s}", buf);
		warn(lbuf);
		myfree(n->name);
		myfree(n->fmt);
		myfree(n->oname);
		myfree(n);
		return(NULLNP);
	}
	ept = bpt;
	for (i=0; i<n->numdim; i++)
	{
		for (ept++,bpt=ept; *ept != ';'; ept++);
		*ept = '\0';
		if( (n->labels[i] = (char*)myalloc(strlen(bpt)+1)) == 0)
		{
			Sprintf(lbuf,"cannot myalloc labels - eparse {%s}",
								 bpt);
			warn(lbuf);
			for(j=0; j<i; j++)
				myfree(n->labels[j]);
			myfree(n->labels);
			myfree(n->name);
			myfree(n->fmt);
			myfree(n->oname);
			myfree(n);
			return(NULLNP);
		}
		strcpy(n->labels[i], bpt);
	}

    /* get the value(s) of the knob */
	if( (n->value = (float*)myalloc(sizeof(float)*n->maxnumvalues)) == 0)
	{
		Sprintf(lbuf,"cannot myalloc values - eparse {%s}", buf);
		warn(lbuf);
		for(j=0; j<n->numdim; j++)
			myfree(n->labels[j]);
		myfree(n->labels);
		myfree(n->name);
		myfree(n->fmt);
		myfree(n->oname);
		myfree(n);
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

    /* allocate knob slide Bitmaps */
	i = (n->maxnumvalues + 2) * 32;
	if( ((n->knobslide).base = (Word*)myalloc(sizeof(Word)*i)) == 0)
	{
		Sprintf(lbuf,"cannot myalloc knobslide Bitmaps- eparse {%s}",
			 n->oname);
		warn(lbuf);
		for(j=0; j<n->numdim; j++)
			myfree(n->labels[j]);
		myfree(n->labels);
		myfree(n->value);
		myfree(n->name);
		myfree(n->fmt);
		myfree(n->oname);
		myfree(n);
		return(NULLNP);
	}

    /* done parsing */
	return(n);
	
}

/*************************************************************************/
