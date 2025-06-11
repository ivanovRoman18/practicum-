#include "pool_allocator.h"

PoolAllocator *pool_create(int block_size, int num_blocks) {
  if (block_size <= 0 || num_blocks <= 0) {
    return NULL;
  }

  PoolAllocator *allocator = (PoolAllocator *)malloc(sizeof(PoolAllocator));
  if (!allocator) {
    return NULL;
  }

  allocator->block_size = block_size;
  allocator->total_blocks = num_blocks;
  allocator->first_free = 0;

  allocator->pool = malloc((size_t)block_size * (size_t)num_blocks);
  if (!allocator->pool) {
    free(allocator);
    return NULL;
  }

  allocator->free_blocks = (void **)malloc((size_t)num_blocks * sizeof(void *));
  if (!allocator->free_blocks) {
    free(allocator->pool);
    free(allocator);
    return NULL;
  }

  for (int i = 0; i < num_blocks; ++i) {
    allocator->free_blocks[i] = (char *)allocator->pool + i * block_size;
  }

  return allocator;
}

void *pool_allocate(PoolAllocator *allocator) {
  if (!allocator || allocator->first_free >= allocator->total_blocks) {
    return NULL;
  }

  void *block = allocator->free_blocks[allocator->first_free];
  allocator->first_free++;
  return block;
}

void pool_deallocate(PoolAllocator *allocator, void *block) {
  if (!allocator || !block || allocator->first_free <= 0) {
    return;
  }

  allocator->first_free--;
  allocator->free_blocks[allocator->first_free] = block;
}

void pool_destroy(PoolAllocator *allocator) {
  if (!allocator) {
    return;
  }

  free(allocator->free_blocks);
  free(allocator->pool);
  free(allocator);
}
