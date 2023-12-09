/*
 * FILE: timers.c (Generic alarm clock)    AUT: jc grams
 *
 * USE: many processes want to set timers.  While this is simple
 *	if only a single timer is in use, it becomes somewhat
 *	more complicated if multiple timers must be run.  This
 *	set of routines provide the application program with
 *	a way to handle many timers (or fuses) at once.
 */

#include <stdio.h>
#include <setjmp.h>
#include <osfcn.h>
#include <signal.h>
#include <Time.h>
#include "Timers.h"		/* interface definition header file */

#ifdef EBUG
#define STATIC
#else
#define STATIC static
#endif

#ifndef SIGALRM
// #include "sys/signal.h"
#endif

struct TIMEOUT {
    unsigned int to_id;
    unsigned long to_time;
    unsigned long to_leng;
				// changes made by shp - 6/24
    unsigned int length;	// length of the alarm period
    Time expiration;		// expiration time of the alarm
    unsigned int repeat;	// is it a snooze?
    int (*to_func)(int, Time);	// modified to return the alarm expration time
    struct TIMEOUT *to_next;
    struct TIMEOUT *to_back;
};

#define NUL_TIMEOUT 	((struct TIMEOUT *)0)
#define NUL_TOFUNC	((int (*)(int, Time))0)
#define TO_STACK	5
#define EMPTY_ID	0
#define TIME_LIMIT	604800L		/* seconds in a week */

STATIC struct TIMEOUT to_table[MAX_TIMEOUTS];  /* timer table */
STATIC struct TIMEOUT *to_pending[TO_STACK];   /* temporary stack */
STATIC struct TIMEOUT *to_head = NUL_TIMEOUT;  /* active timer list */
STATIC unsigned int nextstack = 0;	       /* stack top */
typedef enum {
	TRUE = 1,
	FALSE = 0,
} BOOL;
STATIC BOOL ifever = FALSE;		       /* first time flag */
STATIC BOOL to_ignore = FALSE;		       /* ignore flag */
STATIC BOOL in_tmsleep = FALSE;		       /* in sleep routine */

STATIC struct TIMEOUT *alloc_timer();
STATIC struct TIMEOUT *find_timer(unsigned int);

STATIC void init_timertable();
STATIC void free_timer(struct TIMEOUT *);
STATIC void add_timer(struct TIMEOUT *);
STATIC void rmv_timer(struct TIMEOUT *);
STATIC void start_timer(struct TIMEOUT *);
STATIC void chg_timer(struct TIMEOUT *, int);

STATIC unsigned int howlong(unsigned int);

extern Time current_time();
extern Time now();

int set_timer(unsigned int, Time, unsigned int, unsigned int, int (*)(unsigned int, Time));
int reset_timer(unsigned int, unsigned int, unsigned int, unsigned int, int (*)(unsigned int, Time));
int ext_timer(unsigned int, unsigned int);
int can_timer(unsigned int);
int slp_timer(unsigned int);
STATIC int dump_timer_table(FILE*);

void timers_hndlr(int);

// extern long time(long*);
jmp_buf save_env;

/*
 * init_timertable() - called first time a set_timer call is
 *	done.  Sets up the timer table to the initial state.
 */

STATIC void
init_timertable()
{
    register struct TIMEOUT *dev;
    register int i;

    for (i=0, dev=to_table; i<MAX_TIMEOUTS; i++, dev++) {
	dev->to_id = EMPTY_ID;
	dev->to_leng = 0;
	dev->to_time = 0;
	dev->length = 0;		// modified by shp 6/24/89
	dev->repeat = 0;		// modified by shp 6/24/89
	dev->to_func = NUL_TOFUNC;
	dev->to_next = NUL_TIMEOUT;
	dev->to_back = NUL_TIMEOUT;
    }
    for (i=0; i<TO_STACK; i++)
	to_pending[i] = NUL_TIMEOUT;
}

/*
 * alloc_timer() - allocate an available slot in the TIMEOUT table
 */

STATIC struct TIMEOUT *
alloc_timer()
{
    register int i;
    register struct TIMEOUT *dev;

    for (i=0, dev=to_table; i < MAX_TIMEOUTS; i++, dev++) {
	if (dev->to_id == EMPTY_ID && dev->to_time == 0)
	    return(dev);
    }
    return(NUL_TIMEOUT);
}

/*
 * free_timer() - de-allocate a used slot in the TIMEOUT table.
 *		Must not be on the active timer list or dire things
 *		will happen.
 */

