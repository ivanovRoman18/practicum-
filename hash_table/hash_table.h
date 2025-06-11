#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "../pool_allocator/pool_allocator.h"

typedef struct Item {
  char *key;
  void *value;
  int is_occupied;
} Item;

typedef struct {
  size_t capacity;
  size_t size;
  Item *items;
  PoolAllocator *allocator;
  size_t item_size;
} HashTable;

void hashtable_init(HashTable *table, size_t capacity,
                    PoolAllocator *allocator);
void hashtable_set_item_size(HashTable *table, size_t item_size);
void hashtable_insert(HashTable *table, const char *key, void *value);
void *hashtable_get(HashTable *table, const char *key);
void hashtable_del(HashTable *table, const char *key);
void hashtable_free(HashTable *table);

#endif
