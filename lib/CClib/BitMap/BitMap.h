#ifndef	__BitMapH
#define	__BitMapH


#include	<assert.h>
#include	<iostream.h>
#include	<Block.h>
#include	<Objection.h>
#include	"Common.h"


/*  This class performs resource allocation using a bitmap.  Resources are
**  allocated in granules or chunks of basic units.  The chunksize is one of
**  the arguments to the constructor.  The resource is assummed to be a
**  contiguous set of values (such as a range of memory or disk space).  The
**  starting value is another of the arguments to the constructor.
**
**  The code requires that the chunk size be a power of 2.  The pool of
**  resources can be grown at any time.
**
**  The chunks are represented by bits collected into unsigned longs.  A Block
**  is used to hold these ulong words.  A 1 bit represents a free chunk and a
**  0 bit an in-use chunk.
*/


Blockdeclare(ulong);


class BitMap {
		/*  Some friends of ours.
		*/
		
		friend class BitMapIter;
		
	public:
		/*  The constructor.  The arguments are:
		**
		**	base		The base value for the area being
		**			allocated.
		**	chunksize	The chunk size.  Allocation requests
		**			will be rounded up to the next multiple
		**			of this size.  Each bit in the map will
		**			represent this many basic "units" (such
		**			as bytes of disk space.)  This should
		**			be specified as a power of 2.  If it is
		**			not, the next higher power of two will
		**			be used.
		**	alloc		An optional initial allocation in
		**			"units".  Space can be added later by
		**			calling "size" or "grow".  This should
		**			be a multiple of the chunk size.  If
		**			not, the next higher chunk size multiple
		**			will be used.
		*/
		
		BitMap(ulong base = 0, uint chunksize = 1, uint alloc = 0);
		
		
		/*  Basic functions for manipulating the map.
		*/
		
		long		allocate(uint units = 1, uint incr = 0);
					// Allocate the requested number of
					// units using the first-fit algorithm.
					// If "units" is not a multiple of the
					// chunk size, it will be rounded up to
					// the next chunk size multiple.  Raises
					// objection BitMap_NoSpace on failure
					// unless an "incr" is specified.
					// The recovery action is to return -1.
					
		long		sequential(uint units = 1, uint incr = 0);
					// Allocate the requested number of
					// units using the sequential algorithm.
					// If "units" is not a multiple of the
					// chunk size, it will be rounded up to
					// the next chunk size multiple.  Raises
					// objection BitMap_NoSpace on failure
					// unless an "incr" is specified.
					// The recovery action is to return -1.
					
		long		bestFit(uint units = 1, uint incr = 0);
					// Allocate the requested number of
					// units using the best-fit algorithm.
					// If "units" is not a multiple of the
					// chunk size, it will be rounded up to
					// the next chunk size multiple.  Raises
					// objection BitMap_NoSpace on failure
					// unless an "incr" is specified.
					// The recovery action is to return -1.
					
		void		take(ulong start, uint units = 1);
					// Mark as allocated the "units" number
					// of units starting at "start".  Raise
					// the BadTake Objection if any of these
					// units are already allocated.
					
		void		free(ulong start, uint units = 1);
					// Free up some previously allocated
					// space.  If "start" is not a multiple
					// of the chunk size, it will be
					// truncated to a chunk size boundary.
					// If "units" is not a chunk size
					// multiple, it will be rounded up to
					// the next chunk size multiple.
		
		inline uint	size(void) const;
					// Return the current size of the map
					// in basic units.  The value returned
					// will always be a multiple of the
					// chunk size.
		
		void		size(uint newSize);
					// Change the size of the map to
					// "newSize" basic units.  If it is not
					// a multiple of the chunk size, it 
					// will be rounded up.

		long		highest(void) const;
					// Return the highest allocated unit.
					
		inline void	grow(uint incr);
					// Grow the map to hold the specified
					// number of additional units.  If
					// "incr" is not a multiple of the
					// chunk size, it will be rounded up.
					
		inline ulong	base(void) const;
					// Returns the base value being used by
					// the map.
					
		inline uint	chunk(void) const;
					// Returns the chunk size being used by
					// the map.
					
		uint		isAllocated(ulong unit) const;
					// Returns TRUE if the indicated unit
					// is allocated (contained in an
					// allocated chunk) and FALSE otherwise.
		
		uint		diskSize(void);
					// Returns the number of bytes of disk
					// space read by "read" or written by
					// "write" for the map.
		
		void		read(istream& is);
					// Read a BitMap from the stream.
					// Raises objection BitMap_IO_Error.
					// Recovery is to return with an empty
					// bitmap.
					
		void		write(ostream& os);
					// Write out the BitMap to the stream.
					// Raises objection BitMap_IO_Error.
					// Recovery is to just return.
					
		void		print(ostream& os) const;
					// Print some information about the map.
					// Intended for debugging only.
	
	protected:
		/*  Some useful internal functions.  Not intended to be used
		**  by our clients.
		*/
		
		int		getChunks(uint firstChunk, uint need) const;
					// Find "need" contiguous free chunks
					// beginning the search at the indicated
					// "firstChunk".  Returns the chunk 
					// number of the first chunk in the 
					// range or a negative value if none is
					// found.
					
		int		getRange(uint firstChunk, uint& size) const;
					// Find the first contiguous range of
					// available chunks starting the search
					// with chunk "firstChunk".  If none is
					// found, return a negative value.
					// Otherwise, return the size of the
					// range in "size" and the number of the
					// first chunk as the return value.
					
