/*ident	"@(#)C++env:incl-master/proto-headers/regcmp.h	1.1" */

#ifndef __REGCMP_H
#define __REGCMP_H

extern "C" {
	char *logname();
	char *re_comp(const char *);
	int re_exec(const char *);
}

#endif
