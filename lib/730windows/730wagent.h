static char S_S730wagenth[]=
	"@(#)730wagent.h, 1.6 - gregg.g.wonderly@att.com - 17:44:32, 1/12/93";

/* New agent calls provided by 730windows */

#define A_SCRCREATE		30		/* Create screen. */
#define A_SCRDESTROY	31		/* Destroy screen. */
#define A_SCRNEXT		32		/* Next screen. */
#define A_SCRPREV		33		/* Previous screen. */
#define A_HOSTNEW		34		/* Open new host connection. */
#define A_HOSTEXIT		35		/* Exit host connection. */
#define A_SETDIAL		36		/* Map dialer to host. */

/* Dialer specific agent calls */

#define A_DIALRESET		37		/* Reset dialer string to 0 bytes. */
#define A_DIALCONCAT	38		/* Append string to dialer. */
#define A_DIALREAD		39		/* Read dialer string. */
#define A_TILE			40		/* Tile the current window */
#define A_UNTILE		41		/* Untile the current window */
