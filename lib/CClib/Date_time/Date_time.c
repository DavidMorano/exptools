#include "Date_time.h"

/*
 *	FILE:				Date_time.c
 *	
 *						%W%
 *	
 *	PERSON
 *	IN CHARGE:			Glenn Bradford
 *	
 *	CONTENTS:			This file implements the class Date_time.
 *
 *						Functions:
 *							Date_time(char* date,char* time)
 *							Date_time(long)
 *							Date_time()
 *							int get_mo();
 *							int get_day();
 *							int get_yr();
 *							int get_hr();
 *							int get_min();
 *							int get_sec();
 *							char* get_mos();
 *							char* get_day_of_week();
 *							long get_secs1970();
 *							long conv_secs1970();
 *							int days_in_year(int yr);
 *							int days_in_month(int mo);
 *	Date_time offset(int days=0, int hours=0, int mins=0, int secs=0);	
 *							states input_sane();
 *							ostream operator<<;
 *							int operator==;
 *							int operator!=;
 *							int operator<;
 *							int operator<=;
 *							int operator>;
 *							int operator>=;
 *
 * CONSTRAINTS:			None.
 *
 * RELATED
 * ROUTINES/FILES:		<stdio.h>
 *						<time.h>
 *						"Date_time.h"
 *
 * RESTRICTIONS/
 * PROBLEMS:			None.
 *
 */

/*
 *	FUNCTION:			operator<<
 *
 *	PROCESS:			Print the date fields mo,yr,day,hr,min,sec as
 *						they are set in class date.
 *
 *	INPUTS:				None.
 *
 *	OUTPUTS:			The printed fields mo,yr,day,hr,min,sec.
 *
 *	SIDE EFFECTS:		None.
 *
 *	CONSTRAINTS:		None.
 *
 *	RELATED
 *	ROUTINES/FILES:		
 *
 *	RESTRICTIONS/
 *	PROBLEMS:			None.
 *
 */
ostream& operator<<(ostream &s, Date_time &x)
{
	s << "month: " << x.mo << "\n";
	s << "day  : " << x.day << "\n";
	s << "year : " << x.yr << "\n";
	s << "hr   : " << x.hr << "\n";
	s << "min  : " << x.min << "\n";
	s << "sec  : " << x.sec << "\n";
	s << "month: " << x.mos << "\n";
	s << "day of week: " << x.day_of_week << "\n";
	s << "secs since 1970: " << x.secs1970 << "\n";
	return s;
}

/* The relational operators for Date_time */

int Date_time::operator==(Date_time &y)
{
	return secs1970 == y.secs1970;
}

int Date_time::operator!=(Date_time &y)
{
	return secs1970 != y.secs1970;
}

int Date_time::operator<(Date_time &y)
{
	return secs1970 < y.secs1970;
}

int Date_time::operator<=(Date_time &y)
{
	return secs1970 <= y.secs1970;
}

int Date_time::operator>(Date_time &y)
{
	return secs1970 > y.secs1970;
}

int Date_time::operator>=(Date_time &y)
{
	return secs1970 >= y.secs1970;
}

/*
 *	FUNCTION:			days_in_year
 *
 *	PROCESS:			Finds the number of days in a given year,
 *						366 if yr is a leap year, else 365
 *
 *	INPUTS:				yr
 *
 *	OUTPUTS:			#of days in yr
 *
 *	SIDE EFFECTS:		None.
 *
 *	CONSTRAINTS:		None.
 *
 *	RELATED
 *	ROUTINES/FILES:		None.
 *
 *	RESTRICTIONS/
 *	PROBLEMS:			None.
 *
 */
inline int Date_time::days_in_year(int yr)
{
	if (yr % 4) return(365);
		else return(366);
}

/*
 *	FUNCTION:			Date_time constructor
 *
 *	PROCESS:			Construct a Date_time object from the argument
 *						date = 'mm-dd-yy' and time = 'hh:mm:ss'
 *
 *	INPUTS:				date and time strings.
 *
 *	OUTPUTS:			Sets member data mo,day,yr,hr,min,sec,secs_1970,
 *						mos,day_of_week.
 *
 *	SIDE EFFECTS:		Object will be only partially constructed
 *						if the arguments are not sane.
 *
 *	CONSTRAINTS:		Arguments must be sane to guarantee proper
 *						object construction.
 *
 *	RELATED
 *	ROUTINES/FILES:		atoi(3),ctime(3),input_sane(),conv_secs1970()
 *
 *	RESTRICTIONS/
 *	PROBLEMS:			Do not check for time and date separators '-' and ':'
 *
 */
