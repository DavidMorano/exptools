#ifndef BAGH
#define BAGH
/*
**
**  Things to do:
**
**      o  See if Bagiter(TYPE)::next() can be
**         simplified by using Bag_bucketiter(TYPE)::
**         next() (e.g., in the section marked "find
**         the next leaf")
**
**      o  Uniquify all names that are not intended
**         for public consumption (and also so that
**         they won't collide with Bag_of_p names)
**
**      o  Replace Bagiter by Bucketiter in many
**         Bag operations.  Note that this can't be
**         done in some of the applicators because
**         of the semantics of functions and function
**         objects.
**
*/

/*
**
**  The 32 bits of a Set_or_Bag_hashval are broken into
**  8 4-bit groups.  Each 4-bit group indexes
**  into a Internal_node of 16 Bag_internal_item_ATTLCs.
**  Prefix 'BAG_' needed to avoid collision with
**  Bag_of_p
**
*/
class ostream;
static const int BAG_NODE_SIZE     = 16;
static const int BAG_POSITIONS     = 8;
static const int BAG_MASK_BITS     = 0XF;
static const int BAG_INITIAL_SHIFT = 0;
static const int BAG_SHIFT_INCR    = 4;

extern int BAG_LT_ATTLC(Set_or_Bag_hashval a,Set_or_Bag_hashval b);

/*
**
**  Index to non-parametric classes:
**
*/
    class Bag_bucket_non_param_ATTLC;
    class Bag_internal_item_ATTLC;
    class Bag_internal_node_ATTLC;
    class Bag_position_ATTLC;
/*
**
**  The following ATTLC class declarations are
**  needed to disambiguate the copy-avoidance
**  constructors:
**
*/
class Bag_select_ATTLC;
class Bag_reject_ATTLC;
class Bag_map_ATTLC;
class Bag_union_ATTLC;
class Bag_inter_ATTLC;
class Bag_diff_ATTLC;
class Bag_xor_ATTLC;

extern Pool* bag_internal_node_pool_ptr_ATTLC;

struct Bag_bucket_non_param_ATTLC{
    Set_or_Bag_hashval hashval;
};
struct Bag_internal_item_ATTLC{
/*
**  An Bag_internal_item_ATTLC is a single "slot" in an
**  Bag_internal_node_ATTLC.  It may contain:
**
**      o  An Bag_internal_node_ATTLC*
**      o  A Bag_bucket_non_param_ATTLC*
**      o  NULL
**
**  Bag_bucket_non_param_ATTLC* and Bag_internal_node_ATTLC* 
**  pointers can't be byte-aligned, so the low order 
**  bit is free to be used as the union discriminant.
**
**   o  When the low-order bit is 1, the item
**      is a Bag_bucket_non_param_ATTLC*
**
**   o  When the low order bit is 0, the item
**      is a Bag_internal_node_ATTLC* or NULL.
*/
    union{
        void*                   	ext_leaf;
        Bag_internal_node_ATTLC*	nodep;
        long                    	this_is_leaf;
    };
    inline int is_leaf_or_null()const;

#ifndef FAST

    int
    is_node()const;

    int
    is_leaf()const;

    int
    is_null()const;

    Bag_internal_node_ATTLC*
    next_node()const;

    void*
    external_leaf()const;

    void
    make_leaf(void*);

    void
    make_node(Bag_internal_node_ATTLC*);

    void
    make_null();

#else

    inline int
    is_node()const;

    inline int
    is_leaf()const;

    inline int
    is_null()const;

    inline Bag_internal_node_ATTLC*
    next_node()const;

    inline void*
    external_leaf()const;

    inline void
    make_leaf(void*);

    inline void
    make_node(Bag_internal_node_ATTLC*);

    inline void
    make_null();

#endif

    void
    show(int level)const;
};
struct Bag_internal_node_ATTLC{
/*
**  A Bag_internal_node_ATTLC has 16 Internal_slots
**  plus a count of how many are in use.
**  Each Internal_slot is directly indexed
**  by a 4-bit chunk.
*/

    Bag_internal_item_ATTLC	item[BAG_NODE_SIZE];
    int                 	busy_count;

    Bag_internal_node_ATTLC();

    inline
    ~Bag_internal_node_ATTLC();

    inline void*
    operator new(size_t i);

    inline void
    operator delete(void* p, size_t i);

    void
    show(int level)const;
};
struct Bag_position_ATTLC{
/*
**  A Bag_position_ATTLC caches the result of the most
**  recent search, down to the level of the
**  Bucket:
**
**      o  curr_value is the Set_or_Bag_hashval that we
**         searched for
**
**      o  curr_pos is a stack of pointers to
**         Bag_internal_item_ATTLCs which remembers a
**         path of Bag_internal_item_ATTLCs through the
**         index:
**
**         o  curr_pos[0] points to the Bag_internal_item_ATTLC
**            selected by the first 4 bit chunk
**
**         o  curr_pos[1] points to the Bag_internal_item_ATTLC
**            selected by the second 4 bit chunk
**
**         o  curr_pos[curr_depth] points to the
**            Bag_internal_item_ATTLC which points to
**            a Bucket(TYPE)
**
**  If Bag mutation occurs, a Bag_position_ATTLC is
**  canceled by setting its curr_depth to -1;
**  curr_value can be used subsequently to rebuild
**  the cur_pos stack so that iteration can resume
**
*/
    Bag_internal_item_ATTLC*	curr_pos[BAG_POSITIONS];
    int                     	curr_depth;
    Set_or_Bag_hashval        	curr_value;

    inline
    Bag_position_ATTLC();

    void
    show()const;
};
/*
**
**  Bag_internal_item_ATTLC inlines
**
*/

#ifdef FAST

int
Bag_internal_item_ATTLC::is_leaf_or_null()const{
    return this_is_leaf & 01;
}
int
Bag_internal_item_ATTLC::is_node()const{
    return (
        !is_leaf_or_null() &&
        nodep
    );
}
int
Bag_internal_item_ATTLC::is_leaf()const{
    return (
        is_leaf_or_null() &&
        ((long)ext_leaf & ~(long)01)
    );
}
int
Bag_internal_item_ATTLC::is_null()const{
    return !nodep;
}
Bag_internal_node_ATTLC*
Bag_internal_item_ATTLC::next_node()const{

#ifdef DEBUG

    assert(is_node());

#endif

    return nodep;
}
void*
Bag_internal_item_ATTLC::external_leaf()const{

#ifdef DEBUG

    assert(is_leaf());

#endif

    return (void*)((long)ext_leaf & ~(long)01);
}
void
Bag_internal_item_ATTLC::make_leaf(void* p){

#ifdef DEBUG

    assert(((long)p & 01) == 0);

#endif

    ext_leaf = (void*)((long)p | 01);
}
void
Bag_internal_item_ATTLC::make_node(Bag_internal_node_ATTLC* cp){

#ifdef DEBUG

    assert(((long)cp & 01) == 0);

#endif

    nodep = cp;
}
void
Bag_internal_item_ATTLC::make_null(){
    nodep = 0;
}

#endif
/*
**
**  Bag_internal_node_ATTLC inlines
**
*/
void
Bag_internal_node_ATTLC::operator delete(void* p, size_t i){

    if(
        i == sizeof(Bag_internal_node_ATTLC)
    ){
        bag_internal_node_pool_ptr_ATTLC->free(p);
    }else{
        delete (char*)p;
    }
}
Bag_internal_node_ATTLC::~Bag_internal_node_ATTLC(){
}
void*
Bag_internal_node_ATTLC::operator new(size_t i){
    return (
        i == sizeof(Bag_internal_node_ATTLC) ?(
            bag_internal_node_pool_ptr_ATTLC->alloc()
        ):(
            new char[i]
        )
    );
}
/*
**
**  Bag_position_ATTLC inlines
**
*/
Bag_position_ATTLC::Bag_position_ATTLC():
    curr_depth(-1),
    curr_value(0)       /*  probably not needed */
{ }
/*
**
**  Preparation for parameterization
**
*/
PT_names
	Bag_bucket_ATTLC(T)      T _Bag_bucket_ATTLC
	Bag_initializer_ATTLC(T) T _Bag_initializer_ATTLC
	bag_initializer_ATTLC(T) T _bag_initializer_ATTLC
	Bag_bucketiter_ATTLC(T)  T _Bag_bucketiter_ATTLC
PT_end
/*
**
**  The following are for public consumption
**
*/
PT_names
	Bag_generator(T)        T _Bag_generator
	Bag_pair(T)          	T _Bag_pair
	Bagiter(T)              T _Bagiter
	Bag(T)                  T _Bag
PT_end

PT_define Bagdeclare(TYPE)
Set_or_Bagdeclare_ATTLC(TYPE)
/*
**
**  INDEX TO CLASSES DEFINED BY THIS MACRO
**
*/
class Bag_pair(TYPE);
class Bag_initializer_ATTLC(TYPE);
class Bag_bucket_ATTLC(TYPE);
class Bag_bucketiter_ATTLC(TYPE);
class Bagiter(TYPE);
class Bag_generator(TYPE);
class Bag(TYPE);

class Bag_initializer_ATTLC(TYPE){

    static int count;

public:

    Bag_initializer_ATTLC(TYPE)();
    ~Bag_initializer_ATTLC(TYPE)();
};
static Bag_initializer_ATTLC(TYPE) bag_initializer_ATTLC(TYPE);
/*
**  Each leaf item in the tree-structured index
**  points to a pair of values:
**
**      o  'hashval' is the hash key
**      o  'collision_list' is a list of pairs of
**         (values,count) pairs such that the value
**         hashes to hashval
**
**  Note that ALIGN values in the original version
**  become Bag_bucket_ATTLC(TYPE)* values in this version.
**
*/
struct Bag_pair(TYPE){
    TYPE     value;
    unsigned count;
    int operator==(const Bag_pair(TYPE)& b){
	return (b.value==value && b.count==count);
    }
};
Listdeclare(Bag_pair(TYPE))

struct Bag_bucket_ATTLC(TYPE) : public Bag_bucket_non_param_ATTLC{

    List(Bag_pair(TYPE))   collision_list;

    void
    show()const;
};
class Bag_bucketiter_ATTLC(TYPE){
    friend class Bag(TYPE);
protected:
    Bag(TYPE) *const my_bag;
    Bag_bucketiter_ATTLC(TYPE)* next_it;
    Bag_position_ATTLC pos;
public:

    Bag_bucketiter_ATTLC(TYPE)(const Bag(TYPE)& b);
    ~Bag_bucketiter_ATTLC(TYPE)();

    const Bag_bucket_ATTLC(TYPE)*
    first();

    const Bag_bucket_ATTLC(TYPE)*
    next();

    inline void
    clobber();
};
class Bagiter(TYPE):

    public Bag_bucketiter_ATTLC(TYPE)
{
private:

    int inited;
    Listiter(Bag_pair(TYPE))* itp;

public:

    inline
    Bagiter(TYPE)(const Bag(TYPE)& b);

    const Bag_pair(TYPE)*
    first();              /* undocumented - TBD_make_private */

    const Bag_pair(TYPE)*
    next();               /* subsumes first, next */

    inline void
    reset();              /* new semantics */

    inline const Bag(TYPE)*
    the_bag() const;      /* new */
};

class Pred_obj(CONST(TYPE));
class Tran_obj(CONST(TYPE));
class Gene_obj(CONST(TYPE));
class Proc_obj(CONST(TYPE));

class Bag(TYPE){

    friend class Bag_bucketiter_ATTLC(TYPE);
    friend class Bagiter(TYPE);

private:

