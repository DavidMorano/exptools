#ifndef SET_OF_PH
#define SET_OF_PH

class Set_of_p_select_ATTLC;
class Set_of_p_reject_ATTLC;
class Set_of_p_map_ATTLC;
class Set_of_p_union_ATTLC;
class Set_of_p_inter_ATTLC;
class Set_of_p_diff_ATTLC;
class Set_of_p_xor_ATTLC;
class pst_ATTLC;
class pst_internal_node_ATTLC;
class pst_iter_old_ATTLC;
class pst_new_iter_ATTLC;

#define NODE_SIZE	32
#define POSITIONS	6
#define MASK_BITS	0X1F
#define INITIAL_SHIFT	2
#define SHIFT_INCR	5

extern Pool*	pst_internal_node_pool_ptr_ATTLC;
class Set_of_p_initializer_ATTLC {
	static int	count;
public:
	inline Set_of_p_initializer_ATTLC();
	~Set_of_p_initializer_ATTLC() { if (--count == 0)
		delete pst_internal_node_pool_ptr_ATTLC; }
};
static Set_of_p_initializer_ATTLC pset_initializer_ATTLC;

class pst_internal_item_ATTLC {
    friend pst_ATTLC;
    friend pst_iter_old_ATTLC;
    friend pst_internal_node_ATTLC;
private:
	union	{
		ALIGN	ext_leaf;
		pst_internal_node_ATTLC*	nodep;
		long	this_is_leaf; // assume sizeof(long) != sizeof(ALIGN)
	};
	int	is_leaf_or_null() const { return this_is_leaf & 01; }
#ifndef FAST
	int	is_node() const;
	int	is_leaf() const;
	int	is_null() const;
	pst_internal_node_ATTLC*	next_node() const;
	ALIGN	external_leaf() const;
	void	make_leaf(ALIGN);
	void	make_node(pst_internal_node_ATTLC*);
	void	make_null();
#else
	int	is_node() const { return !is_leaf_or_null() && nodep; }
	int	is_leaf() const { return is_leaf_or_null() &&
				((long)ext_leaf & ~(long)01); }
	int	is_null() const { return !nodep; }
	pst_internal_node_ATTLC*	next_node() const {
#ifdef DEBUG
				assert(is_node());
#endif
				return nodep; }
	ALIGN	external_leaf() const {
#ifdef DEBUG
				assert(is_leaf());
#endif
				return (ALIGN)((long)ext_leaf & ~(long)01); }
	void	make_leaf(ALIGN p) {
#ifdef DEBUG
				assert(((long)p & 01) == 0);
#endif
				ext_leaf = (ALIGN)((long)p | 01); }
	void	make_node(pst_internal_node_ATTLC* cp) {
#ifdef DEBUG
				assert(((long)cp & 01) == 0);
#endif
				nodep = cp; }
	void	make_null() { nodep = 0; }
#endif
};

class pst_internal_node_ATTLC {
    friend pst_ATTLC;
    friend pst_iter_old_ATTLC;
private:
	void*	operator new(size_t i) { return i == sizeof(pst_internal_node_ATTLC) ?
		pst_internal_node_pool_ptr_ATTLC->alloc() : new char[i]; }
	void        operator delete(void* p, size_t i) {
			if (i == sizeof(pst_internal_node_ATTLC))
				pst_internal_node_pool_ptr_ATTLC->free(p);
			else delete (char*)p; }
	~pst_internal_node_ATTLC() {}
	pst_internal_node_ATTLC();
	pst_internal_item_ATTLC	item[NODE_SIZE];
	int	busy_count;
};
    
class pst_position_ATTLC {
    friend pst_ATTLC;
    friend pst_iter_old_ATTLC;
private:
    pst_internal_item_ATTLC*	curr_pos[POSITIONS];
    int	curr_depth;
    ALIGN	curr_value;
	    pst_position_ATTLC() : curr_depth(-1), curr_value(0) {}
};
	
