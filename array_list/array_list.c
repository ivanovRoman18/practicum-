#include "array_list.h"

void array_list_create(array_list *list, linear_allocator *allocator,
                       size_t element_size) {
  if (list == NULL || allocator == NULL)
    return;
  list->allocator = allocator;
  list->size = 0;
  list->capacity = 4;
  list->element_size = element_size;
  list->data =
      linear_allocator_allocate(allocator, list->capacity * list->element_size);
}

void array_list_resize(array_list *list, size_t new_capacity) {
  void *new_data = linear_allocator_allocate(list->allocator,
                                             new_capacity * list->element_size);
  if (new_data == NULL)
    return;
  memcpy(new_data, list->data, list->size * list->element_size);
  list->data = new_data;
  list->capacity = new_capacity;
}

void array_list_add(array_list *list, void *data, size_t index) {
  if (list == NULL)
    return;
  if (index > list->size)
    return;
  if (list->size == list->capacity) {
    size_t new_capacity = list->capacity * 2;
    array_list_resize(list, new_capacity);
  }
  memcpy((char *)list->data + index * list->element_size, data,
         list->element_size);
  list->size++;
}

void *array_list_get(array_list *list, size_t index) {
  if (list == NULL)
    return NULL;
  if (index >= list->size)
    return NULL;
  return (char *)list->data + index * list->element_size;
}

void array_list_remove(array_list *list, size_t index) {
  if (list == NULL)
    return;
  if (index >= list->size)
    return;
  memmove((char *)list->data + index * list->element_size,
          (char *)list->data + (index + 1) * list->element_size,
          (list->size - index - 1) * list->element_size);
  list->size--;
}

void array_list_free(array_list *list) {
  if (list == NULL || list->allocator == NULL)
    return;
  list->allocator = NULL;
  list->size = 0;
  list->capacity = 0;
  list->element_size = 0;
  list->data = NULL;
}
