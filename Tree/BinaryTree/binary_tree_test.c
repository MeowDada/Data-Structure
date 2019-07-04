#include <stdio.h>

#include "binary_tree.h"

#define STRESS_TEST_LOOP 100000000
#define PRINT_PER_LOOPS ((STRESS_TEST_LOOP) / (10))

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

    destroy_binary_tree_recursively(&root);
    print_binary_tree_node(root, print_binary_tree_int);
    if (is_binary_tree_empty(root))
        fprintf(stdout, "This tree is empty!\n");
    else
        fprintf(stdout, "This tree is empty!\n");
    
    /*
     * Stress test loop
     * To check there is any memory leak or not
     */ 
    int i = 0;

    for (i = 0; i < STRESS_TEST_LOOP; i++) {
        if (i % PRINT_PER_LOOPS == 0)
            fprintf(stdout, "#Loop = %d\n", i);
        root = create_binary_tree_node(&test_values[0], sizeof(int));
        root->left = create_binary_tree_node(&test_values[1], sizeof(int));
        root->right = create_binary_tree_node(&test_values[2], sizeof(int));
        root->left->left = create_binary_tree_node(&test_values[3], sizeof(int));
        root->left->right = create_binary_tree_node(&test_values[4], sizeof(int));
        root->right->left = create_binary_tree_node(&test_values[5], sizeof(int));
        root->right->right = create_binary_tree_node(&test_values[6], sizeof(int));
        destroy_binary_tree_recursively(&root);
    }

#ifdef _WIN32
    system("pause");
#else
#endif

    return 0;
}