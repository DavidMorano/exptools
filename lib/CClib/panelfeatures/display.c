
/**************************************************************************/
/* PANELFEATURES Package    Release:  1.0    Release Date: 1/15/89        */
/*                          Provider: J. D. Iorio  (speedy!jdi)           */
/**************************************************************************/

// DISPLAY.C
//
//	Copyright (C) ATT 1987
//
// This header file defines the operations of the derived class of
// panelfeatures called displays
// that will be used to define an instrument for ALMMS
//
//   History:
//	J. D. Iorio	12/10/87		created
//

#include "pf.h"


//////////////////////////////////////////////////////////////////
    // 1 dimension
display::display(char *Name, char *Xname, char *Xslab,
		 float Xmin, float Xmax, int Maxsize)
		:(Name, 0, 0, Disp1Width, DispHeight(Maxsize), NULLFUNC)
		{initdisplay((int) 1, Xname, Xslab, Xmin, Xmax, DFMT,
			 NOAXIS, NOAXIS, Maxsize);}

display::display(char *Name, knob& Xknob, int Maxsize)
		:(Name, 0, 0, Disp1Width, DispHeight(Maxsize), NULLFUNC)
			{initdisplay((int) 1,
			      Xknob.name, Xknob.scalelabel,
				 Xknob.highlimit, Xknob.lowlimit, Xknob.format,
				 NOAXIS, NOAXIS, Maxsize);}

    // 2 dimension
display::display(char *Name, char *Xname, char *Xslab, float Xmin, float Xmax,
		 char *Yname, char *Yslab, float Ymin, float Ymax, int Maxsize)
		:(Name, 0, 0, Disp2Width, DispHeight(Maxsize), NULLFUNC)
			{initdisplay((int) 2, Xname, Xslab, Xmin,Xmax, DFMT,
			      Yname, Yslab, Ymin, Ymax, "%-8.2f",
				 NOAXIS, Maxsize);}

display::display(char *Name, knob& Xknob,
		 char *Yname, char* Yslab, float Ymin, float Ymax, int Maxsize)
		:(Name, 0, 0, Disp2Width, DispHeight(Maxsize), NULLFUNC)
			{initdisplay((int) 2,
			      Xknob.name, Xknob.scalelabel,
				 Xknob.highlimit, Xknob.lowlimit, Xknob.format,
			      Yname, Yslab, Ymin, Ymax, DFMT,
				 NOAXIS, Maxsize);}

display::display(char *Name, char *Xname, char *Xslab, float Xmin, float Xmax,
		 knob& Yknob, int Maxsize)
		:(Name, 0, 0, Disp2Width, DispHeight(Maxsize), NULLFUNC)
			{initdisplay((int) 2,
			      Xname, Xslab, Xmin, Xmax, DFMT,
			      Yknob.name, Yknob.scalelabel,
				 Yknob.highlimit, Yknob.lowlimit, Yknob.format,
		 		NOAXIS, Maxsize);}

display::display(char *Name, knob& Xknob, knob& Yknob, int Maxsize)
		:(Name, 0, 0, Disp2Width, DispHeight(Maxsize), NULLFUNC)
			{initdisplay((int) 2,
			      Xknob.name, Xknob.scalelabel,
				 Xknob.highlimit, Xknob.lowlimit, Xknob.format,
			      Yknob.name, Yknob.scalelabel,
				 Yknob.highlimit, Yknob.lowlimit, Yknob.format,
				 NOAXIS, Maxsize);}

    // 3 dimension
display::display(char *Name, char *Xname, char *Xslab, float Xmin, float Xmax,
		 char *Yname, char *Yslab, float Ymin, float Ymax,
		 char *Zname, char *Zslab, float Zmin, float Zmax, int Maxsize)
			:(Name, 0, 0, Disp3Width, DispHeight(Maxsize), NULLFUNC)
		{initdisplay((int) 3,
			      Xname, Xslab, Xmin, Xmax, DFMT,
			      Yname, Yslab, Ymin, Ymax, DFMT,
			      Zname, Zslab, Zmin, Zmax, DFMT,
				 Maxsize);}

display::display(char *Name, knob& Xknob,
		 char *Yname, char *Yslab, float Ymin, float Ymax,
		 char *Zname, char *Zslab, float Zmin, float Zmax, int Maxsize)
		:(Name, 0, 0, Disp3Width, DispHeight(Maxsize), NULLFUNC)
			{initdisplay((int) 3,
			      Xknob.name, Xknob.scalelabel,
				 Xknob.highlimit, Xknob.lowlimit, Xknob.format,
			      Yname, Yslab, Ymin, Ymax, DFMT,
			      Zname, Zslab, Zmin, Zmax, DFMT,
			      Maxsize); }