class pst_iter_old_ATTLC : private pst_position_ATTLC {
friend pst_ATTLC;
	pst_ATTLC* const	my_pst;
	pst_iter_old_ATTLC*	next_it;
public:
		pst_iter_old_ATTLC(const pst_ATTLC&);
		~pst_iter_old_ATTLC();
	ALIGN	first();
	ALIGN	next();
	pst_ATTLC*	the_pst() { return my_pst; }
	const pst_ATTLC*	the_pst() const { return my_pst; }
};

class pst_new_iter_ATTLC {
	pst_iter_old_ATTLC	it;
	int		inited;
	ALIGN	nxt, prv;
protected:
		pst_new_iter_ATTLC(const pst_ATTLC& p) : it(p), inited(0), prv(0) {}
	int	peek_next(ALIGN&) const;
	ALIGN	peek_next() const;
	int	peek_prev(ALIGN&) const;
	ALIGN	peek_prev() const { return inited ? prv : 0; }
	int	next(ALIGN&);
	ALIGN	next();
	const pst_ATTLC*	the_pst() const { return it.the_pst(); }
public:
	void	reset() { inited = 0; }
};

class pst_ATTLC  {
    friend pst_iter_old_ATTLC;
private:
	pst_internal_item_ATTLC	contents;
	int	sze;
	pst_iter_old_ATTLC*	iter_head;
	pst_position_ATTLC	pos;
	// these functions are only used on empty psets
	void	make_select(PREDICATE&, const pst_ATTLC&);
	void	make_reject(PREDICATE&, const pst_ATTLC&);
	void	make_map(TRANSFORMER&, const pst_ATTLC&);
	void	make_union(const pst_ATTLC&, const pst_ATTLC&);
	void	make_intersection(const pst_ATTLC&, const pst_ATTLC&);
	void	make_difference(const pst_ATTLC&, const pst_ATTLC&);
	void	make_xor(const pst_ATTLC&, const pst_ATTLC&);

	void	warn_iterators() const;
protected:
		pst_ATTLC(PREDICATE& f, const pst_ATTLC& s,
				Set_of_p_select_ATTLC*);
		pst_ATTLC(PREDICATE& f, const pst_ATTLC& s,
				Set_of_p_reject_ATTLC*);
		pst_ATTLC(TRANSFORMER& f, const pst_ATTLC& s,
				Set_of_p_map_ATTLC*);
		pst_ATTLC(const pst_ATTLC& a, const pst_ATTLC& b,
				Set_of_p_union_ATTLC*);
		pst_ATTLC(const pst_ATTLC& a, const pst_ATTLC& b,
				Set_of_p_inter_ATTLC*);
		pst_ATTLC(const pst_ATTLC& a, const pst_ATTLC& b,
				Set_of_p_diff_ATTLC*);
		pst_ATTLC(const pst_ATTLC& a, const pst_ATTLC& b,
				Set_of_p_xor_ATTLC*);
public:
		pst_ATTLC();
		pst_ATTLC(ALIGN p);
		pst_ATTLC(ALIGN p1, ALIGN p2);
		pst_ATTLC(ALIGN p1, ALIGN p2, ALIGN p3);
		pst_ATTLC(ALIGN p1, ALIGN p2, ALIGN p3, ALIGN p4);
		pst_ATTLC(const pst_ATTLC& p);
		pst_ATTLC(GENERATOR&);
		~pst_ATTLC();
	pst_ATTLC&	operator=(const pst_ATTLC&);
	int	size() const { return sze; }
		operator const void*() const { return size() ? this : 0; }
	int	operator==(const pst_ATTLC&) const;
	int	operator!=(const pst_ATTLC& ps) const { return !(*this == ps); }
	int	operator<=(const pst_ATTLC&) const;
	int	operator<(const pst_ATTLC&) const;
	int	operator>=(const pst_ATTLC& ps) const { return ps <= *this; }
	int	operator>(const pst_ATTLC& ps) const { return ps < *this; }
	ALIGN	insert(ALIGN p);             /* jfi */
	unsigned	remove(const ALIGN p); /* jfi unsigned */
	unsigned	remove_all(); /* jfi unsigned */
	ALIGN	contains(const ALIGN p) const;
	void	do_each(PROCEDURE&) const;
	ALIGN	do_while(PREDICATE&) const;	// returns failure item or 0
	ALIGN	do_until(PREDICATE&) const;	// returns failure item or 0
	inline pst_ATTLC	select(PREDICATE&) const;
	inline pst_ATTLC	reject(PREDICATE&) const;
	inline pst_ATTLC	map(TRANSFORMER&) const;
	inline pst_ATTLC	operator|(const pst_ATTLC&) const;
	inline pst_ATTLC	operator-(const pst_ATTLC&) const;
	inline pst_ATTLC	operator&(const pst_ATTLC&) const;
	inline pst_ATTLC	operator^(const pst_ATTLC&) const;
	pst_ATTLC&	operator|=(const pst_ATTLC&);
	pst_ATTLC&	operator-=(const pst_ATTLC&);
	pst_ATTLC&	operator&=(const pst_ATTLC&);
	pst_ATTLC&	operator^=(const pst_ATTLC&);
	void	check() const;
};

