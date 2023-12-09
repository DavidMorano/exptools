
/**************************************************************************/
/* PANELFEATURES Package    Release:  1.0    Release Date: 1/15/89        */
/*                          Provider: J. D. Iorio  (speedy!jdi)           */
/**************************************************************************/

#include <dmd.h>
#include <font.h>

/*****************************************************************************
* void flipstring(*font,str, destblit, originpt, code_fn)
*
*	This function works like the string function and uses
*	the same parameters but prints the string vertically
*	with a 90 degree counter clockwise rotation.  The origin
*	point corresponds to the top left corner of a box for the
*	text which is 16 pixels wide by strwidth() pixels high.

* NOTE this function works only with fonts with a cell height of 16 or less.
*****************************************************************************/

void *flipstring(f,str, db, p, cfn)
Font *f;
char *str;
Bitmap *db;
Point p;
Code cfn;
{
	Bitmap *v, *h;
	int i,j,k,l;
	int wid;
	Rectangle r;
	
	unsigned Word d[16], build, bit;

	l = strwidth(f,str);

	h = balloc(Rect(0,0,l,16));		/* horiz blit */
	wid = h->width;
	j = wid * 16;			/* width in bits, with padding */
	v = balloc(Rect(0,0,16,j));		/* vert blit */

	texture(h,h->rect,&T_white,F_STORE);
	string(f,str,h,Pt(0,0),F_STORE);



	for (j=0; j<wid; j++)			/* for each word */
	{
		for (i=0; i<16; i++)
		{
			d[i] = h->base[j+i*wid];
		}
		
		for (i=0; i<16; i++)
		{
			build = 0;

			for (k=15; k>=0; k--)
			{
				bit = ror(d[k],i) & 0x0001;
				build |= rol(bit,15-k);
			}
			v->base[i+(wid-1-j)*16] = build;
		}
	}
	
	j = v->rect.corner.y - l;
	r = fRpt(Pt(v->rect.origin.x, j), v->rect.corner);
	bitblt(v,r,db,p,cfn);
	bfree(h);
	bfree(v);
}
