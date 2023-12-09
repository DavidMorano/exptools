
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

extern void warn();
extern char lbuf[];
extern void makevalue();

void autoscale();
float divide_plot();
void draw_axis();
int map_point();
void upd_plot();

/********************************************************************/


#define AXWIDTH 100
#define XAXIS	1
#define YAXIS	2
#define ZAXIS	3

/********************************************************************
 *	void draw_plot(n,r)
 *	
 *	This function sets up a plot for the data stored in node n
 *    into n->image in the rectangle r.  Node n is modified to set up
 *    the subwindow and scroll information needed for this plot
 *	NOTE: the calling routine should place the title and r should
 *	describe the axis/plot region only.
 ********************************************************************/

void draw_plot(n,r)
struct node *n;
Rectangle r;
{
	Rectangle xaxbx, yaxbx, zaxbx, pltbx;
	Point p;
	int i, j, k;
	float zslope;
	

	texture(n->image, r, &T_white, F_STORE);


    /* compute the axes and plot areas */
	zslope = divide_plot(n, r, &xaxbx, &yaxbx, &zaxbx, &pltbx);

	
    /* draw the axes */
	/* note Z goes first so Y doesn't get erased by descenders of Z label*/
	if (n->numdim > 2)
		draw_axis(ZAXIS, n, zaxbx);
	draw_axis(XAXIS, n, xaxbx);
	draw_axis(YAXIS, n, yaxbx);

    /* add any existing points */
	j = n->numvalues;
	for (i=0; i<j; i++)
	{
		n->numvalues = i+1;
		upd_plot(n,r);
	}
	n->numvalues = j;


    /* setup single window for now */
	if((n->window_flag & W_INIT) == 0)
	{
	    n->window_flag |= subwin(0);
	    n->sw_origin[0] = n->image_size.origin;
	    n->sw_rect[0].origin = n->window_rect.origin;
	    n->sw_rect[0].corner.x = n->window_rect.corner.x-16;
	    n->sw_rect[0].corner.y = n->window_rect.corner.y-16;
	    n->subwindow_flag[0] = HSCRL | VSCRL;
  
	    n->sbarmin[VERT] = n->sw_origin[0].y;
	    n->sbarmax[VERT] = n->image_size.corner.y -
		(n->sw_rect[0].corner.y-n->sw_rect[0].origin.y);
	    n->sbarcur[VERT] = n->sbarmin[VERT];
  
	    n->sbarmin[HORIZ] = n->sw_origin[0].x;
	    n->sbarmax[HORIZ] = n->image_size.corner.x -
		(n->sw_rect[0].corner.x-n->sw_rect[0].origin.x);
	    n->sbarcur[HORIZ] = n->sbarmin[HORIZ];

	}
}



/********************************************************************
 *	void upd_plot(n,r)
 *	
 *	This function adds the last data point in node n to the plot
 *    associated with the node by storing the new line
 *    into n->image in the rectangle r. 
 ********************************************************************/