PT_names
	Set_of_p(T) 		T _Set_of_p
	Set_of_piter(T) 	T _Set_of_piter
	Set_of_p_generator(T) 	T _Set_of_p_gene
PT_end

PT_define Set_of_pdeclare(T)
Function_minideclare(T)
class Set_of_p_generator(T);
class Pred_obj(T);
class Tran_obj(T);
class Gene_obj(T);
class Proc_obj(T);
class Set_of_p(T) : public pst_ATTLC {
	void	make_select(Pred_obj(T)&, const Set_of_p(T)&);
	void	make_reject(Pred_obj(T)&, const Set_of_p(T)&);
	void	make_map(Tran_obj(T)&, const Set_of_p(T)&);
	Set_of_p(T)(Predicate(T)& f, const Set_of_p(T)& ps,
			Set_of_p_select_ATTLC* x) : pst_ATTLC((PREDICATE&)f, ps, x) {}
	Set_of_p(T)(Pred_obj(T)& f, const Set_of_p(T)& ps,
			Set_of_p_select_ATTLC*) { make_select(f, ps); }
	Set_of_p(T)(Predicate(T)& f, const Set_of_p(T)& ps,
			Set_of_p_reject_ATTLC* x) : pst_ATTLC((PREDICATE&)f, ps, x) {}
	Set_of_p(T)(Pred_obj(T)& f, const Set_of_p(T)& ps,
			Set_of_p_reject_ATTLC*) { make_reject(f, ps); }
	Set_of_p(T)(Transformer(T)& f, const Set_of_p(T)& ps,
			Set_of_p_map_ATTLC* x) : pst_ATTLC((TRANSFORMER&)f, ps, x) {}
	Set_of_p(T)(Tran_obj(T)& f, const Set_of_p(T)& ps,
			Set_of_p_map_ATTLC*) { make_map(f, ps); }
	Set_of_p(T)(const Set_of_p(T)& a, const Set_of_p(T)& b,
			Set_of_p_union_ATTLC* x) : pst_ATTLC((const pst_ATTLC&)a,
			(const pst_ATTLC&)b, x) {}
	Set_of_p(T)(const Set_of_p(T)& a, const Set_of_p(T)& b,
			Set_of_p_inter_ATTLC* x) : pst_ATTLC((const pst_ATTLC&)a,
			(const pst_ATTLC&)b, x) {}
	Set_of_p(T)(const Set_of_p(T)& a, const Set_of_p(T)& b,
			Set_of_p_diff_ATTLC* x) :
			pst_ATTLC((const pst_ATTLC&)a, (const pst_ATTLC&)b, x) {}
	Set_of_p(T)(const Set_of_p(T)& a, const Set_of_p(T)& b,
			Set_of_p_xor_ATTLC* x) :
			pst_ATTLC((const pst_ATTLC&)a, (const pst_ATTLC&)b, x) {}
public:
		Set_of_p(T)() {}
		Set_of_p(T)(T* p) : pst_ATTLC((ALIGN)p) {}
		Set_of_p(T)(T* p1, T* p2) : pst_ATTLC((ALIGN)p1, (ALIGN)p2) {}
		Set_of_p(T)(T* p1, T* p2, T* p3) : pst_ATTLC((ALIGN)p1, (ALIGN)p2,
						(ALIGN)p3) {}
		Set_of_p(T)(T* p1, T* p2, T* p3, T* p4) : pst_ATTLC((ALIGN)p1, (ALIGN)p2,
						(ALIGN)p3, (ALIGN)p4) {}
		inline Set_of_p(T)(Gene_obj(T)&);
	Set_of_p(T)&	operator=(const Set_of_p(T)& p) { return (Set_of_p(T)&)
						(*(pst_ATTLC*)this = p); }
	int	operator==(const Set_of_p(T)& p) const { return
						(*(pst_ATTLC*)this == p); }
	int	operator!=(const Set_of_p(T)& ps) const {
						return !(*this == ps); }
	int	operator<=(const Set_of_p(T)& p) const { return
						(*(pst_ATTLC*)this <= p); }
	int	operator<(const Set_of_p(T)& p) const { return
						(*(pst_ATTLC*)this < p); }
	int	operator>=(const Set_of_p(T)& p) const { return p <= *this; }
	int	operator>(const Set_of_p(T)& p) const { return p < *this; }
	ALIGN	insert(T* p,unsigned count=1) {  /* jfi */
	    if(count==0)return 0;
	    else return pst_ATTLC::insert((ALIGN)p); 
	}   
	unsigned	remove(const T* p,unsigned count=1) { 
	    if(count==0)return 0;
	    else return pst_ATTLC::remove((const ALIGN)p); 
	}
	unsigned	remove_all(const T* p){
	    return pst_ATTLC::remove((const ALIGN)p); 
	}
	unsigned	remove_all(){       /* jfi */
	    return pst_ATTLC::remove_all();
	}
	ALIGN	contains(const T* p) const { return
					pst_ATTLC::contains((const ALIGN)p); }
	unsigned count(const T* p)const{  /* jfi */
	    return contains(p)?1:0;
	}
	void	do_each(Procedure(T)& f) const {
					pst_ATTLC::do_each((PROCEDURE&)f); }
	void	do_each(Proc_obj(T)&) const;
	T*	do_while(Predicate(T)& f) const { return
				(T*)pst_ATTLC::do_while((PREDICATE&)f); }
	T*	do_while(Pred_obj(T)&) const;
	T*	do_until(Predicate(T)& f) const { return
				(T*)pst_ATTLC::do_until((PREDICATE&)f); }
	T*	do_until(Pred_obj(T)&) const;
	T*	select()const;
	inline Set_of_p(T)	select(Predicate(T)& p) const;
	inline Set_of_p(T)	select(Pred_obj(T)& p) const;
	inline Set_of_p(T)	reject(Predicate(T)& p) const;
	inline Set_of_p(T)	reject(Pred_obj(T)& p) const;
	inline Set_of_p(T)	map(Transformer(T)& f) const;
	inline Set_of_p(T)	map(Tran_obj(T)& f) const;
	inline Set_of_p(T)	operator|(const Set_of_p(T)&) const;
	inline Set_of_p(T)	operator-(const Set_of_p(T)&) const;
	inline Set_of_p(T)	operator&(const Set_of_p(T)&) const;
	inline Set_of_p(T)	operator^(const Set_of_p(T)&) const;
	inline Set_of_p_generator(T)	generator() const;
	inline Set_of_p_generator(T)*	new_generator() const;
	Set_of_p(T)&	operator|=(const Set_of_p(T)& p) { return (Set_of_p(T)&)
				((pst_ATTLC*)this)->operator|=(p); }
	Set_of_p(T)&	operator-=(const Set_of_p(T)& p) { return (Set_of_p(T)&)
				((pst_ATTLC*)this)->operator-=(p); }
	Set_of_p(T)&	operator&=(const Set_of_p(T)& p) { return (Set_of_p(T)&)
				((pst_ATTLC*)this)->operator&=(p); }
	Set_of_p(T)&	operator^=(const Set_of_p(T)& p) { return (Set_of_p(T)&)
				((pst_ATTLC*)this)->operator^=(p); }
};
ostream& operator<<(
    ostream& os,
    const Set_of_p(T)& s
);
class Set_of_piter(T) : public pst_new_iter_ATTLC {
public:
		Set_of_piter(T)(const Set_of_p(T)& s) :
				pst_new_iter_ATTLC((const pst_ATTLC&)s) {}
	int	peek_next(T*& p) const { return
				pst_new_iter_ATTLC::peek_next((ALIGN&)p); }
	T*	peek_next() const { return (T*)pst_new_iter_ATTLC::peek_next(); }
	int	peek_prev(T*& p) const { return
				pst_new_iter_ATTLC::peek_prev((ALIGN&)p); }
	T*	peek_prev() const { return (T*)pst_new_iter_ATTLC::peek_prev(); }
	int	next(T*& p) { return pst_new_iter_ATTLC::next((ALIGN&)p); }
	T*	next() { return (T*)pst_new_iter_ATTLC::/*peek_*/next(); }
	const Set_of_p(T)*	the_set_of_p() const { return
				(Set_of_p(T)*)pst_new_iter_ATTLC::the_pst(); }
};
inline Set_of_p(T)
Set_of_p(T)::operator|(const Set_of_p(T)& p) const
{
	return Set_of_p(T)(*this, p, (Set_of_p_union_ATTLC*)0);
}
inline Set_of_p(T)
Set_of_p(T)::operator-(const Set_of_p(T)& p) const
{
	return Set_of_p(T)(*this, p, (Set_of_p_diff_ATTLC*)0);
}
inline Set_of_p(T)
Set_of_p(T)::operator&(const Set_of_p(T)& p) const
{
	return Set_of_p(T)(*this, p, (Set_of_p_inter_ATTLC*)0);
}
inline Set_of_p(T)
Set_of_p(T)::operator^(const Set_of_p(T)& p) const
{
	return Set_of_p(T)(*this, p, (Set_of_p_xor_ATTLC*)0);
}

