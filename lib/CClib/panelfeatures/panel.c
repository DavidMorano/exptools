
/**************************************************************************/
/* PANELFEATURES Package    Release:  1.0    Release Date: 1/15/89        */
/*                          Provider: J. D. Iorio  (speedy!jdi)           */
/**************************************************************************/

// PANEL.C
//
//	Copyright (C) ATT 1987
//
// This source file defines the functions for the class of
// panel which forms the root node of an instrument tree
// built from "panelfeature" objects.
// It will be used to define instruments for ALMMS
//
//   History:
//	J. D. Iorio	12/14/87	created
//

#include "pf.h"


//////////////////////////////////////////////////////////////
						// constructor
//panel::panel(char *Name, cluster *Root, instrument *ins)
panel::panel(char *Name, cluster *Root, void *ins)
	: (Name,0,0,0,0,NULLFUNC)
{
	// set up the panel linkages
	root = Root;
	root->parent = this;
	root->set_this_module(ins);

	// save the name
	instrname = new char[strlen(Name)+1];
	strcpy(instrname, Name);
	
	// show the instrument only if this is the MAIN panel
	if (ins == NULL)
		show();
}

//////////////////////////////////////////////////////////////
						// destructor
panel::~panel()
{
	delete instrname;
}

//////////////////////////////////////////////////////////////
						// misc. functions
