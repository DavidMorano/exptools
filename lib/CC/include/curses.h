/*ident	"@(#)C++env:incl-master/proto-headers/curses.h	1.2" */

#ifndef __CURSES_H
#define __CURSES_H

#define newwin ______newwin
#define subwin ______subwin
#define longname ______longname

#define initscr ______initscr
#define getcap ______getcap

/*	@(#)curses.h 1.8 88/02/08 SMI; from UCB 5.1 85/05/07	*/

/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 */

# ifndef WINDOW

# include	<stdio.h>
 
# include	<sgtty.h>

# undef		HZ		/* in case they've included <sys/param.h> */

# define	bool	char
# define	reg	register

# define	TRUE	(1)
# define	FALSE	(0)
# define	ERR	(0)
# define	OK	(1)

# define	_ENDLINE	001
# define	_FULLWIN	002
# define	_SCROLLWIN	004
# define	_FLUSH		010
# define	_FULLLINE	020
# define	_IDLINE		040
# define	_STANDOUT	0200
# define	_NOCHANGE	-1

# define	_puts(s)	tputs(s, 0, _putchar)

typedef	struct sgttyb	SGTTY;

/*
 * Capabilities from termcap
 */

extern bool     AM, BS, CA, DA, DB, EO, HC, HZ, IN, MI, MS, NC, NS, OS, UL,
		XB, XN, XT, XS, XX;
extern char	*AL, *BC, *BT, *CD, *CE, *CL, *CM, *CR, *CS, *DC, *DL,
		*DM, *DO, *ED, *EI, *K0, *K1, *K2, *K3, *K4, *K5, *K6,
		*K7, *K8, *K9, *HO, *IC, *IM, *IP, *KD, *KE, *KH, *KL,
		*KR, *KS, *KU, *LL, *MA, *ND, *NL, *RC, *SC, *SE, *SF,
		*SO, *SR, *TA, *TE, *TI, *UC, *UE, *UP, *US, *VB, *VS,
		*VE, *AL_PARM, *DL_PARM, *UP_PARM, *DOWN_PARM,
		*LEFT_PARM, *RIGHT_PARM;
extern char	PC;

/*
 * From the tty modes...
 */

extern bool	GT, NONL, UPPERCASE, normtty, _pfast;

struct _win_st {
	short		_cury, _curx;
	short		_maxy, _maxx;
	short		_begy, _begx;
	short		_flags;
	short		_ch_off;
	bool		_clear;
	bool		_leave;
	bool		_scroll;
	char		**_y;
	short		*_firstch;
	short		*_lastch;
	struct _win_st	*_nextp, *_orig;
};

# define	WINDOW	struct _win_st

extern bool	My_term, _echoit, _rawmode, _endwin;

extern char	*Def_term, ttytype[50];

extern int	LINES, COLS, _tty_ch, _res_flg;

extern SGTTY	_tty;

extern WINDOW	*stdscr, *curscr;

/*
 *	Define VOID to stop lint from generating "null effect"
 * comments.
 */
# ifdef lint
int	__void__;
# define	VOID(x)	(__void__ = (int) (x))
# else
# define	VOID(x)	(x)
# endif

/*
 * psuedo functions for standard screen
 */
# define	addch(ch)	VOID(waddch(stdscr, ch))
# define	getch()		VOID(wgetch(stdscr))
# define	addstr(str)	VOID(waddstr(stdscr, str))
# define	getstr(str)	VOID(wgetstr(stdscr, str))
# define	move(y, x)	VOID(wmove(stdscr, y, x))
# define	clear()		VOID(wclear(stdscr))
# define	erase()		VOID(werase(stdscr))
# define	clrtobot()	VOID(wclrtobot(stdscr))
# define	clrtoeol()	VOID(wclrtoeol(stdscr))
# define	insertln()	VOID(winsertln(stdscr))
# define	deleteln()	VOID(wdeleteln(stdscr))
# define	refresh()	VOID(wrefresh(stdscr))
# define	inch()		VOID(winch(stdscr))
# define	insch(c)	VOID(winsch(stdscr,c))
# define	delch()		VOID(wdelch(stdscr))
# define	standout()	VOID(wstandout(stdscr))
# define	standend()	VOID(wstandend(stdscr))

/*
 * mv functions
 */
#define	mvwaddch(win,y,x,ch)	VOID(wmove(win,y,x)==ERR?ERR:waddch(win,ch))
#define	mvwgetch(win,y,x)	VOID(wmove(win,y,x)==ERR?ERR:wgetch(win))
#define	mvwaddstr(win,y,x,str)	VOID(wmove(win,y,x)==ERR?ERR:waddstr(win,str))
#define mvwgetstr(win,y,x,str)  VOID(wmove(win,y,x)==ERR?ERR:wgetstr(win,str))
#define	mvwinch(win,y,x)	VOID(wmove(win,y,x) == ERR ? ERR : winch(win))
#define	mvwdelch(win,y,x)	VOID(wmove(win,y,x) == ERR ? ERR : wdelch(win))
#define	mvwinsch(win,y,x,c)	VOID(wmove(win,y,x) == ERR ? ERR:winsch(win,c))
#define	mvaddch(y,x,ch)		mvwaddch(stdscr,y,x,ch)
#define	mvgetch(y,x)		mvwgetch(stdscr,y,x)
#define	mvaddstr(y,x,str)	mvwaddstr(stdscr,y,x,str)
#define mvgetstr(y,x,str)       mvwgetstr(stdscr,y,x,str)
#define	mvinch(y,x)		mvwinch(stdscr,y,x)
#define	mvdelch(y,x)		mvwdelch(stdscr,y,x)
#define	mvinsch(y,x,c)		mvwinsch(stdscr,y,x,c)

