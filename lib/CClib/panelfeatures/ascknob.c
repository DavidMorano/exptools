
/**************************************************************************/
/* PANELFEATURES Package    Release:  1.0    Release Date: 1/15/89        */
/*                          Provider: J. D. Iorio  (speedy!jdi)           */
/**************************************************************************/

// ASCKNOB.C
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

#include <ctype.h>
#include "pf.h"
#include "proto.h"

extern proto_stream pout;

///////////////////////////////////////////////////////////////////////////////
//class ASCIIknob : public pf		// SINGLE ASCII KNOB

		// constructors
ASCIIknob::ASCIIknob(char *Name, char *Question, char *Verify, char *Dflt,
			int(*func)(panelfeature *), int Width) :
		(Name, 0, 0, 0, 0, func)
{

						// allocate storage
	question = new char[(strlen(Question)+1)];
	int len = strlen(Dflt) + 1;
	dfltans = new char[len];
	if(Width < len)
		Width = len;
	width = Width;
	answer = new char[width];
	vspec = new char[(strlen(Verify)+1)];

		                  	 	// copy values into knob
	strcpy(question, Question);
	strcpy(dfltans, Dflt);
	strcpy(answer, Dflt);
	strcpy(vspec, Verify);

						// setup the verify strings
	char *tempv[30];
	char *bp, *ep, temp;

	for (numverify=0,bp=Verify, ep=Verify; numverify < 30 ; ep++)
	{
		if((*ep == '|') || ((*ep == '\0') && (numverify != 0)))
		{
			temp = *ep;
			*ep = '\0';
			tempv[numverify] = new char[(strlen(bp)+1)];
			strcpy(tempv[numverify], bp);
			
			numverify++;
			bp = ep+1;
			*ep = temp;
		}

		if(*ep == '\0')
			break;
	}

	if (numverify == 0)
		vtypeflag = NOVERIFY;
	else
	{
		vtypeflag = STRINGVERIFY;
		verify = new char *[numverify];
		for(int i=0; i<numverify; i++)
			verify[i] = tempv[i];
	}


	updateflag = MAJOR;
	dofunc(this);

}


ASCIIknob::ASCIIknob(char *Name, char *Question, float Max, float Min,
			 char *Dflt, int(*func)(panelfeature *),int Width) :
		(Name, 0, 0, 0, 0, func)
{

						// allocate storage
	question = new char[(strlen(Question)+1)];
	int len = strlen(Dflt) + 1;
	dfltans = new char[len];
	if(Width < len)
		Width = len;
	width = Width;
	answer = new char[width];

		                  	 	// copy values into knob
	strcpy(question, Question);
	strcpy(dfltans, Dflt);
	strcpy(answer, Dflt);
	vmin = Min;
	vmax = Max;
	width = Width;

	vtypeflag = FLIMITVERIFY;

	updateflag = MAJOR;
	dofunc(this);

}

ASCIIknob::ASCIIknob(char *Name, char *Question, int Max, int Min,
			 char *Dflt, int(*func)(panelfeature *),int Width) :
		(Name, 0, 0, 0, 0, func)
{

						// allocate storage
	question = new char[(strlen(Question)+1)];
	int len = strlen(Dflt) + 1;
	dfltans = new char[len];
	if(Width < len)
		Width = len;
	width = Width;
	answer = new char[width];

		                  	 	// copy values into knob
	strcpy(question, Question);
	strcpy(dfltans, Dflt);
	strcpy(answer, Dflt);
	vmin = (float)Min;
	vmax = (float)Max;
	width = Width;

	vtypeflag = ILIMITVERIFY;

	updateflag = MAJOR;
	dofunc(this);

}


		// destructor
ASCIIknob::~ASCIIknob()
{
	delete question;
	delete dfltans;
	delete answer;

	if( vtypeflag == STRINGVERIFY )
	{
		for (int i=0; i<numverify; i++)
		{
			delete verify[i];
		}
		delete verify;
	}
}

///////////////////////////////////////////////////////////////////////////
// 

int ASCIIknob::write(ostream& FP, int level)
{
	int t;
	FP << level;

	FP << ";ASCIIknob;1;1;";


	if (panelfeature::write(FP,level) != SUCCESS)
	{
		errormsg(form("[ASCIIknob.write] %s failed",getname()));
		return(FAILURE);
	}

	FP << "Response Width: " << width <<" characters;";
	FP << "Question: " << question << ";";
	FP << "Default: " << dfltans << ";CURRENT: "<<answer << ";";
	if( vtypeflag == STRINGVERIFY )
	{
		FP << "CHOICES : ";
		for(t=0; t<numverify; t++)
		{
			if (t>0)
				FP << " | ";
			FP << verify[t];
		}
		FP << ";\n";
	}
	else if( vtypeflag == ILIMITVERIFY )
	{
	       FP<<"INTEGER RESPONSE BETWEEN "<<vmin<<" and "<<vmax<<";\n";
	}
	else if( vtypeflag == FLIMITVERIFY )
	{
	       FP<<"FLOATING PT. RESPONSE BETWEEN "<<vmin<<" and "<<vmax<<";\n";
	}
	else
	       FP << "ACCEPTS ANY RESPONSE;\n";

	return(SUCCESS);
}

