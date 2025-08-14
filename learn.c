#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int val;
    struct node *next;
} node_t;

node_t *createnode(int val) {
    node_t *new_node = (node_t*) malloc(sizeof(node_t));
    if(new_node == NULL) {
        printf("Could not allocate memory");
	exit(1);
    }

    new_node->val = val;
    new_node->next = NULL;
    return new_node;
}

void insert_beginning(node_t **root, int val) {
    node_t *new_node = createnode(val);
    new_node->next = *root;
    *root = new_node;
}

void insert_end(node_t **root, int val) {
    node_t *new_node = createnode(val);
    if(*root == NULL) {
	*root = new_node;
	return;
    }

    node_t *current_node = *root;
    while(current_node->next != NULL) {
	current_node = current_node->next; 
    }
    current_node->next = new_node;
}

void insert_after(node_t *node, int val) {
    node_t *new_node = createnode(val);
    new_node->next = node->next;
    node->next = new_node;
}

void sorted_insert(node_t **root, int val) {
    node_t *new_node = createnode(val);

    if(*root == NULL || val <= (*root)->val) {
	new_node->next = *root;
	*root = new_node; 
	return;
    }
    sorted_insert(&((*root)->next), val);
}

void print_list(node_t *root) {
    node_t *current_node = root;
    while(current_node != NULL) {
	printf("Current node value: %d\n", current_node->val);
	printf("Current node address: %p\n", current_node);
	printf("\n");

	current_node = current_node->next;
    }
}

// Deallocate memory using recursiveness
void free_list_recursive(node_t **root) {
    if(*root == NULL) {
	return;
    }
    node_t *current_node = *root;
    node_t *next_node = current_node->next;

    printf("------ Memory freed at node %d ------\n", current_node->val);
    free(current_node);
    *root = next_node;

    free_list_recursive(root);
}

void free_list(node_t **root) { 	
    node_t *current_node = *root;
    node_t *temp_node = NULL;

    while(current_node != NULL) {
	temp_node = current_node->next;
	free(current_node);
	current_node = temp_node;
    }
    *root = NULL;
    printf("------ Memory freed ------");
}

int main() {
    node_t *node0 = NULL; 

    insert_end(&node0, 2);
    insert_end(&node0, 4);
    insert_end(&node0, 5);
    sorted_insert(&node0, 3);

    print_list(node0);
    free_list_recursive(&node0);

    return 0;
}
