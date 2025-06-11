#include "linear_allocator.h"

void test_linear_allocator_create() {
  size_t size = 1024;
  linear_allocator *allocator = linear_allocator_create(size);
  assert(allocator != NULL);
  assert(allocator->capacity == size);
  assert(allocator->offset == 0);

  linear_allocator_destroy(allocator);
}

void test_linear_allocator_allocate() {
  size_t size = 4 * 1024;
  linear_allocator *allocator = linear_allocator_create(size);

  unsigned int *ptr1 =
      linear_allocator_allocate(allocator, sizeof(unsigned int));
  assert(ptr1 != NULL);

  *ptr1 = 100;
  assert(*ptr1 == 100);
  assert(allocator->offset == sizeof(unsigned int));

  unsigned int *ptr2 =
      linear_allocator_allocate(allocator, sizeof(unsigned int));
  assert(ptr2 != NULL);

  *ptr2 = 200;
  assert(*ptr2 == 200);
  assert(allocator->offset == 2 * sizeof(unsigned int));

  assert(ptr2 == ptr1 + 1);
  linear_allocator_destroy(allocator);
}

void test_linear_allocator_reset() {

  size_t size = 16 * 1024;
  linear_allocator *allocator = linear_allocator_create(size);

  unsigned int *ptr1 =
      linear_allocator_allocate(allocator, sizeof(unsigned int));
  linear_allocator_reset(allocator);
  unsigned int *ptr2 =
      linear_allocator_allocate(allocator, sizeof(unsigned int));

  assert(ptr1 == ptr2);
  linear_allocator_destroy(allocator);
}

void test_linear_allocator_out_of_memory() {

  size_t size = 64 * 1024;
  linear_allocator *allocator = linear_allocator_create(size);

  unsigned int *ptr = linear_allocator_allocate(allocator, 70 * 1024);
  assert(ptr == NULL);

  linear_allocator_destroy(allocator);
}

void linear_allocator_zero_byte_test() {

  size_t size = 128 * 1024;
  linear_allocator *allocator = linear_allocator_create(size);

  unsigned int *ptr = linear_allocator_allocate(allocator, 0);
  assert(ptr == NULL);

  linear_allocator_destroy(allocator);
}

int main() {
  test_linear_allocator_create();
  test_linear_allocator_allocate();
  return 0;
}
