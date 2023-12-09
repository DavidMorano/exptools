
/**************************************************************************/
/* PANELFEATURES Package    Release:  1.0    Release Date: 1/15/89        */
/*                          Provider: J. D. Iorio  (speedy!jdi)           */
/**************************************************************************/

// ENUMHELP.H
//
//	Copyright (C) ATT 1987
//
// This header file defines the functions which help define
// ENUM labels and values for instruments
// that will be used to define instruments for ALMMS
//
//   History:
//	J. D. Iorio	12/21/87	created
//


#include "enumhelp.h"


///////////////////////////////////////////////////////////////////////////////
// ENUMvals routines
///////////////////////////////////////////////////////////////////////////////

ENUMvals::ENUMvals(int a0)
{
	ev = new int[1];
	ev[0] = a0;
}
ENUMvals::ENUMvals(int a0, int a1)
{
	ev = new int[2];
	ev[0] = a0;
	ev[1] = a1;
}
ENUMvals::ENUMvals(int a0, int a1, int a2)
{
	ev = new int[3];
	ev[0] = a0;
	ev[1] = a1;
	ev[2] = a2;
}
ENUMvals::ENUMvals(int a0, int a1, int a2, int a3)
{
	ev = new int[4];
	ev[0] = a0;
	ev[1] = a1;
	ev[2] = a2;
	ev[3] = a3;
}
ENUMvals::ENUMvals(int a0, int a1, int a2, int a3, int a4)
{
	ev = new int[5];
	ev[0] = a0;
	ev[1] = a1;
	ev[2] = a2;
	ev[3] = a3;
	ev[4] = a4;
}
ENUMvals::ENUMvals(int a0, int a1, int a2, int a3, int a4, int a5)
{
	ev = new int[6];
	ev[0] = a0;
	ev[1] = a1;
	ev[2] = a2;
	ev[3] = a3;
	ev[4] = a4;
	ev[5] = a5;
}
ENUMvals::ENUMvals(int a0, int a1, int a2, int a3, int a4, int a5, int a6)
{
	ev = new int[7];
	ev[0] = a0;
	ev[1] = a1;
	ev[2] = a2;
	ev[3] = a3;
	ev[4] = a4;
	ev[5] = a5;
	ev[6] = a6;
}
ENUMvals::ENUMvals(int a0, int a1, int a2, int a3, int a4,
		int a5, int a6, int a7)
{
	ev = new int[8];
	ev[0] = a0;
	ev[1] = a1;
	ev[2] = a2;
	ev[3] = a3;
	ev[4] = a4;
	ev[5] = a5;
	ev[6] = a6;
	ev[7] = a7;
}
ENUMvals::ENUMvals(int a0, int a1, int a2, int a3, int a4,
		int a5, int a6, int a7, int a8)
{
	ev = new int[9];
	ev[0] = a0;
	ev[1] = a1;
	ev[2] = a2;
	ev[3] = a3;
	ev[4] = a4;
	ev[5] = a5;
	ev[6] = a6;
	ev[7] = a7;
	ev[8] = a8;
}
ENUMvals::ENUMvals(int a0, int a1, int a2, int a3, int a4,
		int a5, int a6, int a7, int a8, int a9)
{
	ev = new int[10];
	ev[0] = a0;
	ev[1] = a1;
	ev[2] = a2;
	ev[3] = a3;
	ev[4] = a4;
	ev[5] = a5;
	ev[6] = a6;
	ev[7] = a7;
	ev[8] = a8;
	ev[9] = a9;
}

ENUMvals::~ENUMvals()
{
	delete ev;
}

///////////////////////////////////////////////////////////////////////////////
// ENUMlabs routines
///////////////////////////////////////////////////////////////////////////////

ENUMlabs::ENUMlabs(char* a0)
{
	ev = new char*[1];
	ev[0] = a0;
}
ENUMlabs::ENUMlabs(char* a0, char* a1)
{
	ev = new char*[2];
	ev[0] = a0;
	ev[1] = a1;
}
ENUMlabs::ENUMlabs(char* a0, char* a1, char* a2)
{
	ev = new char*[3];
	ev[0] = a0;
	ev[1] = a1;
	ev[2] = a2;
}
ENUMlabs::ENUMlabs(char* a0, char* a1, char* a2, char* a3)
{
	ev = new char*[4];
	ev[0] = a0;
	ev[1] = a1;
	ev[2] = a2;
	ev[3] = a3;
}
ENUMlabs::ENUMlabs(char* a0, char* a1, char* a2, char* a3, char* a4)
{
	ev = new char*[5];
	ev[0] = a0;
	ev[1] = a1;
	ev[2] = a2;
	ev[3] = a3;
	ev[4] = a4;
}
ENUMlabs::ENUMlabs(char* a0, char* a1, char* a2, char* a3, char* a4, char* a5)
{
	ev = new char*[6];
	ev[0] = a0;
	ev[1] = a1;
	ev[2] = a2;
	ev[3] = a3;
	ev[4] = a4;
	ev[5] = a5;
}
ENUMlabs::ENUMlabs(char* a0, char* a1, char* a2, char* a3, char* a4, char* a5, char* a6)
{
	ev = new char*[7];
	ev[0] = a0;
	ev[1] = a1;
	ev[2] = a2;
	ev[3] = a3;
	ev[4] = a4;
	ev[5] = a5;
	ev[6] = a6;
}
ENUMlabs::ENUMlabs(char* a0, char* a1, char* a2, char* a3, char* a4,
		char* a5, char* a6, char* a7)
{
	ev = new char*[8];
	ev[0] = a0;
	ev[1] = a1;
	ev[2] = a2;
	ev[3] = a3;
	ev[4] = a4;
	ev[5] = a5;
	ev[6] = a6;
	ev[7] = a7;
}
ENUMlabs::ENUMlabs(char* a0, char* a1, char* a2, char* a3, char* a4,
		char* a5, char* a6, char* a7, char* a8)
{
	ev = new char*[9];
	ev[0] = a0;
	ev[1] = a1;
	ev[2] = a2;
	ev[3] = a3;
	ev[4] = a4;
	ev[5] = a5;
	ev[6] = a6;
	ev[7] = a7;
	ev[8] = a8;
}
ENUMlabs::ENUMlabs(char* a0, char* a1, char* a2, char* a3, char* a4,
		char* a5, char* a6, char* a7, char* a8, char* a9)
{
	ev = new char*[10];
	ev[0] = a0;
	ev[1] = a1;
	ev[2] = a2;
	ev[3] = a3;
	ev[4] = a4;
	ev[5] = a5;
	ev[6] = a6;
	ev[7] = a7;
	ev[8] = a8;
	ev[9] = a9;
}

ENUMlabs::~ENUMlabs()
{
	delete ev;
}
