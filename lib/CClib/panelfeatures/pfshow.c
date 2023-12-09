
/**************************************************************************/
/* PANELFEATURES Package    Release:  1.0    Release Date: 1/15/89        */
/*                          Provider: J. D. Iorio  (speedy!jdi)           */
/**************************************************************************/

// PFSHOW.C 
//
//	Copyright (C) ATT 1987
//
//	This file contains all of the show routines for all of the
//   types of panelfeatures. 
//
//   HISTORY:
//	J. D. Iorio	12/14/87	created
//

#include "pf.h"
#include "giproto.h"
#include "proto.h"

proto_stream pout;

extern int OrigUsermode;
extern int TERMTYPE;

 /////////////////////////////////////////////////////////////////////////////
void panel::show(int px, int py)		// display the instrument
{

	if( Usermode != INTERACTIVE )
		return;


	if ((updateflag == MAJOR) && (parent == (panelfeature *)NULL))
	{
		pout << form("%c\n", GILOAD);
		pout.flush();

	    // start throttle protocol
		if(TERMTYPE == ATT630)
			TERMTYPE=ATT630P;
	}

	root->show(px, py);
	if (updateflag == MAJOR)
	{
		pout << form("%c%s;%s;%%s;",GIPANEL,name,officialname);
		pout << form("%d;",attrib); 	// attributes flag
		pout << "1;";		// numchildren
		pout << "0;";		// numvalues
		pout << "0;\n";		// numvalues
		pout.flush();

		if (parent == (panelfeature *)NULL)
		{
			pout.put(GITERMINATE);
			pout.put('\n');
			pout.flush();

		    // end throttle protocol
			if(TERMTYPE == ATT630P)
				TERMTYPE=ATT630;
		}
		updateflag = UP_TO_DATE;
	}
	if (updateflag & ATTRIB_CHANGE)
	{
		pout << form("%c\n",GICHG_ATTRIB);
		pout << form("%s", getpath());
		pout << form("%s;",officialname);
		pout << form("%d;\n", attrib);
	}
	updateflag = UP_TO_DATE;
	pout.flush();
	
}
 /////////////////////////////////////////////////////////////////////////////
void panelfeature::show(int px, int py)			// display panel feature
{

	if( Usermode != INTERACTIVE )
		return;



	px = py;
	if (updateflag & NAME_CHANGE)
	{
		pout << form("%c\n",GICHG_NAME);
		pout << form("%s", getpath());
		pout << form("%s;%s;\n",officialname,name);
			
	}
}

 /////////////////////////////////////////////////////////////////////////////
