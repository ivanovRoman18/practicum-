#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define ERROR_STACK_OVERFLOW -1
#define ERROR_STACK_UNDERFLOW -2

typedef struct {
  int *data;
  int top;
  int capacity;
} Stack;

int stack_init(Stack *s, int initial_capacity);
void stack_free(Stack *s);
int stack_is_empty(const Stack *s);
int stack_is_full(const Stack *s);
int stack_push(Stack *s, int value);
int stack_pop(Stack *s, int *value);
int stack_peek(const Stack *s, int *value);
int stack_size(const Stack *s);
