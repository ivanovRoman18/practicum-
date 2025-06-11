#include <assert.h>
#include <stdlib.h>

typedef struct Node Node;

typedef struct {
  Node *head;
  int size;
} singly_list;

void list_init(singly_list *list);
void list_add_first(singly_list *list, int data);
void list_add_last(singly_list *list, int data);
void list_add_at(singly_list *list, int index, int data);
void list_remove_first(singly_list *list);
void list_remove_last(singly_list *list);
void list_remove_at(singly_list *list, int index);
int list_get_at(singly_list *list, int index);
int list_size(singly_list *list);
void list_clear(singly_list *list);