STATIC void
free_timer(register struct TIMEOUT *dev)
{
    dev->to_id = EMPTY_ID;
    dev->to_leng = 0;
    dev->to_time = 0;
    dev->length = 0;			// modified by shp 6/24/89
    dev->repeat = 0;			// modified by shp 6/24/89
    dev->to_func = NUL_TOFUNC;
    dev->to_next = NUL_TIMEOUT;
    dev->to_back = NUL_TIMEOUT;
}

/*
 * howlong() - count about how many seconds remain for a particular id
 */

STATIC unsigned int
howlong(unsigned int id)
{
    register struct TIMEOUT *dev;
    register unsigned int secs;

    if (find_timer(id) == NUL_TIMEOUT)
	return(0);
    dev = to_head; secs = 0;
    while (dev->to_id != id) {
	secs += (unsigned int)(dev->to_leng);
	dev = dev->to_next;
    }
    secs += (unsigned int)(dev->to_leng);
    return(secs);
}

/*
 * find_timer() - find a particular timer in the table by using
 *	the to_id.
 */

STATIC struct TIMEOUT* 
find_timer(unsigned int id)
{
    register int i;
    register struct TIMEOUT *dev;

    for (i=0, dev=to_table; i < MAX_TIMEOUTS; i++, dev++) {
	    if (dev->to_id == id)
		return(dev);
    }
    return(NUL_TIMEOUT);
}
 
STATIC void
add_timer(struct TIMEOUT *dev)
{
    register struct TIMEOUT *tp, *op;
    long timenow; 
//  long time(long*);

    /*
     * Put this request on the stack, just in case of an interrupt
     * during the time() system call.
     */
    if (nextstack == TO_STACK) {
	/*
	 * overflow - very bad, hope this never happens in practice
	 */
#ifdef EBUG
	fprintf(stderr, "Timer stack overflow!\n");
	abort();
#else
	return;
#endif
    } else {
	to_pending[nextstack] = dev;
	nextstack++;
    }
    timenow = time((long *)0);
    do {
	/*
	 * for each timer now pending, set it
	 */
	dev = to_pending[--nextstack];
	to_pending[nextstack] = 0;
	dev->to_time = timenow + dev->to_leng;
        op = NUL_TIMEOUT;
        if((tp=to_head) == NUL_TIMEOUT) {
	    /*
	     * No timers currently active, make this one the active one
	     */
	    to_head = dev;
	    to_head->to_next = NUL_TIMEOUT;
	    to_head->to_back = NUL_TIMEOUT;
	    start_timer(to_head);
        } else {
            /*
             * Look down the list of active timers to find where this
             * one should go.  If it goes in the front or the back, it
             * is a special case.
             */
            while(tp != NUL_TIMEOUT) {
                if (dev->to_time < tp->to_time)
    	            break;
                else {
    	            op = tp;
    	            tp = tp->to_next;
                }
            }
            if (tp == NUL_TIMEOUT) {
                /*
                 * got to end of list, add this timer there.
                 */
                dev->to_back = op;
		dev->to_leng = dev->to_time - op->to_time;
                dev->to_next = NUL_TIMEOUT;
                op->to_next = dev;
            } else {
                /*
                 * need to insert here
                 */
		if (op == NUL_TIMEOUT) {
                    /*
    	             * It goes ahead of the currently running timer.  We
    	             * must stop the current timer and start this one.
    	             */
		    to_ignore = TRUE;
		    alarm(0);
		    to_ignore = FALSE;
		    if (tp->to_time > dev->to_time)
		        tp->to_leng = tp->to_time - dev->to_time;
		    else
		        tp->to_leng = 0;
		    to_head = dev;
		    dev->to_next = tp;
		    dev->to_back = NUL_TIMEOUT;
		    tp->to_back = dev;
		    start_timer(to_head);
		} else {
		    /*
		     * It goes after a non-active timer.  Adjust the
		     * leng field accordingly.
		     */
		    op->to_next = dev;
		    dev->to_back = op;
		    dev->to_next = tp;
		    tp->to_back = dev;
		    dev->to_leng = dev->to_time - op->to_time;
		    tp->to_leng -= dev->to_leng;
		}
	    }
	}
    } while (nextstack != 0);
}

STATIC void
rmv_timer(struct TIMEOUT *dev)
{
    register struct TIMEOUT *tp;
    register int remain;

    if (dev == to_head) {
	/*
	 * Removing the active timer.  Cancel alarm,
	 * adjust list head, if another timer to run,
	 * adjust length and start it.
	 */
	to_ignore = TRUE;
	remain = alarm(0);
	to_ignore = FALSE;
	to_head = dev->to_next;
	if (to_head != NUL_TIMEOUT) {
	    to_head->to_back = NUL_TIMEOUT;
	    to_head->to_leng += remain;
	    start_timer(to_head);
	}
    } else {
	/*
	 * Removing a non-active timer.  Remove from
	 * list, remembering to adjust following timer's
	 * length.
	 */
	tp = dev->to_next;
	if (tp != NUL_TIMEOUT) {
	    tp->to_leng += dev->to_leng;
	    tp->to_back = dev->to_back;
	}
	tp = dev->to_back;
	if (tp != NUL_TIMEOUT)
	    tp->to_next = dev->to_next;
    }
}

