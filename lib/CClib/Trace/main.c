
/*********************************************************************
PROCESS: tracer
AUTHOR: Kim Tran
VERSION: 1

FUNCTION: main

DESCRIPTION:
    this is the process that provides the external controls over
    Trace facility functionalities imbedded in CMS processes.

**********************************************************************/

// temp
int CMS_err;

#include <string.h>
#include <time.h>
#include "c_tr_hdrs.h"

#define BUF_SZ 100
#define QUIT 0

// regular function declarations
extern "C" {
    long time (long *);
};

int cmd_process ();
void get_num (char *, int *);
void get_str (char *, char *);
void get_ch (char *, char *);
void get_pid (char *, int *);
void new_trace (struct sm_slot *);

int
main (int argc) {
    // attach Trace shared memory for R/W
    Trace_SM.attach (0);

    // search through shared memory looking for UNINITITATED trace 
    // records older than 24 hours and remove them 
    Trace_SM.setlock ();
    Trace_SM.cleanup (24);
    Trace_SM.unlock ();

    if (argc > 1) {
	printf ("Trace Shared Memory ID: %d\n", Trace_SM.get_shmid ());
	printf ("Trace Semaphore ID: %d\n", Trace_SM.get_semid ());
    }
    else {
    // process commands until quit
        int ret = CONT;
        do {
	    ret = cmd_process ();
        } while (ret != QUIT);
    }
	
    // detach shared memory
    Trace_SM.detach ();
    exit (0);
}



/**********************************************************************
PROCESS: tracer

FUNCTION: cmd_process

DESCRIPTION:
    presents options to the user and process each valid option entered.

**********************************************************************/

int
cmd_process () { 

    // prompt for user options
    printf ("\nSelect one of following options:\n");
    printf ("    1. Activate a trace\n");
    printf ("    2. Stop a trace\n");
    printf ("    3. List trace activation records\n");
    printf ("    4. Quit\n");

    // get option number
    int option;
    get_num ("Enter option number: ", &option);

    char pname[NAME_SZ+1];
    int pid;
    struct sm_slot *slot_ptr;

    // NOTICE: It seems more standard to use 'switch' here, but somehow
    // using switch will coredump this process with option 1 and
    // kill it with option 2. And strangely this only occurs when the
    // Shared Memory is first allocated. After that everything is fine.
    // Using 'if' removes the problems described.

    if (option == 1) {
        struct sm_slot act_rec;

	get_pid (act_rec.pg_name, &(act_rec.pid));

	new_trace (&act_rec);

	// add the record to ShMem
	Trace_SM.setlock ();
	slot_ptr = Trace_SM.seize ();
	if (slot_ptr == NULL) {
	    printf ("Sorry - No more activation slot\n");
	    Trace_SM.unlock ();
	    return (CONT);
	}

	*slot_ptr = act_rec;
	Trace_SM.unlock ();
	printf ("Trace for '%s' successfully activated\n", act_rec.pg_name); 
	return (CONT);

    }

    if (option == 2) {
	get_pid (pname, &pid);
	slot_ptr = Trace_SM.search (pname, pid);
	if (slot_ptr == NULL) {
	    printf ("Sorry - trace activation not exist\n");
	    return (CONT);
	}

	// remove this activation record
	Trace_SM.setlock ();
	Trace_SM.free (slot_ptr);
	Trace_SM.unlock ();

	printf ("Trace for '%s' successfully stopped\n", pname); 
	return (CONT);
    }

    if (option == 3) {
    // list activation records
	int slot_cnt = 0;
	int iter_code = RESET;
	while ((slot_ptr = Trace_SM.iterate (iter_code)) != NULL) {
	    printf ("\nProcess name: %s\n", slot_ptr->pg_name);

	    if (slot_ptr->pid == 0) {
		printf ("\tProcess ID: (not initiated)\n");
	    }
	    else {
	        printf ("\tProcess ID: %d\n", slot_ptr->pid);
	    }

	    printf ("\tTrace types: ");
	    if (slot_ptr->trace_type & HIGH) {
	        printf ("HIGH ");
	    }
	    else if (slot_ptr->trace_type & MED) {
	        printf ("MEDIUM ");
	    }
	    else if (slot_ptr->trace_type & LOW) {
	        printf ("LOW ");
	    }

	    if (slot_ptr->trace_type & TIME) {
		printf ("and TIME\n");
	    }
	    else {
		printf ("\n");
	    }

	    if (slot_ptr->beg_func[0] == '\0') {
	        printf ("\tBegin function: (none)\n");
	    }
	    else {
	        printf ("\tBegin function: %s\n", slot_ptr->beg_func);
	    }

	    if (slot_ptr->end_func[0] == '\0') {
	        printf ("\tEnd function: (none)\n");
	    }
	    else {
	        printf ("\tEnd function: %s\n", slot_ptr->end_func);
	    }

	    printf ("\tOutput file: %s\n", slot_ptr->outfile);
	    printf ("\tActivation time: %s\n", ctime (&slot_ptr->acttime));
	    ++slot_cnt;
	    iter_code = CONT;
	}

	printf ("\nTotal: %d activation records\n", slot_cnt);
	return (CONT);
    }

    if (option == 4) {
    // quit
        return (QUIT);
    }

    // invalid option
    printf ("Sorry - invalid option\n");

    return (CONT);
}