		int		getHighChunk(uint word) const;
					// Find the highest order free (1) bit
					// in the map starting with word "word".
					// Returns the bit number (chunk number)
					// or a negative value if none is found.
		int		getHighest(uint word) const;
					// Find the highest allocated chunk in
					// or before the given word.
		int		getHighBit(ulong bts) const;
					// Find the highest order free (1) bit
					// in the word "bts".  Code assumes that
					// there is one.
					
		int		getLowChunk(uint word) const;
					// Find the lowest order free (1) bit
					// in the map starting with word "word".
					// Returns the bit number (chunk number)
					// or a negative value if none is found.
		int		getLowBit(ulong bts) const;
					// Find the lowest order free (1) bit
					// in the word "bts".  Code assumes that
					// there is one.
					
		uint		unitsToChunks(uint units) const;
					// Get the number of chunks required
					// for the given number of units.
					// Round up.
					
		uint		chunksToUnits(uint chunks) const;
					// Get the number of units there are in
					// the given number of chunks.
					
		inline uint	chunksToWords(uint chunks) const;
					// Number of uint words needed to
					// represent the given number of
					// chunks.
					
		inline uint	wordsToChunks(uint word) const;
					// Number of chunks there are in the
					// given number of words.
					
		inline uint	wordNbr(uint chunk) const;
					// The word containing the chunk.
					
		inline ulong	bitMask(uint chunk) const;
					// The mask for the bit representing
					// the chunk.
					
		inline uint	isAvail(uint chunk) const;
					// True if the chunk is available.
					
		inline void	allocChunk(uint chunk);
					// Allocate a chunk by clearing the
					// bit.
					
		inline void	freeChunk(uint chunk);
					// Free a chunk by setting the bit.
					
		
		/*  Some static constants which describe our environment.
		**  These are initialized in BitMap.C.  Some of the values are
		**  hardware dependent and must be changed when porting this
		**  class.
		*/
		
		static const uint	bitsPerLong;
		static const uint	bitsPerLongShift;
		static const uint	bitsPerLongMask;
		
		
		/*  We raise the following objections.
		*/
		
	public:
		static Objection	NoSpace;// We could not allocated the
						// requested resources because
						// we ran out of them.
		static Objection	BadFree;// An attempt to free space that
						// was not allocated or that is
						// not part of the pool.
		static Objection	BadTake;// Attempt to do a "take" of
						// already allocated units.
		static Objection	FileError;
						// An I/O error occurred reading
						// or writing the bit map.
						
		
		
		/*  The map and other related data.
		*/
		
		
	protected:
		Block(ulong)	bits;		// The actual bits.
		uint		nbrChunks;	// The number of chunks
						// allocated.		
		ulong		baseValue;	// The base value.
		uint		chunkSize;	// The chunksize.
		uint		chunkShift;	// Shift count for chunkSize.
		uint		chunkMask;	// Mask for chunkSize.
};

inline uint  BitMap::
size(void) const
{
	return chunksToUnits(nbrChunks);
}

inline void  BitMap::
grow(register uint incr)
{
	incr = chunksToUnits(unitsToChunks(incr));
	size(chunksToUnits(nbrChunks) + incr);
}

inline ulong  BitMap::
base(void) const
{
	return baseValue;
}

inline uint  BitMap::
chunk(void) const
{
	return chunkSize;
}

inline uint  BitMap::
chunksToWords(register uint chunks) const
{
	return (chunks + bitsPerLongMask) >> bitsPerLongShift;
}

inline uint  BitMap::
wordsToChunks(uint words) const
{
	return words << bitsPerLongShift;
}

inline uint  BitMap::
wordNbr(register uint chunk) const
{
	return chunk >> bitsPerLongShift;
}

inline ulong  BitMap::
bitMask(register uint chunk) const
{
	return 1 << (chunk & bitsPerLongMask);
}

inline uint  BitMap::
isAvail(register uint chunk) const
{
	register uint	wrdNbr;
	register ulong	mask;
	
	wrdNbr = wordNbr(chunk);
	mask = bitMask(chunk);
	return wrdNbr < bits.size()  &&  (bits[wrdNbr] & mask);
}

inline void  BitMap::
allocChunk(register uint chunk)
{
	bits[wordNbr(chunk)] &= ~bitMask(chunk);
}

inline void  BitMap::
freeChunk(register uint  chunk)
{
	bits[wordNbr(chunk)] |= bitMask(chunk);
}


/*  This class is used to iterate over the allocated chunks of a BitMap.
*/

class BitMapIter {
	public:
		inline		BitMapIter(const BitMap& bm);
					// The constructor.  Specifies which
					// bit map to iterate over.
		
		int		next(ulong& rv);
					// If there are more allocated chunks,
					// then set "rv" to the unit number of
					// the first unit of the next allocated
					// chunk and return 1.  If all allocated
					// chunks have been returned, leave "rv"
					// unchanged and return 0.
					// Return the unit number of the first
					// unit of the next allocated chunk.
					// Return -1 if past the last chunk.
						
		inline void	reset(void);
					// Reset the iterator to the beginning
					// of the map.
						
	private:
		const BitMap*	bitMapP;
					// Pointer to the BitMap we are
					// iterating over.
					
		uint		nextChunk;
					// The next chunk to test for being
					// allocated.
};

inline BitMapIter::
BitMapIter(register const BitMap& bm)
{
	bitMapP = &bm;
	nextChunk = 0;
}

inline void  BitMapIter::
reset(void)
{
	nextChunk = 0;
}


#endif	/* __BitMapH	*/
