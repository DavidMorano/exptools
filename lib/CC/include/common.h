/*ident	"@(#)C++env:incl-master/const-headers/common.h	1.1" */
/**************************************************************************
			Copyright (c) 1984 AT&T
	  		  All Rights Reserved  	

	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T
	
	The copyright notice above does not evidence any   	
	actual or intended publication of such source code.

*****************************************************************************/

#ifndef COMMONH
#define COMMONH

class istream;
class ostream;

struct common {
	virtual int	cmp(common& oo) { return this==&oo; }
		/* cmp performs a three way comparison if an ordering exists:
			this==arg: return 0,
			this<arg:  return negative,
			this>arg:  return positive
		   otherwise
			this==arg: return 0,
			this!=arg: return non-zero
		*/
	virtual int operator==(common& oo) { return this==&oo; }
	virtual char*	swho() { return 0; }
	virtual int	iwho() { return 0; }
	virtual int	size() { return sizeof(common); }
	virtual ostream&	write(ostream& s) { return s;}
	virtual istream&	read(istream& s) { return s; }
		common() {}
};

#endif