    Bag_internal_item_ATTLC contents;
    int                     sze;
    int			    sze_unique;
    Bag_bucketiter_ATTLC(TYPE)*   iter_head;
    Bag_position_ATTLC      pos;
/*
**
**  The following functions are only used
**  on empty Bags
**
*/
    void
    make_select(
        Predicate(CONST(TYPE))& p,
        const Bag(TYPE)& b
    );
    void
    make_reject(
        Predicate(CONST(TYPE))& p,
        const Bag(TYPE)& b
    );
    void
    make_map(
        Transformer(CONST(TYPE))& f,
        const Bag(TYPE)& b
    );
    void
    make_union(
        const Bag(TYPE)& a,
        const Bag(TYPE)& b
    );
    void
    make_intersection(
        const Bag(TYPE)& a,
        const Bag(TYPE)& b
    );
    void
    make_difference(
        const Bag(TYPE)& a,
        const Bag(TYPE)& b
    );
    void
    make_xor(
        const Bag(TYPE)& a ,
        const Bag(TYPE)& b
    );
    void
    make_select(
        Pred_obj(CONST(TYPE))& p,
        const Bag(TYPE)& b
    );
    void
    make_reject(
        Pred_obj(CONST(TYPE))& p,
        const Bag(TYPE)& b
    );
    void
    make_map(
        Tran_obj(CONST(TYPE))& f,
        const Bag(TYPE)& b
    );
    Bag(TYPE)(
        Predicate(CONST(TYPE))& f,
        const Bag(TYPE)& b,
        Bag_select_ATTLC*
    );
    Bag(TYPE)(
        Pred_obj(CONST(TYPE))& f,
        const Bag(TYPE)& b,
        Bag_select_ATTLC*
    );
    Bag(TYPE)(
        Predicate(CONST(TYPE))& f,
        const Bag(TYPE)&  b,
        Bag_reject_ATTLC*
    );
    Bag(TYPE)(
        Pred_obj(CONST(TYPE))& f,
        const Bag(TYPE)&  b,
        Bag_reject_ATTLC*
    );
    Bag(TYPE)(
        Transformer(CONST(TYPE))& f,
        const Bag(TYPE)& b,
        Bag_map_ATTLC*
    );
    Bag(TYPE)(
        Tran_obj(CONST(TYPE))& f,
        const Bag(TYPE)& b,
        Bag_map_ATTLC*
    );
    Bag(TYPE)(
        const Bag(TYPE)& a,
        const Bag(TYPE)& b,
        Bag_union_ATTLC* x
    );
    Bag(TYPE)(
        const Bag(TYPE)& a,
        const Bag(TYPE)& b,
        Bag_inter_ATTLC*
    );
    Bag(TYPE)(
        const Bag(TYPE)& a,
        const Bag(TYPE)& b,
        Bag_diff_ATTLC*
    );
    Bag(TYPE)(
        const Bag(TYPE)& a,
        const Bag(TYPE)& b,
        Bag_xor_ATTLC*
    );
    void
    warn_iterators()const;

public:
/*
**
**  Constructors
**
*/
    inline
    Bag(TYPE)();

    inline
    Bag(TYPE)(const TYPE& t0);

    Bag(TYPE)(
        const TYPE& t0,
        const TYPE& t1
    );
    Bag(TYPE)(
        const TYPE& t0,
        const TYPE& t1,
        const TYPE& t2
    );
    Bag(TYPE)(
        const TYPE& t0,
        const TYPE& t1,
        const TYPE& t2,
        const TYPE& t3
    );

    Bag(TYPE)(const Bag(TYPE)& b);

    Bag(TYPE)(Generator(CONST(TYPE))& g);

    Bag(TYPE)(Gene_obj(CONST(TYPE))& g);
/*
**
**  We could have a constructor that takes a
**  Generator(TYPE) (note -- no CONST) in order
**  to be able to create a Bag from a Set_of_p
**  generator, but this would require another
**  Functiondeclare and lots of new code.  Yuck.
**
*/
    ~Bag(TYPE)();
/*
**
**  Size
**
*/
    inline unsigned int
    size()const;

    inline unsigned int
    size_unique()const;

    inline
    operator const void*()const;
/*
**
**  Assignment
**
*/
    Bag(TYPE)& operator=(const Bag(TYPE)& b);
/*
**
**  Relations
**
*/
    int
    operator==(const Bag(TYPE)& b)const;

    inline int
    operator!=(const Bag(TYPE)& b)const;

    int
    operator<=(const Bag(TYPE)& b)const;

    int
    operator<(const Bag(TYPE)& b)const;

    inline int
    operator>=(const Bag(TYPE)& b)const;

    inline int
    operator>(const Bag(TYPE)& b)const;
/*
**
**  Membership
**
*/
    const Bag_pair(TYPE)*
    contains(const TYPE& t)const;

    unsigned int
    count(const TYPE& t)const;
/*
**
**  Insert and Remove elements
**
*/
    const Bag_pair(TYPE)*
    insert(const TYPE& t, int count=1);

    unsigned int
    remove(const TYPE& t, int count=1);

    unsigned int
    remove_all(const TYPE& t);

    unsigned int
    remove_all();
/*
**
**  Select an arbitrary element
**
*/
    const Bag_pair(TYPE)*
    select()const;
/*
**
**  Applicators
**
*/
    void
    do_each(Procedure(CONST(TYPE))& p)const;

    void
    do_each(Proc_obj(CONST(TYPE))& p)const;

    const TYPE*
    do_while(Predicate(CONST(TYPE))& p)const;

    const TYPE*
    do_while(Pred_obj(CONST(TYPE))& p)const;

    const TYPE*
    do_until(Predicate(CONST(TYPE))& p)const;

    const TYPE*
    do_until(Pred_obj(CONST(TYPE))& p)const;
/*
**
**  Bag algebra
**
*/
    inline Bag(TYPE)
    operator|(const Bag(TYPE)& b)const;

    inline Bag(TYPE)
    operator-(const Bag(TYPE)& b)const;

    inline Bag(TYPE)
    operator&(const Bag(TYPE)& b)const;

    inline Bag(TYPE)
    operator^(const Bag(TYPE)& b)const;

    Bag(TYPE)&
    operator|=(const Bag(TYPE)& b);

    Bag(TYPE)&
    operator-=(const Bag(TYPE)& b);

    Bag(TYPE)&
    operator&=(const Bag(TYPE)& b);

    Bag(TYPE)&
    operator^=(const Bag(TYPE)& b);
/*
**
**  Bag-valued functions
**
*/
    inline Bag(TYPE)
    select(Predicate(CONST(TYPE))& p)const;

    inline Bag(TYPE)
    select(Pred_obj(CONST(TYPE))& p)const;

    inline Bag(TYPE)
    reject(Predicate(CONST(TYPE))& p)const;

    inline Bag(TYPE)
    reject(Pred_obj(CONST(TYPE))& p)const;

    inline Bag(TYPE)
    map(Transformer(CONST(TYPE))& f)const;

    inline Bag(TYPE)
    map(Tran_obj(CONST(TYPE))& f)const;

    inline Bag_generator(TYPE)
    generator()const;

    inline Bag_generator(TYPE)*
    new_generator()const;
/*
**
**  Performance tuning
**
*/
    void
    histogram(Map(Set_or_Bag_hashval,unsigned)& m)const;
/*
**
**  Debugging
**
*/
    void
    check()const;

    void
    show()const;

};
ostream& operator<<(
    ostream& os,
    const Bag(TYPE)& b
);
/*
**
**  Bag_bucketiter_ATTLC(TYPE) inlines
**
*/
void
Bag_bucketiter_ATTLC(TYPE)::clobber(){
    pos.curr_depth = -1;
}
/*
**
**  Bagiter(TYPE) inlines
**
*/
Bagiter(TYPE)::Bagiter(TYPE)(
    const Bag(TYPE)& b
):
    Bag_bucketiter_ATTLC(TYPE)(b),
    inited(0),
    itp(0)
{ }
void
Bagiter(TYPE)::reset(){
    inited=0;
}
const Bag(TYPE)*
Bagiter(TYPE)::the_bag() const{
    return my_bag;
}
/*
**
**  Bag(TYPE) inlines
**
*/
unsigned int
Bag(TYPE)::size()const{
    return sze;
}
unsigned int
Bag(TYPE)::size_unique()const{
    return sze_unique;
}
Bag(TYPE)::operator const void*()const{
    return (
        size() ?(
            this
        ):(
            0
        )
    );
}
int
Bag(TYPE)::operator!=(const Bag(TYPE)& b)const{
    return !(*this == b);
}
int
Bag(TYPE)::operator>=(const Bag(TYPE)& b)const{
    return b <= *this;
}
int
Bag(TYPE)::operator>(const Bag(TYPE)& b)const{
    return b < *this;
}
Bag(TYPE)
Bag(TYPE)::operator|(const Bag(TYPE)& b)const{
    return Bag(TYPE)(*this,b,(Bag_union_ATTLC*)0);
}
Bag(TYPE)
Bag(TYPE)::operator-(const Bag(TYPE)& b)const{
    return Bag(TYPE)(*this, b,(Bag_diff_ATTLC*)0);
}
Bag(TYPE)
Bag(TYPE)::operator&(const Bag(TYPE)& b)const{
    return Bag(TYPE)(*this,b,(Bag_inter_ATTLC*)0);
}
Bag(TYPE)
Bag(TYPE)::operator^(const Bag(TYPE)& b)const{
    return Bag(TYPE)(*this,b,(Bag_xor_ATTLC*)0);
}
PT_end

PT_define Bagdebug(TYPE)
void Bag_bucket_ATTLC(TYPE)::show()const{
    cout << "    hashval=" << hashval << "\n";
    cout << "    collision_list=";
    Listiter(Bag_pair(TYPE)) it(collision_list);
    int first=1;
    cout << "<";

    while(
        !it.at_end()
    ){
        if(
            first
        ){
            first=0;
        }else{
            cout << ",";
        }
	Bag_pair(TYPE)* result;
        it.next(result);
	cout 
	    << "(" 
	    << result->count 
	    << "," 
	    << result->value
	    << ")"
	;
    }
    cout << ">\n";
}
void
Bag(TYPE)::show()const{
    cout << "sze = " << sze << "\n";
    cout << "sze_unique = " << sze_unique << "\n";
    cout << "pos =\n";
    pos.show();
    cout << "contents =\n";
    contents.show(0);
}
PT_end

