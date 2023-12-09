
/**************************************************************************/
/* PANELFEATURES Package    Release:  1.0    Release Date: 1/15/89        */
/*                          Provider: J. D. Iorio  (speedy!jdi)           */
/**************************************************************************/

/**********************************************************************
*  PFCGLOBDEF.H
*
*	All of the global data items used by the curses PANELFEATURE
*	package are defined for the main module here
*
*	pfcglobals.h declares them external for all other modules
*
*	Copyright AT&T 1988
*
*	History:
*		J. D. Iorio 	7/5/88		created
*
**********************************************************************/



/**************************communications ports **********************/
istream *hostread;
ostream *hostwrite;

/***************************** screen size ****************/
extern int LINES;
extern int COLS;

/***************************** screen regions *************/
WINDOW *namebox;
WINDOW *dividebox;
WINDOW *msgbox;
WINDOW *logobox;
WINDOW *actionbox;


/**************************** logo and copyright store ****/
char Logo1[10];
char Logo2[12];
char Logodate[6];

struct node *currentnode;
struct node *togglenode;

int mouse_alive;

/****************************** resident char buffer ******/
char lbuf[MYBUFSIZE];

/****************************** keyboard definitions ******/
int KEY_HARDCOPY;
int KEY_BRK;
int KEY_DOC;
int KEY_GO;
int KEY_EXIT;
int KEY_TOGLATCH;
int KEY_TOGJUMP;
int KEY_HELP;
int KEY_OPEN;
int KEY_CLOSE;
int KEY_NEXT;
int KEY_PREV;
int KEY_CONT;
