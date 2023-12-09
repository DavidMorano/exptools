
/**************************************************************************/
/* PANELFEATURES Package    Release:  1.0    Release Date: 1/15/89        */
/*                          Provider: J. D. Iorio  (speedy!jdi)           */
/**************************************************************************/





// panelfeature graphics size constants for show()ing and resize()ing

#define NameXoff	1
#define NameYoff	1
#define LabelXoff	2
#define LabelYoff	2
#define ValueXoff	3
#define ValueYoff	3
#define BorderXovrhd	2
#define BorderYovrhd	2
#define PfXspace	1
#define PfYspace	1

#define Fieldwidth	8

#define KnobWidth	Fieldwidth + ValueXoff + BorderXovrhd
#define KnobHeight	BorderYovrhd 
#define Disp1Width	Fieldwidth + ValueXoff + BorderXovrhd
#define Disp2Width	2*(Fieldwidth) + ValueXoff + BorderXovrhd
#define Disp3Width	3*(Fieldwidth) + ValueXoff + BorderXovrhd
#define DispHeight(Sz)	Sz + BorderYovrhd + 1

#define ScreenXmax	135


// panelfeature update flag bit defines for redraw requests

#define UP_TO_DATE	0x00
#define NAME_CHANGE	0x01
#define LABEL_CHANGE	0x02
#define VALUE_CHANGE	0x04
#define WIDTH_CHANGE	0x08
#define VALUE_CLEAR	0x10
#define ATTRIB_CHANGE	0x20
#define AXIS_CHANGE	0x40
#define MAJOR 		0xFF

