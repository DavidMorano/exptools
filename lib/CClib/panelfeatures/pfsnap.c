
/**************************************************************************/
/* PANELFEATURES Package    Release:  1.0    Release Date: 1/15/89        */
/*                          Provider: J. D. Iorio  (speedy!jdi)           */
/**************************************************************************/

// PFSANP.C
//
//	Copyright (C) ATT 1988
//
// This file defines the snapshot generator functions
// for the set of "panelfeature" objects.
// It will be used to define instruments for ALMMS
//
//   History:
//	J. D. Iorio	7/11/88	created
//

#include "pf.h"
#include <ctype.h>

////////////////////////////////////////////////////////////////////////////
char* panel::snap( char *cbuf)		// take a snapshot of the machine
{
	char *cp;

	// if the root, allocate a very large buffer
	if(cbuf == NULL)
	{
		if((cp = new char[16000]) == 0)
		{
			errormsg("snap failed");
			return(NULL);
		}
		*cp = '\0';
	}
	else 
		cp = cbuf;

	cbuf = cp;


	cp = root->snap(cp);
	return(cbuf);
}


////////////////////////////////////////////////////////////////////////////
char * cluster::snap (char *cbuf)
{
	char *cp;

	cp = cbuf;

	if(test_attribute(A_GREY) == FALSE)
	{
		for (int i=0; i<numchildren; i++)
		{
			cp = child[i]->snap(cp);
		}
	}

	return(cp);
}

////////////////////////////////////////////////////////////////////////////
char * panelfeature::snap (char *cbuf)
{
	char *cp = cbuf;

	return(cp);
}

////////////////////////////////////////////////////////////////////////////
char * display::snap (char *cbuf)
{
	char *cp = cbuf;

	return(cp);
}
////////////////////////////////////////////////////////////////////////////
char * ASCIIdisp::snap (char *cbuf)
{
	char *cp = cbuf;

	return(cp);
}

////////////////////////////////////////////////////////////////////////////
char * knob::snap (char *cbuf)
{
	char *cp = cbuf;

	strcat(cp, officialname);
	strcat(cp,"=");

	return(cp);
}

////////////////////////////////////////////////////////////////////////////
char * INTknob::snap (char *cbuf)
{
	char *cp = cbuf;

	if(test_attribute(A_GREY) == TRUE)
		return(cbuf);

	cp = knob::snap(cp);
	
	for(int i=0; i<numvalues; i++)
	{
		strcat(cp,(form(getfmt(),value[i])));
		strcat(cp," ");
	}
	strcat(cp,";");

	for( ; *cp != NULL; cp++);
	return(cp-1);
}

////////////////////////////////////////////////////////////////////////////
char * FLTknob::snap (char *cbuf)
{
	char *cp = cbuf;

	if(test_attribute(A_GREY) == TRUE)
		return(cbuf);

	cp = knob::snap(cp);
	
	for(int i=0; i<numvalues; i++)
	{
		strcat(cp,(form(getfmt(),value[i])));
		strcat(cp," ");
	}
	strcat(cp,";");

	for( ; *cp != NULL; cp++);
	return(cp-1);
}
////////////////////////////////////////////////////////////////////////////
char * FWINTknob::snap (char *cbuf)
{
	char *cp = cbuf;

	if(test_attribute(A_GREY) == TRUE)
		return(cbuf);

	cp = knob::snap(cp);
	
	for(int i=0; i<numvalues; i++)
	{
		strcat(cp,(form(getfmt(),value[i])));
		strcat(cp," ");
	}

	strcat(cp,";");

	for( ; *cp != NULL; cp++);
	return(cp-1);
}
////////////////////////////////////////////////////////////////////////////
char * FWFLTknob::snap (char *cbuf)
{
	char *cp = cbuf;

	if(test_attribute(A_GREY) == TRUE)
		return(cbuf);

	cp = knob::snap(cp);
	
	for(int i=0; i<numvalues; i++)
	{
		strcat(cp,(form(getfmt(),value[i])));
		strcat(cp," ");
	}
	strcat(cp,";");

	for( ; *cp != NULL; cp++);
	return(cp-1);
}
////////////////////////////////////////////////////////////////////////////
char * VWINTknob::snap (char *cbuf)
{
	char *cp = cbuf;

	if(test_attribute(A_GREY) == TRUE)
		return(cbuf);

	cp = knob::snap(cp);
	
	for(int i=0; i<numvalues; i++)
	{
		strcat(cp,(form(getfmt(),value[i])));
		strcat(cp," ");
	}
	strcat(cp,";");

	for( ; *cp != NULL; cp++);
	return(cp-1);
}

////////////////////////////////////////////////////////////////////////////
char * VWFLTknob::snap (char *cbuf)
{
	char *cp = cbuf;

	if(test_attribute(A_GREY) == TRUE)
		return(cbuf);

	cp = knob::snap(cp);
	
	for(int i=0; i<numvalues; i++)
	{
		strcat(cp,(form(getfmt(),value[i])));
		strcat(cp," ");
	}
	strcat(cp,";");

	for( ; *cp != NULL; cp++);
	return(cp-1);
}

////////////////////////////////////////////////////////////////////////////
char * ENUMknob::snap (char *cbuf)
{
	char *cp = cbuf;

	if(test_attribute(A_GREY) == TRUE)
		return(cbuf);

	cp = knob::snap(cp);
	
	for(int i=0; i<numvalues; i++)
	{
		strcat(cp,labels[(int)value[i]]);
		strcat(cp," ");
	}
	strcat(cp,";");

	for( ; *cp != NULL; cp++);
	return(cp-1);
}

////////////////////////////////////////////////////////////////////////////
char * ASCIIknob::snap (char *cbuf)
{
	char *cp = cbuf;

	if(test_attribute(A_GREY) == TRUE)
		return(cbuf);

	strcat(cp, officialname);
	strcat(cp,"=");
	
	strcat(cp,answer);
	strcat(cp,";");

	for( ; *cp != NULL; cp++);
	return(cp-1);
}
