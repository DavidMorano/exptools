/*
			AT&T - PROPRIETARY
	THIS DOCUMENT CONTAINS PROPRIETARY INFORMATION OF
	AT&T AND IS NOT TO BE DISCLOSED OR USED EXCEPT IN
	ACCORDANCE WITH APPLICABLE AGREEMENTS.

		Copyright (c) 1988 AT&T
		Unpublished & Not for Publication
		All Rights Reserved
*/

#ident "libsfmac:node.c 1.1 1/18/89"
#ident "@(#)libsfmac:node.c	1.1"


/**

.File Name

.Author
	M. T. Emanuel

.Date Created
	Oct. 10, 1988

.Description

.Constraints

.Notes

.See Also

.Standards
This file conforms to the Dept. 54141 C Coding Standards
with modifications for the SUN environment and C++.

**/


/*	System Header Files					*/
#include <stdio.h>
#include <string.h>

/*	Project Header Files					*/

/*	Unit Header Files					*/
#include "node.h"
#include "universe.h"
#include "edge.h"
#include "int_sllist.h"
#include "sllist.h"

/*	Constant Definitions					*/

/*	Macro Definitions and inlines				*/

/*	Typedefs, Structure and Union Declarations		*/

/*	External Variable Declarations				*/

/*	Global Variable Definitions Outside of this File	*/

/*	Global Variable Definitions Restricted to this File	*/

/*	Declarations of Functions External to this File		*/

/*	Declarations of Functions Defined in this File		*/


/**

.Name
	Node constructor

.Library Name

.Description

.Preconditions

.Constraints

.Side Effects

.Return Values

.Notes

.See Also

**/

/*	Begin Synopsis	*/
node::node(const String& node_name, universe *t, void *nvalue)
/*	End Synopsis 	*/
{
	name = node_name;
	my_universe = t;
	value = nvalue;
	inpoint_edges = new sllist;
	outpoint_edges = new sllist;
	my_universe->cun(name, this);

}

/**

.Name
	Node destructor

.Library Name

.Description

.Preconditions

.Constraints

.Side Effects

.Return Values

.Notes

.See Also

**/

/*	Begin Synopsis	*/
node::~node()
{
/*	End Synopsis */

	delete inpoint_edges;
	delete outpoint_edges;
}

// create adjacent pair inpointing and outpointing edges
node *
node::cap(edge *nedge, node *node2, void *nvalue)
{
	node *tmp_node;

	if((tmp_node = my_universe->cop(node2,nedge,this, nvalue)) == (node*)NULL)
		return(tmp_node);

	tmp_node = my_universe->cop(this,nedge, node2, nvalue);

	return(tmp_node);

}

// create inpointing pairs
node *
node::cip(edge *nedge , node *node2, void *nvalue)
{
	if((my_universe->cop(node2,nedge ,this,nvalue)) == (node*)NULL)
		return((node *)NULL);
	else
		return(this);
}

// create outpointing pairs
node *
node::cop(edge *nedge, node *node2, void *nvalue)
{

	if((my_universe->cop(this,nedge, node2,nvalue)) == (node*)NULL)
		return((node*)NULL);

	else
		return(this);
}

// bind inpointing pair
node *
node::bip(const int edge_type, node *node2, void *nvalue) 
{
	sllist *tmp_list;
	edge *tmp_edge;
	int i;

	tmp_list = sip();

	for(i = 0;(tmp_edge = (edge*)tmp_list->nth(i)) != (edge*)NULL; i++)
	{
		if(tmp_edge->get_start() == node2 && tmp_edge->get_type() == edge_type)
		{
			tmp_edge->bug(nvalue);
			return(this);
		}
	}
	return((node *)NULL);
}

// bind outpointing pair
node *
node::bop(const int edge_type, node *node2, void *nvalue) 
{
	sllist *tmp_list;
	edge *tmp_edge;
	int i;

	tmp_list = sop();

	for(i = 0;(tmp_edge = (edge*)tmp_list->nth(i)) != (edge*)NULL; i++)
	{
		if(tmp_edge->get_end() == node2 && tmp_edge->get_type() == edge_type)
		{
			tmp_edge->bug(nvalue);
			return(this);
		}
	}
	return((node *)NULL);
}

