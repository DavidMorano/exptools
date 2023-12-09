
/**************************************************************************/
/* PANELFEATURES Package    Release:  1.0    Release Date: 1/15/89        */
/*                          Provider: J. D. Iorio  (speedy!jdi)           */
/**************************************************************************/

// PFATTRIB.C 
//
//	Copyright (C) ATT 1988
//
//	This file contains all of the attribute routines for all of the
//   types of panelfeatures. 
//
//   HISTORY:
//	J. D. Iorio	2/12/88	created
//

#include "pf.h"
#include "giproto.h"


extern int OrigUsermode;


void panelfeature::clr_attribute(int a)
{
	attrib &= ~a;
	if(updateflag != MAJOR)
	{
		updateflag = ATTRIB_CHANGE;
		show(parentX(), parentY());
	}
}
void panelfeature::set_attribute(int a)
{
	attrib |= a;
	if(updateflag != MAJOR)
	{
		updateflag = ATTRIB_CHANGE;
		show(parentX(), parentY());
	}
}
void panelfeature::init_attribute(int a)
{
	attrib |= a;
}
void panelfeature::tog_attribute(int a)
{
	attrib ^= a;
	if(updateflag != MAJOR)
	{
		updateflag = ATTRIB_CHANGE;
		show(parentX(), parentY());
	}
}
int panelfeature::test_attribute(int a)
{
	return((int)(attrib & a) == a);
}
int panelfeature::get_attribute()
{
	return(attrib);
}