void upd_plot(n,r)
struct node *n;
Rectangle r;
{
	Rectangle xaxbx, yaxbx, zaxbx, pltbx;
	Point curp, prev1, prev2;
	float zslope;
	float xmn, xmx, ymn, ymx, zmn, zmx;
	int xoff, yoff, zyoff, zxoff;
	register int this, i;
	register float *dx, *dy, *dz;


	this = n->numvalues - 1;

    /* compute the axes and plot areas */
	zslope = divide_plot(n, r, &xaxbx, &yaxbx, &zaxbx, &pltbx);

    /* determine the plot scale ranges and compute the current point */
	if (n->numdim == 1)
	{
		xmn = (float)0;
		xmx = (float)n->maxnumvalues;
		ymn = n->dmin[0];
		ymx = n->dmax[0];

		xoff = map_point(xmn, xmx, (float)n->numvalues,
				 xaxbx.origin.x, xaxbx.corner.x);
		dy = n->data[0];
		yoff = map_point(ymn, ymx, dy[this],
				 yaxbx.corner.y, yaxbx.origin.y);
		curp = fPt(xoff, yoff);
	}
	else
	{
		xmn = n->dmin[0];
		xmx = n->dmax[0];
		ymn = n->dmin[1];
		ymx = n->dmax[1];

		dx = n->data[0];
		xoff = map_point(xmn, xmx, dx[this],
				 xaxbx.origin.x, xaxbx.corner.x);
		dy = n->data[1];
		yoff = map_point(ymn, ymx, dy[this],
				 yaxbx.corner.y, yaxbx.origin.y);
		curp = fPt(xoff, yoff);

		if (n->numdim > 2)
		{
			zmn = n->dmin[2];
			zmx = n->dmax[2];
			dz = n->data[2];
			zyoff = map_point(zmn, zmx, dz[this],
				 0,zaxbx.corner.y-zaxbx.origin.y);
			zxoff = (int)((float)zyoff / zslope);
			zyoff *= -1;
			curp = add(curp, Pt(zxoff, zyoff));
		}
	}

    /* plot the point and connect to existing points as needed */
	point(n->image, curp, F_STORE);
	if(n->numvalues < 2)
	{
		return;
	}
	else
	{
		if (n->numdim == 1)
		{
		    /* always connect */
			this = this - 1;
			xoff = map_point(xmn, xmx, (float)(n->numvalues-1),
				 xaxbx.origin.x, xaxbx.corner.x);
			yoff = map_point(ymn, ymx, dy[this],
				 yaxbx.corner.y, yaxbx.origin.y);
			prev1 = fPt(xoff, yoff);
			segment(n->image, prev1, curp, F_STORE);
		}
		else if (n->numdim == 2)
		{
		    /* connect to prev. only if this x > previous x */
		    if (dx[this] > dx[this-1])
		    {
			xoff = map_point(xmn, xmx, dx[this-1],
				 xaxbx.origin.x, xaxbx.corner.x);
			yoff = map_point(ymn, ymx, dy[this-1],
				 yaxbx.corner.y, yaxbx.origin.y);

			prev1 = fPt(xoff, yoff);
			segment(n->image, prev1, curp, F_STORE);
		    }
		}
		else  /* 3-D */
		{
		    /* connect to prev. only if this x > previous x */
		    /* and this z == previous z */
		    if ((dx[this] > dx[this-1]) &&
			(dz[this] == dz[this-1]))
		    {
			xoff = map_point(xmn, xmx, dx[this-1],
				 xaxbx.origin.x, xaxbx.corner.x);
			yoff = map_point(ymn, ymx, dy[this-1],
				 yaxbx.corner.y, yaxbx.origin.y);

			prev1 = fPt(xoff, yoff);

			zyoff = map_point(zmn, zmx, dz[this-1],
			 	0,zaxbx.corner.y-zaxbx.origin.y);
			zxoff = (int)((float)zyoff / zslope);
			zyoff *= -1;
			prev1 = add(prev1, Pt(zxoff, zyoff));

			segment(n->image, prev1, curp, F_STORE);
		    }

		    /* find the most recent previous point where z's
		       are not equal but x's are and connect to it */

		    for(i=n->numvalues-2; i>=0; i--)
		    {
			if((dz[this] != dz[i]) &&
			   (dx[this] == dx[i]))
			{
				xoff = map_point(xmn, xmx, dx[i],
				 	xaxbx.origin.x, xaxbx.corner.x);
				yoff = map_point(ymn, ymx, dy[i],
				 	yaxbx.corner.y, yaxbx.origin.y);

				prev2 = fPt(xoff, yoff);

				zyoff = map_point(zmn, zmx, dz[i],
			 		0,zaxbx.corner.y-zaxbx.origin.y);
				zxoff = (int)((float)zyoff / zslope);
				zyoff *= -1;
				prev2 = add(prev2, Pt(zxoff, zyoff));

				segment(n->image, prev2, curp, F_STORE);
				break;
			}
		    }
		}
	}
	
}

/***************************************************************************/
/*	void scaleaxes(n)
**
**	This function recomputes the axis limits based on the current data
**	in node n and updates the min, max for each axis
*/
/***************************************************************************/
void scaleaxes(n)
struct node *n;
{
	register int i, j;
	register float newmax, newmin;
	float d;

	if(n->numvalues < 2)
		return;		/* don't scale if no data */


	for(i=0; i<n->numdim; i++)
	{
		newmax = -1000000.;
		newmin = 1000000.;

		for(j=0; j<(n->numvalues-1); j++)
		{
			d = n->data[i][j];

			newmin = (d < newmin)? d : newmin;
			newmax = (d > newmax)? d : newmax;
		}

		if(newmin >= newmax)
		{
			newmax += .5;
			newmin = newmax - 1.0;
		}
		n->dmin[i] = newmin;
		n->dmax[i] = newmax;
		
	}
}


