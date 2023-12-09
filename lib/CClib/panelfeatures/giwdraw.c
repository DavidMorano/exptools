
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
* These rotuines place items into bitmap images which are windowed
* onto the screen 
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
extern Bitmap *SBAR, *WBAR;
extern char lbuf[];

extern void warn();

extern Texture16 *tweed, *kapow, *busycursor, *normcursor;

void w_kvalue_draw();
void w_kvalue_undraw();
void window_disp_values();
void window_node_draw();
void screen_node_draw();
void initscroll();
void draw_plot();
void upd_plot();
int  w_adjust();
int  w_edit();
extern Rectangle knob_elem_rect();
extern Rectangle knob_slide_rect();
extern void makevalue();
extern void scaleaxes();


/********************************************************************
* void window_node_draw(n)
*
*	This routine draws the node n on the bitmap image 
*	with 1 levels of depth (the current knob or display, or
*	an ICON if cluster or panel)
*	It also computes the subwindows for display on the screen
*	if the W_INIT FLAG is not set.  Subwindows are placed in the
*	specified window_rect as best as possible
*
*********************************************************************/

void window_node_draw(n)
struct node *n;
{
	int h,i,j;
	int wbw, wbh;
	Rectangle r, k;
	Point p, q;
	char *c;

	r = n->image_size;

