
/**************************************************************************/
/* PANELFEATURES Package    Release:  1.0    Release Date: 1/15/89        */
/*                          Provider: J. D. Iorio  (speedy!jdi)           */
/**************************************************************************/
// SETUP.C
//
//	Copyright (C) ATT 1988
//
// This file contains the functions which parse the input text
// strings for the setup function supplied to the user of ALMMS.
//
//   History:
//	J. D. Iorio	1/5/88	created
//

#include <ctype.h>
#include "pf.h"
#define CMDBUFSIZE 1024


extern int Usermode;

/////////////////////////////// declare a global here
int OrigUsermode;

// other functions used
extern char *parsenumber(char *, float *);

//////////////////////////////////////////////////////////////
int panel::user_setup()
{
	extern void mouse_active();
	extern void mouse_inactive();
	extern void hardcopy();
	char buf[CMDBUFSIZE];
	char junk;
	char *cp;


	if (Usermode != INTERACTIVE)
		return(1);

	mouse_active();

	while(1)
	{
		// get a command line from the terminal device
		cp = buf;
		while(1)
		{
		    /* read some data */
			cin.get(cp, CMDBUFSIZE-1, '\n');
		    /* read the newline char */
			cin.get(junk);

		    /* skip to end of line */
			for(  ; *cp != '\0'; cp++);
			cp--;
			if (*cp == '\\')
				continue;	/* get some more data */
			else
				break;
		}

		// process the command
	
	    	// if main GO command was issued 
		if (strncmp(buf,"**GO**",6) == 0 )
		{
			mouse_inactive();
			return(0);
		}
	
	    	// if main STOP command was issued 
		if (strncmp(buf,"**STOP**",8) == 0 )
		{
			mouse_inactive();
			return(1);
		}
	
	    	// if main DOC command was issued 
		if (strncmp(buf,"**DOC**",7) == 0 )
		{
			this->write(cout, 0);
			continue;
		}

	    	// if main HARDCOPY command was issued 
		if (strncmp(buf,"**HARDCOPY**",12) == 0 )
		{
			hardcopy();
			continue;
		}
	
	    	// else it is a setup command
		OrigUsermode = Usermode;
		(void)this->setup(buf);
		Usermode = OrigUsermode;
	}
}
//////////////////////////////////////////////////////////////
// HARDCOPY ROUTINE
// all data comes from the 630 terminal as follows
// 	width length (in  630 pixels)
//	hexdataline1 (width/4 chars long always padded to full byte)
//   ...hexdatalinelength
//      **END_OF_DATA**
//////////////////////////////////////////////////////////////
void hardcopy()
{
	char junk, junktoo;
	int w, h;
	float magw, magh;
	int fileflag;
	int repcnt, j;
	extern int system(char *);

	/* parse the width, height */
	cin >> w >> h;
	
	filebuf tempfile;
	ostream ps(&tempfile);

	fileflag = TRUE;
	if(tempfile.open("psf",output) == 0)
	{
		errormsg("cannot open file for hardcopy");
		fileflag = FALSE;
	}
	else
	{
		fileflag = TRUE;
		
		ps << form("/picstr %d string def\n",w/8);
		if(h > w)
		{
			ps << "50 50 translate\n";
		}
		else
		{
			ps << "500 50 translate\n";
			ps << "90 rotate\n";
		}
	
		magw = 500.0/(float)w;
		magh = 500.0/(float)h;

		if(magw > magh)
		    ps << (int)(w*magh) <<" "<< 500 << " scale\n"; 
		else
		    ps << 500 <<" "<< (int)(h*magw) << " scale\n"; 


		ps << "0 setgray\n";
		ps << form("%d %d true [%d 0 0 -%d 0 %d]\n",w,h,w,h,h);
		ps << "{currentfile picstr readhexstring pop }\n";
		ps << "imagemask\n\n";
	}

	/* process the data to a file */
	while((cin.get(junk)) && (junk != '*'))
	{
	    if(junk == '+')		/* throttle protocol */
	    {
		cout << "+\n";
		continue;
	    }
	    if(fileflag)
	    {
		if(junk == '!')		/* multiplier */
		{
		    cin.get(junk);
		    repcnt = (int)(junk-'0')*10;
		    cin.get(junk);
		    repcnt += (int)(junk-'0');
		    cin.get(junk);
		    cin.get(junktoo);
		
		    for(j=0; j<repcnt; j++)
		    {
			ps.put(junk);
			ps.put(junktoo);
		    }
		}
		else
		    ps.put(junk);
	    }
	} 

	if(fileflag)
	{
		ps << "showpage\n";
		ps.flush();


/* SYSTEM DEPENDENT STUFF MAYBE? */
/* note: inserting the 'H' as the first character of any output lines
         from 'lp' command allows the messages to show in the graphics
	 interface's message box.  Failure to do this could be fatal... */
		(void)system("cat psf | lp -d$DEST | sed 's/^/H/'");

		(void)system("rm psf 2>/dev/null");
	}

	/* flush the rest of line */
	while((cin.get(junk)) && (junk != '\n'));

}
//////////////////////////////////////////////////////////////

