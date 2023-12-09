/*
Here is the code for member functions of the base Hmap and Hmapiter classes,
_Hmap_ and _Hmapiter_.  Everything that could be made common to all h-maps was
put here, to avoid the need for duplicating common code for each type of h-map.
Also included is a routine for hashing a word, which is used by most of the
pre-defined hash functions.

Deciding upon the number of buckets to allocate for an h-map under various
circumstances is a bit of a black art, and has purposefully not been fully
defined in the interface.  Here I describe how things are done in the current
implemention.  If the h-map is initialized with the 5 parameter constructor,
computing the size is straightforward -- allocate enough buckets so that the
maximum load factor won't be exceeded until 10% more elements have been
inserted than the number specified.  Since all bucket sizes come from a table
of primes, the actual size used is the smallest prime in the table that
satisfies this condition.  (I'm assuming throughout that the bucket limit isn't
exceeded.  If it is, you use the limit.)  The number of buckets an h-map gets
when it's initialized in this way is called its "original bucket count."

What about when h-map m is assigned the value of h-map n?  How many buckets
should m have?  The method used is as follows:  Compute how many buckets m
"ought" to have, using the procedure above applied to the number of elements
currently in n.  Use either that quantity or m's original bucket count,
whichever is larger.  The rationale here is that if m was created with a given
size, you probably want it to really be (at least) that big for as long as it
exists; you don't want to be surprised by a lot of expensive resizing caused by
the assignment of n's elements shrinking m well below its usual size.

What about when h-map m is initialized from h-map n?  In this case m's
"original bucket count" is set to n's original bucket count, and then the
actual number of buckets for m is computed as for assignment.  Thus m might
never have actually had a number of buckets as small as its "original"
bucket count.  This may seem bizarre but the rationale here is that m should
inherit all the properties of n, and the original bucket count (specified
indirectly through the size parameter) is an intrinsic property just like
the maximum load factor, bucket limit, and growth exponent.

Comments on freeze() and thaw()

The semantics of iterators aren't as clean as they could be.  The need to
freeze an h-map so as to ensure that successive enumerations return the
elements in the same order is a kludge.  The need for the kludge is a
consequence of two things:

(1)  The use of the move-to-front heuristic whenever an element in a
     non-frozen h-map is accessed by [], element, or contains.
(2)  The fact that the iterators travel along the same pointers that are
     used to implement bucket lists.

An internal consequence of (1) and (2) is the need to maintain for each h-map a
count of how many of its iterators are non-vacuous.  (A map is effectively
frozen so long as at least one of its iterators is non-vacuous.)

The best way to eliminate the kludge is to do iteration via a separate doubly
linked list of the elements that is independent of the bucket lists.  This
imposes a cost of two pointers per node.  There would still be a reason why
you'd like to be able to disable the move-to-front rule -- on a machine with
multiple processors and shared memory you'd like to have one copy of an h-map
that all processors can read, and without the overhead of locking schemes.
This isn't possible if an access operation like [] causes pointers to change
"inside".
*/

#include "Hmap.h"

/*
Hmap_word_hash provides a generic way to hash a word, where a word is defined
as an unsigned int.  Odd/even pairs of bits are exchanged.  When taken modulo a
prime (as is done when the bucket number is computed) this gives a decent hash.
The main problem is to break up arithmetic sequences whose increment is
divisible by the number of buckets.  This method isn't ideal; if the keys
hashed all have the same value modulo the number of buckets the resulting
distribution is a good deal worse than random, but it's much better than what
you get when the identity function is used for the hash, since in that case all
keys hash to the same bucket.  And this hash function has the virtue of being 1
to 1, unlike most schemes based on XORing the word with some shifted version of
itself.

Incidently, when you're hashing an arithmetic sequence whose increment *isn't*
divisible by the number of buckets, you'd be better off with Hmap_word_hash
being the identity function.  This is because the bucket count is always a
prime, so such sequences would always be hashed to a completely uniform
distribution (no bucket gets n+1 elements until all others have n elements).
As it stands, swapping odd/even bits destroys this property and the result of
taking the "bit swapped" values modulo a prime gives a random distribution
rather than a completely uniform distribution.  In short, I chose to make the
nicest cases a little worse so as to keep the rarely occuring worst case from
being abominable.  I think this conservativism is appropriate for a general
purpose hash where it is impossible to predict what the data looks like.
*/