STATIC void
chg_timer(struct TIMEOUT *tp, int amt)
{
    BOOL done = FALSE;
    BOOL wasfirst = FALSE;

    tp->to_time += amt;
    if (tp == to_head) {
	/*
	 * extending current timer.  first bring it up to
	 * the current time.  Then treat it the same.
	 */
	wasfirst = TRUE;
	to_ignore = TRUE;
	tp->to_leng = alarm(0);
	to_ignore = FALSE;
    }

    /*
     * now need to insert change in the list, possibly
     * moving the position of this timer.
     */
    while (done == FALSE) {
        if (tp->to_next == NUL_TIMEOUT) {
    	    /*
    	     * easy at this point, just extend the last timer
    	     * and exit the while.
    	     */
            tp->to_leng += amt;
            done = TRUE;
        } else if (amt > tp->to_next->to_leng) {
            /*
             * position needs to change.  Rearrange the list
    	     * order, reduce the amt, and leave the timer on
    	     * the list, directly behind its former successor.
    	     * stay in the while.
             */
            amt -= (unsigned int)(tp->to_next->to_leng);
            tp->to_next->to_leng += tp->to_leng;
            tp->to_next->to_back = tp->to_back;
	    if (tp->to_back != NUL_TIMEOUT) {
		/*
		 * not current at head
		 */
                tp->to_back->to_next = tp->to_next;
	    } else {
		to_head = tp->to_next;
	    }
            tp->to_back = tp->to_next;
            tp->to_next = tp->to_next->to_next;
	    if (tp->to_next != NUL_TIMEOUT)
		tp->to_next->to_back = tp;
	    tp->to_back->to_next = tp;
            tp->to_leng = 0;
        } else {
            tp->to_leng += amt;
	    tp->to_next->to_leng -= amt;
            done = TRUE;
        }
    }
    if (wasfirst == TRUE)
	start_timer(to_head);
}

/*
 * start_timer() - initiate a timer 
 */

STATIC void
start_timer(struct TIMEOUT *tp)
{
    void timers_hndlr(int);
    int i = 0;
    SIG_PF alarm_handler;

    alarm_handler = timers_hndlr;

    signal(SIGALRM, alarm_handler);
    if (tp->to_leng <= 0)
	/*
	 * this timer has already expired. Simulate the event
	 */
	timers_hndlr(i);
    else if (alarm((unsigned int)(tp->to_leng)) > 0) {
#ifdef EBUG
	fprintf(stderr, "Whoops! Timer was active\n");
#endif
	return;
    }
    return;
}

/*
 * timers_hndlr() - catches the SIGALRM, cleans up the timeout table
 *	and calls the user's signal handler.  Fakes a signal reception
 *	for NULL functions.
 */

void
timers_hndlr(int i)
{
    register struct TIMEOUT *tp;
    int (*func)(int, Time), id, length, repeat;
    Time expiration;

    if (to_ignore == TRUE) {
	/*
	 * timer went off as we were trying to cancel it
	 */
	return;
    }
    /*
     * get rid of the current timer.  Call the user's function
     * If there are more timers to run, start it up.
     */
    tp = to_head;
    to_head = tp->to_next;
    if (to_head != NUL_TIMEOUT)
	to_head->to_back = NUL_TIMEOUT;
    func = tp->to_func;
    id = tp->to_id;
    length = tp->length;
    repeat = tp->repeat;
    expiration = tp->expiration + seconds(length);
    free_timer(tp);
    if (repeat == 1){
	set_timer(id, expiration, length, repeat, func);
    }
    if (func != NUL_TOFUNC)
	(*func)(id, now());
    if (to_head != NUL_TIMEOUT)
	start_timer(to_head);
    if (id == TM_SLEEPID)
	longjmp(save_env, 1);
    return();
}

/*
 * ENTRY_POINT:  set_timer()
 */