char *panelfeature::setup(char *string)
{
	errormsg(form("SET-UP ERROR: panelfeature fn() called: %s", getname()));
	*string = NULL;
	return(NULL);
}


char *cluster::setup(char *string)
{
	errormsg(form("SET-UP ERROR: cluster fn() called: %s", getname()));
	*string = NULL;
	return(NULL);
}


char *display::setup(char *string)
{
	errormsg(form("SET-UP ERROR: display fn() called: %s", getname()));
	*string = NULL;
	return(NULL);
}


char *knob::setup(char *string)
{
	errormsg(form("SET-UP ERROR: knob fn() called: %s", getname()));
	*string = NULL;
	return(NULL);
}




char *panel::setup(char *string)
{
	char *nameptr, *tail, *bkup;
	panelfeature *pf;
	char hold;



	// do until we return for some reason
	while(1)
	{
	    // done parsing if NULL pointer gets here 
	    //     (returned from subnode parsing that failed or completed)
		if (string == NULL)
			return(NULL);
	
	    // strip any leading white space
		for( ; isspace(*string); string++);
		if (*string == NULL)
			return(NULL);

	    // isolate a name off the string
		// until we hit a terminator
		for(tail=nameptr=string; ( (*tail != ';') &&
					  (*tail != '=')) ; tail++)
		{
			// if not alpha-numeric then error
			if ((isalnum(*tail))
			 	|| (*tail == '-')
			 	|| (*tail == '/')
			 	|| (*tail == '_')
			 	|| (*tail == ' ')
			 	|| (*tail == '%')
			 	|| (*tail == '#')
			 	|| (*tail == '.'))
				continue;
			else
			{
				tail++;
				hold = *tail;
				*tail = '\0';
				errormsg(form("SET-UP ERROR: bad name: %s",
							string));
				*tail = hold;
				return(NULL);
			}
		}

		// terminate the name but eliminate trailing blanks
		bkup = tail-1;
		while (isspace(*bkup))
			bkup--;
		bkup++;
		hold = *bkup;
		*bkup = '\0';

	    // find the name in our current subtree
		if ((pf = find(nameptr)) != NULL)
		{
		    // node found, let the node's routine parse the data
			*bkup = hold;
			string = pf->setup(tail+1);
		}
		else
		{
		    // node not in our subtree
			if( getparent() == NULL )
			{
			    // we're the root, error input found
				errormsg(form(
				   "SET-UP ERROR : %s is not an element of %s",
				    nameptr, getname()));
				*bkup = hold;
				return(NULL);
			}
			else
			{
			    // some other panel called this function
			    // let it try to find the node
				*bkup = hold;
				return(string);
			}
		}
	}
	
}



