
/**************************************************************************/
/* PANELFEATURES Package    Release:  1.0    Release Date: 1/15/89        */
/*                          Provider: J. D. Iorio  (speedy!jdi)           */
/**************************************************************************/

/*
*	(C) Copyright ATT 1988
*
*	giwindow.c -
*
* A collection of graphics window routines for the 630 terminal
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
extern char lbuf[];

extern Bitmap* SBAR;

extern void window_node_draw();
/********************************************************************
* initwindow(node *n)
*
*	This routine allocates a bitmap for the image, sets up, and draws
* the window image in the bitmap.  This routine assumes
* that several parameters have been set-up (by sizenode()), and will
* set up a window that can be placed by tilenode().
*********************************************************************/
void initwindow(n)
struct node *n;
{
	int i;
	Rectangle display_area, trial;
	Point curpt;
	int maxy, m;


    /* initialize the bitmap for the image */
	if( (n->image = balloc(n->image_size)) == (Bitmap *)NULL)
	{
		Sprintf(lbuf,"Bitmap alloc for <%s> failed",n->oname);
		warn(lbuf);
		return;
	}

    /* place the initial drawing into the image */
	window_node_draw(n);
}

/********************************************************************
* initscroll(node *n)
*
*	This routine sets up scroll bars in the image BLIT if the
* flags indicate they should be there.
*********************************************************************/
void initscroll(n)
struct node *n;
{

	Rectangle vs, hs, rs;
	Rectangle temp;
	int vset, hset;
	Point poly[4];

    /* set up scroll boxes if any */
	hset = 0;
	vset = 0;

    /* if scroll boxes, draw them */
	if(n->window_flag & WB_VSCR)
	{
		vs.origin.x = n->window_rect.corner.x - WBW;
		vs.origin.y = n->window_rect.origin.y;
		vs.corner.x = n->window_rect.corner.x;
		vs.corner.y = n->window_rect.corner.y - WBH;
		vset = WBH/2;
		temp = rsubp(vs,vs.origin);

		n->sbar_orig[VERT] = vs.origin;

	    /* initialize the bitmap for the image */
		if( (n->sbar[VERT] = balloc(temp)) == (Bitmap *)NULL)
		{
			Sprintf(lbuf,"Bitmap vsbar alloc for <%s> failed",
					n->oname);
			warn(lbuf);
			return;
		}
		
		texture(n->sbar[VERT], temp, &T_lightgrey, F_STORE);
		bitblt(SBAR,Rect(0,0,16,16),n->sbar[VERT],temp.origin,F_STORE);
		bitblt(SBAR,Rect(0,16,16,32),n->sbar[VERT],
					sub(temp.corner,Pt(16,16)),F_STORE);
		box(n->sbar[VERT],temp,F_STORE);
			
	}

	if(n->window_flag & WB_HSCR)
	{

		hs.origin.x = n->window_rect.origin.x;
		hs.origin.y = n->window_rect.corner.y - WBH;
		hs.corner.x = n->window_rect.corner.x - WBW;
		hs.corner.y = n->window_rect.corner.y;
		hset = WBW/2;
		temp = rsubp(hs,hs.origin);

		n->sbar_orig[HORIZ] = hs.origin;

	    /* initialize the bitmap for the image */
		if( (n->sbar[HORIZ] = balloc(temp)) == (Bitmap *)NULL)
		{
			Sprintf(lbuf,"Bitmap hsbar alloc for <%s> failed",
					n->oname);
			warn(lbuf);
			return;
		}
		texture(n->sbar[HORIZ], temp, &T_lightgrey, F_STORE);
		bitblt(SBAR,Rect(16,16,32,32),n->sbar[HORIZ],
					temp.origin,F_STORE);
		bitblt(SBAR,Rect(16,0,32,16),n->sbar[HORIZ],
					sub(temp.corner,Pt(16,16)),F_STORE);
		box(n->sbar[HORIZ],temp,F_STORE);
	}

	if(n->window_flag & (WB_HSCR | WB_VSCR))
	{

	    /* draw resize box */
		rs.origin = sub(n->window_rect.corner,Pt(WBW,WBH));
		rs.corner = n->window_rect.corner;
		temp = rsubp(rs,rs.origin);

		n->sbar_orig[RESHAPE] = rs.origin;

	    /* initialize the bitmap for the image */
		if( (n->sbar[RESHAPE] = balloc(temp)) == (Bitmap *)NULL)
		{
			Sprintf(lbuf,"Bitmap rsbar alloc for <%s> failed",
					n->oname);
			warn(lbuf);
			return;
		}

		texture(n->sbar[RESHAPE], temp, &T_lightgrey, F_STORE);
		texture(n->sbar[RESHAPE],
			 Rpt(temp.origin,sub(temp.corner,Pt(hset,vset))),
			 &T_black, F_STORE);
		box(n->sbar[RESHAPE],temp,F_STORE);
	}
		
}


