#ifndef _File_vec_included
#define _File_vec_included 1

static char File_vech_sccsid[] = "%W%  %G% %U%"; /* %H% %T% */

/*	Copyright (c) 1988 AT&T		All rights reserved.
 *
 *	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T.
 *	The copyright notice above does not evidence any actual
 *	or intended publication of such source code.
*/

/*
*FILE:		File_vec.h
*
*AUTHOR:	Randy Pafford
*
* PERSON
* IN CHARGE:	Glenn Bradford
*
*CONTENTS:	header file for File_vec class
*
*STANDARDS:	C source file Standard-Issue 1.0
*
*CLASS USAGE EXAMPLES:
*
*	struct some_struct {
*		int x;
*		char y[20];
*	}
*	main() 
*	{
*		some_struct foo_in, foo_out;
*
*		foo_out.x = 10;
*		foo_out.y = "some string";
*
*		// open file "afile" with stdio mode "w+"; the 
*		// record size is the length in bytes of some_struct
*
*		File_vec sample("afile", sizeof(foo_in), "w+");
*
*		if (sample.state == _FAIL) // did constructor work?
*			cout << "Open failed: " << sample.bufvalue();
*
*		// with a mode of w+ (truncate or create), size should be zero
*		// numrecs() silently does a flush() to the disk
*		cout << "Number of records in afile = " << sample.numrecs();
*
*		// write foo.out to first record in file; note use of the 
*		// address of foo_out
*		if ((sample[0] = &foo_out) == NULL)  {
*			cout << "failure on write = " << sample.bufvalue();
*			cout << "sample.state = " <<
*
*		// foo_in should now be equal to foo_out
*		if ((&foo_in = sample[0]) == NULL)
*			cout << "failure on read = " << sample.bufvalue();
*
*		// mostly for debugging 
*		cout << "Private state of sample = " << sample;
*		
*		// flushes buffers to disk
*		// returns 0 on success, -1 on failure
*		sample.flush();	
*
*		// move to after the last record currently in file
*		// you can write here, but not read
*		// in this example, we would move to after record 0
*		// returns -1 if failure, otherwise the new current record
*		sample.end();
*
*		// get and put read/write the record from/to the NEXT 
*		// record postion; here the last thing we did was
*		// move to after record 0, so the two puts below will
*		// write to records 1 and 2 respectively. The get
*		// will read from record 3 (which would fail in 
*		// this example since since no record 3 has been 
*		// written yet);
*		// get and put return a ptr to the buffer read/written
*		// or NULL if the operation failed
*		// 
*		sample.put(&foo_out);
*		sample.put(&foo_out);
*		sample.get(&foo_in);
*
*	}	// end main	
*
*NOTES:		The allowable open modes are identical to those of 
*		stdio.h, "w+", "r+", etc. Note that different open
*		modes will start you out at different record postions.
*		
*		I'm not sure why one would want to use get() and put(),
*		we might should make them private member functions.
*
*		The "record type" can be be anything; an int, a struct
*		as in the above example or a character string. Be careful
*		with character strings - if the record size is 50, and 
*		you give it a 10 character string, it will try to read
*		or write a total of 50 characters - it doesn't care
*		about \0 characters.
*
*		If an operation fails, the state variable is set
*		to _FAIL and never reset.  If the user wants to 
*		continue after a failure, he/she might want to
*		set state back to _SUCCESS (state is public).
*/

#include "String.h"
#include "Error_buf.h"

class File_vec : public Error_buf {
	char* filename;
	int rec_size;
	int cur_rec;
	FILE *fptr;
	int last_op;
	int seeked;
	int move(int, int);
public:
	File_vec() : filename(NULL), fptr(NULL) { state = _SUCCESS; }
	File_vec(String&, int, String&);
	~File_vec();
	states init(String&, int, String&);
	int flush();
	int end();
	int numrecs();
	void * put(void *);
	void * get(void *);
	File_vec& operator[](int rec_num);
	friend void * operator=(void *, File_vec&);
	friend void * operator=(File_vec&, void *);
	friend ostream& operator<<(ostream&, File_vec&);
};

#endif