#define ONE_ZERO_PATTERN 0xAAAAAAAA /* Enough alternating 1's and 0's to */
				    /* fill a word. */
unsigned Hmap_word_hash(const unsigned i)
{
    return ((ONE_ZERO_PATTERN & i) >> 1) | ((~ONE_ZERO_PATTERN & i) << 1);
}

void _Hmap_::initialize_table()
{
/* All parameters except resize_limit have already been set.
   Resize limit is set here, and then the table is allocated
   and initialized.					     */

  if (bucket_index == max_bucket_index)
      resize_limit = UINT_MAX; // Never resize again.
  else
    {
      long temp; // Used to get around Alliant bug: unsigned -> float
		 // coercion does not work.
      // Avoid overflow on machines with 16 bit ints.
      unsigned long new_resize_limit = (unsigned long)
                        ((temp = bucket_cnt) * max_load_factor);
      if (new_resize_limit > UINT_MAX) resize_limit = UINT_MAX;
      else resize_limit = (unsigned) new_resize_limit;
    }
  bucket = new _Hmap_nodeP[bucket_cnt];
  for (register unsigned i = 0; i < bucket_cnt; i++) bucket[i] = 0;
}

_Hmap_::_Hmap_(unsigned nelements, float max_lf, unsigned max_bkts,
	       unsigned short g_step):
  max_load_factor(max_lf), growth_step(g_step),
  map_size(0), active_iters(0), frozen(0)
{
/* There's no error reporting.  If the luser gives us a bogus value for some 
   parameter we simply set it to the default and proceed.  (Except that a
   value for max_buckets that's too large is set to _HMAP_MAX_BKTS).
*/

  if (nelements == 0) nelements = _HMAP_DEFAULT_SIZE;
  if (max_load_factor <= 0.0) max_load_factor = _HMAP_DEFAULT_MAX_LF;
  if (growth_step < 1 || growth_step > 12)
    growth_step = _HMAP_DEFAULT_STEP;
  if (max_bkts > _HMAP_MAX_BKTS)
    {
      max_bucket_index = _HMAP_MAX_BKT_IX;
    }
  else if (max_bkts < 1)
    {
      max_bucket_index = _HMAP_DEF_MAX_BKT_IX;
    }
  else
    {
      for (unsigned short i = _HMAP_MAX_BKT_IX; prime(i) > max_bkts; i--);
      max_bucket_index = i;
    }
  orig_bucket_index = 0;
  set_size(nelements);
  orig_bucket_index = bucket_index;
}

_Hmap_::_Hmap_(const _Hmap_& m) :
  max_bucket_index(m.max_bucket_index), max_load_factor(m.max_load_factor),
  orig_bucket_index(m.orig_bucket_index),
  growth_step(m.growth_step), active_iters(0), frozen(0), bucket(0)
{
}

/* Set the table size to whatever's required to store nelements elements.
   Don't make it any smaller than it's initial size, however.
*/

void _Hmap_::set_size(unsigned nelements)
{
  unsigned long max_buckets = prime(max_bucket_index);
  long temp; /* Avoid Alliant bug: can't coerce unsigned -> float. */
  /* Avoid overflow. */
  unsigned long nbuckets = (unsigned long)
		((temp = nelements) / max_load_factor) + 1;
  if (nbuckets >= max_buckets)
    {
      bucket_index = max_bucket_index;
      bucket_cnt = (unsigned int) max_buckets;
    }
  else
    {
      for (register unsigned short i = 0; prime(i) < nbuckets; i++);
      bucket_index = (i > orig_bucket_index) ? i : orig_bucket_index;
      bucket_cnt = (unsigned int) prime(bucket_index);
    }
  initialize_table();
}

