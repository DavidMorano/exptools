#ifndef _Error_buf_included
#define _Error_buf_included 1

/* Version 1.0 */

/*
*FILE:		Error_buf.h
*
*AUTHORS:	Randy Pafford 11/13/87
*			now owned by Glenn Bradford
*
*CONTENTS:	class definition for Error_buf class
*
*STANDARDS:	Issue 1 SDM C coding standards
*
*CLASS USAGE:	
*
*	main() {
*		Error_buf x;
*		x.setbuf("Error string using default buffer size - errno %d", 
*			errno);
*		x.setbuf(100, "Specify size = 100, above string overwritten");
*		x.addbuf("\nAppend this %s to buffer", "message");
*		printf("\nBuffer value = %s", x.bufvalue());
*		cout << x;	// prints out data members of x, labeled
*		exit(0);
*	}
*
*	or used as a base class (its main purpose in life)
*	
*	class foo : public Error_buf {
*		int x;
*	public:
*		foo(int y);
*	}
*
*	foo::foo(int y)
*	{
*		if (y > MAXY) 
*			setbuf("Class foo constructor - y = %d too big", y);
*	}
*
*
*/

#include <stream.h>

const int MSGLOG_SIZE = 990;

enum states { _SUCCESS, _FAIL };

class Error_buf {
	char * errorbuf;
public:
	Error_buf() { errorbuf = NULL; }
	~Error_buf() { if (errorbuf != NULL) delete errorbuf; }
	void setbuf(int, char * ...);
	void setbuf(char * ...);
	void addbuf(char * ...);
	char * bufvalue();
	friend ostream& operator<<(ostream&, Error_buf&);
	states state;
};

#endif
