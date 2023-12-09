
/**************************************************************************/
/* PANELFEATURES Package    Release:  1.0    Release Date: 1/15/89        */
/*                          Provider: J. D. Iorio  (speedy!jdi)           */
/**************************************************************************/



//#define TRUE 1
//#define FALSE 0


/********************************* HOST / 630 GI command types ***********/
#define LOAD		'A'
#define CLEAR		'B'
#define CHANGE_NAME	'C'
#define CHANGE_LABEL	'D'
#define CHANGE_VALUE	'E'
#define UPDATE_DISPLAY	'F'
#define CLEAR_DISPLAY	'G'
#define WARN_MESSAGE	'H'
#define MOUSE_GO	'I'
#define MOUSE_STOP	'J'
#define CHANGE_ATTRIB	'K'
#define CHANGE_AXIS	'L'
#define INFO_MESSAGE	'M'
#define LOAD_LOGO	'N'

#define ERASE_MESSAGE  "*!"



/********************************* panel tree node types for protocol ****/
#define TERMINATE	'0'
#define PANEL 		'1'
#define CLUSTER 	'2'
#define DISPLAY		'3'
#define FWINT 		'4'
#define VWINT 		'5'
#define FWFLT 		'6'
#define VWFLT 		'7'
#define ENUM 		'8'
#define ASCKNOB		'9'
#define ASCDISP		'a'


/*********************************  attribute flags *****************/
#define A_ALL		0xFFFF
#define A_NONE		0x0000
#define A_GREY		0x0001
#define A_HEX		0x0002
#define A_JUSTSET	0x4000



/********************************* drawing control flags *****************/
#define SHOW_NAME	0x01
#define SHOW_LABEL	0x02
#define SHOW_VALUE	0x04
#define SHOW_ALL	(SHOW_NAME | SHOW_LABEL | SHOW_VALUE)


/********************************* Misc. defines *************************/

#define MAXNODESTACK	100		/* stack for node tree creation */

#define MYBUFSIZE 	512

#define NULLNP	(struct node *)NULL

#define MSGBOXH 6
#define MSGBOXW 60
