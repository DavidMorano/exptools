
/**************************************************************************/
/* PANELFEATURES Package    Release:  1.0    Release Date: 1/15/89        */
/*                          Provider: J. D. Iorio  (speedy!jdi)           */
/**************************************************************************/

extern char askmsg( char *s, char *choice);
extern void errormsg( char *s);
extern void infomsg( char *s);
#define ERASE_MSG "*!"

extern void mouse_active();
extern void mouse_inactive();

extern void end_PF();
extern void begin_PF();

extern int detect_brk_cmd();

extern void interactmsg( char *s, float& x);
extern void sleep(int);
extern void loadlogo(char *title, char *stit1, char *stit2,
		 char *date, char *logodata);

