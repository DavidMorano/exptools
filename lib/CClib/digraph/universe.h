#ifndef UNIVERSE_H

#define UNIVERSE_H

/*
			AT&T - PROPRIETARY
	THIS DOCUMENT CONTAINS PROPRIETARY INFORMATION OF
	AT&T AND IS NOT TO BE DISCLOSED OR USED EXCEPT IN
	ACCORDANCE WITH APPLICABLE AGREEMENTS.
	
		Copyright (c) 1988 AT&T
		Unpublished & Not for Publication
		All Rights Reserved
*/

#ident	"libsfmac:universe.h 1.1 1/18/89"
#ident	"@(#)libsfmac:universe.h	1.1"


/**

.File Name
	Universe.h

.Author
	M. T. Emanuel

.Date Created
	Oct . 10, 1988

.Description

.Constraints

.Notes

.See Also

.Standards
This file conforms to the Dept. 54141 C Coding Standards.
Extensions have been made for C++.

**/


/*	System Header Files					*/
#include <String.h>

/*	Project Header Files					*/
#include "general.h"
#include "sllist.h"
#include "int_sllist.h"
#include "node.h"
#include "edge.h"
#include "Hash.h"

/*	Symbolic Constant Definitions				*/

/*	Macro Definitions					*/

/*	Constant Variable Definitions				*/
#define NOTHING 33

/*	Typedefs, Structure and Union Declarations		*/

/*	External Variable Declarations				*/

/*	Function Declarations					*/



class universe {

    friend class node;
    friend class edge;
    String name;        // universe name
    static int exist;            // 0 if the universe does not exist
                                  // 1 if the universe does exist
    sllist *edges;                    // linked list of all edges in the universe
	
    sllist *nodes;

    Hash hashtable;

    void *value;

    // private functions 
    void remove_edge(const edge *del_edge);
    int cun(String& node_name, node *new_node);

public:
    
    universe();
    universe(const String& un_name);
    /*virtual*/ ~universe();

    // create unqualified node

    // return list of unqualified nodes
    sllist *ssun(); 

    // interfaces to destory nodes and edges
    int dun(node *node1);

    int dan(node *node1);
    int din(node *node1);
    int don(node *node1);

    int ding(node *node1, const int edge_type);
    int dong(node *node1, const int edge_type);
    int dang(node *node1, const int edge_type);

    int dig(node *node1);
    int dog(node *node1);
    int dag(node *node1);

    int digg(node *node1,const int edge_type);
    int dogg(node *node1,const int edge_type);
    int dagg(node *node1,const int edge_type);

    int dign(node *node1, node *node2);
    int dogn(node *node1, node *node2);
    int dagn(node *node1, node *node2);

    void dug(edge *des_edge);  

    // check for existance
    int xun(const node *node1);
    int xip(const node *node1,const int edge_type,const node *node2);
    int xop(const node *node1,const int edge_type,const node *node2);
    int xap(const node *node1,const int edge_type,const node *node2);


    // return specified sets
    sllist *sip(const node* node1);
    sllist *sop(const node* node1);
    sllist *sap(const node* node1);

    int_sllist *sig(const node *node1);
    int_sllist *sog(const node *node1);
    int_sllist *sag(const node *node1);

    int_sllist *sign(const node *node1, const node *node2);
    int_sllist *sogn(const node *node1, const node *node2);
    int_sllist *sagn(const node *node1, const node *node2);

    sllist *san(const node* node1);
    sllist *sin(const node* node1);
    sllist *son(const node *node1);

    sllist *sing(const node* node1,const int edge_type);
    sllist *song(const node* node1,const int edge_type);
    sllist *sang(const node* node1,const int edge_type);

     // bind inpointing pair
    node *bip(node *node1,const int edge_type, node *node2, void *nvalue = (void *)0);
    node *bop(node *node1,const int edge_type, node *node2, void *nvalue = (void *)0);
    node *bap(node *node1,const int edge_type, node *node2, void *nvalue = (void *)0);


    // get values of pairs
    void *vip(const node *node1,const int edge_type,const node *node2);         // value of inpointing pair
    void *vop(const node *node1,const int edge_type, const node *node2);         // value of outpointin pair

    // create adjacent pairs
    node *cap(node *node1, edge *nedge, node *node2, void *nvalue = (void*)0);

    // create inpointing pair
    node *cip(node *node1, edge *nedge, node *node2,void *nvalue = (void *)0);

    // create outpointing pair
    node *cop(node *node1, edge *nedge, node *node2, void *nvalue = (void *)0);

    
     //edge interfaces in the universe
    void bug(edge *edge1,void *nvalue = (void *)0);
    void *vug(edge *edge1);

    //return a node from the node name
    node *node_from_name(const String& node_name);


    // bind unqualified space (universe only)
    void bus(void *nvalue = (void *)0);

    // value of unqualified space (universe only)
    void *vus();

    // bind unqualified node
    void bun(node *node1, void *nvalue = (void *)0);

    // value unqualified node
    void *vun(const node *node1);
	
    void add_edge(const edge *nedge);

};
#endif
