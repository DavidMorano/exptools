
/**************************************************************************/
/* PANELFEATURES Package    Release:  1.0    Release Date: 1/15/89        */
/*                          Provider: J. D. Iorio  (speedy!jdi)           */
/**************************************************************************/

/*
*	(C) Copyright ATT 1988
*
*	gidraw.c -
*
* A collection of graphics drawing routines for the 630 terminal
* in conjunction with the panelfeature package in ALMMS:
*  These routines place items on the screen
*
*
*/

#include <dmd.h>
#include <font.h>
#include "gi.h"
#include "giwindow.h"

/********************************************************************/

extern struct node *currentnode;	/* currently displayed node */
extern struct node *togglenode;		/* button 3 toggle node */
extern Bitmap *VKNOB, *HKNOB;
extern Bitmap *JEDI, *copyright;
extern char *logo1, *logo2, *logo3, *logodate;
extern Bitmap *SBAR;
extern char lbuf[];

extern void warn();

extern Texture16 *tweed, *kapow;

void screen_key_draw();
void screen_name_draw();
void screen_node_draw();
void screen_refresh_curnode();
void kvalue_draw();
void kvalue_undraw();
void screen_disp_values();
void screen_subwin_draw();
Rectangle knob_elem_rect();

/********************************************************************
* void screen_com_draw()
*
*	This routine draws the background of the main screen
*********************************************************************/
void screen_logo_draw()
{
	char datebuf[15];
	/* set up the credit */
	texture(&display,TITLE_BOX,&T_white,F_STORE);
	bitblt(JEDI,Rect(0,0,48,48),&display, AUTHOR_ORIG,F_STORE);
/*
	string(&largefont,"ALMMS",&display,TITLE_ORIG, F_STORE);
	string(&smallfont,"MEASURE",&display,SUBTITLE_ORIG, F_STORE);
	string(&smallfont,"Copyright",&display,CRIGHT1_ORIG, F_STORE);
	bitblt(copyright,copyright->rect,&display, CRIGHT_ORIG,F_STORE);

	string(&smallfont,"ATT 1988",&display,CRIGHT2_ORIG, F_STORE);
	string(&smallfont,"by :",&display,BY_ORIG, F_STORE);
*/
	string(&largefont,logo1,&display,TITLE_ORIG, F_STORE);
	string(&smallfont,logo2,&display,SUBTITLE_ORIG, F_STORE);
	string(&smallfont,"Copyright",&display,CRIGHT1_ORIG, F_STORE);
	bitblt(copyright,copyright->rect,&display, CRIGHT_ORIG,F_STORE);

	Sprintf(datebuf,"ATT %s",logodate);
	string(&smallfont,datebuf,&display,CRIGHT2_ORIG, F_STORE);
	string(&smallfont,logo3,&display,BY_ORIG, F_STORE);


	box(&display,TITLE_BOX,F_STORE);


}

void screen_com_draw()
{
	
	/* clear the current screen */
	texture(&display,display.rect,&T_lightgrey,F_STORE);

	/* locate the basic screen features */
	texture(&display,SCR_MSGBOX,&T_white,F_STORE);
	box(&display,SCR_MSGBOX,F_STORE);

	texture(&display,SCR_TOGBOX,&T_white,F_STORE);
	box(&display,SCR_TOGBOX,F_STORE);

	texture(&display,SCR_GOBOX,&T_white,F_STORE);
	box(&display,SCR_GOBOX,F_STORE);

	texture(&display,SCR_STOPBOX,&T_white,F_STORE);
	box(&display,SCR_STOPBOX,F_STORE);

	texture(&display,SCR_KEYBOX,&T_white,F_STORE);
	box(&display,SCR_KEYBOX,F_STORE);

	texture(&display,SCR_ACTIVE,&T_white,F_STORE);
	box(&display,SCR_ACTIVE,F_STORE);
	box(&display,inset(SCR_ACTIVE,1),F_STORE);

	texture(&display,SCR_NAMEBOX,&T_white,F_STORE);

	screen_logo_draw();
	/* set up the key menu */
	screen_key_draw(" COARSE "," FINE ","GO BACK");
	
	/* set up the permanent action switches */
	texture(&display,SCR_TOGIMAGE,tweed,F_STORE);
	string(&mediumfont,"TOGGLE",&display,
			SCR_TOGORIG, F_STORE);
	
	texture(&display,SCR_GOIMAGE,tweed,F_STORE);
	string(&mediumfont,"GO",&display,
			SCR_GOORIG, F_STORE);
	
	texture(&display,SCR_STOPIMAGE,tweed,F_STORE);
	string(&mediumfont,"EXIT",&display,
			SCR_STOPORIG, F_STORE);
}

