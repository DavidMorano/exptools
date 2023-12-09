
/**************************************************************************/
/* PANELFEATURES Package    Release:  1.0    Release Date: 1/15/89        */
/*                          Provider: J. D. Iorio  (speedy!jdi)           */
/**************************************************************************/

// KNOBTYPES.H
//
//	Copyright (C) ATT 1987
//
// This header file defines the types of knobs derived from the
// generic knob class
// that will be used to define instruments for ALMMS
//
//   History:
//	J. D. Iorio	12/8/87		created
//


	// Note: these classes are friendly with class knob

///////////////////////////////////////////////////////////////////////////////
class FLTknob : public knob		// FLOATING POINT SINGLE KNOB
{

public:

		// constructors
	FLTknob(char *Name, char *Slab, float Hi, float Lo, float Dflt,
			int(*func)(panelfeature *));


		// destructor
	~FLTknob();
		// editor functions
	int write(ostream& ost, int level);
	char *setup(char *);
	void show(int, int);
	virtual int whattype() { return(FLT);}
	char *snap(char *);

};

///////////////////////////////////////////////////////////////////////////////
class FWFLTknob : public knob		// FIXED WIDTH FLT POINT ARRAY KNOB
{

public:

		// constructors
	FWFLTknob(char *Name, char *Slab, float Hi, float Lo, float Dflt,
			int(*func)(panelfeature *), int Width);


		// destructor
	~FWFLTknob();
		// editor functions
	int write(ostream& ost, int level);
	char *setup(char *);
	void show(int, int);
	virtual int whattype() { return(FWFLT);}
	char *snap(char *);

};

///////////////////////////////////////////////////////////////////////////////
class VWFLTknob : public knob		// VARIABLE WIDTH FLT POINT ARRAY KNOB
{

public:

		// constructors
	VWFLTknob(char *Name, char *Slab, float Hi, float Lo, float Dflt,
			int(*func)(panelfeature *), int Width,int Maxwidth);


		// destructor
	~VWFLTknob();
		// editor functions
	int write(ostream& ost, int level);
	char *setup(char *);
	void show(int, int);
	virtual int whattype() { return(VWFLT);}
	char *snap(char *);

};

///////////////////////////////////////////////////////////////////////////////
class INTknob : public knob		// INTEGER SINGLE KNOB
{

public:

		// constructors
	INTknob(char *Name, char *Slab, int Hi, int Lo, int Dflt,
			int(*func)(panelfeature *));


		// destructor
	~INTknob();
		// editor functions
	int write(ostream& ost, int level);
	char *setup(char *);
	void show(int, int);
	virtual int whattype() { return(INT);}
	char *snap(char *);

};

///////////////////////////////////////////////////////////////////////////////
class FWINTknob : public knob		// FIXED WIDTH INTEGER ARRAY KNOB
{

public:

		// constructors
	FWINTknob(char *Name, char *Slab, int Hi, int Lo, int Dflt,
			int(*func)(panelfeature *), int Width);


		// destructor
	~FWINTknob();
		// editor functions
	int write(ostream& ost, int level);
	char *setup(char *);
	void show(int, int);
	virtual int whattype() { return(FWINT);}
	char *snap(char *);

};

///////////////////////////////////////////////////////////////////////////////
class VWINTknob : public knob		// VARIABLE WIDTH INTEGER ARRAY KNOB
{

public:

		// constructors
	VWINTknob(char *Name, char *Slab, int Hi, int Lo, int Dflt,
			int(*func)(panelfeature *),int Width,int Maxwidth);


		// destructor
	~VWINTknob();
		// editor functions
	int write(ostream& ost, int level);
	char *setup(char *);
	void show(int, int);
	virtual int whattype() { return(VWINT);}
	char *snap(char *);

};

///////////////////////////////////////////////////////////////////////////////
class ENUMknob : public knob		// SINGLE ENUM KNOB
{
	char **labels;			// enum lables
	int   *vals;			// enum values
	int  numvals;

public:

		// constructors
	ENUMknob(char *Name, int Numlabs, char *Labels[], int *Vals, int Dflt,
			int(*func)(panelfeature *));


		// destructor
	~ENUMknob();

		// converters
		//   (ENUM val to INDEX)
	float value_of(float x);
		//   (ENUM val from INDEX)
	float value_for(float x);

	char *getlabel(float v);
	
		// editor functions
	int write(ostream& ost, int level);
	char *setup(char *);
	void show(int, int);
	virtual int whattype() { return(ENUM);}
	char *snap(char *);

};

