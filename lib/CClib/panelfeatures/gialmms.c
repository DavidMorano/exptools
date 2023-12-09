
/**************************************************************************/
/* PANELFEATURES Package    Release:  1.0    Release Date: 1/15/89        */
/*                          Provider: J. D. Iorio  (speedy!jdi)           */
/**************************************************************************/
/*       Copyright (c) 1988 AT&T   */
/*       All Rights Reserved       */


#include <dmd.h>
#include <font.h>
#include <object.h>
#include "gi.h"


Point setsize()
{
	return(fPt(328,144));
}

/**************************************** globals *********************/
struct node *currentnode;
struct node *togglenode;
Rectangle original_window;
int mouse_alive;

					/* TEXTURE  definitions*/
static Texture16 tweeddata = {
	 0x4444, 0x7777, 0xeeee, 0x2222,
	 0x4444, 0x7777, 0xeeee, 0x2222,
	 0x4444, 0x7777, 0xeeee, 0x2222,
	 0x4444, 0x7777, 0xeeee, 0x2222,
};
static Texture16 kapowdata = {
	 0x1b1b, 0x2727, 0x7d7d, 0xbebe,
	 0x4e4e, 0x8d8d, 0x2828, 0x1414,
	 0x1b1b, 0x2727, 0x7d7d, 0xbebe,
	 0x4e4e, 0x8d8d, 0x2828, 0x1414,
};
static Texture16 cup = {
	0x0380, 0x0400, 0x03E0, 0x0010,
	0x03E0, 0x0400, 0x0300, 0x0000,
	0x3FF8, 0x4004, 0x4034, 0x4034,
	0x4004, 0x4078, 0x2020, 0x1FC0,
};

static Texture16 dstar = {
	 0x07E0, 0x0000, 0x207C, 0x7FFE,
	 0x0000, 0x803F, 0xFFFF, 0x0000,
	 0xC07F, 0xFFFF, 0x0000, 0x7FFE,
	 0x7FFE, 0x0000, 0x1FF8, 0x07E0,
};

Texture16 *tweed, *kapow, *busycursor, *normcursor; 



					/* Copyright symbol */

    static Word crsbuf[] =
	{
	0x03C0, 0x0C30, 0x300C, 0x23C4,
	0x4422, 0x4802, 0x4802, 0x8801,
	0x4802, 0x4802, 0x4422, 0x23C4,
	0x300C, 0x0C30, 0x03C0, 0x0000,
	};
    static Bitmap cpyright = 
	{
		(Word *)crsbuf,
		1,
		(short)0, (short)0, (short)16, (short)16,
		(char *)0
	};

Bitmap *copyright;


					/* VERTICAL STYLE  KNOB COMPONENTS */

    static long vknobbuf[] =
	{
#include "vknob.icon"
	};
    static Bitmap vknob = 
	{
		(Word *)vknobbuf,
		4,
		(short)0, (short)0, (short)48, (short)48,
		(char *)0
	};

Bitmap *VKNOB;

					/* HORIZONTAL STYLE KNOB COMPONENTS */

    static long hknobbuf[] =
	{
#include "hknob.icon"
	};




    static Bitmap hknob = 
	{
		(Word *)hknobbuf,
		4,
		(short)0, (short)0, (short)48, (short)48,
		(char *)0
	};

Bitmap *HKNOB;

/* DEFAULT LOGO STUFF */
					/* Author's face Icon */

    static long jedibuf[] =
	{
		0xFFFFFFFF,0xFFFFC000,
		0xFFFFFFFF,0xFFFFC000,
		0xFFFFFFFF,0xFFFFC000,
		0xFFFFFFFF,0xFFFFC000,
		0xFFFFFC1F,0xFFFFC000,
		0xFFFFF841,0xFFFFC000,
		0xFFFFE040,0x7FFFC000,
		0xFFFF8040,0x3FFFC000,
		0xFFFE0040,0x1FFFC000,
		0xFFFE00C0,0x0FFFC000,
		0xFFFC0080,0x07FFC000,
		0xFFF800C0,0x47FFC000,
		0xFFF82080,0x83FFC000,
		0xFFF02082,0x43FFC000,
		0xFFF00084,0x20FFC000,
		0xFFE30180,0x00FFC000,
		0xFFE883F8,0x207FC000,
		0xFFE03FFC,0x107FC000,
		0xFFC8FFFF,0xCC3FC000,
		0xFFC40000,0x013FC000,
		0xFF817F6F,0xF03FC000,
		0xFFC15068,0xA43FC000,
		0xFFC10961,0xA01FC000,
		0xFFC07E77,0xE03FC000,
		0xFF82BE73,0xC00FC000,
		0xFF00C174,0x300FC000,
		0xFF007F77,0xE21FC000,
		0xFFC07EFB,0xE01FC000,
		0xFF80FEFB,0xF01FC000,
		0xFF017E73,0xF01FC000,
		0xFF007FFF,0xE00FC000,
		0xFF84F801,0xE01FC000,
		0xFF807000,0xE10FC000,
		0xFF903000,0x603FC000,
		0xFF806004,0x018FC000,
		0xFF84A3FE,0x0007C000,
		0xFF01C1F8,0x219FC000,
		0xFE43E001,0x36DFC000,
		0xFF81F108,0x3F7FC000,
		0xFFFDF088,0x7FFFC000,
		0xFFFFF000,0xFFFFC000,
		0xFFFFF000,0xFFFFC000,
		0xFFFFFC01,0xFFFFC000,
		0xFFFFFC01,0xFFFFC000,
		0xFFFFFE03,0xFFFFC000,
		0xFFFFFFFF,0xFFFFC000,
		0xFFFFFFFF,0xFFFFC000,
		0xFFFFFFFF,0xFFFFC000,
		0xFFFFFFFF,0xFFFFC000,
		0xFFFFFFFF,0xFFFFC000,
	};




    static Bitmap jedi = 
	{
		(Word *)jedibuf,
		4,
		(short)0, (short)0, (short)48, (short)48,
		(char *)0
	};

