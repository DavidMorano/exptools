
/**************************************************************************/
/* PANELFEATURES Package    Release:  1.0    Release Date: 1/15/89        */
/*                          Provider: J. D. Iorio  (speedy!jdi)           */
/**************************************************************************/

/*
*	(C) Copyright ATT 1988
*
*	giutil.c -
*
* A collection of graphics calculation routines for the 630 terminal
* in conjunction with the panelfeature package in ALMMS:
*
*
*/

#include <dmd.h>
#include <font.h>
#include "gi.h"
#include "giwindow.h"

/********************************************************************/

extern struct node *currentnode;	/* currently displayed node */

extern void warn();
extern void window_node_draw();
extern void initscroll();
extern char lbuf[];


void makevalue();

/********************************************************************
* tilenode(node *n)
*
*	This routine computes the origins of the children of a node
* so that all elements of the node are displayed properly
*********************************************************************/
void tilenode(n)
struct node *n;
{
	int i;
	Rectangle display_area, trial;
	Point curpt;
	int maxy, m;
	int w, h, da_w, da_h;
	struct node *ch;


    /* initialize the allowable display region and current point*/
	display_area = canon (Pt(MINX,MINY),Pt(MAXX,MAXY));
	curpt = fPt(MINX+GUARDX,MINY+GUARDY);
	maxy = MINY+GUARDY;
	da_w = MAXX-MINX;
	da_h = MAXY-MINY;


	for (i=0; i<n->numchildren; i++)
	{
		ch = n->child[i];

    	    /* if object too wide and scrollable, resize window */
		w = ch->window_rect.corner.x - ch->window_rect.origin.x;
		if( (w > (da_w/2)) && ((ch->window_flag & NO_HSCR)== 0))
		{
			ch->window_rect.corner.x = 
				ch->window_rect.origin.x + (da_w/2) - 32; 
			ch->window_rect.corner.y += WBH;
			ch->window_flag &= ~W_INIT;
			ch->window_flag |= WB_HSCR;
		}

    	    /* if object too high and scrollable, resize window */
		h = ch->window_rect.corner.y - ch->window_rect.origin.y;
		if( (h > (da_h/2)) && ((ch->window_flag & NO_VSCR)== 0))
		{
			ch->window_rect.corner.y = 
				ch->window_rect.origin.y + (da_h/2) - 32; 
			ch->window_rect.corner.x += WBW;
			ch->window_flag &= ~W_INIT;
			ch->window_flag |= WB_VSCR;
		}

	    /* if resized, then call redraw to recompute sizes */
		if ((ch->window_flag & W_INIT) == 0)
		{
		   /* allocate scroll bars */
			initscroll(ch);
			window_node_draw(ch);
		}

		trial = raddp(ch->window_rect,curpt);

	    /* if it does not fit on this line */
		if (trial.corner.x > (MAXX-GUARDX))
		{
		    /* put it on the next line */
			curpt = fPt(MINX+GUARDX, maxy);
			trial = raddp(ch->window_rect,curpt);
		}
		
	    /* place it */
		ch->rel_to_origin = curpt;
	    /* move the current pointer to end on same line */
		curpt.x = trial.corner.x + GUARDX;
	    /* update maximum bottom point for this line */
		m = trial.corner.y + GUARDY;
		maxy = (m>maxy) ? m : maxy;
		
	}
}


/********************************************************************
* sizenode(node *n)
*
*	This routine computes the default size of a node icon or display
* so that all elements of the node are displayed properly
* Initialization of window parameters is done to show the entire
* object on the screen.  Tilenode() and window_node_draw() may
* later override this setting
*********************************************************************/

void sizenode(n)
struct node *n;
{
	int i,j,k;
	int maxwidth;
	char *c;