/***************************************************************************/
/*	void draw_axis(axisid, n, r)
**
**	This function draws the axis text in the rectangle r
**	based on the information in node n into node n's image 
*/
/***************************************************************************/
void draw_axis(ax, n, r)
int ax;
struct node *n;
Rectangle r;
{
	float min, max, v;
	int tic;
	float step;
	float slope;
	int swidth;
	int i;
	char *label, *scale, *fmt;
	char *cp;
	Point o, p, q;
	
	if (ax == XAXIS)
	{
		if(n->numdim == 1)
		{
			min = (float)0;
			max = (float)n->maxnumvalues;
			step = max - min;
			label = "Measurement Number";
			scale = "";
			fmt = "%-4.0f";
		}
		else
		{
			autoscale(5, n->dmin[0], n->dmax[0], &tic,
					&(n->dmin[0]), &(n->dmax[0]));
			min = n->dmin[0];
			max = n->dmax[0];
			step = (max-min)/(float)tic;
			label = n->labels[0];
			scale = n->dscalelab[0];
			fmt = n->dfmt[0];
		}
		
		/* place the labels */
		swidth = strwidth(&smallfont,label);
		p.x = r.origin.x + ((r.corner.x - r.origin.x)-swidth)/2;
		p.y = r.corner.y - 3 * TEXT_HEIGHT;
		string(&smallfont,label,n->image,p,F_STORE);
		swidth = strwidth(&smallfont,scale);
		p.x = r.origin.x + ((r.corner.x - r.origin.x)-swidth)/2;
		p.y = r.corner.y - 2 * TEXT_HEIGHT;
		string(&smallfont,scale,n->image,p,F_STORE);
	
		
		/* place the scales */
		segment(n->image,r.origin, Pt(r.corner.x,r.origin.y),F_STORE);

		for(v=min; v<=max; v+=step)
		{
			p.x = map_point(min, max, v, r.origin.x, r.corner.x);
			p.y = r.origin.y;
			segment(n->image, p, Pt(p.x,p.y+3),F_STORE);
			
			makevalue(lbuf,fmt,v);
			for(i=0,cp=lbuf; *cp != '\0'; cp++)
			{
				if(*cp == '.')
					i = 1;
			}
			if(i == 1)
				for(cp-- ; *cp == '0'; cp--);
			if( *cp != '.')
				cp++;
			*cp = '\0';

			swidth = strwidth(&smallfont,lbuf);
			q.x = map_point(min, max, v, 0, swidth);
			p.x -= q.x;
			p.y += 5;
			string(&smallfont,lbuf,n->image,p,F_STORE);
			
		}
	}
	else if(ax == YAXIS)
	{
		if(n->numdim == 1)
			i=0;
		else
			i=1;

		autoscale(5, n->dmin[i], n->dmax[i], &tic,
					&(n->dmin[i]), &(n->dmax[i]));
		min = n->dmin[i];
		max = n->dmax[i];
		step = (max-min)/(float)tic;
		label = n->labels[i];
		scale = n->dscalelab[i];
		fmt = n->dfmt[i];
		
		/* place the labels */
		swidth = strwidth(&smallfont,label);
		p.x = r.origin.x + 4;
		p.y = r.origin.y + ((r.corner.y - r.origin.y)-swidth)/2;
		flipstring(&smallfont,label,n->image,p,F_STORE);
		swidth = strwidth(&smallfont,scale);
		p.x += TEXT_HEIGHT;
		p.y = r.origin.y + ((r.corner.y - r.origin.y)-swidth)/2;
		flipstring(&smallfont,scale,n->image,p,F_STORE);
	
		
		/* place the scales */
		segment(n->image,Pt(r.corner.x,r.origin.y),r.corner,F_STORE);

		for(v=min; v<=max; v+=step)
		{
			p.y = map_point(min, max, v, r.corner.y, r.origin.y);
			p.x = r.corner.x;
			segment(n->image, p, Pt(p.x-3,p.y),F_STORE);
			
			makevalue(lbuf,fmt,v);
			for(i=0,cp=lbuf; *cp != '\0'; cp++)
			{
				if(*cp == '.')
					i = 1;
			}
			if(i == 1)
				for(cp-- ; *cp == '0'; cp--);
			if( *cp != '.')
				cp++;
			*cp = '\0';

			swidth = strwidth(&smallfont,lbuf);
			p.x = p.x - swidth - 10;

			q.y = map_point(min, max, v, TEXT_HEIGHT, 1);
			p.y -= q.y;
			string(&smallfont,lbuf,n->image,p,F_STORE);
			
		}
	}
	else    /* ZAXIS */
	{
		i=2;

		autoscale(5, n->dmin[i], n->dmax[i], &tic,
					&(n->dmin[i]), &(n->dmax[i]));
		min = n->dmin[i];
		max = n->dmax[i];
		step = (max-min)/(float)tic;
		label = n->labels[i];
		scale = n->dscalelab[i];
		fmt = n->dfmt[i];
		
		/* place the labels */
		swidth = strwidth(&smallfont,label);
		slope = (float)(r.corner.y-r.origin.y)/
				(float)(r.corner.x-r.origin.x-AXWIDTH);
		p.x = r.origin.x + ((r.corner.x - r.origin.x-AXWIDTH)-swidth)/2;
		p.y = r.origin.y + ((r.corner.y - r.origin.y)-TEXT_HEIGHT)/2;
		for(cp = label; *cp != '\0'; cp++)
		{	
			lbuf[0] = *cp;
			lbuf[1] = '\0';
			string(&smallfont,lbuf,n->image,p,F_STORE);
			p.x += 7;
			p.y -= (int)(slope * 7.0);
		}

		swidth = strwidth(&smallfont,scale);
		p.x = r.origin.x + ((r.corner.x - r.origin.x-AXWIDTH)-swidth)/2;
		p.x +=  TEXT_HEIGHT;
		p.y = r.origin.y + ((r.corner.y - r.origin.y)-TEXT_HEIGHT)/2;
		p.y += (int)((float)(TEXT_HEIGHT) * slope);
		for(cp = scale; *cp != '\0'; cp++)
		{	
			lbuf[0] = *cp;
			lbuf[1] = '\0';
			string(&smallfont,lbuf,n->image,p,F_STORE);
			p.x += 7;
			p.y -= (int)(slope * 7.0);
		}
		
		/* place the scales */
		p.x = r.origin.x + AXWIDTH;
		p.y = r.corner.y;
		q.x = r.corner.x;
		q.y = r.origin.y;
		segment(n->image,p,q,F_STORE);


		for(v=min; v<=max; v+=step)
		{
			o.x = map_point(min, max, v, p.x, q.x);
			o.y = map_point(min, max, v, p.y, q.y);
			segment(n->image, o, Pt(o.x-6,o.y),F_STORE);
			
			makevalue(lbuf,fmt,v);
			for(i=0,cp=lbuf; *cp != '\0'; cp++)
			{
				if(*cp == '.')
					i = 1;
			}
			if(i == 1)
				for(cp-- ; *cp == '0'; cp--);
			if( *cp != '.')
				cp++;
			*cp = '\0';

			swidth = strwidth(&smallfont,lbuf);
			o.x = o.x - swidth - 20;
			
			i = map_point(min, max, v, TEXT_HEIGHT, 1);
			o.y -= i;
			string(&smallfont,lbuf,n->image,o,F_STORE);
			
		}
	}

}

