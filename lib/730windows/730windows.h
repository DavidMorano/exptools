static char S_S730windowsh[]=
	"@(#)730windows.h, 1.7 - gregg.g.wonderly@att.com - 17:44:33, 1/12/93";

#define APPL	"730Windows+"
#define TILE_SIZE	(65 + 6)
#define	LOWESTROM	0x080808L	/* Lowest ROM we are compatible with */
#define HIGHESTROM	0x080809L	/* Highest ROM we are compatible with */

long version();

/*version() <= HIGHESTROM) && \*/

#define __FNx(x)	(*((INTERFACE*)Sys[-1])->fn[x])

#define	has730wins( )			( (version() >= LOWESTROM) && \
					Sys[-1] && \
				((INTERFACE*)Sys[-1])->mag == MAGIC730WINDOWS )

#define	set730wins( p, onoff, b )	( has730wins() ? \
					__FNx( SETLABELS )(p,onoff,b) : 0 )

#define	chk730wins( )			( has730wins() ? \
						__FNx( CHKMOUSE )() : 0 )

#define	tile730wins( p )		( has730wins() ? \
						__FNx( TILEWINDOW )(p) : 0 )
#define	untile730wins( p )		( has730wins() ? \
						__FNx( UNTILEWINDOW )(p) : 0 )
#define	popout730wins( p )		( has730wins() ? \
						__FNx( POPOUTWINDOW )(p) : 0 )
#define	drawtile730wins( p, likep )	( has730wins() ? \
					__FNx( DRAWTILE )(p, likep) : 0 )

#define tiledrect(p)		(*((Rectangle *)&((p)->pad6[0])))
#define untiledrect(p)		(*((Rectangle *)&((p)->pad6[2])))

/* state3 flags */
#define wasTILED		0x00000001	/* tiledrect(p) is valid */
#define TILED			0x00000002	/* Process is tiled */
#define PLUSLABELS		0x00000004	/* Label bar has gadgetry */
#define	CURSORSWAP		0x00000008	/* Border cursor is up */

#define CURSUP(p)		((p)->state3 & CURSORSWAP)
#define SETCURSUP(p)		((p)->state3 |= CURSORSWAP)
#define CLRCURSUP(p)		((p)->state3 &= ~CURSORSWAP)
#define APPCURS(p)		(*((Texture16 **)&((p)->pad6[5])))

#define WASTILED(p)		((p)->state3 & wasTILED)
#define SETWASTILED(p)		((p)->state3 |= wasTILED)

#define SETTILED(p)		((p)->state3 |= TILED)
#define ISTILED(p)		((p)->state3 & TILED)
#define CLRTILED(p)		((p)->state3 &= ~TILED)

#define SETPLUSLABELS(p)	((p)->state3 |= PLUSLABELS)
#define HASPLUSLABELS(p)	((p)->state3 & PLUSLABELS)
#define CLRPLUSLABELS(p)	((p)->state3 &= ~PLUSLABELS)

#define SCREENCNT(p)		(((short *)(&(p)->pad5))[0])
#define SCREENS(p)		(*((SCREENARR **)&((p)->pad4[1])))
#define SCREENMAG(p)		((p)->pad4[0])

#define TILEMAP(p)		(*((Bitmap **)&((p)->pad6[4])))

#define	ISWPROC(p)		(((p)->text == WPROC_TEXT)||\
					((p)->text == WSTRT_TEXT))

/* Magic number used for various sanity checks */

#define	MAGIC730WINDOWS	0xdeadfeedL

typedef struct SCREENARR
{
	Rectangle r;		/* Regular rectangle on this screen */
	Rectangle tr;		/* Tiled rectangle on this screen */
	struct swapspacestr *scrn; /* ssp this structure is for */
	char onscrn;		/* swap to this screen */
	char once;		/* Push or Pull to this screen */
} SCREENARR;

typedef struct INTERFACE
{
	long mag;		/* MAGIC730WINDOWS */
	int (*fn[10])();	/* Pointers to functions provided */
} INTERFACE;

/* Indexs into .fn above */
#define	CHKMOUSE	0
#define	SETLABELS	1
#define TILEWINDOW	2
#define UNTILEWINDOW	3
#define POPOUTWINDOW	4
#define DRAWTILE	5

#include <730wagent.h>