/*
 * psuedo functions
 */

#define	clearok(win,bf)	 (win->_clear = bf)
#define	leaveok(win,bf)	 (win->_leave = bf)
#define	scrollok(win,bf) (win->_scroll = bf)
#define flushok(win,bf)	 (bf ? (win->_flags |= _FLUSH):(win->_flags &= ~_FLUSH))
#define	getyx(win,y,x)	 y = win->_cury, x = win->_curx
#define	winch(win)	 (win->_y[win->_cury][win->_curx] & 0177)

#define raw()	 (_tty.sg_flags|=RAW, _pfast=_rawmode=TRUE, stty(_tty_ch,&_tty))
#define noraw()	 (_tty.sg_flags&=~RAW,_rawmode=FALSE,_pfast=!(_tty.sg_flags&CRMOD),stty(_tty_ch,&_tty))
#define cbreak() (_tty.sg_flags |= CBREAK, _rawmode = TRUE, stty(_tty_ch,&_tty))
#define nocbreak() (_tty.sg_flags &= ~CBREAK,_rawmode=FALSE,stty(_tty_ch,&_tty))
#define crmode() cbreak()	/* backwards compatability */
#define nocrmode() nocbreak()	/* backwards compatability */
#define echo()	 (_tty.sg_flags |= ECHO, _echoit = TRUE, stty(_tty_ch, &_tty))
#define noecho() (_tty.sg_flags &= ~ECHO, _echoit = FALSE, stty(_tty_ch, &_tty))
#define nl()	 (_tty.sg_flags |= CRMOD,_pfast = _rawmode,stty(_tty_ch, &_tty))
#define nonl()	 (_tty.sg_flags &= ~CRMOD, _pfast = TRUE, stty(_tty_ch, &_tty))
#define	savetty() ((void) gtty(_tty_ch, &_tty), _res_flg = _tty.sg_flags)
#define	resetty() (_tty.sg_flags = _res_flg, (void) stty(_tty_ch, &_tty))

#define	erasechar()	(_tty.sg_erase)
#define	killchar()	(_tty.sg_kill)
#define baudrate()	(_tty.sg_ospeed)

WINDOW	*initscr(), *newwin(), *subwin();
char	*longname(), *getcap();

/*
 * Used to be in unctrl.h.
 */
#define	unctrl(c)	_unctrl[(c) & 0177]
extern char *_unctrl[];
# endif
 

#undef initscr
#undef subwin
#undef newwin
#undef getcap
#undef longname

extern "C" {
	int set_term(WINDOW*);
	int keypad(WINDOW*, char);
	int nodelay(WINDOW*, char);
	int intrflush(WINDOW*, char);
	int meta(WINDOW*, char);
	int typeahead(int);
	int doupdate();
	int wnoutrefresh(WINDOW*);
	int wclear(WINDOW*);
	int wclrtobot(WINDOW*);
	int wclrtoeol(WINDOW*);
	WINDOW *newpad(int, int);
	void idlok(WINDOW*, char);
	void wattrset(WINDOW*, int);
	int beep();
	int def_prog_mode();
	int def_shell_mode();
	int delay_output(int);
	int fixterm();
	int flash();
	int flushinp();
	int has_ic();
	int has_il();
	int m_addch(char);
	int m_addstr(char *);
	int m_clear();
	int m_erase();
	WINDOW *m_initscr();
	int m_move(int, int);
	int m_refresh();
	int mvprintw(int, int, char* ...);
	int mvscanw(int, int, char* ...);
	int mvwprintw(WINDOW*, int, int, char* ...);
	int mvwscanw(WINDOW*, int, int, char* ...);
	int pnoutrefresh(WINDOW*, int, int, int, int, int, int);
	int prefresh(WINDOW*, int, int, int, int, int, int);
	int putp(char*);
	int reset_prog_mode();
	int reset_shell_mode();
	int resetterm();
	int saveterm();
	int setupterm(char*, int, int*);
	int tgetent(char*, const char*);
	int tgetflag(const char*);
	int tgetnum(const char*);
	char *tgetstr(const char*, char**);
	char *tgoto(const char*, int, int);
	char *tparm(char*, int ...);
	int tputs(const char*, int, int(*)(int));
	int traceoff();
	int traceon();
	int vidattr(int);
	int vidputs(int, int(*)(int));
	int wattroff(WINDOW*, int);
	int wattron(WINDOW*, int);
	void wrefresh(WINDOW*);
	void endwin();
	char *longname(char*, char*);
	int waddch(WINDOW*, char);
	int waddstr(WINDOW*, char*);
	int box(WINDOW*, char, char);
	int wdelch(WINDOW*);
	int wdeleteln(WINDOW*);
	int winsch(WINDOW*, char);
	int winsertln(WINDOW*);
	int wmove(WINDOW*, int, int);
	int overlay(WINDOW*, WINDOW*);
	int overwrite(WINDOW*, WINDOW*);
	int printw(char* ...);
	int wprintw(WINDOW*, char* ...);
	int wstandout(WINDOW*);
	int wstandend(WINDOW*);
	int wgetch(WINDOW*);
	int wgetstr(WINDOW*, char*);
	int scanw(char* ...);
	int wscanw(WINDOW*, char* ...);
	int delwin(WINDOW*);
	int mvwin(WINDOW*, int, int);
	int touchwin(WINDOW*);
	int gettmode();
	int mvcur(int, int, int, int);
	int scroll(WINDOW*);
	int setterm(char*);
	int tstp();
	WINDOW *newwin(int, int, int, int);
	WINDOW *subwin(WINDOW*, int, int, int, int);
	WINDOW *initscr();
	int werase(WINDOW*);
	char *cuserid(char*);
}

#endif
