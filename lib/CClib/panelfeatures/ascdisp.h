
/**************************************************************************/
/* PANELFEATURES Package    Release:  1.0    Release Date: 1/15/89        */
/*                          Provider: J. D. Iorio  (speedy!jdi)           */
/**************************************************************************/
// ASCDISP.H
//
//      Copyright (C) ATT 1988
//
// This header file defines the ASCII type of displays derived from the
// generic pf class
// that will be used to define instruments for ALMMS
//
//   History:
//      J. D. Iorio     6/16/88         created
//


        // Note: this class is friendly with class pf

///////////////////////////////////////////////////////////////////////////////
class ASCIIdisp : public panelfeature           //  ASCII DISPLAY
{
        int numcol;             // number of displayable character columns
        int numrow;             // number of lines 
	char *tempstring;	// local string for buffering commands

        void dont_allow() { errormsg(form(
          "INVALID USAGE:  op>> or op<<(numeric) used for ASCIIdisp %s",                getname()));}
public:

                // constructor
        ASCIIdisp(char *Name, int Rows, int Cols);


                // destructor
        ~ASCIIdisp();

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
        virtual panelfeature& operator>>(char *p)
                {*p =(*p); dont_allow(); return(*this);}

                // editor functions
        int write(ostream& ost, int level);
        void show(int, int);
        void clr_line();
        void clr_screen();
        void home();
        void move_to(int X, int Y);
        void trap();
        void untrap();
        char *setup(char *);
        int whattype() { return(ASCIIDISP);}
        char *snap(char *);

};
