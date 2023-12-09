
/**************************************************************************/
/* PANELFEATURES Package    Release:  1.0    Release Date: 1/15/89        */
/*                          Provider: J. D. Iorio  (speedy!jdi)           */
/**************************************************************************/

//////////////////////////////////////////////////////////////////////////
//  SELFDOC.C
//
//  This program postprocesses the output of the self documenting 
//  feature of the panelfeatures package.  
//  Usage:
//	To generate a tree picture from the original file:
//		cat PFoutfile | selfdoc -t > pic_file
//	To generate a listing of the panelfeature specifications
//		cat PFoutfile | sort +4 -t';' | selfdoc > troff_file
//
//  Copyright AT&T 1988
//
//  Author: J. D. Iorio
//////////////////////////////////////////////////////////////////////////

#include <stream.h>
#include <string.h>

#define MAXLEVELS 10

main(int argc)
{


	char *bpt, *ept;
	char lbuf[2048];
	char junk;

	char *name, *type, *strings;
	int level, extra, cols;
	int lastlevel;
	int levely[MAXLEVELS];
	int first;
	int i, curx, cury;



	first =0;
    // body of printout processing
	while(cin.rdstate() == _good)
	{
	    // read in a line of text
		cin.get(lbuf,4096);
		// and discard the newline
		cin.get(junk);
		if(cin.rdstate() != _good)
			break;


	    // parse the values out
		// tree level
		for(bpt=ept=lbuf; *ept!=';'; ept++);
		*ept = '\0';
		sscanf(bpt,"%d",&level);

		// node type
		for(ept++, type=ept; *ept!=';'; ept++);
		*ept = '\0';

		// number of extra data strings
		for(ept++, bpt=ept; *ept!=';'; ept++);
		*ept = '\0';
		sscanf(bpt,"%d",&extra);

		// number of columnized data strings
		for(ept++, bpt=ept; *ept!=';'; ept++);
		*ept = '\0';
		sscanf(bpt,"%d",&cols);

		// node name
		for(ept++, name=ept; *ept!=';'; ept++);
		*ept = '\0';

		// rest of line
		strings = ept+1;


    // top of printout processing
	if(first==0)
	{
		if(argc > 1)
		{
		  // top of pic file for tree
		    lastlevel = -1;
		    curx = 0; cury = 715;
		    levely[0] = cury;
	
			cout << ".nf\n";
		    // set up the title line
			if(level == 0)
			{
			    cout << form(".tl '%s'PANELFEATURES PACKAGE'%s'\n",
					name,name);
			    cout << form(".PH \"'%s'PANELFEATURES PACKAGE'%s'\"\n",
					name,name);
			}
		    cout << ".PS\nB: box invis ht 719 wid 624 with .sw at 0,0\n";
		    cout << "scale=85\n";
		    cout << form("move to %d,%d\n",curx,cury);
		}
	else
		{
		  // top of troff file for list
		    cout << ".nf\n.ps 8\n.ta 2i 3.25iC 4.5iC 5.75iC 7iC\n";
		}
	}
		first =1;

		if(argc > 1)
		{

	            // print out the tree
		        if(level <= lastlevel)
		        {
			        i=level*100;
        
			        if(level < lastlevel)
				        cury-=10;
			        else
				        cury-=8;
			        cout << form("line from %d,%d to %d,%d\n",
					i,levely[level],i,cury);
			        cout << form("line from %d,%d to %d,%d\n",
					i,cury,i+5,cury);
			        cout << form("move to %d,%d\n",i+6,cury+3);
			        cout << form("\"\\fR\\s6\\&%s\\f1\\s0\" ljust\n",
						name);
			        cout << form("move to %d,%d\n",i+5,cury);
			        levely[level] = cury;
			
			
		        }

		        else // (level > lastlevel)
		        {
			        curx = level*100+5;
			        levely[level] = cury;
			        cout << form("line to %d,%d\n",curx,cury);
			        cout << form("move to %d,%d\n",curx,cury);
			        cout << form("move to %d,%d\n",curx+1,cury+3);
			        cout << form("\"\\fR\\s6\\&%s\\f1\\s0\" ljust\n",
							name);
			        cout << form("move to %d,%d\n",curx,cury);
		        }

		        lastlevel = level;

	        }
		else
		{
		    // print out a list
			cout << "\\fB" <<name;
			cout << "\\fP"<< type << "	";

		        // print any extra strings
			for(i=0; i<extra; i++)
			{
			    for(bpt=ept=strings; *ept!=';'; ept++);
			    *ept = '\0';
			    cout << "	" << bpt;
			    strings = ept+1;
			}
			cout << "\n	";

			// print out any column data
			for(ept=strings; *ept!='\0'; )
			{
			    for(i=0; i<cols; i++)
			    {
			    	for(bpt=ept; *ept!=';'; ept++);
			    	*ept = '\0';
				
				cout << bpt << "	";
				ept++;
			    }
			    cout << "\n	";
			}
			cout << "\n";
		}
	}

    // bottom of printout processing
	if(argc > 1)
	{
		cout << ".PE\n.fi\n.bp\n";
	}
	else
	{
		cout << "\n\n.fi\n.PH \"''-\\\\nP-''\"\n.bp\n";
	}
}
