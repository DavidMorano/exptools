#ifndef SETH
#define SETH
/*
**
**  To do:
**
**      o  See if Setiter(TYPE)::next() can be
**         simplified by using Bucketiter_ATTLC(TYPE)::
**         next() (e.g., in the section marked "find
**         the next leaf")
**
**      o  Uniquify all names that are not intended
**         for public consumption (and also so that
**         they won't collide with Set_of_p names)
**
**      o  Convert operator^= to use Bucketiter's
**
**      o  Make right parameter name consistent for
**         all operators (e.g., "oo")
**
*/

/*
**
**  The 32 bits of a Set_or_Bag_hashval are broken into
**  8 4-bit groups.  Each 4-bit group indexes
**  into a Internal_node of 16 Internal_items.
**  Prefix 'SET_' needed to avoid collision with
**  Set_of_p
**
*/
class ostream;
static const int SET_NODE_SIZE     = 16;
static const int SET_POSITIONS     = 8;
static const int SET_MASK_BITS     = 0XF;
static const int SET_INITIAL_SHIFT = 0;
static const int SET_SHIFT_INCR    = 4;

extern int SET_LT_ATTLC( Set_or_Bag_hashval a, Set_or_Bag_hashval b );

struct Space_info_ATTLC{
    int max_level;                 /* max depth of tree             */
    long node_count;               /* total nodes                   */
    long leaf_count;               /* total leaves                  */
    long overhead;		   /* size of data structure        */
    int leaves[SET_POSITIONS];     /* leaves at each level          */
    int occupancy[SET_POSITIONS];  /* non-null items at each level  */
};
/*
**
**  Index to non-parametric classes:
**
*/
    class Set_bucket_non_param_ATTLC;
    class Internal_item_ATTLC;
    class Internal_node_ATTLC;
    class Position_ATTLC;
/*
**
**  The following ATTLC class declarations are
**  needed to disambiguate the copy-avoidance
**  constructors:
**
*/
class Set_select_ATTLC;
class Set_reject_ATTLC;
class Set_map_ATTLC;
class Set_union_ATTLC;
class Set_inter_ATTLC;
class Set_diff_ATTLC;
class Set_xor_ATTLC;

extern Pool* internal_node_pool_ptr_ATTLC;

struct Set_bucket_non_param_ATTLC{
    Set_or_Bag_hashval hashval;
};
struct Internal_item_ATTLC{
/*
**  An Internal_item is a single "slot" in an
**  Internal_node.  It may contain:
**
**      o  An Internal_node*
**      o  A Set_bucket_non_param_ATTLC*
**      o  NULL
**
**  Set_bucket_non_param_ATTLC* and Internal_node* pointers 
**  can't be byte-aligned, so the low order bit is free to
**  be used as the union discriminant.
**
**   o  When the low-order bit is 1, the item
**      is a Set_bucket_non_param_ATTLC*
**
**   o  When the low order bit is 0, the item
**      is a Internal_node* or NULL.
*/
    union{
        void*                 ext_leaf;
        Internal_node_ATTLC*  nodep;
        long                  this_is_leaf;
    };
    inline int is_leaf_or_null()const;

#ifndef FAST

    int
    is_node()const;

    int
    is_leaf()const;

    int
    is_null()const;

    Internal_node_ATTLC*
    next_node()const;

    void*
    external_leaf()const;

    void
    make_leaf(void*);

    void
    make_node(Internal_node_ATTLC*);

    void
    make_null();

#else

    inline int
    is_node()const;

    inline int
    is_leaf()const;

    inline int
    is_null()const;

    inline Internal_node_ATTLC*
    next_node()const;

    inline void*
    external_leaf()const;

    inline void
    make_leaf(void*);

    inline void
    make_node(Internal_node_ATTLC*);

    inline void
    make_null();

#endif

    void
    show(int level)const;

    void
    space(int level,Space_info_ATTLC& result)const;

};
struct Internal_node_ATTLC{
/*
**  A Internal_node has SET_NODE_SIZE Internal_items
**  plus a count of how many of these are in use.
**  Each Internal_item is directly indexed
**  by a lg(SET_NODE_SIZE) chunk.
*/

    Internal_item_ATTLC item[SET_NODE_SIZE];
    int                 busy_count;

    Internal_node_ATTLC();

    inline
    ~Internal_node_ATTLC();

    inline void*
    operator new(size_t i);

    inline void
    operator delete(void* p, size_t i);

    void
    show(int level)const;

    void
    space(int level,Space_info_ATTLC& result)const;

};
struct Position_ATTLC{
/*
**  A Position caches the result of the most
**  recent search, down to the level of the
**  Bucket:
**
**      o  curr_value is the Set_or_Bag_hashval that we
**         searched for
**
**      o  curr_pos is a stack of pointers to
**         Internal_items which remembers a
**         path of Internal_items through the
**         index:
**
**         o  curr_pos[0] points to the Internal_item
**            selected by the first 4 bit chunk
**
**         o  curr_pos[1] points to the Internal_item
**            selected by the second 4 bit chunk
**
**         o  curr_pos[curr_depth] points to the
**            Internal_item which points to
**            a Bucket_ATTLC(TYPE)
**
**  If set mutation occurs, a Position is
**  canceled by setting its curr_depth to -1;
**  curr_value can be used subsequently to rebuild
**  the cur_pos stack so that iteration can resume
**
*/
    Internal_item_ATTLC*      curr_pos[SET_POSITIONS];
    int                       curr_depth;
    Set_or_Bag_hashval        curr_value;

    inline
    Position_ATTLC();

    void
    show()const;
};
/*
**
**  Internal_item inlines
**
*/

#ifdef FAST

int
Internal_item_ATTLC::is_leaf_or_null()const{
    return this_is_leaf & 01;
}
int
Internal_item_ATTLC::is_node()const{
    return (
        !is_leaf_or_null() &&
        nodep
    );
}
int
Internal_item_ATTLC::is_leaf()const{
    return (
        is_leaf_or_null() &&
        ((long)ext_leaf & ~(long)01)
    );
}
int
Internal_item_ATTLC::is_null()const{
    return !nodep;
}
Internal_node_ATTLC*
Internal_item_ATTLC::next_node()const{

#ifdef DEBUG

    assert(is_node());

#endif

    return nodep;
}
void*
Internal_item_ATTLC::external_leaf()const{

#ifdef DEBUG

    assert(is_leaf());

#endif

    return (void*)((long)ext_leaf & ~(long)01);
}
void
Internal_item_ATTLC::make_leaf(void* p){

#ifdef DEBUG

    assert(((long)p & 01) == 0);

#endif

    ext_leaf = (void*)((long)p | 01);
}
void
Internal_item_ATTLC::make_node(Internal_node_ATTLC* cp){

#ifdef DEBUG

    assert(((long)cp & 01) == 0);

#endif

    nodep = cp;
}
void
Internal_item_ATTLC::make_null(){
    nodep = 0;
}

#endif
/*
**
**  Internal_node inlines
**
*/
void
Internal_node_ATTLC::operator delete(void* p, size_t i){

    if(
        i == sizeof(Internal_node_ATTLC)
    ){
        internal_node_pool_ptr_ATTLC->free(p);
    }else{
        delete (char*)p;
    }
}
void*
Internal_node_ATTLC::operator new(size_t i){
    return (
        i == sizeof(Internal_node_ATTLC) ?(
            internal_node_pool_ptr_ATTLC->alloc()
        ):(
            new char[i]
        )
    );
}
Internal_node_ATTLC::~Internal_node_ATTLC(){
}
/*
**
**  Position inlines
**
*/
Position_ATTLC::Position_ATTLC():
    curr_depth(-1),
    curr_value(0)       /*  probably not needed */
{ }
/*
**
**  Preparation for parameterization
**
*/
PT_names
	Bucket_ATTLC(T)           T _Bucket_ATTLC
	Set_initializer_ATTLC(T)  T _Set_initializer_ATTLC
	set_initializer_ATTLC(T)  T _set_initializer_ATTLC
	Bucketiter_ATTLC(T)       T _Bucketiter_ATTLC
	Setiter(T)                T _Setiter
	Set(T)                    T _Set
	Set_generator(T)          T _Set_generator
PT_end



PT_define Setdeclare(TYPE)
Set_or_Bagdeclare_ATTLC(TYPE)
Listdeclare(TYPE)
/*
**
**  INDEX TO CLASSES DEFINED BY THIS MACRO
**
*/
class Set_initializer_ATTLC(TYPE);
class Bucket_ATTLC(TYPE);
class Bucketiter_ATTLC(TYPE);
/*
**
**  The following classes are for public consumption:
**
*/
class Setiter(TYPE);
class Set_generator(TYPE);
class Set(TYPE);

class Set_initializer_ATTLC(TYPE){

    static int count;

public:

    Set_initializer_ATTLC(TYPE)();
    ~Set_initializer_ATTLC(TYPE)();
};
static Set_initializer_ATTLC(TYPE) set_initializer_ATTLC(TYPE);
/*
**  Each leaf item in the tree-structured index
**  points to a pair of values:
**
**      o  'hashval' is the hash key
**      o  'collision_list' is a list of values which
**         hash to hashval
**
**  Note that ALIGN values in the original version
**  become Bucket_ATTLC(TYPE)* values in this version.
**
*/
struct Bucket_ATTLC(TYPE) : public Set_bucket_non_param_ATTLC{

    List(TYPE)   collision_list;

    void
    show()const;
};
class Bucketiter_ATTLC(TYPE){
    friend class Set(TYPE);
protected:
    Set(TYPE) *const my_set;
    Bucketiter_ATTLC(TYPE)* next_it;
    Position_ATTLC pos;
public:
    Bucketiter_ATTLC(TYPE)(const Set(TYPE)& s);
    ~Bucketiter_ATTLC(TYPE)();

