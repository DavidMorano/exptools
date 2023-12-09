
/**************************************************************************/
/* PANELFEATURES Package    Release:  1.0    Release Date: 1/15/89        */
/*                          Provider: J. D. Iorio  (speedy!jdi)           */
/**************************************************************************/
////////////////////////////////////////////////////////////////////
//  PROTO.c
//
//	The functions associated with the modified ostream
//	driver for PANELFEATURES PROTOCOL to the 630 terminal
//
//
//	Copyright (c) AT&T 1988
//
//	History:
//
//	created					9/21/88	jdi
//
//	stripped out stream buffer 		10/27/88 jdi
//	for use with rel 1.4 of the C++ compiler
////////////////////////////////////////////////////////////////////

#include <stream.h>
#include <string.h>
#include "proto.h"
#include "giproto.h"

extern int TERMTYPE;

proto_stream::proto_stream()
{
	char *bp;
	int i;

	pbuf = new char[PBUFSIZE];
	// clear the buffer
	for(bp=pbuf,i=0; i<PBUFSIZE; i++, bp++)
		*bp = '\0';
}
proto_stream::~proto_stream()
{
	flush();
	delete pbuf;
}
proto_stream& proto_stream::operator<<(char *s)
{
	char *bp;
	for(bp=pbuf; *bp!='\0'; bp++);
	strcpy(bp,s);
	for(bp=pbuf; *bp!='\0'; bp++);
	bp--;
	if(*bp == '\n')
		flush();
	return(*this);
}

void proto_stream::put(char c)
{
	for(char *bp=pbuf; *bp!='\0'; bp++);
	*bp=c;
	if(*bp == '\n')
		flush();
}

void proto_stream::flush()
{
	char *bp, *ep;
	char rcvbuf[64];
	int i;

	if(TERMTYPE != ATT630P)
		// normal protocol 
	{
		cout << pbuf;
		cout.flush();
	}
	else
		// wait for echo of NL on each line
	{
		for(bp=pbuf; *bp!='\0'; bp=ep+1)
		{
			for(ep=bp; (*ep!='\n') && (*ep!='\0'); ep++);
			*ep='\0';

			cout << bp;
			cout.put('\n');
			cout.flush();
			cin.get(*rcvbuf);
		}
	}

	// clear the buffer
	for(bp=pbuf,i=0; i<PBUFSIZE; i++, bp++)
		*bp = '\0';
	
}
