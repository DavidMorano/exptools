#ident "@(#) /sable/sdb/ra/sblib/s.sblib.H"
/*  Copyright (c) 1989, 1990, 1991 AT&T - All Rights Reserved       */

#ifndef sblib_h
#define sblib_h

include(sblib.dd)
#include <sys/types.h>
#include <sys/stat.h>
#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <ftw.h>
#include <osfcn.h>
#include <regcmp.h>
#include <stream.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>

class Counter;
class Curse;
class Error;
class Form;
class Pattern;
class List;
class Link1;
class Link2;
class Vfd;
class Vfile;
class Heapcheck;

char *upper(const char*);
char *lower(const char*);

include(counter.dd)
include(file.dd)
include(roll.dd)
include(string.dd)
include(pathname.dd)
include(error.dd)
include(pattern.dd)

include(list.dd)

include(link1.dd)
include(link1qs.dd)

include(link2.dd)
include(vfd.dd)
include(vfile.dd)
#include <lcurses.h>
include(wgets.dd)
extern "C"
   {
   void init_screen();  /* kludge for 3b2 curses problems */
   void setLabels(char *labels[8]);
   void set_labels();
   void set_menu_labels();
   void clear_labels();
   int wgets(char *,unsigned,WINDOW *);
   };

include(curse.dd)
include(form.dd)
include(node.dd)
include(menu.dd)

include(monitor.ims)

include(heapchck.dd)
#endif
