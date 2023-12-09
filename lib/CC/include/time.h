/*ident	"@(#)C++env:incl-master/proto-headers/time.h	1.3" */

#ifndef __TIME_H
#define __TIME_H

#define gmtime ______gmtime
#define localtime ______localtime
#define asctime ______asctime
#define ctime ______ctime
#define tzset ______tzset
#define tzsetwall ______tzsetwall
#define time ______time

/*	@(#)time.h 1.8 88/02/07 SMI; not from UCB */

/*
 * Structure returned by gmtime and localtime calls (see ctime(3)).
 */
struct tm {
	int	tm_sec;
	int	tm_min;
	int	tm_hour;
	int	tm_mday;
	int	tm_mon;
	int	tm_year;
	int	tm_wday;
	int	tm_yday;
	int	tm_isdst;
	char	*tm_zone;
	long	tm_gmtoff;
};

extern	struct tm *gmtime(), *localtime();
extern	char *asctime(), *ctime();
extern	void tzset(), tzsetwall();
 

#undef tzsetwall
#undef localtime
#undef tzset
#undef ctime
#undef time
#undef asctime
#undef gmtime

extern "C" {
	/*const*/ char *asctime(const struct tm*);
	/*const*/ char *ctime(const long*);
	/*const*/ struct tm *gmtime(const long*);
	/*const*/ struct tm *localtime(const long*);
	long time(long*);
	void tzset();
	/*const*/ char *timezone(int, int);
	int dysize(int);
	void tzsetwall();
}

#endif
