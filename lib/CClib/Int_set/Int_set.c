/********************************************************/
/*  Integer Set Package                                 */
/*  Author: J. E. Grass                                 */
/*          MH 3C- 532C             (201) 582-6905      */
/*          ulysses!jeg                                 */
/*  Date:   Aug. 19, 1988                               */
/********************************************************/

#include "Int_set.h"

int INTSET_DBG = 0;   /* for tracking sizes, max */
#ifndef BITSPERBYTE
    const static int BITSPERBYTE = 8;
#endif

const static int bits_in_word = (sizeof(unsigned int)) * BITSPERBYTE; 
				/* bits in a word   */
const static unsigned int full_word = ~((unsigned int) 0); /* set all bits to 1 */

inline static int Int_set_min(int a, int b) 
	{if (a < b) return(a); else return(b); };
inline static int Int_set_max(int a, int b) 
	{if (a > b) return(a); else return(b); };
inline static int total_words(int max_element) 
	{return (max_element / bits_in_word) + 1; };


/*******************************************************************/
/*   Set Representation functions                                  */
/*******************************************************************/
/*
 * 	constructor functions -
 *
 * 			Int_set_rep()  -  make a small one-word set
 * 			Int_set_rep(Int_set_size)  -  make a set of a specific size
 *          Int_set_rep(Int_set_rep *)- copy a rep before change 
 * 			Int_set_rep(Int_set &)  -  copy an existing set
 */
Int_set_rep::Int_set_rep()
{
	max_member = -1; /* empty for now... */
	max_bits = bits_in_word; /*  max number of bits  */
	word_cnt = 1;
	refcnt = 0;
	bit_vec = new unsigned int[word_cnt];

	memset((char *) bit_vec,0, word_cnt * sizeof(unsigned int));
	if(INTSET_DBG)  
		cout<<"Creating set "<<this<<" with "<< word_cnt <<" words\n";
}

/*
 * 	Int_set_rep(Int_set_size) --
 * 	create a set that can at least hold the element "max_element"
 */
Int_set_rep::Int_set_rep(Int_set_size max_element)
{

	max_member = -1; /* empty for now... */
	word_cnt = total_words(max_element.size);
	max_bits = word_cnt * bits_in_word;
	refcnt = 0;

	bit_vec = new unsigned int[word_cnt];

	memset((char *) bit_vec, 0, word_cnt * sizeof(unsigned int));
	if(INTSET_DBG)
		cout<<"Creating set "<<this<<" with "<<word_cnt<<" words\n";
}

/*
 * 	Int_set_rep(Int_set_rep *) --
 * 	   Duplicate a representation, this is here to allow making
 *     a copy that will be altered soon after
 */
Int_set_rep::Int_set_rep( Int_set_rep *rep)
{
	register int ix;

	max_member = rep->max_member; /* empty for now... */
	word_cnt = rep->word_cnt;
	max_bits = rep->max_bits;
	refcnt = 0;

	bit_vec = new unsigned int[word_cnt];

	for (ix = 0; ix < word_cnt; ix++)
		bit_vec[ix] = rep->bit_vec[ix];

	if(INTSET_DBG)
		cout<<"Creating set "<<this<<" with "<<word_cnt<<" words\n";
}

inline void Int_set_rep::set_member(int member){
    register word, bit;

    word = member / bits_in_word;
    bit = member - (word * bits_in_word);

    bit_vec[word] = bit_vec[word] | (1 << bit);
};

inline void Int_set_rep::clear_member(int member){
	register word, bit;

    word = member / bits_in_word;
    bit = member - (word * bits_in_word);

    bit_vec[word] = bit_vec[word] | (1 << bit);
    bit_vec[word] = bit_vec[word] & ~(1 << bit);

};

void Int_set_rep::grow(int words)
{
	int old_wc;

	old_wc = word_cnt;
	max_bits = words * bits_in_word;
	word_cnt = words;
	bit_vec = (unsigned int *) realloc((char *) bit_vec, words*sizeof(unsigned int));

		// clear the new part of vector
	memset((char *)&bit_vec[old_wc],0,(word_cnt-old_wc) * sizeof(unsigned int));
}

/*
 * 	find_max(int) --
 * 	find the maximum element in the set less than or equal to trialmax
 */
