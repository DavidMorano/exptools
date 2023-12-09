
/**************************************************************************/
/* PANELFEATURES Package    Release:  1.0    Release Date: 1/15/89        */
/*                          Provider: J. D. Iorio  (speedy!jdi)           */
/**************************************************************************/







struct node
{
	char dummy1;
	char dummy2;
	char dummy3;
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
	
	Bitmap knobslide;	/* storage for knob slider images */
	int element_width;	/* computed width of each knob element */
	
	Bitmap *image;		/* bitmap of entire object */
	Rectangle image_size;   /* screen space needed to draw whole feature */ 
	Rectangle window_rect;	/* outside of window on screen */
	Point	rel_to_origin;	/* location of window orig relative to parent */
	Point sw_origin[5];	/* origin of viewable subwindow */
	Rectangle sw_rect[5];	/* size of viewable subwindow */
	int  subwindow_flag[5];	/* descriptor of each subwindow */
	int	window_flag;	/* descriptor of this window */

	Bitmap *sbar[3];	/* scroll bar storage */
	Point   sbar_orig[3];	/* origin of bar w/respect to window origin*/
	int 	sbarmin[3];	/* min range of scroll */
	int 	sbarmax[3];	/* max range of scroll */
	int	sbarcur[3];	/* current scroll position */

	int numchildren;	/* number of children */
	int style;		/* style of display */


	int numvalues;		/* current number of switches */
	int maxnumvalues;	/* maximum number of switches */

	int numdim;
	int attribute;		/* misc attribute flag */

	char type;		/* type of node */
	char showflag;		/* drawing control */

	char dummy4;
	char dummy5;
	char dummy6;

};


#include "gidef.h"
