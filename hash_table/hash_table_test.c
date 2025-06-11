#include "hash_table.h"

#define TEST_CAPACITY 8

static void test_init_and_free() {
  PoolAllocator *allocator = pool_create(64, 128);
  HashTable table;
  hashtable_init(&table, TEST_CAPACITY, allocator);

  assert(table.capacity == TEST_CAPACITY);
  assert(table.size == 0);
  assert(table.items != NULL);

  hashtable_free(&table);
  pool_destroy(allocator);
}

static void test_insert_and_get() {
  PoolAllocator *allocator = pool_create(64, 128);
  HashTable table;
  hashtable_init(&table, TEST_CAPACITY, allocator);

  int val1 = 100;
  int val2 = 200;

  hashtable_insert(&table, "key1", &val1);
  hashtable_insert(&table, "key2", &val2);

  assert(*(int *)hashtable_get(&table, "key1") == 100);
  assert(*(int *)hashtable_get(&table, "key2") == 200);
  assert(table.size == 2);

  hashtable_free(&table);
  pool_destroy(allocator);
}

static void test_update_value() {
  PoolAllocator *allocator = pool_create(64, 128);
  HashTable table;
  hashtable_init(&table, TEST_CAPACITY, allocator);

  int val1 = 100;
  int val2 = 200;

  hashtable_insert(&table, "key1", &val1);
  hashtable_insert(&table, "key1", &val2);

  assert(*(int *)hashtable_get(&table, "key1") == 200);
  assert(table.size == 1);

  hashtable_free(&table);
  pool_destroy(allocator);
}

static void test_delete() {
  PoolAllocator *allocator = pool_create(64, 128);
  HashTable table;
  hashtable_init(&table, TEST_CAPACITY, allocator);

  int val1 = 100;
  hashtable_insert(&table, "key1", &val1);

  assert(hashtable_get(&table, "key1") != NULL);
  assert(table.size == 1);

  hashtable_del(&table, "key1");

  assert(hashtable_get(&table, "key1") == NULL);
  assert(table.size == 0);

  hashtable_free(&table);
  pool_destroy(allocator);
}

static void test_collisions() {
  PoolAllocator *allocator = pool_create(64, 128);
  HashTable table;
  hashtable_init(&table, 2, allocator);

  int val1 = 1;
  int val2 = 2;
  int val3 = 3;

  hashtable_insert(&table, "a", &val1);
  hashtable_insert(&table, "b", &val2);
  hashtable_insert(&table, "c", &val3);

  assert(*(int *)hashtable_get(&table, "a") == 1);
  assert(*(int *)hashtable_get(&table, "b") == 2);
  assert(*(int *)hashtable_get(&table, "c") == 3);
  assert(table.capacity > 2);

  hashtable_free(&table);
  pool_destroy(allocator);
}

int main() {
  test_init_and_free();
  test_insert_and_get();
  test_update_value();
  test_delete();
  test_collisions();

  return 0;
}
