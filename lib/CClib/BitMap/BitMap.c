#include	<iostream.h>
#include	<iomanip.h>
#include	"BitMap.h"


const uint	BitMap::bitsPerLong = 32;
const uint	BitMap::bitsPerLongShift = 5;
const uint	BitMap::bitsPerLongMask = (1 << 5) - 1;


Blockimplement(ulong);

Objection	BitMap::NoSpace(abortObjection);
Objection	BitMap::BadFree(abortObjection);
Objection	BitMap::BadTake(abortObjection);
Objection	BitMap::FileError(abortObjection);


/*  The constructor.
*/

BitMap::
BitMap(ulong base, uint chunksize, uint alloc) : bits(0)
{
	register int	cnt;
	register int	ndx;
	
	nbrChunks = 0;
	baseValue = base;
	
	/*  Compute the chunk shift.
	*/
	
	cnt = chunksize;
	ndx = 0;
	while(cnt >>= 1){
		ndx += 1;
	}
	
	/*  If the specified chunk size is not a power of 2, increase it to the
	**  next higher power of 2.
	*/
	
	if((1 << ndx) < chunksize){
		ndx++;
		assert((1 << ndx) > chunksize);
	} else {
		assert((1 << ndx) == chunksize);
	}
	
	chunkSize = 1 << ndx;
	chunkShift = ndx;
	chunkMask = (1 << chunkShift) - 1;
	
	/*  Do the initial allocation.
	*/
	
	size(alloc);
}


/*  Basic functions for manipulating the map.
*/

long  BitMap::
allocate(register uint units, uint incr)
{
	register uint	need;
	register int	got;
	register uint	ndx;
	register uint	limit;
	
	/*  If only one chunk is needed, allocate the first available bit
	**  starting from the end.  Otherwise, look for the first range which
	**  is large enough starting from the front.  This is an attempt to
	**  reduce fragmentation.
	*/
	
	need = unitsToChunks(units);
	if(need == 1){
		while((got = getHighChunk(bits.size() - 1)) < 0  &&  incr){
			grow(incr);
		}
		if(got >= 0){
			allocChunk(got);
		}
	} else {
		while((got = getChunks(0, need)) < 0  &&  incr){
			grow(incr);
		}
		if(got >= 0){
			limit = got + need;
			for(ndx = got; ndx < limit; ndx++){
				allocChunk(ndx);
			}
		}
	}
	
	if(got < 0){
		NoSpace.raise("BitMap::allocate - Out of space");
		return -1;
	} else {
		return baseValue + chunksToUnits(got);
	}
}

/*  The "sequential" allocation routine.
*/

long  BitMap::
sequential(uint units, uint incr)
{
	register uint		need;
	register int		chunk;
	register uint		ndx;
	uint			limit;
	
	need = unitsToChunks(units);
	
	if(need == 1){
		while((chunk = getLowChunk(0)) < 0  &&  incr){
			grow(incr);
		}
		if(chunk >= 0){
			allocChunk(chunk);
		}
	} else {
		while((chunk = getChunks(0, need)) < 0  &&  incr){
			grow(incr);
		}
		if(chunk >= 0){
			limit = chunk + need;
			for(ndx = chunk; ndx < limit; ndx++){
				allocChunk(ndx);
			}
		}
	}
	
	if(chunk == -1){
		NoSpace.raise("BitMap::bestFit - Out of space");
		return -1;
	}
	
	return baseValue + chunksToUnits(chunk);
}

/*  The "best fit" allocation routine.
*/

long  BitMap::
bestFit(uint units, uint incr)
{
	register uint		need;
	register int		best;
	register uint		bestSize;
	register int		chunk;
	register uint		ndx;
	uint			size;
	
	need = unitsToChunks(units);
	if(need == 1){
		return allocate(units, incr);
	}
	
	best = -1;
	bestSize = nbrChunks + 1;
	chunk = 0;
	
	while(1){
		while(1){
			chunk = getRange(chunk, size);
			if(chunk < 0){
				break;
			}
			if(size >= need  &&  size < bestSize){
				best = chunk;
				bestSize = size;
			}
			chunk += size;
		}
		if(best >= 0  || incr == 0){
			break;
		}
		grow(incr);
	}
	
	if(best == -1){
		NoSpace.raise("BitMap::bestFit - Out of space");
		return -1;
	}
	
	for(ndx = best; ndx < best + need; ndx++){
		allocChunk(ndx);
	}
	
	return baseValue + chunksToUnits(best);
}

