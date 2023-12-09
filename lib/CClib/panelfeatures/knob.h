
/**************************************************************************/
/* PANELFEATURES Package    Release:  1.0    Release Date: 1/15/89        */
/*                          Provider: J. D. Iorio  (speedy!jdi)           */
/**************************************************************************/

// KNOB.H
//
//	Copyright (C) ATT 1987
//
// This header file defines the interface to the derived class of
// panelfeatures called knobs
// that will be used to define an instrument for ALMMS
//
//   History:
//	J. D. Iorio	12/3/87		created
//


enum knobstyle { TOGGLE, SLIDE, ROTARY };

class knob : public panelfeature
{
    // Note: this class is friendly with class panelfeature
	friend class display;

	float highlimit;		// upper limit of knob range 
	float lowlimit;			// lower limit of knob range 
	float dfault;			// default value (init. & out-of-range)
	float stepval;			// data for labeling display
	knobstyle   style;		// knob style for display
	char *format;			// format for display
	char *scalelabel;		// name of units represented

public:
	knob(char *Name, int X, int Y, knobstyle Style, char *Slabel,
		     float Hilimit, float Lolimit, float Dfault,
		     int(*func)(panelfeature *),int width);	// constructor
	~knob();						// destructor

	virtual void queryknob();		// interactive read
	virtual int changesize(int tosize);	// for array knob sizing
	virtual void resetknob();		// set knob to default
						// without calling function

    // assignment operator overloading ////////////////////////////////
	virtual panelfeature& operator<<(float *f);
	virtual panelfeature& operator<<(float f);
	virtual panelfeature& operator<<(int *i);
	virtual panelfeature& operator<<(int i);
	virtual panelfeature& operator<<(panelfeature *p);
	virtual panelfeature& operator<<(panelfeature p);

    // assignment operator overloading ////////////////////////////////
	virtual panelfeature& operator>>(float *f);
	virtual panelfeature& operator>>(float& f);
	virtual panelfeature& operator>>(int& i);
	virtual panelfeature& operator>>(int *i);
	virtual panelfeature& operator>>(panelfeature& p);
	virtual panelfeature& operator>>(panelfeature *p);

	// a little help for ENUM type knobs (these are dummys for all others)
	virtual float value_of(float x);
	virtual float value_for(float x);

	// some graphics things:
	virtual void show(int x=0,int y=0);
	virtual char *getlabel(float v);
	void changefmt(char *newfmt);
	char *getfmt()	{ return(format);}
	virtual int write(ostream& ost, int level);
	virtual char * setup(char *);
	float getmin() { return(lowlimit); }
	float getmax() { return(highlimit); }
	float getdflt() { return(dfault); }
	char *getscalelabel() { return(scalelabel); }
	virtual char *snap(char *);
};

