#ifndef GRAPH_DOT_H
#define GRAPH_DOT_H

#include "Set.h"
#include <Bits.h>
#include <Block.h>
#include <guard.h>
#include "Ticket.h"

class Graph;
class Edge;
class Vertex;
class induced_graph_dummy_ATTLC;

Set_of_pdeclare(Graph)
Set_of_p_func_declare_ATTLC(Graph)
Set_of_pdeclare(Vertex)
Set_of_p_func_declare_ATTLC(Vertex)
Set_of_pdeclare(Edge)
Set_of_p_func_declare_ATTLC(Edge)
Ticketdeclare(Vis_v_ticket,Vertex)
Ticketdeclare(Vis_e_ticket,Edge)
Ticketdeclare(Val_v_ticket,Vertex)
Ticketdeclare(Val_e_ticket,Edge)

Blockdeclare(int)

class Graph {
//	friend void	Vertex::check();
//	friend void	Edge::check();
	friend Vertex;
	friend Edge;
	Set_of_p(Edge)	edgs;
	Set_of_p(Vertex)	vrtices;
protected:
	Graph(const Graph&, const Set_of_p(Vertex)&, induced_graph_dummy_ATTLC*);
	void 	fill_graph(const Graph&, Set_of_p(Vertex)&);

public:
		Graph();
		Graph(const Graph&);
		~Graph();
	Graph&	operator=(const Graph&);
	int	operator==(const Graph&) const;
	int	operator!=(const Graph&) const;
	const Set_of_p(Edge)&	edges() const { return edgs; }
	const Set_of_p(Vertex)&	vertices() const { return vrtices; }
	int	insert(Vertex* x);
	int	insert(Edge* x);
	int	remove(const Vertex* x);
	int	remove(const Edge* x);
	int	contains(const Vertex* x) const { return 
			(vrtices.contains(x) != NULL); }
	int	contains(const Edge* x) const { return 
			(edgs.contains(x) != NULL); }
	Graph	induced_graph(const Set_of_p(Vertex)& vs) { return
				Graph(*this, vs, (induced_graph_dummy_ATTLC*)0); }
	void	check();
};


class Vertex {
friend Graph;
friend Edge;
	Set_of_p(Graph)	grphs;
	Set_of_p(Edge)	in_edgs;
	Set_of_p(Edge)	out_edgs;
	Set_of_p(Edge)	loop_edgs;
	Vertex(const Vertex&);	// declared but not defined
	Vertex&	operator=(const Vertex&);	// declared but not defined
	Bits	visit;
	Block(int)	value;
public:
	Vertex(); //these 2 lines moved from protected	
	~Vertex();
	Set_of_p(Graph)	graphs() const { return grphs; }
	Set_of_p(Edge)	edges() const;
	Set_of_p(Edge)	edges_g(const Graph&) const;
	Set_of_p(Edge)	in_edges() const;
	Set_of_p(Edge)	in_edges_g(const Graph&) const;
	Set_of_p(Edge)	out_edges() const;
	Set_of_p(Edge)	out_edges_g(const Graph&) const;
	Set_of_p(Edge)	loop_edges() const;
	Set_of_p(Edge)	loop_edges_g(const Graph&) const;
	void	check();
	static Vis_v_ticket	get_vis_v_ticket();
	static Val_v_ticket	get_val_v_ticket();
	static void		free_vis_v_ticket(Vis_v_ticket&);
	static void		free_val_v_ticket(Val_v_ticket&);
	int		set_visited();
	int		set_visited(const Vis_v_ticket&);
	int		reset_visited();
	int		reset_visited(const Vis_v_ticket&);
	int		set_val(int);
	int		set_val(const Val_v_ticket&, int);
	int		visited();
	int		visited(const Vis_v_ticket&);
	int		val();
	int		val(const Val_v_ticket&);
	void	do_edges(Procedure(Edge)&, Graph&);
	void	do_edges(Proc_obj(Edge)&, Graph&);
	void	do_in_edges(Procedure(Edge)&, Graph&);
	void	do_in_edges(Proc_obj(Edge)&, Graph&);
	void	do_out_edges(Procedure(Edge)&, Graph&);
	void	do_out_edges(Proc_obj(Edge)&, Graph&);
	void	do_loop_edges(Procedure(Edge)&, Graph&);
	void	do_loop_edges(Proc_obj(Edge)&, Graph&);
	int	in_graph(const Graph& g) const { return 
			(grphs.contains(&g) != NULL); }
};
void		reset_visited(Set_of_p(Vertex)&);
void 		reset_visited(const Vis_v_ticket&, Set_of_p(Vertex)&);
void		reset_val(Set_of_p(Vertex)&);
void		reset_val(const Val_v_ticket&, Set_of_p(Vertex)&);