/***************************************************************************/
/* int map_point(pmn, pmx, v, smn, smx)
**	This function scales v with respect to pmn,pmx and returns
**	the proper offset into the scale smn,smx.
**	For example: pmn.pmx are axis limits, v is value to plot,
**		     smn.smx are pixel limits, return is pixel coord of v.
*/
/***************************************************************************/
int map_point(pmn, pmx, v, smn, smx)
float pmn, pmx, v;
int smn, smx;
{
	float gap, ratio, offset;
	int ioffset;

	ratio = (v-pmn)/(pmx - pmn);
	gap = (float)(smx - smn);
	offset = gap * ratio;
	ioffset = (int)(offset +.5);
	
	return(smn+ioffset);
}
/***************************************************************************/
/* float divide_plot(n, r, &xaxbx, &yaxbx, &zaxbx, &pltbx)
**	This routine subdivides rectangle r into the regions
**	for plotting the axes and data and returns the slope of
**	the Z axis if numdim == 3, else 0;
*/
/***************************************************************************/
float divide_plot(n, r, xaxbx, yaxbx, zaxbx, pltbx)
struct node *n;
Rectangle r;
Rectangle *xaxbx, *yaxbx, *zaxbx, *pltbx;
{
	float sl;


	/* these are constant */
	yaxbx->origin.x = r.origin.x;
	yaxbx->corner.x = r.origin.x + AXWIDTH;
	yaxbx->corner.y = r.corner.y - (2*AXWIDTH)/3;

	xaxbx->origin = yaxbx->corner;
	xaxbx->corner.y = r.corner.y;

	pltbx->origin.x = yaxbx->corner.x;
	pltbx->origin.y = r.origin.y + AXWIDTH/10;
	pltbx->corner.x = r.corner.x - AXWIDTH/10;
	pltbx->corner.y = yaxbx->corner.y;

	
	if(n->numdim < 3)
	{
		yaxbx->origin.y = pltbx->origin.y;
		xaxbx->corner.x = pltbx->corner.x;
		sl = 0;
	}
	else
	{
		yaxbx->origin.y = r.origin.y + (r.corner.y - r.origin.y)/3;
		xaxbx->corner.x = r.corner.x - (r.corner.x - r.origin.x)/3;

		zaxbx->origin.x = r.origin.x;
		zaxbx->origin.y = pltbx->origin.y;
		zaxbx->corner.y = yaxbx->origin.y;
		zaxbx->corner.x = pltbx->corner.x -
				 (xaxbx->corner.x - xaxbx->origin.x);
		sl = (float)(zaxbx->corner.y - zaxbx->origin.y) /
			(float)(zaxbx->corner.x - zaxbx->origin.x - AXWIDTH);
	}

	return(sl);
}