    const Bucket_ATTLC(TYPE)*
    first();

    const Bucket_ATTLC(TYPE)*
    next();

    inline void
    clobber();
};
/*
**
**  This class must be modified to use
**  Bucketiter_ATTLC(TYPE)(*this).first() and next().
**
*/
class Setiter(TYPE):

    public Bucketiter_ATTLC(TYPE)
{
private:

    int inited;           /* new */
    Listiter(TYPE)* itp;

public:

    inline
    Setiter(TYPE)(const Set(TYPE)& s);

    const TYPE*
    first();              /* undocumented - TBD_make private */

    const TYPE*
    next();               /* subsumes first, next */

    inline void
    reset();              /* new semantics */

    inline const Set(TYPE)*
    the_set() const;      /* new */
};

class Pred_obj(CONST(TYPE));
class Tran_obj(CONST(TYPE));
class Gene_obj(CONST(TYPE));
class Proc_obj(CONST(TYPE));

class Set(TYPE){

    friend class Bucketiter_ATTLC(TYPE);
    friend class Setiter(TYPE);

private:

    Internal_item_ATTLC contents;
    int                 sze;
    Bucketiter_ATTLC(TYPE)*   iter_head; /* was Setiter(TYPE) */
    Position_ATTLC      pos;       /* was Position(TYPE) */
/*
**
**  The following are only used on empty sets
**
*/
    void
    make_select(
        Predicate(CONST(TYPE))& p,
        const Set(TYPE)& s
    );
    void
    make_reject(
        Predicate(CONST(TYPE))& p,
        const Set(TYPE)& s
    );
    void
    make_map(
        Transformer(CONST(TYPE))& f,
        const Set(TYPE)& s
    );
    void
    make_union(
        const Set(TYPE)& a,
        const Set(TYPE)& b
    );
    void
    make_intersection(
        const Set(TYPE)& a,
        const Set(TYPE)& b
    );
    void
    make_difference(
        const Set(TYPE)& a,
        const Set(TYPE)& b
    );
    void
    make_xor(
        const Set(TYPE)& a ,
        const Set(TYPE)& b
    );
    void
    make_select(
        Pred_obj(CONST(TYPE))& p,
        const Set(TYPE)& s
    );
    void
    make_reject(
        Pred_obj(CONST(TYPE))& p,
        const Set(TYPE)& s
    );
    void
    make_map(
        Tran_obj(CONST(TYPE))& f,
        const Set(TYPE)& s
    );
    /* was inline */
    Set(TYPE)(
        Predicate(CONST(TYPE))& f,
        const Set(TYPE)& s,
        Set_select_ATTLC*
    );
    /* was inline */
    Set(TYPE)(
        Pred_obj(CONST(TYPE))& f,
        const Set(TYPE)& s,
        Set_select_ATTLC*
    );
    /* was inline */
    Set(TYPE)(
        Predicate(CONST(TYPE))& f,
        const Set(TYPE)&  s,
        Set_reject_ATTLC*
    );
    /* was inline */
    Set(TYPE)(
        Pred_obj(CONST(TYPE))& f,
        const Set(TYPE)&  s,
        Set_reject_ATTLC*
    );
    /* was inline */
    Set(TYPE)(
        Transformer(CONST(TYPE))& f,
        const Set(TYPE)&  s,
        Set_map_ATTLC*
    );
    /* was inline */
    Set(TYPE)(
        Tran_obj(CONST(TYPE))& f,
        const Set(TYPE)&  s,
        Set_map_ATTLC*
    );
    /* was inline */
    Set(TYPE)(
        const Set(TYPE)& a,
        const Set(TYPE)& b,
        Set_union_ATTLC* x
    );
    /* was inline */
    Set(TYPE)(
        const Set(TYPE)& a,
        const Set(TYPE)& b,
        Set_inter_ATTLC*
    );
    /* was inline */
    Set(TYPE)(
        const Set(TYPE)& a,
        const Set(TYPE)& b,
        Set_diff_ATTLC*
    );
    /* was inline */
    Set(TYPE)(
        const Set(TYPE)& a,
        const Set(TYPE)& b,
        Set_xor_ATTLC*
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
    Set(TYPE)();

    /* was inline */
    Set(TYPE)(const TYPE& t0);

    /* was inline */
    Set(TYPE)(
        const TYPE& t0,
        const TYPE& t1
    );
    /* was inline */
    Set(TYPE)(
        const TYPE& t0,
        const TYPE& t1,
        const TYPE& t2
    );
    /* was inline */
    Set(TYPE)(
        const TYPE& t0,
        const TYPE& t1,
        const TYPE& t2,
        const TYPE& t3
    );

    Set(TYPE)(const Set(TYPE)& s);

    Set(TYPE)(Generator(CONST(TYPE))&);

    Set(TYPE)(Gene_obj(CONST(TYPE))& g);

    ~Set(TYPE)();
/*
**
**  Size
**
*/
    inline int
    size()const;

    inline int
    size_unique()const;

    inline
    operator const void*()const;
/*
**
**  Assignment
**
*/
    Set(TYPE)& operator=(const Set(TYPE)& s);
/*
**
**  Relations
**
*/
    int
    operator==(const Set(TYPE)& s)const;

    inline int
    operator!=(const Set(TYPE)& s)const;

    int
    operator<=(const Set(TYPE)& s)const;

    int
    operator<(const Set(TYPE)& s)const;

    inline int
    operator>=(const Set(TYPE)& s)const;

    inline int
    operator>(const Set(TYPE)& s)const;
/*
**
**  Membership
**
*/
    const TYPE*
    contains(const TYPE& t)const;

    inline unsigned int
    count(const TYPE& t)const;
/*
**
**  Insert and Remove elements
**
*/
    const TYPE*                        /* jfi */
    insert(const TYPE& t,unsigned count=1);

    unsigned
    remove(const TYPE& t,unsigned count=1);

    inline unsigned
    remove_all(const TYPE& t);

    unsigned 
    remove_all();
/*
**
**  Select an arbitrary element
**
*/
    const TYPE*
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
**  Set algebra
**
*/
    inline Set(TYPE)
    operator|(const Set(TYPE)& s)const;

    inline Set(TYPE)
    operator-(const Set(TYPE)& s)const;

    inline Set(TYPE)
    operator&(const Set(TYPE)& s)const;

    inline Set(TYPE)
    operator^(const Set(TYPE)& s)const;

    Set(TYPE)&
    operator|=(const Set(TYPE)& s);

    Set(TYPE)&
    operator-=(const Set(TYPE)& s);

    Set(TYPE)&
    operator&=(const Set(TYPE)& s);

    Set(TYPE)&
    operator^=(const Set(TYPE)& s);
/*
**
**  Set-valued functions
**
*/
    inline Set(TYPE)
    select(Predicate(CONST(TYPE))& p)const;

    inline Set(TYPE)
    select(Pred_obj(CONST(TYPE))& p)const;

    inline Set(TYPE)
    reject(Predicate(CONST(TYPE))& p)const;

    inline Set(TYPE)
    reject(Pred_obj(CONST(TYPE))& p)const;

    inline Set(TYPE)
    map(Transformer(CONST(TYPE))& f)const;

    inline Set(TYPE)
    map(Tran_obj(CONST(TYPE))& f)const;

    inline Set_generator(TYPE)
    generator()const;

    inline Set_generator(TYPE)*
    new_generator()const;
/*
**
**  Performance tuning
**
*/
    void histogram(Map(Set_or_Bag_hashval,unsigned)& m)const;
/*
**
**  Debugging, performance tuning
**
*/
    void
    check()const;

    void
    show()const;

    Space_info_ATTLC
    space()const;

};
ostream& operator<<(
    ostream& os,
    const Set(TYPE)& s
);
/*
**
**  Bucketiter_ATTLC(TYPE) inlines
**
*/
void
Bucketiter_ATTLC(TYPE)::clobber(){
    pos.curr_depth = -1;
}
/*
**
**  Setiter(TYPE) inlines
**
*/
Setiter(TYPE)::Setiter(TYPE)(
    const Set(TYPE)& s
):
    Bucketiter_ATTLC(TYPE)(s),
    inited(0),
    itp(0)
{ }
void
Setiter(TYPE)::reset(){
    inited=0;
}
const Set(TYPE)*
Setiter(TYPE)::the_set() const{
    return my_set;
}
/*
**
**  Set(TYPE) inlines
**
*/
Set(TYPE)::Set(TYPE)(
):
    sze(0),
    iter_head(0)
{
    pos.curr_depth = -1;
    contents.make_null();
}
int
Set(TYPE)::size()const{
    return sze;
}
inline int
Set(TYPE)::size_unique()const{
    return sze;
}
Set(TYPE)::operator const void*()const{
    return (
        size() ?(
            this
        ):(
            0
        )
    );
}
int
Set(TYPE)::operator!=(const Set(TYPE)& s)const{
    return !(*this == s);
}
int
Set(TYPE)::operator>=(const Set(TYPE)& s)const{
    return s <= *this;
}
int
Set(TYPE)::operator>(const Set(TYPE)& s)const{
    return s < *this;
}
Set(TYPE)
Set(TYPE)::operator|(const Set(TYPE)& s)const{
    return Set(TYPE)(*this,s,(Set_union_ATTLC*)0);
}
Set(TYPE)
Set(TYPE)::operator-(const Set(TYPE)& s)const{
    return Set(TYPE)(*this, s,(Set_diff_ATTLC*)0);
}
Set(TYPE)
Set(TYPE)::operator&(const Set(TYPE)& s)const{
    return Set(TYPE)(*this,s,(Set_inter_ATTLC*)0);
}
Set(TYPE)
Set(TYPE)::operator^(const Set(TYPE)& s)const{
    return Set(TYPE)(*this,s,(Set_xor_ATTLC*)0);
}
unsigned int
Set(TYPE)::count(const TYPE& t)const{
    return contains(t)?1:0;
}
unsigned
Set(TYPE)::remove_all(const TYPE& t){
    return remove(t);
}
PT_end

PT_define Setdebug(TYPE)
void Bucket_ATTLC(TYPE)::show()const{
    cout << "    hashval=" << hashval << "\n";
    cout << "    collision_list=";
    Listiter(TYPE) it(collision_list);
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
        cout << it.next();
    }
    cout << ">\n";
}
static void showiter(Listiter(TYPE)* itp){
    TYPE e;

    if(
        itp
    ){
        if(
            itp->peek_prev(e)
        ){
            cout << e;
        }else{
            cout << "*";
        }
        if(
            itp->peek_next(e)
        ){
            cout << e;
        }else{
            cout << "*";
        }
        cout << ">\n";
    }else{
        cout << "0";
    }
}
void
Set(TYPE)::show()const{
    cout << "sze = " << sze << "\n";
    cout << "pos =\n";
    pos.show();
    cerr << "contents =\n";
    contents.show(0);
}
Space_info_ATTLC
Set(TYPE)::space()const{
/*
**
**  contents is level 0; the first node is level 1, etc.
**
*/
    Space_info_ATTLC result;
    result.max_level = -1;
    result.node_count = 0;
    result.leaf_count = 0;

    if(!contents.is_null()){

	for(int i=0;i<SET_POSITIONS;i++){
	    result.leaves[i] = 0;
	    result.occupancy[i] = 0;
        }
	result.occupancy[0] = 1;
	contents.space(0,result);
    }
    result.overhead = (
	sizeof(Internal_item_ATTLC) +
        result.node_count * sizeof(Internal_node_ATTLC)
    );
    return result;
}
PT_end


