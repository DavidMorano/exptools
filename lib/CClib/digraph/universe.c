/*
			AT&T - PROPRIETARY
	THIS DOCUMENT CONTAINS PROPRIETARY INFORMATION OF
	AT&T AND IS NOT TO BE DISCLOSED OR USED EXCEPT IN
	ACCORDANCE WITH APPLICABLE AGREEMENTS.

		Copyright (c) 1988 AT&T
		Unpublished & Not for Publication
		All Rights Reserved
*/

#ident "libsfmac:universe.c 1.1 1/18/89"
#ident "@(#)libsfmac:universe.c	1.1"


/**

.File Name
	universe.c

.Author
	M. T. Emanuel

.Date Created
	Oct 10, 1988

.Description
	This file contains the member functions for the universe
	class

.Constraints

.Notes

.See Also

.Standards
This file conforms to the Dept. 54141 C Coding Standards
with modifications for the SUN environment and C++.

**/


/*	System Header Files					*/
#include <stdio.h>
#include <String.h>

/*	Project Header Files					*/
#include "sllist.h"
#include "int_sllist.h"
#include "Hash.h"

/*	Unit Header Files					*/
#include "universe.h"
#include "node.h"
#include "edge.h"

/*	Constant Definitions					*/

/*	Macro Definitions and inlines				*/

/*	Typedefs, Structure and Union Declarations		*/

/*	External Variable Declarations				*/

/*	Global Variable Definitions Outside of this File	*/

/*	Global Variable Definitions Restricted to this File	*/

/*	Declarations of Functions External to this File		*/

/*	Declarations of Functions Defined in this File		*/



// These routines are used to create the components of a directed graph.
// The universe must first be created. Edges are created using 
// member functions of the universe.

/**

.Name
	universe constructor

.Library Name
	libsfmac

.Description
	This function is the universe constructor it is implicitly
	called when an instance of the universe is declared.
	This constructor creates a universe without a name.

.Preconditions

.Constraints

.Side Effects

.Return Values

.Notes

.See Also

**/

/*	Begin Synopsis	*/
universe::universe():hashtable(1000, "universe")
/* 	End Synopsis	*/
{
	if(exist == 1)
	{
		// this is application specific to the SFMAC
		// if multiple universes are desired remove
		fprintf(stderr, "FATAL ERROR: only one universe may exist\n");
		exit(ERROR);
	}
	else
	{
		nodes = new sllist;
		edges = new sllist;
		value = (void *)NULL;
		exist = 1;
	}
}

/**

.Name
	universe constructor

.Library Name
	libsfmac

.Description
	This is the universe constructor it is implictly called
	when an instance of the universe is declared.
	it takes a name of the universe as a argument.

.Preconditions

.Constraints

.Side Effects

.Return Values

.Notes

.See Also

**/

/*	Begin Synopsis	*/
// constructor
universe::universe(const String& un_name):hashtable(1000,"universe")
/* 	End Synopsis	*/
{
	if(exist == 1)
	{
		// this is application dependent for sfmac
		// it should be removed if multiple universes exist
		fprintf(stderr, "FATAL ERROR: only one universe may exist\n");
		exit(ERROR);
	}
	else
	{	
		name = un_name;
		nodes = new sllist;
		edges = new sllist;
		value = (void *)NULL;
		exist = 1;
	}
}

/**

.Name
	universe destructor

.Library Name
	libsfmac

.Description
	This function is implicitly called when the universe
	is destroyed. It is a virtual function.

.Preconditions

.Constraints

.Side Effects

.Return Values

.Notes

.See Also

**/

/*	Begin Synopsis	*/
universe::~universe()
/*	End Synopsis	*/
{
	exist = 0;
	delete nodes;
	delete edges;
}

/**

.Name
	cun

.Library Name
	libsfmac

.Description
	Creates an unqualified node in the universe.

.Preconditions

.Constraints

.Side Effects

.Return Values

.Notes

.See Also

**/

/*	Begin Synopsis	*/
// create an unqualified node
int
universe::cun(String& node_name, node *new_node)
/* 	End Synopsis	*/
{
	int ret;

	// if the node is in the hash table NULL will not be
	// returned, and it already has been added to the universe
	if(((node*)hashtable.get(node_name)) != (node*)NULL)
	{
		return(NOTHING);
	}

	// the node was not found in the hashtable so add it
	if((hashtable.put(node_name, new_node)) == ERROR)
	{
		return(ERROR);
	}

	// add the node to the list of nodes for this 
	ret = nodes->push((void*)new_node);


	return(ret);

}

