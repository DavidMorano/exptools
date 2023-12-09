#ifndef _POOL_H
#define _POOL_H 1

#ifndef __STDDEF_H
#include <stddef.h>
#endif

class Block_header {
	Block_header* next;
	friend class Block_pool;
};

class Block_pool {
	size_t sz;
	unsigned cnt;
	Block_header* head;
	Block_pool(Block_pool&);		// copy protection
	void operator= (Block_pool&);		// copy protection
public:
	size_t size() const { return sz; }
	unsigned count() const { return cnt; }
	Block_pool(size_t);
	~Block_pool();
	char* expand();
	void free();
};

class Pool_element_header {
	Pool_element_header* next;
	friend class Pool;
};

class Pool: private Block_pool {
	size_t elsize;
	unsigned count;
	Pool_element_header* head;
	Pool(Pool&);			// copy protection
	void operator= (Pool&);		// copy protection
	void grow();
public:
	Pool(size_t n);
	void * alloc() {
		if (!head)
			grow();
		register Pool_element_header* p = head;
		head = p->next;
		return p;
	}
	void free(void * b) {
		register Pool_element_header* p = (Pool_element_header*) b;
		p->next = head;
		head = p;
	}
	void purge() {
		Block_pool::free();
		head = 0;
	}
};

struct Vpool_stats {
	unsigned count;     // number of elements currently in the Vpool
	double mem_util;    // current memory utilization
	size_t mem_alloced; // total memory currently allocated to Vpool
	size_t mem_inuse;   // bytes currently holding elements
	size_t mem_waste;   // bytes wasted due to fragmentation
	size_t mem_savings; // bytes saved due to reallocing
	size_t chunk_size;  // underlying memory chunk size
	size_t realsz;      // underlying element size (>= max size)
};

class Vpool: private Block_pool {
	unsigned cnt;
	size_t origsz, realsz;
	size_t space_left, totwaste;
	char *avail, *shrinkable;
	char *prev_avail;
	size_t prev_space_left;

	Vpool(Vpool&);			// copy protection
	void operator=(Vpool&);		// copy protection
	void grow();
	void do_shrink(void *, size_t);
	int legal_realloc(void *, size_t);
public:
	Vpool(size_t max, size_t expected, double desired_occupancy = 0.8);
	void * alloc() {
		if (space_left < realsz)
			grow();
		// assert(space_left >= realsz);
		register void * p = avail;
		shrinkable = avail;
		avail += realsz;
		space_left -= realsz;
		++cnt;
		return p;
	}
	void * realloc(void *, size_t);
	void * realloc_inplace(void *, size_t);
	void purge() {
		Block_pool::free();
		cnt = 0;
		totwaste = space_left = 0;
		avail = shrinkable = 0;
		prev_avail = 0;
		prev_space_left = 0;
	}
	Vpool_stats stats() const;
};

// header file lock
extern char _Pool__version3;

#endif