PT_define Bagimplement(TYPE,H)
Set_or_Bagimplement_ATTLC(TYPE)
Bag_func_declare_ATTLC(TYPE)
#ifndef BUILDING_LIBRARY
Listimplement(Bag_pair(TYPE))
#endif
/*
**
**  TYPE is the type parameter;
**  H is the name of the hash function
**  (Set_zero_ATTLC should be used if the client does
**  not supply its own function).
**
*/
Bag_initializer_ATTLC(TYPE)::Bag_initializer_ATTLC(TYPE)(){
/*
**
**  Pools could be used for Bag_buckets too
**
*/
    if(
        count++ == 0
    ){
        bag_internal_node_pool_ptr_ATTLC = (
            new Pool(sizeof(Bag_internal_node_ATTLC))
        );
    }
}
Bag_initializer_ATTLC(TYPE)::~Bag_initializer_ATTLC(TYPE)(){

    if(
        --count == 0
    ){
        delete bag_internal_node_pool_ptr_ATTLC;
    }
}
Bag_bucketiter_ATTLC(TYPE)::~Bag_bucketiter_ATTLC(TYPE)(){

    if(
        my_bag == 0
    ){
        return;
    }
    if(
        this == my_bag->iter_head
    ){
/*
**
**  Case 1: iterator at head of chain
**
*/
        my_bag->iter_head = next_it;

    }else{
/*
**
**  Case 2: iterator in middle of chain
**
*/
        Bag_bucketiter_ATTLC(TYPE)* x;

        for(
            Bag_bucketiter_ATTLC(TYPE)* an_it=my_bag->iter_head;
            (x = an_it->next_it) != this;
            an_it = x
        );
        an_it->next_it = next_it;
    }
}
Bag_bucketiter_ATTLC(TYPE)::Bag_bucketiter_ATTLC(TYPE)(
    const Bag(TYPE)& b
):
    my_bag(&b),
    next_it(b.iter_head)
{ 
    ((Bag(TYPE)*)(&b))->iter_head = this;
}
/*
**
**  first() and next() are similar to Shopiro's
**  original pset iterator functions  first() and
**  next(); they walk the leaves of the tree,
**  returning Bag_bucket_ATTLC(T))*.
**
*/
const Bag_bucket_ATTLC(TYPE)*
Bag_bucketiter_ATTLC(TYPE)::first() {
    Bag_internal_item_ATTLC* itemp;
    Bag_internal_node_ATTLC* nodep;
    Bag_bucket_ATTLC(TYPE)* bp;

    if(
        my_bag == 0
    ){
        return 0;
    }
    pos.curr_depth = -1;

    if(
        my_bag->contents.is_null()
    ){
        return 0;
    }
    if(
        my_bag->contents.is_leaf()
    ){
/*
**
**  'contents' is a Bag_bucket_ATTLC(TYPE)*
**
*/
        bp = (Bag_bucket_ATTLC(TYPE)*)my_bag->contents.external_leaf();

    }else{
/*
**
**  'contents' is a Bag_internal_node_ATTLC*.  Search the
**  subtree rooted at this node looking for the
**  leftmost leaf.
**
*/
        nodep = my_bag->contents.next_node();

        for(;;){
            assert(pos.curr_depth < BAG_POSITIONS);
/*
**
**  Scan this Bag_internal_node_ATTLC from left to right
**  looking for a non-null Bag_internal_item_ATTLC
**
*/
            for(
                itemp = &nodep->item[0];
                ;
                itemp++
            ){
                assert(itemp < &nodep->item[BAG_NODE_SIZE]);

                if(
                    !itemp->is_null()
                ){
                    break;
                }
            }
            pos.curr_pos[++pos.curr_depth] = itemp;
/*
**
**  If this Bag_internal_item_ATTLC is a leaf, the search 
**  is over; otherwise, iteratively 'recurse'
**
*/
            if(
                itemp->is_leaf()
            ){
                break;
            }
            nodep = itemp->next_node();
        }
        bp = (Bag_bucket_ATTLC(TYPE)*)itemp->external_leaf();
    }
/*
**
**  bp now points to a Bag_bucket_ATTLC(TYPE)
**
*/
    pos.curr_value = bp->hashval;     /* jfi */
    return bp;
}
const Bag_bucket_ATTLC(TYPE)*
Bag_bucketiter_ATTLC(TYPE)::next(){
    Bag_internal_item_ATTLC* itemp;
    Bag_internal_node_ATTLC* nodep;
    Bag_bucket_ATTLC(TYPE)* bp;

    if(
        my_bag == 0
    ){
        return 0;
    }
/*
**
**  Search the index for pos.curr_value.  Since
**  pos caches the result of the last iterator
**  access, the loop should exit almost immediately,
**  unless Bag mutation has occurred since the last
**  access.
**
*/
    itemp = (
        pos.curr_depth == -1 ?(
            &my_bag->contents
        ):(
            pos.curr_pos[pos.curr_depth]
        )

    );
    int unshift = (
        BAG_INITIAL_SHIFT +
        BAG_SHIFT_INCR +
        pos.curr_depth * BAG_SHIFT_INCR
    );
    long mask = BAG_MASK_BITS << unshift;
    nodep = 0;

    for(
        ;
        ;
        mask <<= BAG_SHIFT_INCR, unshift += BAG_SHIFT_INCR
    ){
        assert(pos.curr_depth < BAG_POSITIONS);

        if(
            itemp->is_null()
        ){
            break;
        }else if(
            itemp->is_leaf()
        ){
/*
**
**  While searching for current_value, we have found
**  a leaf.  This may or may not be the leaf containing
**  the current value, depending on whether the
**  Bag_bucket containing the current value has been
**  deleted or not.
**
*/
            bp = (Bag_bucket_ATTLC(TYPE)*)itemp->external_leaf();
            Set_or_Bag_hashval hval = bp->hashval;

            if(
                hval == pos.curr_value ||
                BAG_LT_ATTLC(hval,pos.curr_value)
            ){
/*
**
**  Case 1: we either (a) found the current value or
**  (b) passed it (it must have been deleted).
**
*/
                break;

            }else{
/*
**
**  The leaf points to a Bag_bucket containing a hash
**  value GREATER THAN the current value, so the
**  current value must have been deleted.  The
**  Bag_bucket pointed to is, by definition, the "next"
**  Bag_bucket, the one we arelooking for.
**
*/
                pos.curr_value = hval;
                return bp;
            }

        }else{
/*
**
**  Node: search subindex
**
*/
            nodep = itemp->next_node();
            assert(nodep);
            pos.curr_pos[++pos.curr_depth] = itemp = (
                &nodep->item[(((long)pos.curr_value) & mask) >> unshift]
            );
        }
    }
/*
**
**  pos.curr_pos is now up-to-date and we are ready
**  to locate the NEXT Bag_bucket_ATTLC(TYPE) starting from
**  here.
**
*/
    if(
        pos.curr_depth == -1
    ){
/*
**
**  There was only one hash Bag_bucket; the iteration
**  is therefore terminated.
**
*/
        return 0;
    }
/*
**
**  Find the next Bag_bucket_ATTLC(TYPE)
**
*/
    if(
        nodep == 0
    ){
        nodep = (
            pos.curr_depth == 0 ?(
                my_bag->contents.next_node()
            ):(
                pos.curr_pos[pos.curr_depth-1]->next_node()
            )
        );
    }
    for( ;; ){
        assert(&nodep->item[0] <= itemp  &&  itemp < &nodep->item[BAG_NODE_SIZE]);
/*
**
**  Scan rightward within this node, looking for a
**  non-null item
**
*/
        while(
            itemp < &nodep->item[BAG_NODE_SIZE-1]
        ){
            if(
                !(++itemp)->is_null()
            ){
                goto found;
            }
        }
/*
**
**  Scan reached end of node without finding anything;
**  pop up one level in order to continue the walk
**
*/
        if(
            pos.curr_depth-- == 0
        ){
/*
**
**  The Bag is exhausted, so the iteration is terminated
**
*/
            return 0;
        }
        itemp = pos.curr_pos[pos.curr_depth];
        nodep = (
            pos.curr_depth == 0 ?(
                my_bag->contents.next_node()
            ):(
                pos.curr_pos[pos.curr_depth-1]->next_node()
            )
        );
    }

found:

/*
**
**  itemp now points either to the leaf we're looking
**  for or the root of a subtree containing the leaf.
**
*/
    pos.curr_pos[pos.curr_depth] = itemp;

    while(
        !itemp->is_leaf()
    ){
        assert(itemp->is_node());
        nodep = itemp->next_node();
/*
**
**  Scan to right within this node
**
*/
        for (
            itemp = &nodep->item[0];
            ;
            itemp++
        ){
            assert(itemp < &nodep->item[BAG_NODE_SIZE]);

            if(
                !itemp->is_null()
            ){
                break;
            }
        }
        pos.curr_pos[++pos.curr_depth] = itemp;
    }
    bp = (Bag_bucket_ATTLC(TYPE)*)itemp->external_leaf();
    pos.curr_value = bp->hashval;
    return bp;
}
const Bag_pair(TYPE)*
Bagiter(TYPE)::first(){
/*
**
**  This version has been simplified by using
**  Bag_bucketiter::first()
**
*/
    const Bag_bucket_ATTLC(TYPE)* bp = (
	((Bag_bucketiter_ATTLC(TYPE)*)this)->first()
    );

    if( bp == 0 ){
        return 0;
    }
    delete itp;
    itp=new Listiter(Bag_pair(TYPE))(((Bag_bucket_ATTLC(TYPE)*)bp)->collision_list);
    Bag_pair(TYPE)* result;
    itp->next(result);
/*
**
**  Cast the pointer to const so the client can't
**  modify the element
**
*/
    return (const Bag_pair(TYPE)*)result;
}
const Bag_pair(TYPE)*
Bagiter(TYPE)::next(){
    Bag_internal_item_ATTLC* itemp;
    Bag_internal_node_ATTLC* nodep;
    Bag_bucket_ATTLC(TYPE)* bp;
    Bag_pair(TYPE)* result;
/*
**
**  TBD_see if this code can be simplified by using
**  Bag_bucketiter_ATTLC(TYPE)::next()
**
*/
    assert(my_bag);
/*
**
**  New List-style iterator has next() as only public
**  member function; first() is private and called
**  internally only if this is the first call to next(),
**  i.e., only if inited=0.
**
*/
    if( inited==0 ){
        inited=1;
        return first();
    }
/*
**
**  Search the index for the pos.curr_value.  Since
**  pos normally caches the results of the
**  most recent iterator access, the loop should
**  exit almost immediately.
**
*/
    itemp = (
        pos.curr_depth == -1 ?(
            &my_bag->contents
        ):(
            pos.curr_pos[pos.curr_depth]
        )

    );
    int unshift = (
        BAG_INITIAL_SHIFT +
        BAG_SHIFT_INCR +
        pos.curr_depth * BAG_SHIFT_INCR
    );
    long mask = BAG_MASK_BITS << unshift;
    nodep = 0;

    for(
        ;
        ;
        mask <<= BAG_SHIFT_INCR, unshift += BAG_SHIFT_INCR
    ){
        assert(pos.curr_depth < BAG_POSITIONS);

        if(
            itemp->is_null()
        ){
            break;
        }else if(
            itemp->is_leaf()
        ){
/*
**
**  While searching for current_value, we have found
**  a leaf.  This may or may not be the leaf containing
**  the current value, depending on whether the
**  Bag_bucket containing the current value has been
**  deleted or not.
**
*/
            bp = (Bag_bucket_ATTLC(TYPE)*)itemp->external_leaf();
            Set_or_Bag_hashval hval = bp->hashval;

            if(
                hval == pos.curr_value ||
                BAG_LT_ATTLC(hval,pos.curr_value)
            ){
/*
**
**  Case 1: we either (a) found the current value or
**  (b) passed it (it must have been deleted)
**
*/
                break;

            }else{
/*
**
**  The leaf we have found points to a Bag_bucket
**  containing a next GREATER THAN the current value
**  (the current value must have been deleted).
**
*/
                pos.curr_value = hval;
                delete itp;
                itp = new Listiter(Bag_pair(TYPE))(((Bag_bucket_ATTLC(TYPE)*)bp)->collision_list);
                itp->next(result);
                return (const Bag_pair(TYPE)*)result;
            }

        }else{
/*
**
**  Node: search subindex
**
*/
            nodep = itemp->next_node();
            assert(nodep);
            pos.curr_pos[++pos.curr_depth] = itemp = (
                &nodep->item[(((long)pos.curr_value) & mask) >> unshift]
            );
        }
    }
/*
**
**  curr_pos is now up-to-date and we are ready
**  to locate the next value starting from here.
**
*/
    if(
        pos.curr_depth == -1
    ){
/*
**
**  There is only one Bag_bucket; if we have not not 
**  yet returned all Bag_pairs on the collision list,
**  return the next one; otherwise, the iteration
**  is terminated
**
**  TBD_note:  It is possible that Bag mutation occurred
**  that (1) deleted all the elements in a List and then
**  (2) re-created a List with the same hash value.  In
**  this case, *itp refers to a non-existeng List.  We
**  must guard against this case by using Listiter::the_list.
**
*/
        if(
	    !itp->the_list()
	){
	    return 0;
	}else{

	    if(
		itp->at_end()
	    ){
		return 0;
	    }else{
		itp->next(result);
		return (const Bag_pair(TYPE)*)result;
	    }
	}
    }
/*
**
**  There are multiple Bag_buckets.
**
*/
    if(
        itemp->is_leaf() &&
        (
            ((Bag_bucket_ATTLC(TYPE)*)itemp->external_leaf())->hashval==
            pos.curr_value
        )
    ){
/*
**
**  See if there are more elements in this bucket
**
*/
	if(
	    itp->the_list()
	){
            if(
                !itp->at_end()
            ){
/*
**
**  Move on to the next element
**
*/
                itp->next(result);
                return (const Bag_pair(TYPE)*)result;
            }
        }

    }
/*
**
**  Find the next leaf.
**  TBD_can we use Bag_bucketiter_ATTLC(TYPE)::next() here?
**
*/
    if(
        nodep == 0
    ){
        nodep = (
            pos.curr_depth == 0 ?(
                my_bag->contents.next_node()
            ):(
                pos.curr_pos[pos.curr_depth-1]->next_node()
            )
        );
    }
    for( ;; ){
        assert(&nodep->item[0] <= itemp  &&  itemp < &nodep->item[BAG_NODE_SIZE]);
/*
**
**  Scan rightward within this node, looking for a
**  non-null item
**
*/
        while(
            itemp < &nodep->item[BAG_NODE_SIZE-1]
        ){
            if(
                !(++itemp)->is_null()
            ){
                goto found;
            }
        }
/*
**
**  Scan reached end of node without finding anything;
**  pop up one level in order to continue the walk
**
*/
        if(
            pos.curr_depth-- == 0
        ){
/*
**
**  The Bag is exhausted, so the iteration is terminated
**
*/
            return 0;
        }
        itemp = pos.curr_pos[pos.curr_depth];
        nodep = (
            pos.curr_depth == 0 ?(
                my_bag->contents.next_node()
            ):(
                pos.curr_pos[pos.curr_depth-1]->next_node()
            )
        );
    }

found:

/*
**
**  itemp now points either to the leaf we're looking
**  for or the root of a subindex containing the leaf.
**
*/
    pos.curr_pos[pos.curr_depth] = itemp;

    while(
        !itemp->is_leaf()
    ){
        assert(itemp->is_node());
        nodep = itemp->next_node();
/*
**
**  Scan to right within this node
**
*/
        for (
            itemp = &nodep->item[0];
            ;
            itemp++
        ){
            assert(itemp < &nodep->item[BAG_NODE_SIZE]);

            if(
                !itemp->is_null()
            ){
                break;
            }
        }
        pos.curr_pos[++pos.curr_depth] = itemp;
    }
    bp = (Bag_bucket_ATTLC(TYPE)*)itemp->external_leaf();
    pos.curr_value = bp->hashval;
    delete itp;
    itp = new Listiter(Bag_pair(TYPE))(((Bag_bucket_ATTLC(TYPE)*)bp)->collision_list);
    itp->next(result);
    return (const Bag_pair(TYPE)*)result;
}
Bag(TYPE)::Bag(TYPE)():
    sze(0),
    sze_unique(0),
    iter_head(0)
{
    pos.curr_depth = -1;
    contents.make_null();
}
Bag(TYPE)::Bag(TYPE)(
    const TYPE& t0
):
    sze(0),
    sze_unique(0),
    iter_head(0)
{
    pos.curr_depth = -1;
    contents.make_null();
    insert(t0);
}
Bag(TYPE)::Bag(TYPE)(
    const TYPE& t0,
    const TYPE& t1
):
    sze(0),
    sze_unique(0),
    iter_head(0)
{
    pos.curr_depth = -1;
    contents.make_null();
    insert(t0);
    insert(t1);
}
Bag(TYPE)::Bag(TYPE)(
    const TYPE& t0,
    const TYPE& t1,
    const TYPE& t2
):
    sze(0),
    sze_unique(0),
    iter_head(0)
{
    pos.curr_depth = -1;
    contents.make_null();
    insert(t0);
    insert(t1);
    insert(t2);
}
Bag(TYPE)::Bag(TYPE)(
    const TYPE& t0,
    const TYPE& t1,
    const TYPE& t2,
    const TYPE& t3
):
    sze(0),
    sze_unique(0),
    iter_head(0)
{
    pos.curr_depth = -1;
    contents.make_null();
    insert(t0);
    insert(t1);
    insert(t2);
    insert(t3);
}
Bag(TYPE)::Bag(TYPE)(
    Predicate(CONST(TYPE))& f,
    const Bag(TYPE)& b,
    Bag_select_ATTLC*
):
    sze(0),
    sze_unique(0),
    iter_head(0)
{
    pos.curr_depth = -1;
    contents.make_null();
    make_select(f,b);
}
Bag(TYPE)::Bag(TYPE)(
    Pred_obj(CONST(TYPE))& f,
    const Bag(TYPE)& b,
    Bag_select_ATTLC*
):
    sze(0),
    sze_unique(0),
    iter_head(0)
{
    pos.curr_depth = -1;
    contents.make_null();
    make_select(f,b);
}
Bag(TYPE)::Bag(TYPE)(
    Predicate(CONST(TYPE))& f,
    const Bag(TYPE)& b,
    Bag_reject_ATTLC*
):
    sze(0),
    sze_unique(0),
    iter_head(0)
{
    pos.curr_depth = -1;
    contents.make_null();
    make_reject(f,b);
}
Bag(TYPE)::Bag(TYPE)(
    Pred_obj(CONST(TYPE))& f,
    const Bag(TYPE)& b,
    Bag_reject_ATTLC*
):
    sze(0),
    sze_unique(0),
    iter_head(0)
{
    pos.curr_depth = -1;
    contents.make_null();
    make_reject(f,b);
}
Bag(TYPE)::Bag(TYPE)(
    Transformer(CONST(TYPE))& f,
    const Bag(TYPE)& b,
    Bag_map_ATTLC*
):
    sze(0),
    sze_unique(0),
    iter_head(0)
{
    pos.curr_depth = -1;
    contents.make_null();
    make_map(f,b);
}
Bag(TYPE)::Bag(TYPE)(
    Tran_obj(CONST(TYPE))& f,
    const Bag(TYPE)& b,
    Bag_map_ATTLC*
):
    sze(0),
    sze_unique(0),
    iter_head(0)
{
    pos.curr_depth = -1;
    contents.make_null();
    make_map(f,b);
}
Bag(TYPE)::Bag(TYPE)(
    const Bag(TYPE)& a,
    const Bag(TYPE)& b,
    Bag_union_ATTLC*
):
    sze(0),
    sze_unique(0),
    iter_head(0)
{
    pos.curr_depth = -1;
    contents.make_null();
    make_union(a,b);
}
Bag(TYPE)::Bag(TYPE)(
    const Bag(TYPE)& a,
    const Bag(TYPE)& b,
    Bag_inter_ATTLC*
):
    sze(0),
    sze_unique(0),
    iter_head(0)
{
    pos.curr_depth = -1;
    contents.make_null();
    make_intersection(a, b);
}
Bag(TYPE)::Bag(TYPE)(
    const Bag(TYPE)& a,
    const Bag(TYPE)& b,
    Bag_diff_ATTLC*
):
    sze(0),
    sze_unique(0),
    iter_head(0)
{
    pos.curr_depth = -1;
    contents.make_null();
    make_difference(a, b);
}
Bag(TYPE)::Bag(TYPE)(
    const Bag(TYPE)& a,
    const Bag(TYPE)& b,
    Bag_xor_ATTLC*
):
    sze(0),
    sze_unique(0),
    iter_head(0)
{
    pos.curr_depth = -1;
    contents.make_null();
    make_xor(a,b);
}
Bag(TYPE)::Bag(TYPE)(
    Generator(CONST(TYPE))& f
):
    sze(0),
    sze_unique(0),
    iter_head(0)
{
    pos.curr_depth = -1;
    contents.make_null();
    const TYPE* tp;

    while(
        tp = f()
    ){
        insert(*tp);
    }
}
Bag(TYPE)::Bag(TYPE)(
    Gene_obj(CONST(TYPE))& f
):
    sze(0),
    sze_unique(0),
    iter_head(0)
{
    pos.curr_depth = -1;
    contents.make_null();
    const TYPE* tp;

    while(
        tp = f()
    ){
        insert(*tp);
    }
}
void
Bag(TYPE)::make_select(
    Pred_obj(CONST(TYPE))& f,
    const Bag(TYPE)& b
){
    assert(sze==0);
    Bag_bucketiter_ATTLC(TYPE) bi(b);
    const Bag_bucket_ATTLC(TYPE)* bp = bi.first();

    while(
	bp
    ){
	Listiter(Bag_pair(TYPE)) li(((Bag_bucket_ATTLC(TYPE)*)bp)->collision_list);

	while(
	    !li.at_end()
	){
	    Bag_pair(TYPE)* tp;
	    li.next(tp);

	    for(int i=0;i<tp->count;i++){

		if(
		    f(&tp->value)
		){
		    insert(tp->value);
		}
	    }
	}
	bp = bi.next();
    }
}
void
Bag(TYPE)::make_reject(
    Pred_obj(CONST(TYPE))& f,
    const Bag(TYPE)& b
){
    assert(sze==0);
    Bag_bucketiter_ATTLC(TYPE) bi(b);
    const Bag_bucket_ATTLC(TYPE)* bp = bi.first();

    while(
	bp
    ){
	Listiter(Bag_pair(TYPE)) li(((Bag_bucket_ATTLC(TYPE)*)bp)->collision_list);

	while(
	    !li.at_end()
	){
	    Bag_pair(TYPE)* tp;
	    li.next(tp);

	    for(int i=0;i<tp->count;i++){

		if(
		    !f(&tp->value)
		){
		    insert(tp->value);
		}
	    }
	}
	bp = bi.next();
    }
}
void
Bag(TYPE)::make_map(
    Tran_obj(CONST(TYPE))& f,
    const Bag(TYPE)& b
){
    Bag_bucketiter_ATTLC(TYPE) bi(b);
    const Bag_bucket_ATTLC(TYPE)* bp = bi.first();

    while(
	bp
    ){
	Listiter(Bag_pair(TYPE)) li(((Bag_bucket_ATTLC(TYPE)*)bp)->collision_list);

	while(
	    !li.at_end()
	){
	    Bag_pair(TYPE)* tp;
	    li.next(tp);

	    for(int i=0;i<tp->count;i++){
		insert(*f(&tp->value));
	    }
	}
	bp = bi.next();
    }
}
void
Bag(TYPE)::do_each(
    Proc_obj(CONST(TYPE))& f
)const{
    Bag_bucketiter_ATTLC(TYPE) bi(*this);
    const Bag_bucket_ATTLC(TYPE)* bp = bi.first();

    while(
	bp
    ){
	Listiter(Bag_pair(TYPE)) li(((Bag_bucket_ATTLC(TYPE)*)bp)->collision_list);

	while(
	    !li.at_end()
	){
	    Bag_pair(TYPE)* tp;
	    li.next(tp);

	    for(int i=0;i<tp->count;i++){
		f(&tp->value);
	    }
	}
	bp = bi.next();
    }
}
void
Bag(TYPE)::do_each(
    Procedure(CONST(TYPE))& f
)const{
    Bag_bucketiter_ATTLC(TYPE) bi(*this);
    const Bag_bucket_ATTLC(TYPE)* bp = bi.first();

    while(
	bp
    ){
	Listiter(Bag_pair(TYPE)) li(((Bag_bucket_ATTLC(TYPE)*)bp)->collision_list);

	while(
	    !li.at_end()
	){
	    Bag_pair(TYPE)* tp;
	    li.next(tp);

	    for(int i=0;i<tp->count;i++){
		f(&tp->value);
	    }
	}
	bp = bi.next();
    }
}
const TYPE*
Bag(TYPE)::do_while(
    Pred_obj(CONST(TYPE))& f
)const{
    Bag_bucketiter_ATTLC(TYPE) bi(*this);
    const Bag_bucket_ATTLC(TYPE)* bp = bi.first();

    while(
	bp
    ){
	Listiter(Bag_pair(TYPE)) li(((Bag_bucket_ATTLC(TYPE)*)bp)->collision_list);

	while(
	    !li.at_end()
	){
	    Bag_pair(TYPE)* tp;
	    li.next(tp);

	    for(int i=0;i<tp->count;i++){

		if(
		    !f(&tp->value)
		){
		    return &(tp->value);
		}
	    }
	}
	bp = bi.next();
    }
    return 0;
}
const TYPE*
Bag(TYPE)::do_while(
    Predicate(CONST(TYPE))& f
)const{
    Bag_bucketiter_ATTLC(TYPE) bi(*this);
    const Bag_bucket_ATTLC(TYPE)* bp = bi.first();

    while(
	bp
    ){
	Listiter(Bag_pair(TYPE)) li(((Bag_bucket_ATTLC(TYPE)*)bp)->collision_list);

	while(
	    !li.at_end()
	){
	    Bag_pair(TYPE)* tp;
	    li.next(tp);

	    for(int i=0;i<tp->count;i++){

		if(
		    !f(&tp->value)
		){
		    return &(tp->value);
		}
	    }
	}
	bp = bi.next();
    }
    return 0;
}
const TYPE*
Bag(TYPE)::do_until(
    Pred_obj(CONST(TYPE))& f
)const{
    Bag_bucketiter_ATTLC(TYPE) bi(*this);
    const Bag_bucket_ATTLC(TYPE)* bp = bi.first();

    while(
	bp
    ){
	Listiter(Bag_pair(TYPE)) li(((Bag_bucket_ATTLC(TYPE)*)bp)->collision_list);

	while(
	    !li.at_end()
	){
	    Bag_pair(TYPE)* tp;
	    li.next(tp);

	    for(int i=0;i<tp->count;i++){

		if(
		    f(&tp->value)
		){
		    return &(tp->value);
		}
	    }
	}
	bp = bi.next();
    }
    return 0;
}
const TYPE*
Bag(TYPE)::do_until(
    Predicate(CONST(TYPE))& f
)const{
    Bag_bucketiter_ATTLC(TYPE) bi(*this);
    const Bag_bucket_ATTLC(TYPE)* bp = bi.first();

    while(
	bp
    ){
	Listiter(Bag_pair(TYPE)) li(((Bag_bucket_ATTLC(TYPE)*)bp)->collision_list);

	while(
	    !li.at_end()
	){
	    Bag_pair(TYPE)* tp;
	    li.next(tp);

	    for(int i=0;i<tp->count;i++){

		if(
		    f(&tp->value)
		){
		    return &(tp->value);
		}
	    }
	}
	bp = bi.next();
    }
    return 0;
}
Bag(TYPE)&
Bag(TYPE)::operator=(
    const Bag(TYPE)& b
){
    if(
        this != &b
    ){
	remove_all();
	Bag_bucketiter_ATTLC(TYPE) bi(b);
	const Bag_bucket_ATTLC(TYPE)* bp = bi.first();

        while(
            bp
        ){
            Listiter(Bag_pair(TYPE)) li(((Bag_bucket_ATTLC(TYPE)*)bp)->collision_list);

            while(
                !li.at_end()
            ){
                Bag_pair(TYPE)* tp;
                li.next(tp);
                insert(tp->value,tp->count);
            }
            bp = bi.next();
        }
    }
    return *this;
}
int
Bag(TYPE)::operator==(
    const Bag(TYPE)& b
)const{

    if(
        size() != b.size()
    ){
        return 0;
    }
    Bag_bucketiter_ATTLC(TYPE)     		a_it(*this);
    Bag_bucketiter_ATTLC(TYPE)     		b_it(b);
    const Bag_bucket_ATTLC(TYPE)* ap =  a_it.first();
    const Bag_bucket_ATTLC(TYPE)* bp =  b_it.first();

    while(
        ap && bp
    ){
        if(
            ap->hashval != bp->hashval
        ){
            return 0;

        }
/*
**
**  The two collision lists must contain exactly
**  the same values and counts.
**
*/
        if(
            ap->collision_list.length() !=
            bp->collision_list.length()
        ){
            return 0;
        }
        Listiter(Bag_pair(TYPE)) lia(((Bag_bucket_ATTLC(TYPE)*)ap)->collision_list);
        Listiter(Bag_pair(TYPE)) lib(((Bag_bucket_ATTLC(TYPE)*)bp)->collision_list);

        while(
            !lia.at_end()
        ){
            Bag_pair(TYPE)* atp;
            lia.next(atp);
            lib.reset();
            int found=0;

            while(
                !lib.at_end()
            ){
                Bag_pair(TYPE)* btp;
                lib.next(btp);

                if(
                    atp->value == btp->value &&
                    atp->count == btp->count

                ){
                    found=1;
                    break;
                }
            }
            if(
                !found
            ){
                return 0;
            }
        }
        ap = a_it.next();
        bp = b_it.next();
    }
/*
**
**  The loop exited because either ap or bp became
**  zero.  If they are not both zero, the two Bags
**  are unequal.
**
*/
    if(
        ap != bp
    ){
        return 0;
    }
    return 1;
}
int
Bag(TYPE)::operator<=(
    const Bag(TYPE)& b
)const{

    if(
        size() > b.size()
    ){
        return 0;
    }
    Bag_bucketiter_ATTLC(TYPE)     		a_it(*this);
    Bag_bucketiter_ATTLC(TYPE)     		b_it(b);
    const Bag_bucket_ATTLC(TYPE)* ap =  a_it.first();
    const Bag_bucket_ATTLC(TYPE)* bp =  b_it.first();

    while(
        ap && bp
    ){
        if(
            ap->hashval == bp->hashval
        ){
/*
**
**
**  Make sure ap->collision_list is a subset of
**  bp->collision_list
**
*/
            if(
                ap->collision_list.length() >
                bp->collision_list.length()
            ){
                return 0;
            }
            Listiter(Bag_pair(TYPE)) lia(((Bag_bucket_ATTLC(TYPE)*)ap)->collision_list);
            Listiter(Bag_pair(TYPE)) lib(((Bag_bucket_ATTLC(TYPE)*)bp)->collision_list);

            while(
                !lia.at_end()
            ){
                Bag_pair(TYPE)* atp;
                lia.next(atp);
                lib.reset();
                int ok=0;

                while(
                    !lib.at_end()
                ){
                    Bag_pair(TYPE)* btp;
                    lib.next(btp);

                    if(
                        atp->value == btp->value &&
                        atp->count <= btp->count
                    ){
                        ok=1;
                        break;
                    }
                }
                if(
                    !ok
                ){
                    return 0;
                }
            }
            ap = a_it.next();
            bp = b_it.next();

        }else if(

            BAG_LT_ATTLC(ap->hashval,bp->hashval)
        ){
/*
**
**  *ap contains values that can't be in b, since we've
**  already passed the point where they would be found;
**  return failure
**
*/
            return 0;

        }else{
/*
**
**  *ap contains values that may be in a future
**  Bag_bucket of b; increment b_it
**
*/
            bp = b_it.next();
        }
    }
/*
**
**  The relation is true only if a_it is exhasted
**
*/
    return ap==0;
}
int
Bag(TYPE)::operator<(
    const Bag(TYPE)& b
)const{
/*
**
**  Strict(a.k.a. proper) subset requires that
**  Bag b have at least one more element than this Bag.
**
*/
    if(
        size() >= b.size()
    ){
        return 0;
    }
    Bag_bucketiter_ATTLC(TYPE)     		a_it(*this);
    Bag_bucketiter_ATTLC(TYPE)     		b_it(b);
    const Bag_bucket_ATTLC(TYPE)* ap =  a_it.first();
    const Bag_bucket_ATTLC(TYPE)* bp =  b_it.first();
    int strict=0;

    while(
        ap && bp
    ){
        if(
            ap->hashval == bp->hashval
        ){
/*
**
**  ap->collision_list must be a subset (not necessarily
**  strict) of bp->collision_list.
**
*/
            if(
                ap->collision_list.length() >
                bp->collision_list.length()
            ){
                return 0;
            }
            Listiter(Bag_pair(TYPE)) lia(((Bag_bucket_ATTLC(TYPE)*)ap)->collision_list);
            Listiter(Bag_pair(TYPE)) lib(((Bag_bucket_ATTLC(TYPE)*)bp)->collision_list);

            if(
                ap->collision_list.length() <
                bp->collision_list.length()
            ){
		strict = 1;
	    }
            while(
                !lia.at_end()
            ){
                Bag_pair(TYPE)* atp;
                lia.next(atp);
                lib.reset();
                int found=0;

                while(
                    !lib.at_end()
                ){
                    Bag_pair(TYPE)* btp;
                    lib.next(btp);

                    if(
                        atp->value == btp->value
                    ){
                        found=1;

                        if(
                            atp->count > btp->count
                        ){
                            return 0;
                        }
			if(
                            atp->count < btp->count
                        ){
			    strict=1;
			}
                        break;
                    }
                }
                if(
                    !found
                ){
                    return 0;
                }
            }
            ap = a_it.next();
            bp = b_it.next();

        }else if(

            BAG_LT_ATTLC(ap->hashval,bp->hashval)
        ){
/*
**
**  *ap contains values that can't be in b, since we've
**  already passed the point where they would be found;
**  return failure
**
*/
            return 0;

        }else{
/*
**
**  *ap contains values that may be in a future Bag_bucket of b;
**  increment b_it
**
*/
	    strict = 1;
            bp = b_it.next();
        }
    }
/*
**
**  The relation is strict if bp is not exhausted
**
*/
    strict = strict || bp;
/*
**
**  The relation is true only if strict and a_it
**  is exhausted
**
*/
    return strict && (ap==0);
}
const Bag_pair(TYPE)*
Bag(TYPE)::insert(
    const TYPE& value,
    int count
){
    Bag_internal_item_ATTLC* itemp;
    Bag_internal_node_ATTLC* nodep;
    Bag_bucket_ATTLC(TYPE)* bp;
    Bag_pair(TYPE)* result;

    if( count<=0 ){
        return 0;
    }
/*
**
**  Hash the value
**
*/
    Set_or_Bag_hashval hval = H(value);
/*
**
**  See how much of hval matches pos.curr_value
**  (equivalently, see how much of pos is valid.)
**  This will determine where we start looking for the
**  insertion point.  This is an optimization that takes
**  advantage of the phenomenon that many operations
**  create a Bag by walking an existing index and
**  inserting its elements into the new Bag.
**
*/
    long mask = BAG_MASK_BITS << BAG_INITIAL_SHIFT;

    for(
         int depth = -1;
         depth < pos.curr_depth;
         depth++, mask <<= BAG_SHIFT_INCR
     ){
        if(
            (pos.curr_value & mask) !=
            (hval & mask)
        ){
            break;
        }
    }
/*
**
**  If depth = -1, no bits match;
**  if depth = 0, bits 0..3 match, etc.
**
*/
    register int unshift = (
        BAG_INITIAL_SHIFT +
        BAG_SHIFT_INCR +
        depth * BAG_SHIFT_INCR
    );
    itemp = (
        depth == -1 ?(
            &contents
        ):(
            pos.curr_pos[depth]
        )
    );
/*
**
**  Clobber all the active iterators
**
*/
    warn_iterators();
/*
**
**  Find the insertion point
**
*/
    pos.curr_value = hval;
    nodep = 0;

    for(
        pos.curr_depth = depth;
        ;
        mask <<= BAG_SHIFT_INCR, unshift += BAG_SHIFT_INCR
    ){
        assert(pos.curr_depth < BAG_POSITIONS);

        if(
            itemp->is_null()
        ){

            break;

        }else if(
            itemp->is_leaf()
        ){

            bp = (Bag_bucket_ATTLC(TYPE)*)itemp->external_leaf();

            if(
                bp->hashval == hval
            ){
/*
**
**  The 'value' goes in this Bag_bucket
**
*/
                Listiter(Bag_pair(TYPE)) it(((Bag_bucket_ATTLC(TYPE)*)bp)->collision_list);
                Bag_pair(TYPE)* tp;

                while(
                    it.next(tp)
                ){

                    if(
                        tp->value == value
                    ){
                        sze += count;
                        tp->count += count;
                        return tp;
                    }
                }
/*
**
**  The value is not already in the Bag_bucket;
**  insert it
**
*/
		sze_unique+=1;
                sze += count;
                Bag_pair(TYPE) pair1;
                pair1.value = value;
                pair1.count = count;
                it.insert_next(pair1);
		it.peek_next(result);
                return result;

            }else{
/*
**
**  This Bag_bucket is not the one where the value
**  belongs; a subindex will have to be created
**  containing both this Bag_bucket and a new one
**  created to hold 'value.'
**
*/
                break;

            }

        }else{
/*
**
**  Node: search subindex
**
*/
            nodep = itemp->next_node();
            assert(nodep);
            pos.curr_pos[++pos.curr_depth] = itemp =(
                &nodep->item[(hval & mask) >> unshift]
            );
        }
    }
/*
**
**  ASSERT: itemp is either null or is a leaf that must
**  be moved down into a subindex containing BOTH the
**  existing leaf and a new leaf pointing to a new
**  Bag_bucket containing 'value.'  In either case, the
**  cardinality of the Bag is increased by 'count'.
**
*/
    sze_unique += 1;
    sze += count;

    if(
        itemp->is_null()
    ){
/*
**
**  Make this null slot into a leaf pointing to a new
**  Bag_bucket containing 'value'
**
*/
        itemp->make_leaf( new Bag_bucket_ATTLC(TYPE) );
        bp = (Bag_bucket_ATTLC(TYPE)*)itemp->external_leaf();
        bp->hashval = hval;
        Bag_pair(TYPE) pair2;
        pair2.value = value;
        pair2.count = count;
        bp->collision_list.insert_next(pair2);
	bp->collision_list.peek_next(result);

        if(
            pos.curr_depth > 0
        ){
            pos.curr_pos[pos.curr_depth-1]->next_node()->busy_count++;
        }else if(
            pos.curr_depth == 0
        ){
            contents.next_node()->busy_count++;
        }
        return result;

    }else{

        assert(itemp->is_leaf());
/*
**
**  Replace this leaf by a subindex containing both the
**  original leaf and a new leaf pointing to a new
**  Bag_bucket containing 'value'
**
*/
        bp = (Bag_bucket_ATTLC(TYPE)*)itemp->external_leaf();
        Set_or_Bag_hashval temp = bp->hashval;
        int ind1,ind2;

        for(
            ;
            ;
            mask <<= BAG_SHIFT_INCR, unshift += BAG_SHIFT_INCR
        ){
            itemp->make_node(nodep = new Bag_internal_node_ATTLC);
            assert(pos.curr_depth < BAG_POSITIONS);
            ind1 = int(((long)temp & mask) >> unshift);
            ind2 = int((hval & mask) >> unshift);

            if(
                ind1 != ind2
            ){
/*
**
**  Serendipitous case
**
*/
                break;
            }
            nodep->busy_count = 1;
            itemp = &nodep->item[ind1];
            pos.curr_pos[++pos.curr_depth] = itemp;
        }
/*
**
**  Move the existing leaf down into the subindex
**
*/
        nodep->item[ind1].make_leaf(bp);
/*
**
**  Make a new leaf and Bag_bucket for 'value'
**
*/
        itemp = &nodep->item[ind2];
        itemp->make_leaf( new Bag_bucket_ATTLC(TYPE) );
        bp = (Bag_bucket_ATTLC(TYPE)*)itemp->external_leaf();
        bp->hashval = hval;
        Bag_pair(TYPE) pair;
        pair.value = value;
        pair.count = count;
        bp->collision_list.insert_next(pair);
	bp->collision_list.peek_next(result);
        pos.curr_pos[++pos.curr_depth] = itemp;
        nodep->busy_count = 2;
        return result;
    }
}
unsigned int
Bag(TYPE)::remove(
    const TYPE& value, 
    int count
){
    Bag_internal_item_ATTLC* itemp;
    Bag_internal_node_ATTLC* nodep;
    Bag_bucket_ATTLC(TYPE)* bp=0;
    unsigned int result;

    if( count<=0 ){
        return 0;
    }
/*
**
**  Hash the value
**
*/
    Set_or_Bag_hashval hval = H(value);
/*
**
**  See how much of hval matches pos.curr_value
**  (equivalently, see how much of pos is valid.)
**  This will determine where we start looking for the
**  deletion point.  This is an optimization that takes
**  advantage of the phenomenon that many operations
**  create a Bag by walking an existing index and
**  inserting its elements into the new Bag.
**
*/
    long mask = BAG_MASK_BITS << BAG_INITIAL_SHIFT;

    for(
        int depth = -1;
        depth < pos.curr_depth;
        depth++, mask <<= BAG_SHIFT_INCR
    ){
        if(
            (pos.curr_value & mask) !=
            (hval & mask)
        ){
            break;
        }
    }
/*
**
**  If depth = -1, no bits match;
**  If depth = 0, bits 0...3 match, etc.
**
*/
    register int unshift = (
        BAG_INITIAL_SHIFT +
        BAG_SHIFT_INCR +
        depth * BAG_SHIFT_INCR
    );
    itemp = (
        depth == -1 ?(
            &contents
        ):(
            pos.curr_pos[depth]
        )
    );
    nodep = 0;
    pos.curr_value = hval;
    warn_iterators();
/*
**
**  Find the leaf pointing to the Bag_bucket containing
**  the value to be deleted.
**
*/
    for(
        pos.curr_depth = depth;
        ;
        mask <<= BAG_SHIFT_INCR,
        unshift += BAG_SHIFT_INCR
    ){
        assert(pos.curr_depth < BAG_POSITIONS);

        if(
            itemp->is_null()
        ){
/*
**
**  The value must have been deleted already.
**  Return failure.
**
*/
            return 0;
        }
        if(
            itemp->is_leaf()
        ){

            bp = (Bag_bucket_ATTLC(TYPE)*)itemp->external_leaf();

            if(
                bp->hashval == hval
            ){
/*
**
**  The value may be in the Bag_bucket pointed to by
**  this leaf.
**
*/
                break;

            }else{
/*
**
**  The leaf must have been deleted and subsequently
**  replaced by a different Bag_bucket (one with a
**  different hash value).  Return failure.
**
*/
                return 0;
            }

        }else{
/*
**
**  Node: search subindex
**
*/
            nodep = itemp->next_node();
            assert(nodep);
            pos.curr_pos[++pos.curr_depth] = itemp = (
                &nodep->item[(pos.curr_value & mask)>>unshift]
            );
        }
    }
    assert(bp && bp->hashval==hval);
/*
**
**  We found the Bag_bucket; locate the value in the
**  collision list and remove it
**
*/
    Listiter(Bag_pair(TYPE)) it(((Bag_bucket_ATTLC(TYPE)*)bp)->collision_list);
    Bag_pair(TYPE)* tp;
    int found=0;

    while(
        it.next(tp)
    ){
        if(
            tp->value == value
        ){
            found=1;

            if(
                tp->count > count
            ){
                result = count;
                tp->count -= result;
            }else{
		sze_unique -= 1;
                result = tp->count;
                it.remove_prev();
            }
            sze -= result;
            break;
        }
    }
    if(
        !found
    ){
/*
**
**  The value was not found; return failure
**
*/
        return 0;
    }
/*
**
**  The value was found and deleted.  We must now
**  worry about the Bag_bucket becoming empty.
**
*/
    if(
        bp->collision_list.length() > 0
    ){
/*
**
**  The collision list still has one or more elements.
**
*/
        return result;
    }
/*
**
**  The collision list has become empty as a result of
**  this deletion; we must delete the Bag_bucket and
**  fix up the index accordingly.
**
*/
    if(
        pos.curr_depth == -1
    ){
/*
**
**  Contents was a leaf and its Bucket now contains
**  an empty list; the Bag is now empty
**
*/
        assert(sze == 0);
        delete bp;
        itemp->make_null();
        return result;
    }
/*
**
**  Nodep is the pointer to the node containing
**  this leaf (it will be zero if the cache was
**  up-to-date when we entered this function
**
*/
    if(
        nodep == 0
    ){
        nodep = (
            pos.curr_depth == 0 ?(
                contents.next_node()
            ):(
                pos.curr_pos[pos.curr_depth-1]->next_node()
            )
        );
    }
    if(
        --(nodep->busy_count) > 1
    ){
/*
**
**  Easy case: node still has at least one leaf left
**
*/
        delete bp;
        itemp->make_null();
        return result;
    }
/*
**
**  Hard case: node has only one leaf in it; must
**  collapse node into a leaf
**
*/
    assert(nodep->busy_count == 1);
/*
**
**  Scan for a non-null item
**
*/
    for (
        Bag_internal_item_ATTLC* itp = &nodep->item[0];
        itp < &nodep->item[BAG_NODE_SIZE];
        itp++
    ){
        if(
            itp != itemp &&
            !itp->is_null()
        ){
            break;
        }
    }
    if(
        !itp->is_leaf()
    ){
/*
**
**  Complicated case: punt (we won't try to absorb
**  a node)
**
*/
        delete bp;
        itemp->make_null();
        return result;
    }
    Bag_bucket_ATTLC(TYPE)* temp = (Bag_bucket_ATTLC(TYPE)*)itp->external_leaf();

    for(
        ;
        ;
    ){
        delete nodep;

        if(
            pos.curr_depth-- == 0
        ){
            contents.make_leaf(temp);
            break;
        }
        nodep = (
            pos.curr_depth == 0 ?(
                contents.next_node()
            ):(
                pos.curr_pos[pos.curr_depth-1]->next_node()
            )
        );
        if(
            nodep->busy_count > 1
        ){
            pos.curr_pos[pos.curr_depth]->make_leaf(temp);
            break;
        }
        assert(nodep->busy_count == 1);
    }
    return result;
}
unsigned int
Bag(TYPE)::remove_all(
    const TYPE& value
){
    return remove(value,count(value));
}
unsigned int
Bag(TYPE)::remove_all(){
    unsigned int result = sze;
    warn_iterators();
    Bag_internal_item_ATTLC* itemp = &contents;

    if(
        itemp->is_null()
    ){
        assert(sze == 0);
        assert(sze_unique == 0);
        return result;
    }
    if(
        itemp->is_leaf()
    ){
        assert(sze >= 1);
        assert(sze_unique >= 1);
/*
**
**  We must destroy the bucket
**
*/
	Bag_bucket_ATTLC(TYPE)* bp = (
	    (Bag_bucket_ATTLC(TYPE)*)itemp->external_leaf()
	);
        delete bp;
        itemp->make_null();
	pos.curr_depth = -1;
        sze = 0;
        sze_unique = 0;
        return result;
    }
    Bag_internal_node_ATTLC* nodep = itemp->next_node();
    itemp = &nodep->item[0];
    pos.curr_depth = -1;

    for(;;) {
        Bag_internal_item_ATTLC* stopper = (
            &nodep->item[BAG_NODE_SIZE]
        );
        for (
            ;
            itemp < stopper;
            itemp++
        ){
            if(
                itemp->is_node()
            ){
                pos.curr_pos[++pos.curr_depth] = itemp;
                nodep = itemp->next_node();
                itemp = &nodep->item[0];
                stopper = &nodep->item[BAG_NODE_SIZE];
            }
        }
/*
**
**  Unlike Set_of_p, we must destroy the buckets
**  pointed to by this node
**
*/
	for(
	    itemp = &nodep->item[0];
	    itemp < &nodep->item[BAG_NODE_SIZE];
	    itemp++
	){
	    if(
		itemp->is_leaf()
	    ){
		Bag_bucket_ATTLC(TYPE)* bp = (
		    (Bag_bucket_ATTLC(TYPE)*)itemp->external_leaf()
		);
		delete bp;
		itemp->make_null();
	    }
	}
        delete nodep;

        if(
            pos.curr_depth < 0
        ){
            break;
        }
        itemp = pos.curr_pos[pos.curr_depth--] + 1;
        nodep = (
            pos.curr_depth < 0 ?(
                contents.next_node()
            ):(
                pos.curr_pos[pos.curr_depth]->next_node()
            )
        );
    }
    pos.curr_depth = -1;
    contents.make_null();
    sze = 0;
    sze_unique = 0;
    return result;
}
const Bag_pair(TYPE)*
Bag(TYPE)::select()const{
    Bag_bucketiter_ATTLC(TYPE) bi(*this);
    const Bag_bucket_ATTLC(TYPE)* bp = bi.first();

    if(!bp){
	return 0;
    }
    Listiter(Bag_pair(TYPE)) li(((Bag_bucket_ATTLC(TYPE)*)bp)->collision_list);
    Bag_pair(TYPE)* result;
    li.next(result);
    return result;
}
const Bag_pair(TYPE)*
Bag(TYPE)::contains(
    const TYPE& value
)const{
    Bag_internal_item_ATTLC* itemp;
    Bag_internal_node_ATTLC* nodep;
    Bag_bucket_ATTLC(TYPE)* bp;
/*
**
**  Hash the value
**
*/
    Set_or_Bag_hashval hval = H(value);
/*
**
**  See how much of pos is still good
**
*/
    long mask = BAG_MASK_BITS << BAG_INITIAL_SHIFT;

    for(
        int depth = -1;
        depth < pos.curr_depth;
        depth++, mask <<= BAG_SHIFT_INCR
    ){
        if(
            (pos.curr_value & mask) !=
            (hval & mask)
        ){
            break;
        }
    }
    register int unshift = (
        BAG_INITIAL_SHIFT +
        BAG_SHIFT_INCR +
        depth * BAG_SHIFT_INCR
    );
    itemp = (

        depth == -1 ?(
            &(((Bag(TYPE) *)this)->contents)
        ):(
            pos.curr_pos[depth]
        )
    );
    nodep = 0;
    pos.curr_value = hval;

    for(
        pos.curr_depth = depth;
        ;
        mask <<= BAG_SHIFT_INCR, unshift += BAG_SHIFT_INCR
    ){
        assert(pos.curr_depth < BAG_POSITIONS);

        if(
            itemp->is_null()
        ){
            return 0;
        }
        if(
            itemp->is_leaf()
        ){
/*
**
**  Search the the collision list
**
*/
            bp = (Bag_bucket_ATTLC(TYPE)*)itemp->external_leaf();
            Listiter(Bag_pair(TYPE)) it(((Bag_bucket_ATTLC(TYPE)*)bp)->collision_list);
            Bag_pair(TYPE)* tp;

            while(
                it.next(tp)
            ){

                if(
                    tp->value == value
                ){
                    return tp;
                }
            }
            return 0;

        }else{

            nodep = itemp->next_node();
            assert(nodep);
            pos.curr_pos[++pos.curr_depth] = itemp =(
                &nodep->item[(pos.curr_value & mask) >> unshift]
            );
        }
    }
}
unsigned int
Bag(TYPE)::count(
    const TYPE& value
)const{
/*
**
**  New version uses latest version of contains
**
*/
    const Bag_pair(TYPE)* tp = contains(value);

    if(
	tp
    ){
	return tp->count;
    }else{
	return 0;
    }
}
Bag(TYPE)&
Bag(TYPE)::operator|=(
    const Bag(TYPE)& b
){
    if(
        this != &b
    ){
        Bag_bucketiter_ATTLC(TYPE) bi(b);
        const Bag_bucket_ATTLC(TYPE)* bp = bi.first();

        while(
            bp
        ){
            Listiter(Bag_pair(TYPE)) it(((Bag_bucket_ATTLC(TYPE)*)bp)->collision_list);
            Bag_pair(TYPE)* tp;

            while(
                it.next(tp)
            ){
                insert(tp->value,tp->count);
            }
            bp = bi.next();
        }
    }else{
/*
**
**  Union with self: double all counts
**
*/
        Bag_bucketiter_ATTLC(TYPE) bi(*this);
        const Bag_bucket_ATTLC(TYPE)* bp = bi.first();

        while(
            bp
        ){
            Listiter(Bag_pair(TYPE)) it(((Bag_bucket_ATTLC(TYPE)*)bp)->collision_list);
            Bag_pair(TYPE)* tp;

            while(
                it.next(tp)
            ){
		tp->count *= 2;
            }
            bp = bi.next();
        }
    }
    return *this;
}
Bag(TYPE)&
Bag(TYPE)::operator-=(
    const Bag(TYPE)& b
){
    if(
        this != &b
    ){
        Bag_bucketiter_ATTLC(TYPE) bi(b);
        const Bag_bucket_ATTLC(TYPE)* bp = bi.first();

        while(
            bp
        ){
            Listiter(Bag_pair(TYPE)) it(((Bag_bucket_ATTLC(TYPE)*)bp)->collision_list);
            Bag_pair(TYPE)* tp;

            while(
		it.next(tp)
            ){
	        int result = remove(tp->value,tp->count);
            }
            bp = bi.next();
        }
    }else{
        remove_all();
    }
    return *this;
}
Bag(TYPE)&
Bag(TYPE)::operator&=(
    const Bag(TYPE)& b
){
    if(
        this != &b
    ){
        Bag_bucketiter_ATTLC(TYPE) ai(*this);
        const Bag_bucket_ATTLC(TYPE)* ap = ai.first();

        while(
            ap
        ){
            Listiter(Bag_pair(TYPE)) it(((Bag_bucket_ATTLC(TYPE)*)ap)->collision_list);
            Bag_pair(TYPE)* tp;

            while(
/*
**
**  remove may delete the bucket; beware of dangling
**  list iterator.
**
*/
		it.the_list() &&
		it.next(tp)
            ){
		int my_count = tp->count;
		assert(my_count>0);
		int b_count = b.count(tp->value);
		int retain = (
		    my_count < b_count ?(
			my_count
		    ):(
			b_count
		    )
		);
		int subtract = my_count - retain;

		if(
		    subtract > 0
		){
		    (void)remove(tp->value,subtract);
		}
            }
            ap = ai.next();
        }
    }
    return *this;
}
Bag(TYPE)&
Bag(TYPE)::operator^=(
    const Bag(TYPE)& b
){
    if(
        this != &b
    ){
        Bag_bucketiter_ATTLC(TYPE) a_it(*this);
        Bag_bucketiter_ATTLC(TYPE) b_it(b);
        const Bag_bucket_ATTLC(TYPE)* ap = a_it.first();
        const Bag_bucket_ATTLC(TYPE)* bp = b_it.first();

        while(
            ap && bp
        ){
            if(
                ap->hashval == bp->hashval
            ){
/*
**
**  The two hash values are equal; this means the two
**  collision lists may contain equal values (which must
**  be weeded out)
**
*/
		Listiter(Bag_pair(TYPE))
		lia(((Bag_bucket_ATTLC(TYPE)*)ap)->collision_list);

		Listiter(Bag_pair(TYPE))
		lib(((Bag_bucket_ATTLC(TYPE)*)bp)->collision_list);

		lib.reset();

		while(
		    !lib.at_end()
		){
		    Bag_pair(TYPE)* btp;
		    Bag_pair(TYPE)* atp;
		    lib.next(btp);
		    lia.reset();
		    int found=0;

		    while(
			!lia.at_end()
		    ){
			lia.next(atp);

			if(
			    atp->value == btp->value
			){
			    found=1;
			    break;
			}
		    }
		    if(
			found
		    ){
			int a_count = atp->count;
			int b_count = btp->count;

			if(
			    a_count >= b_count
			){
			    remove(
				atp->value,
				b_count
			    );
			}else{
			    insert(
				atp->value,
				a_count-b_count
			    );
			}
		    }else{
			insert(btp->value,btp->count);
		    }
		}
		ap = a_it.next();
		bp = b_it.next();
            }else if(
                BAG_LT_ATTLC( ap->hashval, bp->hashval )
            ){
                ap = a_it.next();
            }else{
		Listiter(Bag_pair(TYPE))
		lib(((Bag_bucket_ATTLC(TYPE)*)bp)->collision_list);

		while(
		    !lib.at_end()
		){
		    Bag_pair(TYPE)* btp;
		    lib.next(btp);
		    insert(btp->value,btp->count);

		}
                bp = b_it.next();
            }
        }
        while(
            bp
        ){
	    Listiter(Bag_pair(TYPE))
	    lib(((Bag_bucket_ATTLC(TYPE)*)bp)->collision_list);

            Bag_pair(TYPE)* btp;
	    lib.next(btp);
	    insert(btp->value,btp->count);
            bp = b_it.next();
        }
    }else{
        remove_all();
    }
    return *this;
}
void
Bag(TYPE)::warn_iterators()const{

    for(
        Bag_bucketiter_ATTLC(TYPE)* it = iter_head;
        it;
        it = it->next_it
    ){
        it->clobber();
    }
}
void
Bag(TYPE)::histogram(
    Map(Set_or_Bag_hashval,unsigned)& m
)const{
/*
**
**  Iterate over Bag_buckets, creating a Map from
**  bp->hashval to bp->collision_list.length().
**
*/
    Bag_bucketiter_ATTLC(TYPE) bi(*this);
    const Bag_bucket_ATTLC(TYPE)* bp = bi.first();
    m = Map(Set_or_Bag_hashval,unsigned)();

    while(
        bp
    ){
        m[bp->hashval] = bp->collision_list.length();
        bp = bi.next();
    }
}
void
Bag(TYPE)::check()const{

    Bag_bucketiter_ATTLC(TYPE) bi(*this);
    const Bag_bucket_ATTLC(TYPE)* bp = bi.first();
    Set_or_Bag_hashval oldhashval=0;
    int first=1;

    while(
        bp
    ){
/*
**  Bag_buckets must be stored in increasing order of
**  hash value
*/
        if(
            first
        ){
            first=0;
        }else{
            assert(BAG_LT_ATTLC(oldhashval,bp->hashval));
        }
        oldhashval = bp->hashval;
/*
**
**  Collision lists may not be empty
**
*/
        assert(bp->collision_list.length()>0);
/*
**
**  Collision lists may not contain duplicates and
**  counts must be greater than or equal to 1
**
*/
        Listiter(Bag_pair(TYPE)) it1(((Bag_bucket_ATTLC(TYPE)*)bp)->collision_list);

        while(
            !it1.at_end()
        ){
            Bag_pair(TYPE)* p1;
            it1.next(p1);
            assert(p1->count>=1);
            Listiter(Bag_pair(TYPE)) it2(it1);

            while(
                !it2.at_end()
            ){
                Bag_pair(TYPE)* p2;
                it2.next(p2);
                assert(!(p1->value == p2->value));
            }
        }
        bp = bi.next();
    }
}
Bag(TYPE)::~Bag(TYPE)(){
/*
**
**  TBD_study this
**
*/
    for(
        Bag_bucketiter_ATTLC(TYPE)* it = iter_head;
        it;
        it = it->next_it
    ){
/*
**
**  Break const for giggles
**
*/
        Bag(TYPE)** cheat = (Bag(TYPE)**)&it->my_bag;
        *cheat = 0;
    }
    remove_all();
}
Bag(TYPE)::Bag(TYPE)(
    const Bag(TYPE)& b
):
    sze(0),
    sze_unique(0),
    iter_head(0)
{
    pos.curr_depth = -1;
    contents.make_null();
    Bag_bucketiter_ATTLC(TYPE) bi(b);
    const Bag_bucket_ATTLC(TYPE)* bp = bi.first();

    while(
	bp
    ){
	Listiter(Bag_pair(TYPE)) li(((Bag_bucket_ATTLC(TYPE)*)bp)->collision_list);

	while(
	    !li.at_end()
	){
	    Bag_pair(TYPE)* tp;
	    li.next(tp);
	    insert(tp->value,tp->count);
	}
	bp = bi.next();
    }
}
void
Bag(TYPE)::make_select(
    Predicate(CONST(TYPE))& f,
    const Bag(TYPE)& b
){
    assert(sze == 0);
    Bag_bucketiter_ATTLC(TYPE) bi(b);
    const Bag_bucket_ATTLC(TYPE)* bp = bi.first();

    while(
	bp
    ){
	Listiter(Bag_pair(TYPE)) li(((Bag_bucket_ATTLC(TYPE)*)bp)->collision_list);

	while(
	    !li.at_end()
	){
	    Bag_pair(TYPE)* tp;
	    li.next(tp);

	    for(int i=0;i<tp->count;i++){

		if(
		    f(&tp->value)
		){
		    insert(tp->value);
		}
	    }
	}
	bp = bi.next();
    }
}
void
Bag(TYPE)::make_reject(
    Predicate(CONST(TYPE))& f,
    const Bag(TYPE)& b
){
    assert(sze == 0);
    Bag_bucketiter_ATTLC(TYPE) bi(b);
    const Bag_bucket_ATTLC(TYPE)* bp = bi.first();

    while(
	bp
    ){
	Listiter(Bag_pair(TYPE)) li(((Bag_bucket_ATTLC(TYPE)*)bp)->collision_list);

	while(
	    !li.at_end()
	){
	    Bag_pair(TYPE)* tp;
	    li.next(tp);

	    for(int i=0;i<tp->count;i++){

		if(
		    !f(&tp->value)
		){
		    insert(tp->value);
		}
	    }
	}
	bp = bi.next();
    }
}
void
Bag(TYPE)::make_map(
    Transformer(CONST(TYPE))& f,
    const Bag(TYPE)& b
){
    assert(sze == 0);
    Bag_bucketiter_ATTLC(TYPE) bi(b);
    const Bag_bucket_ATTLC(TYPE)* bp = bi.first();

    while(
	bp
    ){
	Listiter(Bag_pair(TYPE)) li(((Bag_bucket_ATTLC(TYPE)*)bp)->collision_list);

	while(
	    !li.at_end()
	){
	    Bag_pair(TYPE)* tp;
	    li.next(tp);

	    for(int i=0;i<tp->count;i++){
		insert(*f(&tp->value));
	    }
	}
	bp = bi.next();
    }
}
void
Bag(TYPE)::make_union(
    const Bag(TYPE)& a,
    const Bag(TYPE)& b
){
    assert(sze == 0);
/*
**
**  First, insert all elements from a
**
*/
    Bag_bucketiter_ATTLC(TYPE) a_it(a);
    const Bag_bucket_ATTLC(TYPE)* ap = a_it.first();

    while(
        ap
    ){
        Listiter(Bag_pair(TYPE)) lia(((Bag_bucket_ATTLC(TYPE)*)ap)->collision_list);

	while(
	    !lia.at_end()
	){
	    Bag_pair(TYPE)* atp;
	    lia.next(atp);
	    insert(atp->value,atp->count);
	}
	ap = a_it.next();
    }
/*
**
**  Next, insert all elements from b
**
*/
    Bag_bucketiter_ATTLC(TYPE) b_it(b);
    const Bag_bucket_ATTLC(TYPE)* bp = b_it.first();

    while(
        bp
    ){
        Listiter(Bag_pair(TYPE)) lib(((Bag_bucket_ATTLC(TYPE)*)bp)->collision_list);

	while(
	    !lib.at_end()
	){
	    Bag_pair(TYPE)* btp;
	    lib.next(btp);
	    insert(btp->value,btp->count);
	}
	bp = b_it.next();
    }
}
void
Bag(TYPE)::make_intersection(
    const Bag(TYPE)& a,
    const Bag(TYPE)& b
){
    assert(sze == 0);
    Bag_bucketiter_ATTLC(TYPE) a_it(a);
    Bag_bucketiter_ATTLC(TYPE) b_it(b);
    const Bag_bucket_ATTLC(TYPE)* ap = a_it.first();
    const Bag_bucket_ATTLC(TYPE)* bp = b_it.first();

    while(
        ap && bp
    ){
        Listiter(Bag_pair(TYPE)) lib(((Bag_bucket_ATTLC(TYPE)*)bp)->collision_list);
        Listiter(Bag_pair(TYPE)) lia(((Bag_bucket_ATTLC(TYPE)*)ap)->collision_list);

        if(
            ap->hashval == bp->hashval
        ){
/*
**
**  The two hash functions are equal; this means
**  that the hash Bag_buckets MAY contain equal values;
**  they must be scanned.
**
*/
            lib.reset();

            while(
                !lib.at_end()
            ){
                Bag_pair(TYPE)* btp;
                lib.next(btp);
                lia.reset();

                while(
                    !lia.at_end()
                ){
                    Bag_pair(TYPE)* atp;
                    lia.next(atp);

                    if(
                        atp->value == btp->value
                    ){
/*
**
**  The intersection consists of those elements in
**  BOTH a and b, i.e., the minimum of the two counts
**
*/
                        unsigned min = (
			    atp->count < btp->count ?(
				atp->count
			    ):(
				btp->count
			    )
			);
                        insert(btp->value,min);
                        break;
                    }
                }
            }
            ap = a_it.next();
            bp = b_it.next();

        }else{

/*
**
**  The two hash functions are unequal; this means there
**  CANNOT be any equal elements in the Bag_buckets.
**
*/
            if(
                BAG_LT_ATTLC( ap->hashval , bp->hashval )
            ){
                ap = a_it.next();
            }else{
                bp = b_it.next();
            }
        }
    }
}
void
Bag(TYPE)::make_difference(
    const Bag(TYPE)& a,
    const Bag(TYPE)& b
){
    assert(sze == 0);
    Bag_bucketiter_ATTLC(TYPE) a_it(a);
    Bag_bucketiter_ATTLC(TYPE) b_it(b);
    const Bag_bucket_ATTLC(TYPE)* ap = a_it.first();
    const Bag_bucket_ATTLC(TYPE)* bp = b_it.first();

    while(
        ap && bp
    ){
        Listiter(Bag_pair(TYPE)) lia(((Bag_bucket_ATTLC(TYPE)*)ap)->collision_list);
        Listiter(Bag_pair(TYPE)) lib(((Bag_bucket_ATTLC(TYPE)*)bp)->collision_list);

        if(
            ap->hashval == bp->hashval
        ){
/*
**
**  The two hash values are equal.  This means that
**  b may contain values to be subtracted from a.
**
*/
            lia.reset();

            while(
                !lia.at_end()
            ){
                Bag_pair(TYPE)* atp;
                Bag_pair(TYPE)* btp;
                lia.next(atp);
                lib.reset();
                int found=0;

                while(
                    !lib.at_end()
                ){
                    lib.next(btp);

                    if(
                        atp->value == btp->value
                    ){
                        found=1;
                        break;
                    }
                }
                if(
                    found
                ){
                    insert(atp->value,atp->count-btp->count);
                }else{
                    insert(atp->value,atp->count);
                }
            }
            ap = a_it.next();
            bp = b_it.next();
        }else if(
            BAG_LT_ATTLC( ap->hashval,bp->hashval )
        ){
/*
**
**  Insert all the values in *ap
**
*/
            lia.reset();

            while(
                !lia.at_end()
            ){
                Bag_pair(TYPE)* atp;
                lia.next(atp);
                insert(atp->value,atp->count);
            }
            ap = a_it.next();
        }else{
            bp = b_it.next();
        }
    }
/*
**
**  Insert the remaining values from ap Bag_buckets
**
*/
    while(
        ap
    ){
        Listiter(Bag_pair(TYPE)) lia(((Bag_bucket_ATTLC(TYPE)*)ap)->collision_list);

        while(
            !lia.at_end()
        ){
            Bag_pair(TYPE)* atp;
            lia.next(atp);
            insert(atp->value,atp->count);
        }
        ap = a_it.next();
    }
}
void
Bag(TYPE)::make_xor(
    const Bag(TYPE)& a,
    const Bag(TYPE)& b
){
    assert(sze == 0);
    Bag_bucketiter_ATTLC(TYPE)     a_it(a);
    Bag_bucketiter_ATTLC(TYPE)     b_it(b);
    const Bag_bucket_ATTLC(TYPE)* ap = a_it.first();
    const Bag_bucket_ATTLC(TYPE)* bp = b_it.first();

    while(
        ap && bp
    ){
        Listiter(Bag_pair(TYPE)) lia(((Bag_bucket_ATTLC(TYPE)*)ap)->collision_list);
        Listiter(Bag_pair(TYPE)) lib(((Bag_bucket_ATTLC(TYPE)*)bp)->collision_list);

        if(
            ap->hashval == bp->hashval
        ){
/*
**
**  The two hash values are equal; this means
**  the two collision lists may contain equal
**  values (which must be weeded out).
**
*/
            lib.reset();

            while(
                !lib.at_end()
            ){
                Bag_pair(TYPE)* btp;
                Bag_pair(TYPE)* atp;
                lib.next(btp);
                lia.reset();
                int found=0;

                while(
                    !lia.at_end()
                ){
                    lia.next(atp);

                    if(
                        atp->value == btp->value
                    ){
                        found=1;
                        break;
                    }
                }
                if(
                    found
                ){
		    int diff = atp->count - btp->count;

		    if(
			diff<0
		    ){
			diff = -diff;
		    }
                    insert(btp->value,diff);
                }else{
                    insert(btp->value,btp->count);
                }
            }
            lia.reset();

            while(
                !lia.at_end()
            ){
                Bag_pair(TYPE)* atp;
                Bag_pair(TYPE)* btp;
                lia.next(atp);
                lib.reset();
                int found=0;

                while(
                    !lib.at_end()
                ){
                    lib.next(btp);

                    if(
                        btp->value == atp->value
                    ){
                        found=1;
                        break;
                    }
                }
                if(
                    !found
                ){
                    insert(atp->value,atp->count);
                }
            }
            ap = a_it.next();
            bp = b_it.next();

        }else if(
            BAG_LT_ATTLC( ap->hashval,bp->hashval )
        ){
            lia.reset();

            while(
                !lia.at_end()
            ){
                Bag_pair(TYPE)* atp;
                lia.next(atp);
                insert(atp->value,atp->count);
            }
            ap = a_it.next();
        }else{
            lib.reset();

            while(
                !lib.at_end()
            ){
                Bag_pair(TYPE)* btp;
                lib.next(btp);
                insert(btp->value,btp->count);
            }
            bp = b_it.next();
        }
    }
/*
**
**  Insert the remaining values from ap Bag_buckets
**
*/
    while(
        ap
    ){
        Listiter(Bag_pair(TYPE)) lia(((Bag_bucket_ATTLC(TYPE)*)ap)->collision_list);

        while(
            !lia.at_end()
        ){
            Bag_pair(TYPE)* atp;
            lia.next(atp);
            insert(atp->value,atp->count);
        }
        ap = a_it.next();
    }
/*
**
**  Insert the remaining values from bp Bag_buckets
**
*/
    while(
        bp
    ){
        Listiter(Bag_pair(TYPE)) lib(((Bag_bucket_ATTLC(TYPE)*)bp)->collision_list);

        while(
            !lib.at_end()
        ){
            Bag_pair(TYPE)* btp;
            lib.next(btp);
            insert(btp->value,btp->count);
        }
        bp = b_it.next();
    }
}
PT_end

