#include "linear_allocator.h"

linear_allocator *linear_allocator_create(size_t size) {
  linear_allocator *allocator = malloc(sizeof(linear_allocator));

  if (allocator == NULL)
    return NULL;

  allocator->buffer = malloc(size);
  if (!allocator->buffer) {
    free(allocator);
    return NULL;
  }

  allocator->capacity = size;
  allocator->offset = 0;

  return allocator;
}

void *linear_allocator_allocate(linear_allocator *allocator, size_t size) {
  if (!allocator) {
    return NULL;
  }

  if (allocator->capacity < allocator->offset + size) {
    return NULL;
  }
  if (size == 0) {
    return NULL;
  }

  void *ptr = allocator->buffer + allocator->offset;
  allocator->offset += size;

  return ptr;
}

void linear_allocator_reset(linear_allocator *allocator) {
  allocator->offset = 0;
}

void linear_allocator_destroy(linear_allocator *allocator) {
  if (!allocator)
    return;
  free(allocator->buffer);
  free(allocator);
}