int Int_set_rep::find_max(int trialmax)
{
	if (trialmax < 0)
		return (trialmax);
	else if (trialmax > max_bits-1) 
		trialmax = max_bits-1;

	int fbits = trialmax % bits_in_word;
	int fword = trialmax / bits_in_word;
	register int ix;

	/* are there bits set in fword that are <= fbits? */
	if (bit_vec[fword] & ~(full_word << (fbits + 1))) {
		for (ix = fbits; ix >= 0; ix--) {
			if (bit_vec[fword] & (1 << ix)) {
				return (fword * bits_in_word + ix);
			}
		}
	}

	/* largest element is earlier */
	for (--fword; fword >= 0 && (bit_vec[fword] == 0); fword--);

	if (fword >= 0) {/* max is here */
		for (ix = bits_in_word - 1; ix >= 0; ix--) {
			if (bit_vec[fword] & (1 << ix)) {
				return ((fword) * bits_in_word + ix);
			}
		}
	}
	else return (-1); /* empty if haven't returned by now */
}

/*
 * 	find_min(int) --
 * 	find the minimum element in the set greater than or equal to trialmax
 */
int Int_set_rep::find_min(int trialmax)
{
	if (trialmax > max_member)  
		return (-1);  /* can't be an element >= this */
	else if (trialmax < 0) 
		trialmax = 0;

	int fbits = trialmax % bits_in_word;
	int fword = trialmax / bits_in_word;
	register int ix;

	/* are there bits set in fword that are >= fbits? */
	if (bit_vec[fword] & (full_word << fbits )) {
		for (ix = fbits; ix < bits_in_word; ix++ ){
			if (bit_vec[fword] & (1 << ix)) {
				return (fword * bits_in_word + ix);
			}
		}
	}

	/* smallest element is later */
	for (++fword; (fword < word_cnt) && (bit_vec[fword] == 0); fword++);

	if (fword < word_cnt) {/* min is here */
		for (ix = 0; ix < bits_in_word; ix++) {
			if (bit_vec[fword] & (1 << ix)) {
				return ((fword) * bits_in_word + ix);
			}
		}
	}
	else return (-1); /* empty above trialmax if haven't returned by now */
}

/* binary set operations */

/*
 * 	operator-(Int_set &) --
 * 	set difference operation
 */
Int_set_rep *Int_set_rep::diff(Int_set_rep *rmset)
{
	register Int_set_rep *newrep;
	register int ix;
	
	newrep = new Int_set_rep(max_bits-1);    /* max element */
	for (ix = 0; ix < word_cnt && ix < rmset->word_cnt; ix++)
		newrep->bit_vec[ix] = bit_vec[ix] & ~rmset->bit_vec[ix];

	for (ix = rmset->word_cnt; ix < word_cnt; ix++)
		newrep->bit_vec[ix] = bit_vec[ix];

	newrep->max_member = newrep->find_max(max_member);
	return (newrep);
}

/*
 * 	intersect(Int_set_rep *) --
 * 	set intersection operation
 */
Int_set_rep *Int_set_rep::intersect(Int_set_rep *mset)
{
	register Int_set_rep *newrep;
	int m_size = Int_set_min(max_bits, mset->max_bits); /* largest wd */
	register int ix;

	newrep = new Int_set_rep(m_size-1);    /* max possible element */
	for (ix = 0; ix < newrep->word_cnt; ix++)
		newrep->bit_vec[ix] = bit_vec[ix] & mset->bit_vec[ix];

	newrep->max_member = newrep->find_max(m_size);
	return (newrep);
}

/*
 * 	do_union(Int_set_rep *) --
 * 	set union operation
 */
Int_set_rep *Int_set_rep::do_union(Int_set_rep *mset)
{
	register Int_set_rep *newrep;
	register int ix;
	int minval = Int_set_min(word_cnt, mset->word_cnt);

	newrep = new Int_set_rep(Int_set_max(max_bits, mset->max_bits)-1);

	// this may copy too much
	for (ix = 0; (ix < minval) && (ix < newrep->word_cnt); ix++)
		newrep->bit_vec[ix] = bit_vec[ix] | mset->bit_vec[ix];

	if (word_cnt > mset->word_cnt) {
		for (ix = mset->word_cnt; ix < newrep->word_cnt; ix++)
			newrep->bit_vec[ix] = bit_vec[ix];
	}
	else {
		for (ix = word_cnt; ix < newrep->word_cnt; ix++)
			newrep->bit_vec[ix] = mset->bit_vec[ix];
	}
	newrep->max_member = Int_set_max(max_member, mset->max_member);
	return(newrep);
}

/*********************************************************************/
/*   Int_set functions                                                */
/*********************************************************************/

