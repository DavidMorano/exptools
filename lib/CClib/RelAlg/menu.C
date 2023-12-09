#ident "@(#) /sable/sdb/ra/sblib/menu/s.menu.C"
/*       Copyright (c) 1989, 1990, 1991 AT&T - All Rights Reserved */

#include <sblib.h>

#define ERROR_MSG(NOTICE) { move(0,0); clrtoeol(); addstr(NOTICE); } 

static struct transition *opts;
static unsigned short max_option;

const int topRow = 2;

Boolean_t help(WINDOW *w)
{
int origRow=0,origColumn=0,row=0,column=0,i=0,option=0, c;
getyx(w,origRow,origColumn);
wmove(w,origRow,0);
wclrtoeol(w);
mvwprintw(w,origRow,0,"     Which option did you want help with? ");
wrefresh(w);
c = wgetch(w);
if ( isalpha(c) )
   {
   option = toupper(c) - 'A';
   if (option <= max_option)
      {
      row = topRow;
      column = 10;
      i = 0;
      werase(w);
      while (opts[option].help_message[i][0] != (char) NULL)
         mvwprintw(w,row++,column,opts[option].help_message[i++]);
      wmove(w,origRow,0);
      wclrtoeol(w);
      mvwprintw(w,origRow,0,"   Press any key to continue: ");
      c = wgetch(w);
      }
   else flash();
   }
else
   flash();
return TRUE;
}

unsigned short manage_menus(unsigned short cur_state,struct menu state_table[])
{
unsigned short prev_state=cur_state, new_state;
int row=0, column=0, headingCol=0, i=0,option=0, c;
while (TRUE)
   {
/* Format the Screen */
   move(1,0);wclrtobot(stdscr);
   set_menu_labels();
   row = topRow+1; column = 1; headingCol = column+3;
   opts = state_table[cur_state].opts;
   for (i=0;i < NUM_OPTIONS;i++)
      {
      if (opts[i].menu_item[0] == (char) NULL)
         break;
      if ( i == NUM_OPTIONS/2 )
         {
         row = topRow+2;
         column += L_MENU_ITEM+5;
         headingCol = (80-strlen(state_table[cur_state].heading))/2;
         }
      else if (i%3 == 0)
         row++; /* Group in sets of three */
      mvwprintw(stdscr,row++,column,"%c) %s,",i+'A', opts[i].menu_item);
      }
   mvwprintw(stdscr,topRow,headingCol,"%s", state_table[cur_state].heading);
   max_option = i - 1;
   row = BOTTOMROW(stdscr)-1;
   mvwprintw(stdscr,row,5,"Please enter selected option: ");
   touchwin(stdscr);
/* Elicit Option from User */
   wrefresh(stdscr);
   switch(c=wgetch(stdscr))
      {
   CASE_TOP_MENU: prev_state = cur_state; cur_state = 0; ERROR_MSG("");
                  continue;
   CASE_PREVIOUS: new_state = prev_state; prev_state = cur_state;
                  cur_state = new_state; ERROR_MSG(""); continue;
   CASE_HELP: help(stdscr); ERROR_MSG(""); continue;
   CASE_QUIT: return cur_state;
   default:
      waddch(stdscr,c);
      if ( isalpha(c) && isascii(c) )  /* isalpha doesn't check for ascii */
         option = toupper(c) - 'A';
      else
         {
         ERROR_MSG("ERROR: Please specify options by letter");
         beep();
         continue;
         }
      }
   if (option > max_option)
      {
      ERROR_MSG(form("ERROR: Option %c not in list",option+'A'));
      beep();
      continue;
      }
   else ERROR_MSG("");
   move(++row,0);

/* Process Selected Option */
   clear_labels();
   wclear(stdscr);
   wnoutrefresh(stdscr);
   if (opts[option].action == noop)
      new_state = opts[option].next_state;
   else if(opts[option].action(stdscr) == TRUE)
      new_state = opts[option].next_state;
   if ( new_state != cur_state )
      { prev_state = cur_state; cur_state = new_state; }
   wclear(stdscr);
   }
}

Boolean_t noop(WINDOW *w)
{
(void) w; /* void reference w to shut up compiler */ 
return TRUE;
}