	switch (n->type)
	{
	case PANEL:
		if((n->window_flag & W_INIT) == 0)
		{
			/* always 1 window with no borders */
			n->window_rect = n->image_size;
			n->window_flag = NOBORDER | NO_HSCR | NO_VSCR | W_INIT;
		}

		texture(n->image, r, kapow, F_STORE);
		box(n->image,r,F_STORE);
		box(n->image,inset(r,1),F_CLR);
		box(n->image,inset(r,2),F_STORE);
		/* add the node name */
		string(&mediumfont, n->name, n->image,
			add(r.origin,Pt(24,4)), F_STORE);
		/* add the move icon */
		bitblt(WBAR, Rect(0,0,16,16), n->image,
			WB_MOVEorig(r), F_STORE);

		break;
	case CLUSTER:
		if((n->window_flag & W_INIT) == 0)
		{
			/* always 1 window with no borders */
			n->window_rect = n->image_size;
			n->window_flag = NOBORDER | NO_HSCR | NO_VSCR | W_INIT;
		}

		texture(n->image, r, tweed, F_STORE);
		box(n->image,inset(r,1),F_CLR);
		box(n->image,r,F_STORE);
		/* add the node name */
		string(&mediumfont, n->name, n->image,
			add(r.origin,Pt(24,4)), F_STORE);
		/* add the move icon */
		bitblt(WBAR, Rect(0,0,16,16), n->image,
			WB_MOVEorig(r), F_STORE);

		break;
	case FWINT:
	case VWINT:
	case FWFLT:
	case VWFLT:


		texture(n->image, r, &T_lightgrey, F_STORE);
	    /* locate the node name */
		string(&mediumfont, n->name, n->image,
			add(r.origin,Pt(24,4)), F_STORE);
		/* add the move icon */
		bitblt(WBAR, Rect(0,0,16,16), n->image,
			WB_MOVEorig(r), F_STORE);
		if((n->window_flag & W_INIT) == 0)
		{
		    /* initialize the name subwindow */
			n->window_flag |= subwin(0);
			n->sw_origin[0] = fPt(0,0);
			k.origin = r.origin;
			k.corner = fPt(n->window_rect.corner.x,
				 n->window_rect.origin.y+mediumfont.height+4);
			n->sw_rect[0] = k;
			n->subwindow_flag[0] = NOSCRL;
		}

    	    /* FILL THE BITMAPS */
		(n->knobslide).width = 2;
		(n->knobslide).rect = fRect(0,0,32,(16*(n->maxnumvalues + 2)));
		for(i=0; i<n->maxnumvalues; i++)
		{
			bitblt(VKNOB,VKNOBSLIDE,&n->knobslide,
						KVSLIDEPT(i),F_STORE);
		}
		bitblt(HKNOB,HKNOBSLIDE,&n->knobslide,KHSLIDEPT,F_STORE);

	    /* locate and draw the vertical knob elements */
		for(i=0; i<n->numvalues; i++)
		{
		    /* get the element's rectangle */
 			k = knob_elem_rect(n, r, i); 

		    /* the knob background */
			texture(n->image, k, &T_white, F_STORE);

		    /* the scale elements */
			q = add(k.origin,Pt(14,0));
			bitblt(VKNOB,VKNOBTOP,n->image,q,F_STORE);
			for (j=1; j<7; j++)
			{
				q = add(q,Pt(0,14));
				
				bitblt(VKNOB,VKNOBMID, n->image, q, F_STORE);
				bitblt(VKNOB,VKNOBTICK, n->image,
						 Pt(k.origin.x,q.y), F_STORE);
			}
			q = add(q,Pt(0,14));
			bitblt(VKNOB,VKNOBBOT, n->image,q ,F_STORE);
			bitblt(VKNOB,VKNOBTICK, n->image,
					 Pt(k.origin.x,q.y), F_STORE);

		    /* the knob value and slider */
			w_kvalue_draw(n, k, i);
		}
	    /* locate the scale values */
 		k = knob_elem_rect(n, r, n->maxnumvalues-1); 
		k = raddp(k, Pt(n->element_width,0));
		makevalue(lbuf, n->fmt, n->max);
		string(&TEXT_FONT, lbuf, n->image, k.origin, F_STORE);

		makevalue(lbuf, n->fmt, n->min);
		string(&TEXT_FONT,lbuf,n->image,
			sub(Pt(k.origin.x,k.corner.y),Pt(0,(TEXT_HEIGHT+3))),
			F_STORE);

		if((n->window_flag & W_INIT) == 0)
		{
		    /* initialize the scale subwindow */
			n->window_flag |= subwin(1);
			n->sw_origin[1].x = k.origin.x;
			n->sw_origin[1].y = n->image_size.origin.y +
				mediumfont.height + 4;

			n->sw_rect[1].origin.y = n->sw_rect[0].corner.y;
			n->sw_rect[1].corner.y = n->window_rect.corner.y-WBH;

			n->sw_rect[1].corner.x = n->window_rect.corner.x;
			n->sw_rect[1].origin.x = n->sw_rect[1].corner.x -
				(n->image_size.corner.x - k.origin.x);
			n->subwindow_flag[1] = NOSCRL;
		}

	    /* locate the scale label */
		Sprintf(lbuf, "%s", n->scalelab);
		for (c=lbuf; (*c != ' ')&&(*c !='\0'); c++);
		*c = '\0';
		q.x = k.origin.x;
		q.y = (k.corner.y-k.origin.y)/2 + k.origin.y;
		string(&TEXT_FONT,lbuf,n->image, q, F_STORE);

		if ((n->type == VWINT) || (n->type == VWFLT))
		{
		/* only for variable width knobs */
		/* draw the width knob element */
		    /* get the WIDTH knob's rectangle */
 			k = knob_elem_rect(n, r, n->maxnumvalues); 

		    /* the knob background */
			texture(n->image, k, &T_white, F_STORE);
			q = add(k.origin,Pt(0,16));
			bitblt(HKNOB,HKNOBTOP, n->image, q, F_STORE);
			q = add(q,Pt(16,0));
			for( ; q.x < k.corner.x - 17;)
			{
				bitblt(HKNOB,HKNOBMID, n->image, q, F_STORE);
				q.x += 16;
			}
			q.x = k.corner.x - 17;
			bitblt(HKNOB,HKNOBBOT, n->image, q, F_STORE);

		    /* add the number of elements */
			q = add(k.origin,Pt(VKNOB_WIDTH/2,1));
			for(j=1; j <= n->maxnumvalues; j++ )
			{
				Sprintf(lbuf, "%d", j);
				string(&smallfont,lbuf,n->image, q, F_STORE);
				q = add(q, Pt(n->element_width,0));
			}
		    /* add the knob slider */
			w_kvalue_draw(n, k, n->maxnumvalues);
		}

		/* if the utility function is enabled, add the icon */
		if (n->window_flag & WB_UTIL)
		{
			k = WB_UTILarea(n->image_size);
			bitblt(SBAR, Rect(32,16,48,32), n->image,
					k.origin, F_STORE);
		}


		if((n->window_flag & W_INIT) == 0)
		{
		    /* initialize the main knob subwindow */
			n->window_flag |= subwin(2);
			n->sw_origin[2].x = n->image_size.origin.x;
			n->sw_origin[2].y = n->image_size.origin.y +
				mediumfont.height + 4;
			n->sw_rect[2].origin.x = n->sw_rect[0].origin.x;
			n->sw_rect[2].origin.y = n->sw_rect[0].corner.y;
			n->sw_rect[2].corner.x = n->sw_rect[1].origin.x;
			n->sw_rect[2].corner.y = n->sw_rect[1].corner.y;
			
			/* set up the scroll parameters */
			n->sbarmin[HORIZ] = n->sw_origin[2].x;
			n->sbarmax[HORIZ] = n->sw_origin[1].x -
			      (n->sw_rect[2].corner.x - n->sw_rect[2].origin.x);
			n->sbarcur[HORIZ] = n->sbarmin[HORIZ];
			n->subwindow_flag[2] = HSCRL;
		}

		/* window is always initialized when we leave this routine */
		n->window_flag |= W_INIT;
		break;
	case ASCKNOB:
		if((n->window_flag & W_INIT) == 0)
		{
		    /* initialize the name subwindow */
			n->window_flag |= subwin(0);
			n->sw_origin[0] = fPt(0,0);
			k.origin = r.origin;
			k.corner = fPt(n->window_rect.corner.x,
				 n->window_rect.origin.y+mediumfont.height+4);
			n->sw_rect[0] = k;
			n->subwindow_flag[0] = NOSCRL;

		    /* initialize the main knob subwindow */
			n->window_flag |= subwin(1);
			n->sw_origin[1].x = n->image_size.origin.x;
			n->sw_origin[1].y = n->image_size.origin.y +
				mediumfont.height + 4;
			n->sw_rect[1].origin.x = n->sw_rect[0].origin.x;
			n->sw_rect[1].origin.y = n->sw_rect[0].corner.y;
			n->sw_rect[1].corner = n->window_rect.corner;
			
			/* set up the scroll parameters */
			n->sbarmin[HORIZ] = n->sw_origin[1].x;
			n->sbarmax[HORIZ] = n->image_size.corner.x -
			      (n->sw_rect[1].corner.x - n->sw_rect[1].origin.x);
			n->sbarcur[HORIZ] = n->sbarmin[HORIZ];
			n->subwindow_flag[1] = HSCRL;
			n->window_flag |= W_INIT;
		}


		texture(n->image, r, &T_lightgrey, F_STORE);
	    /* locate the node name */
		string(&mediumfont, n->name, n->image,
			add(r.origin,Pt(24,4)), F_STORE);
		/* add the move icon */
		bitblt(WBAR, Rect(0,0,16,16), n->image,
			WB_MOVEorig(r), F_STORE);


	    /* locate and draw the data strings */
		q = fPt(2,22);
		string(&TEXT_FONT, n->labels[0], n->image, q, F_STORE);
		q = fPt(2,38);
		string(&TEXT_FONT, n->labels[1], n->image, q, F_OR);
		q = fPt(2,54);
		box(n->image,Rect(q.x,q.y,q.x+n->element_width,q.y+16),F_STORE);
		string(&TEXT_FONT, n->labels[2], n->image, q, F_STORE);

		break;

	case ENUM:

		if((n->window_flag & W_INIT) == 0)
		{
		    /* initialize the name subwindow */
			n->window_flag |= subwin(0);
			n->sw_origin[0] = fPt(0,0);
			k.origin = r.origin;
			k.corner = fPt(n->window_rect.corner.x,
				 n->window_rect.origin.y+mediumfont.height+4);
			n->sw_rect[0] = k;
			n->subwindow_flag[0] = NOSCRL;

		    /* initialize the main knob subwindow */
			n->window_flag |= subwin(1);
			n->sw_origin[1].x = n->image_size.origin.x;
			n->sw_origin[1].y = n->image_size.origin.y +
				mediumfont.height + 4;
			n->sw_rect[1].origin.x = n->sw_rect[0].origin.x;
			n->sw_rect[1].origin.y = n->sw_rect[0].corner.y;
			n->sw_rect[1].corner = n->window_rect.corner;
			
			/* set up the scroll parameters */
			n->sbarmin[VERT] = n->sw_origin[1].y;
			n->sbarmax[VERT] = n->image_size.corner.y -
			      (n->sw_rect[1].corner.y - n->sw_rect[1].origin.y);
			n->sbarcur[VERT] = n->sbarmin[VERT];
			n->subwindow_flag[1] = VSCRL;
			n->window_flag |= W_INIT;
		}


		texture(n->image, r, &T_lightgrey, F_STORE);
	    /* locate the node name */
		string(&mediumfont, n->name, n->image,
			add(r.origin,Pt(24,4)), F_STORE);
		/* add the move icon */
		bitblt(WBAR, Rect(0,0,16,16), n->image,
			WB_MOVEorig(r), F_STORE);


    	    /* FILL THE BITMAPS */
		(n->knobslide).width = 2;
		(n->knobslide).rect = fRect(0,0,32,(16*(n->maxnumvalues + 2)));
		for(i=0; i<n->maxnumvalues; i++)
		{
			bitblt(VKNOB,VKNOBSLIDE,&n->knobslide,
						KVSLIDEPT(i),F_STORE);
		}


	    /* locate and draw the vertical knob elements */
		for(i=0; i<n->maxnumvalues; i++)
		{
		    /* get the element's rectangle */
 			k = knob_elem_rect(n, r, i); 

		    /* the knob background */
			texture(n->image, k, &T_white, F_STORE);

		    /* the scale elements */
			q = add(k.origin,Pt(14,0));
			bitblt(VKNOB,VKNOBTOP,n->image,q,F_STORE);

			q = add(q,Pt(0,TEXT_HEIGHT));
			bitblt(VKNOB,VKNOBMID, n->image, q, F_STORE);

			for (j=0; j<n->numdim-2; j++)
			{
				q = add(q,Pt(0,TEXT_HEIGHT));
				bitblt(VKNOB,VKNOBMID, n->image, q, F_STORE);
				q = add(q,Pt(0,TEXT_HEIGHT));
				bitblt(VKNOB,VKNOBMID, n->image, q, F_STORE);
			}
			q = add(q,Pt(0,TEXT_HEIGHT));
			bitblt(VKNOB,VKNOBBOT, n->image,q ,F_STORE);

		    /* place the labels */
			q = add(k.origin,Pt(VKNOB_WIDTH+4,4));
			for (j=0; j<n->numdim; j++)
			{
				i = n->numdim - j - 1;
				string(&TEXT_FONT, n->labels[i],
					 n->image, q, F_STORE);
				h = q.y + 6;
				bitblt(VKNOB,VKNOBTICK, n->image,
					 Pt(k.origin.x,h), F_STORE);
				q = add(q,Pt(0,(2*TEXT_HEIGHT)));
			}

		    /* the knob value and slider */
			w_kvalue_draw(n, k, i);
		}
		break;
	case ASCDISP:

		if((n->window_flag & W_RESIZE) == 0)
		{
			/* don't erase image on a resize mouse operation */
			/* draw the outer border */
			texture(n->image, r, &T_white, F_STORE);
			box(n->image, inset(r,2), F_STORE);
			box(n->image, inset(r,4), F_STORE);
			texture(n->image, inset(r,6), &T_lightgrey, F_STORE);
	
			/* add the node name */
			string(&mediumfont, n->name, n->image,
				add(r.origin,Pt(GUARDX+8,11)), F_STORE);
			/* add the move icon */
			bitblt(WBAR, Rect(0,0,16,16), n->image,
				WB_MOVEorig(r), F_STORE);


			texture(n->image,
			 	Rect(  r.origin.x+GUARDX,
					r.origin.y+2*GUARDY+TEXT_HEIGHT,
					r.origin.x+GUARDX + n->element_width,
					r.corner.y-GUARDY), 
			 	&T_white, F_STORE);
		}

		if((n->window_flag & W_INIT) == 0)
		{
			wbw = (n->window_flag & WB_VSCR) ? WBW : 0;
			wbh = (n->window_flag & WB_HSCR) ? WBH : 0;
		    /* initialize the name subwindow */
			n->window_flag |= subwin(0);
			n->sw_origin[0] = fPt(0,0);
			k.origin = r.origin;
			k.corner = fPt(n->window_rect.corner.x-GUARDX-wbw,
				 n->window_rect.origin.y+2*GUARDY+ TEXT_HEIGHT);
			n->sw_rect[0] = k;
			n->subwindow_flag[0] = NOSCRL;
   
		    /* initialize the main knob subwindow */
/*
		    	n->window_flag |= subwin(1);
		    	n->sw_origin[1].x = r.origin.x;
		    	n->sw_origin[1].y = r.origin.y+2*GUARDY+TEXT_HEIGHT;

			n->sw_rect[1].origin.x = n->sw_rect[0].origin.x;
			n->sw_rect[1].origin.y = n->sw_rect[0].corner.y;
			n->sw_rect[1].corner.x = n->window_rect.corner.x-wbw;
			n->sw_rect[1].corner.y = n->window_rect.corner.y-wbh;
		    	n->subwindow_flag[1] = VSCRL | HSCRL;
*/

			/* set up the scroll parameters */
/*
			n->sbarmin[HORIZ] = n->sw_origin[1].x;
			n->sbarmax[HORIZ] = n->image_size.corner.x -
			      (n->sw_rect[1].corner.x - n->sw_rect[1].origin.x);
			n->sbarcur[HORIZ] = n->sbarmin[HORIZ];

		    	n->sbarmin[VERT] = n->sw_origin[1].y;
		    	n->sbarmax[VERT] = n->image_size.corner.y -
			    (n->sw_rect[1].corner.y-n->sw_rect[1].origin.y);
		    	n->sbarcur[VERT] = n->sbarmin[VERT];
*/
		    	n->window_flag |= subwin(1);
		    	n->sw_origin[1].x = r.origin.x+GUARDX;
		    	n->sw_origin[1].y = r.origin.y+2*GUARDY+TEXT_HEIGHT;

			n->sw_rect[1].origin.x = n->sw_rect[0].origin.x+GUARDX;
			n->sw_rect[1].origin.y = n->sw_rect[0].corner.y;
			n->sw_rect[1].corner.x = n->window_rect.corner.x-
					GUARDX-wbw;
			n->sw_rect[1].corner.y = n->window_rect.corner.y-
					GUARDY-wbh;
		    	n->subwindow_flag[1] = VSCRL | HSCRL;

			/* set up the scroll parameters */
			n->sbarmin[HORIZ] = n->sw_origin[1].x;
			n->sbarmax[HORIZ] = n->image_size.corner.x - GUARDX -
			      (n->sw_rect[1].corner.x - n->sw_rect[1].origin.x);
			n->sbarcur[HORIZ] = n->sbarmin[HORIZ];

		    	n->sbarmin[VERT] = n->sw_origin[1].y;
		    	n->sbarmax[VERT] = n->image_size.corner.y - GUARDY -
			    (n->sw_rect[1].corner.y-n->sw_rect[1].origin.y);
		    	n->sbarcur[VERT] = n->sbarmin[VERT];



				/* BORDER BARS */
		    	n->window_flag |= subwin(2);
		    	n->sw_origin[2].x = r.origin.x;
		    	n->sw_origin[2].y = r.corner.y - GUARDY -
			    (n->sw_rect[1].corner.y-n->sw_rect[1].origin.y);

			n->sw_rect[2].origin.x = n->sw_rect[0].origin.x;
			n->sw_rect[2].origin.y = n->sw_rect[0].corner.y;
			n->sw_rect[2].corner.x = n->sw_rect[0].origin.x+GUARDX;
			n->sw_rect[2].corner.y = n->window_rect.corner.y-wbh;
			n->subwindow_flag[2] = NOSCRL;


		    	n->window_flag |= subwin(3);
		    	n->sw_origin[3].x = r.corner.x - GUARDX;
		    	n->sw_origin[3].y = r.origin.y;

			n->sw_rect[3].origin.x = n->sw_rect[0].corner.x;
			n->sw_rect[3].origin.y = n->sw_rect[0].origin.y;
			n->sw_rect[3].corner.x = n->window_rect.corner.x-wbw;
			n->sw_rect[3].corner.y = n->window_rect.corner.y-
					GUARDY-wbh;
			n->subwindow_flag[3] = NOSCRL;


		    	n->window_flag |= subwin(4);
		    	n->sw_origin[4].x = n->image_size.corner.x - GUARDY -
			      (n->sw_rect[1].corner.x - n->sw_rect[1].origin.x);
		    	n->sw_origin[4].y = r.corner.y - GUARDY;

			n->sw_rect[4].origin.x = n->sw_rect[1].origin.x;
			n->sw_rect[4].origin.y = n->sw_rect[1].corner.y;
			n->sw_rect[4].corner.x = n->window_rect.corner.x-wbw;
			n->sw_rect[4].corner.y = n->window_rect.corner.y-wbh;
			n->subwindow_flag[4] = NOSCRL;

		}
		
		n->window_flag |= W_INIT;
		break;

	case DISPLAY:

		/* draw the outer border */
		texture(n->image, r, &T_white, F_STORE);
		box(n->image, inset(r,2), F_STORE);
		box(n->image, inset(r,4), F_STORE);
		texture(n->image, inset(r,6), &T_lightgrey, F_STORE);

		/* add the node name */
		string(&mediumfont, n->name, n->image,
			add(r.origin,Pt(GUARDX+8,11)), F_STORE);
		/* add the move icon */
		bitblt(WBAR, Rect(0,0,16,16), n->image,
			WB_MOVEorig(r), F_STORE);

		/* if the utility function is enabled, add the icon */
		if (n->window_flag & WB_UTIL)
		{
			k = WB_PUTILarea(n->image_size);
			if(n->window_flag & WB_PLOT)
				bitblt(WBAR, Rect(32,0,48,16), n->image,
					k.origin, F_STORE);
			else
				bitblt(WBAR, Rect(16,0,32,16), n->image,
					k.origin, F_STORE);
		}
		
		/* if plot flag set, do plot */
		if(n->window_flag & WB_PLOT)
		{
			k.origin = fPt(GUARDX,GUARDY+2*TEXT_HEIGHT+6);
			k.corner = sub(r.corner,Pt(GUARDX,GUARDY));
			
			draw_plot(n,k);
		}
		else
		{

		    /* else do text display */
			/* add the data labels */
			q = fPt(GUARDX,GUARDY+2*TEXT_HEIGHT+6);
			for(i=0; i<n->numdim; i++)
			{
				string(&mediumfont, n->labels[i], n->image,
			    	add(r.origin,q), F_STORE);
				q.x += 100;
			}

			/* add the data scale labels */
			q = fPt(GUARDX,GUARDY+3*TEXT_HEIGHT+8);
			for(i=0; i<n->numdim; i++)
			{
				Sprintf(lbuf,"%s", n->dscalelab[i]);
				for (c=lbuf; (*c != ' ')&&(*c !='\0'); c++);
				*c = '\0';
				string(&mediumfont, lbuf, n->image,
			    	add(r.origin,q), F_STORE);
				q.x += 100;
			}


			/* add the data */
			/* and compute origin and corner of active display */
			/* values stored in n->sw_origin[2].y and          */
			/* n->sw_origin[1].y respectively                  */
			window_disp_values(n, r);

			if((n->window_flag & W_INIT) == 0)
			{
			    n->window_flag |= subwin(0);
			    n->sw_origin[0] = r.origin;
			    n->sw_rect[0].origin = n->window_rect.origin;
			    n->sw_rect[0].corner.x = n->window_rect.corner.x;
			    n->sw_rect[0].corner.y = n->sw_origin[2].y - 
					r.origin.y;
			    n->subwindow_flag[0] = NOSCRL;
    
			    n->window_flag |= subwin(1);
			    n->sw_origin[1].x = r.origin.x;
			    n->sw_rect[1].origin.x = n->window_rect.origin.x;
			    n->sw_rect[1].origin.y = n->window_rect.corner.y - 
					(r.corner.y - n->sw_origin[1].y);
			    n->sw_rect[1].corner = n->window_rect.corner;
			    n->subwindow_flag[1] = NOSCRL;

			    n->window_flag |= subwin(2);
			    n->sw_origin[2].x = r.origin.x;
			    n->sw_rect[2].origin.x = n->sw_rect[0].origin.x;
			    n->sw_rect[2].origin.y = n->sw_rect[0].corner.y;
			    n->sw_rect[2].corner.x = n->sw_rect[1].corner.x;
			    n->sw_rect[2].corner.y = n->sw_rect[1].origin.y;
			    n->subwindow_flag[2] = VSCRL;

			    n->sbarmin[VERT] = n->sw_origin[2].y;
			    n->sbarmax[VERT] = n->sw_origin[1].y -
				(n->sw_rect[2].corner.y-n->sw_rect[2].origin.y);
			    n->sbarcur[VERT] = n->sbarmax[VERT];
			    n->sw_origin[2].y = n->sbarcur[VERT];

			}
		}
		
		n->window_flag |= W_INIT;
		break;

	}