/*******************************************************************/
/* void autoscale( olddiv, oldmin, oldmax, newdiv, newmin, newmax )
**
**	This routine adjusts the number of divisions and the min/max
**	values for an axis to be plotted so that the numbers are
**	"nice"
*/
/*******************************************************************/
void autoscale( olddiv, oldmin, oldmax, newdiv, newmin, newmax )
int	olddiv, *newdiv;
float	oldmin, oldmax, *newmin, *newmax;
{
	int	iexpon, idiv, ixfactor, iyfactor;   /* used for truncation */
	float	xfactor, yfactor;
	float	div;				    /* length of 1 division */
	float	expfac;
	double 	log10(), pow();

	if( oldmin == oldmax || olddiv == 0 )
	{
		*newdiv = 1;
		*newmin = oldmin-1;
		*newmax = oldmax;
		return;
	}

	if( oldmin > oldmax )	/* then switch min and max and */
	{ 			/* call this routine again     */
		autoscale( olddiv, oldmax, oldmin, newdiv, newmax, newmin );
		return;
	}

/*
**	This is where we compute a "nice" division length.  We take the most
**	significant digit of the exact division length and add one to it.
**	For example, a division length of .001978 becomes .002.
*/

	div = ( oldmax - oldmin ) / olddiv;
	div *= 0.999;			/* in case div is x.001eyy... */
	iexpon = log10( div );
	if( div < 1.0 )
		iexpon--;		/* so that mantissa is >= 1.0 */
	expfac = pow( 10.0, (float) iexpon );	/* exponent part */
	idiv = div/expfac;		/* integerized mantissa */
	idiv++;				/* add one */
	div = idiv * expfac;		/* rebuild the division length */

/*
**	Now we need to adjust the min/max values.  These values are changed
**	so that they are multiples of the new division length.  The number
**	of divisions is changed if needed.
*/

/*
**	Make the minimum a multiple of div
*/

	xfactor = oldmin/div;
	if( xfactor < 0.0 )
		xfactor -= 1.0;
	xfactor += 0.001;	/* in case factor = xxx.999... */
	ixfactor = xfactor;	/* truncate it */

/*
**	Make the maximum a multiple of div
*/

	yfactor = oldmax/div;
	if( yfactor > 0.0 )
		yfactor += 1.0;
	yfactor -= 0.001;	/* in case factor = xxx.000999... */
	iyfactor = yfactor;	/* truncate it */

/*
**	Return "nice" values for div, min, and max
*/

	*newmin = ixfactor * div;
	*newmax = iyfactor * div;
	*newdiv = iyfactor - ixfactor;

	return;
}
