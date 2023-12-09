/*
*FILE:		File_vec.c
*
*AUTHORS:	Randy Pafford
*
*CONTENTS:	member and friend functions for File_vec class
*
*STANDARDS:	C Source File Standard-Issue 1.0
*
*GENERAL NOTES:	the class is based on stdio, which might have been a 
*		mistake.  For example, with stdio, you can't write
*		and then read without an intervening seek. Since
*		File_vec keeps track of the current record postion,
*		and only seeks when necessary, one must know 
*		when reading if the last operation was a write,
*		and if so perform a seek (and vice-versa).  This is 
*		why the last_op	and seeked flag variables are kept.
*		It might have been better to just take the potential
*		performance penalty and seek on every read/write.
*		If any operation fails the state is set to _FAIL, 
*		and never cleared.
*
*POSSIBLE ENHANCEMENTS:
*		Some of the member functions, especially the 
*		overloaded operators, should be moved inline.
*
*		I would like to add an additional open mode
*		- which the UNIX open(2) has but stdio fopen(3) lacks - 
*		having the semantics if the file exists, use it for update,
*		if doesn't exist, create it for update.
*
*		I'm not sure put() and get() should be public
*/

#include "File_vec.h"
#include <stream.h>
#include <memory.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

enum flags { YES, NO, BAD_SEEK, NO_OP, READ, WRITE };
/*
*FUNCTION:	File_vec
*
*PURPOSE:	Constructor 
*
*SIDE EFFECTS:	Sets filename, rec_size, fptr, and cur_rec, and state
*
*DESCRIPTION:	Opens file, error checks, and sets private variables
*/

File_vec::File_vec(String& pathname, int size, String& mode) :
filename(NULL), fptr(NULL)
{
	state = init(pathname,size,mode);
}

/*
*FUNCTION:	~File_vec
*
*PURPOSE:	destructor 
*
*DESCRIPTION:	Closes file and deletes free store for filename
*/

File_vec::~File_vec()
{
	fclose(fptr);
	delete filename;
}

/*
*FUNCTION:	init
*
*PURPOSE:	Guts of the constructor with the same arguments.
*			Should be used publicly in place of the constructor in
*			places where you need to extend the scope of the object.
*			Ex.
*
*			File_vec fvec;
*			if (file_exists()) {
*				fvec.init(file,...);
*			}
*			else {
*				func1(file,...);	//  func1 creates the file fvec opens
*				fvec.init(file,...);
*			}
*			// fvec remains in scope here, instead of in 'if' or 'else' block
*
*OUTPUT:	_SUCCESS or _FAIL
*
*SIDE EFFECTS:	Sets filename, rec_size, fptr, and cur_rec, and state
*
*DESCRIPTION:	Opens file, error checks, and sets private variables
*/

states File_vec::init(String& pathname, int size, String& mode)
{
	states ret;

	if (fptr != NULL) { fclose(fptr); }
	if (filename != NULL) { delete filename; }

	rec_size = size;

	filename = new char[pathname.length() + 1];
	pathname.dump(filename);

	char* open_mode = new char[mode.length() + 1];
	mode.dump(open_mode);

	if ((fptr = fopen(filename, open_mode)) != NULL) {
		ret = _SUCCESS;
		cur_rec = ftell(fptr) / rec_size;
	}
	else {
		ret = _FAIL;
		addbuf("File_vec - errno %d on fopen of %s", errno, filename);
	}
	delete open_mode;
	last_op = NO_OP;
	return ret;
}
/*
*FUNCTION:	flush
*
*PURPOSE:	forces write of any data in buffers to disk
*
*RETURN VALUE:	-1 if error, 0 otherwise
*
*SIDE EFFECTS:	sets state 
*
*DESCRIPTION:	flush buffers and check for errors
*/

int
File_vec::flush()
{
	if (fflush(fptr) != 0) {
		addbuf("File_vec - errno %d on fflush of %s", errno, filename);
		state = _FAIL;
		return -1;
	}
	return 0;
}

/*
*FUNCTION:	end
*
*PURPOSE:	move to end of file 
*
*RETURN VALUE:	-1 if error, record number otherwise
*
*SIDE EFFECTS: 	sets cur_rec
*
*DESCRIPTION:	Move to end of file; set cur_rec and return that value
*/

int
File_vec::end()
{
	if (move(0, 2) == -1)
		return -1;
	else {
		cur_rec = ftell(fptr) / rec_size;
		return cur_rec;
	}
}

/*
*FUNCTION:	put
*
*PURPOSE:	writes record to current position in file
*
*PRECONDITIONS:	constructor must have been invoked with write mode
*
*RETURN VALUE:	returns ptr to input buffer if success, NULL otherwise
*
*SIDE EFFECTS:	sets cur_rec
*
*DESCRIPTION:	check to see if we should seek, fwrite to file, 
*		and check for errors.  If no error,
*		update cur_rec
*/

