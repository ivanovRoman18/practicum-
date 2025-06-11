#include "singly_list.h"

void test_list_size() {
  singly_list list;
  list_init(&list);
  assert(list_size(&list) == 0);
  list_add_first(&list, 1);
  assert(list_size(&list) == 1);
  list_clear(&list);
}

void test_list_add_first() {
  singly_list list;
  list_init(&list);
  for (int i = 0; i < 3; i++) {
    list_add_first(&list, i);
  }
  assert(list_size(&list) == 3);
  assert(list_get_at(&list, 2) == 0);
  list_clear(&list);
}

void test_list_add_last() {
  singly_list list;
  list_init(&list);
  for (int i = 0; i < 3; i++) {
    list_add_last(&list, i);
  }
  assert(list_size(&list) == 3);
  assert(list_get_at(&list, 2) == 2);
  list_clear(&list);
}

void test_list_add_at() {
  singly_list list;
  list_init(&list);
  for (int i = 0; i < 3; i++) {
    list_add_first(&list, i);
  }
  list_add_at(&list, 1, 6);
  assert(list_size(&list) == 4);
  assert(list_get_at(&list, 1) == 6);
  list_clear(&list);
}

void test_list_get_at() {
  singly_list list;
  list_init(&list);
  for (int i = 0; i < 6; i++) {
    list_add_first(&list, i);
  }
  assert(list_get_at(&list, 3) == 2);
  list_clear(&list);
  assert(list_get_at(&list, 0) == -1);
}

void test_list_remove_first() {
  singly_list list;
  list_init(&list);
  for (int i = 0; i < 3; i++) {
    list_add_first(&list, i);
  }
  list_remove_first(&list);
  assert(list_get_at(&list, 0) == 1);
  assert(list_size(&list) == 2);
  list_clear(&list);
}

void test_list_remove_last() {
  singly_list list;
  list_init(&list);
  for (int i = 0; i < 3; i++) {
    list_add_first(&list, i);
  }
  list_remove_last(&list);
  assert(list_get_at(&list, 2) == -1);
  assert(list_size(&list) == 2);
  list_clear(&list);
}

void test_list_remove_at() {
  singly_list list;
  list_init(&list);
  for (int i = 0; i < 3; i++) {
    list_add_first(&list, i);
  }
  list_remove_at(&list, 1);
  assert(list_get_at(&list, 1) == 0);
  assert(list_size(&list) == 2);
  list_clear(&list);
}

int main() {

  test_list_size();
  test_list_add_first();
  test_list_add_last();
  test_list_add_at();
  test_list_get_at();
  test_list_remove_first();
  test_list_remove_last();
  test_list_remove_at();

  return 0;
}
