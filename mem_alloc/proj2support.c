#include <assert.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdint.h>
#define align_8(k) (((k-1)>>3)<<3)+8

/*void *malloc(size_t size) {
  void *p = sbrk(0);
  void *request = sbrk(size);
  if (request == (void*) -1) {
    return NULL; // sbrk failed.
  } else {
    assert(p == request); // Not thread safe.
    return p;
  }
}*/
struct block_meta {
	size_t size;
	struct block_meta *next, *prev;
	int free;
	int magic;    // For debugging only. TODO: remove this in non-debug mode.
};


#define META_SIZE sizeof(struct block_meta)

void *global_base = NULL;
struct block_meta *find_free_block(struct block_meta **last, size_t size) {
struct block_meta *current = global_base;
while (current && !(current->free && current->size >= size)) {
*last = current;
current = current->next;
}
return current;
}

struct block_meta *find_best_free_block(struct block_meta **last, size_t size) {
struct block_meta *current = global_base;
struct  block_meta *bestFit;
while (current && !(current->free && current->size >= size)) {
*last = current;
current = current->next;
}
bestFit=current;
while(current){
if(current->free && current->size < bestFit->size && current->size >=size){
bestFit = current;}
current= current->next;
}
return bestFit;
}


struct block_meta *request_space(struct block_meta* last, size_t size) {
struct block_meta *block;
block = sbrk(0);
void *request = sbrk(size + META_SIZE);
assert((void*)block == request); // Not thread safe.
if (request == (void*) -1) {
return NULL; // sbrk failed.
}
if (last) { // NULL on first request.
last->next = block;
block->prev = last;
}
block->size = size;
block->next = NULL;
block->free = 0;
block->magic = 0x12345678;
return block;
}

void *malloc(size_t size) {
struct block_meta *block;
size = align_8(size);// TODO: align size?
if (size <= 0) {
return NULL;
}
if (!global_base) { // First call.
block = request_space(NULL, size);
if (!block) {
return NULL;
}
global_base = block;
} else {
struct block_meta *last = global_base;
block = find_free_block(&last, size);
if (!block) { // Failed to find free block.
block = request_space(last, size);
if (!block) {
return NULL;
}
} else { // Found free block
// TODO: consider splitting block here.
 block->free = 0;
 block->magic = 0x77777777;
 }
 }
 return(block+1);
 } 

void *malloc2(size_t size) {
struct block_meta *block;
size = align_8(size);// TODO: align size?
if (size <= 0) {
return NULL;
 }
 if (!global_base) { // First call.
block = request_space(NULL, size);
 if (!block) {
return NULL;
}
global_base = block;
} else {
struct block_meta *last = global_base;
block = find_free_block(&last, size);
if (!block) { // Failed to find free block.
block = request_space(last, size);
if (!block) {
return NULL;
}
} else { // Found free block
splitBlk(block + 1, size);// TODO: consider splitting block here.
 block->free = 0;
 block->magic = 0x77777777;
mergeAll(); 
}
 }
return(block+1);
}


struct block_meta *get_block_ptr(void *ptr) {
return (struct block_meta*)ptr - 1;
}


void free(void *ptr) {
if (!ptr) {
return;
}
// TODO: consider merging blocks once splitting blocks is implemented.
struct block_meta* block_ptr = get_block_ptr(ptr);
assert(block_ptr->free == 0);
assert(block_ptr->magic == 0x77777777 || block_ptr->magic == 0x12345678);
block_ptr->free = 1;
block_ptr->magic = 0x55555555;
mergeAll();
}

void *realloc(void *ptr, size_t size) {
size = align_8(size);
if (!ptr) {
// NULL ptr. realloc should act like malloc.
 return malloc(size);
 }
 struct block_meta* block_ptr = get_block_ptr(ptr);
 if (block_ptr->size >= size) {
 // We have enough space. Could free some once we implement split.
splitBlk(ptr,size);
mergeAll(); 
return ptr;
 }
 // Need to really realloc. Malloc new space and free old space.
 // Then copy old data to new space.
 void *new_ptr;
 new_ptr = malloc(size);
 if (!new_ptr) {
 return NULL; // TODO: set errno on failure.
 }
 memcpy(new_ptr, ptr, block_ptr->size);
 free(ptr);
 return new_ptr;
 }


void *realloc2(void *ptr, size_t size) {
size = align_8(size);
if (!ptr) {
// NULL ptr. realloc should act like malloc.
return malloc2(size);
}
struct block_meta* block_ptr = get_block_ptr(ptr);
if (block_ptr->size >= size) {
// We have enough space. Could free some once we implement split.
splitBlk(ptr,size);
mergeAll();
return ptr;
}
// Need to really realloc. Malloc new space and free old space.
// Then copy old data to new space.
void *new_ptr;
new_ptr = malloc2(size);
if (!new_ptr) {
return NULL; // TODO: set errno on failure.
}
memcpy(new_ptr, ptr, block_ptr->size);
free(ptr);
return new_ptr;
}

void *calloc(size_t nelem, size_t elsize) {
size_t size = align_8(nelem * elsize); // TODO: check for overflow.
void *ptr = malloc(size);
memset(ptr, 0, size);
return ptr;
}

void *calloc2(size_t nelem, size_t elsize) {
size_t size = align_8(nelem * elsize); // TODO: check for overflow.
void *ptr = malloc2(size);
memset(ptr, 0, size);
return ptr;
}


uint8_t mergeAdj()
{
   struct block_meta * current = global_base;
    uint8_t merge = 0;
    while (current)
    {
         if(current->next && current->free == 1 && current->next->free == 1){
         current->size = current->size + META_SIZE + current->next->size;
            current->next = current->next->next;
       merge=1;
}
 current = current->next;
}
 return merge;
}


void mergeAll()
{
    uint8_t merge = 1;             

    while(merge)
    {
        merge = mergeAdj();   
    }
}


int memLeaks(void * start, void * currBrk, int bytes)
{
    int memoryLeak = 0;
    int heapSize = 0;
struct block_meta * current = global_base;
    while (current)
    {
        memoryLeak += META_SIZE;    
        if(current->free)                    
        {
            memoryLeak += current->size;
        }
        current = current->next;
    }

    heapSize = (uint64_t)(currBrk) - (uint64_t)(start);
    return memoryLeak;
}

void print()
{
    printf("\nBlocks: ");
    struct block_meta * current = global_base;
    if(current)
    {
        printf("(%zu %d)", current->size, current->free);
        current = current->next;
    }
    while (current)
    {
        printf("  (%zu %d) ", current->size, current->free);
        current = current->next;
    }
    printf("\n");
}



void splitBlk(void *ptr, size_t size)
{
   struct block_meta * blk1 = get_block_ptr(ptr);
    if(blk1->size - size < META_SIZE + 4)   
    {                                                 
        return;
    }

   struct block_meta * blk2 = ptr + size;
    blk2->size = blk1->size - size - META_SIZE;
    blk1->size = size;
    blk2->next = blk1->next;
    blk1->next = blk2;
    blk2->free = 1;
    blk1->free = 0;
}