PT_define Bagout(TYPE)
ostream& operator<<(
    ostream& os,
    const Bag(TYPE)& b
){
    Bag_bucketiter_ATTLC(TYPE) bi(b);
    const Bag_bucket_ATTLC(TYPE)* bp = bi.first();
    os << "{";

    while(
	bp
    ){
	Listiter(Bag_pair(TYPE)) li(((Bag_bucket_ATTLC(TYPE)*)bp)->collision_list);

	while(
	    !li.at_end()
	){
	    Bag_pair(TYPE)* tp;
	    li.next(tp);
	    os 
		<< "("
		<< tp->count
		<< ","
		<< tp->value
		<< ")"
	    ;
	}
	bp = bi.next();
    }
    os << "}";
    return os;
}
PT_end

PT_define Bag_func_declare_ATTLC(TYPE)
class Bag_generator(TYPE) :

    public Gene_obj(CONST(TYPE))
{

    friend Bag(TYPE);

private:

    Bagiter(TYPE)         it;
    const Bag_pair(TYPE)* hold;
    unsigned              count;

    inline
    Bag_generator(TYPE)(const Bag(TYPE)& b);

public:
    CONST(TYPE)* operator()();
/*
**
**  The following was needed to eliminate an inline msg
**
*/
    ~Bag_generator(TYPE)();
};
Bag(TYPE)
Bag(TYPE)::select(Predicate(CONST(TYPE))& p)const{
    return Bag(TYPE)(p,*this,(Bag_select_ATTLC*)0);
}
Bag(TYPE)
Bag(TYPE)::select(Pred_obj(CONST(TYPE))& p)const{
    return Bag(TYPE)(p,*this,(Bag_select_ATTLC*)0);
}
Bag(TYPE)
Bag(TYPE)::reject(Predicate(CONST(TYPE))& p)const{
    return Bag(TYPE)(p,*this,(Bag_reject_ATTLC*)0);
}
Bag(TYPE)
Bag(TYPE)::reject(Pred_obj(CONST(TYPE))& p)const{
    return Bag(TYPE)(p,*this,(Bag_reject_ATTLC*)0);
}
Bag(TYPE)
Bag(TYPE)::map(Transformer(CONST(TYPE))& f)const{
    return Bag(TYPE)(f,*this,(Bag_map_ATTLC*)0);
}
Bag(TYPE)
Bag(TYPE)::map(Tran_obj(CONST(TYPE))& f)const{
    return Bag(TYPE)(f,*this,(Bag_map_ATTLC*)0);
}
Bag_generator(TYPE)::Bag_generator(TYPE)(
    const Bag(TYPE)& b
):
    it(b),
    count(0)
{ }
const TYPE* 
Bag_generator(TYPE)::operator()(){
    if(count==0){
	hold=it.next();
	if(hold==0)return 0;
	count=hold->count;
    }
    count--;
    return &(hold->value);
}
Bag_generator(TYPE)
Bag(TYPE)::generator()const{
    return Bag_generator(TYPE)(*this);
}
Bag_generator(TYPE)*
Bag(TYPE)::new_generator()const{
    return new Bag_generator(TYPE)(*this);
}
/*
**
**  Needed to eliminate an inline message
**
*/
Bag_generator(TYPE)::~Bag_generator(TYPE)(){
}
PT_end

PT_define Bagimplement(TYPE)
Bagimplement(TYPE,Set_zero_ATTLC)
PT_end

#endif
