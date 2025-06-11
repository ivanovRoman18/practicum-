#ifndef LINEAR_ALLOCATOR_H
#define LINEAR_ALLOCATOR_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  void *buffer;
  size_t capacity;
  size_t offset;
} linear_allocator;

linear_allocator *linear_allocator_create(size_t size);
void *linear_allocator_allocate(linear_allocator *allocator, size_t size);
void linear_allocator_reset(linear_allocator *allocator);
void linear_allocator_destroy(linear_allocator *allocator);

#endif
