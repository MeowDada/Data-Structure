#include <stdio.h>

#include "binary_tree.h"

void print_binary_tree_int(binary_tree_node* node)
{
    printf("%d ", *(int*)node->data);
}

int main(int argc, char** argv)
{
    int test_values[] = {1,2,3,4,5,6,7,8,9};
    binary_tree_node* head = 
        create_binary_tree_node(&test_values[0], sizeof(int));
    head->left = create_binary_tree_node(&test_values[1], sizeof(int));
    head->right = create_binary_tree_node(&test_values[2], sizeof(int));
    head->left->left = create_binary_tree_node(&test_values[3], sizeof(int));
    head->left->right = create_binary_tree_node(&test_values[4], sizeof(int));
    head->right->left = create_binary_tree_node(&test_values[5], sizeof(int));
    head->right->right = create_binary_tree_node(&test_values[6], sizeof(int));

    print_binary_tree_node(head, print_binary_tree_int);

#ifdef _WIN32
    system("pause");
#else
#endif

    return 0;
}