/**

.Name
	universe constructor

.Library Name
	libsfmac

.Description
	This is the universe constructor it is implictly called
	when an instance of the universe is declared.
	it takes a name of the universe as a argument.

.Preconditions

.Constraints

.Side Effects

.Return Values

.Notes

.See Also

**/

/*	Begin Synopsis	*/
// create adjacent pairs
node *
universe::cap(node *node1, edge *nedge, node *node2, void *nvalue)
/*	End Synopsis	*/
{
	node *tmp_node;

	// switch node1 and node2 to create first edge
	if((tmp_node = cop(node2, nedge, node1, nvalue)) == (node*)NULL)
	{
		return(tmp_node);
	}

	tmp_node = cop(node1, nedge, node2, nvalue);

	return(tmp_node);

}

/**

.Name
	cip

.Library Name
	libsfmac

.Description
	Create an impointing pair

.Preconditions

.Constraints

.Side Effects

.Return Values

.Notes

.See Also

**/

/*	Begin Synopsis	*/
// create inpointing pairs
node *
universe::cip(node *node1, edge *nedge, node *node2, void *nvalue)
/*	End Synopsis	*/
{
	node *tmp_node;

	// nodes are switched to create inpointing
	tmp_node = cop(node2, nedge, node1, nvalue);

	return(tmp_node);

}

/**

.Name
	cop

.Library Name
	libsfmac

.Description
	Create an outpointing pair

.Preconditions

.Constraints

.Side Effects

.Return Values

.Notes

.See Also

**/

/*	Begin Synopsis	*/
// create outpointing pairs
node *
universe::cop(node *node1, edge *nedge, node *node2, void *nvalue)
/*	End Synopsis	*/
{

	int_sllist *tmp_intlist;
	int i, *tmp_type;

	// get the list of outpointing edges for these nodes
	tmp_intlist = sogn(node1, node2);


	// traverse list of edges types to see if one exists
	for(i = 0; (tmp_type = (int *)tmp_intlist->nth(i)) != (int *)NULL; i++)
	{
		// if edge already exists return
		if( *tmp_type == nedge->get_type())
		{
			return(node1);
		}
	}


	// create new edge
	nedge->set_nodes(node1, node2, this, nvalue);

	// add to edges in the universe
	if((edges->push((void *)nedge)) == ERROR)
	{
		return((node*)NULL);
	}
	
	return(node1);

}

/**

.Name
	dun

.Library Name
	libsfmac

.Description
	This function destroys an unqualified node
	
.Preconditions

.Constraints

.Side Effects

.Return Values

.Notes

.See Also

**/

/*	Begin Synopsis	*/
int
universe::dun(node *node1)
/* 	End Synopsis	*/
{

	// destroy all edges to the node
	if((node1->dag()) == ERROR)
		return(ERROR);

	// remove node from hash table
	if((hashtable.rm(node1->get_name())) == ERROR)
		return(ERROR);
	
	// remove node from node list 
	if((nodes->remove((void *)node1)) == ERROR)
		return(ERROR);
	
	// delete the node 
	delete node1;
	return(SUCCESS);

}
	
/**

.Name
	dan

.Library Name
	libsfmac

.Description
	This function destroys adjacent nodes.

.Preconditions

.Constraints

.Side Effects

.Return Values

.Notes

.See Also

**/

/*	Begin Synopsis	*/
// destroy adjacent nodes 
int
universe::dan(node *node1)
/*	End Synopsis	*/
{

	// destroy inpointing nodes of a node
	if((din(node1)) == ERROR)
		return(ERROR);

	// destroy outpointing nodes of a node
	if((don(node1)) == ERROR)
		return(ERROR);

	return(SUCCESS);

}

/**

.Name
	din

.Library Name
	libsfmac

.Description
	Destroy inpointing nodes.

.Preconditions

.Constraints

.Side Effects

.Return Values

.Notes

.See Also

**/

