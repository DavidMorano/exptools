
/**************************************************************************/
/* PANELFEATURES Package    Release:  1.0    Release Date: 1/15/89        */
/*                          Provider: J. D. Iorio  (speedy!jdi)           */
/**************************************************************************/

// PFWRITE.C
//
//	Copyright (C) ATT 1987
//
// This file defines the sub-editor function write(ostream&)
// for the set of "panelfeature" objects.
// It will be used to define instruments for ALMMS
//
//   History:
//	J. D. Iorio	12/14/87	created
//

#include "pf.h"
#include <ctype.h>

////////////////////////////////////////////////////////////////////////////
int panel::write(ostream& FP,int level)		// write an instrument file
{
	char *cp;


    	    // construct the file name
		char *logname;
		char filename[40];
		char tfilename[40];

		extern char *getlogin();

		if ( (logname=getlogin()) == NULL)
		{
			errormsg("[panel.write] Can not get logname");
			return(FAILURE);
		}
		
		
		// build a filename
		strcpy(tfilename,root->getname());
		for(cp=tfilename; *cp != '\0'; cp++)
		{
			if(isalnum(*cp))
				continue;
			else
				*cp = '_';
		}
		strcpy(filename,tfilename);
		strcat(filename,".");
		strcat(filename,logname);
		strcat(tfilename,".doc");


	    // open the file for write and create an ostream

		filebuf FB;
	
		if (FB.open(tfilename, output) == NULL)
		{
			errormsg(form("[panel.write] Can not open file %s",
							filename));
			return(FAILURE);
		}
		ostream outfile(&FB);

	// put out the panel information to the original file
	if (FP != cout)
	{
	    FP << level;
	    FP << ";SUB-PANEL;1;0;" << getname() << ";" 
				<< root->getname() <<  ";\n";
	}


	    // perform the walk and write node data to outfile

		if (root->write(outfile, (int) 0) != SUCCESS)
		{
			outfile.flush();
			return(FAILURE);
		}
		outfile.flush();
		FB.close();
		system(form("cat %s | $PFPATH/selfdoc -t > %s",tfilename,filename));
		system(form("cat %s | sort +4 -f -t';' | $PFPATH/selfdoc >> %s",
				tfilename,filename));
		system(form("rm %s",tfilename));
		return(SUCCESS);
}

////////////////////////////////////////////////////////////////////////////
int panelfeature::write (ostream& FP, int level)
{
	int dumlevel = level;
	FP <<  officialname << ";" ;
	return(SUCCESS);
}

////////////////////////////////////////////////////////////////////////////
int cluster::write (ostream& FP, int level)
{
	FP << level;
	FP << ";CLUSTER;0;0;";
	if (panelfeature::write(FP, level) != SUCCESS)
	{
		errormsg(form("[cluster.write] %s failed",getname()));
		return(FAILURE);
	}

	FP << "\n";
	
	for (int i=0; i<numchildren; i++)
	{
		if (child[i]->write(FP, level+1) != SUCCESS)
			return(FAILURE);
	}
	return(SUCCESS);
}

////////////////////////////////////////////////////////////////////////////
int display::write (ostream& FP,int level)
{
	FP << level;
	FP << ";DISPLAY;1;4;";
	if (panelfeature::write(FP,level) != SUCCESS)
	{
		errormsg(form("[display.write] %s failed",getname()));
		return(FAILURE);
	}

	FP << "(dimensions: " << numdimensions << " maximum points: " 
			<< maxdata  << ");"; 
	FP << "axis label;axis units;minimum value;maximum value;";
	for (int i=0; i<getsize(); i++)
	{
		FP << dlabels[i] << ";" << dscalelabels[i] << ";"
			<< min[i] << ";" << max[i] << ";" ;
	}
	FP <<"\n";

	return(SUCCESS);
}

////////////////////////////////////////////////////////////////////////////
int knob::write (ostream& FP, int level)
{
	if (panelfeature::write(FP, level) != SUCCESS)
	{
		errormsg(form("[knob.write] %s failed",getname()));
		return(FAILURE);
	}

	return(SUCCESS);
}

