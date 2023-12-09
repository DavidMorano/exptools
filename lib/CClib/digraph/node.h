#ifndef NODE_H
/*
			AT&T - PROPRIETARY
	THIS DOCUMENT CONTAINS PROPRIETARY INFORMATION OF
	AT&T AND IS NOT TO BE DISCLOSED OR USED EXCEPT IN
	ACCORDANCE WITH APPLICABLE AGREEMENTS.

		Copyright (c) 1988 AT&T
		Unpublished & Not for Publication
		All Rights Reserved
*/

#ident "libsfmac:node.h 1.1 1/18/89"
#ident "@(#)libsfmac:node.h	1.1"


/**

.File Name node.h

.Author M. T. Emanuel

.Date Created Oct. 10, 1988

.Description
This is the class definitions for the object node
used in the directed graph library

.Constraints

.Notes

.See Also

.Standards
This file conforms to the Dept. 54141 C Coding Standards
with modifications for the SUN environment and C++.

**/

#define NODE_H

/*	System Header Files					*/
#include <String.h>

/*	Project Header Files					*/
#include "general.h"

/*	Unit Header Files					*/

// external class definitions
class sllist;
class int_sllist;
class universe;
class edge;

class node {
    friend class universe;
    friend class edge;

    String name;      		         // node name

    sllist *inpoint_edges;              // linked list of all inpointing
                                        // edges to this node

    sllist *outpoint_edges;             // linked list of all outpointing    
                                        // edges to this node
    void *value;

    universe *my_universe;

   // private functions
   void add_edge_in(const edge *new_edge);
   void add_edge_out(const edge *new_edge);
   void remove_edge(edge *del_edge);
   void remove_edge_in(const edge *del_edge);
   void remove_edge_out(edge *del_edge);

public:
    
    node(const String& node_name, universe *t,void *nvalue = (void*)0);
    /*virtual*/ ~node();

    int dun();

    int dan();
    int din();
    int don();

    int ding(const int edge_type);
    int dong(const int edge_type);
    int dang(const int edge_type);

    int dig();
    int dog();
    int dag();

    int digg(const int edge_type);
    int dogg(const int edge_type);
    int dagg(const int edge_type);

    int dign(node *node2);
    int dogn(node *node2);
    int dagn(node *node2);

    int xun();
    int xip(const int edge_type,const node *node2);
    int xop(const int edge_type,const node *node2);
    int xap(const int edge_type,const node *node2);

    sllist *sip();
    sllist *sop();
    sllist *sap();

    int_sllist *sig();
    int_sllist *sog();
    int_sllist *sag();

    int_sllist *sign(const node *node2);
    int_sllist *sogn(const node *node2);
    int_sllist *sagn(const node *node2);

    sllist *san();
    sllist *sin();
    sllist *son();

    sllist *sing(const int edge_type);
    sllist *song(const int edge_type);
    sllist *sang(const int edge_type);

    node *bip(const int edge_type, node *node2, void *nvalue = (void*)0); 
    node *bop(const int edge_type, node *node2, void *nvalue = (void*)0);
    node *bap(const int edge_type, node *node2, void *nvalue = (void*)0);


    void *vip(const int edge_type, const node *node2);
    void *vop(const int edge_type, const node *node2);

    node *cap(edge *nedge, node *node2, void *nvalue = (void*)0);
    node *cip(edge *nedge, node *node2, void *nvalue = (void*)0);
    node *cop(edge *nedge, node *node2, void *nvalue = (void*)0);


   void bun(void *nvalue = (void *)0);
   void *vun();

   // utility functions
    String get_name() {return(name);}
};
#endif
