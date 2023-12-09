
/**************************************************************************/
/* PANELFEATURES Package    Release:  1.0    Release Date: 1/15/89        */
/*                          Provider: J. D. Iorio  (speedy!jdi)           */
/**************************************************************************/

// DISPLAY.H
//
//	Copyright (C) ATT 1987
//
// This header file defines the interface to the derived class of
// panelfeatures called displays
// that will be used to define an instrument for ALMMS
//
//   History:
//	J. D. Iorio	12/3/87		created
//


enum displaystyle { DIGITAL, PLOT, BINARY };

class display : public panelfeature
{
    // Note: this class is friendly with class panelfeature
    //	     and class knob


	int numdimensions;			// format of data
	int   maxdata;			// amount of points[numdim] to allocate
	float **ddata;			// storage for data
	char **dlabels;			// storage for axes labels
	char **dscalelabels;		// storage for axis unit labels
	float *min;			// axes limits
	float *max;
	int   numdata;			// number of valid points
	displaystyle   style;		// display style for display
	char **format;			// format for display labels
	char showflag;			// used for private graphics

    // some private functions
	void dont_allow() { errormsg(form(
	           "INVALID USAGE:  operator>> for display %s",getname()));}
	void dont_show() { showflag = FALSE; }

	void initdisplay(int Dim,
	        char *xn, char *xs, float xmn, float xmx, char *xfm,
		char *yn, char *ys, float ymn, float ymx, char *yfm,
		char *zn, char *zs, float zmn, float zmx, char *zfm,
		int Maxsz);

	void doallfunc(panelfeature *t);
//////////////////////////////////////////////////////////////////////////////

#define NOAXIS (char *)NULL,(char *)NULL,0.0,0.0,(char *)NULL
		// name,     scalelabel, min,max, format
#define DFMT "%-8.2f"

#define XAXIS 0
#define YAXIS 1
#define ZAXIS 2

public:
    // 1 dimension
	display(char *Name, char *Xname, char *Xslab,
			 float Xmin, float Xmax, int Maxsize);

	display(char *Name, knob& Xknob, int Maxsize);

    // 2 dimension
	display(char *Name, char *Xname, char *Xslab, float Xmin, float Xmax,
		 char *Yname, char *Yslab, float Ymin, float Ymax, int Maxsize);

	display(char *Name, knob& Xknob,
		 char *Yname, char *Yslab, float Ymin, float Ymax, int Maxsize);

	display(char *Name, char *Xname, char *Xslab, float Xmin, float Xmax,
		 knob& Yknob, int Maxsize);

	display(char *Name, knob& Xknob, knob& Yknob, int Maxsize);

    // 3 dimension
	display(char *Name, char *Xname, char *Xslab, float Xmin, float Xmax,
		 char *Yname, char *Yslab, float Ymin, float Ymax,
		 char *Zname, char *Zslab, float Zmin, float Zmax, int Maxsize);

	display(char *Name, knob& Xknob,
		 char *Yname, char *Yslab, float Ymin, float Ymax,
		 char *Zname, char *Zslab, float Zmin, float Zmax, int Maxsize);

	display(char *Name, char *Xname, char *Xslab, float Xmin, float Xmax,
		 knob& Yknob,
		 char *Zname, char *Zslab, float Zmin, float Zmax, int Maxsize);

	display(char *Name, knob& Xknob,
		 knob& Yknob,
		 char *Zname, char *Zslab, float Zmin, float Zmax, int Maxsize);

	display(char *Name, char *Xname, char *Xslab, float Xmin, float Xmax,
		 char *Yname, char *Yslab, float Ymin, float Ymax,
		 knob& Zknob, int Maxsize);

	display(char *Name, knob& Xknob,
		 char *Yname, char *Yslab, float Ymin, float Ymax,
		 knob& Zknob, int Maxsize);

	display(char *Name, char *Xname, char *Xslab, float Xmin, float Xmax,
		 knob& Yknob,
		 knob& Zknob, int Maxsize);

	display(char *Name, knob& Xknob,
		 knob& Yknob,
		 knob& Zknob, int Maxsize);

////////////////////////////////////////////////////////////////////////
	~display();						// destructor
////////////////////////////////////////////////////////////////////////


    // assignment operator overloading ////////////////////////////////
	virtual panelfeature& operator<<(float *f);
	virtual panelfeature& operator<<(float f);
	virtual panelfeature& operator<<(int *i);
	virtual panelfeature& operator<<(int i);
	virtual panelfeature& operator<<(panelfeature *p);
	virtual panelfeature& operator<<(panelfeature p);

    // assignment operator overloading ////////////////////////////////
	virtual panelfeature& operator>>(float *f) 
				{*f=(*f);dont_allow();return(*this);}
	virtual panelfeature& operator>>(float& f) 
				{f=f;dont_allow();return(*this);}
	virtual panelfeature& operator>>(int& i) 
				{i=i;dont_allow();return(*this);}
	virtual panelfeature& operator>>(int *i) 
				{*i=(*i);dont_allow();return(*this);}
	virtual panelfeature& operator>>(panelfeature& p) 
				{p.show(0,0);dont_allow();return(*this);}
	virtual panelfeature& operator>>(panelfeature *p) 
				{(*p).show(0,0);dont_allow();return(*this);}


	// some graphics things:
	virtual void show(int x=0, int y=0);
	virtual void clear();
	virtual char *getlabel(int axis,float v);
	void changefmt(int axis,char *newfmt);
	void changeaxis(int axis, char *lab, char *slab, float mn, float mx);
	char *getfmt(int axis)	{ return(format[axis]);}
	void shiftdata();
	virtual int write(ostream& ost, int level);
	virtual char *setup(char *);
	int whattype() { return(DISPLAY);}
	char *snap(char *);
};