/*	Begin Synopsis	*/
int
universe::din(node *node1)
/*	End Synopsis	*/
{
	sllist *in_set;
	node *nxt_node;
	int i;

	// get the list of nodes with inpointing edges
	if((in_set= sin(node1)) == (sllist *)NULL)
		return(NOTHING);
	
	for(i = 0; (nxt_node = (node *)in_set->nth(i)) != (node *)NULL; i++)
	{
		// loop back case
		if(nxt_node == node1)
		{
			if((dign(node1, node1)) == ERROR)
				return(ERROR);
		}
		else if((dun(nxt_node)) == ERROR)
		{
			return(ERROR);
		}
	}

	return(SUCCESS);
}

/**

.Name
	don

.Library Name
	libsfmac

.Description
	This function destroys the outpointing nodes of
	a given node.

.Preconditions

.Constraints

.Side Effects

.Return Values

.Notes

.See Also

**/

/*	Begin Synopsis	*/
// destory outpoint nodes
int
universe::don(node *node1)
/*	End Synopsis	*/
{
	sllist *out_set;
        node *nxt_node;
        int i;

        if((out_set = son(node1)) == (sllist *)NULL)
		return(NOTHING);

	for(i = 0; (nxt_node = (node *)out_set->nth(i)) != (node *)NULL; i++)
	{
		// loop back case
		if(nxt_node == node1)
		{
			if((dogn(node1, node1)) == ERROR)
			{
				return(ERROR);
			}

		}
		else if((dun(nxt_node)) == ERROR)
		{
			return(ERROR);
		}
	}
	return(SUCCESS);
}
/**

.Name
	ding

.Library Name
	libsfmac

.Description
	Destroy inpointing nodes given an edge type

.Preconditions

.Constraints

.Side Effects

.Return Values

.Notes

.See Also

**/

/*	Begin Synopsis	*/
int
universe::ding(node *node1, const int edge_type)
/* 	End Synopsis 	*/
{
	sllist *in_set;
        int i;
        node *nxt_node;

	if((in_set = sing(node1, edge_type)) == (sllist *)NULL)
		return(SUCCESS);

	// destroy each node in the list
	for(i = 0; (nxt_node = (node *)in_set->nth(i)) != (node *)NULL; i++)
	{
		if(nxt_node == node1)
		{
			// i already have the list of nodes
			// so destroying the edges shouldn't do
			// any thing
			if((digg(node1, edge_type)) == ERROR)
			{
				return(ERROR);
			}
		}
		else if((dun(nxt_node)) == ERROR)
		{
			return(ERROR);
		}
	}
	return(SUCCESS);

}

/**

.Name
	dong

.Library Name
	libsfmac

.Description
	Destroy outpointing nodes given an edge type

.Preconditions

.Constraints

.Side Effects

.Return Values

.Notes

.See Also

**/

/*	Begin Synopsis	*/
int
universe::dong(node *node1, const int edge_type)
/*	End Synopsis	*/
{
	sllist *out_set;
	int i;
	node *nxt_node;

	if((out_set = song(node1, edge_type)) == (sllist *)NULL)
	{
		return(NOTHING);
	}

	// destroy each node in the list
	for(i = 0; (nxt_node = (node *)out_set->nth(i)) != (node *)NULL; i++)
	{
		if(nxt_node == node1)
		{
			if((dogg(node1, edge_type)) == ERROR)
			{
				return(ERROR);
			}
		}
		else if((dun(nxt_node)) == ERROR)
		{
			return(ERROR);
		}
	}
	return(SUCCESS);
}
/**

.Name
	dang

.Library Name
	libsfmac

.Description
	Destroy adjacent nodes given an edge type

.Preconditions

.Constraints

.Side Effects

.Return Values

.Notes

.See Also

**/

/*	Begin Synopsis	*/
int
universe::dang(node *node1, const int edge_type)
{
/*	End Synopsis 	*/
	if((ding(node1, edge_type)) == ERROR)
		return(ERROR);
	if((dong(node1, edge_type)) == ERROR)
		return(ERROR);

	return(SUCCESS);
}
/**

.Name
	dig

.Library Name
	libsfmac

.Description
	Destroy inpointing edges of a node

.Preconditions

.Constraints

.Side Effects

.Return Values

.Notes

.See Also

**/

/*	Begin Synopsis	*/
int
universe::dig(node *node1)
/*	End Synopsis	*/
{
	if((node1->dig()) == ERROR)
		return(ERROR);

	return(SUCCESS);
}