char *ASCIIknob::setup(char *s)
{

	char *cp, *ep;
	char hold;

	// strip any leading white space
	for( ; ((isspace(*s)) ||
		(*s == '=')   ||
		(*s == ',')   ||
		(*s == '\0') ); s++)
	{
		if (*s == NULL)
		{
			errormsg("ASCIIknob setup: NULL found");
			return(NULL);
		}
	}

	// find the end of the string for this knob
	for( cp=s; 1; cp++ )
	{
		if( (*cp == ';') || (*cp == '\0'))
		{
			// backup to last good character
			for( ep=cp; isspace(*(ep-1)); ep--);

			break;
		}
	}

	// do the assignment
	hold = *ep;
	*ep = '\0';
	
	(*this) << s;
	*ep = hold;

	return(cp+1);
}

void ASCIIknob::show(int px, int py)
{

	int dummy;
	dummy = px;
	dummy = py;

	if (Usermode != INTERACTIVE )
		return;

	if (updateflag == MAJOR)
	{
		pout.put(GIASCKNOB);
		pout << form("%s;%s;",name,officialname);
		pout << "%s;";			// format
		pout << form("%d;",attrib); 	// attributes flag
		pout << "0;";			// numchildren
		pout << "1;";			// numvalues
		pout << form("%d;",width); 	// maxnumvalues 
		pout << "0;";			// style

		pout << question << ";";
	
		if( vtypeflag == STRINGVERIFY )
		{
			pout << "{ "<<vspec<<" };";
		}
		else if( vtypeflag == ILIMITVERIFY )
		{
			pout << form("{ %d ... %d };", (int)vmin, (int)vmax);
		}
		else if( vtypeflag == FLIMITVERIFY )
		{
			pout << form("{ %f ... %f };", vmin, vmax);
		}
		else  // no verification
		{
			pout << ";";
		}

		pout << answer << ";\n";

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
		pout << form ("%c\n", GICHG_VALUE);
		pout << form ("%s", getpath());
		pout << form ("%s;", officialname);
		pout << form ("1;%s;\n", answer);  // and numvalues
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

panelfeature& ASCIIknob::operator<< (char *s)
{
	if(strlen(s) > width)
	{
		errormsg( form("Invalid assignment - knob %s; string too long",
			getname()));
		strcpy(answer, dfltans);
	}
	else if( vtypeflag == STRINGVERIFY )
	{
		for(int t=0; t<numverify; t++)
		{
			if (strcmp(s, verify[t]) == 0)
			{
				strcpy(answer, s);
				break;
			}
		}
		if(t == numverify)
		{
			errormsg(
			    form("Invalid assignment - knob %s; try one of {%s}",
				getname(),vspec));
			strcpy(answer, dfltans);
		}
	}
	else if( vtypeflag == ILIMITVERIFY )
	{
		int i;
		if(sscanf(s,"%d",&i) == 0)
		{
			errormsg(
			 form("Invalid assignment - knob %s; try integer {%d...%d}",
				getname(), (int)vmin, (int)vmax));
			strcpy(answer, dfltans);
		}
		else if( (i<(int)vmin) || (i>(int)vmax) )
		{
			errormsg(
			 form("Invalid range - knob %s; try integer {%d...%d}",
				getname(),(int)vmin, (int)vmax));
			strcpy(answer, dfltans);
		}
		else 
		{
			sprintf(answer,"%d",i);
		}
		
	}
	else if( vtypeflag == FLIMITVERIFY )
	{
		float f;
		if(sscanf(s,"%f",&f) == 0)
		{
			errormsg(
			 form("Invalid assignment - knob %s; try float {%f...%f}",
				getname(), vmin, vmax));
			strcpy(answer, dfltans);
		}
		else if( (f<vmin) || (f>vmax) )
		{
			errormsg(
			 form("Invalid range - knob %s; try float {%f...%f}",
				getname(), vmin, vmax));
			strcpy(answer, dfltans);
		}
		else
			sprintf(answer,"%g",f);
	}
	else	/* type NOVERIFY */
		strcpy(answer, s);


	if( updateflag != MAJOR )
	{
		updateflag = VALUE_CHANGE;
		show(parentX(),parentY());
	}
	doallfunc(this);
	return(*this);
}

panelfeature& ASCIIknob::operator>> (char *s)
{
	strcpy(s,answer);
	return(*this);
}
