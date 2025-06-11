#include "pool_allocator.h"
#include <assert.h>
#include <stdio.h>

static void test_pool_create() {
  int block_size = 32;
  int num_blocks = 5;
  PoolAllocator *alloc = pool_create(block_size, num_blocks);

  assert(alloc != NULL);

  void *blocks[num_blocks];
  for (int i = 0; i < num_blocks; ++i) {
    blocks[i] = pool_allocate(alloc);
    assert(blocks[i] != NULL);
  }

  assert(pool_allocate(alloc) == NULL);

  pool_destroy(alloc);
}

static void test_pool_allocate_deallocate() {
  int block_size = 16;
  int num_blocks = 3;
  PoolAllocator *alloc = pool_create(block_size, num_blocks);

  void *block1 = pool_allocate(alloc);
  void *block2 = pool_allocate(alloc);

  assert(block1 != NULL);
  assert(block2 != NULL);
  assert(block1 != block2);

  pool_deallocate(alloc, block2);
  void *reused_block = pool_allocate(alloc);
  assert(reused_block == block2);

  pool_destroy(alloc);
}

static void test_boundary_conditions() {
  assert(pool_create(0, 10) == NULL);
  assert(pool_create(10, 0) == NULL);

  assert(pool_allocate(NULL) == NULL);
  pool_deallocate(NULL, NULL);
}

static void test_lifo_order() {
  int block_size = 8;
  int num_blocks = 2;
  PoolAllocator *alloc = pool_create(block_size, num_blocks);

  void *first = pool_allocate(alloc);
  void *second = pool_allocate(alloc);

  pool_deallocate(alloc, second);
  pool_deallocate(alloc, first);

  assert(pool_allocate(alloc) == first);
  assert(pool_allocate(alloc) == second);

  pool_destroy(alloc);
}

int main() {
  test_pool_create();
  test_pool_allocate_deallocate();
  test_boundary_conditions();
  test_lifo_order();

  return 0;
}
