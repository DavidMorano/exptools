/*ident	"@(#)C++env:incl-master/proto-headers/arpa/inet.h	1.1" */

#ifndef __INET_H
#define __INET_H

/*
 * External definitions for functions in inet(3N)
 */

extern "C" {
        unsigned long    inet_addr(const char*);
        char*            inet_ntoa(struct in_addr);
        struct in_addr   inet_makeaddr(int, int);
        unsigned long    inet_network(const char*);
        int              inet_lnaof(struct in_addr);
        int              inet_netof(struct in_addr);
}

#endif