	if (currentnode == NULLNP)
		return;
	if(n->parent == currentnode)    /* this node is on the screen */
		screen_node_draw(n);	/* the draw it on screen */
	
}

/********************************************************************
* void window_disp_values(n, r);
*
*	This routine does a complete redraw of the data area of
*	a display type node n which is on the screen in rectangle r.
*********************************************************************/
void window_disp_values(n, r)
struct node* n;
Rectangle r;
{
		int i, j;
		Rectangle ad;
		char *c;
		Point q;
		

		/* find data area */
		ad.origin.x = r.origin.x + GUARDX;
		ad.corner.x = r.corner.x - GUARDX;
		ad.origin.y = r.origin.y + (4 * TEXT_HEIGHT) + GUARDY + 12;
		ad.corner.y = r.corner.y - GUARDY - 2;
		texture(n->image, ad, &T_white, F_STORE);

		/* add to the subwindow data */
		if((n->window_flag & W_INIT) == 0)
		{
			n->sw_origin[2].y = ad.origin.y;
			n->sw_origin[1].y = ad.corner.y;
		}

		/* print data at proper start line */
		q.y = ad.origin.y +
		     (n->maxnumvalues - n->numvalues) * TEXT_HEIGHT;

		for (j=0; j<n->numvalues; j++)
		{
		    q.x = ad.origin.x;
		    for (i=0; i<n->numdim; i++)
		    {
			makevalue(lbuf, n->dfmt[i], n->data[i][j]);
			string(&smallfont, lbuf, n->image, q, F_STORE);
			q.x += 100;
		    }
		    q.y += TEXT_HEIGHT;
		}
	
}
/********************************************************************
* void window_upd_disp(n);
*
*	This routine adds the last stored datavalue to the data area of
*	a display type node n if it is on the screen 
*********************************************************************/
void window_upd_disp(n)
struct node* n;
{
	Rectangle r,ad;
	int i, j;
	char *c;
	Bitmap *bm;
	Point q;
	struct node *par;