class Edge {
friend Graph;
friend Vertex;
	Set_of_p(Graph)	grphs;
	Vertex*		frnt;
	Vertex*		bck;
	static void	clobber_it(Edge* ep);	// when a vertex is destroyed
	void	clobber() { clobber_it(this); }
	Bits	visit;
	Block(int)	value;
public:
	Edge(Vertex* src, Vertex* dst); //these 4 lines moved from protected
	Edge(const Edge&);
	~Edge(); 
	Edge&	operator=(const Edge&);
	Vertex*	src() const { return bck; }
	Vertex*	dst() const { return frnt; }
	const Set_of_p(Graph)&	graphs() const { return grphs; }
	int	in_graph(const Graph& g) const { return 
			(grphs.contains(&g) != NULL); }
	void	check();
	static Vis_e_ticket	get_vis_e_ticket();
	static Val_e_ticket	get_val_e_ticket();
	static void		free_vis_e_ticket(Vis_e_ticket&);
	static void		free_val_e_ticket(Val_e_ticket&);
	int		set_visited();
	int		set_visited(const Vis_e_ticket&);
	int		reset_visited();
	int		reset_visited(const Vis_e_ticket&);
	int		set_val(int);
	int		set_val(const Val_e_ticket&, int);
	int		visited();
	int		visited(const Vis_e_ticket&);
	int		val();
	int		val(const Val_e_ticket&);
};
void		reset_visited(Set_of_p(Edge)&);
void 		reset_visited(const Vis_e_ticket&, Set_of_p(Edge)&);
void		reset_val(Set_of_p(Edge)&);
void		reset_val(const Val_e_ticket&, Set_of_p(Edge)&);

enum InOutLoop_ATTLC { IN, OUT, LOOP, ALL };

PT_names
	PSETF_ATTLC(X) 	X _PSETF_ATTLC
PT_end
PT_names
	PSETFG_ATTLC(X)	X _PSETFG_ATTLC
PT_end
PT_names
	graphtypedefs_ATTLCdeclareguard(G,V,E) 	graphtypedefs_ATTLCdeclareguard_ G V E
PT_end
PT_names
	Graphdeclare1guard(G,V,E) 	Graphdeclare1guard_ G V E
PT_end
PT_names
	derivedGraphguard(G,V,E) 	derivedGraphguard_ G V E
PT_end
PT_names
	derivedVertexguard(G,V,E) 	derivedVertexguard_ G V E
PT_end
PT_names
	derivedEdgeguard(G,V,E) 	derivedEdgeguard_ G V E
PT_end
PT_names
	Graphdeclare2guard(G,V,E) 	Graphdeclare2guard_ G V E
PT_end
PT_names
	Graphimplementguard(G,V,E) 	Graphimplementguard_ G V E
PT_end

PT_define graphtypedefs_ATTLCdeclare(G,V,E)

typedef Set_of_p(G) Vertex::PSETF_ATTLC(G)();
typedef Set_of_p(E) Vertex::PSETF_ATTLC(E)();
typedef Set_of_p(E) Vertex::PSETFG_ATTLC(E)(const Graph&);


PT_end
PT_define Graphdeclare1(G,V,E)

class G;
class V;
class E;
Set_of_pdeclare(G)
Set_of_pdeclare(V)
Set_of_pdeclare(E)
Set_of_p_func_declare_ATTLC(G)
Set_of_p_func_declare_ATTLC(V)
Set_of_p_func_declare_ATTLC(E)
graphtypedefs_ATTLCdeclare(G,V,E)


PT_end
graphtypedefs_ATTLCdeclare(Graph,Vertex,Edge)