/* Return a prime close to 2**((10 + i)/4).  One is considered a prime here.
   We use a very liberal definition of "close" when i is small.  Works for
   0 <= i <= 115.  This routine takes about half as much space as an array of
   primes.
*/
unsigned long _Hmap_::prime(unsigned short i)
{
  static char delta[] =
    { 4,  4,  5,  4,  4,  2,  3,  2,  3,  3,  1,  1,  2,  0,  3,  3,
      1,  0,  1,  1,  0,  4,  5, 11,  3,  9,  3,  1,  5,  2,  3,  0,
      1,  1,  9, 12,  9, 11,  3,  9,  1,  5,  1,  2,  6, 14,  3,  0,
      3,  3, 19,  8,  3,  5, 15,  2,  0, 34,  1,  8,  0, 14,  5,  0,
      4,  8,  1, 10, 24,  0,  3, 11,  3, 10,  9,  1,  1, 26,  3,  5,
      0, 39, 15, 19,  4, 11,  3,  5,  5,  2, 39,  8, 21,  2,  5, 21,
     16,  9, 39, 24, 24, 33, 57, 23, 15,  2,  3, 31, 13,  7, 35, 28,
     36, 38,  1, 15
    };
  static unsigned long magic[4] =
		{1518500249,  /* approx. 2**(122/4) */
		 1805811301,  /* approx. 2**(123/4) */
		 2147483648,  /* approx. 2**(124/4) */
		 2553802834}; /* approx. 2**(125/4) */
  return (magic[i & 03] >> (28 - (i >> 2))) - delta[i];
}

/* This only works when wrapped inside a derived class.  It doesn't create
   the new links, which requires knowing the type of the key and its hash
   function.
*/
void _Hmap_::resize_table()
{
  if ((bucket_index += growth_step) > max_bucket_index)
    bucket_index = max_bucket_index;
  bucket_cnt = (unsigned int) prime(bucket_index);
  initialize_table();
}

_Hmapiter_::_Hmapiter_(const _Hmapiter_ &iter)
{
  m = iter.m;
  b = iter.b;
  if (p = iter.p) m->active_iters++;
}

_Hmapiter_& _Hmapiter_::operator=(const _Hmapiter_& iter)	
{
  if (this != &iter)
    {
      if (p) m->active_iters--;
      m = iter.m;
      b = iter.b;
      if (p = iter.p) m->active_iters++;
    }
  return *this;
}

_Hmapiter_& _Hmapiter_::operator++()
{
  if (p)
    {
      p = p->next;
      if (p) return *this;
      for (b++; b < m->bucket_cnt; b++)
      	if (m->bucket[b]) {p = m->bucket[b]; return *this;}
      b = 0;
      m->active_iters--;
      return *this;
    }
  for (b = 0; b < m->bucket_cnt; b++)
    if (m->bucket[b])
      {
	p = m->bucket[b];
	m->active_iters++;
	return *this;
      }
  b = 0;
  return *this;
}

_Hmapiter_& _Hmapiter_::operator--()
{
  register int vacuous = (p == 0);
  if (vacuous) b = m->bucket_cnt;
  else 
    if (p == m->bucket[b]) p = 0;
    else goto scan;
  while (b) if (m->bucket[--b]) goto scan;
  if (!vacuous) m->active_iters--;
  return *this;

scan: // We have found the bucket, now find the node.
  for (register _Hmap_nodeP q = m->bucket[b]; q->next != p; q = q->next);
  p = q;
  if (vacuous) m->active_iters++;
  return *this;
}

_Hmap_nodeP _Hmapiter_::remove()
{
  if (p == 0) return (_Hmap_nodeP) 0;
  register _Hmap_nodeP q = p;
  register unsigned c = b;
  --(*this);
  if (p && b == c) p->next =  q->next;
  else m->bucket[c] = q->next;
  m->map_size--;
  return q;
}