// bind adjacent edges to value 
node *
node::bap(const int edge_type, node *node2, void *nvalue) 
{
	sllist *tmp_list;
	edge *tmp_edge;
	int i, t;

	tmp_list = sap();

	for(t = 0,i = 0;(tmp_edge = (edge*)tmp_list->nth(i)) != (edge*)NULL; i++)
	{
		if(((tmp_edge->get_end() == node2) || (tmp_edge->get_start() == node2)) && (tmp_edge->get_type() == edge_type))
		{
			t = t+1;
			tmp_edge->bug(nvalue);
			if(t == 2)
			     return(this);
		}
	}
	return((node *)NULL);
}

// value of inpointing pair
void *
node::vip(const int edge_type, const node *node2)
{
	sllist *tmp_list;
	edge *tmp_edge;
	int i;


	tmp_list = sip();
	
	for(i = 0;(tmp_edge=(edge *)tmp_list->nth(i)) != (edge *)NULL; i++)
	{
		if(tmp_edge->get_type() == edge_type && tmp_edge->get_start() == node2)
		{
			return(tmp_edge->vug());
		}
	}
	
	return((void *)NULL);

}

	
// value of outpointing pair
void *
node::vop(const int edge_type, const node *node2)
{
	sllist *tmp_list;
	edge *tmp_edge;
	int i;


	tmp_list = sop();
	
	for(i = 0;((tmp_edge = (edge *)tmp_list->nth(i))) != (edge *)NULL; i++)
	{
		if(tmp_edge->get_type() == edge_type && tmp_edge->get_end() == node2)
		{
			return(tmp_edge->vug());
		}
	}
	
	return((void *)NULL);

}

/**

.Name
	san

.Library Name

.Description
	set of adjacent nodes

.Preconditions

.Constraints

.Side Effects

.Return Values

.Notes

.See Also

**/

/*	Begin Synopsis	*/
sllist *
node::san()
/* 	End Synopsis	*/
{
	sllist *tmp_list, *node_list;
	edge *tmp_edge;
	node *tmp_node;
	int i;

	tmp_list = inpoint_edges->concat(outpoint_edges);

	node_list = new sllist;

	for(i = 0; ((tmp_edge = (edge *)tmp_list->nth(i))) != (edge *)NULL; i++)
	{
		if((tmp_node = tmp_edge->get_start()) != this)
		{
			if(node_list->exist((void *)tmp_node) == FALSE)
			{
				node_list->push((void *)tmp_node);
			}
		}
		else if((tmp_node = tmp_edge->get_end()) != this)
		{
			if(node_list->exist((void *)tmp_node) == FALSE)
			{
				node_list->push((void*)tmp_node);
			}
		}
		else if(((tmp_node = tmp_edge->get_end()) == this) &&
			((tmp_edge->get_start()) == this))
		{
			if(node_list->exist((void *)tmp_node) == FALSE)
			{
				node_list->push((void*)tmp_node);
			}
		}
		else
		{
			fprintf(stderr,"ERROR: wrong edge in list\n");
			return((sllist *)NULL);
		}
	}
	delete tmp_list;
	return(node_list);
}
			
/**

.Name
	sin

.Library Name

.Description
	set of all inpointing nodes

.Preconditions

.Constraints

.Side Effects

.Return Values

.Notes

.See Also

**/

/*	Begin Synopsis	*/
sllist *
node::sin()
{
/*	End Synopsis	*/

	sllist *node_list;
	int i;
	edge *tmp_edge;
	node *tmp_node, *tmp_node2;

	node_list = new sllist;
	for(i = 0; (tmp_edge = (edge *)inpoint_edges->nth(i)) != (edge *)NULL; i++)
	{
		tmp_node = tmp_edge->get_end();
		tmp_node2 = tmp_edge->get_start();
		if(tmp_node != this)
		{
			fprintf(stderr,"WHOOPS: edge in list not inpointing\n");
			return((sllist *)NULL);
		}
		else if(tmp_node2 == this && tmp_node != this)
		{
			fprintf(stderr,"WHOOPS: this is an outpointing edge\n");
			return((sllist *)NULL);
		}
		else
		{
			if(node_list->exist((void *)tmp_node2) == FALSE)
				node_list->push((void *)tmp_node2);
		}
	}
	return(node_list);
}


