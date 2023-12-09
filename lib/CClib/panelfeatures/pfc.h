
/**************************************************************************/
/* PANELFEATURES Package    Release:  1.0    Release Date: 1/15/89        */
/*                          Provider: J. D. Iorio  (speedy!jdi)           */
/**************************************************************************/



/*********************************************************************
* PFC.H
* 
*	Definition for node data structure for non 630 MTG
*	interface processes for PANELFEATURES
*
*       Copyright (c) 1988 AT&T  
*       All Rights Reserved     
*
*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T  
*       The copyright notice above does not evidence any    
*       actual or intended publication of such source code.
*
* HISTORY:
* created: jdi - 7/1/88
**********************************************************************/


struct node
{
	char *name;		/* current name */
	char *oname;		/* official name */
	char *fmt;		/* label format */
	char *scalelab;		/* label for scale */
	struct node *parent;		/* pointer to parent */
	struct node **child;
	char **labels;	/* storage for enum & display labels */
	float *value;		/* storage for knob type values */
	float **data;		/* storage for display type values */
	float *dmin;		
	float *dmax;		
	char **dfmt;
	char **dscalelab;		/* label for display scales */
	
	float max;		/* limits */
	float min;
	
	int element_width;	/* computed width of each knob element */
	
	char **image;		/* storage of ascii display object */

	short orig_x; 		/* where on screen(origin in parents screen) */
	short orig_y;

	short current_item;	/* item which is at curs_x,y */

	short curs_x; 		/* location of cursor on this node's screen */
	short curs_y;

	int	window_flag;	/* descriptor of this window */

	int numchildren;	/* number of children */
	int style;		/* style of display */


	int numvalues;		/* current number of switches */
	int maxnumvalues;	/* maximum number of switches */

	int numdim;
	int attribute;		/* misc attribute flag */

	char type;		/* type of node */
	char showflag;		/* drawing control */

};


