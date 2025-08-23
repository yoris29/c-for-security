#include <stdio.h>
#include <stdlib.h>

// TODO: sort list

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

void insert_beginning(node_t **root, int val) {
  node_t *new_node = createnode(val);

  if (*root != NULL) {
    new_node->next = *root;
    (*root)->prev = new_node;
  }

  *root = new_node;
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

void insert_position(node_t **root, int pos, int val) {
  node_t *current_node = *root;
  node_t *new_node = createnode(val);
  int i = 0;

  if (pos == 1) {
    if (*root != NULL) {
      (*root)->prev = new_node;
      new_node->next = *root;
    }

    *root = new_node;
    return;
  }

  while (current_node != NULL && i != pos - 2) {
    i++;
    current_node = current_node->next;
  }

  node_t *next = current_node->next;
  current_node->next = new_node;
  new_node->prev = current_node;

  if (next != NULL) {
    new_node->next = next;
    next->prev = new_node;
  }
}

void delete_beginning(node_t **root) {
  if (*root == NULL) {
    return;
  }

  node_t *next = (*root)->next;
  free(*root);
  *root = next;

  if (*root != NULL) {
    (*root)->prev = NULL;
  }
}

void delete_ending(node_t **root) {
  node_t *current_node = *root;

  if (*root == NULL) {
    return;
  }
  if ((*root)->next == NULL) {
    free(current_node);
    *root = NULL;
    return;
  }

  while (current_node->next->next != NULL) {
    current_node = current_node->next;
  }

  node_t *next = current_node->next;
  free(next);
  current_node->next = NULL;
}

void delete_position(node_t **root, int pos) {
  node_t *current_node = *root;
  int i = 1;

  if (*root == NULL || pos <= 0) {
    return;
  }

  if (pos == 1) {
    *root = current_node->next;
    if (*root != NULL) {
      (*root)->prev = NULL;
      free(current_node);
    }
    return;
  }

  while (current_node->next != NULL && i != pos - 1) {
    current_node = current_node->next;
    i++;
  }

  node_t *next = current_node->next->next;
  node_t *deleted_node = current_node->next;
  current_node->next = next;
  free(deleted_node);

  if (next == NULL) {
    return;
  }
  next->prev = current_node;
}

void reverse_list(node_t **root) {
  node_t *current_node = *root;
  node_t *temp = NULL;

  while (current_node != NULL) {
    temp = current_node->prev;
    current_node->prev = current_node->next;
    current_node->next = temp;

    current_node = current_node->prev;
  }

  if (temp != NULL) {
    *root = temp->prev;
  }
}

void print_list(node_t *root) {
  node_t *current_node = root;

  while (current_node != NULL) {
    printf("value: %d, address: %p, prev: %p, next: %p\n", current_node->val,
           current_node, current_node->prev, current_node->next);
    current_node = current_node->next;
  }
}

void freenondes(node_t **root) {
  node_t *current_node = *root;
  node_t *next = NULL;

  if (*root == NULL) {
    return;
  }

  while (current_node != NULL) {
    next = current_node->next;
    free(current_node);
    current_node = next;
  }

  *root = NULL;
  printf("\n");
  printf("------ Memory freed ------");
}

int main() {
  node_t *node0 = createnode(3);
  insert_end(&node0, 4);
  insert_position(&node0, 3, 5);
  reverse_list(&node0);

  print_list(node0);
  freenondes(&node0);
  return 0;
}