Int_set::Int_set(int head, int ...) {
    va_list args;
    int val, max_val;
    

		/* how big a set is needed? */
	max_val = head;
    va_start(args,head);
	for(val = va_arg(args,int); val >= 0; val = va_arg(args,int)){
        if (val > max_val) 
			max_val = val;
	}

		/* create a rep. big enough for largest */
    rep = new Int_set_rep(max_val);
    rep->refcnt++;
	rep->max_member = max_val;

		/* add the members for initialization */
    rep->set_member(head);
    va_start(args,head);
	for(val = va_arg(args,int); val >= 0; val = va_arg(args,int))
        rep->set_member(val);
    va_end(args);
}


/*******************************************************************/
/*  these ops do not change the representation                     */
/*******************************************************************/

/*
 * 	includes(int) --
 * 	check if the set includes the given element
 */
unsigned int Int_set::includes(register int member)
{
	register int ix;

	if ((member > rep->max_member) || (member < 0)) return(0); /* not in set! */

	ix = member / bits_in_word; /* in this byte */
	member = member - (ix * bits_in_word); /* this bit in byte */

	if ((rep->bit_vec[ix] & (1 << member)) != 0) return(1);
	else return(0);
}

/*
 * 	cardinality() --
 * 	return the number of 1's in the set
 */
int Int_set::cardinality()
{
	int size = 0;
	register int last_ix, ix, i;

	last_ix = rep->max_member / bits_in_word; /* byte.. */
	for (ix = 0; ix <= last_ix; ix++) {/* don't count past biggest */
		for (i = 0; i < bits_in_word; i++) {
			if (rep->bit_vec[ix] & (1 << i)) size++;
		}
	}
	return(size);
}

/*
 * 	compare(Int_set &) --
 * 	compare returns 0 if the sets are equal,
 * 	-1 if *this is lexicographically less than m ("poker hand" comparison),
 * 	and 1 if *this is lexicographically greater than m.
 */
int Int_set::compare(Int_set &m)
{
	register int i;

	if (this->rep == m.rep) return(0);    /* same set */

	if (rep->max_bits <= m.rep->max_bits) {
		for (i = m.rep->word_cnt - 1; i >= rep->word_cnt; i--)
			if (m.rep->bit_vec[i]) return(-1);
		for (i = rep->word_cnt - 1; i >= 0; i--)
			if (rep->bit_vec[i] != m.rep->bit_vec[i])
			{
				return(rep->bit_vec[i] - m.rep->bit_vec[i]);
			}
	}
	else {
		for (i = rep->word_cnt - 1; i >= m.rep->word_cnt; i--)
			if (rep->bit_vec[i]) return(1);
		for (i = m.rep->word_cnt - 1; i >= 0; i--)
			if (rep->bit_vec[i] != m.rep->bit_vec[i])
			{
				return(rep->bit_vec[i] - m.rep->bit_vec[i]);
			}
	}

	return(0);
}

/*
 * 	is_subset_of(Int_set &) --
 * 	returns true if *this is contained by m
 */
unsigned int Int_set::is_subset_of(Int_set &m)
{
	register int i;
	int last_block;

	if (is_empty()) return(1);      /* cheap test */
	if (rep == m.rep) return(1);   /* equal */
	if (rep->max_member > m.rep->max_member) return(0); /* another cheapie */

	/* cheap didn't work, have to do the ugly stuff */
	last_block = Int_set_min(rep->word_cnt, m.rep->word_cnt);

	for (i = 0; i < last_block; i++)
		if ((rep->bit_vec[i] ^ m.rep->bit_vec[i]) & rep->bit_vec[i]) return(0);

	// if max_bits > m.max_bits, we still don't need to look
	// further as we know its max member isn't bigger than m's
	return(1);
}

/**************************************************/
/* These Int_set ops may change the representation */
/**************************************************/

/*
 * 	grow(int) --
 * 	used to expand maximum size of set, could also shrink it.
 *   If this is rep used by one set, do in place, else do to NEW rep
 */
void Int_set::grow(int words)
{
    if (words <= rep->word_cnt) return();  /* no grow needed, so no change */

	if (rep->refcnt > 1){             /* split it */
		Int_set_rep *oldrep = rep;

		rep->refcnt--;
		rep = new Int_set_rep(oldrep);
		rep->refcnt++;
	}

	rep->grow(words);
}

/*
 * 	make_empty() --
 * 	make this set the empty set by setting everything to zero
 */
