#include <stdlib.h>
#include <memory.h>

#include "binary_tree.h"

binary_tree_node *create_binary_tree_node(void* data, int size)
{
    if (!data || size < 0)
        return NULL;

    binary_tree_node *node = (binary_tree_node*)malloc(sizeof(binary_tree_node));
    if (!node)
        return NULL;
    
    node->left = NULL;
    node->right = NULL;
    node->data = (void*)malloc(size);
    if (!node->data) {
        free(node);
        return NULL;
    }
    memcpy(node->data, data, size);

    return node;
}

int is_binary_tree_empty(binary_tree_node *node)
{
    return node? 0 : 1;
}

binary_tree_node *get_left_binary_tree(binary_tree_node *node)
{
    if (!node)
        return NULL;
    
    return node->left;
}

binary_tree_node *get_right_binary_tree(binary_tree_node *node)
{
    if (!node)
        return NULL;
    
    return node->right;
}

void *get_binary_tree_node_data(binary_tree_node *node)
{
    if (!node)
        return NULL;
    
    return node->data;
}

void print_binary_tree_node(binary_tree_node* node, 
                            void (*print_func)(binary_tree_node*))
{
    (*print_func)(node);
}