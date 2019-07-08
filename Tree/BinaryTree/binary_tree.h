#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include "object.h"

typedef struct binary_tree_node {
    struct binary_tree_node *left;
    struct binary_tree_node *right;
    object_t *data;
} binary_tree_node;

typedef enum binary_tree_traversal_mode {
    BINARY_TREE_TRAVERSAL_INORDER,
    BINARY_TREE_TRAVERSAL_PREORDER,
    BINARY_TREE_TRAVERSAL_POSTORDER
} binary_tree_traversal_mode;

/* Create / Destroy  */
binary_tree_node *binary_tree_create_node(void* data, size_t size);
binary_tree_node *binary_tree_copy(binary_tree_node *src);
void binary_tree_destroy_node(binary_tree_node **node);
void binary_tree_destroy_tree(binary_tree_node **root);

/* Get Attributes */
binary_tree_node *binary_tree_get_left_tree(binary_tree_node *node);
binary_tree_node *binary_tree_get_right_tree(binary_tree_node *node);
void *binary_tree_get_node_data(binary_tree_node *node);

/* Utilites */
int binary_tree_equal(binary_tree_node *tree1, binary_tree_node *tree2);
void binary_tree_print_node(binary_tree_node *node, void (*print_func)(binary_tree_node*));
int binary_tree_is_empty(binary_tree_node *node);
int binary_tree_depth(binary_tree_node *root);
int binary_tree_node_count(binary_tree_node *root);
void binary_tree_traversal(binary_tree_node *root, 
                           void (*print_func)(binary_tree_node*), 
                           binary_tree_traversal_mode mode);
void binary_tree_dump(binary_tree_node *root, 
                      void (*traversal_func)(binary_tree_node *root,
                      void(*print_func)(binary_tree_node*)));


#endif /* BINARY_TREE_H */