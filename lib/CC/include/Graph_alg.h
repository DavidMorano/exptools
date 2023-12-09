#ifndef GRAPHALGS_DOT_H
#define GRAPHALGS_DOT_H

#include "Graph.h"
#include <List.h>
#include "Set.h"
#include <generic.h>
#include <guard.h>


enum tcwbool_ATTLC { FALS, TRU };

class temp_set_dummy_ATTLC;
class List_of_p(Vertex);
class List_of_p(Edge);


PT_names
	SRCH_ATTLC(V) 	V _SRCH_ATTLC
PT_end
PT_names
	SRCH2_ATTLC(V) 	V _SRCH2_ATTLC
PT_end
PT_names
	CYCLEG_ATTLC(G) 	G _CYCLE_ATTLC
PT_end
PT_names
	CYCLEE_ATTLC(E) 	E _CYCLE_ATTLC
PT_end
PT_names
	CYCLEV_ATTLC(V) 	V _CYCLE_ATTLC
PT_end
PT_names
	ECYCLE_ATTLC(E) 	E _ECYCLE_ATTLC
PT_end
PT_names
	VCYCLE_ATTLC(V) 	V _VCYCLE_ATTLC
PT_end
PT_names
	PSETGA_ATTLC(X) 	X _PSETGA_ATTLC
PT_end
PT_names
	PSETGA2_ATTLC(X) 	X _PSETGA2_ATTLC
PT_end
PT_names
	TEMPSET_ATTLC(G) 	G _TEMPSET_ATTLC
PT_end
PT_names
	GApredicate(V) 	V _GApredicate
PT_end
PT_names
	Graph_algdeclareguard(G,V,E) 	Graph_algdeclareguard_ G V E
PT_end
PT_names
	Graph_algimplementguard(G,V,E) 	Graph_algimplementguard_ G V E
PT_end

typedef int (*GAFUNCPTR_ATTLC)(Vertex*);

extern List_of_p(Vertex) intermediate_dfs_p_ATTLC(char, Graph&, Vertex*, GAFUNCPTR_ATTLC);
extern List_of_p(Vertex) intermediate_dfs_po_ATTLC(char, Graph&, Vertex*, Pred_obj(Vertex)&);
extern List_of_p(Vertex) intermediate_bfs_p_ATTLC(char, Graph&, Vertex*, GAFUNCPTR_ATTLC);
extern List_of_p(Vertex) intermediate_bfs_po_ATTLC(char, Graph&, Vertex*, Pred_obj(Vertex)&);
extern Vertex* intermediate_cycle_ATTLC(char, const Graph&);
extern int intermediate_cycle_v_ATTLC(char, const Graph&, const Vertex*);
extern int intermediate_cycle_e_ATTLC(char, const Graph&, const Edge*);
extern List_of_p(Edge) internal_cycle_list_v_ATTLC(const Graph&, const Vertex*);
extern List_of_p(Edge) internal_u_cycle_list_v_ATTLC(const Graph&, const Vertex*);
extern List_of_p(Edge) intermediate_cycle_list_e_ATTLC(char,const Graph&,const Edge*);
extern Set_of_p(Vertex) internal_artic_pts2_ATTLC(const Graph&);
extern Set_of_p(Vertex) internal_artic_pts_ATTLC(const Graph&, const Set_of_p(Vertex)&);

PT_define Graph_algdeclare(G,V,E)

List_of_pdeclare(V)
typedef int GApredicate(V)(V*);
typedef List_of_p(V) SRCH_ATTLC(V)(char, G&, V*, GApredicate(V)*);
typedef List_of_p(V) SRCH2_ATTLC(V)(char, G&, V*, Pred_obj(V)&);
typedef V* CYCLEG_ATTLC(G)(char, const G&);
typedef int CYCLEE_ATTLC(E)(char, const G&, const E*);
typedef int CYCLEV_ATTLC(V)(char, const G&, const V*);
List_of_pdeclare(E)
typedef List_of_p(E) VCYCLE_ATTLC(V)(const G&, const V*);
typedef List_of_p(E) ECYCLE_ATTLC(E)(char, const G&, const E*);
typedef Set_of_p(V) PSETGA_ATTLC(V)(const G&, const Set_of_p(V)&);
typedef Set_of_p(V) PSETGA2_ATTLC(V)(const G&);
Set_of_pdeclare(Set_of_p(V))
Set_of_p_func_declare_ATTLC(Set_of_p(V))
/*Listdeclare(G): early placeholder for Set*/
/*Set_or_Bagdeclare(G)*/
Setdeclare(G)
inline List_of_p(V)	dfs(G& g, V* v, GApredicate(V)* f = 0) { return
				(*((SRCH_ATTLC(V)*)intermediate_dfs_p_ATTLC))('d', g, v, f); }
