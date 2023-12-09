
/**********************************************************************
LIBRARY: trace

AUTHOR: Kim Tran
VERSION: 1

CLASS: trace_sm

TITLE: Trace facility shared memory

DESCRIPTION:
    manages the shared memory space for Trace facility which is 
    organized as an array of struct (sm_slot). The functions include
    shared memory attachment for target programs and shared memory
    update for Trace controls.

PUBLIC:
    setlock
        set the exclusive lock on the Trace shared memory segment	
    attach
	attaches the ShMem to a process with appropriate r/w mode
    seize
	reserves a free slot for use
    free
	frees a slot
    search
	searches the array for a particular slot 
    base_ptr
	returns the base adress of ShMem
    unlock
	remove the exclusive lock
    detach
	detach ShMem from the process
    cleanup
	make uninitiated slots free for reuse
    get_semid
	returns semid
    get_shmid
	returns shmid

PRIVATE:
    shm_ptr
	pointer to the allocated shared memory
    semid
	id of semaphore associated with ShMem
    shmid
	id of ShmMem associated with Trace facility

**********************************************************************/

#ifndef TRACE_SM_H
#define TRACE_SM_H

class trace_sm {
public:
    trace_sm ();

    void setlock ();
    int attach (int mode=0);
    struct sm_slot *seize ();
    void free (struct sm_slot *ptr);
    struct sm_slot *search (char *name, int pid = 0);
    char *base_ptr ();
    void unlock ();
    void detach ();
    void cleanup (int hour);
    struct sm_slot *iterate (int code=CONT);
    int get_semid ();
    int get_shmid ();
private:
    char *shm_ptr;
    int semid;
    int shmid;
};

#endif
