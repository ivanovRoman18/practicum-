#ifndef POOL_ALLOCATOR_H
#define POOL_ALLOCATOR_H

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

typedef struct PoolAllocator {
  void *pool;
  void **free_blocks;
  int block_size;
  int total_blocks;
  int first_free;
} PoolAllocator;

PoolAllocator *pool_create(int block_size, int num_blocks);
void *pool_allocate(PoolAllocator *allocator);
void pool_deallocate(PoolAllocator *allocator, void *block);
void pool_destroy(PoolAllocator *allocator);

#endif