/**

.Name
	son

.Library Name

.Description
	 set of all outpointing nodes

.Preconditions

.Constraints

.Side Effects

.Return Values

.Notes

.See Also

**/

/*	Begin Synopsis	*/
sllist *
node::son()
/*	End Synopsis	*/
{
	sllist *node_list;
	int i;
	edge *tmp_edge;
	node *tmp_node, *tmp_node2;

	node_list = new sllist;
	for(i = 0; (tmp_edge = (edge *)outpoint_edges->nth(i)) != (edge *)NULL; i++)
	{
		tmp_node = tmp_edge->get_end();
		tmp_node2 = tmp_edge->get_start();
		if(tmp_node == this && tmp_node2 != this)
		{
			fprintf(stderr,"WHOOPS: edge in list not outpointing\n");
			return((sllist *)NULL);
		}
		else if(tmp_node2 != this)
		{
			fprintf(stderr,"WHOOPS: this is an inpointing edge\n");
			return((sllist *)NULL);
		}
		else
		{	
			if(node_list->exist((void *)tmp_node) == FALSE)
				node_list->push((void *)tmp_node);
		}
	}
	return(node_list);
}

/**

.Name
	sing

.Library Name

.Description
	 set of inpointing nodes given an edge type

.Preconditions

.Constraints

.Side Effects

.Return Values

.Notes

.See Also

**/

/*	Begin Synopsis	*/
sllist *
node::sing(const int edge_type)
/*	End Synopsis 	*/
{
	sllist *node_list;
	int i;
	edge *tmp_edge;
	node *tmp_node, *tmp_node2;

	node_list = new sllist;
	for(i = 0; (tmp_edge = (edge *)inpoint_edges->nth(i)) != (edge *)NULL; i++)
	{
		if((tmp_edge->get_type()) == edge_type)
		{
			tmp_node = tmp_edge->get_end();
			tmp_node2 = tmp_edge->get_start();
			if(tmp_node != this)
			{
				fprintf(stderr,"WHOOPS: edge in list not inpointing\n");
				return((sllist *)NULL);
			}
			else if(tmp_node2 == this && tmp_node != this)
			{
				fprintf(stderr,"WHOOPS: this is an outpointing edge\n");
				return((sllist *)NULL);
			}
			else
			{
				if(node_list->exist((void *)tmp_node2) == FALSE)
					node_list->push((void *)tmp_node2);
			}
		}
	}
	return(node_list);
}

/**

.Name
	song

.Library Name

.Description
	 set of all outpointing nodes 

.Preconditions

.Constraints

.Side Effects

.Return Values

.Notes

.See Also

**/

/*	Begin Synopsis	*/
sllist *
node::song(const int edge_type)
/*	End Synopsis 	*/
{
	sllist *node_list;
	int i;
	edge *tmp_edge;
	node *tmp_node, *tmp_node2;

	node_list = new sllist;
	for(i = 0; (tmp_edge = (edge *)outpoint_edges->nth(i)) != (edge *)NULL; i++)
	{
		if(tmp_edge->get_type() == edge_type)
		{
			tmp_node = tmp_edge->get_end();
			tmp_node2 = tmp_edge->get_start();
			if(tmp_node == this && tmp_node2 != this)
			{
				fprintf(stderr,"WHOOPS: edge in list not outpointing\n");
				return((sllist *)NULL);
			}
			else if(tmp_node2 != this)
			{
				fprintf(stderr,"WHOOPS: this is an inpointing edge\n");
				return((sllist *)NULL);
			}
			else
			{	
				if(node_list->exist((void *)tmp_node) == FALSE)
					node_list->push((void *)tmp_node);
			}
		}
	}
	return(node_list);
}