PT_end

PT_define Set_of_pimplement(T)
Functiondeclare(T)
Set_of_p_func_declare_ATTLC(T)
#ifndef BUILDING_LIBRARY
Functionimplement(T)
#endif
Set_of_p(T)::Set_of_p(T)(Gene_obj(T)& f)
{
	register T*	p;
	while (p = f())
		insert(p);
}
void
Set_of_p(T)::make_select(Pred_obj(T)& f, const Set_of_p(T)& ps)
{
	pst_iter_old_ATTLC	it(ps);
	for (T* p = (T*)it.first(); p; p = (T*)it.next())
		if (f(p))
			insert(p);
}
void
Set_of_p(T)::make_reject(Pred_obj(T)& f, const Set_of_p(T)& ps)
{
	pst_iter_old_ATTLC	it(ps);
	for (T* p = (T*)it.first(); p; p = (T*)it.next())
		if (!f(p))
			insert(p);
}
void
Set_of_p(T)::make_map(Tran_obj(T)& f, const Set_of_p(T)& ps)
{
	pst_iter_old_ATTLC	it(ps);
	for (T* p = (T*)it.first(); p; p = (T*)it.next())
		insert(f(p));
}
void
Set_of_p(T)::do_each(Proc_obj(T)& f) const
{
	pst_iter_old_ATTLC	it(*this);
	for (T* p = (T*)it.first(); p; p = (T*)it.next())
		f(p);
}
T*
Set_of_p(T)::do_while(Pred_obj(T)& f) const
{
	pst_iter_old_ATTLC	it(*this);
	for (T* p = (T*)it.first(); p; p = (T*)it.next())
		if (!f(p))
			return p;
	return 0;
}
T*
Set_of_p(T)::do_until(Pred_obj(T)& f) const
{
	pst_iter_old_ATTLC	it(*this);
	for (T* p = (T*)it.first(); p; p = (T*)it.next())
		if (f(p))
			return p;
	return 0;
}
T*
Set_of_p(T)::select()const
{
	pst_iter_old_ATTLC	it(*this);
	return (T*)it.first();
}
T*
Set_of_p_generator(T)::operator()()
{
	return (T*)(!inited ? (inited = 1, it.first()) : it.next());
}
PT_end

