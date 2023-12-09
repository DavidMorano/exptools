/*ident	"@(#)C++env:incl-master/proto-headers/auevents.h	1.1" */

#ifndef __AUEVENTS_H
#define __AUEVENTS_H

/*	@(#)auevents.h 1.3 88/02/07 SMI; c2 secure	*/
/*
 * Integer, short and long representations of audit event classes
 * used by audit mechanism.
 *
 * audit.h must be included before this include file. AU_* values
 * are defined in audit.h.
 */
#ifndef _AUEVENTS_
#define	_AUEVENTS_

#define AU_ALL AU_DREAD|AU_DWRITE|AU_DACCESS|AU_DCREATE|AU_LOGIN|AU_SREAD|AU_SCTL  |AU_MINPRIV|AU_MAJPRIV|AU_ADMIN|AU_ASSIGN

struct event_cl {
	unsigned int event_mask;
	char *event_sname;
	char *event_lname;
} event_class[] ={
	AU_DREAD,	"dr",	"data_read",
	AU_DWRITE,	"dw",	"data_write",
	AU_DACCESS,	"da",	"data_access_change",
	AU_DCREATE,	"dc",	"data_create",
	AU_LOGIN,	"lo",	"login_logout",
	AU_SREAD,	"sr",	"spooler_read",
	AU_SCTL,	"sc",	"spooler_control",
	AU_MINPRIV,	"p0",	"minor_privilege",
	AU_MAJPRIV,	"p1",	"major_privilege",
	AU_ADMIN,	"ad",	"administrative",
	AU_ASSIGN,	"as",	"device_assign",
	AU_ALL,		"all",	"all"
};
#endif	_AUEVENTS_
 


#endif
