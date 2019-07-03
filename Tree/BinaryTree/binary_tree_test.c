#include <stdio.h>

#include "binary_tree.h"

void print_binary_tree_int(binary_tree_node* node)
{
    printf("%d ", *(int*)node->data);
}

int main(int argc, char** argv)
{
    int test_values[] = {1,2,3,4,5,6,7,8,9};
    binary_tree_node* root = 
        create_binary_tree_node(&test_values[0], sizeof(int));
    root->left = create_binary_tree_node(&test_values[1], sizeof(int));
    root->right = create_binary_tree_node(&test_values[2], sizeof(int));
    root->left->left = create_binary_tree_node(&test_values[3], sizeof(int));
    root->left->right = create_binary_tree_node(&test_values[4], sizeof(int));
    root->right->left = create_binary_tree_node(&test_values[5], sizeof(int));
    root->right->right = create_binary_tree_node(&test_values[6], sizeof(int));

    print_binary_tree_node(root, print_binary_tree_int);
    printf("\n");
    printf("#nodes = %d\n", get_binary_tree_node_count(root));
    printf("#depth = %d\n", get_binary_tree_depth(root));
    traversal_binary_tree(root, print_binary_tree_int, BINARY_TREE_TRAVERSAL_INORDER);
    printf("\n");
    traversal_binary_tree(root, print_binary_tree_int, BINARY_TREE_TRAVERSAL_PREORDER);
    printf("\n");
    traversal_binary_tree(root, print_binary_tree_int, BINARY_TREE_TRAVERSAL_POSTORDER);
    printf("\n");

#ifdef _WIN32
    system("pause");
#else
#endif

    return 0;
}