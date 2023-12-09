#include <Time.h>
#include <stdio.h>
#include <signal.h>
#include "Timers.h"
#include <libc.h>

#define FALSE	0
#define TRUE	1
#define ERROR  -1
#define SUCCESS 0

extern Time current_time();
typedef int AlarmId;
typedef int (*AlrmHndlr)(AlarmId, Time);

class Tim{

	private:
		static double speed;		
		static unsigned int next_id;
		Time start_time;
		Time simulated_time;
		int run_state;

	public:
		    	Tim();

		Time	currTime();
		Time	realTime();

		AlarmId	alarm(Duration, AlrmHndlr,
			      int real = 0);
		AlarmId	alarm(Time, AlrmHndlr, 
			      int real = 0);

		AlarmId	snooze(Duration, AlrmHndlr, 
			       int real = 0);
		AlarmId	snooze(Duration, Time,
			       AlrmHndlr, int real = 0);

		int	clear(AlarmId);

		void debug();


};

extern Tim tim;

inline
Time Tim::currTime() { 
	Time ctm = current_time(), ntm;
	Duration offset = ctm - start_time;
	ntm = simulated_time + seconds(seconds(offset)*speed);
	return(ntm);
}

inline
Time Tim::realTime() { return(make_time(time(0))); }