	r = n->image_size;

	/* place this node at top of list for drawing */
	if((par = n->parent) != (struct node *)NULL)
	{
	    for (i=0; i<par->numchildren; i++)
	    {
		if(par->child[i] == n)
		{
			for(j=i-1; j>=0; j--)
				par->child[j+1] = par->child[j];
			par->child[0] = n;
			break;
		}
	    }
	}

	if(n->window_flag & WB_PLOT)
	{
		ad.origin = add(r.origin,fPt(GUARDX,GUARDY+2*TEXT_HEIGHT+6));
		ad.corner = sub(r.corner,Pt(GUARDX,GUARDY));
		upd_plot(n,ad);
	}
	else
	{
	   /* for text displays */
		/* find data area */
		ad.origin.x = r.origin.x + GUARDX;
		ad.corner.x = r.corner.x - GUARDX;
		ad.origin.y = r.origin.y + (4 * TEXT_HEIGHT) + GUARDY + 12;
		ad.corner.y = r.corner.y - GUARDY - 2;


		if(n->numvalues == 0)
		{
			texture(n->image, ad, &T_white, F_STORE);
			return;
		}
	
		/* scroll up display */
		    /* copy all lines */
		r = rsubp(ad,ad.origin);
		bm = balloc(r);
		bitblt(n->image, ad, bm, Pt(0,0),F_STORE);
		    /* clear display area */
		texture(n->image, ad, &T_white, F_STORE);
		    /* restore all but first line */
		r.origin.y += TEXT_HEIGHT;
		bitblt(bm, r, n->image, ad.origin, F_STORE);
		bfree(bm);

		/* add the new last line  */
		q.y = ad.origin.y + (n->maxnumvalues-1) * TEXT_HEIGHT;
		q.x = ad.origin.x;
		for (i=0; i<n->numdim; i++)
		{
			makevalue(lbuf,n->dfmt[i],n->data[i][(n->numvalues-1)]);
			string(&smallfont, lbuf, n->image, q, F_STORE);
			q.x += 100;
		}
	}

