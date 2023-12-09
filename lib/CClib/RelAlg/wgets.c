#ident "@(#) /sable/sdb/ra/sblib/wgets/s.wgets.c"
/*       Copyright (c) 1989, 1990, 1991 AT&T - All Rights Reserved      */

#include <wgets.h>

/*   THIS CAME FROM wgets.ct, IT HAS NOT BEEN CHECKED AGAINST THE CODE.
**   int wgets(char *string,unsigned length,WINDOW *window)
**      -- return is a character in CASE_SAVE, CASE_QUIT, CASE_NEXT,
**            CASE_PREVIOUS or -1.
**      -- string is a non-NULL pointer to a character array of size length.
**      -- NULL string is rejected by returning -1.
**      -- otherwise string is assumed valid.
**      -- length is a valid positive integer equal to the length of string.
**      -- 0 length is rejected by returning -1.
**      -- otherwise length is assumed valid.
**      -- window is a non-NULL pointer to a valid WINDOW
**      -- NULL window is rejected by returning -1.
**      -- otherwise window is assumed valid.
*/

#define FOREVER for(;;)

void init_screen()
{
slk_init(1);
initscr();
cbreak();
noecho();
keypad(stdscr,TRUE);
}

void setLabels(labels)
char *labels[8];
{
int i;
for ( i=0; i<8; i++ )
   slk_set(i+1,labels[i],1);
slk_clear();
slk_restore();
slk_touch();
slk_noutrefresh();
doupdate();   /* do this now or you can't control cursor position */
}

void set_labels()
{
static char *formLabels[8] =
   { "QUIT  ^D","","SAVE  ^N","PRVOUS^P","","ERASE ^X","EDTFLE^E","" };
setLabels(formLabels);
}

void set_menu_labels()
{
static char  *menuLabels[8] =
   { "QUIT  ^D","HELP  ^?","TOPMNU^T","PRVMNU^P","","","","" };
setLabels(menuLabels);
}
void clear_labels()
{
slk_clear();
slk_touch();
slk_noutrefresh();
}

int wgets(string,length,window)
char *string;
unsigned length;
WINDOW *window;
{
int i=0, c=0, row=0, col=0;
if ( !string || !length || !window ) return -1;
getyx(window,row,col);
cbreak();
noecho();
keypad(window,TRUE);
wrefresh(window);
for ( i=0; i < length-1; i++ )
   {
   c = wgetch(window);
backout: /* for backspaces typed after length is reached */
   switch(c)
      {
   CASE_ERASE_CHAR:
      if ( i > 0 )
         i -= 2;
      else i = -1;
      wmove(window,row,col+i+1);
      waddch(window,(chtype)' ');
      wmove(window,row,col+i+1);
      break;
   CASE_ERASE_FIELD:
      i = -1; /* will get bumped to zero */
      wmove(window,row,col);
      wclrtoeol(window);
      break;
   CASE_T_MENU:
   CASE_HELP:   CASE_EDIT_FILE:    CASE_SAVE:   
   CASE_QUIT:   CASE_NEXT:         CASE_PREVIOUS:
   case -1:
      string[i] = '\0';
      wclrtoeol(window);
      wrefresh(window);
      return c;
   default: 
      string[i] = c;
      waddch(window,(chtype)c);
      }
   wrefresh(window);
   }
FOREVER
   {
   c = wgetch(window);
   switch(c)
      {
   CASE_T_MENU:
   CASE_ERASE_CHAR: CASE_ERASE_FIELD: CASE_SAVE:
   CASE_QUIT: CASE_PREVIOUS: CASE_NEXT: 
   CASE_EDIT_FILE: CASE_HELP: case -1:
      goto backout;
   default: beep();   /* user is trying to type too many characters */
      }
   }
}

