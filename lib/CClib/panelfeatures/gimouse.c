
/**************************************************************************/
/* PANELFEATURES Package    Release:  1.0    Release Date: 1/15/89        */
/*                          Provider: J. D. Iorio  (speedy!jdi)           */
/**************************************************************************/
/*
*	(C) Copyright ATT 1988
*
*	gimouse.c -
*
* A collection of mouse tracking routines for the 630 terminal
* in conjunction with the panelfeature package in ALMMS:
*
*
*/

#include <dmd.h>
#include <font.h>
#include "gi.h"
#include "giwindow.h"

/********************************************************************/

extern struct node *currentnode;	/* currently displayed node */
extern struct node *togglenode;		/* alternate displayed node */
extern Texture16 *tweed, *kapow;
extern void screen_curnode_draw();
extern void screen_refresh_curnode();
extern void screen_node_draw();
extern void screen_subwin_draw();
extern char lbuf[];
extern int w_adjust();
extern int w_edit();
extern void warn();
extern void sendhost();
void knob_message();
void aknob_edit();


/********************************************************************
* void m_button12(b,mxy)
*
*	This routine determines what action to take for the specified
*	button given the mouse.xy
*********************************************************************/

void m_button12(b,mxy)
int b;
Point mxy;
{
	int i, j, k;
	struct node *this;
	Rectangle r;
	struct node *temp;
	Point mxy_on_window;

	if (ptinrect(mxy,SCR_TOGBOX))
	{
		/* swap the nodes */
		temp = currentnode;
		currentnode = togglenode;
		togglenode = temp;

		/* and the new node */
		if (currentnode != togglenode)
			screen_curnode_draw();

		/* wait for the key to come up */
		for( ;bttn(b);)
			nap(2);
		return;
	}

	if (ptinrect(mxy,SCR_NAMEBOX))
	{
		/* save the node pointer for toggle */
		togglenode = currentnode;
	}

	if (ptinrect(mxy,SCR_GOBOX))
	{
		sendhost("**GO**");

		/* wait for the key to come up */
		for( ;bttn(b);)
			nap(2);
		return;
	}

	if (ptinrect(mxy,SCR_STOPBOX))
	{
		sendhost("**STOP**");

		/* wait for the key to come up */
		for( ;bttn(b);)
			nap(2);
		return;
	}


	for (i=0; i<currentnode->numchildren; i++)
	{
		this = currentnode->child[i];
		r = raddp(this->window_rect,this->rel_to_origin);

		/* if we're on a panelfeature */
		if(ptinrect(mxy,r))
		{

		    /* place it at the top of the list */
		    for (j=i; j>0; j--)
		    {
			/* shift all nodes above down */
			k = j-1;
			currentnode->child[j] = currentnode->child[k];
		    }
		    /* put this one on top */
		    currentnode->child[0] = this;
		    screen_node_draw(this);

		    /* where are we in the knob? */
		    mxy_on_window = sub(mxy,this->rel_to_origin);
		    
		    /* try the edit functions (move, resize, scroll, etc) */
		    if((k=w_edit(this, mxy_on_window, (bttn1()?1:2))) != 0)
		    {
			/* if something done, then update display and return */
			if(k == -2)
			{
				screen_node_draw(this);
				screen_refresh_curnode();
			}
			else
			{
				screen_node_draw(this);
			}
			return;
		    }


		    /* else try to perform the action based on node type */
		    /* only on ungreyed nodes */
		    if ((this->attribute & A_GREY) == 0)
		    {
			switch(this->type)
			{
			case PANEL:
				this = this->child[0];
				/* panel->child 0 is always a cluster so */
				/* fall through to cluster case here */
			case CLUSTER:
				currentnode = this;
				screen_curnode_draw();
				/* wait for the key to come up */
				for( ;bttn(b);)
					nap(2);
				return;
				break;

			case ASCKNOB:
				while(ptinrect(mouse.xy,r))
				{
				    if(button12())
				    {
					mxy_on_window =
					     sub(mouse.xy,this->rel_to_origin);
					aknob_edit(this, r, mxy_on_window);
				    }
				}
				break;

			case FWINT:
			case VWINT:
			case FWFLT:
			case VWFLT:
			case ENUM:
				while(ptinrect(mouse.xy,r))
				{
				    if(button12())
				    {
					/* update knob */
					for( ;bttn12();)
					{
					    mxy_on_window =
					     sub(mouse.xy,this->rel_to_origin);

					    if((j=w_adjust(this,mxy_on_window,
							(bttn1()?1:2))) >= 0)
						screen_subwin_draw(this,j);
					    else if(j == -1)
					    	screen_node_draw(this);
					    else
						warn("bad return w_adj");

					  /* recompute area in case reshape or 
						move has occurred */
					    r = raddp(this->window_rect,
							this->rel_to_origin);
					    if(!ptinrect(mouse.xy,r))
						break;
					   /*  sleep(4); */
					}
					/* send ENUM UPDATES HERE */
					if(this->type == ENUM) 
					{
					    knob_message(this);
					    return;
					}
				    }
				}

			/* send the message here if not ENUM knob */
				if(this->type != ENUM)
				{
					knob_message(this);
				}

				for( ;bttn12();)
					nap(2);
				
				break;
			}
		    }
		    return;
		}
	}
}