	if(n->parent == currentnode)    /* this node is on the screen */
		screen_node_draw(n);	/* the draw it on screen */
}

/********************************************************************
* void bmswap(&destBitmap,&srcBitmap,srcrect, destrect); 
*
*	This routine does an in-place exchange of rect srcrect
*	in bitmap srcBitmap with rectangle destrect in bitmap
*	destBitmap.  (similar (but slower) to screenswap()3R.
*	action is undefined if srcrect != destrect in size and shape
*	but not checked here due to speed reqt's
*********************************************************************/

void bmswap(db,sb,sr,dr) 
Bitmap *db, *sb;
Rectangle sr,dr;
{

	/* blit back and forth 3 times with XOR */
	bitblt(sb,sr,db,dr.origin,F_XOR);
	bitblt(db,dr,sb,sr.origin,F_XOR);
	bitblt(sb,sr,db,dr.origin,F_XOR);
	
}

/********************************************************************
* void w_kvalue_draw(n, r, e)
*
*	This routine places the slider and value fields of knob
*	element e in knob n with elements of KNOB background in Rect r.
*
*** note:  this routine should be called in conjunction with 
***	   w_kvalue_undraw() below and only from the screen_node_draw()
***	   and screen_value_update() routines.
*********************************************************************/

void w_kvalue_draw(n, r, e)
struct node *n;
Rectangle r;
int e;
{
	Rectangle scr;
	Rectangle scl;
	char *c;

	/* compute new pointer position */
	/*   if a regular knob element  */
	if(e < n->maxnumvalues)
	{
		scr = knob_slide_rect(n, r, e);
		bmswap(n->image,&n->knobslide,KVSLIDERECT(e),scr); 
	}
	else
	/*    a width control element  */
	{
		scr = knob_slide_rect(n, r, e);
		bmswap(n->image,&n->knobslide,KHSLIDERECT,scr); 

		/* don't bother to show the value */
		return;
	
	}
	
	
	/* show the current value */
	if (n->type != ENUM)
	{
		/* add the value field */
		makevalue(lbuf, n->fmt, n->value[e]);
		string(&TEXT_FONT, lbuf, n->image,
			sub(r.origin,Pt(0,TEXT_HEIGHT+4)), F_STORE);
	}
	else
	{
		scl.origin.x = scr.origin.x + 38;
		scl.origin.y = scr.origin.y + 3;
		scr = raddp(n->image_size, n->rel_to_origin);
		scl.corner.x = scr.corner.x - 1;
		scl.corner.y = scl.origin.y + TEXT_HEIGHT + 2;
		texture(n->image, scl, &T_black, F_XOR);
	}
	
}

/********************************************************************
* void w_kvalue_undraw(n, r, i)
*
*	This routine removes the slider and value fields of knob
*	element i in knob n with elements of KNOB background in Rect r.
*
*** note:  this routine should be called in conjunction with 
***	   w_kvalue_draw() above and only from the screen_node_draw()
***	   and screen_value_update() routines.
*********************************************************************/

void w_kvalue_undraw(n, r, e)
struct node *n;
Rectangle r;
int e;
{
	Rectangle scr;
	Rectangle scl;
	char *c;

	/* compute existing pointer position */
	/*   if a regular knob element  */
	if(e < n->maxnumvalues)
	{
		scr = knob_slide_rect(n, r, e);
		bmswap(n->image,&n->knobslide,KVSLIDERECT(e),scr); 
	}
	else
	/*    a width control element  */
	{
		scr = knob_slide_rect(n, r, e);
		bmswap(n->image,&n->knobslide,KHSLIDERECT,scr); 

		/* don't bother to erase the value */
		return;
	
	}
	
	
	/* erase the current value */
	if (n->type != ENUM)
	{
		/* wipe out the value field */
		scr.origin = sub(r.origin,Pt(0,TEXT_HEIGHT+4));
		scr.corner.x = r.corner.x + 6;
		scr.corner.x = r.origin.x + n->element_width;
		scr.corner.y = r.origin.y - 1;
		texture(n->image, scr, &T_lightgrey, F_STORE);
	}
	else
	{
		scl.origin.x = scr.origin.x + 38;
		scl.origin.y = scr.origin.y + 3;
		scr = raddp(n->image_size, n->rel_to_origin);
		scl.corner.x = scr.corner.x - 1;
		scl.corner.y = scl.origin.y + TEXT_HEIGHT + 2;
		texture(n->image, scl, &T_black, F_XOR);
	}
	
}


/********************************************************************
* int w_adjust(n, mxy, but)
*
*	This routine adjusts the slider and value fields of KNOB
*   	n if mouse_on_window (mxy_on_w) is within one of the hot spots of the
*	knob.  Action of coarse of fine is determined by button (but).
*	returns -1 if not in subwindow or +n if in subwindow n
*********************************************************************/

