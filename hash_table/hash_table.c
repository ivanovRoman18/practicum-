#include "hash_table.h"

#define MAX_LOAD_FACTOR 0.7

static uint32_t hash(const char *key) {
  uint32_t hash = 5381;
  int c;
  while ((c = *key++)) {
    hash = ((hash << 5) + hash) + c;
  }
  return hash;
}

void hashtable_init(HashTable *table, size_t capacity,
                    PoolAllocator *allocator) {
  assert(table != NULL);
  assert(allocator != NULL);
  assert(capacity > 0);

  table->capacity = capacity;
  table->size = 0;
  table->allocator = allocator;
  table->item_size = 0;
  table->items = (Item *)calloc(capacity, sizeof(Item));
  assert(table->items != NULL);
}

void hashtable_set_item_size(HashTable *table, size_t item_size) {
  assert(table != NULL);
  table->item_size = item_size;
}

static void hashtable_resize(HashTable *table) {
  size_t new_capacity = table->capacity * 2;
  Item *new_items = (Item *)calloc(new_capacity, sizeof(Item));
  assert(new_items != NULL);

  for (size_t i = 0; i < table->capacity; i++) {
    Item *old_item = &table->items[i];
    if (!old_item->is_occupied)
      continue;

    uint32_t new_index = hash(old_item->key) % new_capacity;
    while (new_items[new_index].is_occupied) {
      new_index = (new_index + 1) % new_capacity;
    }

    new_items[new_index] = *old_item;
  }

  free(table->items);
  table->items = new_items;
  table->capacity = new_capacity;
}

void hashtable_insert(HashTable *table, const char *key, void *value) {
  assert(table != NULL);
  assert(key != NULL);
  assert(value != NULL);

  if ((double)table->size / table->capacity >= MAX_LOAD_FACTOR) {
    hashtable_resize(table);
  }

  uint32_t index = hash(key) % table->capacity;
  size_t start_index = index;

  do {
    Item *item = &table->items[index];

    if (!item->is_occupied) {
      size_t key_len = strlen(key) + 1;
      char *key_copy = (char *)pool_allocate(table->allocator);
      if (!key_copy)
        return;
      strncpy(key_copy, key, key_len);

      void *value_copy = value;
      if (table->item_size > 0) {
        value_copy = pool_allocate(table->allocator);
        if (!value_copy) {
          pool_deallocate(table->allocator, key_copy);
          return;
        }
        memcpy(value_copy, value, table->item_size);
      }

      item->key = key_copy;
      item->value = value_copy;
      item->is_occupied = 1;
      table->size++;
      return;
    } else if (strcmp(item->key, key) == 0) {
      if (table->item_size > 0) {
        void *value_copy = pool_allocate(table->allocator);
        if (!value_copy)
          return;
        memcpy(value_copy, value, table->item_size);

        if (item->value != value) {
          pool_deallocate(table->allocator, item->value);
        }

        item->value = value_copy;
      } else {
        item->value = value;
      }
      return;
    }

    index = (index + 1) % table->capacity;
  } while (index != start_index);
}

void *hashtable_get(HashTable *table, const char *key) {
  assert(table != NULL);
  assert(key != NULL);

  uint32_t index = hash(key) % table->capacity;
  size_t start_index = index;

  do {
    Item *item = &table->items[index];
    if (!item->is_occupied)
      break;

    if (strcmp(item->key, key) == 0) {
      return item->value;
    }

    index = (index + 1) % table->capacity;
  } while (index != start_index);

  return NULL;
}

void hashtable_del(HashTable *table, const char *key) {
  assert(table != NULL);
  assert(key != NULL);

  uint32_t index = hash(key) % table->capacity;
  size_t start_index = index;

  do {
    Item *item = &table->items[index];
    if (!item->is_occupied)
      break;

    if (strcmp(item->key, key) == 0) {
      pool_deallocate(table->allocator, item->key);

      if (table->item_size > 0 && item->value != NULL) {
        pool_deallocate(table->allocator, item->value);
      }

      item->key = NULL;
      item->value = NULL;
      item->is_occupied = 0;
      table->size--;
      return;
    }

    index = (index + 1) % table->capacity;
  } while (index != start_index);
}

void hashtable_free(HashTable *table) {
  if (!table)
    return;

  if (table->items) {
    for (size_t i = 0; i < table->capacity; i++) {
      Item *item = &table->items[i];
      if (item->is_occupied) {
        if (item->key) {
          pool_deallocate(table->allocator, item->key);
        }
        if (table->item_size > 0 && item->value) {
          pool_deallocate(table->allocator, item->value);
        }
      }
    }
    free(table->items);
  }

  table->items = NULL;
  table->capacity = 0;
  table->size = 0;
  table->allocator = NULL;
  table->item_size = 0;
}