/********************************************************************
* void screen_key_draw(k1, k2, k3)
*
*	This routine draws the mouse key definitions with the
*	strings provided. If a string == NULL, don't touch
*	that key.
*** note:  Key 1 and 2 are one liners, key 3 is always 2 lines
*** 	   with "TOGGLE TO:" in first line.
*********************************************************************/
void screen_key_draw(k1,k2,k3)
char *k1, *k2, *k3;
{
    int length;
    char *tt;

    string(&smallfont,"MOUSE KEY DEFINITIONS:",&display,
		SCR_KEYORIG, F_STORE);

	/* set up the key menu */
    if (k1 != NULL)
    {
	length = strwidth(&smallfont,k1) / 2;
	texture(&display,SCR_KEY1,&T_lightgrey,F_STORE);
	string(&smallfont,k1,&display,
			sub(SCR_KEY1ORIG,Pt(length,0)), F_STORE);
    }
    if (k2 != NULL)
    {
	length = strwidth(&smallfont,k2) / 2;
	texture(&display,SCR_KEY2,&T_lightgrey,F_STORE);
	string(&smallfont,k2,&display,
			sub(SCR_KEY2ORIG,Pt(length,0)), F_STORE);
    }
    if (k3 != NULL)
    {
	tt = " GO BACK   ";
	length = strwidth(&smallfont,tt) / 2;
	texture(&display,SCR_KEY3,&T_lightgrey,F_STORE);
	string(&smallfont, tt ,&display,
			sub(SCR_KEY3ORIG,Pt(length,0)), F_STORE);

	tt = " ONE LEVEL ";
	length = strwidth(&smallfont,tt) / 2;
	string(&smallfont, tt ,&display,
			sub(SCR_KEY3AORIG,Pt(length,0)), F_STORE);
    }
}

/********************************************************************
* void screen_curnode_draw()
*
*	This routine draws the currentnode on the main screen
*	with 2 levels of depth (the current node and its children)
*
*** note: current node will always be a cluster or a panel at call,
***       and will be bumped to the sub-cluster if it is a panel
********************************************************************/

void screen_curnode_draw()
{

	
	if (currentnode->type == PANEL)
		currentnode = currentnode->child[0];

	/* update the name */
	screen_name_draw();

	/* clear out what is going to be re-drawn */
	texture(&display,inset(SCR_ACTIVE,3),&T_white,F_STORE);

	
	screen_refresh_curnode();
}

/********************************************************************
* void screen_refresh_curnode()
*
*	This routine refreshes the currentnode on the main screen
*	by redrawing it's children, without clearing the screen
*
********************************************************************/
void screen_refresh_curnode()
{
	int i;

	/* should always be a cluster now */
	for(i=currentnode->numchildren-1; i>=0; i--)
	{
		nap(1);
		/* draw each child with single level of depth */
		screen_node_draw(currentnode->child[i]);
	}
	
}
/********************************************************************
* void screen_name_draw()
*
*********************************************************************/
void screen_name_draw()
{

	char abuf[BUFSIZE];
	char bbuf[BUFSIZE];
	struct node *n;
	int length;

	
	/* clear out what is going to be re-drawn */
	box(&display,SCR_NAMEBOX,F_STORE);
	box(&display,inset(SCR_NAMEBOX,1),F_STORE);
	texture(&display,inset(SCR_NAMEBOX,3),tweed,F_STORE);

	/* add the node name */
	Sprintf(abuf," %s",currentnode->name);
	for(n=currentnode->parent; n != NULLNP ; n=n->parent)
	{
		if ((strlen(abuf) > 50) ||
		   (strlen(abuf) + strlen(n->name) > 60))
		{
			strcpy(bbuf, " ... /");
			strcat(bbuf, abuf);
			strcpy(abuf,bbuf);
			break;
		}
		Sprintf(bbuf," %s /%s",n->name, abuf);
		strcpy(abuf,bbuf);
		if (n->type == PANEL)
			break;
	}
	strcat(abuf, " : ");
	length = strwidth(&largefont,abuf)/2;
	string( &largefont, abuf, &display,
			sub(SCR_NAMEORIG,Pt(length,0)),F_STORE);
	
}

