#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

#define STACK_TEST_OUTER_LOOP 100000
#define STACK_TEST_OPERATION_LOOP 1000

int main(int argc, char **argv)
{
    stack *s;
    stack_init(&s, STACK_IMPL_BY_VECTOR, sizeof(int));
    printf("capacity = %d\n", stack_capacity(s));

    int arr[] = {1,2,3,4,5};
    int i = 0;
    for (i = 0; i < 5; i++) {
        stack_push(s, &arr[i], sizeof(int));
    }

    int *top = stack_top(s);
    printf("top = %d\n", *top);
    printf("capacity = %d\n", stack_capacity(s));
    printf("size = %d\n", stack_size(s));
    printf("=====Start poping=====\n");

    i = 3;
    while (i--) {
        top = stack_pop(s);
        printf("top = %d\n", *top);
        printf("capacity = %d\n", stack_capacity(s));
        printf("size = %d\n", stack_size(s));
        free(top);
    }
    printf("=====Stop poping=====\n");
    vector_check_all_content_exist(v);
#ifdef _WIN32
    system("pause");
#endif

    int j = 0;
    for (i = 0; i < STACK_TEST_OUTER_LOOP; i++) {
        if (i % (STACK_TEST_OUTER_LOOP/10)==0 && i != 0) {
            printf("BEFORE PUSH\n");
            printf("#Loop = %d\n", i);
            printf("top = %d\n", *top);
            printf("capacity = %d\n", stack_capacity(s));
            printf("size = %d\n", stack_size(s));
        }
        for(j = 0; j < STACK_TEST_OPERATION_LOOP; j++) {
            int idx = j % 5;
            stack_push(s, &arr[idx], sizeof(int));
        }
        for(j = 0; j < STACK_TEST_OPERATION_LOOP; j++) {
            top = (int*)stack_pop(s);
            free(top);
            if (j % 500 == 0) {
#ifdef _WIN32
                //system("pause");
#endif
            }
        }
    }

    stack_destroy(&s);

#ifdef _WIN32
    system("pause");
#else
#endif

    return 0;
}