void INTknob::show(int px,int py)
{

	if( Usermode != INTERACTIVE )
		return;



	if (updateflag == MAJOR)
	{
		pout.put(GIFWINT);
		knob::show(px,py);
	
		pout << form("%4.1f",getmin());
		pout.put(';');
		pout << form("%4.1f",getmax());
		pout.put(';');
		pout << getscalelabel();
		pout.put(';');
		for(int i=0; i<numvalues; i++)
		{
			pout << form("%4.1f",value[i]);
			pout.put(';');
		}
		pout << "\n";
		updateflag = UP_TO_DATE;
		pout.flush();
	}
	if (updateflag & NAME_CHANGE)
	{
		pout << form("%c\n",GICHG_NAME);
		pout << form("%s", getpath());
		pout << form("%s;%s;\n",officialname,name);
		updateflag = UP_TO_DATE;
		pout.flush();
	}
	if (updateflag & LABEL_CHANGE)
	{
		updateflag = UP_TO_DATE;
		pout.flush();
	}
	if (updateflag & VALUE_CHANGE)
	{
		pout << form("%c\n",GICHG_VALUE);
		pout << form("%s", getpath());
		pout << form("%s;", officialname);
		pout << form("%d;", numvalues);
		for(int j=0; j<numvalues; j++)
		{
			pout << form("%4.1f",value[j]);
			pout.put(';');
		}
		pout << "\n";
		updateflag = UP_TO_DATE;
		pout.flush();
	}
	if (updateflag & ATTRIB_CHANGE)
	{
		pout << form("%c\n",GICHG_ATTRIB);
		pout << form("%s", getpath());
		pout << form("%s;", officialname);
		pout << form("%d;\n", attrib);
		updateflag = UP_TO_DATE;
		pout.flush();
	}

}
void FWINTknob::show(int px,int py)
{

	if( Usermode != INTERACTIVE )
		return;



	if (updateflag == MAJOR)
	{
		pout.put(GIFWINT);
		knob::show(px,py);

		pout << form("%4.1f",getmin());
		pout.put(';');
		pout << form("%4.1f",getmax());
		pout.put(';');
		pout << getscalelabel();
		pout.put(';');
		for(int i=0; i<numvalues; i++)
		{
			pout << form("%4.1f",value[i]);
			pout.put(';');
		}
		pout << "\n";
		updateflag = UP_TO_DATE;
		pout.flush();
	}
	if (updateflag & NAME_CHANGE)
	{
		pout << form("%c\n",GICHG_NAME);
		pout << form("%s", getpath());
		pout << form("%s;", officialname);
		pout << form("%s;\n", name);
		updateflag = UP_TO_DATE;
		pout.flush();
	}
	if (updateflag & LABEL_CHANGE)
	{
		updateflag = UP_TO_DATE;
		pout.flush();
	}
	if (updateflag & VALUE_CHANGE)
	{
		pout << form("%c\n",GICHG_VALUE);
		pout << form("%s", getpath());
		pout << form("%s;", officialname);
		pout << form("%d;", numvalues);
		for(int j=0; j<numvalues; j++)
		{
			pout << form("%4.1f",value[j]);
			pout.put(';');
		}
		pout << "\n";
		updateflag = UP_TO_DATE;
		pout.flush();
	}
	if (updateflag & ATTRIB_CHANGE)
	{
		pout << form("%c\n",GICHG_ATTRIB);
		pout << form("%s", getpath());
		pout << form("%s;", officialname);
		pout << form("%d;\n", attrib);
		updateflag = UP_TO_DATE;
		pout.flush();
	}

}
void VWINTknob::show(int px,int py)
{

	if( Usermode != INTERACTIVE )
		return;



	if (updateflag == MAJOR)
	{
		pout.put(GIVWINT);
		knob::show(px,py);

		pout << form("%4.1f",getmin());
		pout.put(';');
		pout << form("%4.1f",getmax());
		pout.put(';');
		pout << getscalelabel();
		pout.put(';');
		for(int i=0; i<numvalues; i++)
		{
			pout << form("%4.1f",value[i]);
			pout.put(';');
		}
		pout << "\n";
		updateflag = UP_TO_DATE;
		pout.flush();
	}
	if (updateflag & NAME_CHANGE)
	{
		pout << form("%c\n",GICHG_NAME);
		pout << form("%s", getpath());
		pout << form("%s;", officialname);
		pout << form("%s;\n", name);
		updateflag = UP_TO_DATE;
		pout.flush();
	}
	if (updateflag & LABEL_CHANGE)
	{
		updateflag = UP_TO_DATE;
		pout.flush();
	}
	if (updateflag & VALUE_CHANGE)
	{
		pout << form("%c\n",GICHG_VALUE);
		pout << form("%s", getpath());
		pout << form("%s;", officialname);
		pout << form("%d;",numvalues);
		for(int j=0; j<numvalues; j++)
		{
			pout << form("%4.1f",value[j]);
			pout.put(';');
		}
		pout << "\n";
		updateflag = UP_TO_DATE;
		pout.flush();
	}
	if (updateflag & ATTRIB_CHANGE)
	{
		pout << form("%c\n",GICHG_ATTRIB);
		pout << form("%s", getpath());
		pout << form("%s;", officialname);
		pout << form("%d;\n", attrib);
		updateflag = UP_TO_DATE;
		pout.flush();
	}

}
void FLTknob::show(int px,int py)
{

	if( Usermode != INTERACTIVE )
		return;



	if (updateflag == MAJOR)
	{
		pout.put(GIFWFLT);
		knob::show(px,py);

		pout << form("%f",getmin());
		pout.put(';');
		pout << form("%f",getmax());
		pout.put(';');
		pout << getscalelabel();
		pout.put(';');
		for(int i=0; i<numvalues; i++)
		{
			pout << form("%f",value[i]);
			pout.put(';');
		}
		pout << "\n";
		updateflag = UP_TO_DATE;
		pout.flush();
	}
	if (updateflag & NAME_CHANGE)
	{
		pout << form("%c\n",GICHG_NAME);
		pout << form("%s", getpath());
		pout << form("%s;", officialname);
		pout << form("%s;\n", name);
		updateflag = UP_TO_DATE;
		pout.flush();
	}
	if (updateflag & LABEL_CHANGE)
	{
		updateflag = UP_TO_DATE;
		pout.flush();
	}
	if (updateflag & VALUE_CHANGE)
	{
		pout << form("%c\n",GICHG_VALUE);
		pout << form("%s", getpath());
		pout << form("%s;", officialname);
		pout << form("%d;",numvalues);
		for(int j=0; j<numvalues; j++)
		{
			pout << form("%f",value[j]);
			pout.put(';');
		}
		pout << "\n";
		updateflag = UP_TO_DATE;
		pout.flush();
	}
	if (updateflag & ATTRIB_CHANGE)
	{
		pout << form("%c\n",GICHG_ATTRIB);
		pout << form("%s", getpath());
		pout << form("%s;", officialname);
		pout << form("%d;\n", attrib);
		updateflag = UP_TO_DATE;
		pout.flush();
	}

}
void FWFLTknob::show(int px,int py)
{

	if( Usermode != INTERACTIVE )
		return;



	if (updateflag == MAJOR)
	{
		pout.put(GIFWFLT);
		knob::show(px,py);

		pout << form("%f",getmin());
		pout.put(';');
		pout << form("%f",getmax());
		pout.put(';');
		pout << getscalelabel();
		pout.put(';');
		for(int i=0; i<numvalues; i++)
		{
			pout << form("%f",value[i]);
			pout.put(';');
		}
		pout << "\n";
		updateflag = UP_TO_DATE;
		pout.flush();
	}
	if (updateflag & NAME_CHANGE)
	{
		pout << form("%c\n",GICHG_NAME);
		pout << form("%s", getpath());
		pout << form("%s;", officialname);
		pout << form("%s;\n", name);
		updateflag = UP_TO_DATE;
		pout.flush();
	}
	if (updateflag & LABEL_CHANGE)
	{
		updateflag = UP_TO_DATE;
		pout.flush();
	}
	if (updateflag & VALUE_CHANGE)
	{
		pout << form("%c\n",GICHG_VALUE);
		pout << form("%s", getpath());
		pout << form("%s;", officialname);
		pout << form("%d;",numvalues);
		for(int j=0; j<numvalues; j++)
		{
			pout << form("%f",value[j]);
			pout.put(';');
		}
		pout << "\n";
		updateflag = UP_TO_DATE;
		pout.flush();
	}
	if (updateflag & ATTRIB_CHANGE)
	{
		pout << form("%c\n",GICHG_ATTRIB);
		pout << form("%s", getpath());
		pout << form("%s;", officialname);
		pout << form("%d;\n", attrib);
		updateflag = UP_TO_DATE;
		pout.flush();
	}

}
void VWFLTknob::show(int px,int py)
{

	if( Usermode != INTERACTIVE )
		return;



	if (updateflag == MAJOR)
	{
		pout.put(GIVWFLT);
		knob::show(px,py);

		pout << form("%f",getmin());
		pout.put(';');
		pout << form("%f",getmax());
		pout.put(';');
		pout << getscalelabel();
		pout.put(';');
		for(int i=0; i<numvalues; i++)
		{
			pout << form("%f",value[i]);
			pout.put(';');
		}
		pout << "\n";
		updateflag = UP_TO_DATE;
		pout.flush();
	}
	if (updateflag & NAME_CHANGE)
	{
		pout << form("%c\n",GICHG_NAME);
		pout << form("%s", getpath());
		pout << form("%s;", officialname);
		pout << form("%s;\n", name);
		updateflag = UP_TO_DATE;
		pout.flush();
	}
	if (updateflag & LABEL_CHANGE)
	{
		updateflag = UP_TO_DATE;
		pout.flush();
	}
	if (updateflag & VALUE_CHANGE)
	{
		pout << form("%c\n",GICHG_VALUE);
		pout << form("%s", getpath());
		pout << form("%s;", officialname);
		pout << form("%d;",numvalues);
		for(int j=0; j<numvalues; j++)
		{
			pout << form("%f",value[j]);
			pout.put(';');
		}
		pout << "\n";
		updateflag = UP_TO_DATE;
		pout.flush();
	}
	if (updateflag & ATTRIB_CHANGE)
	{
		pout << form("%c\n",GICHG_ATTRIB);
		pout << form("%s", getpath());
		pout << form("%s;", officialname);
		pout << form("%d;\n", attrib);
		updateflag = UP_TO_DATE;
		pout.flush();
	}

}
void ENUMknob::show(int px,int py)
{

	if( Usermode != INTERACTIVE )
		return;


	if (updateflag == MAJOR)
	{
		pout.put(GIENUM);
		knob::show(px,py);

		pout << form("%d;",numvals);
		for(int i=0; i<numvals; i++)
		{
			pout << form("%s;",labels[i]);
		}
		pout << form("%d;\n",(int)value[0]);
		updateflag = UP_TO_DATE;
		pout.flush();
	}
	if (updateflag & NAME_CHANGE)
	{
		pout << form("%c\n",GICHG_NAME);
		pout << form("%s", getpath());
		pout << form("%s;", officialname);
		pout << form("%s;\n", name);
		updateflag = UP_TO_DATE;
		pout.flush();
	}
	if (updateflag & LABEL_CHANGE)
	{
		pout << form("%c\n",GICHG_LABEL);
		pout << form("%s", getpath());
		pout << form("%s;", officialname);
		for(int j=0; j<numvals; j++)
			pout << form("%s;",labels[j]);
		updateflag = UP_TO_DATE;
		pout.flush();
	}
	if (updateflag & VALUE_CHANGE)
	{
		pout << form("%c\n",GICHG_VALUE);
		pout << form("%s", getpath());
		pout << form("%s;", officialname);
		pout << form("%d;",numvalues);
		for(int j=0; j<numvalues; j++)
		{
			pout << form("%d;",(int)value[0]);
		}
		pout.put('\n');
		updateflag = UP_TO_DATE;
		pout.flush();
	}
	if (updateflag & ATTRIB_CHANGE)
	{
		pout << form("%c\n",GICHG_ATTRIB);
		pout << form("%s", getpath());
		pout << form("%s;", officialname);
		pout << form("%d;\n", attrib);
		updateflag = UP_TO_DATE;
		pout.flush();
	}

}
 /////////////////////////////////////////////////////////////////////////////