inline List_of_p(V)	bfs(G& g, V* v, GApredicate(V)* f = 0) { return
				(*((SRCH_ATTLC(V)*)intermediate_bfs_p_ATTLC))('d', g, v, f); }
inline List_of_p(V)	dfs_u(G& g, V* v, GApredicate(V)* f = 0) { return
				(*((SRCH_ATTLC(V)*)intermediate_dfs_p_ATTLC))('u', g, v, f); }
inline List_of_p(V)	bfs_u(G& g, V* v, GApredicate(V)* f = 0) { return
				(*((SRCH_ATTLC(V)*)intermediate_bfs_p_ATTLC))('u', g, v, f); }
inline List_of_p(V)	dfs(G& g, V* v, Pred_obj(V)& f) { return
				(*((SRCH2_ATTLC(V)*)intermediate_dfs_po_ATTLC))('d', g, v, f); }
inline List_of_p(V)	bfs(G& g, V* v, Pred_obj(V)& f) { return
				(*((SRCH2_ATTLC(V)*)intermediate_bfs_po_ATTLC))('d', g, v, f); }
inline List_of_p(V)	dfs_u(G& g, V* v, Pred_obj(V)& f) { return
				(*((SRCH2_ATTLC(V)*)intermediate_dfs_po_ATTLC))('u', g, v, f); }
inline List_of_p(V)	bfs_u(G& g, V* v, Pred_obj(V)& f) { return
				(*((SRCH2_ATTLC(V)*)intermediate_bfs_po_ATTLC))('u', g, v, f); }
inline V*	cycle(const G& g) { return
				(*((CYCLEG_ATTLC(G)*)intermediate_cycle_ATTLC))('d', g); }
inline int	cycle(const G& g, const V* v) { return
				(*((CYCLEV_ATTLC(V)*)intermediate_cycle_v_ATTLC))('d', g, v); }
inline int	cycle(const G& g, const E* e) { return
				(*((CYCLEE_ATTLC(E)*)intermediate_cycle_e_ATTLC))('d', g, e); }
inline List_of_p(E)	cycle_list(const G& g, const V* v) { return
				(*((VCYCLE_ATTLC(V)*)internal_cycle_list_v_ATTLC))(g, v); }
inline List_of_p(E)	cycle_list(const G& g, const E* e) { return
				(*((ECYCLE_ATTLC(E)*)intermediate_cycle_list_e_ATTLC))('d', g, e); }
inline V*	cycle_u(const G& g) { return
				(*((CYCLEG_ATTLC(G)*)intermediate_cycle_ATTLC))('u', g); }
inline int	cycle_u(const G& g, const V* v) { return
				(*((CYCLEV_ATTLC(V)*)intermediate_cycle_v_ATTLC))('u', g, v); }
inline int	cycle_u(const G& g, const E* e) { return
				(*((CYCLEE_ATTLC(E)*)intermediate_cycle_e_ATTLC))('u', g, e); }
inline List_of_p(E)	cycle_list_u(const G& g, const V* v) { return
				(*((VCYCLE_ATTLC(V)*)internal_u_cycle_list_v_ATTLC))(g, v); }
inline List_of_p(E)	cycle_list_u(const G& g, const E* e) { return
				(*((ECYCLE_ATTLC(E)*)intermediate_cycle_list_e_ATTLC))('u', g, e); }
inline Set_of_p(V)	artic_pts(const G& g) { return
				(*((PSETGA2_ATTLC(V)*)internal_artic_pts2_ATTLC))(g); }
inline Set_of_p(V)	artic_pts(const G& g, const Set_of_p(V)& vs) { return
				(*((PSETGA_ATTLC(V)*)internal_artic_pts_ATTLC))(g, vs); }
Set(G) conn_comps_u(const G&);
Set(G) strong_conn_comps(const G&);

PT_end


Graph_algdeclare(Graph,Vertex,Edge)


PT_define Graph_algimplement(G,V,E)

#ifndef BUILDING_LIBRARY
Set_of_pimplement(Set_of_p(V))
/*Listimplement(G): early placeholder for Set*/
/*Set_or_Bagimplement(G)*/
Setimplement(G)
List_of_pimplement(V)
List_of_pimplement(E)
#endif
int scc_sub_ATTLC(V* v, int* i, Set_of_p(Set_of_p(V))& scc, List_of_p(V)& v_list, int vsize, const G& g, Val_v_ticket& vt) {
	int min, ret_val;
	V* e_dst;
	V* stacked_v;
	min = ++(*i);
	v->set_val(vt, min);
	v_list.put(v);
	Gene_obj(E)& eset_gen = v->out_edges_g(g).generator();
	E* e;
	while (e = eset_gen()) {
		e_dst = e->dst();
		ret_val = (!e_dst->val(vt)) ? scc_sub_ATTLC(e_dst,i,scc,v_list,vsize,g,vt) : e_dst->val(vt);
		if (ret_val < min)
			min = ret_val;
		}
	if (min == v->val(vt)) {
		Set_of_p(V)* v_pset = new Set_of_p(V);
		while (v_list.unput(stacked_v) && (stacked_v != v)) {
			v_pset->insert(stacked_v);
			stacked_v->set_val(vt, vsize+1);
			}
		v_pset->insert(stacked_v);
		stacked_v->set_val(vt, vsize+1);
		scc.insert(v_pset);
		}
	return(min);
	}
