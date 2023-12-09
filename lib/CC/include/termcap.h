/*ident	"@(#)C++env:incl-master/proto-headers/termcap.h	1.2" */

#ifndef __TERMCAP_H
#define __TERMCAP_H

extern char PC,*BC,*UP;
extern short ospeed;

extern "C" {
    int tgetent(char *, const char *);
    int tgetnum(const char *id);
    int tgetflag(const char *id);
    char *tgetstr(const char *id, char **area);
    char *tgoto(const char *cm, int destcol, int destline);
    int tputs(const char *cp, int affcnt, int (*outc)(int));
}

#endif
