#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

int main(int argc, char **argv)
{
    stack s;
    stack_init(&s, STACK_IMPL_BY_ARRAY, sizeof(int));

    int arr[] = {1,2,3,4,5};
    int i = 0;
    for (i = 0; i < 5; i++) {
        stack_push(&s, &arr[i]);
    }
    int *top = stack_top(&s);
    printf("%d\n", *top);
    
    i = 3;
    while (i--) {
        top = stack_pop(&s);
        printf("%d\n", *top);
    }

    system("pause");

    return 0;
}