/*
**********************************************************************
CLASS: trace_sm
AUTHOR: Kim Tran
VERSION: 1
**********************************************************************
*/
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <string.h>
#include "c_tr_hdrs.h"

extern "C" {
    long time (long *);
    void perror (const char *);
}

trace_sm::trace_sm () {
    shm_ptr = NULL;
}

int
trace_sm::attach (int mode)
{
    // locate or create sema4 to control Trace ShMem
    semid = semget (TRACE_LK, 1, IPC_CREAT|0666);

    /// set ownership of sema4 to root
    // get sema4 stat
    semun stat;
    struct semid_ds sem_stat;

    stat.buf = &sem_stat; 
    if (semctl (semid, 0, IPC_STAT, stat) == -1) {
	perror ("trace - semctl - IPC_STAT");
	return (-1);
    }

    // set uid to ROOT if it's not set before
    if (stat.buf->sem_perm.uid != 0) {
	stat.buf->sem_perm.uid = 0;
        if (semctl (semid, 0, IPC_SET, stat) == -1) {
	    perror ("trace - semctl - IPC_SET");
	    return (-1);
        }
    }
	

    /// check if Trace shared memory is allocated the first time -
    /// if so, init sema4 to make Trace ShMem available

    shmid = shmget (TRACE_CH, SLOT_SZ*MAX_SLOTS, 0666);

    if (shmid == -1) {
    // ShMem not exist - create it

        shmid = shmget (TRACE_CH, SLOT_SZ*MAX_SLOTS, IPC_CREAT|0666);
	if (shmid == -1) {
	    perror ("trace - shmget(2)");
	    return (-1);
	}

	/// set ownership of Sh_Mem to root
	// get Sh_Mem stat
	struct shmid_ds statbuf;

	if (shmctl (shmid, IPC_STAT, &statbuf) == -1) {
	    perror ("trace - shmctl - IPC_STAT");
	    return (-1);
	}

	// change uid to root and reset it
	statbuf.shm_perm.uid = 0;

	if (shmctl (shmid, IPC_SET, &statbuf) == -1) {
	    perror ("trace - shmctl - IPC_SET");
	    return (-1);
	}

	// initialize sema4 to make Trace ShMem available
	stat.val = 1;
	(void) semctl (semid, 0, SETVAL, stat);
    }

    // attach it with appropriate R/W mode
    shm_ptr = shmat (shmid, 0, mode);
    if (shm_ptr == NULL) {
	perror ("trace - shmat(2)");
    }
    return (OK);
}


void
trace_sm::setlock () {
    sembuf stat[1];

    // set lock on ShMem by decrementing sema4
    stat[0].sem_num = 0;
    stat[0].sem_op = -1;
    stat[0].sem_flg = SEM_UNDO;
    (void) semop (semid, stat, 1);
    return;
}


struct sm_slot *
trace_sm::seize ()
{
    // traverse the ShMem and grab the first slot with (pg_name)
    // being NULL (not used)

    int i;
    struct sm_slot *slot_ptr;
    for (i = 0; i < MAX_SLOTS; i++) {
	slot_ptr = (struct sm_slot *) (shm_ptr + i*SLOT_SZ);
	if (slot_ptr->pg_name[0] == '\0') {
	    return (slot_ptr);
	}
    }

    // if all slots are used , return NULL
    return (NULL);
}


void
trace_sm::free (struct sm_slot *ptr)
{
    if (ptr != NULL) {
        // set (pg_name) of the slot to NULL
        ptr->pg_name[0] = '\0';
    }
}


struct sm_slot *
trace_sm::search (char *name, int pid)
{
    // return the address of the slot matching 'name' (AND 'pid' if
    // 'pid' is not 0) or NULL if no match 
    
    int i;
    struct sm_slot *slot_ptr;

    for (i = 0; i < MAX_SLOTS; i++) {

	slot_ptr = (struct sm_slot *) (shm_ptr + i*SLOT_SZ);

	if (strncmp (name, slot_ptr->pg_name, NAME_SZ) == 0) {
	    // return if matched pg name is enough
	    if (pid == 0) {
		return (slot_ptr);
	    }

	    // otherwise check pid also
	    if (pid == slot_ptr->pid) {
		return (slot_ptr);
	    }
	}
    }

    // no match at all
    return (NULL);
}


void 
trace_sm::cleanup (int lim_hr) {

    // free all UNINITIATED activation slots longer than lim_hr
    
    int i;
    struct sm_slot *slot_ptr;

    for (i = 0; i < MAX_SLOTS; i++) {

	slot_ptr = (struct sm_slot *) (shm_ptr + i*SLOT_SZ);

	// get UNINITIATED slot and check its time
	if ((slot_ptr->pg_name[0] != '\0') && (slot_ptr->pid == 0)) {
	    // get current time
	    long ctime = time (0);

	    // get duration time
	    long dtime = slot_ptr->acttime + (lim_hr*3600); 

	    if (dtime < ctime) {
		slot_ptr->pg_name[0] = '\0';
	    }
	}
    }
    return;
}



void
trace_sm::unlock () {
    sembuf stat[1];

    // unlock ShMem by incrementing sema4
    stat[0].sem_num = 0;
    stat[0].sem_op = 1;
    stat[0].sem_flg = SEM_UNDO;
    (void) semop (semid, stat, 1);
    return;
}

char *
trace_sm::base_ptr () {
    return (shm_ptr);
}

void
trace_sm::detach () {
    (void)  shmdt (shm_ptr);
    return;
}


struct sm_slot *
trace_sm::iterate (int code) {
    static cur_ptr = 0;

    if (code == RESET) {
	cur_ptr = 0;
    }

    struct sm_slot *slot_ptr;
    while (cur_ptr < MAX_SLOTS) {
	slot_ptr = (struct sm_slot *) (shm_ptr + cur_ptr*SLOT_SZ);
	++cur_ptr;
	if (slot_ptr->pg_name[0] != '\0') {
	    return (slot_ptr);
	}
    }

    return (NULL);
}

int
trace_sm::get_semid () {
    return (semid);
}


int
trace_sm::get_shmid () {
    return (shmid);
}
