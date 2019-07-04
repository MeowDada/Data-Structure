#ifndef BINARY_TREE_H
#define BINARY_TREE_H

typedef struct binary_tree_node {
    struct binary_tree_node *left;
    struct binary_tree_node *right;
    void *data;
} binary_tree_node;

typedef enum binary_tree_traversal_mode {
    BINARY_TREE_TRAVERSAL_INORDER,
    BINARY_TREE_TRAVERSAL_PREORDER,
    BINARY_TREE_TRAVERSAL_POSTORDER
} binary_tree_traversal_mode;

binary_tree_node *create_binary_tree_node(void* data, int size);
int is_binary_tree_empty(binary_tree_node *node);
binary_tree_node *get_left_binary_tree(binary_tree_node *node);
binary_tree_node *get_right_binary_tree(binary_tree_node *node);
void *get_binary_tree_node_data(binary_tree_node *node);
void print_binary_tree_node(binary_tree_node *node, void (*print_func)(binary_tree_node*));
void destroy_binary_tree_node(binary_tree_node **node);
void destroy_binary_tree_recursively(binary_tree_node **root);
int get_binary_tree_depth(binary_tree_node *root);
int get_binary_tree_node_count(binary_tree_node *root);
void traversal_binary_tree(binary_tree_node *root, 
                           void (*print_func)(binary_tree_node*), 
                           binary_tree_traversal_mode mode);
void dump_binary_tree(binary_tree_node *root, void (*traversal_func)(binary_tree_node *root,
 void(*print_func)(binary_tree_node*)));

#endif /* BINARY_TREE_H */