extern const PSETF_ATTLC(Graph)*	Vertex_graphs_ATTLC;
extern const PSETF_ATTLC(Edge)*	Vertex_edges_ATTLC;
extern const PSETFG_ATTLC(Edge)*	Vertex_edges_g_ATTLC;
extern const PSETF_ATTLC(Edge)*	Vertex_in_edges_ATTLC;
extern const PSETFG_ATTLC(Edge)*	Vertex_in_edges_g_ATTLC;
extern const PSETF_ATTLC(Edge)*	Vertex_out_edges_ATTLC;
extern const PSETFG_ATTLC(Edge)*	Vertex_out_edges_g_ATTLC;
extern const PSETF_ATTLC(Edge)*	Vertex_loop_edges_ATTLC;
extern const PSETFG_ATTLC(Edge)*	Vertex_loop_edges_g_ATTLC;

PT_define Graphimplement(G,V,E)

#ifndef BUILDING_LIBRARY
Set_of_pimplement(G)
Set_of_pimplement(V)
Set_of_pimplement(E)
#endif


PT_end
PT_define derivedGraph(G,V,E)

protected:
	inline G(const G&, const Set_of_p(V)&, induced_graph_dummy_ATTLC*);
	inline void	 fill_graph(const G&, Set_of_p(V)&);
public:
	inline const Set_of_p(E)&	edges() const;
	inline const Set_of_p(V)&	vertices() const;
	inline int	insert(V* x);
	inline int	insert(E* x);
	inline int	remove(V* x);
	inline int	remove(E* x);
	inline G	induced_graph(const Set_of_p(V)& vp);
	/*inline G(); taken out*/
	/*inline G(const G&); taken out*/


PT_end
PT_define derivedVertex(G,V,E)

public:
	inline Set_of_p(G)	graphs() const;
	inline Set_of_p(E)	edges() const;
	inline Set_of_p(E)	edges_g(const G& g) const;
	inline Set_of_p(E)	in_edges() const;
	inline Set_of_p(E)	in_edges_g(const G& g) const;
	inline Set_of_p(E)	out_edges() const;
	inline Set_of_p(E)	out_edges_g(const G& g) const;
	inline Set_of_p(E)	loop_edges() const;
	inline Set_of_p(E)	loop_edges_g(const G& g) const;
	inline void	do_edges(Procedure(E)& f, G& g);
	inline void	do_edges(Proc_obj(E)& f, G& g);
	inline void	do_in_edges(Procedure(E)& f, G& g);
	inline void	do_in_edges(Proc_obj(E)& f, G& g);
	inline void	do_out_edges(Procedure(E)& f, G& g);
	inline void	do_out_edges(Proc_obj(E)& f, G& g);
	inline void	do_loop_edges(Procedure(E)& f, G& g);
	inline void	do_loop_edges(Proc_obj(E)& f, G& g);


PT_end

PT_define derivedEdge(G,V,E)

/*	E(V* v1, V* v2) : (v1, v2) {}	taken out*/
	V*	src() const { return (V*)Edge::src(); }
	V*	dst() const { return (V*)Edge::dst(); }
	const Set_of_p(G)&	graphs() const { return
				(const Set_of_p(G)&)Edge::graphs(); }


PT_end

PT_define Graphdeclare2(G,V,E)

/*tcw stuff*/
inline void	reset_visited(Set_of_p(V)& vpset) {
			reset_visited((Set_of_p(Vertex)&)vpset); }
inline void	reset_val(Set_of_p(V)& vpset) {
			reset_val((Set_of_p(Vertex)&)vpset); }
inline void	reset_visited(Set_of_p(E)& epset) {
			reset_visited((Set_of_p(Edge)&)epset); }
inline void	reset_val(Set_of_p(E)& epset) {
			reset_val((Set_of_p(Edge)&)epset); }
inline void	reset_visited(const Vis_v_ticket& vt, Set_of_p(V)& vpset) {
			reset_visited(vt, (Set_of_p(Vertex)&)vpset); }
inline void	reset_val(const Val_v_ticket& vt, Set_of_p(V)& vpset) {
			reset_val(vt, (Set_of_p(Vertex)&)vpset); }
inline void	reset_visited(const Vis_e_ticket& et, Set_of_p(E)& epset) {
			reset_visited(et, (Set_of_p(Edge)&)epset); }
