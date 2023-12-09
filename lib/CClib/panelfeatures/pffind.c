
/**************************************************************************/
/* PANELFEATURES Package    Release:  1.0    Release Date: 1/15/89        */
/*                          Provider: J. D. Iorio  (speedy!jdi)           */
/**************************************************************************/

// PFFIND.C 
//
//	Copyright (C) ATT 1987
//
//	This file contains all of the search routines for all of the
//   types of panelfeatures. 
//
//   HISTORY:
//	J. D. Iorio	12/14/87	created
//

#include "pf.h"


/////////////////////////////////////////////////////////////////////////
panelfeature *panelfeature::find(int X, int Y)
{
	// is point X,Y within this panelfeature
	X = X-xloc;
	Y = Y-yloc;

	if ( (X < 0) || (X > xsize) )
		return(NULL);
	if ( (Y < 0) || (Y > ysize) )
		return(NULL);

	return(this);
}

panelfeature *panelfeature::find(char *Name)
{
	// is Name the name of this panelfeature?
	if (strcmp(Name,name) == 0)
		return(this);
	else 
		return(NULL);
}

/////////////////////////////////////////////////////////////////////////
panelfeature *cluster::find(int X, int Y)
{
	panelfeature *p;

	// is point X,Y within this cluster
	if (panelfeature::find(X, Y) == NULL)
		return(NULL);
	else
	{
		X = X-xloc;
		Y = Y-yloc;
		
		for( int i=0; i<numchildren; i++)
		{
			if ((p=child[i]->find(X, Y)) != NULL)
				return(p);
		}
		return(this);
	}

}

panelfeature *cluster::find(char *Name)
{
	panelfeature *p;

	// is Name the name of this cluster?
	if ((p=panelfeature::find(Name)) != NULL)
		return(p);
	else 
	{
		for( int i=0; i<numchildren; i++)
		{
			if ((p=child[i]->find(Name)) != NULL)
				return(p);
		}
		return(NULL);
	}
}

/////////////////////////////////////////////////////////////////////////
panelfeature *panel::find( int X, int Y)
{
	return(root->find(X, Y));
}
panelfeature *panel::find( char *Name)
{
	panelfeature *p;
	char *ep;

	// if full path, find the subpanel first
	for( ep=Name; (*ep!='\0') && (*ep!='!'); ep++);
	if(*ep == '!')
	{
		*ep = '\0';
		if((p = find(Name)) == NULL)
			return(p);
		else
		{
			ep++;
			return(p->find(ep));
		}
	}


	// else is Name the name of this panel?
	if ((p=panelfeature::find(Name)) != NULL)
		return(p);

	// look into cluster
	return(root->find(Name));
}