char *INTknob::setup(char *str)
{
	char *cp;	
	float f;
	
	cp = parsenumber(str, &f);
	if(cp == NULL)
	{
		errormsg(form("SET-UP ERROR: INTknob %s",getname()));
		return(NULL);
	}
	(*this) << f;

	if (*cp != ';')
	{
		errormsg(form("SET-UP ERROR: Too Many Values: knob - %s",
					getname()));
		return(NULL);
	}
	

	return(cp+1);
}



char * FWINTknob::setup(char *str)
{
	char *cp;	
	float *f;
	float g;
	int sz, j;
	
	// determine the knob's size and allocate storage
	sz = getsize();
	f = new float[sz];
	
	// read the current values of the knob
	(*this) >> f;

	// read parameters from the input line until a semicolon
	for(j=0, cp=str; (*cp != ';'); j++)
	{
		if((cp = parsenumber(cp, &g)) == NULL)
		{
			errormsg(form("SET-UP ERROR: FWINTknob %s",getname()));
			return(NULL);
		}
		if (j == sz)
		{
			errormsg(form("SET-UP ERROR: Too Many Vals: knob - %s",
						getname()));
			return(NULL);
		}
		f[j]=g;
	}
	// set the new values
	(*this) << f;
	delete f;

	return(cp+1);
}



char * VWINTknob::setup(char *string)
{
	char *cp;	
	float *f;
	float g;
	int sz, j;
	
	// determine the knob's size and allocate storage
	sz = getmaxsize();
	f = new float[sz];

	// read parameters from the input line until a semicolon
	for(j=0, cp=string; (*cp != ';'); j++)
	{
		if((cp = parsenumber(cp, &g)) == NULL)
		{
			errormsg(form("SET-UP ERROR: VWINTknob %s",getname()));
			return(NULL);
		}
		if (j == sz)
		{
			errormsg(form("SET-UP ERROR: Too Many Vals: knob - %s",
						getname()));
			return(NULL);
		}
		f[j]=g;
	}

	if(changesize(j) != j)
	{
		errormsg(form("SET-UP ERROR: VWINTknob %s BADSIZE",getname()));
		return(NULL);
	}

	(*this) << f;
	delete f;

	return(cp+1);
}



char * FLTknob::setup(char *string)
{
	char *cp;	
	float f;
	
	if((cp = parsenumber(string, &f)) == NULL)
	{
		errormsg(form("SET-UP ERROR: FLTknob %s",getname()));
		return(NULL);
	}
	(*this) << f;

	if (*cp != ';')
	{
		errormsg(form("SET-UP ERROR: Too Many Values: knob - %s",
					getname()));
		return(NULL);
	}
	

	return(cp+1);
}



char * FWFLTknob::setup(char *string)
{
	char *cp;	
	float *f;
	float g;
	int sz, j;
	
	// determine the knob's size and allocate storage
	sz = getsize();
	f = new float[sz];
	
	// read the current values of the knob
	(*this) >> f;

	// read parameters from the input line until a semicolon
	for(j=0, cp=string; (*cp != ';'); j++)
	{
		if((cp = parsenumber(cp, &g)) == NULL)
		{
			errormsg(form("SET-UP ERROR: FWFLTknob %s",getname()));
			return(NULL);
		}
		if (j == sz)
		{
			errormsg(form("SET-UP ERROR: Too Many Vals: knob - %s",
						getname()));
			return(NULL);
		}
		f[j]=g;
	}
	// set the new values
	(*this) << f;
	delete f;

	return(cp+1);
}



