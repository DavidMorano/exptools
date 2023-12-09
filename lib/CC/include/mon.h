/*ident	"@(#)C++env:incl-master/proto-headers/mon.h	1.1" */

#ifndef __MON_H
#define __MON_H


extern "C" {
	void monitor(int (*)(), int(*)(), short *, int, int);
	void monstartup(int (*)(), int (*)());
	void moncontrol(int);
}
#endif