void  BitMap::
take(register ulong start, uint units)
{
	register uint	realStart;
	register uint	need;
	register uint	startChunk;
	register uint	ndx;
	register uint	limit;
	
	if(start < baseValue){
		BadTake.raise("BitMap::take - bad starting unit number");
		return;
	}
	realStart = uint(start - baseValue) & ~chunkMask;
	startChunk = unitsToChunks(realStart);
	units = chunksToUnits(unitsToChunks(units));
	limit = unitsToChunks(realStart + units);
	need = limit - startChunk;
	if(need == 1){
		if(!isAvail(startChunk)){
			BadTake.raise("BitMap::take - unit already allocated");
			return;
		}
		allocChunk(startChunk);
		return;
	}
	
	for(ndx = startChunk; ndx < limit; ndx++){
		if(!isAvail(ndx)){
			BadTake.raise("BitMap::take - unit already allocated");
			return;
		}
	} 
	for(ndx = startChunk; ndx < limit; ndx++){
		allocChunk(ndx);
	}
}

void  BitMap::
free(register ulong start, uint units)
{
	register uint	firstUnit;
	register uint	ndx;
	register uint	limit;
	
	if(start < baseValue){
		BadFree.raise("BitMap::free - start < base value");
		return;
	}
	
	firstUnit = uint((start - baseValue) & ~chunkMask);
	units = chunksToUnits(unitsToChunks(units));
	ndx = unitsToChunks(firstUnit);
	limit = unitsToChunks(firstUnit + units);
	if(limit > nbrChunks){
		BadFree.raise("BitMap::free - attempt to free past "
			      "end of pool");
		return;
	}
	
	for( ; ndx < limit ; ndx++){
		if(isAvail(ndx)){
			BadFree.raise("BitMap::free - attempt to free "
				      "unallocated chunk");
			return;
		} else {
			freeChunk(ndx);
		}
	}
}

void  BitMap::
size(register uint newSize)
{
	register uint	ndx;
	
	newSize = unitsToChunks(newSize);
	
	bits.size(chunksToWords(newSize));
	
	/*  Mark the newly allocated chunks as available.  If the number of
	**  chunks is not a multiple of bitsPerLong, we must mark the last bits
	**  of the last word as allocated so they won't be used.
	*/
	
	ndx = nbrChunks;
	for( ; ndx < newSize  &&  (ndx & bitsPerLongMask); ndx++){
		freeChunk(ndx);
	}
	for( ; ndx < newSize; ndx += bitsPerLong){
		bits[chunksToWords(ndx)] = ~0;
	}
	nbrChunks = newSize;
	for(ndx = nbrChunks; ndx & bitsPerLongMask; ndx++){
		allocChunk(ndx);
	}
}

/*  Find the highest bit that is off.  This is the highest allocated chunk.
*/

long  BitMap::
highest(void) const
{
	register int	chunk;
	
	chunk = getHighest(bits.size() - 1);
	return baseValue + chunksToUnits(chunk + 1) - 1;
}

uint  BitMap::
isAllocated(register ulong unit) const
{
	register uint		firstUnit;
	
	if(unit < baseValue){
		return 0;
	}
	firstUnit = uint((unit - baseValue) & ~chunkMask);
	return !isAvail(unitsToChunks(firstUnit));
}

uint  BitMap::
diskSize(void)
{
	register uint	size;
	
	size = sizeof(uint) + sizeof(ulong) * bits.size();
	size += sizeof(nbrChunks) + sizeof(baseValue) + sizeof(chunkSize);
	size += sizeof(chunkShift) + sizeof(chunkMask);
	return size;
}

void  BitMap::
read(register istream& is)
{
	register ulong*		ulp;
	uint			cnt;
	
	is.read((char*)&cnt, sizeof(cnt));
	bits.size(cnt);
	ulp = bits;
	is.read((char*)ulp, cnt * sizeof(ulong));
	is.read((char*)&nbrChunks, sizeof(nbrChunks));
	is.read((char*)&baseValue, sizeof(baseValue));
	is.read((char*)&chunkSize, sizeof(chunkSize));
	is.read((char*)&chunkShift, sizeof(chunkShift));
	is.read((char*)&chunkMask, sizeof(chunkMask));
	
	if(!is.good()){
		FileError.raise("BitMap::read - I/O error");
	}
}

void  BitMap::
write(register ostream& os)
{
	register ulong*		ulp;
	uint			cnt;
	
	cnt = bits.size();
	ulp = bits;
	os.write((char*)&cnt, sizeof(cnt));
	os.write((char*)ulp, cnt * sizeof(ulong));
	os.write((char*)&nbrChunks, sizeof(nbrChunks));
	os.write((char*)&baseValue, sizeof(baseValue));
	os.write((char*)&chunkSize, sizeof(chunkSize));
	os.write((char*)&chunkShift, sizeof(chunkShift));
	os.write((char*)&chunkMask, sizeof(chunkMask));
	
	if(!os.good()){
		FileError.raise("BitMap::write - I/O error");
	}
}

