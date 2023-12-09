
/**************************************************************************/
/* PANELFEATURES Package    Release:  1.0    Release Date: 1/15/89        */
/*                          Provider: J. D. Iorio  (speedy!jdi)           */
/**************************************************************************/

// PANELFEATURE.C
//
//	Copyright (C) ATT 1987
//
// This source file defines the operations to the panel features
// that will be used to define an instrument for ALMMS
//
//   History:
//	J. D. Iorio	12/2/87		created
//


#include <stream.h>
#include <string.h>

#include "pf.h"


//////////////////////////////////////////////////////////////////////////////
panelfeature::panelfeature(char *Name, int X, int Y, int xSize, int ySize,
		     int(*func)(panelfeature *))		// constructor
{
	// store the name of the entity
	name = new char[strlen(Name)+1];
	strcpy(name,Name);
	officialname = new char[strlen(Name)+1];
	strcpy(officialname,Name);

	// store plot info
	xloc = X;
	yloc = Y;
	xsize = xSize;
	ysize = ySize;

	// initialize parameters for generic panelfeature;
	maxnumvalues = 1;
	numvalues = 1;
	lastfilled = numvalues;
	lastread = numvalues;
	intflag = FALSE;
	value = new float;
	*value = 0;
	attrib = 0;

	// set-up the handler function for this panelfeature;
	handler = func;
	
	// set-up parent linkage
	parent = (panelfeature *) NULL;
	this_module = NULL;

	// set up the graphics window
	updateflag = MAJOR;
}

//////////////////////////////////////////////////////////////////////////////
panelfeature::~panelfeature()					// destructor
{
	delete name;
	delete officialname;
	delete value;
}

//////////////////////////////////////////////////////////////////////////////
////  THIS IS A KLUDGE - PLEASE TAKE NOTE of the following function:
////  I am trying to call a function via a pointer to the function.
////  Under normal conditions, this poses no problem with arguments,
////  but when the function is a member of a C++ class, there is an
////  implied this pointer inserted on the stack which I cannot supply
////  because the compiler would object.  The execution of the code would
////  skew the arguments and fail if the THIS pointer was not supplied.
////  Here I have type cast the function pointer to a new type which takes
////  an extra argument of type this (panelfeature *) in this case and have
////  supplied the desired value...

int (*kludge)(panelfeature *, panelfeature *);
//////////////////////////////////////////////////////////////////////////////
void panelfeature::dofunc(panelfeature *t)
{
	if (t->handler == NULLFUNC)
		return;
	
	kludge = (int (*)(panelfeature *, panelfeature *)) t->handler;

	if ((*(kludge))(t,t) != 0)
	{
	    errormsg(form("Handler function for pannelfeature %s failed",
					t->getname()));
	}
}
//////////////////////////////////////////////////////////////////////////////
////  END OF KLUDGE
//////////////////////////////////////////////////////////////////////////////

void panelfeature::doallfunc(panelfeature *t)
{

	panelfeature *nx;

	dofunc(t);

	if ((nx = t->getparent()) != NULL)
		nx->doallfunc(nx);
}

//////////////////////////////////////////////////////////////////////////////
int panelfeature::parentY()
{
	panelfeature *next;
	int y;

	for (y=0, next=getparent(); next != NULL; next = (*next).getparent())
	{
		y += next->yloc;
	}
	return(y);
}
int panelfeature::parentX()
{
	panelfeature *next;
	int x;

	for (x=0, next=getparent(); next != NULL; next = (*next).getparent())
	{
		x += next->xloc;
	}
	return(x);
}
//////////////////////////////////////////////////////////////////////////////
char * panelfeature::getpath()
{
    // build a new string of all panel names "name!name!name!"
    // ommiting the root and terminating with a '!'

	static char str[128];
	char *np, *sp;
	char *lname;
	panelfeature *p;
	int i;

	sp = &str[127];
	*sp = '\0';
	for(p=getparent(); p != NULL; p=p->getparent())
	{
		if((p->ispanel()) && (p->getparent() != NULL))
		{
			sp--;
			*sp = '!';
			lname = p->getname();
			for (i=0,np=lname; *np!='\0'; i++,np++);
			for (  ; i>0; i--)
			{
				np--;
				sp--;
				*sp=*np;
			}
			
		}
	}
	return(sp);
	
	
}
//////////////////////////////////////////////////////////////////////////////
panelfeature& panelfeature::operator<<(float *f)
{

	// fill the array, assume that f[] is correct size
	for(int i=0; i<numvalues; i++)
	{
		if (intflag == TRUE)
			value[i] = (float)((int)f[i]);
		else
			value[i] = f[i];

	}
	// mark that all elements filled
	lastfilled = numvalues;

	// call the action function when assignment is done
	doallfunc(this);

	updateflag = VALUE_CHANGE;
	return(*this);
}
panelfeature& panelfeature::operator<<(float f) 
{

	// fill the next array element
	if (lastfilled == numvalues)
		lastfilled = 0;
	if (intflag == TRUE)
		value[lastfilled] = (float)((int)f);
	else
		value[lastfilled] = f;

	lastfilled++;

	// call the action function when assignment is done
	doallfunc(this);

	updateflag = VALUE_CHANGE;
	return(*this);
}
panelfeature& panelfeature::operator<<(int i) 
{
	float f=(float) i;
	return(*this << f);
}
panelfeature& panelfeature::operator<<(int *i) 
{
	float *v = new float[numvalues];
	for (int j=0; j<numvalues; j++)
		v[j] = i[j];
	*this << v;
	delete v;
	return(*this);
}
//////////////////////////////////////////////////////////////////////////////
panelfeature& panelfeature::operator>>(float *f)
{
	// read all the values, assume the proper array length
	for (int i=0; i<numvalues; i++)
		f[i] = value[i];
	lastread = numvalues;
	return(*this);
}

panelfeature& panelfeature::operator>>(float& f)
{
	// read the next array element
	if (lastread == numvalues)
		lastread = 0;

	f = value[lastread];
	lastread++;
	return(*this);
}
panelfeature& panelfeature::operator>>(int& i)
{
	float f;

	*this >> f;
	i=(int)f;
	return(*this);
}
panelfeature& panelfeature::operator>>(int *i)
{
	float *v = new float[numvalues];

	*this >> v;

	for (int j=0; j<numvalues; j++)
		i[j] = (int)v[j];
	delete v;
	return(*this);
}

    // define this << after >> is defined
panelfeature& panelfeature::operator<<(panelfeature *p)
{
	if (numvalues <= (*p).numvalues)
	// if source is equal or bigger than destination
	{
		// assign as many as you can
		float *v = new float[(*p).numvalues];
		(*p) >> v;
		*this << v; 
		delete v;
		return(*this); 
	}
	else
	{
	// source is smaller then destination
		// assign one value

		float t;
		(*p) >> t;
		*this << t; 
		
	    return(*this);
	}
}
panelfeature& panelfeature::operator<<(panelfeature p)
			{ return ( (*this) << (&p) ); }

    // ... again a sequencing thing
panelfeature& panelfeature::operator>>(panelfeature& p)
			{ p << this; return(*this); }
panelfeature& panelfeature::operator>>(panelfeature *p)
			{ *p << this; return(*this); }

void panelfeature::setintflag(int flg)
{
	intflag = flg;
	if(intflag == TRUE)
	{
		for(int i=0; i<numvalues; i++)
			value[i] = (float)(int)value[i];
	}
}

void *panelfeature::get_this_module()
{
	return( this_module);
}

void panelfeature::set_this_module(void *ins)
{
	this_module = ins;
}
