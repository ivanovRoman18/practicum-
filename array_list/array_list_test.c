#include "array_list.h"

void test_array_list_create() {
  size_t size = 1024;
  linear_allocator *allocator = linear_allocator_create(size);
  assert(allocator != NULL);
  assert(allocator->capacity == size);
  assert(allocator->offset == 0);
  array_list list;
  array_list_create(&list, allocator, sizeof(int));

  assert(list.allocator == allocator);
  assert(list.size == 0);
  assert(list.capacity == 4);
  assert(list.data != NULL);

  array_list_free(&list);
  linear_allocator_destroy(allocator);
}

void test_array_list_add() {
  size_t size = 4 * 1024;
  linear_allocator *allocator = linear_allocator_create(size);
  array_list list;
  array_list_create(&list, allocator, sizeof(int));

  for (int i = 0; i < 10; i++) {
    int *val = malloc(sizeof(int));
    *val = i * 5;
    array_list_add(&list, val, list.size);
    free(val);
  }
  assert(list.size == 10);
  assert(list.capacity == 16);

  array_list_free(&list);
  linear_allocator_destroy(allocator);
}

void test_array_list_get() {
  size_t size = 16 * 1024;
  linear_allocator *allocator = linear_allocator_create(size);
  array_list list;
  array_list_create(&list, allocator, sizeof(int));

  for (int i = 0; i < 10; i++) {
    int *val = malloc(sizeof(int));
    *val = i * 10;
    array_list_add(&list, val, list.size);
    free(val);
  }

  for (int i = 0; i < list.size; i++) {
    int *val = (int *)array_list_get(&list, i);
    assert(*val == i * 10);
  }

  array_list_free(&list);
  linear_allocator_destroy(allocator);
}

void test_array_list_get_out_of_bounds() {
  size_t size = 16 * 1024;
  linear_allocator *allocator = linear_allocator_create(size);
  array_list list;
  array_list_create(&list, allocator, sizeof(int));

  for (int i = 0; i < 2; i++) {
    int *val = malloc(sizeof(int));
    *val = i;
    array_list_add(&list, val, list.size);
    free(val);
  }

  int *val = (int *)array_list_get(&list, 3);
  assert(val == NULL);

  array_list_free(&list);
  linear_allocator_destroy(allocator);
}

void test_array_list_remove() {
  size_t size = 64 * 1024;
  linear_allocator *allocator = linear_allocator_create(size);
  array_list list;
  array_list_create(&list, allocator, sizeof(int));

  for (int i = 0; i < 10; i++) {
    int *val = malloc(sizeof(int));
    *val = i * 10;
    array_list_add(&list, val, list.size);
    free(val);
  }

  array_list_remove(&list, 2);
  assert(list.size == 9);
  assert(*(int *)array_list_get(&list, 2) == 3 * 10);

  array_list_remove(&list, 0);
  assert(list.size == 8);
  assert(*(int *)array_list_get(&list, 0) == 1 * 10);
  assert(*(int *)array_list_get(&list, 2) == 4 * 10);

  array_list_free(&list);
  linear_allocator_destroy(allocator);
}

void test_array_list_free() {
  size_t size = 128 * 1024;
  linear_allocator *allocator = linear_allocator_create(size);
  array_list list;
  array_list_create(&list, allocator, sizeof(int));

  int val = 0;
  array_list_add(&list, &val, 0);
  array_list_free(&list);

  assert(list.allocator == NULL);
  assert(list.size == 0);
  assert(list.capacity == 0);
  assert(list.data == NULL);

  linear_allocator_destroy(allocator);
}

void test_array_list_free_empty() {
  size_t size = 512 * 1024;
  linear_allocator *allocator = linear_allocator_create(size);
  array_list list;
  array_list_create(&list, allocator, sizeof(int));

  array_list_free(&list);
  linear_allocator_destroy(allocator);
}

int main() {
  test_array_list_create();
  test_array_list_add();
  test_array_list_get();
  test_array_list_get_out_of_bounds();
  test_array_list_remove();
  test_array_list_free();
  test_array_list_free_empty();
  return 0;
}
