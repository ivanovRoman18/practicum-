#include "stack.h"

int stack_init(Stack *stack, int initial_capacity) {
  stack->data = (int *)malloc(initial_capacity * sizeof(int));
  stack->top = -1;
  stack->capacity = initial_capacity;
  return 0;
}

void stack_free(Stack *stack) {
  if (stack->data != NULL)
    free(stack->data);
}

int stack_is_empty(const Stack *stack) { return stack->top == -1; }

int stack_is_full(const Stack *stack) {
  return stack->top == stack->capacity - 1;
}

int stack_push(Stack *stack, int value) {
  if (stack_is_full(stack))
    return ERROR_STACK_OVERFLOW;
  stack->top++;
  stack->data[stack->top] = value;
  return 0;
}

int stack_pop(Stack *stack, int *value) {
  if (stack_is_empty(stack))
    return ERROR_STACK_UNDERFLOW;
  *value = stack->data[stack->top--];
  return 0;
}

int stack_peek(const Stack *stack, int *value) {
  if (stack_is_empty(stack))
    return ERROR_STACK_UNDERFLOW;
  *value = stack->data[stack->top];
  return 0;
}

int stack_size(const Stack *stack) { return stack->top + 1; }