inline pst_ATTLC
pst_ATTLC::select(PREDICATE& f) const
{
	return pst_ATTLC(f, *this, (Set_of_p_select_ATTLC*)0);
}
inline pst_ATTLC
pst_ATTLC::reject(PREDICATE& f) const
{
	return pst_ATTLC(f, *this, (Set_of_p_reject_ATTLC*)0);
}
inline pst_ATTLC
pst_ATTLC::map(TRANSFORMER& f) const
{
	return pst_ATTLC(f, *this, (Set_of_p_map_ATTLC*)0);
}
inline pst_ATTLC
pst_ATTLC::operator|(const pst_ATTLC& p) const
{
	return pst_ATTLC(*this, p, (Set_of_p_union_ATTLC*)0);
}
inline pst_ATTLC
pst_ATTLC::operator-(const pst_ATTLC& p) const
{
	return pst_ATTLC(*this, p, (Set_of_p_diff_ATTLC*)0);
}
inline pst_ATTLC
pst_ATTLC::operator&(const pst_ATTLC& p) const
{
	return pst_ATTLC(*this, p, (Set_of_p_inter_ATTLC*)0);
}
inline pst_ATTLC
pst_ATTLC::operator^(const pst_ATTLC& p) const
{
	return pst_ATTLC(*this, p, (Set_of_p_xor_ATTLC*)0);
}
inline Set_of_p_initializer_ATTLC::Set_of_p_initializer_ATTLC()
{
	if (count++ == 0)
		pst_internal_node_pool_ptr_ATTLC = new Pool(sizeof(pst_internal_node_ATTLC));
}