int
set_timer(unsigned int id, Time expiration, unsigned int when, 
	  unsigned int repeat, int (*func)(int, Time))
{
    register struct TIMEOUT *dev;
    Duration interval;

    if (ifever == FALSE) {
	ifever = TRUE;
	init_timertable();
    }

    if (id == 0 || (id == TM_SLEEPID && in_tmsleep == FALSE) ||
		when > TIME_LIMIT) {
	/*
	 * Value judgement.
	 */
	return(-3);
    }

    if ((dev=find_timer(id)) != NUL_TIMEOUT) {
	/*
	 * Timer already active
	 */
	return(-1);
    }

    if ((dev=alloc_timer()) == NUL_TIMEOUT) {
	/*
	 * No room in time out table
	 */
	return(-2);
    }

    dev->to_id = id;
    dev->expiration = expiration;
    interval = expiration - current_time();
    dev->to_leng = seconds(interval);
    dev->length = when;
    dev->to_time = 0L;		/* set later in add_timer */
    dev->repeat = repeat;
    dev->to_func = func;
    add_timer(dev);
    return(0);
}

/*
 * ENTRY_POINT: reset_timer()
 */

int
reset_timer(unsigned int id, unsigned int when,
	  unsigned int repeat, int (*func)(int, Time))
{
    register struct TIMEOUT *dev;

    if (ifever == FALSE) {
	/*
	 * Obviously, set_timer never called, so id is invalid
	 */
	return(-1);
    }

    if (id == 0 || (id == TM_SLEEPID && in_tmsleep == FALSE) ||
		when > TIME_LIMIT) {
	/*
	 * Value judgement.
	 */
	return(-2);
    }

    if ((dev=find_timer(id)) == NUL_TIMEOUT) {
	/*
	 * id is not currently running
	 */
	return(-1);
    }

    rmv_timer(dev);
    dev->to_leng = when;
    dev->length = when;
    dev->repeat = repeat;
    dev->to_func = func;
    add_timer(dev);
    return(0);
}

/*
 * ENTRY_POINT: ext_timer()
 */

int
ext_timer(unsigned int id, unsigned int amt)
{
    register struct TIMEOUT *dev;

    if (ifever == FALSE) {
	/*
	 * Obviously, set_timer never called, so id is invalid
	 */
	return(-1);
    }

    if (id == 0 || (id == TM_SLEEPID && in_tmsleep == FALSE) ||
		amt > TIME_LIMIT) {
	/*
	 * Value judgement.
	 */
	return(-2);
    }

    if ((dev=find_timer(id)) == NUL_TIMEOUT) {
	/*
	 * id is not currently running
	 */
	return(-1);
    }

    chg_timer(dev, amt);
    return(0);
}

/*
 * ENTRY_POINT: can_timer()
 */

int
can_timer(unsigned int id)
{
    register struct TIMEOUT *dev;

    if (id == 0 || (id == TM_SLEEPID && in_tmsleep == FALSE) ||
		ifever == FALSE) {
	/*
	 * Obviously, if set_timer was never called, id is invalid
	 */
	return(-1);
    }

    if ((dev=find_timer(id)) == NUL_TIMEOUT) {
	/*
	 * id is not currently running
	 */
	return(-1);
    }

    rmv_timer(dev);
    free_timer(dev);
    return(0);
}

/*
 * ENTRY POINT: slp_timer()
 *
 *	This routine is not re-entrant.
 */

int
slp_timer(unsigned int s)
{
    int remain;

    if (in_tmsleep == TRUE) {
	/*
	 * weird.  error.
	 */
	return(-1);
    }
    in_tmsleep = TRUE;
    if ((remain=setjmp(save_env)) == 0) {
        if (set_timer(TM_SLEEPID, current_time(), s, 0, NUL_TOFUNC) < 0) {
	    in_tmsleep = FALSE;
	    return(-1);
        }
#ifdef EBUG
	dump_timer_table(stderr);
#endif
	pause();
    }
    if (remain == 0) {
	/*
	 * got interrupted from pause
	 */
	remain = howlong(TM_SLEEPID);
	can_timer(TM_SLEEPID);
	in_tmsleep = FALSE;
	return(remain);
    } else {
	/*
	 * completed sleep, returned via longjmp
	 */
	in_tmsleep = FALSE;
	return(0);
    }
}

/*
 * Special debugging routine, can be called by user if EBUG is defined
 */

STATIC int
dump_timer_table(FILE *fp)
{
#ifndef EBUG
    return(0);
#else
    struct TIMEOUT *tp;
    char *ctime(long*);
    int i;

    for (tp=to_head, i = 1; tp != NUL_TIMEOUT; tp=tp->to_next, i++) {
	fprintf(fp, "Entry %d: Id: %d  Len: %d  Time: %s",
	    i, tp->to_id, tp->to_leng, ctime(&tp->to_time));
    }
#endif
}

static char sccs_id[] = "@(#)timers.c	7.1.2.1";
