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
#define CURSMSG	" Use J,j or K,k Key for Cursor Movement - Spacebar Selects "
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
int clr();
/*int cumesg(WINDOW *w);*/
int cumesg();
/*int fillwin(FILE f, WINDOW *window);*/
int fillwin();
int get_free();
int go_noprompt();
int go_prompt();
/*message(WINDOW *w, char *str, int size);*/
int message();
/*int newselect( char **options, int count);*/
int newselect();
/*char	*prompt( char **options, int count);*/
char	*prompt();
/*char *c_select( char **options, int count);*/
char *c_select();
/*int view(char *file);*/
int view();
#define MAXARG 20
char	arrayofstuff[MAXARG][80];
char	moptions[MAXARG][80];
char	workin[180], workin1[180], work[220], *attr;

int	t;	/* Format TEST VARIABLE */
				
/********************* End of Selection Definitions **********/
				
#define NUMBER	0
#define QUIT	1
#define MAXOPTIONS	15
#define VHELPSIZE	10
#define HHELPSIZE	COLS/2
#define FRESHENUP	-5
WINDOW *win;
WINDOW *sel;
int hpos, vpos;
int response;
char p;
char inp[20];