display::display(char *Name, char *Xname, char *Xslab, float Xmin, float Xmax,
		 knob& Yknob,
		 char *Zname, char *Zslab, float Zmin, float Zmax, int Maxsize)
		:(Name, 0, 0, Disp3Width, DispHeight(Maxsize), NULLFUNC)
			{initdisplay((int) 3,
			      Xname, Xslab, Xmin, Xmax, DFMT,
			      Yknob.name, Yknob.scalelabel,
				 Yknob.highlimit, Yknob.lowlimit, Yknob.format,
			      Zname, Zslab, Zmin, Zmax, DFMT,
			      Maxsize); }

display::display(char *Name, knob& Xknob,
		 knob& Yknob,
		 char *Zname, char *Zslab, float Zmin, float Zmax, int Maxsize)
		:(Name, 0, 0, Disp3Width, DispHeight(Maxsize), NULLFUNC)
			{initdisplay((int) 3,
			      Xknob.name, Xknob.scalelabel,
				 Xknob.highlimit, Xknob.lowlimit, Xknob.format,
			      Yknob.name, Yknob.scalelabel,
				 Yknob.highlimit, Yknob.lowlimit, Yknob.format,
			      Zname, Zslab, Zmin, Zmax, DFMT,
			      Maxsize); }

display::display(char *Name, char *Xname, char *Xslab, float Xmin, float Xmax,
		 char *Yname, char *Yslab, float Ymin, float Ymax,
		 knob& Zknob, int Maxsize)
		:(Name, 0, 0, Disp3Width, DispHeight(Maxsize), NULLFUNC)
			{initdisplay((int) 3,
			      Xname, Xslab, Xmin, Xmax, DFMT,
			      Yname, Yslab, Ymin, Ymax, DFMT,
			      Zknob.name, Zknob.scalelabel,
				 Zknob.highlimit, Zknob.lowlimit, Zknob.format,
			      Maxsize); }

display::display(char *Name, knob& Xknob,
		 char *Yname, char *Yslab, float Ymin, float Ymax,
		 knob& Zknob, int Maxsize)
		:(Name, 0, 0, Disp3Width, DispHeight(Maxsize), NULLFUNC)
			{initdisplay((int) 3,
			      Xknob.name, Xknob.scalelabel,
				 Xknob.highlimit, Xknob.lowlimit, Xknob.format,
			      Yname, Yslab, Ymin, Ymax, DFMT,
			      Zknob.name, Zknob.scalelabel,
				 Zknob.highlimit, Zknob.lowlimit, Zknob.format,
			      Maxsize); }

display::display(char *Name, char *Xname, char *Xslab, float Xmin, float Xmax,
		 knob& Yknob,
		 knob& Zknob, int Maxsize)
		:(Name, 0, 0, Disp3Width, DispHeight(Maxsize), NULLFUNC)
			{initdisplay((int) 3,
			      Xname, Xslab, Xmin, Xmax, DFMT,
			      Yknob.name, Yknob.scalelabel,
				 Yknob.highlimit, Yknob.lowlimit, Yknob.format,
			      Zknob.name, Zknob.scalelabel,
				 Zknob.highlimit, Zknob.lowlimit, Zknob.format,
			      Maxsize); }

display::display(char *Name, knob& Xknob,
		 knob& Yknob,
		 knob& Zknob, int Maxsize)
		:(Name, 0, 0, Disp3Width, DispHeight(Maxsize), NULLFUNC)
			{initdisplay((int) 3,
			      Xknob.name, Xknob.scalelabel,
				 Xknob.highlimit, Xknob.lowlimit, Xknob.format,
			      Yknob.name, Yknob.scalelabel,
				 Yknob.highlimit, Yknob.lowlimit, Yknob.format,
			      Zknob.name, Zknob.scalelabel,
				 Zknob.highlimit, Zknob.lowlimit, Zknob.format,
			      Maxsize); }