/**

.Name
	sang

.Library Name

.Description
	 set of adjacent nodes given an edge type

.Preconditions

.Constraints

.Side Effects

.Return Values

.Notes

.See Also

**/

/*	Begin Synopsis	*/
sllist *
node::sang(const int edge_type)
/*	End Synopsis	*/
{
	sllist *tmp_list, *node_list;
	edge *tmp_edge;
	node *tmp_node;
	int i;

	tmp_list = inpoint_edges->concat(outpoint_edges);
	node_list = new sllist;

	for(i = 0; (tmp_edge = (edge *)tmp_list->nth(i)) != (edge *)NULL; i++)
	{
		if(tmp_edge->get_type() == edge_type)
		{
			if((tmp_node = tmp_edge->get_start()) != this)
			{
				if(node_list->exist((void *)tmp_node) == FALSE)
				{
					node_list->push((void *)tmp_node);
				}
			}
			else if((tmp_node = tmp_edge->get_end()) != this)
			{
				if(node_list->exist((void *)tmp_node) == FALSE)
				{
					node_list->push((void*)tmp_node);
				}
			}
			else if(((tmp_node = tmp_edge->get_end()) == this) && (tmp_edge->get_start() == this))
			{
				if(node_list->exist((void *)tmp_node) == FALSE)
				{
					node_list->push((void*)tmp_node);
				}
			}
			else
			{
				fprintf(stderr,"WHOOPS: wrong edge in list\n");
				return((sllist *)NULL);
			}
		}
	}
	return(node_list);
}

// set of inpointing edges of a node
sllist *
node::sip()
{
	
	sllist *tmp_list;
	tmp_list = inpoint_edges->copy();
	return(tmp_list);
}

// set of outpointing edges of a node
sllist *
node::sop()
{
	return(outpoint_edges->copy());
}

// set of adjacent edges of a node
sllist *
node::sap()
{
	// concatenate lists then make a copy of the list to return
	return((inpoint_edges->concat(outpoint_edges))->copy());
}

//set of inpointing edge types
int_sllist *
node::sig()
{
	int_sllist *tmp_intlist;
	int i;
	edge *tmp_edge;

	
	tmp_intlist = new int_sllist;
	for(i = 0; (tmp_edge =(edge *) inpoint_edges->nth(i)) != (edge *)NULL;i++)
	{
		if(tmp_intlist->exist(tmp_edge->get_type()) == FALSE)
		{
			tmp_intlist->push(tmp_edge->get_type());
		}
	}
	return(tmp_intlist);
}

// set of outpointng edge types
int_sllist *
node::sog()
{
	int_sllist *tmp_intlist;
	int i;
	edge *tmp_edge;

	tmp_intlist = new int_sllist;
	for(i = 0; (tmp_edge = (edge *)outpoint_edges->nth(i)) != (edge *)NULL;i++)
	{
		if(tmp_intlist->exist(tmp_edge->get_type()) == FALSE)
		{
			tmp_intlist->push(tmp_edge->get_type());
		}
	}
	return(tmp_intlist);
}

// set of adjacent edge types
int_sllist *
node::sag()
{
	int_sllist *tmp_intlist;
	sllist *tmp_list;
	int i;
	edge *tmp_edge;

	
	tmp_intlist = new int_sllist;
	tmp_list = inpoint_edges->concat(outpoint_edges);

	for(i = 0; (tmp_edge = (edge *)tmp_list->nth(i)) != (edge *)NULL;i++)
	{
		if(tmp_intlist->exist(tmp_edge->get_type()) == FALSE)
		{
			tmp_intlist->push(tmp_edge->get_type());
		}
	}
	return(tmp_intlist);
}

// set of inpointing edge types given a node
int_sllist *
node::sign(const node *node2)
{

	int_sllist *tmp_intlist;
	edge *tmp_edge;
	int i;

	tmp_intlist = new int_sllist;
	for(i = 0; (tmp_edge = (edge *)inpoint_edges->nth(i)) != (edge*)NULL;i++)
	{
		if(tmp_edge->get_start() == node2)
		{
			if(tmp_intlist->exist(tmp_edge->get_type()) == FALSE)
			{
				tmp_intlist->push(tmp_edge->get_type());
			}
		}
	}

	return(tmp_intlist);
}