Date_time::Date_time(String& date,String& time)
{
	long stoi(String&);

	mo = stoi(date(0,2));
//	assume date[2] is '-' or some other sensible separator
	day = stoi(date(3,2));
//	assume date[5] is '-' or some other sensible separator
	yr = stoi(date(6,2));
	hr = stoi(time(0,2));
//	assume time[2] is ':' or some other sensible separator
	min = stoi(time(3,2));
//	assume time[5] is ':' or some other sensible separator
	sec = stoi(time(6,2));

/*	what I'd like to do, but old String can't
	mo = atoi(date(0,2));
	day = atoi(date(3,2));
	yr = atoi(date(6,2));
	hr = atoi(time(0,2));
	min = atoi(time(3,2));
	sec = atoi(time(6,2));
*/
	state = input_sane();
	secs1970 = conv_secs1970();
	sscanf(ctime(&secs1970),"%s%s%*s%*s%*s",day_of_week,mos);
}

long stoi(String& s)
{
	char* ch = new char[s.length() + 1];
	s.dump(ch);
	int ret = atoi(ch);
	delete ch;
	return ret;
}

void Date_time::copy(Date_time& dt)
{
	mo = dt.mo;
	day = dt.day;
	yr = dt.yr;
	hr = dt.hr;
	min = dt.min;
	sec = dt.sec;
	state = dt.state;
	secs1970 = dt.secs1970;
	strcpy(mos, dt.mos);
	strcpy(day_of_week, dt.day_of_week);
}

/*
 *	FUNCTION:			init_secs
 *
 *	PROCESS:			Construct a Date_time object from the argument
 *						secs_1970, the number of seconds since
 *						00:00:00 GMT, Jan 1, 1970.
 *
 *	INPUTS:				secs_1970, a long integer.
 *
 *	OUTPUTS:			Sets member data mo,day,yr,hr,min,sec,secs_1970,
 *						mos,day_of_week.
 *
 *	SIDE EFFECTS:		Object will be untrustworthy if the argument
 *						produces member data found not sane.
 *
 *	CONSTRAINTS:		Argument must be sane to guarantee proper
 *						object construction.
 *
 *	RELATED
 *	ROUTINES/FILES:		sscanf(3),ctime(3),localtime(3),input_sane().
 *
 *	RESTRICTIONS/
 *	PROBLEMS:			None.
 *
 */
void Date_time::init_secs1970(long secs_1970)
{
	struct tm *tm_ptr;		// from <time.h>, see ctime(3)

	secs1970 = secs_1970;
	sscanf(ctime(&secs1970),"%s%s%*s%*s%*s",day_of_week,mos);
	tm_ptr = localtime(&secs1970);
	mo = tm_ptr->tm_mon + 1;
	day = tm_ptr->tm_mday;
	yr = tm_ptr->tm_year;
	hr = tm_ptr->tm_hour;
	min = tm_ptr->tm_min;
	sec = tm_ptr->tm_sec;
}

/*
 *	FUNCTION:			Date_time constructor
 *
 *	PROCESS:			Construct a Date_time object representing
 *						the current date.
 *
 *	INPUTS:				None.
 *
 *	OUTPUTS:			Sets member data mo,day,yr,hr,min,sec,secs_1970,
 *						mos,day_of_week.
 *
 *	SIDE EFFECTS:		None.
 *
 *	CONSTRAINTS:		None.
 *
 *	RELATED
 *	ROUTINES/FILES:		time(2),init_secs1970()
 *
 *	RESTRICTIONS/
 *	PROBLEMS:			None.
 *
 */
Date_time::Date_time()
{
	long secs_1970;
	extern errno;

	state = _SUCCESS;
	secs_1970 = time((long *) 0);
	if (secs_1970 == -1) {
		setbuf("error in time(2), errno: %d\n",errno);
		state = _FAIL;
		return;
	}
	init_secs1970(secs_1970);
}

/* see comments for init_secs1970 */

Date_time::Date_time(long secs_1970)
{
	state = _SUCCESS;
	if (secs_1970 < 0) {
		state = _FAIL;
		return;
	}
	init_secs1970(secs_1970);
}

/*
 *	FUNCTION:			offset
 *
 *	PROCESS:			Make a new Date_time object that is a relative number
 *						of days/hours/min/sec from the object's date.
 *
 *	INPUTS:				The number of days/hours/min/sec to add to the 
 *						object's date.
 *
 *	OUTPUTS:			A new Date_time object.
 *
 *	SIDE EFFECTS:		None.
 *
 *	CONSTRAINTS:		None.
 *
 *	RELATED
 *	ROUTINES/FILES:		Constructor Date_time(long).
 *
 *	RESTRICTIONS/
 *	PROBLEMS:			None.
 *
 */
Date_time Date_time::offset(int days, int hours, int mins, int secs)
{
	int secs_1970;

	secs_1970 = secs1970 + days*SECS_IN_DAY
						 + hours*SECS_IN_HOUR 
						 + mins*SECS_IN_MIN 
						 + secs;
	Date_time future_dt(secs_1970);
	return future_dt;
}