void Int_set::make_empty()
{
		// if more than one ptr to this, need a new rep
		// else: use old one
	if (rep->refcnt > 1){
		rep->refcnt--;   /* not the same now */
		rep = new Int_set_rep((rep->word_cnt * bits_in_word) - 1);
                               /* arg is largest ELEMENT */
		rep->refcnt++;
	}
	else   // in place
		memset((char *)rep->bit_vec, 0, rep->word_cnt * sizeof(unsigned int));
	rep->max_member = -1;
}

/*
 * 	add( int, int ...)
 * 	add the elements in arg list to the set, last must be neg ... 
 *   list must have -1 terminator;  (any neg will do... )
 */
void Int_set::add(int head, int ...)
{
    va_list args;
    
    register int new_max;
    register int mem_val;

    new_max = head;
    if (new_max < 0)  /* adding empty list, s'alright */
        return();         /* nothing to add */
 
    /* find largest member in list first... */
    va_start(args,head);
	for(mem_val = va_arg(args,int); mem_val >= 0; mem_val = va_arg(args,int))
        if (mem_val > new_max) 
			new_max = mem_val;
 
    if (rep->refcnt > 1){   /* split rep id shared rep */
        rep->refcnt--;   /* not the same now */
        rep = new Int_set_rep(rep);
        rep->refcnt++;
    }

    if (new_max >= rep->max_bits){  /* create big enough for max_member */
        grow(total_words(new_max));
    }
	if(new_max > rep->max_member)
    	rep->max_member = new_max;
        /* add all the new members to the list */
    rep->set_member(head);

    va_start(args,head);
    for(mem_val = va_arg(args,int); mem_val >= 0; mem_val = va_arg(args,int)){
        rep->set_member(mem_val);
    }
    va_end(args);
}

/*
 * 	add( int *)
 * 	add the elements in int list to the set, 
 *   list must have -1 terminator;  (any neg will do... )
 */
void Int_set::add(int* mem_list)
{
	register int new_max;
	register int *mem_ptr;       

	new_max = -1;

	/* find largest member in list first... */
	for (mem_ptr = mem_list; *mem_ptr >=0; mem_ptr++){
		if (*mem_ptr > new_max) new_max = *mem_ptr;
	}

	if (new_max < 0) { /* adding empty list, s'alright */
		return();         /* nothing to add */
	}
	if (rep->refcnt > 1){   /* split rep id shared rep */
		rep->refcnt--;   /* not the same now */
		rep = new Int_set_rep(rep);
		rep->refcnt++;
	}

	if (new_max >= rep->max_bits){  /* create big enough for max_member */
		grow(total_words(new_max));
	}
	if (new_max > rep->max_member)
		rep->max_member = new_max;

		/* add all the new members to the list */
	for (mem_ptr = mem_list; *mem_ptr >= 0; mem_ptr++){
		rep->set_member(*mem_ptr);
	}
}


/*
 * 	fill_range(int, int) --
 * 	set bits int the range first to last
 * 	if last is too big to fit, grow the set
 */
void Int_set::fill_range(int first, int last)
{
	register int ix;
	int fword, lword;
	int fbits, lbits;

	if ((first < 0) || (last < 0)) {
		cerr <<"Int_set::fill_range("<<first<<","<<last
			<<") ... arguments must not be negative.  Command ignored.\n";
		return;
	}
	if (last < first) return;

	// Do this in place if rep is unique, copy then do it otherwise
	if (rep->refcnt > 1){
		Int_set_rep *old_rep = rep;
		rep->refcnt--;   /* not the same now */
		rep = new Int_set_rep(old_rep);
		rep->refcnt++;
	}

	if (last >= rep->max_bits)/* need to grow */
		rep->grow(total_words(last));

	fword = first / bits_in_word; /* first word to fill */
	fbits = first % bits_in_word; /* bit to start 	*/
	lword = last / bits_in_word;
	lbits = last % bits_in_word;

	if (fword == lword) {/* range all in one word */
		unsigned int tempvec = full_word;
		tempvec >>= (bits_in_word + fbits - lbits - 1);
		tempvec <<= fbits;
		rep->bit_vec[fword] |= tempvec;
	}
	else {/* do 1st wd, intermediate wds, last wd */
		rep->bit_vec[fword] |= (full_word << fbits);

		for (ix = fword++; fword < lword; fword++)
			rep->bit_vec[fword] = full_word;

		unsigned int tempvec = full_word;
		tempvec >>= (bits_in_word - lbits - 1);
		rep->bit_vec[lword] |= tempvec;
	}
	if (last > rep->max_member) rep->max_member = last;
}