// set of outpointing edge types given a node
int_sllist *
node::sogn(const node *node2)
{

	int_sllist *tmp_intlist;
	edge *tmp_edge;
	int i;

	tmp_intlist = new int_sllist;
	for(i = 0; (tmp_edge = (edge *)outpoint_edges->nth(i)) != (edge*)NULL;i++)
	{
		if(tmp_edge->get_end() == node2)
		{
			if(tmp_intlist->exist(tmp_edge->get_type()) == FALSE)
			{
				tmp_intlist->push(tmp_edge->get_type());
			}
		}
	}

	return(tmp_intlist);
}

/**

.Name
	sagn

.Library Name

.Description
	set of adjacent edge-types given a node

.Preconditions

.Constraints

.Side Effects

.Return Values

.Notes

.See Also

**/

/*	Begin Synopsis	*/
int_sllist *
node::sagn(const node *node2)
/* 	End Synopsis	*/
{
	int_sllist *tmp_list1, *tmp_list2, *tmp_list3, *tmp_list4;
	int i, *type;

	tmp_list1 = sign(node2);
	tmp_list2 = sogn(node2);

	tmp_list3 = tmp_list1->concat(tmp_list2);

	tmp_list4 = new int_sllist;
	for(i = 0;( type = (int *)tmp_list3->nth(i)) != (int *)NULL; i++)
	{
		if(tmp_list4->exist(*type) == FALSE)
		{
			tmp_list4->push(*type);
		}
	}
	delete tmp_list1;
	delete tmp_list2;
	delete tmp_list3;
	return(tmp_list4);
}

// existance of unqualified node in the universe
int
node::xun()
{
	if(this == (node *)NULL)
		return(FALSE);

	return(my_universe->xun(this));
}

// existance of inpointing pair
int
node::xip(const int edge_type, const node *node2)
{
	int i;
	edge *tmp_edge;

	if(xun() == FALSE)
		return(FALSE);

	if(node2->xun() == FALSE)
		return(FALSE);

	for(i = 0; (tmp_edge = (edge *)inpoint_edges->nth(i)) != (edge *)NULL; i++)
	{
		if(tmp_edge->get_end() == this && tmp_edge->get_start() == node2 && tmp_edge->get_type() == edge_type)
		{
			return(TRUE);
		}
	}
	return(FALSE);
}

// existance of outpointing pair
int
node::xop(const int edge_type, const node *node2)
{
	int i;
	edge *tmp_edge;

	if(xun() == FALSE)
		return(FALSE);

	if(node2->xun() == FALSE)
		return(FALSE);

	for(i = 0; (tmp_edge = (edge *)outpoint_edges->nth(i)) != (edge *)NULL; i++)
	{
		if((tmp_edge->get_start() == this) && (tmp_edge->get_end() == node2) && (tmp_edge->get_type() == edge_type))
		{
			return(TRUE);
		}
	}
	return(FALSE);
}

// existance of adjacent pairs
int
node::xap(const int edge_type, const node *node2)
{
	int ret1, ret2;

	ret1 = xip(edge_type, node2);
	ret2 = xop(edge_type, node2);

	if(ret1 == TRUE && ret2 == TRUE)
		return(TRUE);
	else
		return(FALSE);
}

/**

.Name
	dig

.Library Name

.Description
	 destroy inpointing edges of a node

.Preconditions

.Constraints

.Side Effects

.Return Values

.Notes

.See Also

**/

/*	Begin Synopsis	*/
int
node::dig()
/*	End Synopsis	*/
{
	int i;
	edge *tmp_edge;
	node *tmp_node;
	sllist *in_copy;

	in_copy = inpoint_edges->copy();
	for(i = 0; (tmp_edge = (edge *)in_copy->nth(i)) != (edge *)NULL; i++)
	{
		// get the starting node and remove it from the node
		tmp_node = tmp_edge->get_start();
		tmp_node->remove_edge_out(tmp_edge);
		my_universe->remove_edge(tmp_edge);
		inpoint_edges->remove((void*)tmp_edge);
		
	}
	delete in_copy;
	delete tmp_edge;
	return(SUCCESS);
}

