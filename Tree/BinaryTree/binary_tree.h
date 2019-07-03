#ifndef BINARY_TREE_H
#define BINARY_TREE_H

typedef struct binary_tree_node {
    binary_tree_node *left;
    binary_tree_node *right;
    void *data;
} binary_tree_node;

binary_tree_node *create_binary_tree_node(void* data);
int is_binary_tree_empty(binary_tree_node *node);
binary_tree_node *get_left_binary_tree(binary_tree_node *node);
binary_tree_node *get_right_binary_tree(binary_tree_node *node);
void *get_binary_tree_node_data(binary_tree_node *node);
void print_binary_tree_node(binary_tree_node* node, void (*print_func)
(binary_tree_node*));

#endif /* BINARY_TREE_H */