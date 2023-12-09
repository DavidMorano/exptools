/* config */

/* last modified %G% version %I% */


#define	VERSION		"0"
#define	WHATINFO	"@(#)GROPEDICT "
#define	BANNER		"Grope Dictionary Updater"
#define	SEARCHNAME	"gropedict"
#define	VARPRNAME	"TOOLS"

#define	VARPROGRAMROOT1	"GROPEDICT_PROGRAMROOT"
#define	VARPROGRAMROOT2	VARPRNAME
#define	VARPROGRAMROOT3	"PROGRAMROOT"

#define	VARSEARCHNAME	"GROPEDICT_NAME"
#define	VARERRORFNAME	"GROPEDICT_ERRORFILE"

#define	VARDEBUGFNAME	"GROPEDICT_DEBUGFILE"
#define	VARDEBUGFD1	"GROPEDICT_DEBUGFD"
#define	VARDEBUGFD2	"DEBUGFD"

#define	VARTMPDNAME	"TMPDIR"

#ifndef	PROGRAMROOT
#define	PROGRAMROOT	"/usr/add-on/exptools"
#endif

#define	TMPDNAME	"/tmp"
#define	DICTDNAME	"lib/grope"

#define	ETCDIR1		"etc/grope"
#define	ETCDIR2		"etc"
#define	CONFIGFNAME1	"grope.conf"
#define	CONFIGFNAME2	"conf"
#define	LOGFNAME	"log/grope-dict"
#define	HELPFNAME	"grope-dict.help"

#define	LOGSIZE		(80*1024)

#define	PREFIX		"dic_"

#define	NOUTFILES	10		/* number of output files */
#define	MAXWORDLEN	70		/* maximum word length */