PT_define Set_of_pout(TYPE)
ostream& operator<<(
    ostream& os,
    const Set_of_p(TYPE)& s
){
    os << "{";
    Set_of_piter(TYPE) it(s);
    TYPE* p;
    int first=1;

    while(
	p = it.next()
    ){
	if(
	    first
	){
	    first=0;
	}else{
	    os << ",";
	}
	os << *p;
    }
    os << "}";
    return os;
}
PT_end

PT_define Set_of_p_func_declare_ATTLC(T)
Functiondeclare(T)
class Set_of_p_generator(T) : public Gene_obj(T) {
friend Set_of_p(T);
	pst_iter_old_ATTLC	it;
	int		inited;
		Set_of_p_generator(T)(const Set_of_p(T)& p) : it(p), inited(0)
						{}
public:
	T*	operator()();
};
inline Set_of_p(T)
Set_of_p(T)::select(Predicate(T)& p) const
{
	return Set_of_p(T)(p, *this, (Set_of_p_select_ATTLC*)0);
}
inline Set_of_p(T)
Set_of_p(T)::select(Pred_obj(T)& p) const
{
	return Set_of_p(T)(p, *this, (Set_of_p_select_ATTLC*)0);
}
inline Set_of_p(T)
Set_of_p(T)::reject(Predicate(T)& p) const
{
	return Set_of_p(T)(p, *this, (Set_of_p_reject_ATTLC*)0);
}
inline Set_of_p(T)
Set_of_p(T)::reject(Pred_obj(T)& p) const
{
	return Set_of_p(T)(p, *this, (Set_of_p_reject_ATTLC*)0);
}
inline Set_of_p(T)
Set_of_p(T)::map(Transformer(T)& f) const
{
	return Set_of_p(T)(f, *this, (Set_of_p_map_ATTLC*)0);
}
inline Set_of_p(T)
Set_of_p(T)::map(Tran_obj(T)& f) const
{
	return Set_of_p(T)(f, *this, (Set_of_p_map_ATTLC*)0);
}
inline Set_of_p_generator(T)
Set_of_p(T)::generator() const
{
	return Set_of_p_generator(T)(*this);
}
inline Set_of_p_generator(T)*
Set_of_p(T)::new_generator() const
{
	return new Set_of_p_generator(T)(*this);
}
PT_end

#endif