	switch (n->type)
	{
	case PANEL:
		n->image_size = PANEL_AREA;

		 /* if the panel name is still longer use its length */
		maxwidth = n->image_size.corner.x - n->image_size.origin.x;
		i = strwidth(&mediumfont,n->name) + 28;
		if (i > maxwidth)
			n->image_size.corner.x = n->image_size.origin.x + i;

		/* use a single subwindow */
		n->window_rect = n->image_size;
		n->window_flag = NOBORDER | NO_VSCR | NO_HSCR | W_INIT;
		break;
	case CLUSTER:
		n->image_size = CLUSTER_AREA;

		 /* if the cluster name is still longer use its length */
		maxwidth = n->image_size.corner.x - n->image_size.origin.x;
		i = strwidth(&mediumfont,n->name) + 28;
		if (i > maxwidth)
			n->image_size.corner.x = n->image_size.origin.x + i;

		/* use a single subwindow */
		n->window_rect = n->image_size;
		n->window_flag = NOBORDER | NO_VSCR | NO_HSCR | W_INIT;
		break;

	case DISPLAY:

		/* determine the data size */
	
		if((n->window_flag & WB_PLOT) == 0)
		{
		    /* if not a plot */
			n->element_width = n->numdim * 100;

			/* make the basic shape */
			n->image_size.origin = fPt(0,0);
			n->image_size.corner.y = n->maxnumvalues * TEXT_HEIGHT;
			n->image_size.corner.x = n->element_width + (2*GUARDX);
		}
		else
		{
			/* make the plot shape */
			if(n->numdim < 3)
			{
				n->image_size.origin = fPt(0,0);
				n->image_size.corner.y = 300;
				n->image_size.corner.x = 300 + (2*GUARDX);
			}
			else
			{
				n->image_size.origin = fPt(0,0);
				n->image_size.corner.y = 500;
				n->image_size.corner.x = 500 + (2*GUARDX);
			}

		}
		/* if display name is still longer use its length */
		maxwidth = n->image_size.corner.x - n->image_size.origin.x;
		i = strwidth(&mediumfont,n->name) + 24 + GUARDX;
		if (i > maxwidth)
			n->image_size.corner.x = n->image_size.origin.x + i;
	
		/* add on for the name and border */
		n->image_size.corner.y += 3*(TEXT_HEIGHT+4)+(2*GUARDY);

		/*add on for optional style labels line*/
		n->image_size.corner.y += TEXT_HEIGHT+8;
	
		/* use a single subwindow */
		n->window_rect = n->image_size;
		n->element_width = n->image_size.corner.x -
					 n->image_size.origin.x;

		/* save plot status but init all other flags */
		n->window_flag &= WB_PLOT;
		n->window_flag |= (NOBORDER | W_INIT | WB_UTIL);

		/* eliminate plot/text toggle for one elem. displays */
		if ((n->numdim == 1) && (n->maxnumvalues == 1))
			n->window_flag &= ~WB_UTIL;
			
		break;

	case FWINT:
	case FWFLT:
	case VWINT:
	case VWFLT:
		/*find width of longest label*/
		makevalue(lbuf,n->fmt,n->max+.000001);
		i = strwidth(&TEXT_FONT,lbuf);
		makevalue(lbuf,n->fmt,n->min-.000001);
		j = strwidth(&TEXT_FONT,lbuf);
		j = (i>j) ? i : j;

		Sprintf(lbuf,"%s",n->scalelab);
		   /* omitting trailing blanks */
		for (c=lbuf; *c != ' '; c++);
			*c = '\0';
		i = strwidth(&TEXT_FONT,lbuf);
		maxwidth = (i>j) ? i : j;

		maxwidth = (maxwidth>VKNOB_WIDTH) ? maxwidth : VKNOB_WIDTH;

		maxwidth += 2;
		n->element_width = maxwidth;

		n->image_size.origin = fPt(0,0);
		n->image_size.corner.y = VKNOB_HEIGHT;
		n->image_size.corner.x = maxwidth * n->maxnumvalues;
	    	
		  /*add on for name and value lines*/
		n->image_size.corner.y += 2*TEXT_HEIGHT+GUARDY;
		  /*add on for label spaces*/
		n->image_size.corner.x += maxwidth + 4;

		 /* if the knob name is still longer use its length */
		maxwidth = n->image_size.corner.x - n->image_size.origin.x;
		i = strwidth(&mediumfont,n->name) + 28;
		if (i > maxwidth)
			n->image_size.corner.x = n->image_size.origin.x + i;

		if ((n->type == VWINT) || (n->type == VWFLT))
		{
		   /* if variable width add size knob */
			n->image_size.corner.y += HKNOB_HEIGHT + GUARDY;
		}

		/* use a single subwindow */
		n->window_rect = n->image_size;
		n->window_flag = NOBORDER | NO_VSCR | W_INIT;
		/* if large enough, add the slope utility icon */
		if (n->maxnumvalues >= 3)
			n->window_flag |= WB_UTIL;
		
		break;

	case ASCKNOB:
		/* find the longest label */
		i = strwidth(&mediumfont,n->name)+28;
				/* the question */
		j = strwidth(&TEXT_FONT,n->labels[0]);
		maxwidth = (i>j) ? i : j;
				/* the aid string */
		j = strwidth(&TEXT_FONT,n->labels[1]);
		maxwidth = (maxwidth>j) ? maxwidth : j;
				/* the answer string */
		for(j=0; j<n->maxnumvalues; j++)
			lbuf[j] = 'm';
		lbuf[j] = '\0';
		j = strwidth(&TEXT_FONT,lbuf);
		n->element_width = j;

		maxwidth = (maxwidth>j) ? maxwidth : j;


		/* setup the image window */
		n->image_size.origin = fPt(0,0);
		n->image_size.corner.y = 4 * TEXT_HEIGHT+GUARDY+8;
		n->image_size.corner.x = maxwidth + 4;


		/* use a single subwindow */
		n->window_rect = n->image_size;
		n->window_flag = NOBORDER | NO_VSCR | W_INIT;

		
		break;

	case ASCDISP:

		/* determine the data size */
	
		n->element_width = n->numvalues * 7;  /* cell width */

		/* make the basic shape */
		n->image_size.origin = fPt(0,0);
		n->image_size.corner.y = n->maxnumvalues * 14;  /*cell height*/
		n->image_size.corner.x = n->element_width + (2*GUARDX);

		/* if display name is still longer use its length */
		maxwidth = n->image_size.corner.x - n->image_size.origin.x;
		i = strwidth(&mediumfont,n->name) + 24 + GUARDX;
		if (i > maxwidth)
			n->image_size.corner.x = n->image_size.origin.x + i;
	
		/* add on for the name and border */
		n->image_size.corner.y += TEXT_HEIGHT+(3*GUARDY);

		/* use a single subwindow */
		n->window_rect = n->image_size;

		/* init all other flags */
		n->window_flag = (NOBORDER | W_INIT);

		/* special case - use these to track the cursor */
			/* the image area on the storage blit */
		AD_CMAP = fRpt(add(n->image_size.origin,
				Pt(GUARDX,2*GUARDY+TEXT_HEIGHT)),
			   sub(n->image_size.corner,Pt(GUARDX,GUARDY)));
			/* the x, y coords in characters/rows */
		AD_CXY = fPt(0,0);
			/* the x, y coords in pixels */
		AD_CPT = AD_CMAP.origin;


		break;

		
	case ENUM:
		n->image_size.origin = fPt(0,0);
		n->image_size.corner.y = TEXT_HEIGHT * 2 * n->numdim;
		n->image_size.corner.x = VKNOB_WIDTH + 2;
	    	
		 /*add on for name*/
		n->image_size.corner.y += TEXT_HEIGHT+GUARDY;

		 /*add longest label*/
		for(maxwidth=0, j=0; j<n->numdim; j++)
		{
		    /*find width of longest label*/
			Sprintf(lbuf,n->fmt,n->labels[j]);
			k = strwidth(&TEXT_FONT,lbuf);
			maxwidth = (maxwidth>k)?maxwidth:k;
		}
		n->image_size.corner.x += maxwidth + 6;

		 /* if the knob name is still longer use its length */
		maxwidth = n->image_size.corner.x - n->image_size.origin.x;
		i = strwidth(&mediumfont,n->name) + 28;
		if (i > maxwidth)
			n->image_size.corner.x = n->image_size.origin.x + i;

		n->element_width = VKNOB_WIDTH;

		/* use a single subwindow */
		n->window_rect = n->image_size;
		n->window_flag = NOBORDER | NO_HSCR | W_INIT;
	}
}