inline void	reset_val(const Val_e_ticket& et, Set_of_p(E)& epset) {
			reset_val(et, (Set_of_p(Edge)&)epset); }
inline void	G::fill_graph(const G& g, Set_of_p(V)& vpset) {
		Graph::fill_graph((const Graph&)g, (Set_of_p(Vertex)&)vpset); }
inline  	G::G(const G& g, const Set_of_p(V)& vs, induced_graph_dummy_ATTLC* x)
			: Graph((const Graph&)g, (const Set_of_p(Vertex)&)vs, x) {}
inline G	G::induced_graph(const Set_of_p(V)& vs) {return
				G(*this, vs, (induced_graph_dummy_ATTLC*)0); }
/*end of tcw stuff*/
/*inline		G::G() : () {} taken out*/
/*inline		G::G(const G& g) : (g) {}	*/
inline const Set_of_p(E)&	G::edges() const { return
				(const Set_of_p(E)&)Graph::edges(); }
inline const Set_of_p(V)&	G::vertices() const { return
				(Set_of_p(V)&)Graph::vertices(); }
inline int	G::insert(V* x) { return Graph::insert(x); }
inline int	G::insert(E* x) { return Graph::insert(x); }
inline int	G::remove(V* x) { return Graph::remove(x); }
inline int	G::remove(E* x) { return Graph::remove(x); }
inline Set_of_p(G)	V::graphs() const { return
				(this->*((PSETF_ATTLC(G)*)Vertex_graphs_ATTLC))(); }
inline Set_of_p(E)	V::edges() const { return
				(this->*((PSETF_ATTLC(E)*)Vertex_edges_ATTLC))(); }
inline Set_of_p(E)	V::edges_g(const G& g) const { return
				(this->*((PSETFG_ATTLC(E)*)Vertex_edges_g_ATTLC))(g); }
inline Set_of_p(E)	V::in_edges() const { return
				(this->*((PSETF_ATTLC(E)*)Vertex_in_edges_ATTLC))(); }
inline Set_of_p(E)	V::in_edges_g(const G& g) const { return
			(this->*((PSETFG_ATTLC(E)*)Vertex_in_edges_g_ATTLC))(g); }
inline Set_of_p(E)	V::out_edges() const { return
				(this->*((PSETF_ATTLC(E)*)Vertex_out_edges_ATTLC))(); }
inline Set_of_p(E)	V::out_edges_g(const G& g) const { return
			(this->*((PSETFG_ATTLC(E)*)Vertex_out_edges_g_ATTLC))(g); }
inline Set_of_p(E)	V::loop_edges() const { return
				(this->*((PSETF_ATTLC(E)*)Vertex_loop_edges_ATTLC))(); }
inline Set_of_p(E)	V::loop_edges_g(const G& g) const { return
		(this->*((PSETFG_ATTLC(E)*)Vertex_loop_edges_g_ATTLC))(g); }
inline void	V::do_edges(Procedure(E)& f, G& g) {
			Vertex::do_edges((Procedure(Edge)*)f, g); }
inline void	V::do_edges(Proc_obj(E)& f, G& g) {
			Vertex::do_edges((Proc_obj(Edge)&)f, g); }
inline void	V::do_in_edges(Procedure(E)& f, G& g) {
			Vertex::do_in_edges((Procedure(Edge)*)f, g); }
inline void	V::do_in_edges(Proc_obj(E)& f, G& g) {
			Vertex::do_in_edges((Proc_obj(Edge)&)f, g); }
inline void	V::do_out_edges(Procedure(E)& f, G& g) {
			Vertex::do_out_edges((Procedure(Edge)*)f, g); }
inline void	V::do_out_edges(Proc_obj(E)& f, G& g) {
			Vertex::do_out_edges((Proc_obj(Edge)&)f, g); }
inline void	V::do_loop_edges(Procedure(E)& f, G& g) {
			Vertex::do_loop_edges((Procedure(Edge)*)f, g); }
inline void	V::do_loop_edges(Proc_obj(E)& f, G& g) {
			Vertex::do_loop_edges((Proc_obj(Edge)&)f, g); }

PT_end



#endif