/**

.Name
	dog

.Library Name
	libsfmac

.Description
	Destroy outpointing edges of a node

.Preconditions

.Constraints

.Side Effects

.Return Values

.Notes

.See Also

**/

/*	Begin Synopsis	*/
int
universe::dog(node *node1)
/*	End Synopsis 	*/
{
	if((node1->dog()) == ERROR)
		return(ERROR);

	return(SUCCESS);
}
/**

.Name
	dag

.Library Name
	libsfmac

.Description
	destroy adjacent edges of a node

.Preconditions

.Constraints

.Side Effects

.Return Values

.Notes

.See Also

**/

/*	Begin Synopsis	*/
int
universe::dag(node *node1)
/*	End Synopsis	*/
{

	if((node1->dog()) == ERROR)
		return(ERROR);

	if((node1->dig()) == ERROR)
		return(ERROR);

	return(SUCCESS);

}
/**

.Name
	digg

.Library Name
	libsfmac

.Description
	destroy inpointing edges given an edge type

.Preconditions

.Constraints

.Side Effects

.Return Values

.Notes

.See Also

**/

/*	Begin Synopsis	*/
int
universe::digg(node *node1, const int edge_type)
/*	End Synopsis 	*/
{

	return((node1->digg(edge_type)));

}

/**

.Name
	dogg

.Library Name
	libsfmac

.Description
	destroy outpointing edges given an edge type

.Preconditions

.Constraints

.Side Effects

.Return Values

.Notes

.See Also

**/

/*	Begin Synopsis	*/
int
universe::dogg(node *node1, const int edge_type)
/*	End Synopsis	*/
{
	return((node1->dogg(edge_type)));
}

/**

.Name
	dagg

.Library Name
	libsfmac

.Description
	destroy adjacent edges given an edge type

.Preconditions

.Constraints

.Side Effects

.Return Values

.Notes

.See Also

**/

/*	Begin Synopsis	*/
int
universe::dagg(node *node1, const int edge_type)
/*	End Synopsis	*/
{
	if((node1->digg(edge_type)) == ERROR)
		return(ERROR);

	if((node1->dogg(edge_type)) == ERROR)
		return(ERROR);

	return(SUCCESS);
}

/**

.Name
	dign

.Library Name
	libsfmac

.Description
	Destroy inpointing edges give two edges

.Preconditions

.Constraints

.Side Effects

.Return Values

.Notes

.See Also

**/

/*	Begin Synopsis	*/
int
universe::dign(node *node1, node *node2)
/*	End Synopsis	*/
{

	if((node1->dign(node2)) == ERROR)
		return(ERROR);

	return(SUCCESS);
}

/**

.Name
	dogn

.Library Name
	libsfmac

.Description
	Destroy outpoint edges given a node

.Preconditions

.Constraints

.Side Effects

.Return Values

.Notes

.See Also

**/

/*	Begin Synopsis	*/
int
universe::dogn(node *node1, node *node2)
/*	End Synopsis	*/
{
	if((node1->dogn(node2)) == ERROR)
		return(ERROR);

	return(SUCCESS);
}

/**

.Name
	dagn

.Library Name
	libsfmac

.Description
	Destroy adjacent edges given a node

.Preconditions

.Constraints

.Side Effects

.Return Values

.Notes

.See Also

**/

/*	Begin Synopsis	*/
int
universe::dagn(node *node1, node *node2)
/*	End Synopsis 	*/
{
	if((node1->dign(node2)) == ERROR)
		return(ERROR);

	if((node1->dogn(node2)) == ERROR)
		return(ERROR);

	return(SUCCESS);
}

/**

.Name
	dug

.Library Name
	libsfmac

.Description
	Destroy unqualified edge

.Preconditions

.Constraints

.Side Effects

.Return Values

.Notes

.See Also

**/

/*	Begin Synopsis	*/
void
universe::dug(edge *des_edge)
/*	End Synopsis	*/
{
	edges->remove((void*)des_edge);
	des_edge->dug();
	delete des_edge;

}
/**

.Name
	xun

.Library Name
	libsfmac

.Description
	check for the existance of an unqualified node

.Preconditions

.Constraints

.Side Effects

.Return Values

.Notes

.See Also

**/

/*	Begin Synopsis	*/
int
universe::xun(const node *node1)
/*	End Synopsis	*/
{

	if(node1 == (node *)NULL)
		return(FALSE);

	if((node*)hashtable.get(node1->get_name()) == (node*)NULL)
		return(FALSE);
	else
		return(TRUE);
}

