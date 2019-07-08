#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

#define STACK_TEST_OUTER_LOOP 100000
#define STACK_TEST_OPERATION_LOOP 10000

int main(int argc, char **argv)
{
    stack *s;
    stack_init(&s, STACK_IMPL_BY_ARRAY, sizeof(int));
    printf("capacity = %d\n", stack_capacity(s));

    int arr[] = {1,2,3,4,5};
    int i = 0;
    for (i = 0; i < 5; i++) {
        stack_push(s, &arr[i]);
    }

    int *top = stack_top(s);
    printf("top = %d\n", *top);
    printf("capacity = %d\n", stack_capacity(s));
    printf("size = %d\n", stack_size(s));

    i = 3;
    while (i--) {
        top = stack_pop(s);
        printf("top = %d\n", *top);
        printf("capacity = %d\n", stack_capacity(s));
        printf("size = %d\n", stack_size(s));
    }

    int j = 0;
    for (i = 0; i < STACK_TEST_OUTER_LOOP; i++) {
        if (i % (STACK_TEST_OUTER_LOOP/10)==0) {
            printf("#Loop = %d\n", i);
            printf("top = %d\n", *top);
            printf("capacity = %d\n", stack_capacity(s));
            printf("size = %d\n", stack_size(s));
        }
        for(j = 0; j < STACK_TEST_OPERATION_LOOP; j++) {
            int idx = j % 5;
            stack_push(s, &arr[idx]);
        }

        for(j = 0; j < STACK_TEST_OPERATION_LOOP; j++) {
            int idx = j % 5;
            stack_pop(s);
        }
    }

    stack_destroy(&s);

#ifdef _WIN32
    system("pause");
#else
#endif

    return 0;
}