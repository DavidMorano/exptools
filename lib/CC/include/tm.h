#ifndef TMH
#define TMH

/*
 * Glenn Fowler
 * AT&T Bell Laboratories
 *
 * time conversion support definitions
 */

#ifndef TM_DEFAULT

#include "mytime.h"
#include <sys/types.h>

#define tmset()	/*do{if(!tm_local->daylight)tminit();}while(0)*/

#ifndef VOID
#define VOID	void
#endif

#define TM_ADJUST      (1<<0)	 /* local doesn't do leap secs	*/
#define TM_LEAP	       (1<<1)	 /* do leap seconds		*/
#define TM_UTC	       (1<<2)	 /* universal coordinated ref	*/

#define TM_DST	       (-60)	 /* default minutes for DST	*/
#define TM_LOCALZONE   (25 * 60) /* use local time zone offset	*/
#define TM_MAXLEAP     1	 /* max leap secs per leap	*/

/*
 * these indices must agree with tm_dform[]
 */

#define TM_MONTH_3	0
#define TM_MONTH	12
#define TM_DAY_3	24
#define TM_DAY		31
#define TM_TIME		38
#define TM_DATE		39
#define TM_DEFAULT	40
#define TM_MERIDIAN	41

#define TM_UT		43
#define TM_DT		47
#define TM_SUFFIXES	51
#define TM_PARTS	55
#define TM_HOURS	62
#define TM_DAYS		66
#define TM_LAST		69
#define TM_THIS		72
#define TM_NEXT		75
#define TM_NOISE	78

#define TM_NFORM	82

struct tl{ // leap second info

    time_t  time;	/* the leap second event	*/
    int	    total;	/* inclusive total since epoch	*/
};

struct tz{   // timezone information

    char*	type;		/* type name (not used)		*/
    char*	standard;	/* standard time name		*/
    char*	daylight;	/* daylight or summertime name	*/
    short	west;		/* minutes west of GMT		*/
    short	dst;		/* add to tz.west for DST	*/

//  jfi extensions

    long        spring_ahead;   /* offset in seconds of dst start */
    long        fall_back;      /* offset in seconds of dst end */
    int         observes;       /* 1 iff dst is observed        */
};

extern int	  tm_flags;	/* tm library global flags	*/
extern char*	  tm_dform[];	/* default tmformat() strings	*/
extern char	  tm_digit[];	/* output format digits		*/
extern char**	  tm_form;	/* current tmformat() strings	*/
extern struct tl  tm_leap[];	/* leap second info		*/
extern char	  tm_lex[];	/* tm_form[] lex type classes	*/
extern struct tz* tm_local;	// local time zone info
extern short	  tm_mcnt[];	/* number of days in month i	*/
extern short	  tm_msum[];	/* total days in months before i*/
extern struct tz  tm_zone[];	/* alternate time zone table	*/

extern char*      mystrdup(const char*);

extern "C"{
    time_t time(time_t* clock);
}
extern time_t	  tmdate(const char* date, char** end, time_t* clock);
extern struct tm* tmfix(struct tm* tm);
extern char*	  tmform(char* buf, char* format, time_t* clock);
extern int	  tmgoff(char* buf, char** end, int d);
//extern void	  tminit();
extern time_t	  tmleap(time_t* clock);
extern int	  tmlex(char* buf, char** end, char** tab, int n, char** suf, int n);
extern struct tm* tmmake(time_t* clock);
extern char*	  tmpoff(char* buf, char* p, int m, int d);
extern time_t	  tmtime(struct tm* tm, int west);
extern char*	  tmtype(char* buf, char** end);
extern int	  tmword(char* buf, char** end, char* str, char** suf, int n);
extern int	  tmzone(char* buf, char** end, char* type, int* dst);

#endif
#endif