/**

.Name
	xip

.Library Name
	libsfmac

.Description
	check for the existance of an inpointing pair

.Preconditions

.Constraints

.Side Effects

.Return Values

.Notes

.See Also

**/

/*	Begin Synopsis	*/
int
universe::xip(const node *node1, const int edge_type, const node *node2)
/*	End Synopsis 	*/
{
	int ret;
	ret = node1->xip(edge_type, node2);
	
	return(ret);
}

/**

.Name
	xop

.Library Name
	libsfmac

.Description
	check for the existance of an outpointing pair

.Preconditions

.Constraints

.Side Effects

.Return Values

.Notes

.See Also

**/

/*	Begin Synopsis	*/
int
universe::xop(const node *node1, const int edge_type,const node *node2)
/*	End Synopsis	*/
{
	int ret;
	
	ret = node1->xop(edge_type, node2);

	return(ret);
}

/**

.Name
	xap

.Library Name
	libsfmac

.Description
	Check for existance of adjacent pair

.Preconditions

.Constraints

.Side Effects

.Return Values

.Notes

.See Also

**/

/*	Begin Synopsis	*/
int
universe::xap(const node *node1, const int edge_type, const node *node2)
/*	End Synopsis	*/
{
	int ret, ret1;

	ret = node1->xop(edge_type, node2);
	ret1 = node1->xip(edge_type, node2);

	if((ret == TRUE) &&  (ret1 == TRUE))
		return(TRUE);

	else 
		return(FALSE);

}

/**

.Name
	ssun

.Library Name
	libsfmac

.Description
	get the set of unqualified nodes

.Preconditions

.Constraints

.Side Effects

.Return Values

.Notes

.See Also

**/

/*	Begin Synopsis	*/
sllist *
universe::ssun()
/*	End Synopsis	*/
{
	sllist *node_list;

	// returns a copy of the internal list
	 node_list = new sllist(nodes);

	return(node_list);
}

/**

.Name
	san

.Library Name
	libsfmac

.Description
	Get the set of adjacent nodes to a particular node

.Preconditions

.Constraints

.Side Effects

.Return Values

.Notes

.See Also

**/

/*	Begin Synopsis	*/
sllist *
universe::san(const node *node1)
/*	End Synopsis	*/
{
	if(node1 != (node*)NULL)
	{
	 	return(node1->san());
	}
	else
	{
		return((sllist*)NULL);
	}
}

/**

.Name
	sin

.Library Name
	libsfmac

.Description
	GEt the set of inpointing nodes

.Preconditions

.Constraints

.Side Effects

.Return Values

.Notes

.See Also

**/

/*	Begin Synopsis	*/
sllist *
universe::sin(const node *node1)
/*	End Synopsis	*/
{
	return(node1->sin());
}

/**

.Name
	son

.Library Name
	libsfmac

.Description
	Get the set of outpointing nodes

.Preconditions

.Constraints

.Side Effects

.Return Values

.Notes

.See Also

**/

/*	Begin Synopsis	*/
sllist *
universe::son(const node *node1)
/*	End Synopsis	*/
{
	return(node1->son());
}

/**

.Name
	sing

.Library Name
	libsfmac

.Description
	setn of inpointing nodes given an edge type

.Preconditions

.Constraints

.Side Effects

.Return Values

.Notes

.See Also

**/

/*	Begin Synopsis	*/
sllist*
universe::sing(const node *node1,const int edge_type)
/*	End Synopsis	*/
{
	return(node1->sing(edge_type));
}

/**

.Name
	song

.Library Name
	libsfmac

.Description
	Set of outpointing nodes given an edge type

.Preconditions

.Constraints

.Side Effects

.Return Values

.Notes

.See Also

**/

/*	Begin Synopsis	*/
sllist *
universe::song(const node *node1,const int edge_type)
/*	End Synopsis	*/
{
	return(node1->song(edge_type));
}

/**

.Name
	sang

.Library Name
	libsfmac

.Description
	Set of adjacent nodes given an edge type

.Preconditions

.Constraints

.Side Effects

.Return Values

.Notes

.See Also

**/

/*	Begin Synopsis	*/
sllist *
universe::sang(const node *node1, const int edge_type)
/*	End Synopsis	*/
{
	return(node1->sang(edge_type));
}