/**********************************************************************
PROCESS: tracer

FUNCTION: get_num 

DESCRIPTION:
    prompts and gets a number from the user.

**********************************************************************/

void
get_num (char *prompt, int *num) {
    char buf[BUF_SZ];
    printf ("%s", prompt);
    fgets (buf, BUF_SZ, stdin);
    *num = 0;
    sscanf (buf, "%d", num);
    return;
}


/**********************************************************************
PROCESS: tracer

FUNCTION: get_str 

DESCRIPTION:
    prompts and gets a string from the user.

**********************************************************************/
void
get_str (char *prompt, char *sbuf) {
    char buf[BUF_SZ];
    printf ("%s", prompt);
    fgets (buf, BUF_SZ, stdin);
    sbuf[0] = '\0';
    sscanf (buf, "%s", sbuf);
    return;
}

/**********************************************************************
PROCESS: tracer

FUNCTION: get_ch 

DESCRIPTION:
    prompts and gets a char from the user.

**********************************************************************/
void
get_ch (char *prompt, char *c) {
    char buf[BUF_SZ];
    printf ("%s", prompt);
    fgets (buf, BUF_SZ, stdin);
    sscanf (buf, "%1s", c);
    return;
}

/**********************************************************************
PROCESS: tracer

FUNCTION: get_pid 

DESCRIPTION:
    prompts and gets the identity (name and PID) of a process

**********************************************************************/
void 
get_pid (char *pname, int *pid) {

    get_str ("process name? ", pname);
    get_num ("process PID (-1 for test process or <CR> if unique)? ", pid);
    return;
}



/**********************************************************************
PROCESS: tracer

FUNCTION: new_trace 

DESCRIPTION:
    prompts and gets info for a new trace activation.

**********************************************************************/
void
new_trace (struct sm_slot *act_rec) {

    int level, done;
    do {
        printf ("Select level of trace:\n");
        printf ("    1. LOW\n");
        printf ("    2. MEDIUM\n");
        printf ("    3. HIGH\n");

        get_num ("Level of trace? ", &level);
	done = YES;
	switch (level) {
	    case 1: 
		level = LOW;
	        break;
	    case 2:
		level = MED;
		break;
	    case 3:
		level = HIGH;
		break;
	    default:
		printf ("Invalid option entered - enter 1,2, or 3\n");
		done = NO;
		break;
	}
    } while (done == NO);

    char ans;
    get_ch ("Is process TIMING needed? (y/n) ", &ans);
    if (ans == 'y') {
	level = level|TIME;
    }

    char beg_func[50], end_func[50], outfile[50];
    get_str ("Function to START trace (<CR> for none)? ", beg_func);
    get_str ("Function to STOP trace (<CR> for none)? ", end_func);
    get_str ("Output file? ", outfile); 

   // form the record
   strncpy (act_rec->outfile, outfile, FNAME_SZ);
   act_rec->outfile[FNAME_SZ] = '\0';

   act_rec->trace_type = level;

   strncpy (act_rec->beg_func, beg_func, NAME_SZ);
   act_rec->beg_func[NAME_SZ] = '\0';

   strncpy (act_rec->end_func, end_func, NAME_SZ);
   act_rec->end_func[NAME_SZ] = '\0';

   act_rec->acttime = time (0);

   return;
}

