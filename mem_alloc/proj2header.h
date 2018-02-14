
#include <stdint.h>
//Functional Prototypes

void *malloc(size_t size);

void free(void *ptr);

void *global_base;

struct block_meta *find_free_block(struct block_meta **last, size_t size);

struct block_meta *request_space(struct block_meta* last, size_t size);

struct block_meta *get_block_ptr(void *ptr);

#define META_SIZE sizeof(struct block_meta)

void *calloc(size_t nelem, size_t elsize);

uint8_t mergeAdj();

void mergeAll();

void print();

void splitBlk(void *ptr, size_t size);

int memLeaks(void * start, void * currBrk, int bytes);

void *realloc(void *ptr, size_t size);

void *malloc2(size_t size);

void *realloc2(void *ptr, size_t size);

void *calloc2(size_t nelem, size_t elsize);

