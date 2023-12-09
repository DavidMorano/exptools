
	/************************************************************************
	*									*
	*	This code is designed to encapsulate the UNIX alarm facility	*
	*	and make it easy for the user to specify multiple alarms &	*
	*	snoozes.  Since the UNIX system provides no easy way to stack	*
	*	multiple alarm calls, it lies upon each individual programmer	*
	*	to make sure that multiple alarm calls get handled correctly	*
	*	etc.  This code maintains a list of scheduled alarms and 	*
	*	automatically calls a user specified handler when an alarm	*
	*	expires.  It will then set the next alarm for the correct time.	*
	*									*
	*	A snooze facility, designed to emulate a periodic alarm, is 	*
	*	provided.							*
	*									*
	*	This code is built on top of a set of routines written by	*
	*	J. C. Grams for the EADAS project.  That code resides in a	*
	*	file called Timers.c in this subdirectory.			*
	*									*
	*	The Time and Duration classes from Liberty Corner are also	*
	*	utilized.							*
	*									*
	*	Written by:		Sanjay H. Patel				*
	*				AT&T Bell Labs				*
	*				October 11, 1989			*
	*									*
	*	Modification History:	October 16, 1989 - Modified the code to	*
	*				work with decimal speeds. (shp)		*
	*									*
	*				October 17, 1989 - Added trace stats.	*
	*									*
	************************************************************************/

#include "Tim.h"
#include <math.h>

#define REPEAT 1
#define NO_REPEAT 0
#define SYNCH 0
#define UNSYNCH 1

Tim tim;					// Global instance of class 

Time current_time(){				// Returns current system time
	return(make_time(time(0)));
}

Time now(){					// Returns the Tim internal time
	return(tim.currTime());
}

/*	This function returns the last time at which a boundary defined
	by interval would have been reached.  This assumes that time
	starts at midnight, and an interval of 15 minutes implies that
	the caller wants to synchronize to 0, 15, 30, 45 minutes after
	the hour
*/

Time synch_up(Duration interval){
	
	Time tm, synch;
	register unsigned int yr, dy;
	Month mnth;


	tm = current_time();			// current system time
	yr = tm.year_part();			// set synch date to today
	mnth = tm.month_part();
	dy = tm.day_part();

	Time start(yr, mnth, dy);		// set synch time to midnight
	synch = start + ((tm - start) / interval) * interval;
	

	return(synch);
}

Tim::Tim(){
	
	register char *speed_val, *time_val;

	if (next_id == 0) {			// First time ??
	  speed_val = getenv("TIM_SPEED");  	// Get speed value from env.
	  if (speed_val == 0)			// Speed not set
	    speed = 1;
	  else 
	    speed = abs(atof(speed_val));	// Only +ve speed makes sense
	  time_val = getenv("TIM_TIME");	// Get start time from env.
	  if (time_val != 0){			// Time value set
	  
	   //  make the start time right now & internal time from time_val
	    
	    simulated_time = make_time(time_val, HERE);
	    start_time = current_time();
	    run_state = UNSYNCH;			//  NOT NEEDED?
	  }
	  else{					// Time value not set
	   
	    //  We round start time to the last hour bounadry.  This is an
	    //  arbitrary choice, picked because the 800DCS problem was
	    //  based on 3 minute & 15 minute intervals
	    
	    Duration synch_interval(0,1,0,0);
	    simulated_time = start_time = synch_up(synch_interval);
	    run_state = SYNCH;
	  }
	  sleep(1);				// chill for a second
	  next_id++;				// up the id counter
        }
}

/*	currTime() - returns the current Tim time to the caller

	INPUT CONDITIONS  :  None
	OUTPUT CONDITIONS :  Returns a pointer to a Time object

-->	This function is declared inline in Tim.h

Time
Tim::currTime(){

	Time ctm = current_time(), ntm;
	Duration offset = ctm - start_time;
	ntm = simulated_time + seconds(seconds(offset)*speed); 
	return(ntm);
}
*/

/*	realTime() - returns the system time to the caller

	INPUT CONDITIONS  :  None
	OUTPUT CONDITIONS :  Returns a pointer to a Time object

-->	This function is declared inline in Tim.h

Time
Tim::realTime(){
	return(make_time(time(0)));
}
*/

/*	alarm(Duration interval, AlrmHndlr alarm_func, int real)
	   This function takes an interval and sets an alarm
	   interval seconds from now if real is true and
	   interval/speed (rounded off to the nearest second) seconds
	   from now if real is false.

	   The function returns the id of the alarm.

	INPUT CONDITIONS  :  A valid duration, a valid handler
	OUTPUT CONDITIONS :  An alarm is set
*/

