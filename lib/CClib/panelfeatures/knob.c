
/**************************************************************************/
/* PANELFEATURES Package    Release:  1.0    Release Date: 1/15/89        */
/*                          Provider: J. D. Iorio  (speedy!jdi)           */
/**************************************************************************/

// KNOB.C
//
//	Copyright (C) ATT 1987
//
// This header file defines the functions for the derived class of
// panelfeatures called knobs
// that will be used to define an instrument for ALMMS
//
//   History:
//	J. D. Iorio	12/3/87		created
//

#include "pf.h"

extern int Usermode;
extern int OrigUsermode;


	// constructor
knob::knob(char *Name, int X, int Y, knobstyle Style, char *Slab,
	     float Hilimit, float Lolimit, float Dfault,
	     int(*func)(panelfeature *), int Maxwidth) :	
		(Name, X, Y, KnobWidth, (Maxwidth+KnobHeight), func)
{

	// save the generic knob parameters
	style = Style;
	highlimit = Hilimit;
	lowlimit = Lolimit;
	maxnumvalues = Maxwidth;
	dfault = Dfault;
	format = new char[strlen("%-8.2f")+1];
	strcpy(format, "%-8.2f");

	scalelabel = new char[strlen(Slab)+1];
	strcpy(scalelabel,Slab);

	// re-size and set the knob's initial values to default
	// and execute the handler function for this knob only
	
	changesize(Maxwidth);
	dofunc(this);

}


knob::~knob()
{
	delete format;
	delete scalelabel;
}

///////////////////////////////////////////////////////////////////////////////
void knob::changefmt(char *fmt)
{
	delete format;
	format = new char[strlen(fmt)+1];
	strcpy(format, fmt);
	
}
///////////////////////////////////////////////////////////////////////////////
// these are dummy functions overloaded and used by ENUM type knobs
// to get indexes of enumerated values
float knob::value_of(float x)
{
	return(x);
}
float knob::value_for(float x)
{
	return(x);
}
//////////////////////////////////////////////////////////////////////////////
// reset knob to its default without executing  the action function
void knob::resetknob()
{
	int sz;
	
	sz = getsize();
	for(int i=0; i<sz; i++)
		value[i] = value_of(dfault);

	// allow for display refresh if interactive
	Usermode = OrigUsermode;

	if (updateflag != MAJOR)
	{
		updateflag = VALUE_CHANGE;
		show(parentX(),parentY());
	}
}
///////////////////////////////////////////////////////////////////////////////
panelfeature& knob::operator<<(float *f)
{
	int num = getsize();
	float *v = new float[num];
	int found_one = 0;
	char *warnmsg;

	for(int i=0; i<num; i++)
	{
		v[i] = value_of(f[i]);

		if( (v[i] > highlimit) || (v[i] < lowlimit))
		{
			v[i] = value_of(dfault);
			if (found_one == 0)
			{
				warnmsg=form("RANGE ERROR: knob %s\n",
								getname());
				if (num > 1)
					warnmsg=form("%s  element(s)",warnmsg);
				found_one = 1;
			}
			if (num > 1)
				warnmsg=form("%s [%d]",warnmsg, i);

		}
	}
	if (found_one != 0)
	{
		warnmsg=form("%s set to default",warnmsg);
		errormsg(warnmsg);
	}
	panelfeature::operator<<(v);
	if (updateflag != MAJOR)
	{
		updateflag = VALUE_CHANGE;
		show(parentX(),parentY());
	}
	delete v;
	return(*this);
	
}
panelfeature& knob::operator<<(float g)
{
	float f = value_of(g);

	if( (f > highlimit) || (f < lowlimit))
	{
		f = value_of(dfault);
		errormsg(form("RANGE ERROR: knob %s",getname()));
	}
	panelfeature::operator<<(f);
	if (updateflag != MAJOR)
	{
		updateflag = VALUE_CHANGE;
		show(parentX(),parentY());
	}
	return(*this);
	
}
panelfeature& knob::operator<<(int *i)
{
	int num = getsize();
	float *v = new float[num];
	
	for(int j=0; j<num; j++)
		v[j] = (float)i[j];

	(*this) << (v);
	delete v;
	return(*this);
}
panelfeature& knob::operator<<(int i)
{
	float v;
	
	v = (float)i;
	(*this) << v;
	return(*this);
}
panelfeature& knob::operator<<(panelfeature *p)
{
	// if an assignment is made from the NULL knob 
	// then use the screen interaction routine

	if (p == QUERY)
		queryknob();
	else 
	{
		int num = getsize();
		float *v = new float[num];

		(*p) >> v;
		(*this) << v;
		delete v;
	}

	return(*this);
}
panelfeature& knob::operator<<(panelfeature p)
{
	(*this)<< &p;
	return(*this);
}
//////////////////////////////////////////////////////////////////////////////
panelfeature& knob::operator>>(float *f)
{
	panelfeature::operator>>(f);

	int num = getsize();
	for (int i=0; i<num; i++)
		f[i] = value_for(f[i]);
	return(*this);
}
panelfeature& knob::operator>>(float& f)
{
	panelfeature::operator>>(f);
	f = value_for(f);
	return(*this);
}
panelfeature& knob::operator>>(int& i)
{
	int k;
	panelfeature::operator>>(k);
	i = k;
	return(*this);
}
panelfeature& knob::operator>>(int *j)
{
	panelfeature::operator>>(j);
	return(*this);
}
panelfeature& knob::operator>>(panelfeature& p)
{
	panelfeature::operator>>(p);
	return(*this);
}
panelfeature& knob::operator>>(panelfeature *p)
{
	panelfeature::operator>>(p);
	return(*this);
}
//////////////////////////////////////////////////////////////////////////////

void knob::queryknob()
{
	float temp;
	int num = getsize();
	float *v = new float[num];
	char *qrymsg;

	for(int j=0; j<num; j++)
	{
		qrymsg = form("Enter the value for knob %s :",getname());

		if (num != 1)
			qrymsg = form("%s element [%d] :",j);

		interactmsg(qrymsg,temp);
		v[j] = temp;
	}
	(*this) << v;
	delete v;
}

int knob::changesize(int tosize)
{
	int oldsize = numvalues;
	int smaller = oldsize < tosize ? oldsize : tosize;
	float *temp;

	if ((tosize < 0) || (tosize > maxnumvalues))
	{
		errormsg(form("KNOB SIZE ERROR: knob %s -cannot set to size %d",
					getname(), tosize));
		return(numvalues);
	}
	numvalues = tosize;
	temp = new float[tosize];
	
	
		// first value is always default on initialization
	if ((tosize == maxnumvalues) && (oldsize == 1))
		temp[0] = value_of(dfault);
	else
		temp[0] = value[0];

	for (int i=1; i<smaller; i++)
		temp[i] = value[i];

	for (       ; i<tosize; i++)
		temp[i] = value_of(dfault);


	delete value;
	value = temp;
	lastfilled = numvalues;
	lastread = numvalues;
	return(tosize);
}


char *knob::getlabel(float v)
{
	return (form(format,v));
}
