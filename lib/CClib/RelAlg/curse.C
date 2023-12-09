#ident "@(#) /sable/sdb/ra/sblib/curse/s.curse.C"
/*        Copyright (c) 1989, 1990, 1991 AT&T All Rights Reserved */

#include <sblib.h>
unsigned Curse::nobjects = 0;

/*  Initialize array of signals we are interested in trapping.   */
/*  Note that it is 0 terminated.                                */
int Curse::signalsToBeTrapped[NSIG] = { SIGHUP, SIGINT, SIGQUIT, SIGILL,
                                        SIGTRAP, SIGIOT, SIGEMT, SIGFPE,
                                        SIGBUS, SIGSEGV, SIGSYS, SIGPIPE,
                                        SIGALRM, SIGTERM, SIGUSR1, SIGUSR2,
                                        0
                                       };

void Curse::trap(int signo)
{
register SIG_PF oldtrap = traps[signo];
/* C++ complains if this is a switch statement */
if ( (oldtrap==SIG_ERR) || (oldtrap==SIG_DFL) )
   { endwin(); cerr<<"\nSignal "<<signo<<" received.\n"; exit(signo); }
else if ( (oldtrap!=SIG_HOLD) && (oldtrap!=SIG_IGN) )
   { endwin(); (*oldtrap)(signo); init_screen(); /* an old trap */ }
(void) sigset(signo,&Curse::trap);
}

Curse::Curse()
{
if ( !(nobjects++) )
   {
   init_screen();
   for ( int i=0; signalsToBeTrapped[i]; i++ )
      traps[signalsToBeTrapped[i]] = sigset(signalsToBeTrapped[i],&Curse::trap);
   }
}

Curse::~Curse()
{
if ( !(--nobjects) )
   {
   for ( int i=0; i < NSIG; i++ )
      (void) sigset(i,traps[i]);
   endwin();
   }
}