//////////////////////////////////////////////////////////////////////
void display::initdisplay(int Dim, char *Xname, char *Xslab,
					 float Xmin, float Xmax, char *Xfmt,
				char *Yname, char *Yslab,
					 float Ymin, float Ymax, char *Yfmt,
				char *Zname, char *Zslab,
					 float Zmin, float Zmax, char *Zfmt,
				 int Maxsize)
{
    // set up data storage area
	numdimensions = Dim;
	maxdata = Maxsize;

	ddata = new float *[numdimensions];
	dlabels = new char *[numdimensions];
	dscalelabels = new char *[numdimensions];
	format = new char *[numdimensions];
	min = new float[numdimensions];
	max = new float[numdimensions];
	
	for (int i=0; i< numdimensions; i++)
	{
		ddata[i] = new float[maxdata];
	}

    // set up axes information
	dlabels[0] = new char[strlen(Xname)+1];
	strcpy(dlabels[0], Xname);
	dscalelabels[0] = new char[strlen(Xslab)+1];
	strcpy(dscalelabels[0], Xslab);
	min[0] = Xmin;
	max[0] = Xmax;
	format[0] = new char[strlen(Xfmt)+1];
	strcpy(format[0], Xfmt);

	if (numdimensions > 1)
	{
		dlabels[1] = new char[strlen(Yname)+1];
		strcpy(dlabels[1], Yname);
		dscalelabels[1] = new char[strlen(Yslab)+1];
		strcpy(dscalelabels[1], Yslab);
		min[1] = Ymin;
		max[1] = Ymax;
		format[1] = new char[strlen(Yfmt)+1];
		strcpy(format[1], Yfmt);
	}

	if (numdimensions > 2)
	{
		dlabels[2] = new char[strlen(Zname)+1];
		strcpy(dlabels[2], Zname);
		dscalelabels[2] = new char[strlen(Zslab)+1];
		strcpy(dscalelabels[2], Zslab);
		min[2] = Zmin;
		max[2] = Zmax;
		format[2] = new char[strlen(Zfmt)+1];
		strcpy(format[2], Zfmt);
	}

    // set the base panelfeature size to numdimensions
	if (numdimensions > 1)
	{
		delete value;
		value = new float[numdimensions];
		numvalues = numdimensions;
		lastfilled = numdimensions;
		lastread = numdimensions;
	}

    // set up generic stuff
	showflag = TRUE;
	numdata = 0;
	style = DIGITAL;
	
}



////////////////////////////////////////////////////////////////////////
display::~display()
{

	delete min;
	delete max;

	for (int i=0; i<numdimensions; i++)
	{
		delete format[i];
		delete ddata[i];
		delete dlabels[i];
		delete dscalelabels[i];
	}

	delete format;
	delete ddata;
	delete dlabels;
}
////////////////////////////////////////////////////////////////////////
void display::doallfunc(panelfeature *t)
{
	if (t->lastfilled == numvalues)
	{
		// we could do the walk here
		// panelfeature::doallfunc();
	}
}
//////////////////////////////////////////////////////////////////////////////
void display::clear()
{
	numdata = 0;
	if( updateflag != MAJOR )
	{
		updateflag = VALUE_CLEAR;
		show(parentX(),parentY());
	}
}

////////////////////////////////////////////////////////////////////////

    // assignment operator overloading ////////////////////////////////
panelfeature& display::operator<<(float *f)
{

	panelfeature::operator<<(f);

    // make room for data
	if (numdata == maxdata)
	{
		shiftdata();
		numdata--;
	}

    // read the data
	
	for (int i=0; i<numdimensions; i++)
	{
		ddata[i][numdata] = value[i];
	}
	numdata++;

	if( updateflag != MAJOR )
	{
		updateflag = VALUE_CHANGE;
		show(parentX(),parentY());
	}
	return(*this);
}
panelfeature& display::operator<<(float f)
{
	panelfeature::operator<<(f);

    // if not a complete data point do not process yet
	if (lastfilled != numvalues)
		return(*this);

    // else make room for data
	if (numdata == maxdata)
	{
		shiftdata();
		numdata--;
	}

    // read the data
	
	for (int i=0; i<numdimensions; i++)
	{
		ddata[i][numdata] = value[i];
	}
	numdata++;
	if( updateflag != MAJOR )
	{
		updateflag = VALUE_CHANGE;
		show(parentX(),parentY());
	}

	return(*this);
}
panelfeature& display::operator<<(int *j)
{
	panelfeature::operator<<(j);
	return(*this);
}
panelfeature& display::operator<<(int j)
{
	panelfeature::operator<<(j);
	return(*this);
}
panelfeature& display::operator<<(panelfeature *p)
{
	float *v = new float[numdimensions];
	(*p) >> v;
	(*this) << v;
	delete v;
	return(*this);
}
panelfeature& display::operator<<(panelfeature p)
{
	(*this) << &p;
	return(*this);
}

////////////////////////////////////////////////////////////////////////

	// some misc. things:

char *display::getlabel(int axis,float v)
{
	return (form(format[axis],v));
}
void display::changefmt(int axis,char *newfmt)
{
	delete format[axis];
	format[axis] = new char[strlen(newfmt)+1];
	strcpy(format[axis],newfmt);
	if( updateflag != MAJOR )
	{
		updateflag = AXIS_CHANGE;
		show(parentX(),parentY());
	}
}
void display::changeaxis(int axis,char *lab, char *slab, float mn, float mx)
{
	delete dlabels[axis];
	dlabels[axis] = new char[strlen(lab)+1];
	strcpy(dlabels[axis],lab);

	delete dscalelabels[axis];
	dscalelabels[axis] = new char[strlen(slab)+1];
	strcpy(dscalelabels[axis],slab);

	min[axis] = mx;
	max[axis] = mn;
	if( updateflag != MAJOR )
	{
		updateflag = AXIS_CHANGE;
		show(parentX(),parentY());
	}
}

void display::shiftdata()
{
	for (int i=1; i<numdata; i++)
		for( int j=0; j<numdimensions; j++)
			ddata[j][i-1] = ddata[j][i];
}