void *
File_vec::put(void * buffer)
{
	if (last_op == READ && seeked == NO)
		if (move(0,1) == -1) 
			return NULL;

	if (fwrite((char *) buffer, rec_size, 1, fptr) == 1) {
		last_op = WRITE;
		cur_rec++;
		return buffer;
	}
	else {
		state = _FAIL;
		addbuf("File_vec - errno %d on fwrite to record %d in %s", 
				errno, cur_rec, filename);
		return NULL;
	}
}


/*
*FUNCTION:	get
*
*PURPOSE:	reads record from current position in file
*
*PRECONDITIONS:	constructor must have been invoked with read mode
*
*RETURN VALUE:	returns ptr to input buffer if success, NULL otherwise
*
*SIDE EFFECTS:	sets cur_rec
*
*DESCRIPTION:	check to see if we should seek, fread file, 
*		checking for errors; if success update cur_rec
*/

void *
File_vec::get(void * buffer)
{
	if (last_op == WRITE && seeked == NO) 
		if (move(0,1) == -1) 
			return NULL;

	if (fread((char *) buffer, rec_size, 1, fptr) == 1) {
		last_op = READ;
		cur_rec++;
		return buffer;
	}
	else {
		state = _FAIL;
		addbuf("File_vec - errno %d on fread of record %d in %s", 
				errno, cur_rec, filename);
		return NULL;
	}
}
	

/*
*FUNCTION:	operator[]
*
*PURPOSE:	moves to a specific record number
*
*RETURN VALUE:	*this ptr, for operator= functions
*
*SIDE EFFECTS:	Sets cur_rec
*
*DESCRIPTION:	Moves to specified record number 
*/

File_vec&
File_vec::operator[](int rec_num)
{
	if (cur_rec == rec_num)
		seeked = NO;
	else {
		if (move(rec_num * rec_size, 0) == -1)
			seeked = BAD_SEEK;
		else {
			seeked = YES;
			cur_rec = rec_num;
		}
	}
	return *this;
}

/*
*FUNCTION:	operator<<
*
*PURPOSE:	prints out object on a stream
*
*RETURN VALUE:	ptr to stream for other <<
*
*DESCRIPTION:	outputs string representation on stream s
*/

ostream&
operator<<(ostream& s, File_vec& x)
{
	Error_buf temp = (Error_buf &) x;
	s << "Error_buf = " << temp;
	return s << "\nfilename = " << x.filename <<
		    "\nrec_size = " << x.rec_size << 
		    "\ncur_rec = " << x.cur_rec <<
		    "\nseeked = " << x.seeked <<
		    "\nlast_op = " << x.last_op;
}

/*
*FUNCTION:	operator=(buffer, File_vec)
*
*PURPOSE:	reads record from file and stores in buffer
*
*RETURN VALUE:	return value from get
*
*DESCRIPTION:	invoke get
*/

void *
operator=(void * buffer, File_vec&  x)
{
	if (x.seeked == BAD_SEEK)
		return NULL;
	else 
		return x.get(buffer);
}

/*
*FUNCTION:	operator=(File_vec, buffer)
*
*PURPOSE:	write buffer to file
*
*RETURN VALUE:	return value from put
*
*DESCRIPTION:	invoke put
*/

void *
operator=(File_vec& x, void * buffer)
{
	if (x.seeked  == BAD_SEEK)
		return NULL;
	else 
		return x.put(buffer);
}

/*
*FUNCTION:	numrecs
*
*PURPOSE:	return number of records in file
*
*RETURN VALUE:	number of records in file, -1 if error
*
*SIDE EFFECTS:	sets state
*
*DESCRIPTION:	flush buffer, stat to get number of bytes in file, 
*		then divide by 	rec_size to compute number of records.
*/

int
File_vec::numrecs()
{
	struct stat buf;
	
	/*
	*	must flush as fstat is a system call and doesn't know about
	* 	data sitting in stdio buffers
	*/
	if (flush() == -1)
		return -1;

	if (fstat(fileno(fptr), &buf) == 0)
		return buf.st_size / rec_size;
	else {
		state = _FAIL;
		addbuf("File_vec - errno %d on fstat of %s", errno, filename);
		return -1;
	}
}

/*
*FUNCTION:	move
*
*PURPOSE:	perform seek and error check
*
*RETURN VALUE:	0 if success, -1 if error
*
*SIDE EFFECTS:	sets state
*
*DESCRIPTION:	performs fseek and error checks
*/

int
File_vec::move(int offset, int flag)
{
	if (fseek(fptr, offset, flag) != 0) {
		addbuf("File_vec - errno %d on fseek to record %d in file %s", 
			errno, offset / rec_size, filename);
		state = _FAIL;
		return -1;
	}
	return 0;
}