Bitmap *JEDI;

    static char Logo1[] = {"PANEL "};
    static char Logo2[] = {"FEATURES  "};
    static char Logodate[] = {"1988"};
    static char Logo3[] = {"by :      "};

char *logo1, *logo2, *logodate, *logo3;




					/* scroll bar and window Icons */

    static long sbarbuf[] =
	{
#include "sbar.icon"
	};

    static Bitmap sbarbm = 
	{
		(Word *)sbarbuf,
		4,
		(short)0, (short)0, (short)48, (short)32,
		(char *)0
	};

Bitmap *SBAR;

    static long wbarbuf[] =
	{
#include "wbar.icon"
	};
    static Bitmap wbarbm = 
	{
		(Word *)wbarbuf,
		4,
		(short)0, (short)0, (short)48, (short)32,
		(char *)0
	};

Bitmap *WBAR;
/*******************************/
char lbuf[BUFSIZE];	/* buffer for message building via Sprintf */


int proto_mode;
/********************************** End of globals ********************/

extern void sendhost();
extern void screen_logo_draw();

main()
{

    /* local variables */
	int kchar, hchar;
	int idled;
	void gi_exit();
	void blitinit();
	void m_button12();
	void m_button3();
	void hardcopy();

	struct node *root;


	
	/* cache the program if not already present to avoid re-download */
	cache((char *)0,A_NO_SHOW); 


	/* initialize the bit blits */
	blitinit();

	/* reshape the window for panelfeature applications */
	  /* save the original window */
	original_window = display.rect;

	  /* set-up the panelfeature graphic interface window (whole screen) */
	reshape(Jrect);

	  /* clear the workspace */
	jrectf(Drect, F_CLR);
	screen_logo_draw();
	


	/* initialize current node */
	currentnode = NULLNP;
	root = NULLNP;
	mouse_alive == FALSE;

	/* no protocol throttling except during panel loads */
	proto_mode = 0;

	/*
	** Request the use of the mouse and
	** keyboard, and host send/receive  application resources.
	*/
	request(MOUSE|KBD|RCV|SEND);

	/*
	** Main loop.
	*/
	for(;;) {
		/*
		** Release the CPU until the mouse or
		** the keyboard need service.
		*/
		wait(MOUSE|KBD|RCV);

		if ((button1()) && (mouse_alive == TRUE)) 
		{
			m_button12(1,mouse.xy);
		}
		else if ((button2()) && (mouse_alive == TRUE)) 
		{
			m_button12(2,mouse.xy);
		}
		else if ((button3()) && (mouse_alive == TRUE)) 
		{
			m_button3(mouse.xy);
		}
		else
			;

		/*
		** check at the keyboard for chars
		*/
		if ((kchar = kbdchar()) != -1)
		{
			if((char)kchar == 'Q') 
			{
			/*
			** If the user types a 'Q', then exit.
			*/
				gi_exit(root);
			}
			if((char)kchar == 'D') 
			{
			/*
			** If the user types a 'D', then initiate document.
			*/
				sendhost("**DOC**");
				continue;
			}
			if((char)kchar == 'B') 
			{
			/*
			** If the user types a 'B', then initiate BREAK.
			*/
				sendhost("**BREAK**");
				continue;
			}
			if((char)kchar == 'H') 
			{
			/*
			** If the user types a 'H', then initiate hardcopy.
			*/
				hardcopy(0);
				continue;
			}
			if((char)kchar == 'S') 
			{
			/*
			** If the user types a 'S', then report bitmap size.
			*/
				hardcopy(1);
				continue;
			}
		}


		/*
		** check at the host port for chars
		*/
		if ((hchar = rcvchar()) != -1)
		{
			hostcmd(&root,(char)hchar);
		}
		
	}
}