int w_adjust(n, mxy_on_w, but)
struct node *n;
Point mxy_on_w;
int but;
{
	int i,j,k;
	Rectangle knobrect, knobelerect, sliderect, temprect;
	Point p, q,qprime;
	float drange, range, gap, temp, v;
	char *cp;
	int naptime;
	Bitmap *kstore;
	Point mxy;
	int retcode;


    /* determine where on window the mouse is */

    /* if in utility function box */
	if ((n->window_flag & WB_UTIL) &&
		(ptinrect(mxy_on_w, WB_UTILarea(n->window_rect))))
	{
	    /* evenly space all values of the knob */
	    /* from the first knob to the last knob selected's value */

		range = n->value[n->numvalues-1] - n->value[0];
		gap = range / (n->numvalues - 1);

		/* for all available elements of knob n except first & last */
		knobrect = n->image_size;
		temp = n->value[0];
		for (i=1; i<n->numvalues-1; i++)
		{
		    /* get the knob elements rectangle */
			knobelerect = knob_elem_rect(n, knobrect, i);
	
		    /* recompute */
			temp += gap;
			if ((n->type == ENUM)
				|| (n->type == FWINT)
				|| (n->type == VWINT))
			{
				/* round off integer values */
				k = (int)temp + .5;
				v = (float) k;
			}
			else
				v = temp;

			    /* undraw */
			w_kvalue_undraw(n,knobelerect,i);

			n->value[i] = v;

			    /* draw */
			w_kvalue_draw(n,knobelerect,i);
			
		}

		/* request re-draw of entire knob */
		return(-1);
	}

	
    /* determine where on image the mouse is */
	if ((n->window_flag & ANYBORDER) == 0)
	{
	    /* non scrollable, use whole window coord system */
		mxy = mxy_on_w;
	    /* if not found to be a subwindow, indicate a complete re-draw */
		retcode = -1;
	}
	else
	{
	    /* else check each sub_window */
		for (j=0; j<MAXSUBWIN; j++)
		{
			if ((n->window_flag & subwin(j)) &&
				(ptinrect(mxy_on_w, n->sw_rect[j])))
			{
				/* set mxy to point relative to image */
				/* compute offset into the sub_window */
				mxy = sub(mxy_on_w, (n->sw_rect[j]).origin);
				/* map offset onto the image */
				mxy = add(mxy, n->sw_origin[j]);
				/* redraw only this window */
				retcode = j;
				break;
			}
		}
		if (j == MAXSUBWIN) 	/* this should not occur */
					/* unless error in subwindow defines */
		{
			return(-1);
		}
	}
	

	/* for all available elements of knob n */
	for (i=0; i<n->numvalues; i++)
	{
	    /* get the knob elements rectangle */
		knobrect = n->image_size;
		knobelerect = knob_elem_rect(n, knobrect, i);
	
	    /* process only if mouse in this element */
		if (ptinrect(mxy,knobelerect))
		{
		    /* COARSE */
			if(but == 1)
			{
			    /* recompute */
				drange = (float)(knobelerect.corner.y -
						 knobelerect.origin.y - 16);
				range = n->max - n->min;
				gap = (float)(mxy.y - 8 - knobelerect.origin.y);
				temp = n->max - (gap/drange * range); 
				if ((n->type == ENUM)
					|| (n->type == FWINT)
					|| (n->type == VWINT))
				{
					/* round off integer values */
					k = (int)temp + .5;
					temp = (float) k;
				}
				if (temp > n->max)
					temp = n->max;
				if (temp < n->min)
					temp = n->min;
				

			    /* undraw */
				w_kvalue_undraw(n,knobelerect,i);

				n->value[i] = temp;

			    /* draw */
				w_kvalue_draw(n,knobelerect,i);

			}
		    /* FINE */
			else
			{
			    /* save away the knob element image */
				temprect=rsubp(knobelerect,knobelerect.origin);
				kstore = balloc(temprect);
				bitblt(n->image,knobelerect,
						kstore,Pt(0,0),F_STORE);

			    /* where's the slider */
				sliderect = knob_slide_rect(n,knobelerect,i);

			    /* determine up/down pull */
				if (mxy.y > sliderect.origin.y + 12)
					gap = -1.0;
				else if (mxy.y < sliderect.origin.y + 4)
					gap = 1.0;
				else
					gap = 0;

			    /* compute the delta */
				if ((n->type == ENUM)
					|| (n->type == FWINT)
					|| (n->type == VWINT))
				{
						
					temp = n->value[i] + gap;

					/* round off integer values */
					k = (int)temp + .5;
					temp = (float) k;

					naptime = 30;
				}
				else   /* FLOAT TYPES */
				{
				    /* draw the alternate knob image */
					q.x = knobelerect.origin.x;
					q.y = sliderect.origin.y + 4;
					qprime.x = knobelerect.corner.x;
					qprime.y = q.y;
					segment(n->image, q, qprime, F_XOR);
					q.y = sliderect.origin.y + 12;
					qprime.y = q.y;
					segment(n->image, q, qprime, F_XOR);

					q.y = knobelerect.origin.y;
					qprime.y = knobelerect.corner.y;
					for (j=0; j<2; j++)
					{
						q.x += VKNOB_WIDTH/3;
						qprime.x = q.x;
						segment(n->image, q,
							 qprime, F_XOR);
					}
					screen_node_draw(n);

				    /* parse the format to get lsd */
					for (cp=n->fmt; (*cp != '%'); cp++);
					for (cp++     ; (*cp != '.'); cp++);
					for (k=0,cp++ ; (*cp != 'f'); cp++)
					{
						k = k*10 + (int)(*cp - '0');
					}
					for (j=0,range=1.0; j<k; j++)
						range /= 10.0;
					/* range is now the least sig. digit*/
					
				    /* naptime is function of distance */
					naptime = 30;

					/* left / right determines multiplier*/
					j = knobelerect.corner.x -
						knobelerect.origin.x;
					k = mxy.x - knobelerect.origin.x;
					if (k < (j/3))
						gap *= range * 100;
					else if (k < (2*j/3))
						gap *= range * 10;
					else 
						gap *= range;

					temp = n->value[i] + gap;
				}


			    /* bind to ranges */
				if (temp > n->max)
					temp = n->max;
				if (temp < n->min)
					temp = n->min;

			    /* slow down the process */
					nap(naptime);

			    /* restore the knob element image */
				bitblt(kstore, kstore->rect,n->image,
						knobelerect.origin, F_STORE);
				bfree(kstore);

			    /* if button released, don't apply last update */
			    /* for float types because delay is before update */
				if((button2() == 0) && (n->type != ENUM))
					return(retcode);

			    /* undraw */
				w_kvalue_undraw(n,knobelerect,i);

				n->value[i] = temp;

			    /* draw */
				w_kvalue_draw(n,knobelerect,i);
				
			}

			/* we found one, adjust is done so return */
			return(retcode);
		}
	}

	/* if variable width knob, check for resizing */
	if ((n->type == VWINT) || (n->type == VWFLT))
	{
	    /* get the knob elements rectangle */
		knobrect = n->image_size;
		knobelerect = knob_elem_rect(n, knobrect, n->maxnumvalues);
	
	    /* process only if mouse in this element */
		if (ptinrect(mxy,knobelerect))
		{
		    /* recompute */
			drange = (float)(knobelerect.corner.x -
					 knobelerect.origin.x - 16);
			range = n->maxnumvalues - 1;
			gap = (float)(mxy.x - knobelerect.origin.x);
			temp =  (gap/drange * range); 

			/* round off integer values */
			k = (int)temp + .5;
			temp = (float) k;

			if (temp > (n->maxnumvalues - 1))
				temp = n->maxnumvalues - 1;
			if (temp < 0)
				temp = 0;
				
			temp = temp + 1;

		    /* undraw */
			w_kvalue_undraw(n,knobelerect,n->maxnumvalues);

			i = n->numvalues;
			n->numvalues = temp;

		    /* draw */
			w_kvalue_draw(n,knobelerect,n->maxnumvalues);

		    /* fix the knobs proper */
			if (i < temp)		/* need to add knob */
			{
				for( ; i<temp; i++)
				{
	    			/* locate and draw the vertical knob */
		    		/* get the element's rectangle */
				    knobelerect = knob_elem_rect(n,knobrect,i);
			
				    texture(n->image, knobelerect, &T_white,
						 F_STORE);

		    		/* the scale elements */
				    q = add(knobelerect.origin,Pt(14,0));
				    bitblt(VKNOB,VKNOBTOP,n->image,q,F_STORE);
				    for (j=1; j<7; j++)
				    {
					q = add(q,Pt(0,14));

					bitblt(VKNOB,VKNOBMID, n->image,
						 q, F_STORE);
					bitblt(VKNOB,VKNOBTICK, n->image,
						Pt(knobelerect.origin.x,q.y),
							 F_STORE);
				    }
				    q = add(q,Pt(0,14));
				    bitblt(VKNOB,VKNOBBOT, n->image,q ,F_STORE);
				    bitblt(VKNOB,VKNOBTICK, n->image,
						Pt(knobelerect.origin.x,q.y),
							 F_STORE);
			
		    		/* the knob value and slider */
				    w_kvalue_draw(n,knobelerect,i);
				}
			}
			if (i > temp)		/* need to blank knob */
			{
				for( ; i>temp; )
				{
				    i--;
				    knobelerect = knob_elem_rect(n,knobrect,i);
				    w_kvalue_undraw(n,knobelerect,i);
			
				    texture(n->image, knobelerect, &T_lightgrey,
						 F_STORE);
				}
			}
		}
	}

	return(retcode);

}

