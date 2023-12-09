
/**************************************************************************/
/* PANELFEATURES Package    Release:  1.0    Release Date: 1/15/89        */
/*                          Provider: J. D. Iorio  (speedy!jdi)           */
/**************************************************************************/

// CLUSTER.C
//
//	Copyright (C) ATT 1987
//
// This source file defines the operations of the derived class of
// panelfeatures called clusters
// that will be used to define instruments for ALMMS
//
//   History:
//	J. D. Iorio	12/8/87		created
//

#include "pf.h"


//////////////////////////////////////////////////////////////////////////////
		// constructors for various numbers of children (1 - 10)


cluster::cluster(char *Name, int(*func)(panelfeature *),
			panelfeature *pf1):
		(Name, 0, 0, 0, 0, func)
	
{

	numchildren = 1;
	child = new panelfeature *[numchildren];
	child[0] = pf1;

	for (int i=0; i<numchildren; i++)
		child[i]->parent = this;

	
	resize();

	dofunc(this);
}

cluster::cluster(char *Name, int(*func)(panelfeature *),
			panelfeature *pf1, panelfeature *pf2)
		: (Name, 0, 0, 0, 0, func)
{
	numchildren = 2;
	child = new panelfeature *[numchildren];
	child[0] = pf1;
	child[1] = pf2;

	for (int i=0; i<numchildren; i++)
		child[i]->parent = this;
	
	resize();

	dofunc(this);
}

cluster::cluster(char *Name, int(*func)(panelfeature *),
			panelfeature *pf1, panelfeature *pf2, panelfeature *pf3)
		: (Name, 0, 0, 0, 0, func)
{
	numchildren = 3;
	child = new panelfeature *[numchildren];
	child[0] = pf1;
	child[1] = pf2;
	child[2] = pf3;

	for (int i=0; i<numchildren; i++)
		child[i]->parent = this;
	
	resize();

	dofunc(this);
}

cluster::cluster(char *Name, int(*func)(panelfeature *),
			panelfeature *pf1, panelfeature *pf2, panelfeature *pf3,
			panelfeature *pf4)
		: (Name, 0, 0, 0, 0, func)
{
	numchildren = 4;
	child = new panelfeature *[numchildren];
	child[0] = pf1;
	child[1] = pf2;
	child[2] = pf3;
	child[3] = pf4;

	for (int i=0; i<numchildren; i++)
		child[i]->parent = this;
	
	resize();

	dofunc(this);
}

cluster::cluster(char *Name, int(*func)(panelfeature *),
			panelfeature *pf1, panelfeature *pf2, panelfeature *pf3,
			panelfeature *pf4, panelfeature *pf5)
		: (Name, 0, 0, 0, 0, func)
{
	numchildren = 5;
	child = new panelfeature *[numchildren];
	child[0] = pf1;
	child[1] = pf2;
	child[2] = pf3;
	child[3] = pf4;
	child[4] = pf5;

	for (int i=0; i<numchildren; i++)
		child[i]->parent = this;
	
	resize();

	dofunc(this);
}

cluster::cluster(char *Name, int(*func)(panelfeature *),
			panelfeature *pf1, panelfeature *pf2, panelfeature *pf3,
			panelfeature *pf4, panelfeature *pf5, panelfeature *pf6)
		: (Name, 0, 0, 0, 0, func)
{
	numchildren = 6;
	child = new panelfeature *[numchildren];
	child[0] = pf1;
	child[1] = pf2;
	child[2] = pf3;
	child[3] = pf4;
	child[4] = pf5;
	child[5] = pf6;

	for (int i=0; i<numchildren; i++)
		child[i]->parent = this;
	
	resize();

	dofunc(this);
}

cluster::cluster(char *Name, int(*func)(panelfeature *),
			panelfeature *pf1, panelfeature *pf2, panelfeature *pf3,
			panelfeature *pf4, panelfeature *pf5, panelfeature *pf6,
			panelfeature *pf7)
		: (Name, 0, 0, 0, 0, func)
{
	numchildren = 7;
	child = new panelfeature *[numchildren];
	child[0] = pf1;
	child[1] = pf2;
	child[2] = pf3;
	child[3] = pf4;
	child[4] = pf5;
	child[5] = pf6;
	child[6] = pf7;

	for (int i=0; i<numchildren; i++)
		child[i]->parent = this;
	
	resize();

	dofunc(this);
}

