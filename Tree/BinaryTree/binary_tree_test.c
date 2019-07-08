#include <stdio.h>

#include "binary_tree.h"

#define TEST_BINARY_TREE_COPY_FLAG 1
#define TEST_BINARY_TREE_EQUAL_FLAG 0
#define TEST_CREATE_AND_DESTROY_FLAG 1
#define TEST_STRESS_LOOP_FLAG 1
#define STRESS_TEST_LOOP 100000000
#define PRINT_PER_LOOPS ((STRESS_TEST_LOOP) / (10))

void print_binary_tree_int(binary_tree_node* node)
{
    printf("%d ", *(int*)node->data->content);
}

void binary_tree_copy_test()
{
    int test_values[] = {1,2,3,4,5,6,7,8,9};

    binary_tree_node* root = 
        binary_tree_create_node(&test_values[0], sizeof(int));
    root->left = binary_tree_create_node(&test_values[1], sizeof(int));
    root->right = binary_tree_create_node(&test_values[2], sizeof(int));
    root->left->left = binary_tree_create_node(&test_values[3], sizeof(int));
    root->left->right = binary_tree_create_node(&test_values[4], sizeof(int));
    root->right->left = binary_tree_create_node(&test_values[5], sizeof(int));
    root->right->right = binary_tree_create_node(&test_values[6], sizeof(int));

    binary_tree_node *copy = binary_tree_copy(root);
    binary_tree_traversal(root, print_binary_tree_int, BINARY_TREE_TRAVERSAL_INORDER);
    printf("\n");
    binary_tree_traversal(copy, print_binary_tree_int, BINARY_TREE_TRAVERSAL_INORDER);
    printf("\n");
    binary_tree_destroy_tree(&root);
    binary_tree_destroy_tree(&copy);
}

void binary_tree_equal_test()
{
    int test_values[] = {1,2,3,4,5,6,7,8,9};

    binary_tree_node* root = 
        binary_tree_create_node(&test_values[0], sizeof(int));
    root->left = binary_tree_create_node(&test_values[1], sizeof(int));
    root->right = binary_tree_create_node(&test_values[2], sizeof(int));
    root->left->left = binary_tree_create_node(&test_values[3], sizeof(int));
    root->left->right = binary_tree_create_node(&test_values[4], sizeof(int));
    root->right->left = binary_tree_create_node(&test_values[5], sizeof(int));
    root->right->right = binary_tree_create_node(&test_values[6], sizeof(int));

    binary_tree_node *copy = binary_tree_copy(root);
    int equal = binary_tree_equal(copy, root);
    if (equal)
        fprintf(stdout, "Both tree is equal\n");
    else
        fprintf(stdout, "Both tree is not equal\n");
    
    binary_tree_destroy_tree(&root);
    binary_tree_destroy_tree(&copy);
}

int main(int argc, char** argv)
{
#if TEST_BINARY_TREE_COPY_FLAG
    binary_tree_copy_test();
#endif

#if TEST_BINARY_TREE_EQUAL_FLAG
    binary_tree_equal_test();
#endif

#if TEST_CREATE_AND_DESTROY_FLAG
    int test_values[] = {1,2,3,4,5,6,7,8,9};

    binary_tree_node* root = 
        binary_tree_create_node(&test_values[0], sizeof(int));
    root->left = binary_tree_create_node(&test_values[1], sizeof(int));
    root->right = binary_tree_create_node(&test_values[2], sizeof(int));
    root->left->left = binary_tree_create_node(&test_values[3], sizeof(int));
    root->left->right = binary_tree_create_node(&test_values[4], sizeof(int));
    root->right->left = binary_tree_create_node(&test_values[5], sizeof(int));
    root->right->right = binary_tree_create_node(&test_values[6], sizeof(int));

    binary_tree_print_node(root, print_binary_tree_int);
    printf("\n");
    printf("#nodes = %d\n", binary_tree_node_count(root));
    printf("#depth = %d\n", binary_tree_depth(root));
    binary_tree_traversal(root, print_binary_tree_int, BINARY_TREE_TRAVERSAL_INORDER);
    printf("\n");
    binary_tree_traversal(root, print_binary_tree_int, BINARY_TREE_TRAVERSAL_PREORDER);
    printf("\n");
    binary_tree_traversal(root, print_binary_tree_int, BINARY_TREE_TRAVERSAL_POSTORDER);
    printf("\n");

    binary_tree_destroy_tree(&root);
    binary_tree_print_node(root, print_binary_tree_int);
    if (binary_tree_is_empty(root))
        fprintf(stdout, "This tree is empty!\n");
    else
        fprintf(stdout, "This tree is empty!\n");
#endif
    /*
     * Stress test loop
     * To check there is any memory leak or not
     */ 
#if TEST_STRESS_LOOP_FLAG
    int i = 0;

    for (i = 0; i < STRESS_TEST_LOOP; i++) {
        if (i % PRINT_PER_LOOPS == 0)
            fprintf(stdout, "#Loop = %d\n", i);
        root = binary_tree_create_node(&test_values[0], sizeof(int));
        root->left = binary_tree_create_node(&test_values[1], sizeof(int));
        root->right = binary_tree_create_node(&test_values[2], sizeof(int));
        root->left->left = binary_tree_create_node(&test_values[3], sizeof(int));
        root->left->right = binary_tree_create_node(&test_values[4], sizeof(int));
        root->right->left = binary_tree_create_node(&test_values[5], sizeof(int));
        root->right->right = binary_tree_create_node(&test_values[6], sizeof(int));
        binary_tree_destroy_tree(&root);
    }
#endif

#ifdef _WIN32
    system("pause");
#else
#endif

    return 0;
}