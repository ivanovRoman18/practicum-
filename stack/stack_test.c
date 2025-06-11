#include "stack.h"

void test_stack_init() {
  Stack stack;
  stack_init(&stack, 2);
  assert(stack.top == -1);
  stack_free(&stack);
}

void test_stack_empty() {
  Stack stack;
  stack_init(&stack, 2);
  assert(stack_is_empty(&stack) == true);
  stack_free(&stack);
}

void test_stack_full() {
  Stack stack;
  int size = 2;
  stack_init(&stack, size);
  for (int i = 0; i < size; i++) {
    stack_push(&stack, i);
  }
  assert(stack_is_full(&stack) == true);
  stack_free(&stack);
}

void test_stack_push() {
  Stack stack;
  int value;
  stack_init(&stack, 2);
  stack_push(&stack, 10);
  assert(stack.top == 0);
  assert(stack.data[0] == 10);
  stack_free(&stack);
}

void test_stack_peek() {
  Stack stack;
  int value;
  stack_init(&stack, 2);
  stack_push(&stack, 10);
  assert(stack_peek(&stack, &value) == 0);
  assert(value == 10);
  stack_free(&stack);
}

void test_stack_pop() {
  Stack stack;
  int value;
  stack_init(&stack, 2);
  stack_push(&stack, 10);
  stack_pop(&stack, &value);
  assert(stack.top == -1);
  assert(value == 10);
  stack_free(&stack);
}

void test_stack_pop_empty() {
  Stack stack;
  int value;
  stack_init(&stack, 2);
  stack_push(&stack, -1);
  stack_push(&stack, 10);
  stack_pop(&stack, &value);
  assert(stack_pop(&stack, &value) == 0);
  assert(value == -1);
  assert(stack_pop(&stack, &value) == ERROR_STACK_UNDERFLOW);
  stack_free(&stack);
}

void test_stack_peek_empty() {
  Stack stack;
  int value;
  stack_init(&stack, 2);
  assert(stack_peek(&stack, &value) == ERROR_STACK_UNDERFLOW);
  stack_free(&stack);
}

void test_stack_push_full() {
  Stack stack;
  int size = 2;
  stack_init(&stack, size);
  for (int i = 0; i < size; i++) {
    stack_push(&stack, i);
  }
  stack_push(&stack, 3);
  assert(stack.top == size - 1);
  stack_free(&stack);
}

int main() {
  test_stack_init();
  test_stack_empty();
  test_stack_full();
  test_stack_push();
  test_stack_peek();
  test_stack_pop();
  test_stack_pop_empty();
  test_stack_peek_empty();
  test_stack_push_full();

  return 0;
}
