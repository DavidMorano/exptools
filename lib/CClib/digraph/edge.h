#ifndef EDGE_H
#define EDGE_H 

/*
			AT&T - PROPRIETARY
	THIS DOCUMENT CONTAINS PROPRIETARY INFORMATION OF
	AT&T AND IS NOT TO BE DISCLOSED OR USED EXCEPT IN
	ACCORDANCE WITH APPLICABLE AGREEMENTS.

		Copyright (c) 1988 AT&T
		Unpublished & Not for Publication
		All Rights Reserved
*/

#ident "libsfmac:edge.h 1.2 1/30/89"
#ident "@(#)libsfmac:edge.h	1.2"


/**

.File Name edge.h

.Author M. T. Emanuel

.Date Created Oct. 10, 1988

.Description
This is the header file defining the edge class used in the directed
graph library.

.Constraints

.Notes

.See Also edge.c, universe.h, universe.c, node.h, and node.c

.Standards
This file conforms to the Dept. 54141 C Coding Standards
with modifications for the SUN environment and C++.

**/



// external classes
class node;
class universe;

class edge {

    friend class node;
    friend class universe;
    node *node_ptr_start;
    node *node_ptr_end;
    int edge_type;
    void *value;
    universe *my_universe;
    void set_nodes(node *node1, node *node2, universe *t,void *nvalue = (void *)0);
    


public:

    //constructors and destructors
    edge();
    edge(int edge_type);
    /*virtual*/ ~edge();

    // member functions
    void dug();
    void bug(void *nvalue = (void *)0);
    void *vug();

    int get_type();
    node *get_start();
    node *get_end();
};

#endif
