
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


//////////////////////////////////////////////////////////////////////////////
class ENUMvals
{
	int *ev;

public:
	ENUMvals(int a0);
	ENUMvals(int a0, int a1);
	ENUMvals(int a0, int a1, int a2);
	ENUMvals(int a0, int a1, int a2, int a3);
	ENUMvals(int a0, int a1, int a2, int a3, int a4);
	ENUMvals(int a0, int a1, int a2, int a3, int a4, int a5);
	ENUMvals(int a0, int a1, int a2, int a3, int a4, int a5, int a6);
	ENUMvals(int a0, int a1, int a2, int a3, int a4,
		int a5, int a6, int a7);
	ENUMvals(int a0, int a1, int a2, int a3, int a4,
		int a5, int a6, int a7, int a8);
	ENUMvals(int a0, int a1, int a2, int a3, int a4,
		int a5, int a6, int a7, int a8, int a9);

	~ENUMvals();

	operator int*() { return(ev);}
};

//////////////////////////////////////////////////////////////////////////////
class ENUMlabs
{
	char **ev;

public:
	ENUMlabs(char* a0);
	ENUMlabs(char* a0, char* a1);
	ENUMlabs(char* a0, char* a1, char* a2);
	ENUMlabs(char* a0, char* a1, char* a2, char* a3);
	ENUMlabs(char* a0, char* a1, char* a2, char* a3, char* a4);
	ENUMlabs(char* a0, char* a1, char* a2, char* a3, char* a4, char* a5);
	ENUMlabs(char* a0, char* a1, char* a2, char* a3, char* a4,
		char* a5, char* a6);
	ENUMlabs(char* a0, char* a1, char* a2, char* a3, char* a4,
		char* a5, char* a6, char* a7);
	ENUMlabs(char* a0, char* a1, char* a2, char* a3, char* a4,
		char* a5, char* a6, char* a7, char* a8);
	ENUMlabs(char* a0, char* a1, char* a2, char* a3, char* a4,
		char* a5, char* a6, char* a7, char* a8, char* a9);

	~ENUMlabs();

	operator char **() { return(ev);}
};

