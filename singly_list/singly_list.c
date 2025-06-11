#include "singly_list.h"

struct Node {
  int data;
  Node *next;
};

struct singly_list {
  Node *head;
  int size;
};

void list_init(singly_list *list) {
  list->head = NULL;
  list->size = 0;
}

void list_add_first(singly_list *list, int data) {
  Node *new_node = (Node *)malloc(sizeof(Node));
  new_node->data = data;
  new_node->next = list->head;
  list->head = new_node;
  list->size++;
}

void list_add_last(singly_list *list, int data) {
  Node *new_node = (Node *)malloc(sizeof(Node));
  new_node->data = data;
  new_node->next = NULL;

  if (list->head == NULL) {
    list->head = new_node;
  } else {
    Node *current = list->head;
    while (current->next != NULL) {
      current = current->next;
    }
    current->next = new_node;
  }
  list->size++;
}

void list_add_at(singly_list *list, int index, int data) {
  if (index < 0 || index > list->size)
    return;

  if (index == 0) {
    list_add_first(list, data);
  } else if (index == list->size) {
    list_add_last(list, data);
  } else {
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->data = data;

    Node *current = list->head;
    for (int i = 0; i < index - 1; i++) {
      current = current->next;
    }

    new_node->next = current->next;
    current->next = new_node;
    list->size++;
  }
}

void list_remove_first(singly_list *list) {
  if (list->head == NULL)
    return;

  Node *temp = list->head;
  int data = temp->data;

  list->head = list->head->next;
  free(temp);
  list->size--;

  return;
}

void list_remove_last(singly_list *list) {
  if (list->head == NULL)
    return;

  if (list->head->next == NULL) {
    return list_remove_first(list);
  }

  Node *current = list->head;
  while (current->next->next != NULL) {
    current = current->next;
  }

  int data = current->next->data;
  free(current->next);
  current->next = NULL;
  list->size--;

  return;
}

void list_remove_at(singly_list *list, int index) {
  if (index < 0 || index >= list->size)
    return;

  if (index == 0) {
    return list_remove_first(list);
  } else if (index == list->size - 1) {
    return list_remove_last(list);
  } else {
    Node *current = list->head;
    for (int i = 0; i < index - 1; i++) {
      current = current->next;
    }

    Node *temp = current->next;
    int data = temp->data;
    current->next = temp->next;
    free(temp);
    list->size--;

    return;
  }
}

int list_get_at(singly_list *list, int index) {
  if (index < 0 || index >= list->size)
    return -1;

  Node *current = list->head;
  for (int i = 0; i < index; i++) {
    current = current->next;
  }

  return current->data;
}

int list_size(singly_list *list) { return list->size; }

void list_clear(singly_list *list) {
  while (list->head != NULL) {
    list_remove_first(list);
  }
}
