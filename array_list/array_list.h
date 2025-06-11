#include "../linear_allocator/linear_allocator.h"
#include <string.h>

typedef struct {
  void *data;
  linear_allocator *allocator;
  size_t size;
  size_t capacity;
  size_t element_size;
} array_list;

void array_list_create(array_list *list, linear_allocator *allocator,
                       size_t element_size);
void array_list_add(array_list *list, void *data, size_t index);
void *array_list_get(array_list *list, size_t index);
void array_list_remove(array_list *list, size_t index);
void array_list_free(array_list *list);
