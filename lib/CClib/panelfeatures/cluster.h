
/**************************************************************************/
/* PANELFEATURES Package    Release:  1.0    Release Date: 1/15/89        */
/*                          Provider: J. D. Iorio  (speedy!jdi)           */
/**************************************************************************/

// CLUSTER.H
//
//	Copyright (C) ATT 1987
//
// This header file defines the functions for the derived class of
// panelfeatures called clusters
// that will be used to define instruments for ALMMS
//
//   History:
//	J. D. Iorio	12/8/87		created
//


class cluster : public panelfeature
{
	// Note: this class is friendly with class panelfeature

	int numchildren;	// number of children
	panelfeature **child;	// pointers to children

	void dont_allow() { errormsg(form(
	  "INVALID USAGE:   no operator>> for CLUSTER %s",
		getname()));}
public:

		// constructors
	cluster(char *Name, int(*func)(panelfeature *),
			panelfeature *pf1);

	cluster(char *Name, int(*func)(panelfeature *),
			panelfeature *pf1, panelfeature *pf2);

	cluster(char *Name, int(*func)(panelfeature *),
			panelfeature *pf1, panelfeature *pf2,
			panelfeature *pf3);

	cluster(char *Name, int(*func)(panelfeature *),
			panelfeature *pf1, panelfeature *pf2,
			panelfeature *pf3, panelfeature *pf4);

	cluster(char *Name, int(*func)(panelfeature *),
			panelfeature *pf1, panelfeature *pf2,
			panelfeature *pf3, panelfeature *pf4,
			panelfeature *pf5);

	cluster(char *Name, int(*func)(panelfeature *),
			panelfeature *pf1, panelfeature *pf2,
			panelfeature *pf3, panelfeature *pf4,
			panelfeature *pf5, panelfeature *pf6);

	cluster(char *Name, int(*func)(panelfeature *),
			panelfeature *pf1, panelfeature *pf2,
			panelfeature *pf3, panelfeature *pf4,
			panelfeature *pf5, panelfeature *pf6,
			panelfeature *pf7);

	cluster(char *Name, int(*func)(panelfeature *),
			panelfeature *pf1, panelfeature *pf2,
			panelfeature *pf3, panelfeature *pf4,
			panelfeature *pf5, panelfeature *pf6,
			panelfeature *pf7, panelfeature *pf8);

	cluster(char *Name, int(*func)(panelfeature *),
			panelfeature *pf1, panelfeature *pf2,
			panelfeature *pf3, panelfeature *pf4,
			panelfeature *pf5, panelfeature *pf6,
			panelfeature *pf7, panelfeature *pf8,
			panelfeature *pf9);

	cluster(char *Name, int(*func)(panelfeature *),
			panelfeature *pf1, panelfeature *pf2,
			panelfeature *pf3, panelfeature *pf4,
			panelfeature *pf5, panelfeature *pf6,
			panelfeature *pf7, panelfeature *pf8,
			panelfeature *pf9, panelfeature *pfA);


		// destructor
	~cluster();



		// graphic functions

	void show(int x=0, int y=0);
	void resize();

	        // edit functions
	panelfeature *find(int X, int Y);
	panelfeature *find(char *Name);
	int write(ostream& ost, int level);

		// misc functions
	void set_this_module(void *);
	char * setup(char *);
	int whattype() { return(CLUST);}
	panelfeature *getchild(int i) {if(i<numchildren)return(child[i]);else return((panelfeature *)NULL);}

	char * snap(char *);
	int getnumchild() {return(numchildren);}
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
	virtual panelfeature& operator<<(char *p)
		{*p =(*p); dont_allow(); return(*this);}

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
	virtual panelfeature& operator>>(char *p)
		{*p =(*p); dont_allow(); return(*this);}

};