/*
 * 	remove member, adjust max_member if needed
 *  remove (int, int =-1 ...)
 *    remove args from set, last arg MUST be a negative number
 */
void Int_set::remove(int head, int ...)
{
    va_list args;
    register int mem_val;

    if (head < 0) {
        return (); /* no change, nothing removed */
    }

    if (rep->refcnt > 1){   /* split rep id shared rep */
        rep->refcnt--;   /* not the same now */
        rep = new Int_set_rep(rep);
        rep->refcnt++;
    }

    rep->clear_member(head);

    va_start(args,head);
    for( mem_val = va_arg(args,int);mem_val >= 0; mem_val = va_arg(args, int)){
        rep->clear_member(mem_val);
    }
    // look for new largest starting at byte containing old largest
    rep->max_member = find_max(rep->max_member);
    va_end(args);
}

/*
 * 	remove( int *)
 * 	remove the elements in int list from the set, 
 *   ignore any bigger than present max
 *   list must have -1 terminator;  (any neg will do... )
 */
void Int_set::remove(int* mem_list)
{
	register int *mem_ptr;       

	if (rep->max_member < 0) return();    /* empty set */

	if (rep->refcnt > 1){   /* split rep id shared rep */
		rep->refcnt--;   /* not the same now */
		rep = new Int_set_rep(rep);
		rep->refcnt++;
	}
		/* remove all the list members from the list */
	for (mem_ptr = mem_list; *mem_ptr >= 0; mem_ptr++){
		if (*mem_ptr <= rep->max_member){
			rep->clear_member(*mem_ptr);
		}
	}
	rep->max_member = find_max(rep->max_member);
}

/*
 * 	clear_range(int, int) --
 * 	clear bits in the range first to last
 */
void Int_set::clear_range(int first, int last)
{
	register int ix;
	int fword, lword;
	int fbits, lbits;

	if ((first < 0) || (last < 0)) {
		cerr<<"Int_set::clear_range("<<first<<","<<last
			<<") ... arguments must not be negative.  Command ignored.\n";
		return;
	}
	if (last < first) return;


	// Do this in place if rep is unique, copy then do it otherwise
	if (rep->refcnt > 1){
		Int_set_rep *old_rep = rep;
		rep->refcnt--;   /* not the same now */
		rep = new Int_set_rep(old_rep);
		rep->refcnt++;
	}

	if (rep->max_bits < last)/* don't clear beyond end */
		last = rep->max_bits - 1;

	fword = first / bits_in_word; /* first word to fill */
	fbits = first % bits_in_word; /* bit to start 	*/
	lword = last / bits_in_word;
	lbits = last % bits_in_word;

	if (fword == lword) {/* range all in one word */
		unsigned int tempvec = full_word;
		tempvec >>= (bits_in_word + fbits - lbits - 1);
		tempvec <<= fbits;
		rep->bit_vec[fword] &= ~tempvec;
	}
	else {/* do 1st wd, intermediate wds, last wd */
		rep->bit_vec[fword] &= ~(full_word << fbits);

		for (ix = fword++; fword < lword; fword++)
			rep->bit_vec[fword] = 0;

		unsigned int tempvec = full_word;
		tempvec >>= (bits_in_word - lbits - 1);
		rep->bit_vec[lword] &= ~tempvec;
	}
	if ((rep->max_member <= last) && (rep->max_member >= first)) {/* needs adjusting */
		rep->max_member = find_max(first);
	}
}

/*************************************************************/
/*     iostream Set Operators                                */
/*************************************************************/


iostream &operator<<(iostream &outfile, Int_set& dset)
{
	register int i, j;

	if (INTSET_DBG){
		outfile<<"(word_count = " << dset.rep->word_cnt 
			   << ", max_member = " << dset.rep->max_member
			   << ", max_bits = " << dset.rep->max_bits <<") ";
	}
	outfile << "[";

	int curval = 0;
	int isfirst = 1;

	for (i = 0; i < dset.rep->word_cnt; i++) {
		if (dset.rep->bit_vec[i] == 0) {
			curval += bits_in_word;
		}
		else {
			int tmpword = dset.rep->bit_vec[i];
			for (j = 0; j < bits_in_word; j++) {
				if (tmpword & 01)
				{
					if (isfirst) isfirst = 0;
					else outfile<<" ";

					outfile << curval;
				}
				curval++;
				tmpword >>= 1;
			}
		}
	}
	outfile <<"]";
	return(outfile);
}
