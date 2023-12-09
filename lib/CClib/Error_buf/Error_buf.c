/*
*FILE:		Error_buf.c
*
*AUTHORS:	Randy Pafford 11/13/87
*
*CONTENTS:	member and friend functions for Error_buf class
*		The following member functions are present:
*		setbuf(int ...) - creates errorbuf of user-specified size
*				  and formats string
*		setbuf(...)	- creates errorbuf of default size and 
*				  and places string in it
*		addbuf(...)	- appends to buffer rather than create 
*				  new one
*		bufvalue()	- returns ptr to errorbuf
*		operator<<()	- output of Error_buf object
*		
*
*STANDARDS:	Issue 1 SDM C coding standards
*/

#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stream.h>

#include "Error_buf.h"

void 
Error_buf::setbuf(int buf_size, char * format ...)
{
	va_list args;

	if (errorbuf != NULL)
		delete errorbuf;	

	errorbuf = new char [buf_size];

	va_start(args, format);

	(void) vsprintf(errorbuf, format, args);

	va_end(args);
	
	return;
}

void
Error_buf::setbuf(char * format ...)
{
	va_list args;

	if (errorbuf != NULL)
		delete errorbuf;	

	errorbuf = new char [MSGLOG_SIZE]; 	// size from prism log.h

	va_start(args, format);

	(void) vsprintf(errorbuf, format, args);

	va_end(args);
	
	return;
}
void
Error_buf::addbuf(char * format ...)
{
	char * eptr;
	va_list args;

	if (errorbuf == NULL) 
		eptr = errorbuf = new char [MSGLOG_SIZE];
	else {
		eptr = errorbuf + strlen(errorbuf);	 // after null
	}

	va_start(args, format);

	(void) vsprintf(eptr, format, args);

	va_end(args);
	
	return;
}

ostream&
operator<<(ostream& s, Error_buf& x)
{
	return s << "errorbuf = " << x.errorbuf;
}

char *
Error_buf::bufvalue()
{
	return errorbuf;
}
