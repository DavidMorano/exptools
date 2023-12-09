/*ident	"@(#)C++env:incl-master/proto-headers/rand48.h	1.1" */

#ifndef __RAND48_H
#define __RAND48_H


extern "C" {
	double drand48();
	double erand48(unsigned short *);
	long jrand48(unsigned short *);
	long lrand48();
	long mrand48();
	long nrand48(unsigned short *);
	void srand48(long);
	void lcong48(unsigned short *);
	unsigned short *seed48(unsigned short *);
}

#endif