/********************************************************************
* char *aknob_edit(n, wrect, mxyow)
*
*	This routine handles the interaction for an ascii type knob
*    in node n located on screen in Rect. wrect with mouse coord at mxyow
*    relative to the displayable window
*********************************************************************/
void aknob_edit(n, wrect, mxyow)
struct node *n;
Rectangle wrect;
Point mxyow;
{
	Rectangle r, s;
	Point mxy, p, q;
	int i, j, k;
	char *bp, *cp, *ep;

	    /* determine where on real image the mouse is */
	if((n->window_flag & ANYBORDER) == 0)
	{
		/* non scrollable, use whole window coord system */
		mxy = mxyow;
	}
	else
	{
		/* check each subwindow for inclusion */
		for(j=0; j<MAXSUBWIN; j++)
		{
			if((n->window_flag & subwin(j)) &&
				(ptinrect(mxyow, n->sw_rect[j])))
			{
			    /* set mxy relative to this subwindow on image */
			    mxy = sub(mxyow,(n->sw_rect[j]).origin);
			    mxy = add(mxy,n->sw_origin[j]);
			    break;
			}
		}

		if(j==MAXSUBWIN)
		{
			warn("subwindow error in aknob_edit");
			return;		/* error condition */
		}
	}

	    /* locate the images's answer area */
	q = fPt(2,54);
	s = fRect(q.x,q.y,q.x+n->element_width,q.y+16);

	    /* if mouse in the answer box */
	if (ptinrect(mxy,s))
	{
		while(button12());

	    /* clear the current string */
		for(j=0, bp=n->labels[2]; j<n->maxnumvalues; j++, bp++)
			*bp = '\0';

	    /* read the new string */
		bp = n->labels[2];
		r.origin.x = s.origin.x;
		r.origin.y = s.origin.y;
		r.corner.x = s.corner.x;
		r.corner.y = s.corner.y;
		texture(n->image,r,&T_black,F_STORE);
		for(j=0; j<n->maxnumvalues; j++)
		{
			screen_node_draw(n);
			while((k=kbdchar()) == -1)
				wait(KBD);
			if((k == '\n') || (k == '\r'))
			{
				
				*bp = '\0';
				texture(n->image,r,&T_lightgrey,F_STORE);
				break;
			}
			else if (k == 0x08)   /* backspace */
			{
				bp --;
				j -= 2;
				*bp = '\0';
				r.origin.x -= 7;
				texture(n->image,r,&T_black,F_STORE);
			}
			else
			{
				*bp = (char)k;
				bp++;
				string(&TEXT_FONT, n->labels[2],
					 n->image, q, F_STORE);
				r.origin.x += 7;
			}
				
		}
		box(n->image,s,F_STORE);
		screen_node_draw(n);
		knob_message(n);
	}
	else
	{
	    while(button12());
	}

	return;
	
}
/********************************************************************
* char *knob_message(n)
*
*	This routine constructs a message for the knob values and sends
*	it off to the host based on the current values
*********************************************************************/
void knob_message(n)
struct node *n;
{
	char *cp;
	int i, j, k;
	struct node *m;

	/* get the closest panel above */
    for (m=n->parent; m->type != PANEL; m=m->parent);
	
    if (m->parent != NULLNP)
    {
	Sprintf(lbuf,"%s; ",m->name);
        for(cp=lbuf; *cp != '\0'; cp++);
    }
    else 
    {
	cp = lbuf;
    }

	/* add the knob command */
    Sprintf(cp,"%s = ", n->name);
    for (j=0; j<n->numvalues; j++)
    {
       for(cp=lbuf; *cp != '\0'; cp++);
       if (n->type == ENUM)
	{
       		k = n->value[j];
       		Sprintf(cp," %s\\\n", n->labels[k]);
	}
       else if (n->type == ASCKNOB)
	{
       		Sprintf(cp," %s\\\n", n->labels[2]);
	}
	else
	{
	        Sprintf(cp," %f\\\n", n->value[j]);
	}
    }
    for(cp=lbuf; *cp != '\0'; cp++);
    *cp = ';';
    cp++;
    *cp = '\0';
    sendhost(lbuf);


	/* let ascii knob verification take place on host */
    if(n->type != ASCKNOB)
    	n->attribute |= A_JUSTSET;
}
	


/********************************************************************
* void m_button3(mxy)
*
*	This routine determines what action to take for the third
*	button given the mouse.xy (currently will close cluster)
*********************************************************************/

void m_button3(mxy)
Point mxy;
{
	if (currentnode->parent == NULLNP)
	{
		warn("At top level already!");
		/* wait for the key to come up */
		for( ;bttn(3);)
			nap(2);
		return;
	}

	currentnode = currentnode->parent;

    /* don't ever stop on a panel item */
	if(currentnode->type == PANEL)
	{
		if (currentnode->parent == NULLNP)
		{
			warn("At top level already!");
			currentnode = currentnode->child[0];
			/* wait for the key to come up */
			for( ;bttn(3);)
				nap(2);
			return;
		}
		else
		{
			currentnode = currentnode->parent;
		}

	}
	screen_curnode_draw();
	/* wait for the key to come up */
	for( ;bttn(3);)
		nap(2);
	return;
}


