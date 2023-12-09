
/**************************************************************************/
/* PANELFEATURES Package    Release:  1.0    Release Date: 1/15/89        */
/*                          Provider: J. D. Iorio  (speedy!jdi)           */
/**************************************************************************/



#define TRUE 1
#define FALSE 0


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
#define ASK_MESSAGE	'O'
#define NEW_S		'P'

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



/******************** panelfeature graphics size parameters **************/

#define GUARDX		16		/* guard band between objects */
#define GUARDY		16

    					/* standard sizes of objects */
#define PANEL_WIDTH 	250
#define PANEL_HEIGHT 	60
#define PANEL_AREA	fRect(0,0,PANEL_WIDTH,PANEL_HEIGHT)

#define CLUSTER_WIDTH 	200
#define CLUSTER_HEIGHT 	25
#define CLUSTER_AREA	fRect(0,0,CLUSTER_WIDTH,CLUSTER_HEIGHT)

#define VKNOB_WIDTH	36
#define VKNOB_HEIGHT	116
#define VKNOB_AREA	Rect(0,0,VKNOB_WIDTH,VKNOB_HEIGHT)

#define VKNOBTOP 	Rect(0,0,8,16)
#define VKNOBMID 	Rect(0,16,8,32)
#define VKNOBBOT 	Rect(0,32,8,48)
#define VKNOBTICK 	Rect(16,16,48,19)
#define VKNOBSLIDE 	Rect(16,0,48,16)
#define KVSLIDERECT(n)  fRect(0,((n+2)*16),32,((n+3)*16))
#define KVSLIDEPT(n)  	fPt(0,((n+2)*16))

#define HKNOB_WIDTH	36
#define HKNOB_HEIGHT	36
#define HKNOB_AREA	Rect(0,0,HKNOB_WIDTH,HKNOB_HEIGHT)

#define HKNOBTOP 	Rect(0,40,16,48)
#define HKNOBMID 	Rect(16,40,32,48)
#define HKNOBBOT 	Rect(32,40,48,48)
#define HKNOBTICK 	Rect(16,0,19,32)
#define HKNOBSLIDE 	Rect(0,0,16,32)
#define KHSLIDERECT	Rect(0,0,16,32)
#define KHSLIDEPT	Pt(0,0)

#define TEXT_HEIGHT	12
#define TEXT_FONT	smallfont

/************************** screen graphics size parameters **************/

#define MINX 		100		/* active panel screen coordinates */
#define MINY		100
#define MAXX		915
#define MAXY		850

#define TITLE_BOX	Rect(10,50,90,186)
#define TITLE_ORIG	Pt(12,52)
#define SUBTITLE_ORIG	Pt(12,68)
#define CRIGHT1_ORIG	Pt(12,86)
#define CRIGHT_ORIG	Pt(12,102)
#define CRIGHT2_ORIG	Pt(30,102)
#define BY_ORIG		Pt(12,121)
#define AUTHOR_ORIG	Pt(26,136)

#define SCR_ACTIVE	Rect(MINX,MINY,MAXX,MAXY)

#define SCR_NAMEBOX     Rect(MINX+GUARDX,MINY-50,MAXX-GUARDX,MINY-GUARDY)
#define SCR_NAMEORIG	Pt(512, MINY-35)

#define SCR_MSGBOX	Rect(Drect.origin.x,MAXY+2*GUARDY,600,Drect.corner.y)
#define SCR_MSGORIG	Pt(Drect.origin.x,MAXY+2*GUARDY+4)

#define SCR_KEYBOX	Rect(602,950,Drect.corner.x,Drect.corner.y)
#define SCR_KEYORIG	Pt(606,954)
#define SCR_KEY1	Rect(606,969,731,1010)
#define SCR_KEY1ORIG	Pt(668,977)
#define SCR_KEY2	Rect(736,969,861,1010)
#define SCR_KEY2ORIG	Pt(798,977)
#define SCR_KEY3	Rect(866,969,991,1010)
#define SCR_KEY3ORIG	Pt(928,977)
#define SCR_KEY3AORIG	Pt(928,990)

#define SCR_TOGBOX	Rect(602,MAXY+2*GUARDY,731,948)
#define SCR_TOGIMAGE	Rect(618,MAXY+3*GUARDY,731-GUARDX,932) 
#define SCR_TOGORIG	Pt(622,MAXY+3*GUARDY+4)

#define SCR_GOBOX	Rect(736,MAXY+2*GUARDY,861,948)
#define SCR_GOIMAGE	Rect(752,MAXY+3*GUARDY,861-GUARDX,932) 
#define SCR_GOORIG	Pt(756,MAXY+3*GUARDY+4)

#define SCR_STOPBOX	Rect(866,MAXY+2*GUARDY,Drect.corner.x,948)
#define SCR_STOPIMAGE	Rect(882,MAXY+3*GUARDY,Drect.corner.x-GUARDX,932) 
#define SCR_STOPORIG	Pt(886,MAXY+3*GUARDY+4)


/********************************* ASCDISP  defines *************************/
/*#define AD_CPT	n->sw_origin[4]		/* cursor point in pixels */
/*#define AD_CXY	n->sw_origin[3]		/* cursor pt in chars/lines */
/*#define AD_CMAP	n->sw_rect[4]		/* image bitmap rect for text */
					/* image bitmap rect for scroll */
#define AD_CPT	(*(Point *)(n->dmax))		/* cursor point in pixels */
#define AD_CXY	(*(Point *)(n->dmin))		/* cursor pt in chars/lines */
#define AD_CMAP	(*(Rectangle *)(n->value))	/* image bitmap rect for text */

#define AD_SMAP	fRpt(add(AD_CMAP.origin,Pt(0,14)), AD_CMAP.corner)

/********************************* Misc. defines *************************/

#define MAXNODESTACK	50		/* stack for node tree creation */

#define BUFSIZE 	512

#define NULLNP	(struct node *)NULL
