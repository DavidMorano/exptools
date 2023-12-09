
/*
			AT&T - PROPRIETARY
	THIS DOCUMENT CONTAINS PROPRIETARY INFORMATION OF
	AT&T AND IS NOT TO BE DISCLOSED OR USED EXCEPT IN
	ACCORDANCE WITH APPLICABLE AGREEMENTS.

		Copyright (c) 1988 AT&T
		Unpublished & Not for Publication
		All Rights Reserved
*/

#ident "libsfmac:edge.c 1.1 1/18/89"
#ident "@(#)libsfmac:edge.c	1.1"


/**

.File Name edge.c

.Author M. T. Emanuel

.Date Created Oct. 10, 1988

.Description
This is the source code for the member functions of the edge class.
It also includes constructors and destructors.

.Constraints

.Notes

.See Also

.Standards
This file conforms to the Dept. 54141 C Coding Standards
with modifications for the SUN environment and C++.

**/

/*	System Header Files					*/
#include <stdio.h>

/*	Project Header Files					*/

/*	Unit Header Files					*/
#include "edge.h"
#include "node.h"
#include "universe.h"

// edge constructor that should never be used
edge::edge()
{
	fprintf(stderr, "FATAL ERROR: edge created incorrectly\n");
	exit(ERROR);
}

edge::edge(int etype)
{
	edge_type = etype;
}

//edge constructor only called from the universe
void
edge::set_nodes(node *node1, node *node2,universe *t, void *nvalue)
{
	node_ptr_start = node1;
	node_ptr_end = node2;
	value = nvalue;
	my_universe = t;

	// add edges to node lists
	node1->add_edge_out(this);
	node2->add_edge_in(this);
	my_universe->add_edge(this);
}

edge::~edge()
{
	if(node_ptr_start != (node *)NULL)
		node_ptr_start->remove_edge_out(this);
	if(node_ptr_end!= (node *)NULL)
		node_ptr_end->remove_edge_in(this);

	if(my_universe != (universe *)NULL)
		my_universe->remove_edge(this);

}

// destroy an unqualified edge
void
edge::dug()
{
	node_ptr_start->remove_edge_out(this);
	node_ptr_end->remove_edge_in(this);
	my_universe->remove_edge(this);
}

// bind unqualified edge
void
edge::bug(void *nvalue)
{
	value = nvalue;
}

// value unqualified edge
void *
edge::vug()
{
	return(value);
}

// return starting node
node *
edge::get_start()
{
	return(node_ptr_start);
}

// return ending node
node *
edge::get_end()
{
	return(node_ptr_end);
}

// return edge type
int 
edge::get_type()
{
	return(edge_type);
}
