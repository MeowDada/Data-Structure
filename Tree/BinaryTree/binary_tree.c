#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

#include "binary_tree.h"

#ifndef MAX
#define MAX(x,y) (((x)>(y))?(x):(y))
#endif

binary_tree_node *binary_tree_create_node(void* data, size_t size)
{
    if (!data || size < 0)
        return NULL;

    binary_tree_node *node = (binary_tree_node*)malloc(sizeof(binary_tree_node));
    if (!node)
        return NULL;
    
    node->left = NULL;
    node->right = NULL;
    node->data = object_create(data, size);
    if (!node->data) {
        free(node);
        return NULL;
    }

    return node;
}

int binary_tree_is_empty(binary_tree_node *node)
{
    return node? node->data? 1 : 0 : 0;
}

binary_tree_node *binary_tree_get_left_tree(binary_tree_node *node)
{
    if (!node)
        return NULL;
    
    return node->left;
}

binary_tree_node *binary_tree_get_right_tree(binary_tree_node *node)
{
    if (!node)
        return NULL;
    
    return node->right;
}

void *binary_tree_get_node_data(binary_tree_node *node)
{
    if (!node || !node->data)
        return NULL;
    
    return node->data->content;
}

// Will return TRUE if both tree are NULL trees
int binary_tree_equal(binary_tree_node *tree1, binary_tree_node *tree2)
{
    if (!tree1 && !tree2)
        return 1;
    
    if (tree1 && tree2 && tree1->data && tree2->data) {
        if (tree1->data->equal_func && tree2->data->equal_func) {
            if (object_equal(tree1->data, tree2->data)) {
                return binary_tree_equal(tree1->left, tree2->left) && 
                       binary_tree_equal(tree1->right, tree2->right);
            }
        }
        else {
            fprintf(stderr, "[binary_tree_equal] Undefined object equal function!\n");
            return 0;
        }
    }
    return 0;
}

binary_tree_node *binary_tree_copy(binary_tree_node *src)
{
    if (!src || !src->data)
        return NULL;
    
    binary_tree_node *root = binary_tree_create_node(src->data->content, src->data->size);
    if (!root)
        return NULL;
    
    root->left = binary_tree_copy(src->left);
    root->right = binary_tree_copy(src->right);

    return root;
}

void binary_tree_print_node(binary_tree_node *node, 
                            void (*print_func)(binary_tree_node*))
{
    if (!node) {
        fprintf(stderr, "In binary_tree.c:\n");
        fprintf(stderr, "[binary_tree_print_node] Cannot print NULL node\n");
        return;
    }
    
    if (node->data && node->data->print_func)
        (*node->data->print_func)(node->data->content);
    else
        (*print_func)(node);
}

void binary_tree_destroy_node(binary_tree_node **node)
{
    if (!node || !(*node))
        return;

    binary_tree_node *tmp = *node;
    
    tmp->left = NULL;
    tmp->right = NULL;

    object_destroy(&tmp->data);
    free(tmp);
    *node = NULL;
}

void binary_tree_destroy_tree(binary_tree_node **node)
{
    if (!node || !(*node))
        return;
    
    if ((*node)->left)
        binary_tree_destroy_tree(&((*node)->left));
    
    if ((*node)->right)
        binary_tree_destroy_tree(&((*node)->right));
    
    binary_tree_destroy_node(node);
}

int binary_tree_depth(binary_tree_node *node)
{
    if (!node)
        return 0;
    
    int left_depth = binary_tree_depth(node->left);
    int right_depth = binary_tree_depth(node->right);

    return MAX(left_depth, right_depth) + 1;
}

int binary_tree_node_count(binary_tree_node* node)
{
    if (!node)
        return 0;
    
    int left_counts = binary_tree_node_count(node->left);
    int right_counts = binary_tree_node_count(node->right);

    return left_counts + right_counts + 1;
}

/* Traversal methods */
void binary_tree_inorder_traversal(binary_tree_node *root, void (*print_func)(binary_tree_node* node))
{
    if (!root)
        return;
    
    (*print_func)(root);
    binary_tree_inorder_traversal(root->left, print_func);
    binary_tree_inorder_traversal(root->right, print_func);
}

void binary_tree_preorder_traversal(binary_tree_node *root, void (*print_func)(binary_tree_node* node))
{
    if (!root)
        return;
    
    binary_tree_preorder_traversal(root->left, print_func);
    (*print_func)(root);
    binary_tree_preorder_traversal(root->right, print_func);
}

void binary_tree_postorder_traversal(binary_tree_node *root, void (*print_func)(binary_tree_node* node))
{
    if (!root)
        return;
    
    binary_tree_postorder_traversal(root->left, print_func);
    binary_tree_postorder_traversal(root->right, print_func);
    (*print_func)(root);
}

static void (*binary_tree_traversal_func[])(binary_tree_node*, void (*print_func)(binary_tree_node*)) = {
    binary_tree_inorder_traversal,
    binary_tree_preorder_traversal,
    binary_tree_postorder_traversal
};

void binary_tree_traversal(binary_tree_node *root, 
                           void (*print_func)(binary_tree_node*), 
                           binary_tree_traversal_mode mode)
{
    if (!root) {
        fprintf(stderr, "In binary_tree.c:\n");
        fprintf(stderr, "[binary_tree_traversal] Cannot traversal from NULL root\n");
        return;
    }
    
    (*binary_tree_traversal_func[mode])(root, print_func);
}