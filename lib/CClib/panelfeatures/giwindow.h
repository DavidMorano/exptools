
/**************************************************************************/
/* PANELFEATURES Package    Release:  1.0    Release Date: 1/15/89        */
/*                          Provider: J. D. Iorio  (speedy!jdi)           */
/**************************************************************************/



/******************************** MAIN Window attribute flags ***/

#define NO_VSCR		0x0001		/* disallow vert scroll */
#define WB_VSCR		0x0002		/* Vertical scroll selected */

#define NO_HSCR		0x0004		/* disallow horiz scroll */
#define WB_HSCR		0x0008		/* Horiz. scroll  selected*/

#define WB_UTIL		0x0010		/* node has a utility function */
#define WB_PLOT		0x0020		/* display node should be plotted */

#define W_INIT		0x4000		/* set when window is initialized */
#define W_RESIZE	0x8000		/* set when window is resized */

#define NOBORDER	0x0000
#define ANYBORDER	0x000A		/* bits that indicate scrolling */

#define MAXSUBWIN	5
#define subwin(i)	(rol(0x01,(8+i)))
#define ANYSUBWIN	0x1F00

/******************************** Window border size Params	       ***/

			/* note these are the size of a 16x16 icon */
#define WBH		16		/* height */
#define WBW		16		/* width */

			/* get the scroll bar areas of window a */
#define WB_VSCRarea(a) fRect(a.corner.x-WBW,a.origin.y,a.corner.x,a.corner.y-WBH)
#define WB_HSCRarea(a) fRect(a.origin.x,a.corner.y-WBH,a.corner.x-WBW,a.corner.y)

			/* get the sub areas of scrollbar area a */
#define WB_VSCRrect(a) fRect(a.origin.x,a.origin.y+16,a.corner.x,a.corner.y-16)
#define WB_HSCRrect(a) fRect(a.origin.x+16,a.origin.y,a.corner.x-16,a.corner.y)
#define WB_incr(a)  fRpt(a.origin,add(a.origin,Pt(16,16)))
#define WB_decr(a)  fRpt(sub(a.corner,Pt(16,16)),a.corner)

			/* other areas of the main window a */
#define WB_RESHAPEarea(a) Rect(a.corner.x-WBW,a.corner.y-WBH,a.corner.x,a.corner.y)
#define WB_MOVEarea(a) Rect(a.origin.x+4,a.origin.y+4,a.origin.x+20,a.origin.y+20)
#define WB_MOVEorig(a) fPt(a.origin.x+4,a.origin.y+4)


			/* utility icon area */
			    /* for wide knobs, this is the max/min/slope icon */
#define WB_UTILarea(a) fRect(a.corner.x-36,a.origin.y+20,a.corner.x-20,a.origin.y+36)
#define WB_PUTILarea(a) fRect(a.origin.x+20,a.origin.y+28,a.origin.x+36,a.origin.y+44)

/******************************** Subwindow attribute flags	       ***/

#define NOSCRL		0x0000
#define VSCRL		0x0001
#define HSCRL		0x0002


/******************************** scroll bar definitions              ***/
#define VERT		0
#define HORIZ		1
#define RESHAPE		2
