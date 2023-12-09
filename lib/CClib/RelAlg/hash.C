#ident "@(#) /sable/sdb/ra/rel/tuple/s.hash.C"
/*      Copyright (c) 1989,1991 AT&T - All Rights Reserved */

#include <relation.h>

typedef Tuple *PTuple;

Tuple_Hash::Tuple_Hash(Hashindex cardinality)
{
power=1;
for ( _size=2; _size < cardinality; _size <<= 1 )
   power++;
_size <<= 2;
mask = _size-1;
rel_prime = mask >> power++;
table = new PTuple[_size?_size:1];
memset(table,0,(int)(sizeof(PTuple) * _size));
}

Tuple_Hash::~Tuple_Hash()
{
for ( int i=0; i < _size; i++ )
   if ( table[i] )
      table[i]->done();
delete table;
}

Hashindex Tuple_Hash::hash(char *start,Dlength length,
                          register Hashindex startval)
{
register char *c = start;
for ( Dlength i=0; i < length-1; i++ )
   startval = crunch(startval,*c,*(++c));
startval= crunch(startval,*c,*start) * rel_prime;
const unsigned NBITS=32;
Hashindex result = startval;
for ( Hashindex shaft=power; shaft < NBITS; shaft *= 2 )
   result ^= (startval >> shaft);
return result&mask;
}

Boolean_t Tuple_Hash::insert(Tuple *tuple,Hashindex start)
{
Hashindex slot=start;
if ( start >= _size ) return FALSE;
while ( table[slot] )
   {
   slot = (slot+1) & mask;
   if ( slot == start )
      return FALSE; // table full
   }
tuple->share();
table[slot] = tuple;
return TRUE;
}

ostream & operator<<(ostream &s,Tuple_Hash &h)
{
s << "Hash table size: " << h._size << " mask: " << h.mask << " rel_prime: "
       << h.rel_prime << " power: " << h.power << "\n";
for ( int i=0; i < h._size; i++ )
   if (h.table[i])
      s << i << ": " << h.table[i];
   else s << i << ": " << "<NULL>\n";
return s;
}

Hashindex Tuple_Hash::crunch(register Hashindex result,
                register const char b1,register const char b2)
{
return (result ^ ((b1&HASHMASK) << ((b2&SHIFTMASK)<<SHIFTBY)));
}