void  BitMap::
print(register ostream& os) const
{
	register long		first;
	register long		next;
	ulong			val;
	BitMapIter		bmi(*this);
	
	os << "Map size = " << size() << " units." << endl;
	os << "Chunk size = " << chunkSize << " unit";
	os << (chunkSize > 1 ? "s." : ".") << endl;
	os << "Base = " << baseValue << " unit";
	os << (baseValue > 1 ? "s." : ".") << endl;
	
	os << "Allocated units:\tstart  next   nbr\n";
	first = -1;
	
	while(bmi.next(val)){
		if(first == -1){
			first = val;
			next = first + chunkSize;
			continue;
		}
		if(val == next){
			next += chunkSize;
			continue;
		}
		os << "\t\t\t";
		os << setw(5)  << first << " ";
		os << setw(5) << next << " ";
		os << setw(5) << next - first;
		os << endl;
		first = val;
		next = first + chunkSize;
	}
	
	if(first != -1){
		os << "\t\t\t";
		os << setw(5)  << first << " ";
		os << setw(5) << next << " ";
		os << setw(5) << next - first;
		os << endl;
	}
}


/*  Find the first contiguous range of chunks of the requested size.  Begin
**  the search at the requested chunk number.
*/

int  BitMap::
getChunks(register uint firstChunk, register uint need) const
{
	register uint	ndx;
	register uint	limit;
	
	while(firstChunk < nbrChunks){
		if(!isAvail(firstChunk)){
			firstChunk++;
			continue;
		}
		
		limit = firstChunk + need;
		ndx = firstChunk + 1;
		for( ; ndx < limit; ndx++){
			if(!isAvail(ndx)){
				break;
			}
		}
		
		if(ndx == limit){
			return firstChunk;
		}
		firstChunk = ndx + 1;
	}
	
	return -1;
}


/*  Look for a contiguous range of available chunks starting at "firstChunk".
**  Return the range size in "size" and the number of the first chunk as the
**  value of the function.  Return -1 if no range is found.
*/

int  BitMap::
getRange(register uint firstChunk, register uint& size) const
{
	register uint		ndx;
	
	while(!isAvail(firstChunk)  &&  ++firstChunk < nbrChunks){
	}
	
	if(firstChunk >= nbrChunks){
		return -1;
	}
	
	for(ndx = firstChunk; isAvail(ndx); ndx++){
	}
	
	size = ndx - firstChunk;
	return firstChunk;
}


/*  Find highest order bit that is on, and is within or below the word
**  specified by "word".  Uses fast binary search.
**
**  NOTE:  assumes 32 bit word size.
*/

int  BitMap::
getHighChunk(register uint word) const
{
	register ulong	bts;
	register int	chunk;

	while((bts = bits[word]) == 0){
		if(word == 0){
			return -1;
		}
		word--;
	}
	
	chunk = wordsToChunks(word);
	chunk |= getHighBit(bts);
	return chunk;
}

int  BitMap::
getHighest(register uint word) const
{
	register ulong	bts;
	register int	chunk;

	while((bts = bits[word]) == ~0){
		if(word == 0){
			return -1;
		}
		--word;
	}
	chunk = wordsToChunks(word);
	
	/*  If we are using the last word of bits, then free the bits above the
	**  total size.  They are not really allocated, they have just been
	**  marked that way to prevent them from being allocated.
	*/
	
	if(word == (bits.size() - 1)){
		ulong	mask;
		
		mask = (1 << (nbrChunks % wordsToChunks(1))) - 1;
		if(mask != 0){
			bts |= ~mask;
		}
	}
	chunk |= getHighBit(~bts);
	return chunk;
}