void knob::show(int px, int py)
{

	px = py;

	if( Usermode != INTERACTIVE )
		return;


	pout << form("%s;%s;%s;",name,officialname,getfmt());
	pout << form("%d;",attrib); 	// attributes flag
	pout << "0;";		// numchildren
	pout << form("%d;",numvalues);
	pout << form("%d;",maxnumvalues);
	pout << form("%d;",style);

}

 /////////////////////////////////////////////////////////////////////////////
void cluster::show(int px, int py)
{

	if( Usermode != INTERACTIVE )
		return;


	for (int i=0; i<numchildren; i++)
	{
		child[i]->show(px+xloc, py+yloc);
	}

	if (updateflag == MAJOR)
	{
		pout << form("%c%s;%s;%%s;",GICLUSTER,name,officialname);
		pout << form("%d;",attrib); 	// attributes flag
		pout << form("%d;",numchildren);
		pout << "0;";			// numvalues
		pout << "0;\n";			// maxnumvalues
		updateflag = UP_TO_DATE;
		pout.flush();
	}
	if (updateflag & ATTRIB_CHANGE)
	{
		pout << form("%c\n",GICHG_ATTRIB);
		pout << form("%s", getpath());
		pout << form("%s;", officialname);
		pout << form("%d;\n", attrib);
	}

	updateflag = UP_TO_DATE;
		pout.flush();

}

 /////////////////////////////////////////////////////////////////////////////