/********************************************************************
* void screen_node_draw(n)
*
*	This routine draws the node n on the main screen
*	with 1 levels of depth (the current knob or display, or
*	an ICON if cluster or panel)
*
*** note:  this routine should be called only by screen_curnode_draw()
*********************************************************************/

void screen_node_draw(n)
struct node *n;
{
	int h,i,j;
	float sbarratio;
	float offset;
	Rectangle r, s;
	Point p, q;
	char *c;
	Bitmap *b;

    /* get the window area on the screen */
	r = raddp(n->window_rect,n->rel_to_origin);


	if ((n->window_flag & ANYBORDER) == 0)
	{
	    /* there are no scroll bars or subwindows */
		bitblt(n->image,n->image_size,
			&display,n->rel_to_origin,F_STORE);
	}
	else
	{

	    /* place the subwindows */
		for (j=0; j<MAXSUBWIN; j++)
		{
			if (n->window_flag & subwin(j))
			{
				screen_subwin_draw(n,j);
			}
		}

		if(n->window_flag & WB_VSCR)
		{
			b = n->sbar[VERT];
			p = add(r.origin,(n->sbar_orig)[VERT]);
			bitblt(b, b->rect, &display,p, F_STORE);

		    /* place the horizontal scroll pip */
			s = raddp(b->rect,p);
			s.origin.y += 16;
			s.corner.y -= 32;
			p.x = s.origin.x;
			sbarratio=(float)(n->sbarmax[VERT]-n->sbarcur[VERT])/
				(float)(n->sbarmax[VERT] - n->sbarmin[VERT]);
			offset = (float)(s.corner.y - s.origin.y)*sbarratio;
			p.y = s.corner.y - (int)offset;
			bitblt(SBAR, Rect(32,0,48,16), &display,p, F_STORE);
		}

		if(n->window_flag & WB_HSCR)
		{
			b = n->sbar[HORIZ];
			p = add(r.origin,(n->sbar_orig)[HORIZ]);
			bitblt(b, b->rect, &display,p, F_STORE);

		    /* place the horizontal scroll pip */
			s = raddp(b->rect,p);
			s.origin.x += 16;
			s.corner.x -= 32;
			p.y = s.origin.y;
			sbarratio=(float)(n->sbarmax[HORIZ]-n->sbarcur[HORIZ])/
				(float)(n->sbarmax[HORIZ] - n->sbarmin[HORIZ]);
			offset = (float)(s.corner.x - s.origin.x)*sbarratio;
			p.x = s.corner.x - (int)offset;
			bitblt(SBAR, Rect(32,0,48,16), &display,p, F_STORE);
		}

		b = n->sbar[RESHAPE];
		p = (n->sbar_orig)[RESHAPE];
		bitblt(b, b->rect, &display,add(r.origin,p), F_STORE);
	}
	
    /* if GREY attribute set , grey out the box */
	if (n->attribute & A_GREY)
		texture(&display, r, &T_grey, F_CLR);
	

}


/********************************************************************
* void screen_subwin_draw(n,w)
*
*	This routine draws the subwindow of node n on the main screen
*	in the window of node n
*
*********************************************************************/

