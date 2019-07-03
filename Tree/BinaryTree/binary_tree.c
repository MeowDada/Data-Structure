#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

#include "binary_tree.h"

#ifndef MAX
#define MAX(x,y) (((x)>(y))?(x):(y))
#endif

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

void print_binary_tree_node(binary_tree_node *node, 
                            void (*print_func)(binary_tree_node*))
{
    (*print_func)(node);
}

void destroy_binary_tree_node(binary_tree_node *node)
{
    if (!node)
        return;
    
    node->left = NULL;
    node->right = NULL;
    free(node->data);
    free(node);
}

void destroy_binary_tree_recursively(binary_tree_node *node)
{
    if (!node)
        return;
    
    if (node->left)
        destroy_binary_tree_recursively(node->left);
    
    if (node->right)
        destroy_binary_tree_recursively(node->right);
    
    destroy_binary_tree_node(node);
}

int get_binary_tree_depth(binary_tree_node *node)
{
    if (!node)
        return 0;
    
    int left_depth = get_binary_tree_depth(node->left);
    int right_depth = get_binary_tree_depth(node->right);

    return MAX(left_depth, right_depth) + 1;
}

int get_binary_tree_node_count(binary_tree_node* node)
{
    if (!node)
        return 0;
    
    int left_counts = get_binary_tree_node_count(node->left);
    int right_counts = get_binary_tree_node_count(node->right);

    return left_counts + right_counts + 1;
}

/* Traversal methods */
void inorder_traversal_binary_tree(binary_tree_node *root, void (*print_func)(binary_tree_node* node))
{
    if (!root)
        return;
    
    (*print_func)(root);
    inorder_traversal_binary_tree(root->left, print_func);
    inorder_traversal_binary_tree(root->right, print_func);
}

void preorder_traversal_binary_tree(binary_tree_node *root, void (*print_func)(binary_tree_node* node))
{
    if (!root)
        return;
    
    preorder_traversal_binary_tree(root->left, print_func);
    (*print_func)(root);
    preorder_traversal_binary_tree(root->right, print_func);
}

void postorder_traversal_binary_tree(binary_tree_node *root, void (*print_func)(binary_tree_node* node))
{
    if (!root)
        return;
    
    postorder_traversal_binary_tree(root->left, print_func);
    postorder_traversal_binary_tree(root->right, print_func);
    (*print_func)(root);
}

static void (*binary_tree_traversal_func[])(binary_tree_node*, void (*print_func)(binary_tree_node*)) = {
    inorder_traversal_binary_tree,
    preorder_traversal_binary_tree,
    postorder_traversal_binary_tree
};

void traversal_binary_tree(binary_tree_node *root, 
                           void (*print_func)(binary_tree_node*), 
                           binary_tree_traversal_mode mode)
{
    (*binary_tree_traversal_func[mode])(root, print_func);
}