/**

.Name
	sip

.Library Name
	libsfmac

.Description
	Set of inpointing edges of a node

.Preconditions

.Constraints

.Side Effects

.Return Values

.Notes

.See Also

**/

/*	Begin Synopsis	*/
sllist *
universe::sip(const node *node1)
/*	End Synopsis 	*/
{
	return(node1->sip());
}

/**

.Name
	sop

.Library Name
	libsfmac

.Description
	Set of outpointing edges of a node

.Preconditions

.Constraints

.Side Effects

.Return Values

.Notes

.See Also

**/

/*	Begin Synopsis	*/
sllist *
universe::sop(const node *node1)
/*	End Synopsis	*/
{
	return(node1->sop());
}

/**

.Name
	sap

.Library Name
	libsfmac

.Description
	Set of all adjacent edges of a node

.Preconditions

.Constraints

.Side Effects

.Return Values

.Notes

.See Also

**/

/*	Begin Synopsis	*/
sllist *
universe::sap(const node *node1)
/*	End Synopsis	*/
{
	return(node1->sap());
}

/**

.Name
	sig

.Library Name
	libsfmac

.Description
	Set of inpointing edge types

.Preconditions

.Constraints

.Side Effects

.Return Values

.Notes

.See Also

**/

/*	Begin Synopsis	*/
int_sllist *
universe::sig(const node *node1)
/*	End Synopsis	*/
{
	return(node1->sig());
}

/**

.Name
	sog

.Library Name
	libsfmac

.Description
	SEt of inpointing edge types

.Preconditions

.Constraints

.Side Effects

.Return Values

.Notes

.See Also

**/

/*	Begin Synopsis	*/
int_sllist *
universe::sog(const node *node1)
/* 	End Synopsis	*/
{
	return(node1->sog());
}

/**

.Name
	sag

.Library Name
	libsfmac

.Description
	Set of adjacent edge types

.Preconditions

.Constraints

.Side Effects

.Return Values

.Notes

.See Also

**/

/*	Begin Synopsis	*/
int_sllist *
universe::sag(const node *node1)
/*	End Synopsis	*/
{
	return(node1->sag());
}

/**

.Name
	sign

.Library Name
	libsfmac

.Description
	Set of inpointing edge types given a node

.Preconditions

.Constraints

.Side Effects

.Return Values

.Notes

.See Also

**/

/*	Begin Synopsis	*/
int_sllist *
universe::sign(const node *node1,const node *node2)
/*	End Synopsis	*/
{
	return(node1->sign(node2));
}

/**

.Name
	sogn

.Library Name
	libsfmac

.Description
	SEt of outpointing edge types given a node

.Preconditions

.Constraints

.Side Effects

.Return Values

.Notes

.See Also

**/

/*	Begin Synopsis	*/
int_sllist *
universe::sogn(const node *node1, const node *node2)
/*	End Synopsis	*/
{
	return(node1->sogn(node2));
}

/**

.Name
	sagn

.Library Name
	libsfmac

.Description
	Set of adjacent edge types given a node

.Preconditions

.Constraints

.Side Effects

.Return Values

.Notes

.See Also

**/

/*	Begin Synopsis	*/
int_sllist *
universe::sagn(const node *node1,const node *node2)
/*	End Synopsis	*/
{
	return(node1->sagn(node2));
}

/**

.Name
	node_from_name

.Library Name
	libsfmac

.Description
	return a node based on its name

.Preconditions

.Constraints

.Side Effects

.Return Values

.Notes

.See Also

**/

/*	Begin Synopsis	*/
node *
universe::node_from_name(const String& node_name)
/*	End Synopsis 	*/
{
	node *tmp_node;

	tmp_node = (node *)hashtable.get(node_name);
	return(tmp_node);
}

/**

.Name
	remove_edge

.Library Name
	libsfmac

.Description
	remove an edge from the list in the universe

.Preconditions

.Constraints

.Side Effects

.Return Values

.Notes

.See Also

**/

/*	Begin Synopsis	*/
void
universe::remove_edge(const edge *del_edge)
/*	End Synopsis	*/
{

	edges->remove((void*)del_edge);
}

/**

.Name
	bus

.Library Name
	libsfmac

.Description
	Bind unqualified space

.Preconditions

.Constraints

.Side Effects

.Return Values

.Notes

.See Also

**/

