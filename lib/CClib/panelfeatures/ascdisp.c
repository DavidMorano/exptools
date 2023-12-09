
/**************************************************************************/
/* PANELFEATURES Package    Release:  1.0    Release Date: 1/15/89        */
/*                          Provider: J. D. Iorio  (speedy!jdi)           */
/**************************************************************************/

// ASCDISP.C
//
//	Copyright (C) ATT 1988
//
// This src code file defines the ASCII type of displays derived from the
// generic pf class
// that will be used to define instruments for ALMMS
//
//   History:
//	J. D. Iorio	6/16/88		created
//

#include <ctype.h>
#include "pf.h"
#include "proto.h"

extern proto_stream pout;
extern void set_term_almms();
extern void reset_term_almms();

///////////////////////////////////////////////////////////////////////////////
//class ASCIIdisp : public pf		// ASCII display

		// constructor
ASCIIdisp::ASCIIdisp(char *Name, int Rows, int Cols) :
		(Name, 0, 0, 0, 0, NULLFUNC)
{

	numcol = Cols;
	numrow = Rows;

	if(numcol < 50)
		tempstring = new char[50];
	else
		tempstring = new char[numcol+1];

	updateflag = MAJOR;

}

		// destructor
ASCIIdisp::~ASCIIdisp()
{

	delete tempstring;
}

///////////////////////////////////////////////////////////////////////////
// 

int ASCIIdisp::write(ostream& FP, int level)
{
	FP << level;
	FP << ";ASCIIdisp;1;0;";


	if (panelfeature::write(FP,level) != SUCCESS)
	{
		errormsg(form("[ASCIIdisp.write] %s failed",getname()));
		return(FAILURE);
	}

	FP << " - " << numcol <<" characters by " << numrow << " lines;\n";

	return(SUCCESS);
}

char *ASCIIdisp::setup(char *s)
{
	errormsg(form("SET-UP ERROR: ASCIIdisp fn() called: %s", getname()));
	*s = NULL;
	return(NULL);
}

void ASCIIdisp::show(int px, int py)
{

	int dummy;
	dummy = px;
	dummy = py;

	if (Usermode != INTERACTIVE )
		return;

	if (updateflag == MAJOR)
	{
		pout.put(GIASCDISP);
		pout << form("%s;%s;",name,officialname);
		pout << "%s;";			// format
		pout << form("%d;",attrib); 	// attributes flag
		pout << "0;";			// numchildren
		pout << form("%d;",numcol); 	// numvalues 
		pout << form("%d;",numrow); 	// maxnumvalues 
		pout << "0;\n";			// style

		updateflag = UP_TO_DATE;
		pout.flush();
	}

	if (updateflag == NAME_CHANGE)
	{
		pout << form ("%c\n", GICHG_NAME);
		pout << form ("%s", getpath());
		pout << form ("%s;%s;\n", officialname, name);
		updateflag = UP_TO_DATE;
		pout.flush();
	}

	if (updateflag == LABEL_CHANGE)
	{
		updateflag = UP_TO_DATE;
		pout.flush();
	}

	if (updateflag == VALUE_CHANGE)
	{
		pout << form ("%c\n", GIUPDATE_DISP);
		pout << form ("%s", getpath());
		pout << form ("%s;", officialname);
		pout << form ("%s\n", tempstring);  // and numvalues
		updateflag = UP_TO_DATE;
		pout.flush();
	}

	if (updateflag == ATTRIB_CHANGE)
	{
		pout << form ("%c\n", GICHG_ATTRIB);
		pout << form ("%s", getpath());
		pout << form ("%s;", officialname);
		pout << form ("%d;\n", attrib);
		updateflag = UP_TO_DATE;
		pout.flush();
	}
}

panelfeature& ASCIIdisp::operator<< (char *s)
{
	if(strlen(s) > numcol)
	{
		errormsg( form("Line truncated - knob %s; string too long",
			getname()));
		s[numcol] = '\0';
	}

	strcpy(tempstring, s);


	if(updateflag != MAJOR)
	{
		updateflag = VALUE_CHANGE;
		show(parentX(),parentY());
	}
	return(*this);
}

//////////////////////////////////
void ASCIIdisp::clr_line()
{

	strcpy(tempstring,"!!CLRL!!");
	if(updateflag != MAJOR)
	{
		updateflag = VALUE_CHANGE;
		show(parentX(),parentY());
	}
}


void ASCIIdisp::clr_screen()
{

	strcpy(tempstring,"!!CLRS!!");
	if(updateflag != MAJOR)
	{
		updateflag = VALUE_CHANGE;
		show(parentX(),parentY());
	}
}


void ASCIIdisp::home()
{

	strcpy(tempstring,"!!HOME!!");
	if(updateflag != MAJOR)
	{
		updateflag = VALUE_CHANGE;
		show(parentX(),parentY());
	}
}


void ASCIIdisp::move_to(int col, int row)
{

	strcpy(tempstring,form("!!MOVE!!%d;%d;", col, row));
	if(updateflag != MAJOR)
	{
		updateflag = VALUE_CHANGE;
		show(parentX(),parentY());
	}
}


void ASCIIdisp::trap()
{

	strcpy(tempstring,"!!TRAP!!");
	if(updateflag != MAJOR)
	{
		updateflag = VALUE_CHANGE;
		show(parentX(),parentY());
	}
	reset_term_almms();
}


void ASCIIdisp::untrap()
{

	if(updateflag != MAJOR)
	{
		cout << "!!UNTR!!\n";
		set_term_almms();
	}
}