int  BitMap::
getHighBit(register ulong bts) const
{
	if(bts & 0xffff0000){
		if(bts & 0xff000000){
			if(bts & 0xf0000000){
				if(bts & 0xc0000000){
					if(bts & 0x80000000){
						return 31;
					} else {
						return 30;
					}
				} else if(bts & 0x20000000){
					return 29;
				} else {
					return 28;
				}
			} else if(bts & 0x0c000000){
				if(bts & 0x08000000){
					return 27;
				} else {
					return 26;
				}
			} else if(bts & 0x02000000){
				return 25;
			} else {
				return 24;
			}
		} else if(bts & 0x00f00000){
			if(bts & 0x00c00000){
				if(bts & 0x00800000){
					return 23;
				} else {
					return 22;
				}
			} else if(bts & 0x00200000){
				return 21;
			} else {
				return 20;
			}
		} else if(bts & 0x000c0000){
			if(bts & 0x00080000){
				return 19;
			} else {
				return 18;
			}
		} else if(bts & 0x00020000){
			return 17;
		} else {
			return 16;
		}
	} else if(bts & 0x0000ff00){
		if(bts & 0x0000f000){
			if(bts & 0x0000c000){
				if(bts & 0x00008000){
					return 15;
				} else {
					return 14;
				}
			} else if(bts & 0x00002000){
				return 13;
			} else {
				return 12;
			}
		} else if(bts & 0x00000c00){
			if(bts & 0x00000800){
				return 11;
			} else {
				return 10;
			}
		} else if(bts & 0x00000200){
			return 9;
		} else {
			return 8;
		}
	} else if(bts & 0x000000f0){
		if(bts & 0x000000c0){
			if(bts & 0x00000080){
				return 7;
			} else {
				return 6;
			}
		} else if(bts & 0x00000020){
			return 5;
		} else {
			return 4;
		}
	} else if(bts & 0x0000000c){
		if(bts & 0x00000008){
			return 3;
		 } else {
			return 2;
		}
	} else if(bts & 0x00000002){
		return 1;
	} else {
		return 0;
	}
}


/*  Find lowest order bit that is on, and is within or above the word
**  specified by "word".  Uses fast binary search.
**
**  NOTE:  assumes 32 bit word size.
*/

int  BitMap::
getLowChunk(register uint word) const
{
	register ulong	bts;
	register int	chunk;

	while(word < bits.size()  &&  (bts = bits[word]) == 0){
		word++;
	}
	
	if(word >= bits.size()){
		return -1;
	}
	chunk = wordsToChunks(word);
	chunk |= getLowBit(bts);
	return chunk;
}

int  BitMap::
getLowBit(register ulong bts) const
{
	if(bts & 0x0000ffff){
		if(bts & 0x000000ff){
			if(bts & 0x0000000f){
				if(bts & 0x00000003){
					if(bts & 0x00000001){
						return 0;
					} else {
						return 1;
					}
				} else if(bts & 0x00000004){
					return 2;
				} else {
					return 3;
				}
			} else if(bts & 0x00000030){
				if(bts & 0x00000010){
					return 4;
				} else {
					return 5;
				}
			} else if(bts & 0x00000040){
				return 6;
			} else {
				return 7;
			}
		} else if(bts & 0x00000f00){
			if(bts & 0x00000300){
				if(bts & 0x00000100){
					return 8;
				} else {
					return 9;
				}
			} else if(bts & 0x00000400){
				return 10;
			} else {
				return 11;
			}
		} else if(bts & 0x00003000){
			if(bts & 0x00001000){
				return 12;
			} else {
				return 13;
			}
		} else if(bts & 0x00004000){
			return 14;
		} else {
			return 15;
		}
	} else if(bts & 0x00ff0000){
		if(bts & 0x000f0000){
			if(bts & 0x00030000){
				if(bts & 0x00010000){
					return 16;
				} else {
					return 17;
				}
			} else if(bts & 0x00040000){
				return 18;
			} else {
				return 19;
			}
		} else if(bts & 0x00300000){
			if(bts & 0x00100000){
				return 20;
			} else {
				return 21;
			}
		} else if(bts & 0x00400000){
			return 22;
		} else {
			return 23;
		}
	} else if(bts & 0x0f000000){
		if(bts & 0x03000000){
			if(bts & 0x01000000){
				return 24;
			} else {
				return 25;
			}
		} else if(bts & 0x04000000){
			return 26;
		} else {
			return 27;
		}
	} else if(bts & 0x30000000){
		if(bts & 0x10000000){
			return 28;
		 } else {
			return 29;
		}
	} else if(bts & 0x40000000){
		return 30;
	} else {
		return 31;
	}
}

/*  For some reason, the following two functions keep geting outlined when I
**  make them inline.
*/

uint  BitMap::
unitsToChunks(register uint units) const
{
	return (units + chunkMask) >> chunkShift;
}

uint  BitMap::
chunksToUnits(register uint chunks) const
{
	return chunks << chunkShift;
}


/*  Get the next allocated unit for the iterator.
*/

int  BitMapIter::
next(ulong& rv)
{
	for( ; nextChunk < bitMapP->nbrChunks; nextChunk++){
		if(!bitMapP->isAvail(nextChunk)){
			break;
		}
	}
	if(nextChunk >= bitMapP->nbrChunks){
		return 0;
	}
	
	rv = bitMapP->chunksToUnits(nextChunk) + bitMapP->baseValue;
	nextChunk++;
	return 1;
}
