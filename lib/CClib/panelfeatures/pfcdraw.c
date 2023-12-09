
/**************************************************************************/
/* PANELFEATURES Package    Release:  1.0    Release Date: 1/15/89        */
/*                          Provider: J. D. Iorio  (speedy!jdi)           */
/**************************************************************************/

/*************************************************************************
* PFCDRAW.C
*
*	Screen manipulation routines for the curses interface for 
*    PANELFEATURES
*
*	Copyright AT&T 1988
*
*	History:
*
*		J. Iorio 	7/5/88		created
*
***************************************************************************/

#include <stream.h>
#include <string.h>
#include <curses.h>

#include "pfcfunc.h"
#include "pfc.h"
#include "pfcglobals.h"
#include "pfcdef.h"


extern int LINES, COLS;


/******* common screen outline initialization ***************/
void pfscr_init_com()
{
	int i;
	extern WINDOW *newwin(int,int,int,int);
	
    /* create the windows */
	namebox = newwin(1,COLS,0,0);
	dividebox = newwin(MSGBOXH+1,COLS,LINES-MSGBOXH-1,0);
	msgbox = newwin(MSGBOXH,MSGBOXW,LINES-MSGBOXH,0);
	logobox = newwin(MSGBOXH,COLS-MSGBOXW-2,LINES-MSGBOXH,MSGBOXW+2);
	actionbox = newwin(LINES-MSGBOXH-3,COLS,2,0);

	
    /* outline the boxes */
	wmove(dividebox,0,0);
	for(i=0; i<(COLS-1); i++)
	{
		waddch(dividebox,'_');
	}
	for(i=1; i<7; i++)
	{
		mvwaddch(dividebox,i,MSGBOXW+1,'|');
	}
	
	wclear(namebox);
	wclear(msgbox);
	wclear(logobox);
	wclear(actionbox);

	wrefresh(namebox);
	wrefresh(msgbox);
	wrefresh(logobox);
	wrefresh(actionbox);
	wrefresh(dividebox);
	
	strcpy(Logo1,"PANEL");
	strcpy(Logo2,"FEATURES");
	strcpy(Logodate,"1988");
}


/****** logo draw routine ***************************************/
void pfscr_logo_draw()
{
	werase(logobox);
	mvwaddstr(logobox,1,2,Logo1);
	mvwaddstr(logobox,2,2,Logo2);
	mvwaddstr(logobox,4,2,"Copyright");
	mvwaddstr(logobox,5,6,"AT&T ");
	waddstr(logobox,Logodate);
	wrefresh(logobox);

}