/*	Begin Synopsis	*/
void
universe::bus(void *nvalue)
/*	End Synopsis	*/
{
	value = nvalue;
}

/**

.Name
	vus

.Library Name
	libsfmac

.Description
	value of an unqualified space

.Preconditions

.Constraints

.Side Effects

.Return Values

.Notes

.See Also

**/

/*	Begin Synopsis	*/
void *
universe::vus()
/*	End Synopsis	*/
{
   	return(value);
}

/**

.Name
	bun

.Library Name
	libsfmac

.Description
	bind unqualified node

.Preconditions

.Constraints

.Side Effects

.Return Values

.Notes

.See Also

**/

/*	Begin Synopsis	*/
void
universe::bun(node *node1, void *nvalue)
/*	End Synopsis	*/
{
	node1->bun(nvalue);
}

/**

.Name
	vun

.Library Name
	libsfmac

.Description
	value unqualified node

.Preconditions

.Constraints

.Side Effects

.Return Values

.Notes

.See Also

**/

/*	Begin Synopsis	*/
void *
universe::vun(const node *node1)
/*	End Synopsis	*/
{
	return(node1->vun());
}

/**

.Name
	bip

.Library Name
	libsfmac

.Description
	bind inpointing edges to value

.Preconditions

.Constraints

.Side Effects

.Return Values

.Notes

.See Also

**/

/*	Begin Synopsis	*/
node *
universe::bip(node *node1,const int edge_type, node *node2, void *nvalue)
/*	End Synopsis	*/
{
	return(node1->bip(edge_type, node2, nvalue));
}

/**

.Name
	bop

.Library Name
	libsfmac

.Description
	bind outpointing edges to value

.Preconditions

.Constraints

.Side Effects

.Return Values

.Notes

.See Also

**/

/*	Begin Synopsis	*/
node *
universe::bop(node *node1,const int edge_type, node *node2, void *nvalue)
/*	End Synopsis	*/
{
	return(node1->bop(edge_type, node2, nvalue));
}

/**

.Name
	bap

.Library Name
	libsfmac

.Description
	bind adjacent edges to value

.Preconditions

.Constraints

.Side Effects

.Return Values

.Notes

.See Also

**/

/*	Begin Synopsis	*/
node *
universe::bap(node *node1,const int edge_type, node *node2, void *nvalue)
/*	End Synopsis 	*/
{
	return(node1->bap(edge_type, node2, nvalue));
}

/**

.Name
	vip

.Library Name
	libsfmac

.Description
	value of inpointing pair

.Preconditions

.Constraints

.Side Effects

.Return Values

.Notes

.See Also

**/

/*	Begin Synopsis	*/
void *
universe::vip(const node *node1,const int edge_type,const  node *node2)
/*	End Synopsis	*/
{
	return(node1->vip(edge_type, node2));
}

/**

.Name
	vop

.Library Name
	libsfmac

.Description
	value of outpointing pair

.Preconditions

.Constraints

.Side Effects

.Return Values

.Notes

.See Also

**/

/*	Begin Synopsis	*/
void *
universe::vop(const node *node1,const int edge_type, const node *node2)
/*	End Synopsis	*/
{
	return(node1->vop(edge_type, node2));
}

/**

.Name
	add_edge

.Library Name
	libsfmac

.Description
	Add and edge to the universe

.Preconditions

.Constraints

.Side Effects

.Return Values

.Notes

.See Also

**/

/*	Begin Synopsis	*/
void
universe::add_edge(const edge *nedge)
/*	End Synopsis	*/
{
	edges->push((void *)nedge);
}

/**

.Name
	bug

.Library Name
	libsfmac

.Description
	Bind value to an edge

.Preconditions

.Constraints

.Side Effects

.Return Values

.Notes

.See Also

**/

/*	Begin Synopsis	*/
void
universe::bug(edge *nedge,void *nvalue)
/*	End Synopsis	*/
{
	nedge->bug(nvalue);
}

/**

.Name
	vug

.Library Name
	libsfmac

.Description
	get a value of an edge

.Preconditions

.Constraints

.Side Effects

.Return Values

.Notes

.See Also

**/

/*	Begin Synopsis	*/
void *
universe::vug(edge *nedge)
/*	End Synopsis	*/
{
	return(nedge->vug());

}
