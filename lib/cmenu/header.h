#ifndef CMENUDEFS
#define CMENUDEFS
#endif /*CMENUDEFS*/
#include <stdio.h>
#include <ctype.h>
#include <curses.h>
#include <string.h>

/************************** Selection defines ***************/

#define PROMPT	" ---> "
#define PCLEAR	"      "
#define CURSMSG	" Use J or K Key for Cursor Movement - Spacebar Selects "
#define CURS2MSG " Use J or K to move - Letter in []'s or Spacebar Selects "
#define CURS3MSG " Use Letter in []'s to select "
#define PSIZE	(sizeof(PROMPT))
#define TEXTCOL	 20
#define PCOL	 (TEXTCOL - PSIZE + 1 )
#define STEXTCOL	(PSIZE + 1)
#define SPCOL	 2
#define CURCOL   (STEXTCOL - 1)
#define CHRCTRL(c)	( (c) & 037 )
#define ARGINDEX	(promptrow - homerow)
#define SELINDEX	(promptrow - homerow + 1)
#define TITLEROW	( homerow - 2 )
extern char	*c_select();
#define MAXARG 20
extern char	arrayofstuff[MAXARG][80];
extern char	moptions[MAXARG][80];
extern char	workin[180], workin1[180], work[220], *attr;

extern int	t;	/* Format TEST VARIABLE */
				
/********************* End of Selection Definitions **********/
				
#define NUMBER	0
#define QUIT	1
#define MAXOPTIONS	15
#define VHELPSIZE	10
#define HHELPSIZE	COLS/2
#define FRESHENUP	-5
extern WINDOW *win;
extern WINDOW *sel;
extern int hpos, vpos;
extern int response;
extern char p;
extern char inp[20];

