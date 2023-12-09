
/**************************************************************************/
/* PANELFEATURES Package    Release:  1.0    Release Date: 1/15/89        */
/*                          Provider: J. D. Iorio  (speedy!jdi)           */
/**************************************************************************/

/**********************************************************************
*  PFCGLOBALS.H
*
*	All of the global data items used by the curses PANELFEATURE
*	package
*
*	Copyright AT&T 1988
*
*	History:
*		J. D. Iorio 	7/5/88		created
*
**********************************************************************/
extern istream *hostread;
extern ostream *hostwrite;

extern int LINES;
extern int COLS;

extern WINDOW *namebox;
extern WINDOW *dividebox;
extern WINDOW *msgbox;
extern WINDOW *logobox;
extern WINDOW *actionbox;

extern char Logo1[];
extern char Logo2[];
extern char Logodate[];

extern struct node *currentnode;
extern struct node *togglenode;

extern int mouse_alive;

extern char lbuf[];

extern int KEY_HARDCOPY;
extern int KEY_BRK;
extern int KEY_DOC;
extern int KEY_GO;
extern int KEY_EXIT;
extern int KEY_TOGLATCH;
extern int KEY_TOGJUMP;
extern int KEY_HELP;
extern int KEY_OPEN;
extern int KEY_CLOSE;
extern int KEY_NEXT;
extern int KEY_PREV;
extern int KEY_CONT;