/**

.Name
	dog

.Library Name

.Description
	 destroy outpointing edges of a node

.Preconditions

.Constraints

.Side Effects

.Return Values

.Notes

.See Also

**/

/*	Begin Synopsis	*/
int
node::dog()
/*	End Synopsis	*/
{
	int i;
	edge *tmp_edge;
	node *tmp_node;
	sllist *out_copy;

	out_copy = outpoint_edges->copy();

	for(i = 0;( tmp_edge = (edge *)out_copy->nth(i)) != (edge *)NULL; i++)
	{
		// get the starting node and remove it from the node
		tmp_node = tmp_edge->get_end();
		tmp_node->remove_edge_in(tmp_edge);
		my_universe->remove_edge(tmp_edge);
		outpoint_edges->remove((void*)tmp_edge);
		
	}
	delete tmp_edge;
	delete out_copy;
	return(SUCCESS);
}

// destroy adjacent edges of a node
int
node::dag()
{
	if(dog() == ERROR)
		return(ERROR);

	if(dig() == ERROR)
		return(ERROR);

	return(SUCCESS);
}


/**

.Name
	digg

.Library Name

.Description
	 destroy inpointing edges given an edge_type

.Preconditions

.Constraints

.Side Effects

.Return Values

.Notes

.See Also

**/

/*	Begin Synopsis	*/
int
node::digg(const int edge_type)
/*	End Synopsis	*/
{
	int i;
	edge *tmp_edge;
	sllist *in_copy;
	node *tmp_node;


	in_copy = inpoint_edges->copy();
	for(i = 0; (tmp_edge = (edge *)in_copy->nth(i)) != (edge *)NULL; i++)
	{
		if(tmp_edge->get_type() == edge_type)
		{
			tmp_node = tmp_edge->get_start();
			tmp_node->remove_edge_out(tmp_edge);
			my_universe->remove_edge(tmp_edge);
			inpoint_edges->remove((void*)tmp_edge);
		}
	}
	delete tmp_edge;
	delete in_copy;
	return(SUCCESS);
}

/**

.Name
	dogg

.Library Name

.Description
	 destroy outpointing edges given an edge_type

.Preconditions

.Constraints

.Side Effects

.Return Values

.Notes

.See Also

**/

/*	Begin Synopsis	*/
int
node::dogg(const int edge_type)
/*	End Synopsis 	*/
{
	int i;
	edge *tmp_edge;
	sllist *out_copy;
	node *tmp_node;


	out_copy = outpoint_edges->copy();
	for(i = 0; (tmp_edge = (edge *)out_copy->nth(i)) != (edge *)NULL; i++)
	{
		if(tmp_edge->get_type() == edge_type)
		{
			tmp_node = tmp_edge->get_end();
			tmp_node->remove_edge_in(tmp_edge);
			my_universe->remove_edge(tmp_edge);
			outpoint_edges->remove((void*)tmp_edge);
		}
	}
	delete tmp_edge;
	delete out_copy;
	return(SUCCESS);
}


// destroy adjacent edges given an edge type
int
node::dagg(const int edge_type)
{
	if(digg(edge_type) == ERROR)
		return(ERROR);

	if(dogg(edge_type) == ERROR)
		return(ERROR);

	return(SUCCESS);
}

/**

.Name
	dign

.Library Name

.Description
	 destroy inpointing edges given a node

.Preconditions

.Constraints

.Side Effects

.Return Values

.Notes

.See Also

**/

