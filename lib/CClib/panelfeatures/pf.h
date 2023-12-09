
/**************************************************************************/
/* PANELFEATURES Package    Release:  1.0    Release Date: 1/15/89        */
/*                          Provider: J. D. Iorio  (speedy!jdi)           */
/**************************************************************************/
// PANELFEATURE.H
//
//	Copyright (C) ATT 1987
//
// This header file defines the interface to the panel features
// that will be used to define an instrument for ALMMS
//
//   History:
//	J. D. Iorio	12/2/87		created
//


#include <stream.h>
#include <string.h>
#include "screen.h"
#include "giproto.h"
#include "pfgraphics.h"
#include "enumhelp.h"

#define TRUE 1
#define FALSE 0

#define SUCCESS 0
#define FAILURE -1

#define PANEL 1
#define CLUST 2
#define DISPLAY 3
#define ENUM 4
#define INT 4
#define FLT 5
#define FWINT 6
#define FWFLT 7
#define VWINT 8
#define VWFLT 9
#define ASCIIKNOB 10
#define ASCIIDISP 11



//////////////////////////////////////////////////////
// attach GLOBAL USER MODE indicator 
#define INTERACTIVE 0
#define PROGRAM	    1
extern int Usermode;

class panelfeature
{
    friend class panel;
    friend class knob;
    friend class cluster;
    friend class display;
    friend class INTknob;
    friend class FWINTknob;
    friend class VWINTknob;
    friend class FLTknob;
    friend class FWFLTknob;
    friend class VWFLTknob;
    friend class ENUMknob;
    friend class ASCIIknob;
    friend class ASCIIdisp;

	char *name;		// name of the panel feature
	char *officialname;	// tag for panel editing


	void *this_module;	// pointer to the instrument containing this pf
				//  note: could be null;
	int  xloc;		// North West corner and plotting info
	int  yloc;
	int  xsize;
	int  ysize;
	int  attrib;		// misc attributes
	float *value;		// data value associated with this panelfeature
	int  intflag;		// TRUE indicates truncate fraction part
	int maxnumvalues;	// maximum amount of data
	int numvalues;		// current amount of data 
	int lastfilled;		// last filled item (for scalor assign of array)
	int lastread;		// last read item (for scalor read of array)
	int  (*handler)(panelfeature *);	// action function for node
	panelfeature *parent;	// pointer to parent node

	int updateflag;		// a graphics thing
	
//private functions:
			  // perform this handler function only 
	virtual void dofunc(panelfeature *pf);  
			  // perform the handler func "walk"
	virtual void doallfunc(panelfeature *pf);

	void dont_allow() { errormsg(form(
	           "INVALID USAGE: operator>> with string arg: %s",getname()));}

public:
	panelfeature(char *Name, int X, int Y, int xSize, int ySize,
		     int(*func)(panelfeature *));		// constructor
	~panelfeature();					// destructor

    // plot functions
	virtual void show(int x=0, int y=0);		
	virtual int  parentX();		
	virtual int  parentY();		
	virtual void init_attribute(int a);  // used in constructors only
	virtual void set_attribute(int a);   // used in action functions only
	virtual void clr_attribute(int a);	// action func only
	virtual void tog_attribute(int a);	// action func only
	virtual int test_attribute(int a);	// either
	virtual int get_attribute();		// either

    // edit functions
	virtual panelfeature *find(int X, int Y);
	virtual panelfeature *find(char *Name);
	virtual int write(ostream& ost, int level);
	virtual char * setup(char *);

    // misc. functions;
	virtual panelfeature *getparent() { return(parent); }
	virtual panelfeature *getchild(int) { return((panelfeature *)NULL); }
	virtual int getnumchild() { return(0); }
	virtual char * getname()  { return(name); }
	virtual int getsize()     { return(numvalues); }
	virtual int getmaxsize()     { return(maxnumvalues); }
	virtual void setintflag(int flg);
	virtual void getXY(int& X, int& Y) { X=xloc; Y=yloc; }
	virtual void setXY(int X, int Y);
	virtual void getXYsize(int& X, int& Y) { X=xsize; Y=ysize; }
	virtual void setXYsize(int X, int Y);
	virtual void resize() { ; }
	virtual void touch() { ; }
	virtual void *get_this_module();
	virtual void set_this_module(void *);
	virtual int ispanel() { return(FALSE); }
	virtual char *getpath();
	virtual int whattype() { return(-1);}
	virtual char *snap(char *);

    // assignment operator overloading ////////////////////////////////
	virtual panelfeature& operator<<(float *f);
	virtual panelfeature& operator<<(float f); 
	virtual panelfeature& operator<<(int *i);
	virtual panelfeature& operator<<(int i);
	virtual panelfeature& operator<<(panelfeature *p);
	virtual panelfeature& operator<<(panelfeature p);
	virtual panelfeature& operator<<(char *p)
		{ *p = (*p);dont_allow(); return(*this);}

    // assignment operator overloading ////////////////////////////////
	virtual panelfeature& operator>>(float *f);
	virtual panelfeature& operator>>(float& f);
	virtual panelfeature& operator>>(int& i);
	virtual panelfeature& operator>>(int *i);
	virtual panelfeature& operator>>(panelfeature& p);
	virtual panelfeature& operator>>(panelfeature *p);
	virtual panelfeature& operator>>(char *p)
		{*p = (*p); dont_allow(); return(*this);}

#define QUERY	(panelfeature *) NULL
#define NULLFUNC NULL
};


#include "knob.h"
#include "cluster.h"
#include "display.h"
#include "knobtypes.h"
#include "panel.h"
#include "ascknob.h"
#include "ascdisp.h"