void fill_graph_ATTLC(const G& orig_g, G* dest_g, Set_of_p(V)& v_pset) {
	Gene_obj(V)& vset_gen = v_pset.generator();
	V* vp;
	while (vp = vset_gen()) {
		dest_g->insert(vp);
		Gene_obj(E)& e1set_gen = vp->in_edges_g(orig_g).generator();
		E* ep;
		while (ep = e1set_gen()) {
			if (v_pset.contains(ep->src()))
				dest_g->insert(ep);
			}
		Gene_obj(E)& e2set_gen = vp->out_edges_g(orig_g).generator();
		while (ep = e2set_gen()) {
			if (v_pset.contains(ep->dst()))
				dest_g->insert(ep);
			}
		Gene_obj(E)& e3set_gen = vp->loop_edges_g(orig_g).generator();
		while (ep = e3set_gen())
			dest_g->insert(ep);
		v_pset.remove(vp);
		}
	}
class TEMPSET_ATTLC(G): public Set(G) {
public:
	TEMPSET_ATTLC(G)(const G& g, temp_set_dummy_ATTLC*) {
		const G* g2_ptr;
		Set_of_p(Set_of_p(V)) cc;
		List_of_p(V) vlist;
		V* stacked_v;
		Set_of_p(V) v_set = g.vertices();
		Gene_obj(V)& vset_gen = v_set.generator();
		V* v;
		while (v = vset_gen()) {
			vlist = dfs_u((G&)g, v, 0);
			Set_of_p(V)* vpset = new Set_of_p(V);
			while (vlist.unput(stacked_v)) {
				vpset->insert(stacked_v);
				v_set.remove(stacked_v);
				}
			cc.insert(vpset);
			}
		Gene_obj(Set_of_p(V))& pvset_gen = cc.generator();
		Set_of_p(V)* vset;
		while (vset = pvset_gen()) {
			G g2;
			/* the next 3 lines were for early List version */
			/* put(g2);*/
			/* peek_next(g2_ptr); */
			/* step_next(); */
			insert(g2);
			g2_ptr = contains(g2);
			fill_graph_ATTLC(g, (G*)g2_ptr, *vset);
			cc.remove(vset);
			delete vset;
			}
		/* the next line was for early List version */
		/* reset(); */
		};
	TEMPSET_ATTLC(G)(const G& g, temp_set_dummy_ATTLC*, temp_set_dummy_ATTLC*) {
		Val_v_ticket vt = Vertex::get_val_v_ticket();
		const G* g2_ptr;
		Set_of_p(Set_of_p(V)) scc;
		int j = 0;
		int* i = &j;
		List_of_p(V) v_list;
		int vsize = g.vertices().size();
		Gene_obj(V)& vset_gen = g.vertices().generator();
		V* v;
		while (v = vset_gen())
			if (!v->val(vt))
				scc_sub_ATTLC(v, i, scc, v_list, vsize, g, vt);
		Gene_obj(Set_of_p(V))& pvset_gen = scc.generator();
		Set_of_p(V)* vset;
		while (vset = pvset_gen()) {
			G g2;
			/* the next 3 lines were for early List Version*/
			/*put(g2); */
			/*peek_next(g2_ptr); */
			/*step_next(); */
			insert(g2);
			g2_ptr = contains(g2);
			fill_graph_ATTLC(g, (G*)g2_ptr, *vset);
			scc.remove(vset);
			delete vset;
			}
		/* the next line was for early List version */
		/* reset();	*/
		reset_val(vt, (Set_of_p(V)&)g.vertices());
		Vertex::free_val_v_ticket(vt);
		}
	};
TEMPSET_ATTLC(G) 	list_cc_make_ATTLC(const G& g) { return TEMPSET_ATTLC(G)(g, (temp_set_dummy_ATTLC*)0); }
TEMPSET_ATTLC(G) 	list_scc_make_ATTLC(const G& g) { return TEMPSET_ATTLC(G)(g, (temp_set_dummy_ATTLC*)0, (temp_set_dummy_ATTLC*)0); }
Set(G)	conn_comps_u(const G& g) { return list_cc_make_ATTLC(g); }
Set(G)	strong_conn_comps(const G& g) { return list_scc_make_ATTLC(g); }


PT_end
#endif
