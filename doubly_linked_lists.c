#include <stdio.h>
#include <stdlib.h>

// TODO: createnode, freenondes, insert beginning, insert ending, delete
// beginning, delete ending, insert at position, delete at position, reverse
// list, sort list

typedef struct node {
  int val;
  struct node *next;
  struct node *prev;
} node_t;

node_t *createnode(int val) {
  node_t *new_node = (node_t *)malloc(sizeof(node_t));
  if (new_node == NULL) {
    printf("Could not allocate memory for node %d", val);
  }

  new_node->val = val;
  new_node->next = NULL;
  new_node->prev = NULL;

  return new_node;
}

void insert_end(node_t **root, int val) {
  node_t *current_node = *root;
  node_t *new_node = createnode(val);

  while (current_node->next != NULL) {
    current_node = current_node->next;
  }

  current_node->next = new_node;
  current_node->next->prev = current_node;
}

void print_list(node_t *root) {
  node_t *current_node = root;

  while (current_node != NULL) {
    printf("value: %d, address: %p, prev: %p, next: %p\n", current_node->val,
           current_node, current_node->prev, current_node->next);
    current_node = current_node->next;
  }
}

int main() {
  node_t *node0 = createnode(3);
  insert_end(&node0, 4);

  print_list(node0);
  return 0;
}