////////////////////////////////////////////////////////////////////////////
int INTknob::write (ostream& FP, int level)
{
	FP << level;
	FP << ";INTknob;1;4;";
	if (knob::write(FP,level) != SUCCESS)
	{
		errormsg(form("[INTknob.write] %s failed",getname()));
		return(FAILURE);
	}
	FP << "(maximum number of values: 1);";
	FP << "scale units;default value;minimum value;maximum value;";
	FP << getscalelabel() << ";" << getdflt() << ";" <<getmin()
			 << ";" << getmax() << ";\n";

	return(SUCCESS);

}

////////////////////////////////////////////////////////////////////////////
int FLTknob::write (ostream& FP, int level)
{
	FP << level;
	FP << ";FLTknob;1;4;";
	if (knob::write(FP, level) != SUCCESS)
	{
		errormsg(form("[FLTknob.write] %s failed",getname()));
		return(FAILURE);
	}
	FP << "(maximum number of values: 1);";
	FP << "scale units;default value;minimum value;maximum value;";
	FP << getscalelabel() << ";" << getdflt() << ";" <<getmin()
			 << ";" << getmax() << ";\n";

	return(SUCCESS);
}

////////////////////////////////////////////////////////////////////////////
int FWINTknob::write (ostream& FP, int level)
{
	FP << level;
	FP << ";FWINTknob;1;4;";
	if (knob::write(FP, level) != SUCCESS)
	{
		errormsg(form("[FWINTknob.write] %s failed",getname()));
		return(FAILURE);
	}
	FP << "(number of values: "<< getsize() << ");";
	FP << "scale units;default value;minimum value;maximum value;";
	FP << getscalelabel() << ";" << getdflt() << ";" <<getmin()
			 << ";" << getmax() << ";\n";

	return(SUCCESS);
}

////////////////////////////////////////////////////////////////////////////
int FWFLTknob::write (ostream& FP, int level)
{
	FP << level;
	FP << ";FWFLTknob;1;4;";
	if (knob::write(FP, level) != SUCCESS)
	{
		errormsg(form("[FWFLTknob.write] %s failed",getname()));
		return(FAILURE);
	}
	FP << "(number of values: "<< getsize() << ");";
	FP << "scale units;default value;minimum value;maximum value;";
	FP << getscalelabel() << ";" << getdflt() << ";" <<getmin()
			 << ";" << getmax() << ";\n";

	return(SUCCESS);
}

////////////////////////////////////////////////////////////////////////////
int VWINTknob::write (ostream& FP, int level)
{
	FP << level;
	FP << ";VWINTknob;1;4;";
	if (knob::write(FP, level) != SUCCESS)
	{
		errormsg(form("[VWINTknob.write] %s failed",getname()));
		return(FAILURE);
	}
	FP << "(range of number of values:  1 - "<< getmaxsize() << ");";
	FP << "scale units;default value;minimum value;maximum value;";
	FP << getscalelabel() << ";" << getdflt() << ";" <<getmin()
			 << ";" << getmax() << ";\n";

	return(SUCCESS);
}

////////////////////////////////////////////////////////////////////////////
int VWFLTknob::write (ostream& FP, int level)
{
	FP << level;
	FP << ";VWINTknob;1;4;";
	if (knob::write(FP, level) != SUCCESS)
	{
		errormsg(form("[VWFLTknob.write] %s failed",getname()));
		return(FAILURE);
	}
	FP << "(range of number of values:  1 - "<< getmaxsize() << ");";
	FP << "scale units;default value;minimum value;maximum value;";
	FP << getscalelabel() << ";" << getdflt() << ";" <<getmin()
			 << ";" << getmax() << ";\n";

	return(SUCCESS);
}

////////////////////////////////////////////////////////////////////////////
int ENUMknob::write (ostream& FP, int level)
{

	float df;

	FP << level;
	FP << ";ENUMknob;1;1;";
	if (knob::write(FP, level) != SUCCESS)
	{
		errormsg(form("[FWFLTknob.write] %s failed",getname()));
		return(FAILURE);
	}
	FP << "(number of values: "<< getsize() << ");";
	FP << "Possible Values:;";

	df = getdflt();


	for( int i=0; i<numvals; i++ )
	{
		FP << labels[i];
		if(vals[i] == (int)df)
		{
			FP << " <";
			for(int k=strlen(labels[i]); k<20; k++)
				FP << "-";
			FP << " default value";
		}
		FP << ";";
	}

	FP << "\n";
	return(SUCCESS);
}

