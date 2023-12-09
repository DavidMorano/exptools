#ifndef INTSET_DOT_H
#define INTSET_DOT_H
/********************************************************/
/*  Integer Set Package  for C++ 2.0                    */
/*  Author: J. E. Grass                                 */
/*          MH 3C- 532C             (201) 582-6905      */
/*          ulysses!jeg                                 */
/*  Date:   Aug. 19, 1988                               */
/********************************************************/

#include <iostream.h>
#include <stdlib.h>
#include <stdarg.h>
#include	<memory.h>

#if defined(V9) || defined(SYSV)
#include    <values.h>
#endif

class Int_set_iter;
class Int_set;
extern int   INTSET_DBG;

 /************************************************************/
 /*  The following class is here as an out and out Kluge     */
 /*  If there is a set constructor with an integer argument, */
 /*  Then C++ will do implicit conversions of integers to sets */
 /*  for all of the overloaded set operators. To AVOID that,   */
 /*  defining this and then NO integer arg constructors will   */
 /*  ensure compile time errors in those cases    ....         */
 /*  NONE of this would be needed if C++ used constructors just */
 /*  for constructing and used SOMETHING ELSE just for coercions */
 /*    <End of sermon>                                           */
 /***************************************************************/
 
 struct Int_set_size{
       int size;
               /*the largest member that will fit the set, calc bits from this*/

       Int_set_size(int s){ 
               if (s < 0){
                       cerr << "Int_set_size::Int_set_size("<<s<<") size may not be negative\n";
                       size = 0;       /* smallest allowable */
               }
               else size = s;
       };
 };

/********************************************************/
/*  Representation... is here                           */
/*        organized to limit copies and creation of tmps*/
/********************************************************/
class Int_set_rep {

friend class Int_set_iter;
friend class Int_set;
friend iostream &operator<<(iostream&, Int_set&);

	unsigned int *bit_vec; /* use as bits for set.. bits numbered 0 ..setsize*/
	int	word_cnt;
	int	max_member;	/* biggest value in	set	.. used	in iterating */
	int	max_bits; /* biggest val that will fit */

	int refcnt;            /* count of pointers to this */

	void grow(int);	/* could be	used to	shrink too */
	int	find_max(int);
	int find_min(int);
	void set_member(int);
	void clear_member(int );

	Int_set_rep();    /* default size:	1 word		   */
	Int_set_rep(Int_set_size); /*	set	fits at least this	element	*/
	Int_set_rep(Int_set_rep *); /*	duplicate rep */
	~Int_set_rep() { 
		  delete bit_vec; 
		  if(INTSET_DBG)
			cout << "Deleteing set "<<this<<"\n";
		};

	Int_set_rep 	*diff(Int_set_rep *);	    /* difference */
	Int_set_rep 	*intersect(Int_set_rep*);	/* intersection	*/
	Int_set_rep 	*do_union(Int_set_rep *);	/* union		*/
};

/**********************************************************/
/*  User view of int sets                                 */
/**********************************************************/
class Int_set {
	friend class Int_set_iter;

	Int_set_rep *rep;

	Int_set(Int_set_rep *newrep){ 	
		rep = newrep;
		rep ->refcnt++;
	};

	int	find_max(int old_max){ return (rep->find_max(old_max));};
	int find_min(int old_min){ return (rep->find_min(old_min));};
	int get_max_bits()    {return (rep->max_bits); };

protected:
	void grow(int);	/* could be	used to	shrink too */

public:
	Int_set(){     /* default size:	1 word		   */
		rep = new Int_set_rep();
		rep->refcnt++;
	};

	Int_set(int head, int rest ...);

	Int_set(int *mem_list){     /* initialize with this int vec */
		rep = new Int_set_rep();
		rep->refcnt++;
		add(mem_list);
	};

	Int_set(Int_set_size maxel){ /*	set	fits sat least this	element	*/
		rep = new Int_set_rep(maxel);
		rep->refcnt++;
	};

	Int_set(Int_set &oldobj){ 	/* ptr to a copy			*/
		rep = oldobj.rep;
		rep ->refcnt++;
	};



	~Int_set(){
		rep->refcnt--;
		if(rep->refcnt == 0)
			delete rep;
	};

	void operator=(Int_set &oldobj){ /* assignment	is a copy op. */
		if (this != &oldobj){
			rep->refcnt--;
			if (rep->refcnt == 0)
				delete rep;
			rep = oldobj.rep;
			rep->refcnt++;
		}
	};

		/* binary set operators */
	Int_set operator-(Int_set	&m){	/* difference */
    	return Int_set(rep->diff(m.rep));
	};
	Int_set operator&(Int_set	&m){	/* intersection	*/
    	return Int_set(rep->intersect(m.rep));
	};
	Int_set operator|(Int_set	&m){	/* union		*/
    	return Int_set(rep->do_union(m.rep));
	};

		/* these change the contents of the set */
		/* add: list MUST end in negative number */
	void add(int, int =-1 ...);
	void add(int *);
	void fill_range(int, int);

	void make_empty();
		/* remove: list MUST end in negative number */
	void remove(int, int =-1 ...);
	void remove(int*);
	void clear_range(int, int);

		/* booleans and tests: no change in sets */
	int	compare(Int_set &); /* lexicographic	order */
	unsigned int operator==(Int_set &m) {return(compare(m) == 0); };
	unsigned int operator!=(Int_set &m) {return(compare(m) != 0); };
	unsigned int operator<(Int_set &m) {return(compare(m) < 0); };
	unsigned int operator>(Int_set &m) {return(compare(m) > 0); };
	unsigned int operator<=(Int_set &m){ return(compare(m) <= 0); };
	unsigned int operator>=(Int_set &m){ return(compare(m) >= 0); };

	unsigned int includes(int);
	int	cardinality();

	unsigned int is_subset_of(Int_set &); /* is contained in */
	unsigned int is_superset_of(Int_set &m)/* contains */
		{return(m.is_subset_of(* this)); };
	unsigned int is_empty(){
		if(rep->max_member >= 0)	return(0);
		else return(1);
	};
	int	get_word_count() {return(rep->word_cnt);	};
	int	get_max_member() {return(rep->max_member); };
	int get_min_member() {return(rep->find_min(0));};

	friend iostream &operator<<(iostream&, Int_set&);
};

class Int_set_iter{
	int    nxt_member;   /* memory of last elt returned */
	Int_set *my_set;
public:
	Int_set_iter(Int_set& set)
		{ 
			my_set = &set; 
			nxt_member = -1;
		};

	int first()				/* reset .. return first member */
		{
			register int ret_val;

			ret_val = my_set->find_min(0);         /* first element */
			if(ret_val) nxt_member = ret_val;      /* remember last seen */
			return(ret_val);
		};

	int last()               /* set iteration to last elt   */
		{
			register int ret_val;
			
			ret_val = my_set->find_max(my_set->get_max_bits());
			if (ret_val) nxt_member = ret_val;
			return(ret_val);
		};

	int operator++()              /* return next item in set, -1 if no next */
		{
			register int ret_val;

			ret_val = my_set->find_min(nxt_member+1);
			if (ret_val >= 0) nxt_member = ret_val;
			return(ret_val);
		};

	int operator--()              /* return previous item, -1 if none      */
		{
			register int ret_val;

			ret_val = my_set->find_max(nxt_member-1);
			if (ret_val >= 0) nxt_member = ret_val;
			return(ret_val);
		};
};
#endif