/********************************************************************
* int w_edit(n, mxy, but)
*
*	This routine checks for mouse in edit function hotspots,
*	then performs the move, reshape, and scroll functions
*	for all panelfeatures.  n is the node ptr, mxy is the mouse
*	pointer with respect to the window origin and but is the button
*	number pressed.
*	returns -1 if an edit function occurred indicating to caller
*	that a node redraw should be performed, 
*	returns a -2 if move or reshape indicating that entire screen
*	should be refreshed
*	returns a -99 if error that is fatal
*	else 0 if no action found 
*********************************************************************/

int w_edit(n, mxy_on_w, but)
struct node *n;
Point mxy_on_w;
int but;
{
	int i,j,k;
	Rectangle knobrect, temprect;
	Point p, q,qprime;
	float drange, temp;
	char *cp;
	Point mxy;
	int retcode;


    /* determine where on window the mouse is */

    /* if in vertical scroll boxes */
	if ((n->window_flag & WB_VSCR) &&
		 (ptinrect(mxy_on_w, WB_VSCRarea(n->window_rect))))
	{
	    while(button12())
	    {
		temprect = WB_VSCRarea(n->window_rect);

	    /* move to the bottom ? */
		if(ptinrect(mxy_on_w, WB_decr(temprect)))
		{
			if(n->sbarcur[VERT] < n->sbarmax[VERT])
			{
				n->sbarcur[VERT]++;
				
				for (i=0; i<MAXSUBWIN; i++)
				{
					if((n->window_flag & subwin(i)) &&
					   (n->subwindow_flag[i] & VSCRL))
						n->sw_origin[i].y++;
				}
			}
		}

	    /* move to the top ? */
		if(ptinrect(mxy_on_w, WB_incr(temprect)))
		{
			if(n->sbarcur[VERT] > n->sbarmin[VERT])
			{
				n->sbarcur[VERT]--;
				
				for (i=0; i<MAXSUBWIN; i++)
				{
					if((n->window_flag & subwin(i)) &&
					   (n->subwindow_flag[i] & VSCRL))
						n->sw_origin[i].y--;
				}
			}
		}

	    /* move with cursor ? */
		temprect = WB_VSCRrect(temprect);
		if(ptinrect(mxy_on_w, temprect))
		{
			drange = (float)(temprect.corner.y - mxy_on_w.y) /
				(float)(temprect.corner.y - temprect.origin.y);
			drange *= (float)(n->sbarmax[VERT]-n->sbarmin[VERT]);
			n->sbarcur[VERT] = n->sbarmax[VERT] - (int)drange;
				
			for (i=0; i<MAXSUBWIN; i++)
			{
				if((n->window_flag & subwin(i)) &&
				   (n->subwindow_flag[i] & VSCRL))
					n->sw_origin[i].y = n->sbarcur[VERT];
			}
			mxy_on_w.y = mouse.xy.y - n->rel_to_origin.y;
		}

	    screen_node_draw(n);
	    }
	    return(-1);
	}

    /* if in horizontal scroll boxes */
	if ((n->window_flag & WB_HSCR) &&
		 (ptinrect(mxy_on_w, WB_HSCRarea(n->window_rect))))
	{

	    while(button12())
	    {
		temprect = WB_HSCRarea(n->window_rect);

	    /* move to the left ? */
		if(ptinrect(mxy_on_w, WB_incr(temprect)))
		{
			if(n->sbarcur[HORIZ] > n->sbarmin[HORIZ])
			{
				n->sbarcur[HORIZ]--;
				
				for (i=0; i<MAXSUBWIN; i++)
				{
					if((n->window_flag & subwin(i)) &&
					   (n->subwindow_flag[i] & HSCRL))
						n->sw_origin[i].x--;
				}
			}
		}
		
	    /* move to the right ? */
		if(ptinrect(mxy_on_w, WB_decr(temprect)))
		{
			if(n->sbarcur[HORIZ] < n->sbarmax[HORIZ])
			{
				n->sbarcur[HORIZ]++;
				
				for (i=0; i<MAXSUBWIN; i++)
				{
					if((n->window_flag & subwin(i)) &&
					   (n->subwindow_flag[i] & HSCRL))
						n->sw_origin[i].x++;
				}
			}
		}
		
	    /* move with cursor ? */
		temprect = WB_HSCRrect(temprect);
		if(ptinrect(mxy_on_w, temprect))
		{
			drange = (float)(temprect.corner.x - mxy_on_w.x) /
				(float)(temprect.corner.x - temprect.origin.x);
			drange *= (float)(n->sbarmax[HORIZ]-n->sbarmin[HORIZ]);
			n->sbarcur[HORIZ] = n->sbarmax[HORIZ] - (int)drange;
				
			for (i=0; i<MAXSUBWIN; i++)
			{
				if((n->window_flag & subwin(i)) &&
				   (n->subwindow_flag[i] & HSCRL))
					n->sw_origin[i].x = n->sbarcur[HORIZ];
			}
			mxy_on_w.x = mouse.xy.x - n->rel_to_origin.x;
		}

	    screen_node_draw(n);
	    }
	    return(-1);
	}

    /* if in reshape scroll box */
	if ((n->window_flag & (WB_HSCR | WB_VSCR)) &&
		 (ptinrect(mxy_on_w, WB_RESHAPEarea(n->window_rect))))
	{

		knobrect = raddp(n->window_rect,n->rel_to_origin);

	/* if not a plot */
	    if((n->type != DISPLAY) || ((n->window_flag & WB_PLOT) == 0))
	    {
		q = n->image_size.origin;
		qprime = n->image_size.corner;
		if( (n->window_flag & WB_HSCR)&&(n->window_flag & WB_VSCR))
			qprime = add(qprime,Pt(WBW,WBH));

		temprect = knobrect;
		while(button12())
		{
			box(&display,temprect,F_XOR);
			mxy = add(mouse.xy,Pt(8,8));
			p = sub(mxy,n->rel_to_origin);
			if(n->window_flag & WB_HSCR)
			{
				if( ((q.x+200)<p.x) && (qprime.x >= p.x) &&
				 	(mxy.x < MAXX-2))
					n->window_rect.corner.x = p.x;
				if((qprime.x <= p.x) && (mxy.x < MAXX-2))
					n->window_rect.corner.x = qprime.x;
			}
			if(n->window_flag & WB_VSCR)
			{
				if( (q.y+200 < p.y) && (qprime.y >= p.y) &&
				 	(mxy.y < MAXY-2))
					n->window_rect.corner.y = p.y;
				if((qprime.y <= p.y) && (mxy.y < MAXY-2))
					n->window_rect.corner.y = qprime.y;
			}
			box(&display,temprect,F_XOR);
			temprect = raddp(n->window_rect,n->rel_to_origin);
		}

		texture(&display,knobrect,&T_white,F_STORE);
		n->window_flag &= ~W_INIT;
		bfree(n->sbar[RESHAPE]);

		if(n->window_flag & WB_HSCR)
		{
			bfree(n->sbar[HORIZ]);
		}
		if(n->window_flag & WB_VSCR)
		{
			bfree(n->sbar[VERT]);
		}
	    }
	    else
	/* is a plot */
	    {
		q = n->image_size.origin;
		temprect = knobrect;

		/* sweep out an area */
		while(button12())
		{
			box(&display,temprect,F_XOR);
			mxy = add(mouse.xy,Pt(8,8));
			p = sub(mxy,n->rel_to_origin);
			if(n->window_flag & WB_HSCR)
			{
				if( ((q.x+200)<p.x) && (mxy.x < MAXX-2))
					n->window_rect.corner.x = p.x;
			}
			if(n->window_flag & WB_VSCR)
			{
				if( (q.y+200 < p.y) && (mxy.y < MAXY-2))
					n->window_rect.corner.y = p.y;
			}
			box(&display,temprect,F_XOR);
			temprect = raddp(n->window_rect,n->rel_to_origin);
		}

		cursswitch(busycursor);
		texture(&display,knobrect,&T_white,F_STORE);

		/* clear out the window */
		bfree(n->sbar[RESHAPE]);
		bfree(n->sbar[HORIZ]);
		bfree(n->sbar[VERT]);
		bfree(n->image);

		/* clear out window params */
		n->window_flag &= ~W_INIT;
		
	    /* recompute and redraw the entire thing from scratch */

		temprect = rsubp(temprect, n->rel_to_origin);
		/* set up scroll bars and make image fit the new window */
		n->image_size.origin = temprect.origin;
		n->image_size.corner = sub(temprect.corner,Pt(WBH,WBW));
		n->window_rect = temprect;

    		/* initialize the bitmap for the image */
		if( (n->image = balloc(n->image_size)) == (Bitmap *)NULL)
		{
			Sprintf(lbuf,"Bitmap alloc for <%s> failed",n->oname);
			warn(lbuf);
			/* error */
			return(-99);
		}
	    }
	    n->window_flag |= W_RESIZE;
	    initscroll(n);
	    window_node_draw(n);
	    n->window_flag &= ~W_RESIZE;
	    cursswitch( normcursor );
	    return(-2);
	}

    /* if in move scroll box */
	if (ptinrect(mxy_on_w, WB_MOVEarea(n->window_rect)))
	{
		
		knobrect = raddp(n->window_rect,n->rel_to_origin);
		temprect = knobrect;
		while(button12())
		{
			box(&display,temprect,F_XOR);
			q = sub(mouse.xy,Pt(10,10));
			qprime = add(n->window_rect.corner,q);
			if ((q.x > (MINX+2)) && (qprime.x < (MAXX-2)) &&
		    		(q.y > (MINY+2)) && (qprime.y < (MAXY-2)) )
				n->rel_to_origin = q;
			box(&display,temprect,F_XOR);
			temprect = raddp(n->window_rect,n->rel_to_origin);
		}
		
		texture(&display,knobrect, &T_white,F_STORE);
		return(-2);
	}


    /* if in utility function box of display type only */
	if ((n->type == DISPLAY) && (n->window_flag & WB_UTIL) &&
		(ptinrect(mxy_on_w, WB_PUTILarea(n->window_rect))))
	{
	    if(but == 1) /* toggle from plot to list */
	    {
		cursswitch(busycursor);
		/* blank out the display */
		knobrect = raddp(n->window_rect,n->rel_to_origin);
		texture(&display,knobrect,&T_white,F_STORE);

		/* toggle the plot attribute */
		n->window_flag ^= WB_PLOT;

		/* free all allocated bitblits */
		if(n->window_flag & WB_HSCR)
			bfree(n->sbar[HORIZ]);
		if(n->window_flag & WB_VSCR)
			bfree(n->sbar[VERT]);
		if((n->window_flag & WB_VSCR) || (n->window_flag & WB_HSCR))
			bfree(n->sbar[RESHAPE]);
		bfree(n->image);

		/* clear out window params */
/*
		n->window_flag &= ~W_INIT;
		n->window_flag &= ~WB_HSCR;
		n->window_flag &= ~WB_VSCR;
*/
n->window_flag &= (WB_PLOT | WB_UTIL);
		
	    /* recompute and redraw the entire thing from scratch */

		/* save the current window */
		temprect = n->window_rect;


		/* enforce the current window rect */
		if (n->window_flag & WB_PLOT)
		{
		    /* if plot type */
		    /* set up scroll bars and make image fit the window */
			n->image_size.origin = temprect.origin;
			n->image_size.corner = sub(temprect.corner,Pt(WBH,WBW));
			n->window_flag |= (WB_HSCR | WB_VSCR);
			n->window_rect = temprect;
		}
		else
		{
			/* compute the image size and desired window */
			sizenode(n);	

			/* get computed window area */
			q = sub(n->window_rect.corner, n->window_rect.origin);

			/* get desired window area */
			qprime = sub(temprect.corner, temprect.origin);


			/* if computed taller than desired, add scroll */
			if (q.y > qprime.y)
			{
				n->window_rect.corner.y = qprime.y;
				n->window_rect.corner.x += WBW;
				n->window_flag |=  WB_VSCR;
			}
		}

    		/* initialize the bitmap for the image */
		if( (n->image = balloc(n->image_size)) == (Bitmap *)NULL)
		{
			Sprintf(lbuf,"Bitmap alloc for <%s> failed",n->oname);
			warn(lbuf);
			/* error */
			return(-99);
		}
		n->window_flag &= ~W_INIT;
		initscroll(n);
		window_node_draw(n);

		cursswitch( normcursor );
		return(-2);
	    }
	    else /* button = 2:  autoscale plot */
	    {
		cursswitch(busycursor);
		/* blank out the display */
		knobrect = raddp(n->window_rect,n->rel_to_origin);
		texture(&display,knobrect,&T_white,F_STORE);

		/* recompute the axis limits */
		scaleaxes(n);

		/* refresh the screen */
		window_node_draw(n);

		cursswitch(normcursor);
		return(-2);
	    }

	}
	return(0);
}