cluster::cluster(char *Name, int(*func)(panelfeature *),
			panelfeature *pf1, panelfeature *pf2, panelfeature *pf3,
			panelfeature *pf4, panelfeature *pf5, panelfeature *pf6,
			panelfeature *pf7, panelfeature *pf8)
		: (Name, 0, 0, 0, 0, func)
{
	numchildren = 8;
	child = new panelfeature *[numchildren];
	child[0] = pf1;
	child[1] = pf2;
	child[2] = pf3;
	child[3] = pf4;
	child[4] = pf5;
	child[5] = pf6;
	child[6] = pf7;
	child[7] = pf8;

	for (int i=0; i<numchildren; i++)
		child[i]->parent = this;
	
	resize();

	dofunc(this);
}

cluster::cluster(char *Name, int(*func)(panelfeature *),
			panelfeature *pf1, panelfeature *pf2, panelfeature *pf3,
			panelfeature *pf4, panelfeature *pf5, panelfeature *pf6,
			panelfeature *pf7, panelfeature *pf8, panelfeature *pf9)
		: (Name, 0, 0, 0, 0, func)
{
	numchildren = 9;
	child = new panelfeature *[numchildren];
	child[0] = pf1;
	child[1] = pf2;
	child[2] = pf3;
	child[3] = pf4;
	child[4] = pf5;
	child[5] = pf6;
	child[6] = pf7;
	child[7] = pf8;
	child[8] = pf9;

	for (int i=0; i<numchildren; i++)
		child[i]->parent = this;
	
	resize();

	dofunc(this);
}

cluster::cluster(char *Name, int(*func)(panelfeature *),
			panelfeature *pf1, panelfeature *pf2, panelfeature *pf3,
			panelfeature *pf4, panelfeature *pf5, panelfeature *pf6,
			panelfeature *pf7, panelfeature *pf8, panelfeature *pf9,
			panelfeature *pfA)
		: (Name, 0, 0, 0, 0, func)
{
	numchildren = 10;
	child = new panelfeature *[numchildren];
	child[0] = pf1;
	child[1] = pf2;
	child[2] = pf3;
	child[3] = pf4;
	child[4] = pf5;
	child[5] = pf6;
	child[6] = pf7;
	child[7] = pf8;
	child[8] = pf9;
	child[9] = pfA;

	for (int i=0; i<numchildren; i++)
		child[i]->parent = this;
	
	resize();

	dofunc(this);
}
//////////////////////////////////////////////////////////////////////////////
		// destructor
cluster::~cluster()
{
	delete child;
}

//////////////////////////////////////////////////////////////////////////////
		// graphics functions
void cluster::resize()
{
	int xmax, ymax, xtot, ytot, xs, ys;
	int width;
	
	xmax = xtot = BorderXovrhd;
	ytot = BorderYovrhd;
	ymax = 0;

	for (int i=0; i<numchildren; i++)
	{
		child[i]->getXYsize(xs, ys);

		// width if we add this panelfeature to current line
		width = xtot + xs;

		// if too wide, advance to next line
		if (width > ScreenXmax)
		{
			xmax = (xmax > xtot) ? xmax : xtot;
			ytot = ytot + ymax + PfYspace;
			xtot = BorderXovrhd;
			ymax = 0;
			child[i]->setXY(xtot, ytot);
			xtot = xtot + xs + PfXspace;
		}
		else 
		// else put on current line
		{
			child[i]->setXY(xtot, ytot);
			xtot = width + PfXspace;
		}


		// keep track of tallest panelfeature on this line
		ymax = (ymax > ys) ? ymax : ys;
	}

	// is the current line the longest ?
	xmax = (xmax > xtot) ? xmax : xtot;
	
	setXYsize(xmax, ytot+ymax);

}
//////////////////////////////////////////////////////////////////////////////
void cluster::set_this_module(void *ins)
{
	this_module = ins;

	for (int i=0; i<numchildren; i++)
	{
		child[i]->set_this_module(ins);
	}
}