/********************************************************************
* void makevalue(buf, format, value)
*
*	This routine builds a string in buf representing value using
* format.  Trailing blanks are truncated and any float to integer
* conversions are done (all values are stored as floats)
*********************************************************************/
void makevalue(buf, fmt, val)
char *buf, *fmt;
float val;
{
	int ival;
	char *c;
	int looking, flag;

	/* parse the format */
	flag = -1;
	for (looking=TRUE, c=fmt; *c != '\0'; c++)
	{
		if(looking == TRUE)
		{
			if(*c == '%')
				looking = FALSE;
			continue;
		}
		else
		{
			if(*c == '%')
			{
				looking = FALSE;
				continue;
			}
			if((*c == 'e') || (*c == 'f'))
			{
				flag = 0;
				break;
			}
			else if (*c == 'x')
			{
				flag = 1;
				break;
			}
			else if (*c == 'd')
			{
				flag = 2;
				break;
			}
			else
				;
		}
	}


	/* build the string */
	switch(flag)
	{
	case 0:
		Sprintf(buf, fmt, val);
		break;
	case 1:
		Sprintf(buf, fmt, (unsigned int)val);
		break;
	case 2:
		Sprintf(buf, fmt, (int)val);
		break;
	default:
		Sprintf(buf, "%-4.2f", val);
		warn("bad format encountered");
		break;
	}

	/* eliminate trailing blanks */
	for(c=buf; (*c != ' ') && (*c != '\0'); c++);
	*c = '\0';

}
