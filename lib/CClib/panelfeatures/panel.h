
/**************************************************************************/
/* PANELFEATURES Package    Release:  1.0    Release Date: 1/15/89        */
/*                          Provider: J. D. Iorio  (speedy!jdi)           */
/**************************************************************************/

// PANEL.H
//
//	Copyright (C) ATT 1987
//
// This header file defines the functions for the class of
// panel which forms the root node of an instrument tree
// built from "panelfeature" objects.
// It will be used to define instruments for ALMMS
//
//   History:
//	J. D. Iorio	12/14/87	created
//


class panel : public panelfeature
{
	char *instrname;	// name used to derive filenames from
	cluster  *root;		// the root cluster of the instrument

public:

		// constructor
//	panel(char *Name, cluster *Root, instrument *ins);
	panel(char *Name, cluster *Root, void *ins);


		// destructor
	~panel();

		// misc. functions

	void show(int x=0, int y=0);		// display the instrument

//	void edit();		// main editor function

	int write(ostream& FP = cout, int level = 0);	// sub-editor functions
//	int read(ostream& FP = cin);
	char * setup(char *);			// programmed setup
	int user_setup();			// interactive setup

	panelfeature *find(int X, int Y); 	// locate a node
	panelfeature *find(char *Name);

	void getXY(int& X, int& Y)
			 { int T,U; (*root).getXY(T,U); X=T; Y=U; }
	void setXY(int X, int Y)   {(*root).setXY(X,Y);}
	void getXYsize(int& X, int& Y)
			 { int T,U; (*root).getXYsize(T,U); X=T; Y=U; }
	void setXYsize(int X, int Y)   {(*root).setXYsize(X,Y);}
	void set_this_module(void *)   {;}
	virtual int ispanel() { return(TRUE); }
	virtual int whattype() { return(PANEL);}
	int getnumchild() { return(1); }
	panelfeature *getchild(int i) {if(i==0)return(root);else return(0);}
	char * snap(char *);
};