/*
 *	FUNCTION:			conv_secs1970
 *
 *	PROCESS:			Return a long integer representing
 *						the number of seconds elapsed since 
 *						00:00:00 GMT, Jan 1, 1970 to this date.
 *
 *						Set time zone variables
 *
 *						Add century to yr
 *
 *						Initialize the secs_1970 return value to 0
 *
 *						secs_1970 += #days since 1970 to the year before yr
 *
 *						If yr is a leap year and mo is past Feb, 
 *							add another day to secs_1970
 *
 *						secs_1970 += #days since the beginning of the year up
 *						to but not including the days in mo.
 *
 *						secs_1970 += #days since the beginning of mo up
 *						to but not including the last day in mo
 *						
 *						Convert the #days in secs_1970 to hours
 *
 *						Add hr to secs_1970
 *
 *						Convert the #hrs in secs_1970 to minutes
 *
 *						Add min to secs_1970
 *
 *						Convert the #mins in secs_1970 to seconds
 *
 *						Add sec to secs_1970
 *
 *						Add the #seconds difference from Greenwich Mean Time
 *						to secs_1970
 *
 *						If in daylight savings time, subtract an hour's worth
 *						of seconds from secs_1970
 *
 *	INPUTS:				None
 *
 *	OUTPUTS:			The long integer conversion of the date/time string.
 *
 *	SIDE EFFECTS:		None.
 *
 *	CONSTRAINTS:		The private data members mo,day,yr,hr,min, and sec
 *						must be initialized and sanity checked before this 
 *						routine is called.
 *
 *	RELATED
 *	ROUTINES/FILES:		
 *
 *	RESTRICTIONS/
 *	PROBLEMS:			None.
 *
 */
long Date_time::conv_secs1970()
{
	int year,m,y;
	long secs_1970;

	tzset();	// set time zone
	year = BASE_CENTURY + yr;
	secs_1970 = 0;
	for (y=BASE_YEAR; y < year; y++) secs_1970 += days_in_year(y);
	if (days_in_year(year) == DAYS_IN_LEAP && mo > FEB) secs_1970++;
	for (m=JAN; m < mo; m++) secs_1970 += days_in_month(m);
	secs_1970 += (day-1);
	secs_1970 *= HOURS_IN_DAY;
	secs_1970 += hr;
	secs_1970 *= MINS_IN_HOUR;
	secs_1970 += min;
	secs_1970 *= SECS_IN_MIN;
	secs_1970 += sec;
	secs_1970 += timezone;
	if (localtime(&secs_1970)->tm_isdst) {
		secs_1970 -= 1*SECS_IN_MIN*MINS_IN_HOUR;
	}
	return(secs_1970);
}

/*
 *	FUNCTION:			days_in_month
 *
 *	PROCESS:			finds the number of days in a given month
 *
 *	INPUTS:				mo
 *
 *	OUTPUTS:			#days in mo
 *
 *	SIDE EFFECTS:		None.
 *
 *	CONSTRAINTS:		None.
 *
 *	RELATED
 *	ROUTINES/FILES:		None.
 *
 *	RESTRICTIONS/
 *	PROBLEMS:			None.
 *
 */
int Date_time::days_in_month(int mo)
{
	switch(mo) {
	case JAN:
	case MAR:
	case MAY:
	case JUL:
	case AUG:
	case OCT:
	case DEC:
		return(31);
	case APR:
	case JUN:
	case SEP:
	case NOV:
		return(30);
	case FEB:
		return(28);
	}
}

/*
 *	FUNCTION:			input_sane
 *
 *	PROCESS:			Makes sure the arguments are within proper ranges.
 *
 *	INPUTS:				mo,day,yr,hr,min,sec, as integers
 *
 *	OUTPUTS:			_FAIL if any of the arguments are out of range,
 *						else _SUCCESS.
 *
 *	SIDE EFFECTS:		None.
 *
 *	CONSTRAINTS:		None.
 *
 *	RELATED
 *	ROUTINES/FILES:		None.
 *
 *	RESTRICTIONS/
 *	PROBLEMS:			None.
 *
 */
states Date_time::input_sane()
{
	states ret = _SUCCESS;

	if (mo < JAN || mo > DEC) {
		addbuf("month out of range: %d\n",mo);
		ret = _FAIL;
	}
	int max_day = days_in_month(mo);
	if (days_in_year(yr) == DAYS_IN_LEAP && mo == FEB) max_day++;
	if (day < 1 || day > max_day) {
		addbuf("day out of range: %d\n",day);
		ret = _FAIL;
	}
	if (yr < MIN_YR || yr > MAX_YR) {
		addbuf("year out of range: %d\n",yr);
		ret = _FAIL;
	}
	if (hr < 0 || hr >= MAX_HR) {
		addbuf("hour out of range: %d\n",hr);
		ret = _FAIL;
	}
	if (min < 0 || min >= MAX_MIN) {
		addbuf("minutes out of range: %d\n",min);
		ret = _FAIL;
	}
	if (sec < 0 || sec >= MAX_SEC) {
		addbuf("seconds out of range: %d\n",sec);
		ret = _FAIL;
	}
	return ret;
}