void display::show(int px, int py)
{

	if((Usermode != INTERACTIVE) && (OrigUsermode != INTERACTIVE) )
		return;

	// dont show if disabled
	if (showflag != TRUE)
	{
		showflag = TRUE;
		return;
	}


	px += xloc;
	py += yloc;

	if (updateflag == MAJOR)
	{
		pout << form("%c%s;%s;%%s;",GIDISPLAY,name,officialname);
		pout << form("%d;",attrib); 	// attributes flag
		pout << "0;";			// numchildren
		pout << form("%d;",0);		// numdata always 0 to start
		pout << form("%d;",maxdata);
		pout << form("%d;",style);
		pout << form("%d;",numdimensions);
		for(int i=0; i<numdimensions; i++)
		{
			pout << form("%f",max[i]);
			pout.put( ';' );
			pout << form("%f",min[i]);
			pout.put( ';' );
			pout << form("%s;%s;", format[i],dlabels[i]);
			pout << form("%s;",dscalelabels[i]);
		}
		pout << "\n";
		updateflag = UP_TO_DATE;
		pout.flush();
	}
	if (updateflag & NAME_CHANGE)
	{
		pout << form("%c\n",GICHG_NAME);
		pout << form("%s", getpath());
		pout << form("%s;", officialname);
		pout << form("%s;\n", name);
		updateflag = UP_TO_DATE;
		pout.flush();
	}
	if (updateflag & LABEL_CHANGE)
	{
		pout << form("%c\n",GICHG_LABEL);
		pout << form("%s", getpath());
		pout << form("%s;", officialname);
		for(int j=0; j<numdimensions; j++)
			pout << form("%s;",dlabels[j]);
		pout << "\n";
		updateflag = UP_TO_DATE;
		pout.flush();
	}
	if (updateflag & AXIS_CHANGE)
	{
		pout << form("%c\n",GICHG_AXIS);
		pout << form("%s", getpath());
		pout << form("%s;", officialname);
		for(int i=0; i<numdimensions; i++)
		{
			pout << form("%f",max[i]);
			pout.put( ';' );
			pout << form("%f",min[i]);
			pout.put( ';' );
			pout << form("%s;%s;", format[i],dlabels[i]);
			pout << form("%s;",dscalelabels[i]);
		}
		pout << "\n";
		updateflag = UP_TO_DATE;
		pout.flush();
	}
	if (updateflag & VALUE_CHANGE)
	{
		pout << form("%c\n",GIUPDATE_DISP);
		pout << form("%s", getpath());
		pout << form("%s;", officialname);
		for(int j=0; j<numdimensions; j++)
		{
			pout << form("%f",ddata[j][numdata-1]);
			pout.put( ';' );
		}
		pout << "\n";
		updateflag = UP_TO_DATE;
		pout.flush();
	}
	if (updateflag & VALUE_CLEAR)
	{
		pout << form("%c\n",GICLR_DISP);
		pout << form("%s", getpath());
		pout << form("%s;", officialname);
		pout << "\n";
		updateflag = UP_TO_DATE;
		pout.flush();
	}
	if (updateflag & ATTRIB_CHANGE)
	{
		pout << form("%c\n",GICHG_ATTRIB);
		pout << form("%s", getpath());
		pout << form("%s;", officialname);
		pout << form("%d;\n", attrib);
		updateflag = UP_TO_DATE;
		pout.flush();
	}
}


