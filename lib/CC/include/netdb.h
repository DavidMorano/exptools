/*ident	"@(#)C++env:incl-master/proto-headers/netdb.h	1.1" */

#ifndef __NETDB_H
#define __NETDB_H

#define getrpcent ______getrpcent
#define gethostbyname ______gethostbyname
#define gethostbyaddr ______gethostbyaddr
#define gethostent ______gethostent
#define sethostent ______sethostent
#define endhostent ______endhostent
#define getnetbyname ______getnetbyname
#define getnetbyaddr ______getnetbyaddr
#define getnetent ______getnetent
#define setnetent ______setnetent
#define endnetent ______endnetent
#define getservbyname ______getservbyname
#define getservbyport ______getservbyport
#define getservent ______getservent
#define setservent ______setservent
#define endservent ______endservent
#define getprotobyname ______getprotobyname
#define getprotobynumber ______getprotobynumber
#define getprotoent ______getprotoent
#define setprotoent ______setprotoent
#define endprotoent ______endprotoent

/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)netdb.h 1.9 88/02/07 SMI from UCB 5.7 5/12/86
 */

/*
 * Structures returned by network
 * data base library.  All addresses
 * are supplied in host order, and
 * returned in network order (suitable
 * for use in system calls).
 *
 */
struct	hostent {
	char	*h_name;	/* official name of host */
	char	**h_aliases;	/* alias list */
	int	h_addrtype;	/* host address type */
	int	h_length;	/* length of address */
	char	**h_addr_list;	/* list of addresses from name server */
#define	h_addr	h_addr_list[0]	/* address, for backward compatiblity */
};

/*
 * Assumption here is that a network number
 * fits in 32 bits -- probably a poor one.
 */
struct	netent {
	char		*n_name;	/* official name of net */
	char		**n_aliases;	/* alias list */
	int		n_addrtype;	/* net address type */
	unsigned long	n_net;		/* network # */
};

struct	servent {
	char	*s_name;	/* official service name */
	char	**s_aliases;	/* alias list */
	int	s_port;		/* port # */
	char	*s_proto;	/* protocol to use */
};

struct	protoent {
	char	*p_name;	/* official protocol name */
	char	**p_aliases;	/* alias list */
	int	p_proto;	/* protocol # */
};

struct rpcent {
	char	*r_name;	/* name of server for this rpc program */
	char	**r_aliases;	/* alias list */
	int	r_number;	/* rpc program number */
};

struct hostent	*gethostbyname(), *gethostbyaddr(), *gethostent();
struct netent	*getnetbyname(), *getnetbyaddr(), *getnetent();
struct servent	*getservbyname(), *getservbyport(), *getservent();
struct protoent	*getprotobyname(), *getprotobynumber(), *getprotoent();
struct rpcent	*getrpcbyname(), *getrpcbynumber(), *getrpcent();

/*
 * Error return codes from gethostbyname() and gethostbyaddr()
 * (when using the resolver)
 */

extern  int h_errno;	

#define	HOST_NOT_FOUND	1 /* Authoritive Answer Host not found */
#define	TRY_AGAIN	2 /* Non-Authoritive Host not found, or SERVERFAIL */
#define	NO_RECOVERY	3 /* Non recoverable errors, FORMERR, REFUSED, NOTIMP */
#define NO_ADDRESS	4 /* Valid host name, no address, look for MX record */

 

#undef endprotoent
#undef getprotobynumber
#undef gethostbyname
#undef getservbyname
#undef sethostent
#undef setservent
#undef getprotoent
#undef endnetent
#undef getprotobyname
#undef getrpcent
#undef setprotoent
#undef getnetent
#undef getnetbyaddr
#undef getnetbyname
#undef endhostent
#undef endservent
#undef setnetent
#undef getservbyport
#undef gethostent
#undef getservent
#undef gethostbyaddr

extern "C" {
	hostent*	gethostbyname(const char*);
	hostent*	gethostbyaddr(const char*, int, int);
	hostent*	gethostent();
	int		sethostent(int);
	int		endhostent();

	netent*		getnetbyname(const char*);
	netent*		getnetbyaddr(long, int);
	netent*		getnetent();
	int		setnetent(int);
	int		endnetent();

	servent*	getservbyname(const char*, const char*);
	servent*	getservbyport(int, const char*);
	servent*	getservent();
	int		setservent(int);
	int		endservent();

	protoent*	getprotobyname(const char*);
	protoent*	getprotobynumber(int);
	protoent*	getprotoent();
	int		setprotoent(int);
	int		endprotoent();
	rpcent*		getrpcent();
	rpcent*		getrpcbyname(const char *);
	rpcent*		getrpcbynumber(int);
	int 		setrpcent(int);
	int 		endrpcent();
}

#endif