void screen_subwin_draw(n,w)
struct node *n;
int w;
{
	int h,i,j;
	Rectangle r, k;
	Point p, q;
	char *c;

    /* get the major window rect */
	r = raddp(n->window_rect,n->rel_to_origin);

    /* compute the screen dest origin */
	q = (n->sw_rect[w]).origin;
	p = add(r.origin, q);

    /* find the source rect in the image blit */
	k = rsubp(n->sw_rect[w],q);		   /* area of source */
	k = raddp(k,n->sw_origin[w]);		   /* area on image */ 

    /* place it on the screen */
	bitblt(n->image,k,&display,p,F_STORE);

}

/********************************************************************
* Rectangle knob_elem_rect(n, r, e);
*
*	This routine returns the rectangle of size KNOB_AREA around
*       the element e of knob n which is on the screen in rectangle r.
*	This returned rectangle is usefull for both drawing and
*	determining if a mouse hit is on an element
*********************************************************************/
Rectangle knob_elem_rect(n, r, e)
struct node *n;
Rectangle r;
int e;
{
	int i, iy, m, my, offset;
	Point p;
	Rectangle k;

	switch(n->type)
	{
	case FWINT:
	case VWINT:
	case FWFLT:
	case VWFLT:
		if (e < n->maxnumvalues)
		{
		    /* find the first element's box */
			i = (2*TEXT_HEIGHT) + GUARDY - 2;
			p=add(r.origin,Pt(2,i));
			k=raddp(VKNOB_AREA,p);

		    /* increment to the desired knob element */
			offset = n->element_width * e;
			k=raddp(k,Pt(offset,0));
			return(k);
		}
		else
		{
			i = r.origin.x + 2;
			m = i + n->element_width * n->maxnumvalues - 8;

			my = r.corner.y - TEXT_HEIGHT - 2;
			iy = my - HKNOB_HEIGHT;
			return(fRect(i,iy,m,my));
		}
		break;

	case ENUM:
	    /* find the first element's box origin */
		i = TEXT_HEIGHT + GUARDY - 3;
		p = add(r.origin,Pt(2,i));

		i = TEXT_HEIGHT * 2 * n->numdim;
		k = fRect(0,0,VKNOB_WIDTH,i);
		k = raddp(k, p);
		return(k);
		
		break;
	}
}




/********************************************************************
* Rectangle knob_slide_rect(n, r, e);
*
*	This routine returns the rectangle around the slider of element e
*  	of knob n which is on the screen in KNOB_AREA r.  This
*	returned rectangle is usefull for both drawing and
*	determining if a mouse hit is on an element
*********************************************************************/
Rectangle knob_slide_rect(n, r, e)
struct node *n;
Rectangle r;
int e;
{
	float range;
	float drange;
	int cur;
	Rectangle scr;
	Rectangle scl;
	Point hsl;
	char *c;

	/* compute new pointer position */
	/*   if a regular knob element  */
	if(e < n->maxnumvalues)
	{
	    if(n->type != ENUM)
	    {
		drange = (float)(r.corner.y - r.origin.y - 16);
		range = n->max - n->min;
		cur = r.corner.y - 16 -
			 (int) ((n->value[e] - n->min)/range * drange);

		scr = raddp(Rect(0,0,32,16),Pt(r.origin.x,cur));
		return(scr);
	    }
	    else
	    {
		cur =  (n->max - n->value[e]) * 2 * TEXT_HEIGHT;
		scr = raddp(Rect(0,0,32,16),r.origin);
		scr = raddp(scr,Pt(0,cur));
		return(scr);
	    }
	}
	else
	/*    a width control element  */
	{
		
		hsl = add(r.origin,Pt(VKNOB_WIDTH/2,0));
		hsl.x += (n->numvalues-1) * n->element_width;
		scr = raddp(Rect(0,0,16,32),hsl);
		return(scr);
/*
		drange = (float)(r.corner.x - r.origin.x - 16);
		range = n->maxnumvalues;
	
		cur = r.origin.x + (int) (n->numvalues/range * drange);

		scr = raddp(Rect(0,0,16,32),Pt(cur,r.origin.y));
		return(scr);
*/

	}
	
}
