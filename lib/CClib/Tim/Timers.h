#define TM_SLEEPID  0x1FFFFFFF	
#define MAX_TIMEOUTS	300

typedef int alarm_id;
typedef int (*alarm_handler)(alarm_id, Time);

extern int set_timer(unsigned int, Time, unsigned int, unsigned int, 
		     alarm_handler);

extern int reset_timer(unsigned int, unsigned int, unsigned int, unsigned int,
		       alarm_handler);
 
extern int ext_timer(unsigned int, unsigned int);
 
extern int can_timer(unsigned int);

extern int slp_timer(unsigned int);

