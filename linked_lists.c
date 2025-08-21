#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int val;
  struct node *next;
  struct node *prev;
} node_t;

node_t *createnode(int val) {
  node_t *new_node = (node_t *)malloc(sizeof(node_t));
  if (new_node == NULL) {
    printf("Could not allocate memory");
    exit(1);
  }

  new_node->val = val;
  new_node->next = NULL;
  new_node->prev = NULL;

  return new_node;
}

void print_list(node_t *head) {
  node_t *current_node = head;

  while (current_node != NULL) {
    printf("value: %d, address: %p\n", current_node->val, current_node);
    current_node = current_node->prev;
  }

  return;
}

void deallocating_list(node_t *head) {
  if (head == NULL) {
    return;
  }

  node_t *current_node = head;
  node_t *prev = NULL;

  while (current_node != NULL) {
    prev = current_node->prev;
    current_node->prev = NULL;
    free(current_node);

    current_node = prev;
  }
  printf("---- Freeing memory ---- \n");
}

int main() {
  node_t *tail = createnode(1);
  node_t *node1 = createnode(3);
  tail->next = node1;
  node1->prev = tail;
  node_t *head = createnode(4);
  node1->next = head;
  head->prev = node1;

  print_list(head);
  deallocating_list(head);

  return 0;
}
