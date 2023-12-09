#ident "@(#) /sable/sdb/ra/sblib/wgets/s.wgets.H"
/*      Copyright (c) 1989,1990,1991 AT&T - All Rights Reserved             */

#ifndef wgets_h
#define wgets_h

#include <curses.h>
include(wgets.dd)
extern void init_screen();   /* kludge for 3b2 curses problems */
extern void setLabels();
extern void set_labels();
extern void set_menu_labels();
extern void clear_labels();
extern int wgets( /* char *,unsigned,WINDOW * */ );

#endif