/****** node draw routine ***************************************/
void pfscr_node_draw()
{
	int i, j;
	int ix,iy, ifirst;
	int tx, ty;
	char abuf[100];
	char bbuf[100];
	char *cp, *dp;
	struct node *n;


	werase(namebox);
	werase(actionbox);


    // update name box

	sprintf(abuf," %s",currentnode->name);
	for(n=currentnode->parent; n != NULL; n=n->parent)
	{
		if(strlen(abuf) > (COLS-15))
		{
			strcpy(bbuf, "... /");
			strcat(bbuf, abuf);
			strcpy(abuf, bbuf);
			break;
		}
		sprintf(bbuf, " %s /%s", n->name, abuf);
		strcpy(abuf, bbuf);
		if(n->type == PANEL)
			break;
	}
	i=strlen(abuf)/2;
	mvwaddstr(namebox,0,(COLS/2)-i,abuf);
	wnoutrefresh(namebox);



    // draw the node's contents in the actionbox

	mvwaddstr(actionbox,0,0,currentnode->name);
	switch(currentnode->type)
	{
		case PANEL:
		case CLUSTER:
		    iy = 1;
		    ifirst = currentnode->current_item;
		 
		    for(i=0; i<currentnode->numchildren; i++)
		    {
			n = currentnode->child[i];
			if(n->attribute != A_GREY)
			{
		    		if (currentnode->child[ifirst]->attribute ==
								 A_GREY)
					currentnode->current_item = i;
			     mvwaddstr(actionbox,iy,2,form("%-d",((i+1)%10)));
			     mvwaddstr(actionbox,iy,8,n->name);
			     n->orig_y = iy;
			     n->orig_x = 8;
			     switch(n->type)
			     {
			     case PANEL:
			          mvwaddstr(actionbox,iy,5,"P:");
			          break;
			     case CLUSTER:
			          mvwaddstr(actionbox,iy,5,"C:");
			          break;
			     case VWINT:
			     case VWFLT:
		    	          waddstr(actionbox, " - width: max. ");
		    	          waddstr(actionbox,
				      form("%-d",n->maxnumvalues));
		    	          waddstr(actionbox, " cur. ");
		    	          waddstr(actionbox,
				      form("%-d",n->numvalues));
			     	  iy++;
			          wmove(actionbox,iy,8);
			     case FWINT:
			     case FWFLT:
		    	          waddstr(actionbox, ":  ");
		    	          for(j=0; j<n->numvalues; j++)
		    	          {
		    	              waddstr(actionbox,
				            form(n->fmt,n->value[j]));
		    	              waddstr(actionbox, " ");
				      getyx(actionbox,ty,tx);
				      if((tx>(COLS-20)) && ((j+1)<n->numvalues))
				      {
		    	                  waddstr(actionbox, " >>>>");
				          break;
				      }
			          }
				  if((n->type == VWINT) || (n->type == VWFLT))
			          	mvwaddstr(actionbox,iy-1,5,"K:");
				  else
			          	mvwaddstr(actionbox,iy,5,"K:");
			          break;
			     case ENUM:
		    	          waddstr(actionbox, ":  ");
		    	          waddstr(actionbox,
				      n->labels[(int)(n->value[0])]);
			          mvwaddstr(actionbox,iy,5,"K:");
			          break;
			     case ASCKNOB:
		    	          waddstr(actionbox, ":  ");
		    	          waddstr(actionbox, n->labels[2]);
			          mvwaddstr(actionbox,iy,5,"K:");
			          break;
			     case DISPLAY:
				  tx = 80 - (20*n->numdim);
				  ix = tx;
		    		  for(j=0; j<n->numdim; j++)
		    		  {
		    			  mvwaddstr(actionbox,iy,ix,
								n->labels[j]);
		    			  waddstr(actionbox,"(");
		    			  waddstr(actionbox,n->dscalelab[j]);
		    			  waddstr(actionbox,")");
					  ix += 20;
		    		  }
			     	  iy++;
				  ix = tx;
		    		  for(j=0; j<n->numdim; j++)
		    		  {
					if(n->numvalues <= 0)
						break;
		    	    		mvwaddstr(actionbox,iy,ix,
						form(n->dfmt[j],
						n->data[j][n->numvalues-1]));

					ix += 20;
				  }
			          mvwaddstr(actionbox,iy-1,5,"D:");
				  break;

			     case ASCDISP:
			     	  iy++;

				  if(n->curs_x == 0)
					ty = n->curs_y - 1;
				  else
					ty = n->curs_y;

				  if(ty < 0)
					ty = 0;

				  if(strlen(n->image[ty]) > 65)
				  {
					cp = &(n->image[ty][65]);
					dp = abuf;

					*dp++ = *cp;
					*cp++ = ' ';
					*dp++ = *cp;
					*cp++ = '>';
					*dp = *cp;
					*cp = '\0';
			                mvwaddstr(actionbox,iy,8,n->image[ty]);
					cp = &(n->image[ty][65]);
					dp = abuf;
					*cp++ = *dp++;
					*cp++ = *dp++;
					*cp = *dp;
					
				  }
				  else
				  {
				        mvwaddstr(actionbox,iy,8,n->image[ty]);
				  }

			          mvwaddstr(actionbox,iy-1,5,"D:");
			          break;
			     default:
				   warn("Unknown child type in node_draw()");
			     }
			     iy++;
			}
		    }
		    ifirst = currentnode->current_item;
		    ty = currentnode->child[ifirst]->orig_y;
		    currentnode->curs_x = 8;
		    currentnode->curs_y = ty;
		    wmove(actionbox,ty,8);
		
		    break;

		case VWINT:
		case VWFLT:
		    mvwaddstr(actionbox,2,2,"maximum number of elements: ");
		    mvwaddstr(actionbox,2,30,
				form("%-d",currentnode->maxnumvalues));
		case FWINT:
		case FWFLT:
		    mvwaddstr(actionbox,1,2,"valid range: { ");
		    waddstr(actionbox,
				form(currentnode->fmt, currentnode->min));
		    waddstr(actionbox," ... ");
		    waddstr(actionbox,
				form(currentnode->fmt, currentnode->max));
		    waddstr(actionbox," }");
		    mvwaddstr(actionbox,3,2,"number of elements: ");
		    mvwaddstr(actionbox,3,30,
				form("%-d",currentnode->numvalues));
		
		    ix = 2;
		    iy = 4;
		    for(i=0; i<currentnode->numvalues; i++)
		    {
		    	mvwaddstr(actionbox,iy,ix,
				form(currentnode->fmt, currentnode->value[i]));
			if((int)currentnode->current_item == i)
			{
		    		currentnode->curs_x = ix;
		    		currentnode->curs_y = iy;
			}

			iy++;
			if(iy >= 14)
			{
				ix += 13;
				iy = 4;
			}
		    }

		    if(currentnode->current_item == -1)
		    {
		    		currentnode->curs_x = 30;
		    		currentnode->curs_y = 3;
		    }
		    wmove(actionbox,currentnode->curs_y,currentnode->curs_x);
		    break;

		case ENUM:
		    ix = 2;
		    iy = 4;
		    for(i=0; i<currentnode->numdim; i++)
		    {
		    	mvwaddstr(actionbox,iy,ix, currentnode->labels[i]);
			if((int)currentnode->value[0] == i)
			{
		    		currentnode->curs_x = ix;
		    		currentnode->curs_y = iy;
		    		mvwaddstr(actionbox,iy,ix-1, "*");
			}
			iy++;
			if(iy >= 14)
			{
				ix += 25;
				iy = 4;
			}
		    }
		    wmove(actionbox,currentnode->curs_y,currentnode->curs_x);
		    break;

		case ASCKNOB:
		    mvwaddstr(actionbox,1,2,currentnode->labels[0]);

		    if(strlen(currentnode->labels[1]) > 3)
		    {
		    	mvwaddstr(actionbox,2,2,"Valid range: ");
		    	waddstr(actionbox,currentnode->labels[1]);
		    }

		    mvwaddstr(actionbox,4,2,currentnode->labels[2]);
		    wmove(actionbox,currentnode->curs_y,currentnode->curs_x);
		    break;

		case DISPLAY:
		    ix = 6;
		    for(i=0; i<currentnode->numdim; i++)
		    {
		    	mvwaddstr(actionbox,1,ix,currentnode->labels[i]);
		    	mvwaddstr(actionbox,2,ix,currentnode->dscalelab[i]);
			ix += 20;
		    }
		    tx = (currentnode->current_item <= currentnode->numvalues)
			? currentnode->current_item : currentnode->numvalues;
		    
		    iy = 4;
		    for(i=tx,j=0; (i<currentnode->numvalues)&&(j<10); j++,i++)
		    {
		    	mvwaddstr(actionbox,iy,0,
				form("%d",i-currentnode->numvalues+1));
		        ix = 6;
		        for(ty=0; ty<currentnode->numdim; ty++)
		        {
		    	    mvwaddstr(actionbox,iy,ix,
					form(currentnode->dfmt[ty],
					currentnode->data[ty][i]));
			    ix += 20;
		        }
			iy++;
		    }
		    wmove(actionbox,0,0);
		    currentnode->curs_x = 0;
		    currentnode->curs_y = 0;
		    break;
			
		case ASCDISP:
			iy = currentnode->current_item;
			if(iy <= 0)
			{
				iy = 0;
				mvwaddstr(actionbox,3,0,"__ TOP __");
				
			}
			
			for(tx=4,ty=iy;
			     (tx < 16) && (ty < currentnode->maxnumvalues);
			 	ty++,tx++)
			{
			    mvwaddstr(actionbox,tx,0,currentnode->image[ty]);
			}
			if(ty == currentnode->maxnumvalues)
				mvwaddstr(actionbox,tx,0,"__ BOTTOM __");
		    break;

		default:
			warn("Unknown node type in node_draw()");
	}

	wnoutrefresh(actionbox);
	doupdate();

}
