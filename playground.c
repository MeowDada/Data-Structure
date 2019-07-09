#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

typedef struct test {
    int *arr;
    int value;
} test_t;

void set_value(test_t **t, int *v)
{
    (*t)->arr = (int*)malloc(sizeof(int)*2);
    memcpy((*t)->arr, v, sizeof(int)*2);
}

int main(int argc, char **argv)
{
    test_t *test_arr = (test_t*)malloc(sizeof(test_t)*3);
    test_arr[0].arr = (int*)malloc(sizeof(int)*3);
    test_arr[0].arr[0] = 0;
    test_arr[0].arr[1] = 1;
    test_arr[0].arr[2] = 2;
    test_arr[1].arr = (int*)malloc(sizeof(int)*1);
    test_arr[1].arr[0] = 3;

    int v[] = {4,5};
    test_t *tmp = &test_arr[2];
    set_value(&tmp, v);

    printf("%d\n", test_arr[0].arr[0]);
    printf("%d\n", test_arr[0].arr[1]);
    printf("%d\n", test_arr[0].arr[2]);
    printf("%d\n", test_arr[1].arr[0]);
    printf("%d\n", test_arr[2].arr[0]);
    printf("%d\n", test_arr[2].arr[1]);

    return 0;
}