/*	Begin Synopsis	*/
int
node::dign(node *node2)
/*	End Synopsis	*/
{
	sllist *in_copy;
	int i;
	edge *tmp_edge;
	node *tmp_node;


	in_copy = inpoint_edges->copy();

	for(i = 0; (tmp_edge = (edge *)in_copy->nth(i)) != (edge *)NULL; i++)
	{

		if((tmp_node = tmp_edge->get_start()) == node2)
		{
			tmp_node->remove_edge_out(tmp_edge);
			inpoint_edges->remove((void*)tmp_edge);
			my_universe->remove_edge(tmp_edge);
		}
	}
	delete tmp_edge;
	delete in_copy;
	return(SUCCESS);
}

		
/**

.Name
	dogn

.Library Name

.Description
	 destroy outpointing edges given a node

.Preconditions

.Constraints

.Side Effects

.Return Values

.Notes

.See Also

**/

/*	Begin Synopsis	*/
int
node::dogn(node *node2)
/*	End Synopsis	*/
{
	sllist *out_copy;
	int i;
	edge *tmp_edge;
	node *tmp_node;


	out_copy = outpoint_edges->copy();

	for(i = 0; (tmp_edge = (edge *)out_copy->nth(i)) != (edge *)NULL; i++)
	{

		if((tmp_node = tmp_edge->get_end()) == node2)
		{
			tmp_node->remove_edge_in(tmp_edge);
			outpoint_edges->remove((void*)tmp_edge);
			my_universe->remove_edge(tmp_edge);
		}
	}
	delete tmp_edge;
	delete out_copy;
	return(SUCCESS);
}

// destroy adjacent edges given a node
int
node::dagn(node *node2)
{
	if(dign(node2) == ERROR)
		return(ERROR);

	if(dogn(node2) == ERROR)
		return(ERROR);

	return(SUCCESS);

}

//  functions

//add inpointing edges to list
 void
node::add_edge_in(const edge *new_edge)
{
	inpoint_edges->push((void*)new_edge);
	
}

// used to add outpointing edges to list
 void
node::add_edge_out(const edge *new_edge)
{
	outpoint_edges->push((void*)new_edge);
}

/**

.Name
	remove_edge

.Library Name

.Description
	 remove an edge from the lists

.Preconditions

.Constraints

.Side Effects

.Return Values

.Notes

.See Also

**/

/*	Begin Synopsis	*/
 void
node::remove_edge(edge *del_edge)
/*	End Synopsis	*/
{
	inpoint_edges->remove((void *)del_edge);
	outpoint_edges->remove((void*)del_edge);
}

/**

.Name
	remove_edge_in

.Library Name

.Description
	 remove an edge from inpointing list

.Preconditions

.Constraints

.Side Effects

.Return Values

.Notes

.See Also

**/

/*	Begin Synopsis	*/
 void
node::remove_edge_in(const edge *del_edge)
/*	End Synopsi	*/
{
	inpoint_edges->remove((void *)del_edge);
}
	
/**

.Name
	remove_edge_out

.Library Name

.Description
	 remove an edge from outpointing list

.Preconditions

.Constraints

.Side Effects

.Return Values

.Notes

.See Also

**/

/*	Begin Synopsis	*/
void
node::remove_edge_out(edge *del_edge)
/*	End Synopsis	*/
{
	outpoint_edges->remove((void *)del_edge);
}
	
// bind unqualified node
 void
node::bun(void *nvalue)
{
	value = nvalue;
}

// value unqualified node
 void *
node::vun()
{
	return(value);
}

// destroy unqualified node
 int
node::dun()
{
	return(my_universe->dun(this));
}

// destroy adjacent nodes
 int
node::dan()
{
	return(my_universe->dan(this));
}

// destroy inpointing nodes
 int
node::din()
{
	return(my_universe->din(this));
}

// destroy outpointing nodes
 int
node::don()
{
	return(my_universe->don(this));
}

// destroy inpointing nodes given an edge type
 int
node::ding(const int edge_type)
{
	return(my_universe->ding(this, edge_type));
}

// destory outpointing nodes given an edge type
 int
node::dong(const int edge_type)
{
	return(my_universe->dong(this, edge_type));
}

// destroy adjacent nodes given an edgge type
 int
node::dang(const int edge_type)
{
	return(my_universe->dang(this, edge_type));
}