PT_define Setimplement(TYPE,H)
Set_or_Bagimplement_ATTLC(TYPE)
Set_func_declare_ATTLC(TYPE)
#ifndef BUILDING_LIBRARY
Listimplement(TYPE)
#endif
/*
**
**  TYPE is the type parameter;
**  H is the name of the hash function
**  (Set_zero_ATTLC should be used if the client does
**  not have an explicit function).
**
*/
Set_initializer_ATTLC(TYPE)::Set_initializer_ATTLC(TYPE)(){
/*
**
**  Pools could be used for Buckets too
**
*/
    if(
        count++ == 0
    ){
        internal_node_pool_ptr_ATTLC = (
            new Pool(sizeof(Internal_node_ATTLC))
        );
    }
}
Set_initializer_ATTLC(TYPE)::~Set_initializer_ATTLC(TYPE)(){

    if(
        --count == 0
    ){
        delete internal_node_pool_ptr_ATTLC;
    }
}
Bucketiter_ATTLC(TYPE)::~Bucketiter_ATTLC(TYPE)(){

    if(
        my_set == 0
    ){
        return;
    }
    if(
        this == my_set->iter_head
    ){
/*
**
**  Case 1: iterator at head of chain
**
*/
        my_set->iter_head = next_it;

    }else{
/*
**
**  Case 2: iterator in middle of chain
**
*/
        register Bucketiter_ATTLC(TYPE)* x;

        for(
            register Bucketiter_ATTLC(TYPE)* an_it=my_set->iter_head;
            (x = an_it->next_it) != this;
            an_it = x
        );
        an_it->next_it = next_it;
    }
}
Bucketiter_ATTLC(TYPE)::Bucketiter_ATTLC(TYPE)(
    const Set(TYPE)& s
):
    my_set(&s),
    next_it(s.iter_head)
{ 
    ((Set(TYPE)*)(&s))->iter_head = this;
}
/*
**
**  first() and next() are similar to Shopiro's original
**  pset iterator functions  first() and next(); they
**  walk the leaves of the tree, returning Bucket(T))*.
**
*/
const Bucket_ATTLC(TYPE)*
Bucketiter_ATTLC(TYPE)::first() {
    register Internal_item_ATTLC* itemp;
    register Internal_node_ATTLC* nodep;
    Bucket_ATTLC(TYPE)* bp;

    if(
        my_set == 0
    ){
        return 0;
    }
    pos.curr_depth = -1;

    if(
        my_set->contents.is_null()
    ){
        return 0;
    }
    if(
        my_set->contents.is_leaf()
    ){
/*
**
**  'contents' is a Bucket_ATTLC(TYPE)*
**
*/
        bp = (Bucket_ATTLC(TYPE)*)my_set->contents.external_leaf();

    }else{
/*
**
**  'contents' is an Internal_node*.  Search the
**  subtree rooted at this node looking for the
**  leftmost leaf.
**
*/
        nodep = my_set->contents.next_node();

        for(;;){
            assert(pos.curr_depth < SET_POSITIONS);
/*
**
**  Scan this Internal_node from left to right looking
**  for a non-null Internal_item
**
*/
            for(
                itemp = &nodep->item[0];
                ;
                itemp++
            ){
                assert(itemp < &nodep->item[SET_NODE_SIZE]);

                if(
                    !itemp->is_null()
                ){
                    break;
                }
            }
            pos.curr_pos[++pos.curr_depth] = itemp;
/*
**
**  If this Internal_item is a leaf, the search is over;
**  otherwise, iteratively 'recurse'
**
*/
            if(
                itemp->is_leaf()
            ){
                break;
            }
            nodep = itemp->next_node();
        }
        bp = (Bucket_ATTLC(TYPE)*)itemp->external_leaf();
    }
/*
**
**  bp now points to a Bucket_ATTLC(TYPE)
**
*/
    pos.curr_value = bp->hashval;     /* jfi */
    return bp;
}
const Bucket_ATTLC(TYPE)*
Bucketiter_ATTLC(TYPE)::next(){
    register Internal_item_ATTLC* itemp;
    register Internal_node_ATTLC* nodep;
    register Bucket_ATTLC(TYPE)* bp;

    if(
        my_set == 0
    ){
        return 0;
    }
/*
**
**  Search the index for pos.curr_value.  Since
**  pos caches the result of the last iterator
**  access, the loop should exit almost immediately,
**  unless set mutation has occurred since the last
**  access.
**
*/
    itemp = (
        pos.curr_depth == -1 ?(
            &my_set->contents
        ):(
            pos.curr_pos[pos.curr_depth]
        )

    );
    int unshift = (
        SET_INITIAL_SHIFT +
        SET_SHIFT_INCR +
        pos.curr_depth * SET_SHIFT_INCR
    );
    register long mask = SET_MASK_BITS << unshift;
    nodep = 0;

    for(
        ;
        ;
        mask <<= SET_SHIFT_INCR, unshift += SET_SHIFT_INCR
    ){
        assert(pos.curr_depth < SET_POSITIONS);

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
**  the current value, depending on whether the Bucket
**  containing the current value has been deleted or not.
**
*/
            bp = (Bucket_ATTLC(TYPE)*)itemp->external_leaf();
            Set_or_Bag_hashval hval = bp->hashval;

            if(
                hval == pos.curr_value ||
                SET_LT_ATTLC(hval,pos.curr_value)
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
**  The leaf points to a Bucket containing a hash value
**  GREATER THAN the current value, so the current value
**  must have been deleted.  The Bucket pointed to is,
**  by definition, the "next" Bucket, the one we are
**  looking for.
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
**  to locate the NEXT Bucket_ATTLC(TYPE) starting from here.
**
*/
    if(
        pos.curr_depth == -1
    ){
/*
**
**  There was only one hash Bucket; the iteration
**  is therefore terminated.
**
*/
        return 0;
    }
/*
**
**  Find the next Bucket_ATTLC(TYPE)
**
*/
    if(
        nodep == 0
    ){
        nodep = (
            pos.curr_depth == 0 ?(
                my_set->contents.next_node()
            ):(
                pos.curr_pos[pos.curr_depth-1]->next_node()
            )
        );
    }
    for( ;; ){
        assert(&nodep->item[0] <= itemp  &&  itemp < &nodep->item[SET_NODE_SIZE]);
/*
**
**  Scan rightward within this node, looking for a
**  non-null item
**
*/
        while(
            itemp < &nodep->item[SET_NODE_SIZE-1]
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
**  The set is exhausted, so the iteration is terminated
**
*/
            return 0;
        }
        itemp = pos.curr_pos[pos.curr_depth];
        nodep = (
            pos.curr_depth == 0 ?(
                my_set->contents.next_node()
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
            assert(itemp < &nodep->item[SET_NODE_SIZE]);

            if(
                !itemp->is_null()
            ){
                break;
            }
        }
        pos.curr_pos[++pos.curr_depth] = itemp;
    }
    bp = (Bucket_ATTLC(TYPE)*)itemp->external_leaf();
    pos.curr_value = bp->hashval;
    return bp;
}
const TYPE*
Setiter(TYPE)::first(){
/*
**
**  This version has been simplified by using
**  Bucketiter::first()
**
*/
    const Bucket_ATTLC(TYPE)* bp = ((Bucketiter_ATTLC(TYPE)*)this)->first();

    if( bp == 0 ){
        return 0;
    }
    delete itp;
    itp=new Listiter(TYPE)(((Bucket_ATTLC(TYPE)*)bp)->collision_list);
    TYPE* result;
    itp->next(result);
/*
**
**  Cast the pointer to const so the client can't
**  modify the element
**
*/
    return (const TYPE*)result;
}
const TYPE*
Setiter(TYPE)::next(){
    register Internal_item_ATTLC* itemp;
    register Internal_node_ATTLC* nodep;
    register Bucket_ATTLC(TYPE)* bp;
/*
**
**  TBD_see if this code can be simplified by using
**  Bucketiter_ATTLC(TYPE)::next()
**
*/
    if(
        my_set == 0
    ){
        return 0;
    }
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
            &my_set->contents
        ):(
            pos.curr_pos[pos.curr_depth]
        )

    );
    int unshift = (
        SET_INITIAL_SHIFT +
        SET_SHIFT_INCR +
        pos.curr_depth * SET_SHIFT_INCR
    );
    register long mask = SET_MASK_BITS << unshift;
    nodep = 0;

    for(
        ;
        ;
        mask <<= SET_SHIFT_INCR, unshift += SET_SHIFT_INCR
    ){
        assert(pos.curr_depth < SET_POSITIONS);

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
**  the current value, depending on whether the Bucket
**  containing the current value has been deleted or not.
**
*/
            bp = (Bucket_ATTLC(TYPE)*)itemp->external_leaf();
            Set_or_Bag_hashval hval = bp->hashval;

            if(
                hval == pos.curr_value ||
                SET_LT_ATTLC(hval,pos.curr_value)
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
**  The leaf we have found points to a Bucket containing
**  a next GREATER THAN the current value (the current
**  value must have been deleted).
**
*/
                pos.curr_value = hval;
                delete itp;
                itp = new Listiter(TYPE)(((Bucket_ATTLC(TYPE)*)bp)->collision_list);
                TYPE* result;
                itp->next(result);
                return (const TYPE*)result;
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
**  There is only one hash Bucket; if we have not
**  not yet returned all values on the collision list,
**  return the next one; otherwise, the iteration
**  is terminated
**
**  TBD_note:  It is possible that Set mutation occurred
**  that (1) deleted all the elements in a List and then
**  (2) re-created a List with the same hash value.  In
**  this case, *itp refers to a non-existeng List.  We
**  must guard against this case by using Listiter::TBD
**  which returns a pointer to TheList.
**
**
*/
        if(
            itp->at_end()
        ){
            return 0;
        }else{
            TYPE* result;
            itp->next(result);
            return (const TYPE*)result;
        }
    }
    if(
        itemp->is_leaf() &&
        ((Bucket_ATTLC(TYPE)*)itemp->external_leaf())->hashval == pos.curr_value &&
        !itp->at_end()
    ){
/*
**
**  There are still values on the collision list in
**  the current Bucket
**
*/
        TYPE* result;
        itp->next(result);
        return (const TYPE*)result;

    }else{
/*
**
**  Find the next leaf.
**  TBD_can we use Bucketiter_ATTLC(TYPE)::next() here?
**
*/
        if(
            nodep == 0
        ){
            nodep = (
                pos.curr_depth == 0 ?(
                    my_set->contents.next_node()
                ):(
                    pos.curr_pos[pos.curr_depth-1]->next_node()
                )
            );
        }
        for( ;; ){
            assert(&nodep->item[0] <= itemp  &&  itemp < &nodep->item[SET_NODE_SIZE]);
/*
**
**  Scan rightward within this node, looking for a
**  non-null item
**
*/
            while(
                itemp < &nodep->item[SET_NODE_SIZE-1]
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
**  The set is exhausted, so the iteration is terminated
**
*/
                return 0;
            }
            itemp = pos.curr_pos[pos.curr_depth];
            nodep = (
                pos.curr_depth == 0 ?(
                    my_set->contents.next_node()
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
                assert(itemp < &nodep->item[SET_NODE_SIZE]);

                if(
                    !itemp->is_null()
                ){
                    break;
                }
            }
            pos.curr_pos[++pos.curr_depth] = itemp;
        }
    }
    bp = (Bucket_ATTLC(TYPE)*)itemp->external_leaf();
    pos.curr_value = bp->hashval;
    delete itp;
    itp = new Listiter(TYPE)(((Bucket_ATTLC(TYPE)*)bp)->collision_list);
    TYPE* result;
    itp->next(result);
    return (const TYPE*)result;
}
/*
**
**  The following was needed to remove an inline msg
**
*/
Set_generator(TYPE)::~Set_generator(TYPE)(){
}
CONST(TYPE)*
Set_generator(TYPE)::operator()(){
    return (CONST(TYPE)*)(it.next());
}
Set(TYPE)::Set(TYPE)(
    const TYPE& t0
):
    sze(0),
    iter_head(0)
{
    pos.curr_depth = -1;
    contents.make_null();
    insert(t0);
}

Set(TYPE)::Set(TYPE)(
    const TYPE& t0,
    const TYPE& t1
):
    sze(0),
    iter_head(0)
{
    pos.curr_depth = -1;
    contents.make_null();
    insert(t0);
    insert(t1);
}
Set(TYPE)::Set(TYPE)(
    const TYPE& t0,
    const TYPE& t1,
    const TYPE& t2
):
    sze(0),
    iter_head(0)
{
    pos.curr_depth = -1;
    contents.make_null();
    insert(t0);
    insert(t1);
    insert(t2);
}
Set(TYPE)::Set(TYPE)(
    const TYPE& t0,
    const TYPE& t1,
    const TYPE& t2,
    const TYPE& t3
):
    sze(0),
    iter_head(0)
{
    pos.curr_depth = -1;
    contents.make_null();
    insert(t0);
    insert(t1);
    insert(t2);
    insert(t3);
}
Set(TYPE)::Set(TYPE)(
    Predicate(CONST(TYPE))& f,
    const Set(TYPE)& s,
    Set_select_ATTLC*
):
    sze(0),
    iter_head(0)
{
    pos.curr_depth = -1;
    contents.make_null();
    make_select(f,s);
}
Set(TYPE)::Set(TYPE)(
    Pred_obj(CONST(TYPE))& f,
    const Set(TYPE)& s,
    Set_select_ATTLC*
):
    sze(0),
    iter_head(0)
{
    pos.curr_depth = -1;
    contents.make_null();
    make_select(f,s);
}
Set(TYPE)::Set(TYPE)(
    Predicate(CONST(TYPE))& f,
    const Set(TYPE)& s,
    Set_reject_ATTLC*
):
    sze(0),
    iter_head(0)
{
    pos.curr_depth = -1;
    contents.make_null();
    make_reject(f,s);
}
Set(TYPE)::Set(TYPE)(
    Pred_obj(CONST(TYPE))& f,
    const Set(TYPE)& s,
    Set_reject_ATTLC*
):
    sze(0),
    iter_head(0)
{
    pos.curr_depth = -1;
    contents.make_null();
    make_reject(f,s);
}
Set(TYPE)::Set(TYPE)(
    Transformer(CONST(TYPE))& f,
    const Set(TYPE)& s,
    Set_map_ATTLC*
):
    sze(0),
    iter_head(0)
{
    pos.curr_depth = -1;
    contents.make_null();
    make_map(f,s);
}
Set(TYPE)::Set(TYPE)(
    Tran_obj(CONST(TYPE))& f,
    const Set(TYPE)& s,
    Set_map_ATTLC*
):
    sze(0),
    iter_head(0)
{
    pos.curr_depth = -1;
    contents.make_null();
    make_map(f,s);
}
Set(TYPE)::Set(TYPE)(
    const Set(TYPE)& a,
    const Set(TYPE)& b,
    Set_union_ATTLC*
):
    sze(0),
    iter_head(0)
{
    pos.curr_depth = -1;
    contents.make_null();
    make_union(a,b);
}
Set(TYPE)::Set(TYPE)(
    const Set(TYPE)& a,
    const Set(TYPE)& b,
    Set_inter_ATTLC*
):
    sze(0),
    iter_head(0)
{
    pos.curr_depth = -1;
    contents.make_null();
    make_intersection(a, b);
}
Set(TYPE)::Set(TYPE)(
    const Set(TYPE)& a,
    const Set(TYPE)& b,
    Set_diff_ATTLC*
):
    sze(0),
    iter_head(0)
{
    pos.curr_depth = -1;
    contents.make_null();
    make_difference(a, b);
}
Set(TYPE)::Set(TYPE)(
    const Set(TYPE)& a,
    const Set(TYPE)& b,
    Set_xor_ATTLC*
):
    sze(0),
    iter_head(0)
{
    pos.curr_depth = -1;
    contents.make_null();
    make_xor(a,b);
}
Set(TYPE)::Set(TYPE)(
    Generator(CONST(TYPE))& f
):
    sze(0),
    iter_head(0)
{
    const TYPE* tp;
    contents.make_null();

    while(
        tp = f()
    ){
        insert(*tp);
    }
}
Set(TYPE)::Set(TYPE)(
    Gene_obj(CONST(TYPE))& f
){
    const TYPE* tp;

    while(
        tp = f()
    ){
        insert(*tp);
    }
}
void
Set(TYPE)::make_select(
    Pred_obj(CONST(TYPE))& f,
    const Set(TYPE)& a
){
    assert(sze==0);
    Bucketiter_ATTLC(TYPE) bi(a);
    const Bucket_ATTLC(TYPE)* bp = bi.first();

    while(
        bp
    ){
	Listiter(TYPE) li(((Bucket_ATTLC(TYPE)*)bp)->collision_list);

	while(
	    !li.at_end()
	){
            TYPE* tp;
	    li.next(tp);

	    if(
		f(tp)
	    ){
		insert(*tp);
	    }
	}
	bp = bi.next();
    }
}
void
Set(TYPE)::make_reject(
    Pred_obj(CONST(TYPE))& f,
    const Set(TYPE)& a
){
    assert(sze==0);
    Bucketiter_ATTLC(TYPE) bi(a);
    const Bucket_ATTLC(TYPE)* bp = bi.first();

    while(
        bp
    ){
	Listiter(TYPE) li(((Bucket_ATTLC(TYPE)*)bp)->collision_list);

	while(
	    !li.at_end()
	){
            TYPE* tp;
	    li.next(tp);

	    if(
		!f(tp)
	    ){
		insert(*tp);
	    }
	}
	bp = bi.next();
    }
}
void
Set(TYPE)::make_map(
    Tran_obj(CONST(TYPE))& f,
    const Set(TYPE)& a
){
    assert(sze==0);
    Bucketiter_ATTLC(TYPE) bi(a);
    const Bucket_ATTLC(TYPE)* bp = bi.first();

    while(
        bp
    ){
	Listiter(TYPE) li(((Bucket_ATTLC(TYPE)*)bp)->collision_list);

	while(
	    !li.at_end()
	){
            TYPE* tp;
	    li.next(tp);
	    insert(*f(tp));
	}
	bp = bi.next();
    }
}
void
Set(TYPE)::do_each(Proc_obj(CONST(TYPE))& f)const{
    Bucketiter_ATTLC(TYPE) bi(*this);
    const Bucket_ATTLC(TYPE)* bp = bi.first();

    while(
	bp
    ){
	Listiter(TYPE) li(((Bucket_ATTLC(TYPE)*)bp)->collision_list);

	while(
	    !li.at_end()
	){
	    TYPE* tp;
	    li.next(tp);
	    f(tp);
	}
	bp = bi.next();
    }
}
const TYPE*
Set(TYPE)::do_while(Pred_obj(CONST(TYPE))& f)const{
    Bucketiter_ATTLC(TYPE) bi(*this);
    const Bucket_ATTLC(TYPE)* bp = bi.first();

    while(
	bp
    ){
	Listiter(TYPE) li(((Bucket_ATTLC(TYPE)*)bp)->collision_list);

	while(
	    !li.at_end()
	){
	    TYPE* tp;
	    li.next(tp);

	    if(
		!f(tp)
	    ){
		return tp;
	    }
	}
	bp = bi.next();
    }
    return 0;
}
const TYPE*
Set(TYPE)::do_until(Pred_obj(CONST(TYPE))& f)const{
    Bucketiter_ATTLC(TYPE) bi(*this);
    const Bucket_ATTLC(TYPE)* bp = bi.first();

    while(
	bp
    ){
	Listiter(TYPE) li(((Bucket_ATTLC(TYPE)*)bp)->collision_list);

	while(
	    !li.at_end()
	){
	    TYPE* tp;
	    li.next(tp);

	    if(
		f(tp)
	    ){
		return tp;
	    }
	}
	bp = bi.next();
    }
    return 0;
}
Set(TYPE)&
Set(TYPE)::operator=(const Set(TYPE)& oo){

    if(
        this != &oo
    ){
        remove_all();
	Bucketiter_ATTLC(TYPE) bi(oo);
	const Bucket_ATTLC(TYPE)* bp = bi.first();

	while(
	    bp
	){
	    Listiter(TYPE) li(((Bucket_ATTLC(TYPE)*)bp)->collision_list);

	    while(
		!li.at_end()
	    ){
		TYPE* tp;
		li.next(tp);
		insert(*tp);
	    }
	    bp = bi.next();
	}
    }
    return *this;
}
int
Set(TYPE)::operator==(const Set(TYPE)& b)const{
/*
**
**  New version uses Bucketiter_ATTLC(TYPE)
**
*/
    if(
        size() != b.size()
    ){
        return 0;
    }
    Bucketiter_ATTLC(TYPE)     a_it(*this);
    Bucketiter_ATTLC(TYPE)     b_it(b);
    register const Bucket_ATTLC(TYPE)* ap = a_it.first();
    register const Bucket_ATTLC(TYPE)* bp = b_it.first();

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
**  the same values.
**
*/
        if(
            ap->collision_list.length() !=
            bp->collision_list.length()
        ){
            return 0;
        }
        Listiter(TYPE) lia(((Bucket_ATTLC(TYPE)*)ap)->collision_list);
        Listiter(TYPE) lib(((Bucket_ATTLC(TYPE)*)bp)->collision_list);

        while(
            !lia.at_end()
        ){
            TYPE* atp;
            lia.next(atp);
            lib.reset();
            int found=0;

            while(
                !lib.at_end()
            ){
                TYPE* btp;
                lib.next(btp);

                if(
                    *atp == *btp
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
**  zero.  If they are not both zero, the two Sets
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
Set(TYPE)::operator<=(const Set(TYPE)& b)const{
/*
**
**  New version uses Bucketiter_ATTLC(TYPE)
**
*/
    if(
        size() > b.size()
    ){
        return 0;
    }
    Bucketiter_ATTLC(TYPE)     a_it(*this);
    Bucketiter_ATTLC(TYPE)     b_it(b);
    register const Bucket_ATTLC(TYPE)* ap = a_it.first();
    register const Bucket_ATTLC(TYPE)* bp = b_it.first();

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
            Listiter(TYPE) lia(((Bucket_ATTLC(TYPE)*)ap)->collision_list);
            Listiter(TYPE) lib(((Bucket_ATTLC(TYPE)*)bp)->collision_list);

            while(
                !lia.at_end()
            ){
                TYPE* atp;
                lia.next(atp);
                lib.reset();
                int found=0;

                while(
                    !lib.at_end()
                ){
                    TYPE* btp;
                    lib.next(btp);

                    if(
                        *atp == *btp
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

        }else if(

            SET_LT_ATTLC(ap->hashval,bp->hashval)
        ){
/*
**
**  *ap contains values that can't be in oo, since we've
**  already passed the point where they would be found;
**  return failure
**
*/
            return 0;

        }else{
/*
**
**  *ap contains values that may be in a future 
**  Bucket_ATTLC of oo; increment b_it
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
Set(TYPE)::operator<(const Set(TYPE)& b)const{
/*
**
**  New version uses Bucketiter_ATTLC(TYPE)
**
*/
    if(
        size() >= b.size()
    ){
        return 0;
    }
    Bucketiter_ATTLC(TYPE)     a_it(*this);
    Bucketiter_ATTLC(TYPE)     b_it(b);
    register const Bucket_ATTLC(TYPE)* ap = a_it.first();
    register const Bucket_ATTLC(TYPE)* bp = b_it.first();
    int strict=0;

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
            Listiter(TYPE) lia(((Bucket_ATTLC(TYPE)*)ap)->collision_list);
            Listiter(TYPE) lib(((Bucket_ATTLC(TYPE)*)bp)->collision_list);

	    if(
                ap->collision_list.length() <
                bp->collision_list.length()
            ){
		strict = 1;
	    }
            while(
                !lia.at_end()
            ){
                TYPE* atp;
                lia.next(atp);
                lib.reset();
                int found=0;

                while(
                    !lib.at_end()
                ){
                    TYPE* btp;
                    lib.next(btp);

                    if(
                        *atp == *btp
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

        }else if(

            SET_LT_ATTLC(ap->hashval,bp->hashval)
        ){
/*
**
**  *ap contains values that can't be in oo, since we've
**  already passed the point where they would be found;
**  return failure
**
*/
            return 0;

        }else{
/*
**
**  *ap contains values that may be in a future
**  bucket of oo; increment b_it
**
*/
	    strict = 1;
            bp = b_it.next();
        }
    }
    strict = strict || (bp != 0 );
/*
**
**  The relation is true only if strict and a_it is exhasted
**
*/
    return strict && (ap==0);
}
const TYPE*
Set(TYPE)::insert(const TYPE& value,unsigned count){

    register Internal_item_ATTLC* itemp;
    register Internal_node_ATTLC* nodep;
    Bucket_ATTLC(TYPE)* bp;
    TYPE* result;

    if(count==0){
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
**  create a Set by walking an existing index and
**  inserting its elements into the new Set.
**
*/
    long mask = SET_MASK_BITS << SET_INITIAL_SHIFT;

    for(
         int depth = -1;
         depth < pos.curr_depth;
         depth++, mask <<= SET_SHIFT_INCR
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
        SET_INITIAL_SHIFT +
        SET_SHIFT_INCR +
        depth * SET_SHIFT_INCR
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
        mask <<= SET_SHIFT_INCR, unshift += SET_SHIFT_INCR
    ){
        assert(pos.curr_depth < SET_POSITIONS);

        if(
            itemp->is_null()
        ){

            break;

        }else if(
            itemp->is_leaf()
        ){

            bp = (Bucket_ATTLC(TYPE)*)itemp->external_leaf();

            if(
                bp->hashval == hval
            ){
/*
**
**  The 'value' goes in this Bucket
**
*/
                Listiter(TYPE) it(((Bucket_ATTLC(TYPE)*)bp)->collision_list);
                TYPE* tp;

                while(
                    it.next(tp)
                ){

                    if(
                        *tp == value
                    ){
/*
**
**  The value is already in the Bucket; return failure
**
*/
                        return 0;
                    }
                }
/*
**
**  The value is not already in the Bucket; insert it
**
*/
                sze++;
                it.insert_next(value);
		it.peek_next(result);
                return result;

            }else{
/*
**
**  This Bucket is not the one where the value belongs;
**  a subindex will have to be created containing both
**  this Bucket and a new one created to hold 'value'
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
**  existing leaf and a new leaf pointing to a new Bucket
**  containing 'value.'  In either case, the cardinality
**  of the Set is increased by one.
**
*/
    sze++;

    if(
        itemp->is_null()
    ){
/*
**
**  Make this null item into a leaf pointing to a new
**  Bucket containing 'value'
**
*/
        itemp->make_leaf( new Bucket_ATTLC(TYPE) );
        bp = (Bucket_ATTLC(TYPE)*)itemp->external_leaf();
        bp->hashval = hval;
        bp->collision_list.insert_next(value);
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
**  Bucket containing 'value'
**
*/
        bp = (Bucket_ATTLC(TYPE)*)itemp->external_leaf();
        Set_or_Bag_hashval temp = bp->hashval;
        int ind1,ind2;

        for(
            ;
            ;
            mask <<= SET_SHIFT_INCR,
	    unshift += SET_SHIFT_INCR
        ){
            itemp->make_node(nodep = new Internal_node_ATTLC);
            assert(pos.curr_depth < SET_POSITIONS);
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
**  Make a new leaf and Bucket for 'value'
**
*/
        itemp = &nodep->item[ind2];
        itemp->make_leaf( new Bucket_ATTLC(TYPE) );
        bp = (Bucket_ATTLC(TYPE)*)itemp->external_leaf();
        bp->hashval = hval;
        bp->collision_list.insert_next(value);
	bp->collision_list.peek_next(result);
        pos.curr_pos[++pos.curr_depth] = itemp;
        nodep->busy_count = 2;
        return result;
    }
}
unsigned
Set(TYPE)::remove(const TYPE& value,unsigned count){
    register Internal_item_ATTLC* itemp;
    register Internal_node_ATTLC* nodep;
    Bucket_ATTLC(TYPE)* bp=0;

    if(count==0){
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
**  create a Set by walking an existing index and inserting
**  its elements into the new Set.
**
*/
    register long mask = SET_MASK_BITS << SET_INITIAL_SHIFT;

    for(
        int depth = -1;
        depth < pos.curr_depth;
        depth++, mask <<= SET_SHIFT_INCR
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
        SET_INITIAL_SHIFT +
        SET_SHIFT_INCR +
        depth * SET_SHIFT_INCR
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
**  Find the leaf pointing to the Bucket containing
**  the value to be deleted.
**
*/
    for(
        pos.curr_depth = depth;
        ;
        mask <<= SET_SHIFT_INCR,
        unshift += SET_SHIFT_INCR
    ){
        assert(pos.curr_depth < SET_POSITIONS);

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

            bp = (Bucket_ATTLC(TYPE)*)itemp->external_leaf();

            if(
                bp->hashval == hval
            ){
/*
**
**  The value may be in the Bucket pointed to by
**  this leaf.
**
*/
                break;

            }else{
/*
**
**  The leaf must have been deleted and subsequently
**  replaced by a different Bucket (one with a different
**  hash value).  Return failure
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
**  We found the Bucket; locate the value in the
**  collision list and remove it
**
*/
    Listiter(TYPE) it(((Bucket_ATTLC(TYPE)*)bp)->collision_list);
    TYPE* tp;
    int found=0;

    while(
        it.next(tp)
    ){

        if(
            *tp == value
        ){
            found=1;
            it.remove_prev();
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
**  worry about the Bucket becoming empty.
**
*/
    sze--;

    if(
        bp->collision_list.length() > 0
    ){
/*
**
**  The collision list still has one or more elements.
**
*/
        return 1;
    }
/*
**
**  The collision list has become empty as a result of
**  this deletion; we must delete the Bucket and fix up
**  the index accordingly.
**
*/
    if(
        pos.curr_depth == -1
    ){
/*
**
**  The Set had only one element in it
**
*/
        assert(sze == 0);
        delete bp;
        itemp->make_null();
        return 1;
    }
/*
**
**  Get the parent node (if not already known)
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
**  Easy case: node still has more than one busy item
**
*/
        delete bp;
        itemp->make_null();
        return 1;
    }
/*
**
**  Hard case: node has only one busy item; since nodes
**  ideally contain two or more busy items, we should
**  try to absorb the item
**
*/
    assert(nodep->busy_count == 1);
/*
**
**  Find the busy item, itp
**
*/
    for (
        register Internal_item_ATTLC* itp = &nodep->item[0];
        itp < &nodep->item[SET_NODE_SIZE];
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
        return 1;
    }
/*
**
**  Relatively easy case: absorb a leaf
**
*/
    Bucket_ATTLC(TYPE)* temp = (Bucket_ATTLC(TYPE)*)itp->external_leaf();

    for(
        ;
        ;
    ){
        delete nodep;

        if(
            pos.curr_depth-- == 0
        ){
            assert(sze == 1);
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
    return 1;
}
unsigned 
Set(TYPE)::remove_all(){
    unsigned result = sze;
    warn_iterators();
    register Internal_item_ATTLC* itemp = &contents;

    if(
        itemp->is_null()
    ){
        assert(sze == 0);
        return result;
    }
    if(
        itemp->is_leaf()
    ){
        assert(sze >= 1);
        itemp->make_null();
        sze = 0;
        return result;
    }
    register Internal_node_ATTLC* nodep = itemp->next_node();
    itemp = &nodep->item[0];
    pos.curr_depth = -1;

    for(;;) {
        register Internal_item_ATTLC* stopper = (
            &nodep->item[SET_NODE_SIZE]
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
                stopper = &nodep->item[SET_NODE_SIZE];
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
		Bucket_ATTLC(TYPE)* bp = (
		    (Bucket_ATTLC(TYPE)*)itemp->external_leaf()
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
    return result;
}
const TYPE*
Set(TYPE)::contains(const TYPE& value)const{

    register Internal_item_ATTLC* itemp;
    register Internal_node_ATTLC* nodep;
    Bucket_ATTLC(TYPE)* bp;
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
    register long mask = SET_MASK_BITS << SET_INITIAL_SHIFT;

    for(
        int depth = -1;
        depth < pos.curr_depth;
        depth++, mask <<= SET_SHIFT_INCR
    ){
        if(
            (pos.curr_value & mask) !=
            (hval & mask)
        ){
            break;
        }
    }
    register int unshift = (
        SET_INITIAL_SHIFT +
        SET_SHIFT_INCR +
        depth * SET_SHIFT_INCR
    );
    if (depth == -1) itemp = &(((Set(TYPE) *)this)->contents);
    else itemp = pos.curr_pos[depth];
/*    itemp = (

        depth == -1 ?(
            &contents
        ):(
            pos.curr_pos[depth]
        )
    );*/
    nodep = 0;
    pos.curr_value = hval;

    for(
        pos.curr_depth = depth;
        ;
        mask <<= SET_SHIFT_INCR, unshift += SET_SHIFT_INCR
    ){
        assert(pos.curr_depth < SET_POSITIONS);

        if(
            itemp->is_null()
        ){
            return 0;
        }
        if(
            itemp->is_leaf()
        ){
            bp = (Bucket_ATTLC(TYPE)*)itemp->external_leaf();
            Listiter(TYPE) it(((Bucket_ATTLC(TYPE)*)bp)->collision_list);
            TYPE* tp;

            while(
                it.next(tp)
            ){

                if(
                    value == *tp
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
void
Set(TYPE)::do_each(Procedure(CONST(TYPE))& f)const{
    Bucketiter_ATTLC(TYPE) bi(*this);
    const Bucket_ATTLC(TYPE)* bp = bi.first();

    while(
	bp
    ){
	Listiter(TYPE) li(((Bucket_ATTLC(TYPE)*)bp)->collision_list);

	while(
	    !li.at_end()
	){
	    TYPE* tp;
	    li.next(tp);
	    f(tp);
	}
	bp = bi.next();
    }
}
const TYPE*
Set(TYPE)::do_while(Predicate(CONST(TYPE))& f)const{
    Bucketiter_ATTLC(TYPE) bi(*this);
    const Bucket_ATTLC(TYPE)* bp = bi.first();

    while(
	bp
    ){
	Listiter(TYPE) li(((Bucket_ATTLC(TYPE)*)bp)->collision_list);

	while(
	    !li.at_end()
	){
	    TYPE* tp;
	    li.next(tp);

	    if(
		!f(tp)
	    ){
		return tp;
	    }
	}
	bp = bi.next();
    }
    return 0;
}
const TYPE*
Set(TYPE)::do_until(Predicate(CONST(TYPE))& f)const{
    Bucketiter_ATTLC(TYPE) bi(*this);
    const Bucket_ATTLC(TYPE)* bp = bi.first();

    while(
	bp
    ){
	Listiter(TYPE) li(((Bucket_ATTLC(TYPE)*)bp)->collision_list);

	while(
	    !li.at_end()
	){
	    TYPE* tp;
	    li.next(tp);

	    if(
		f(tp)
	    ){
		return tp;
	    }
	}
	bp = bi.next();
    }
    return 0;
}
Set(TYPE)&
Set(TYPE)::operator|=(const Set(TYPE)& oo){

    if(
        this != &oo
    ){
	Bucketiter_ATTLC(TYPE) bi(oo);
	const Bucket_ATTLC(TYPE)* bp = bi.first();

	while(
	    bp
	){
	    Listiter(TYPE) li(((Bucket_ATTLC(TYPE)*)bp)->collision_list);

	    while(
		!li.at_end()
	    ){
		TYPE* tp;
		li.next(tp);
		(void)insert(*tp);
	    }
	    bp = bi.next();
	}
    }
    return *this;
}
Set(TYPE)&
Set(TYPE)::operator-=(const Set(TYPE)& oo){

    if(
        this != &oo
    ){
	Bucketiter_ATTLC(TYPE) bi(oo);
	const Bucket_ATTLC(TYPE)* bp = bi.first();

	while(
	    bp
	){
	    Listiter(TYPE) li(((Bucket_ATTLC(TYPE)*)bp)->collision_list);

	    while(
		!li.at_end()
	    ){
		TYPE* tp;
		li.next(tp);
		(void)remove(*tp);
	    }
	    bp = bi.next();
	}
    }else{
        remove_all();
    }
    return *this;
}
Set(TYPE)&
Set(TYPE)::operator&=(const Set(TYPE)& oo){

    if(
        this != &oo
    ){
	Bucketiter_ATTLC(TYPE) bi(*this);
	const Bucket_ATTLC(TYPE)* bp = bi.first();

	while(
	    bp
	){
	    Listiter(TYPE) li(((Bucket_ATTLC(TYPE)*)bp)->collision_list);
/*
**
**  remove() may delete the collision list;
**  beware of dangling list iterator;
**
*/
	    while(
		li.the_list() &&
		!li.at_end()
	    ){
		TYPE* tp;
		li.next(tp);

		if(
		    !oo.contains(*tp)
		){
		    remove(*tp);
		}
	    }
	    bp = bi.next();
	}
    }
    return *this;
}
Set(TYPE)&
Set(TYPE)::operator^=(const Set(TYPE)& oo){
/*
**
**  This should be converted to use Bucketiters!
**
*/

    if(
        this != &oo
    ){
        Setiter(TYPE) a_it(*this);
        Setiter(TYPE) b_it(oo);
        register const TYPE* ap = a_it.next();
        register const TYPE* bp = b_it.next();

        while(
            ap && bp
        ){

            if(
                *ap == *bp
            ){
                remove(*ap);
                ap = a_it.next();
                bp = b_it.next();
            }else if(
                SET_LT_ATTLC( H(*ap) , H(*bp) )
            ){
                ap = a_it.next();
            }else{
                insert(*bp);
                bp = b_it.next();
            }
        }
        while(
            bp
        ){
            insert(*bp);
            bp = b_it.next();
        }
    }else{
        remove_all();
    }
    return *this;
}
void
Set(TYPE)::warn_iterators()const{

    for(
        register Bucketiter_ATTLC(TYPE)* it = iter_head;
        it;
        it = it->next_it
    ){
        it->clobber();
    }
}
void
Set(TYPE)::histogram(Map(Set_or_Bag_hashval,unsigned)& m)const{
/*
**
**  Iterate over buckets, creating a Map from
**  bp->hashval to bp->collision_list.length().
**
*/
    Bucketiter_ATTLC(TYPE) bi(*this);
    const Bucket_ATTLC(TYPE)* bp = bi.first();
    m = Map(Set_or_Bag_hashval,unsigned)();

    while(
        bp
    ){
        m[bp->hashval] = bp->collision_list.length();
        bp = bi.next();
    }
}
void
Set(TYPE)::check()const{

/*
**
**  New version uses Bucketiter_ATTLC(TYPE)'s
**
*/
    Bucketiter_ATTLC(TYPE) bi(*this);
    const Bucket_ATTLC(TYPE)* bp = bi.first();
    Set_or_Bag_hashval oldhashval=0;  /* initialize to avoid warning */
    int first=1;

    while(
        bp
    ){
/*
**  Buckets must be stored in increasing order of
**  hash value
*/
        if(
            first
        ){
            first=0;
        }else{
            assert(SET_LT_ATTLC(oldhashval,bp->hashval));
        }
        oldhashval = bp->hashval;
/*
**  Collision lists may not be empty
*/
        assert(bp->collision_list.length()>0);
/*
**  Collision lists may not contain duplicates
*/
        Listiter(TYPE) it1(((Bucket_ATTLC(TYPE)*)bp)->collision_list);
        Listiter(TYPE) it2(((Bucket_ATTLC(TYPE)*)bp)->collision_list);

        while(
            !it1.at_end()
        ){
            it2.reset();

            while(
            !it2.at_end()
            ){
                TYPE* p1;
                TYPE* p2;
                it1.next(p1);
                it2.next(p2);
                assert(*p1 == *p2);
            }
        }
        bp = bi.next();
    }
}
Set(TYPE)::~Set(TYPE)(){
/*
**
**  TBD_study this
**
*/
    for(
        register Bucketiter_ATTLC(TYPE)* it = iter_head;
        it;
        it = it->next_it
    ){
/*
**
**  Break const for giggles
**
*/
        Set(TYPE)** cheat = (Set(TYPE)**)&it->my_set;
        *cheat = 0;
    }
    remove_all();
}
Set(TYPE)::Set(TYPE)(const Set(TYPE)& oo) :
    sze(0),
    iter_head(0)
{
    pos.curr_depth = -1;
    contents.make_null();
    Bucketiter_ATTLC(TYPE) bi(oo);
    const Bucket_ATTLC(TYPE)* bp = bi.first();

    while(
	bp
    ){
	Listiter(TYPE) li(((Bucket_ATTLC(TYPE)*)bp)->collision_list);

	while(
	    !li.at_end()
	){
	    TYPE* tp;
	    li.next(tp);
	    insert(*tp);
	}
	bp = bi.next();
    }
}
void
Set(TYPE)::make_select(
    Predicate(CONST(TYPE))& f,
    const Set(TYPE)& a
){
    assert(sze==0);
    Bucketiter_ATTLC(TYPE) bi(a);
    const Bucket_ATTLC(TYPE)* bp = bi.first();

    while(
        bp
    ){
	Listiter(TYPE) li(((Bucket_ATTLC(TYPE)*)bp)->collision_list);

	while(
	    !li.at_end()
	){
            TYPE* tp;
	    li.next(tp);

	    if(
		f(tp)
	    ){
		insert(*tp);
	    }
	}
	bp = bi.next();
    }
}
void
Set(TYPE)::make_reject(
    Predicate(CONST(TYPE))& f,
    const Set(TYPE)& a
){
    assert(sze==0);
    Bucketiter_ATTLC(TYPE) bi(a);
    const Bucket_ATTLC(TYPE)* bp = bi.first();

    while(
        bp
    ){
	Listiter(TYPE) li(((Bucket_ATTLC(TYPE)*)bp)->collision_list);

	while(
	    !li.at_end()
	){
            TYPE* tp;
	    li.next(tp);

	    if(
		!f(tp)
	    ){
		insert(*tp);
	    }
	}
	bp = bi.next();
    }
}
void
Set(TYPE)::make_map(
    Transformer(CONST(TYPE))& f,
    const Set(TYPE)& a
){
    assert(sze==0);
    Bucketiter_ATTLC(TYPE) bi(a);
    const Bucket_ATTLC(TYPE)* bp = bi.first();

    while(
        bp
    ){
	Listiter(TYPE) li(((Bucket_ATTLC(TYPE)*)bp)->collision_list);

	while(
	    !li.at_end()
	){
            TYPE* tp;
	    li.next(tp);
	    insert(*f(tp));
	}
	bp = bi.next();
    }
}
void
Set(TYPE)::make_union(
    const Set(TYPE)& a,
    const Set(TYPE)& b
){
/*
**
**  New version uses Bucketiter(T))'s
**
*/
    assert(sze == 0);
    Bucketiter_ATTLC(TYPE)     a_it(a);
    Bucketiter_ATTLC(TYPE)     b_it(b);
    register const Bucket_ATTLC(TYPE)* ap = a_it.first();
    register const Bucket_ATTLC(TYPE)* bp = b_it.first();

    while(
        ap && bp
    ){
        Listiter(TYPE) lia(((Bucket_ATTLC(TYPE)*)ap)->collision_list);
        Listiter(TYPE) lib(((Bucket_ATTLC(TYPE)*)bp)->collision_list);

        if(
            ap->hashval == bp->hashval
        ){
/*
**
**  First, insert all values in ap->collision_list
**
*/
            lia.reset();

            while(
                !lia.at_end()
            ){
                TYPE* atp;
                lia.next(atp);
                insert(*atp);
            }
/*
**
**  Next, insert those values in bp->collision list
**  that were not already in ap->collision_list.
**
**  For an optimal hash function (collision_lists of
**  length 1), only one comparison will be required.
**  In general, the complexity is quadratic.
**
**  TBD_note: Alternatively, we could let insert()
**  handle the duplicates.
**
*/
            lib.reset();

            while(
                !lib.at_end()
            ){
                TYPE* btp;
                lib.next(btp);
                lia.reset();
                int found=0;

                while(
                    !lia.at_end()
                ){
                    TYPE* atp;
                    lia.next(atp);

                    if(
                        *atp == *btp
                    ){
                        found=1;
                        break;
                    }
                }
                if(
                    !found
                ){
                    insert(*btp);
                }
            }
            ap = a_it.next();
            bp = b_it.next();
        }else if(
            SET_LT_ATTLC(ap->hashval,bp->hashval)
        ){
            lia.reset();

            while(
                !lia.at_end()
            ){
                TYPE* atp;
                lia.next(atp);
                insert(*atp);
            }
            ap = a_it.next();
        }else{
            lib.reset();

            while(
                !lib.at_end()
            ){
                TYPE* btp;
                lib.next(btp);
                insert(*btp);
            }
            bp = b_it.next();
        }
    }
/*
**
**  Insert whatever's left over from a and b
**
*/
    for(
        ;
        ap;
        ap = a_it.next()
    ){
        Listiter(TYPE) lia(((Bucket_ATTLC(TYPE)*)ap)->collision_list);

        while(
            !lia.at_end()
        ){
            TYPE* atp;
            lia.next(atp);
            insert(*atp);
        }
    }
    for(
        ;
        bp;
        bp = b_it.next()
    ){
        Listiter(TYPE) lib(((Bucket_ATTLC(TYPE)*)bp)->collision_list);

        while(
            !lib.at_end()
        ){
            TYPE* btp;
            lib.next(btp);
            insert(*btp);
        }
    }
}
void
Set(TYPE)::make_intersection(
    const Set(TYPE)& a,
    const Set(TYPE)& b
){
/*
**
**  New version uses Bucketiter(T))'s
**
*/
    assert(sze == 0);
    Bucketiter_ATTLC(TYPE)     a_it(a);
    Bucketiter_ATTLC(TYPE)     b_it(b);
    register const Bucket_ATTLC(TYPE)* ap = a_it.first();
    register const Bucket_ATTLC(TYPE)* bp = b_it.first();

    while(
        ap && bp
    ){
        Listiter(TYPE) lib(((Bucket_ATTLC(TYPE)*)bp)->collision_list);
        Listiter(TYPE) lia(((Bucket_ATTLC(TYPE)*)ap)->collision_list);

        if(
            ap->hashval == bp->hashval
        ){
/*
**
**  The two hash functions are equal; this means
**  that the hash Buckets MAY contain equal values;
**  they must be scanned.
**
**  For an optimal hash function
**  (collision_list.length()==1),
**  only one comparison will be required.
**  In general, the complexity is quadratic.
**
*/
            lib.reset();

            while(
                !lib.at_end()
            ){
                TYPE* btp;
                lib.next(btp);
                lia.reset();

                while(
                    !lia.at_end()
                ){
                    TYPE* atp;
                    lia.next(atp);

                    if(
                        *atp == *btp
                    ){
                        insert(*btp);
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
**  CANNOT be any equal elements in the buckets.
**
*/
            if(
                SET_LT_ATTLC( ap->hashval , bp->hashval )
            ){
                ap = a_it.next();
            }else{
                bp = b_it.next();
            }
        }
    }
}
void
Set(TYPE)::make_difference(
    const Set(TYPE)& a,
    const Set(TYPE)& b
){
/*
**
**  Experimental version, optimized for singleton lists
**  Note: this "optimization" has little effect
**
*/
    assert(sze == 0);
    Bucketiter_ATTLC(TYPE) a_it(a);
    Bucketiter_ATTLC(TYPE) b_it(b);
    register const Bucket_ATTLC(TYPE)* ap = a_it.first();
    register const Bucket_ATTLC(TYPE)* bp = b_it.first();
    TYPE *atp;
    TYPE* btp;

    while(
        ap && bp
    ){
        if(
            ap->hashval == bp->hashval
        ){
/*
**
**  The two hash values are equal.  This means that
**  b may contain values to be subtracted from a.
**
**  For lists of length 1, only one comparison will
**  be required.  In general, complexity is quadratic.
**
*/
	    if(
		ap->collision_list.length() == 1 &&
		bp->collision_list.length() == 1
	    ){
		ap->collision_list.peek_next(atp);
		bp->collision_list.peek_next(btp);

		if(
		    !(*atp == *btp)
		){
		    insert(*atp);
		}
	    }else{

		Listiter(TYPE) lia(((Bucket_ATTLC(TYPE)*)ap)->collision_list);
		Listiter(TYPE) lib(((Bucket_ATTLC(TYPE)*)bp)->collision_list);

		while(
		    !lia.at_end()
		){
		    lia.next(atp);
		    lib.reset();
		    int found=0;

		    while(
			!lib.at_end()
		    ){
			lib.next(btp);

			if(
			    *atp == *btp
			){
			    found=1;
			    break;
			}
		    }
		    if(
			!found
		    ){
			insert(*atp);
		    }
		}
	    }
	    ap = a_it.next();
	    bp = b_it.next();

        }else if(

            SET_LT_ATTLC( ap->hashval,bp->hashval )
        ){
/*
**
**  Insert all the values in *ap
**
*/
            if(
		ap->collision_list.length() == 1
	    ){
		ap->collision_list.peek_next(atp);
                insert(*atp);

	    }else{

		Listiter(TYPE) lia(((Bucket_ATTLC(TYPE)*)ap)->collision_list);

		while(
		    !lia.at_end()
		){
		    lia.next(atp);
		    insert(*atp);
		}
	    }
            ap = a_it.next();
        }else{
            bp = b_it.next();
        }
    }
/*
**
**  Insert the remaining values from ap buckets
**
*/
    while(
	ap
    ){
	if(
	    ap->collision_list.length() == 1
	){
	    ap->collision_list.peek_next(atp);
	    insert(*atp);
	}else{
	    Listiter(TYPE) lia(((Bucket_ATTLC(TYPE)*)ap)->collision_list);

	    while(
		!lia.at_end()
	    ){
		lia.next(atp);
		insert(*atp);
	    }
	}
	ap = a_it.next();
    }
}
void
Set(TYPE)::make_xor(
    const Set(TYPE)& a,
    const Set(TYPE)& b
){
/*
**
**  New version uses Bucketiter(T))'s
**
*/
    assert(sze == 0);
    Bucketiter_ATTLC(TYPE)     a_it(a);
    Bucketiter_ATTLC(TYPE)     b_it(b);
    register const Bucket_ATTLC(TYPE)* ap = a_it.first();
    register const Bucket_ATTLC(TYPE)* bp = b_it.first();

    while(
        ap && bp
    ){
        Listiter(TYPE) lia(((Bucket_ATTLC(TYPE)*)ap)->collision_list);
        Listiter(TYPE) lib(((Bucket_ATTLC(TYPE)*)bp)->collision_list);

        if(
            ap->hashval == bp->hashval
        ){
/*
**
**  The two hash values are equal; this means
**  the two collision lists may contain equal
**  values (which must be weeded out).
**
**  For an optimal hash function
**  (collision_list.length()==1),
**  only one comparison will be required.
**  In general, the complexity is quadratic.
**
*/
            lib.reset();

            while(
                !lib.at_end()
            ){
                TYPE* btp;
                lib.next(btp);
                lia.reset();
                int found=0;

                while(
                    !lia.at_end()
                ){
                    TYPE* atp;
                    lia.next(atp);

                    if(
                        *atp == *btp
                    ){
                        found=1;
                        break;
                    }
                }
                if(
                    !found
                ){
                    insert(*btp);
                }
            }
            lia.reset();

            while(
                !lia.at_end()
            ){
                TYPE* atp;
                lia.next(atp);
                lib.reset();
                int found=0;

                while(
                    !lib.at_end()
                ){
                    TYPE* btp;
                    lib.next(btp);

                    if(
                        *btp == *atp
                    ){
                        found=1;
                        break;
                    }
                }
                if(
                    !found
                ){
                    insert(*atp);
                }
            }
            ap = a_it.next();
            bp = b_it.next();

        }else if(
            SET_LT_ATTLC( ap->hashval,bp->hashval )
        ){
            lia.reset();

            while(
                !lia.at_end()
            ){
                TYPE* atp;
                lia.next(atp);
                insert(*atp);
            }
            ap = a_it.next();
        }else{
            lib.reset();

            while(
                !lib.at_end()
            ){
                TYPE* btp;
                lib.next(btp);
                insert(*btp);
            }
            bp = b_it.next();
        }
    }
/*
**
**  Insert the remaining values from ap buckets
**
*/
    for (
        ;
        ap;
        ap = a_it.next()
    ){
        Listiter(TYPE) lia(((Bucket_ATTLC(TYPE)*)ap)->collision_list);

        while(
            !lia.at_end()
        ){
            TYPE* atp;
            lia.next(atp);
            insert(*atp);
        }
    }
/*
**
**  Insert the remaining values from bp buckets
**
*/
    for (
        ;
        bp;
        bp = b_it.next()
    ){
        Listiter(TYPE) lib(((Bucket_ATTLC(TYPE)*)bp)->collision_list);

        while(
            !lib.at_end()
        ){
            TYPE* btp;
            lib.next(btp);
            insert(*btp);
        }
    }
}
const TYPE*
Set(TYPE)::select()const{
    Bucketiter_ATTLC(TYPE) bi(*this);
    const Bucket_ATTLC(TYPE)* bp = bi.first();

    if(!bp){
	return 0;
    }
    Listiter(TYPE) li(((Bucket_ATTLC(TYPE)*)bp)->collision_list);
    TYPE* tp;
    li.next(tp);
    return tp;
}
PT_end

PT_define Setout(TYPE)
ostream& operator<<(
    ostream& os,
    const Set(TYPE)& s
){
    os << "{";
    Setiter(TYPE) it(s);
    const TYPE* tp;
    int first=1;

    while(
	tp = it.next()
    ){
	if(
	    first
	){
	    first=0;
	}else{
	    os << ",";
	}
	os << *tp;
    }
    os << "}";
    return os;
}
PT_end
					



PT_define Set_func_declare_ATTLC(TYPE)
/*--------- set generator declaration -----------*/
class Set_generator(TYPE) : public Gene_obj(CONST(TYPE)){

    friend Set(TYPE);

private:

    Setiter(TYPE)        it;

    inline
    Set_generator(TYPE)(const Set(TYPE)&);
public:
    CONST(TYPE)* operator()();
/*
**
**  The following is needed to eliminate an inline msg
**
*/
    ~Set_generator(TYPE)();
};

Set(TYPE)
Set(TYPE)::select(Predicate(CONST(TYPE))& p)const{
    return Set(TYPE)(p,*this,(Set_select_ATTLC*)0);
}
Set(TYPE)
Set(TYPE)::select(Pred_obj(CONST(TYPE))& p)const{
    return Set(TYPE)(p,*this,(Set_select_ATTLC*)0);
}
Set(TYPE)
Set(TYPE)::reject(Predicate(CONST(TYPE))& p)const{
    return Set(TYPE)(p,*this,(Set_reject_ATTLC*)0);
}
Set(TYPE)
Set(TYPE)::reject(Pred_obj(CONST(TYPE))& p)const{
    return Set(TYPE)(p,*this,(Set_reject_ATTLC*)0);
}
Set(TYPE)
Set(TYPE)::map(Transformer(CONST(TYPE))& f)const{
    return Set(TYPE)(f,*this,(Set_map_ATTLC*)0);
}
Set(TYPE)
Set(TYPE)::map(Tran_obj(CONST(TYPE))& f)const{
    return Set(TYPE)(f,*this,(Set_map_ATTLC*)0);
}
Set_generator(TYPE)::Set_generator(TYPE)(
    const Set(TYPE)& s
):
    it(s)
{ }
Set_generator(TYPE)
Set(TYPE)::generator()const{
    return Set_generator(TYPE)(*this);
}
Set_generator(TYPE)*
Set(TYPE)::new_generator()const{
    return new Set_generator(TYPE)(*this);
}
PT_end

PT_define Setimplement(TYPE)
Setimplement(TYPE,Set_zero_ATTLC)
PT_end

#endif
