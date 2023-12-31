/*ident	"@(#)C++env:incl-master/proto-headers/ar.h	1.1" */

#ifndef __AR_H
#define __AR_H

/*	@(#)ar.h 1.5 88/02/07 SMI; from UCB 4.1 83/05/03	*/

#define	ARMAG	"!<arch>\n"
#define	SARMAG	8

#define	ARFMAG	"`\n"

struct ar_hdr {
	char	ar_name[16];
	char	ar_date[12];
	char	ar_uid[6];
	char	ar_gid[6];
	char	ar_mode[8];
	char	ar_size[10];
	char	ar_fmag[2];
};
 


#endif
