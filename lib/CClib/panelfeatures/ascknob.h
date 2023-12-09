
/**************************************************************************/
/* PANELFEATURES Package    Release:  1.0    Release Date: 1/15/89        */
/*                          Provider: J. D. Iorio  (speedy!jdi)           */
/**************************************************************************/

// ASCKNOB.H
//
//	Copyright (C) ATT 1988
//
// This header file defines the ASCII type of knobs derived from the
// generic pf class
// that will be used to define instruments for ALMMS
//
//   History:
//	J. D. Iorio	6/7/88		created
//


	// Note: this class are friendly with class pf

#define NOVERIFY 	0
#define STRINGVERIFY	1
#define ILIMITVERIFY 	2
#define FLIMITVERIFY 	3

///////////////////////////////////////////////////////////////////////////////
class ASCIIknob : public panelfeature		// SINGLE ASCII KNOB
{
	char *question;			// current question string
	char *dfltans;			// default answer string
	char *answer;			// current answer string
	char *vspec;			// original verification string
	char **verify;			// parsed verification strings
	int  numverify;			// number of verify strings
	int  vtypeflag;			// type of verification 
	float vmin;			// numeric verify range
	float vmax;
	int width;			// width of response

	void dont_allow() { errormsg(form(
	  "INVALID USAGE:  operator>> works only with strings for ASCIIknob %s",
		getname()));}
public:

		// constructors
	ASCIIknob(char *Name, char *Question, char *Verify, char *Dflt,
			int(*func)(panelfeature *), int Width=40);

	ASCIIknob(char *Name, char *Question, float Max, float Min, char *Dflt,
			int(*func)(panelfeature *), int Width=40);

	ASCIIknob(char *Name, char *Question, int Max, int Min, char *Dflt,
			int(*func)(panelfeature *), int Width=40);



		// destructor
	~ASCIIknob();

    // assignment operator overloading ////////////////////////////////
	virtual panelfeature& operator<<(float *f)
		{*f =(*f); dont_allow(); return(*this);}
	virtual panelfeature& operator<<(float f) 
		{f =(f); dont_allow(); return(*this);}
	virtual panelfeature& operator<<(int *i)
		{*i =(*i); dont_allow(); return(*this);}
	virtual panelfeature& operator<<(int i)
		{i =(i); dont_allow(); return(*this);}
	virtual panelfeature& operator<<(panelfeature *p)
		{ int dummy=p->whattype(); dont_allow(); return(*this);}
	virtual panelfeature& operator<<(panelfeature p)
		{ int dummy=p.whattype(); dont_allow(); return(*this);}
	virtual panelfeature& operator<<(char *p);

    // assignment operator overloading ////////////////////////////////
	virtual panelfeature& operator>>(float *f)
		{*f =(*f); dont_allow(); return(*this);}
	virtual panelfeature& operator>>(float& f)
		{f =(f); dont_allow(); return(*this);}
	virtual panelfeature& operator>>(int& i)
		{i =(i); dont_allow(); return(*this);}
	virtual panelfeature& operator>>(int *i)
		{*i =(*i); dont_allow(); return(*this);}
	virtual panelfeature& operator>>(panelfeature& p)
		{int dummy=p.whattype(); dont_allow(); return(*this);}
	virtual panelfeature& operator>>(panelfeature *p)
		{int dummy=p->whattype(); dont_allow(); return(*this);}
	virtual panelfeature& operator>>(char *p);

		// editor functions
	int write(ostream& ost, int level);
	char *setup(char *);
	void show(int, int);
	int whattype() { return(ASCIIKNOB);}
	char *snap(char *);

};

