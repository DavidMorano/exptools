
/**************************************************************************/
/* PANELFEATURES Package    Release:  1.0    Release Date: 1/15/89        */
/*                          Provider: J. D. Iorio  (speedy!jdi)           */
/**************************************************************************/

// KNOBTYPES.C
//
//	Copyright (C) ATT 1987
//
// This header file defines the types of knobs derived from the
// generic knob class
// that will be used to define instruments for ALMMS
//
//   History:
//	J. D. Iorio	12/8/87		created
//

#include "pf.h"

///////////////////////////////////////////////////////////////////////////////
//class FLTknob : public knob		// FLOATING POINT SINGLE KNOB

		// constructors
FLTknob::FLTknob(char *Name, char *slab, float Hi, float Lo, float Dflt,
			int(*func)(panelfeature *)) :
		(Name, 0, 0, SLIDE, slab, Hi, Lo, Dflt, func ,1)
{
	// generic knob is like a FLT KNOB
}

		// destructor
FLTknob::~FLTknob()
{
	// generic knob is like a FLT KNOB
}

///////////////////////////////////////////////////////////////////////////////
//class FWFLTknob : public knob		// FIXED WIDTH FLT POINT ARRAY KNOB

		// constructors
FWFLTknob::FWFLTknob(char *Name, char *slab, float Hi, float Lo, float Dflt,
			int(*func)(panelfeature *), int Width) :
		(Name, 0, 0, SLIDE, slab, Hi, Lo, Dflt, func, Width )
{
}


		// destructor
FWFLTknob::~FWFLTknob()
{
}

///////////////////////////////////////////////////////////////////////////////
//class VWFLTknob : public knob		// VARIABLE WIDTH FLT POINT ARRAY KNOB

		// constructors
VWFLTknob::VWFLTknob(char *Name, char *slab, float Hi, float Lo, float Dflt,
			int(*func)(panelfeature *), int Width,int Maxwidth) :
		(Name, 0, 0, SLIDE, slab, Hi, Lo, Dflt, func, Maxwidth )
{
	changesize(Width);
}


		// destructor
VWFLTknob::~VWFLTknob()
{
}
///////////////////////////////////////////////////////////////////////////////
//class INTknob : public knob		// INTEGER SINGLE KNOB

		// constructors
INTknob::INTknob(char *Name, char *slab, int Hi, int Lo, int Dflt,
			int(*func)(panelfeature *)) :
		(Name, 0, 0, SLIDE, slab, (float)Hi, (float)Lo,
				 (float)Dflt, func, 1)
{
	setintflag(TRUE);
	changefmt("%-8.0f");
}


		// destructor
INTknob::~INTknob() 
{
}
///////////////////////////////////////////////////////////////////////////////
//class FWINTknob : public knob		// FIXED WIDTH INTEGER ARRAY KNOB

		// constructors
FWINTknob::FWINTknob(char *Name, char *slab, int Hi, int Lo, int Dflt,
			int(*func)(panelfeature *), int Width) :
		(Name, 0, 0, SLIDE, slab, (float)Hi, (float)Lo, (float)Dflt,
				 func, Width)
{
	setintflag(TRUE);
	changefmt("%-8.0f");
}


		// destructor
FWINTknob::~FWINTknob()
{
}
///////////////////////////////////////////////////////////////////////////////
//class VWINTknob : public knob		// VARIABLE WIDTH INTEGER ARRAY KNOB

		// constructors
VWINTknob::VWINTknob(char *Name, char *slab, int Hi, int Lo, int Dflt,
			int(*func)(panelfeature *),int Width,int Maxwidth) :
		(Name, 0, 0, SLIDE, slab, (float)Hi, (float)Lo, (float)Dflt,
				 func, Maxwidth )
{
	setintflag(TRUE);
	changesize(Width);
	changefmt("%-8.0f");
}


		// destructor
VWINTknob::~VWINTknob()
{
}
///////////////////////////////////////////////////////////////////////////////
//class ENUMknob : public knob		// SINGLE ENUM KNOB

		// constructors
ENUMknob::ENUMknob(char *Name, int Numvals, char *Labels[], int *Vals, int Dflt,
			int(*func)(panelfeature *)) :
		(Name, 0, 0, SLIDE, " ", (float)(Numvals-1), 0.0, (float)Dflt,
			 func, 1)
{
	char *newfmt;
	int maxfmt = 0;
	int thisfmt;

	setintflag(TRUE);

	vals = new int[Numvals];		// allocate storage
	labels = new char *[Numvals];
	numvals = Numvals;

	for (int i=0; i<numvals; i++)
	{
		vals[i] = Vals[i];		// copy values into knob
		thisfmt = strlen(Labels[i])+1;
		labels[i] = new char[thisfmt];
		strcpy(labels[i], Labels[i]);
		maxfmt = (thisfmt > maxfmt) ? thisfmt : maxfmt;
	}

	// set the format to %Ns where N is the longest label size
	newfmt = form("%%-%ds",maxfmt);
	changefmt(newfmt);
	// now go back and fix the default value
	changesize(1);
}


		// destructor
ENUMknob::~ENUMknob()
{
	for (int i=0; i<numvals; i++)
		delete labels[i];

	delete labels;
	delete vals;

}

float ENUMknob::value_of(float x)
{
	for (int i=0; i<numvals; i++)
		if (x == vals[i])
			break;
	return((float)i);
	
}

float ENUMknob::value_for(float x)
{
	return(vals[(int)x]);
}

char *ENUMknob::getlabel(float v)
{
	return (form(getfmt(),labels[(int)v]));
}
