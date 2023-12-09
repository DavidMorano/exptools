#ifndef _Date_time_included
#define _Date_time_included 1

/* Version 1.0 */

#include "String.h"
#include "Error_buf.h"
#include <time.h>

extern	void exit(int);
extern	char *ctime(long*);
extern	long timezone;

const BASE_CENTURY = 1900;
const BASE_YEAR = 1970;

const SECS_IN_MIN = 60;
const MINS_IN_HOUR = 60;
const HOURS_IN_DAY = 24;
const SECS_IN_HOUR = SECS_IN_MIN*MINS_IN_HOUR;
const SECS_IN_DAY = SECS_IN_HOUR*HOURS_IN_DAY;

const DAYS_IN_YEAR = 365;
const DAYS_IN_LEAP = 366;

const MAX_DAY = 31;
const MAX_YR = 99;
const MIN_YR = 70;
const MAX_HR = 24;
const MAX_MIN = 60;
const MAX_SEC = 60;

enum {ZEROMO, JAN, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC};

class Date_time : public Error_buf {
	int mo, day, yr, hr, min, sec;
	char mos[4];		// month in char* format
	char day_of_week[4];	// day of week in char* format
	long secs1970;		// seconds elapsed since 1970 to this date

	void copy(Date_time&);
	states input_sane();
	int days_in_year(int year);
	int days_in_month(int month);
	long conv_secs1970();
	void init_secs1970(long secs_1970);
public:
	Date_time(String& date,String& time);
	Date_time(long secs_1970);
	Date_time(Date_time& dt) { copy(dt); }
	Date_time();
	Date_time& operator=(Date_time& dt) { copy(dt); return *this; }
	int get_mo()				{ return mo; }
	int get_day()				{ return day; }
	int get_yr()				{ return yr; }
	int get_hr()				{ return hr; }
	int get_min()				{ return min; }
	int get_sec()				{ return sec; }
	char* get_mos()				{ return mos; }
	char* get_day_of_week()		{ return day_of_week; }
	long get_secs1970()			{ return secs1970; }
	Date_time offset(int days=0, int hours=0, int mins=0, int secs=0);	
	friend ostream& operator<<(ostream &,Date_time &);
	int operator==(Date_time &);
	int operator!=(Date_time &);
	int operator<(Date_time &);
	int operator<=(Date_time &);
	int operator>(Date_time &);
	int operator>=(Date_time &);
};

#endif