/*****************************************************************/
void gi_exit(panelroot)
struct node *panelroot;
{
	  /* restore the pre-panelfeature graphic interface window */
	if (panelroot != NULLNP)
		clearnode(panelroot);
	reshape(original_window);
	jrectf(Drect, F_CLR);
	exit();
}

/*****************************************************************/


void blitinit()
{
	tweed = &tweeddata;
	kapow = &kapowdata;
	busycursor = &cup;
/*	normcursor = &dstar; */
	normcursor = (Texture16 *)0;
	copyright = &cpyright;
	HKNOB = &hknob;
	VKNOB = &vknob;
	JEDI = &jedi;
	SBAR = &sbarbm;
	WBAR = &wbarbm;
	logo1 = Logo1;
	logo2 = Logo2;
	logo3 = Logo3;
	logodate = Logodate;
}


/*****************************************************************/
char itoh(i)
int i;
{
	switch(i)
	{
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		return('0'+i);
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
		return('a'+(i-10));
	default:
		warn("ERROR ITOH()");
		return('X');
	}
}

void hardcopy(szflag)
int szflag;
{
    /* if szflag != 0 then just compute the size and issue warning msg */
	char itoh();
	Point mxy;
	struct node *this;
	Rectangle r;
	int i, j, k;
	int width, height, fixwid;
	Word *scanline;
	unsigned short scanincr;
	char *bptr, *lptr;
	char hinib, lonib;
	char ch, mask;
	int rept;
	extern char *gethline();


	/* get a mouse click */
	while(button(1)==0);
	mxy = mouse.xy;
	while(button(1)==1);

	/* find the object */
	for (i=0; i<currentnode->numchildren; i++)
	{
		this = currentnode->child[i];
		r = raddp(this->window_rect,this->rel_to_origin);

		/* if we're on a panelfeature */
		if(ptinrect(mxy,r))
		{
			width = this->image->rect.corner.x;
			height = this->image->rect.corner.y;
			scanline = this->image->base;
			scanincr = this->image->width;
			break;
		}
	}
	
	if(i==currentnode->numchildren)
	{
		if (ptinrect(mxy,SCR_NAMEBOX))
		{
			/* just the active screen area */
			width = 872;
			height = 900;
			scanincr = display.width;
			scanline = display.base;
			scanline += 50*scanincr+13;
		}
		else
		{
			/* entire screen */
			/*
			width = Jrect.corner.x;
			height = Jrect.corner.y;
			*/
			width = physical.rect.corner.x-physical.rect.origin.x;
			height = physical.rect.corner.y-physical.rect.origin.y;
			scanincr = physical.width;
			scanline = physical.base;
		}
	}

	/* fix the width and mask for trailing bits */
	fixwid = width/8;
	mask = 0xff;
	if((j=width % 8) != 0)
	{
		fixwid++;
		mask = (char)(0x7f00 >> j);
	}
	width = fixwid * 8;

	
	if(szflag != 0) /* just report size of bitmap */
	{
		Sprintf(lbuf, "bytes : %d wide, %d high~bytes used: = %d",
			 fixwid, height, fixwid*height);
		warn(lbuf);
		return;
	}
	/* else do a real hardcopy */
	sendhost("**HARDCOPY**");
	cursswitch( busycursor );
	Sprintf(lbuf, "%d %d", width, height);
	sendhost(lbuf);
			
	for(j=0; j<height; j++, scanline+=scanincr)
	{
		/* slow down the terminal */
		if((j%7) == 6)
			nap(30);

		lptr = lbuf;

		for (k=0, bptr = (char *)scanline;
		     k<fixwid;
		     k++, bptr++)
		{
			ch = *bptr;
			rept=1;
			while ((*(bptr+1) == ch) &&
				 (k < (fixwid-2)) &&
				 (rept < 99))
			{
				k++;
				bptr++;
				rept++;
			}

			/* strip off any garbage */
			if(k==(fixwid-1))
			ch &= mask;

			hinib = (ch>>4) & 0x0f;
			lonib = ch & 0x0f;


			if(rept == 1)
			{
			    *lptr = itoh(hinib);
			    lptr++;
			    *lptr = itoh(lonib);
			    lptr++;
			}
			else if(rept == 2)
			{
			    *lptr = itoh(hinib);
			    lptr++;
			    *lptr = itoh(lonib);
			    lptr++;
			    *lptr = itoh(hinib);
			    lptr++;
			    *lptr = itoh(lonib);
			    lptr++;
			}
			else
			{
			    *lptr = '!';
			    lptr++;
			    *lptr = (char)(rept/10) + '0';
			    lptr++;
			    *lptr = (char)(rept%10) + '0';
			    lptr++;

			    *lptr = itoh(hinib);
			    lptr++;
			    *lptr = itoh(lonib);
			    lptr++;
			}
		}
		*lptr = '+';
		lptr++;
		*lptr = '\0';
		sendhost(lbuf);
		lptr = gethline();

	}
	sendhost("**END_OF_DATA**");
	cursswitch( normcursor );
}