AlarmId
Tim::alarm(Duration interval, AlrmHndlr alarm_func, int real){

	register unsigned int sec;
	register unsigned int id = Tim::next_id;	// Id of this alarm
	if (real == FALSE) 				// Do speed up!!
	  sec = (unsigned int)(seconds(interval)/speed);
	else						// Do not speed up!!
	  sec = (unsigned int)(seconds(interval));
	if (sec <= 0){					// speed set to high!!
	  sec = 1;
	}
	Time expiration = current_time() + seconds(sec);	
	if (set_timer(id, expiration, sec, NO_REPEAT, alarm_func) == 0){
	  Tim::next_id++;				// Increment id counter
	  return(id);
	}
	else {
	  return(ERROR);
	}
}

/*	alarm(Time when, AlrmHndlr alarm_func, int real)
	   This function takes a time and sets an alarm
	   to go off at when if real is true and to go off
	   at relative Tim time when if real is false.

	   The function returns the id of the alarm.

	INPUT CONDITIONS  :  A valid time, a valid handler
	OUTPUT CONDITIONS :  An alarm is set
*/

AlarmId
Tim::alarm(Time when, AlrmHndlr alarm_func, int real){

	Time time_now;
	Duration interval;

	if (real == FALSE)				// look at system time
	  time_now = now();				
	else						// else internal Tim time
	  time_now = current_time();
	if (when < time_now){				// Time is already past!
	  return(ERROR);
	}
	else{
	  if (real == FALSE){
	    interval = when - time_now;
	    interval = seconds(seconds(interval)/speed);
	  }
	  else
	    interval = when - time_now; 
	  return(Tim::alarm(interval, alarm_func, real));
	}
}

/*	clear() - Cancel an alarm/snooze previously set.
*/

int
Tim::clear(AlarmId id){
	return(can_timer(id));
}

/*	snooze(Duration interval, AlrmHndlr alarm_func, int real)

	This function takes a duration and sets an alarm that goes
	off every X seconds where X is specified as the interval.
	If real is set to true then the duration is not speeded up,
	otherwise it is.

	The function returns the id of the snooze.

     INPUT CONDITIONS  : A valid duration and handler
     OUTPUT CONDITIONS : An alarm will expire every interval until cleared
*/

AlarmId
Tim::snooze(Duration interval, AlrmHndlr alarm_func, int real){

	register unsigned int sec;
	register unsigned int id = Tim::next_id;
	Time expiration;

	if (real == FALSE){
	  sec = (unsigned int)(seconds(interval)/speed);
	  interval = seconds(seconds(interval)/speed);
	}
	else 
	  sec = (unsigned int)(seconds(interval));
	if (sec <= 0){					// Speed set too high!!
	  sec = 1;					// Min int is 1 sec
	  interval = seconds(1);
	}
	if (Tim::run_state == SYNCH)			// SYNCH mode - synchup
	  expiration = synch_up(interval) + seconds(sec);  // next boundary of sec
	else
	  expiration = current_time() + seconds(sec);

	// The first alarm will go off at expiration, and then every sec after
	if (set_timer(id, expiration, sec, REPEAT, alarm_func) == 0){
	  Tim::next_id++;
	  return(id);
	}
	else{
	  return(ERROR);
	}
}

/*	snooze(Duration interval, Time when, AlrmHndlr alarm_func, int real)

	This function takes a duration and sets an alarm that goes
	off every X seconds where X is specified as the interval.
	The first alarm will go off at the time specified by when.
	If real is set to true then the duration is not speeded up,
	and when is assumed to be the system time.  If real is false
	then when implies the internal TIM time, and the interval is
	assumed to be fast.

	The function returns the id of the snooze.

     INPUT CONDITIONS  : A valid duration and handler
     OUTPUT CONDITIONS : An alarm will expire every interval until cleared
*/

AlarmId
Tim::snooze(Duration interval,  Time when, AlrmHndlr alarm_func, int real){
	
	register unsigned int sec;
	register unsigned int id = Tim::next_id;
	Time time_now = current_time();
	Time expiration; 

	if (real == FALSE){				// look at internal TIM time
	  sec = (unsigned int)(seconds(interval)/speed);
	  if (sec <= 0){
	    sec = 1;
	  }
	  interval = when - simulated_time;
	  expiration = seconds(seconds(interval)/speed) + start_time;
	}	
	else{						// else system time
	  sec = (unsigned int)(seconds(interval));
	  expiration = when;
	}

	while (expiration < time_now)			// find next boundary
	  expiration = expiration + sec;
	if (set_timer(id, expiration, sec, REPEAT, alarm_func) == 0){
	  Tim::next_id++;
	  return(id);
	}
	else{
	  return(ERROR);
	}
}


