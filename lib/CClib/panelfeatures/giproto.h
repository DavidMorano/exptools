
/**************************************************************************/
/* PANELFEATURES Package    Release:  1.0    Release Date: 1/15/89        */
/*                          Provider: J. D. Iorio  (speedy!jdi)           */
/**************************************************************************/
/*  GIPROTO.H
*	This file defines the commands for the 630 graphics protocol
*	used to talk to the ATT 630 terminal resident process.
*/

/* NOTE:  IF THIS FILE CHANGES, YOU MAY ALSO HAVE TO CHANGE GIDEF.H
	  IN THE 630 GRAPHICS INTERFACE PACKAGE
*/

/********************************* TERMINAL DRIVER TYPES *****************/
#define ATT630		1	/* normal dialogue */
#define CURSES		2
#define DBUG		3
#define PDBUG		4
#define ATT630P		5	/* throttle protocol during major shows */

/********************************* HOST / 630 GI command types ***********/
#define GILOAD		'A'
#define GICLEAR		'B'
#define GICHG_NAME	'C'
#define GICHG_LABEL	'D'
#define GICHG_VALUE	'E'
#define GIUPDATE_DISP	'F'
#define GICLR_DISP	'G'
#define GIWARN_MESSAGE	'H'
#define GIMOUSE_GO	'I'
#define GIMOUSE_STOP	'J'
#define GICHG_ATTRIB	'K'
#define GICHG_AXIS	'L'
#define GIINFO_MESSAGE	'M'
#define GILOAD_LOGO	'N'
#define GIASK_MESSAGE	'O'




/********************************* panel tree node types for protocol ****/
#define GITERMINATE	'0'
#define GIPANEL 	'1'
#define GICLUSTER 	'2'
#define GIDISPLAY	'3'
#define GIFWINT 	'4'
#define GIVWINT 	'5'
#define GIFWFLT 	'6'
#define GIVWFLT 	'7'
#define GIENUM 		'8'
#define GIASCKNOB	'9'
#define GIASCDISP 	'a'


/********************************* attribute bit definitions *************/
#define A_ALL		0xFFFF
#define A_NONE		0x0000
#define A_GREY		0x0001
