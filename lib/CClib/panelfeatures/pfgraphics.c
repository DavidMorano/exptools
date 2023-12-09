
/**************************************************************************/
/* PANELFEATURES Package    Release:  1.0    Release Date: 1/15/89        */
/*                          Provider: J. D. Iorio  (speedy!jdi)           */
/**************************************************************************/

// PFGRAPHICS.H
//
//	Copyright (C) ATT 1987
//
// This header file defines misc. graphics functions for the derived class of
// panelfeature
// that will be used to define an instrument for ALMMS
//
//   History:
//	J. D. Iorio	12/15/87	created
//

#include "pf.h"

//////////////////////////////////////////////////////////////////
void panelfeature::setXY(int X, int Y) 
{ 
	xloc=X; yloc=Y; 
}
//////////////////////////////////////////////////////////////////
void panelfeature::setXYsize(int X, int Y)
{
	xsize=X; ysize=Y;
}