char * VWFLTknob::setup(char *string)
{
	char *cp;	
	float *f;
	float g;
	int sz, j;
	
	// determine the knob's size and allocate storage
	sz = getmaxsize();
	f = new float[sz];

	// read parameters from the input line until a semicolon
	for(j=0, cp=string; (*cp != ';'); j++)
	{
		if((cp = parsenumber(cp, &g)) == NULL)
		{
			errormsg(form("SET-UP ERROR: VWFLTknob %s",getname()));
			return(NULL);
		}
		if (j == sz)
		{
			errormsg(form("SET-UP ERROR: Too Many Vals: knob - %s",
						getname()));
			return(NULL);
		}
		f[j]=g;
	}

	if(changesize(j) != j)
	{
		errormsg(form("SET-UP ERROR: VWFLTknob %s BADSIZE",getname()));
		return(NULL);
	}

	(*this) << f;
	delete f;

	return(cp+1);
}



char * ENUMknob::setup(char *string)
{
	char *tail, *bkup, *nameptr;	
	int i;
	char hold;
	

    // strip any leading white space
	for( ;((isspace(*string)) ||
		 (*string=='=') ||
		 (*string==',') ||
		 (*string=='\0') ); string++)
	{
		if (*string == NULL)
		{
			errormsg("SET-UP ERROR: NULL found");

			return(NULL);
		}
	}

    // isolate a name off the string
	// until we hit a terminator
	for(tail=nameptr=string; ( *tail != ';') ; tail++)
	{
		// if not alpha-numeric then error
		if ((isalnum(*tail))
		 	|| (*tail == '-')
		 	|| (*tail == '/')
		 	|| (*tail == '_')
		 	|| (*tail == ' ')
		 	|| (*tail == '.'))
			continue;
		else
		{
			tail++;
			hold = *tail;
			*tail = '\0';
			errormsg(form("SET-UP ERROR: bad label: %s",
						string));
			*tail = hold;
			return(NULL);
		}
	}
	// terminate the name but eliminate trailing blanks
	bkup = tail-1;
	while (isspace(*bkup))
		bkup--;
	bkup++;
	hold = *bkup;
	*bkup = '\0';

    // find the name in our label list
	for (i=0; i<numvals; i++)
	{
		if (strcmp(nameptr, labels[i]) == 0)
		{
			(*this) << vals[i];
			break;
		}
	}

	if (i == numvals)
	{
		errormsg(form("SET-UP ERROR: bad label: %s, knob: %s",
				nameptr, getname()));

		*bkup = hold;
		return(NULL);
	}
	

	*bkup = hold;
	return(tail+1);
}


/////////////////////////////////////////////////////////////////////////
char *parsenumber(char *string, float *f)
{
	float sum;
	float decmult;
	float sign;
	int decflag;
	char *cp;

    // strip any leading white space
	for( ;((isspace(*string)) ||
		 (*string=='=') ||
		 (*string==',') ||
		 (*string=='\0') ); string++)
	{
		if (*string == NULL)
		{
			errormsg("PARSENUMBER ERROR: NULL found");

			return(NULL);
		}
	}

    // isolate a number off the string
	sum = 0.0;
	sign = 1.0;
	decflag = 0;
	decmult = 1;

	for( cp=string; 1; cp++)
	{
		if ((isdigit(*cp)) && (decflag == 0))
		{
			sum = sum*10 + (*cp - '0');
		}
		else if ((isdigit(*cp)) && (decflag == 1))
		{
			sum = sum + (*cp - '0')*decmult;
			decmult /= 10;
		}
		else if (*cp == '.')
		{
			decflag = 1;
			decmult = .1;
		}
		else if (*cp == '-')
		{
			sign = -1.0;
		}
		else if (*cp == '+')
		{
			sign = 1.0;
		}
		else if ((isspace(*cp)) || (*cp == '\0') || 
				(*cp == ',') || (*cp == ';') )
		{
			*f = sum*sign;
			// skip to a terminator , return ptr to it
			while (isspace(*cp))
				cp++;

			return(cp);
		}
		else
		{
			errormsg(form("PARSENUMBER ERROR: found %02x",*cp));
			return(NULL);
		}
	}
}
