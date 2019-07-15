#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

#define LOOP 1000000
#define DEFAULT_SIZE 100000

typedef struct test {
    void **arr;
    int capacity;
} test_t;

test_t* init(int capacity)
{
    test_t *t = (test_t*)malloc(sizeof(test_t));
    t->arr = (void**)malloc(sizeof(void*) * capacity);
    t->capacity = capacity;

    return t;
}

void set_value(test_t *t, void *v, int size, int index)
{
    t->arr[index] = malloc(size);
    memcpy(t->arr[index], v, size);
}

void destroy_test_t(test_t *t)
{
    int i = 0;
    for (i = 0; i < t->capacity; i++) {
        free(t->arr[i]);
        t->arr[i] = NULL;
    }
    free(t->arr);
    free(t);
}

void destroy_whole(test_t* t, int size)
{
    int i = 0;
    for (i = 0; i < size; i++) {
        test_t *tmp = &t[i];
        destroy_test_t(tmp);
    }
    free(t);
}

int main(int argc, char **argv)
{
    /*
    int i = 0;
    for (i = 0; i < LOOP; i++) {
        test_t **ptr = (test_t**)malloc(sizeof(test_t*)*DEFAULT_SIZE);
        int j = 0;
        for (j = 0; j < DEFAULT_SIZE; j++){
            ptr[j] = malloc(sizeof(test_t));
        }
        for (j = 0; j < DEFAULT_SIZE; j++){
            free(ptr[j]);
        }
        free(ptr);
    }
    */

    char* str0 = "Hello";
    char* str1 = "Happyy";
    char* str2 = "Worrrrrrld!";

    test_t *test_arr = (test_t*)malloc(sizeof(test_t)*3);
    test_t *tmp = init(3);
    memcpy(&test_arr[0], tmp, sizeof(test_t));
    free(tmp);
    tmp = init(2);
    memcpy(&test_arr[1], init(2), sizeof(test_t));
    free(tmp);
    tmp = init(1);
    memcpy(&test_arr[2], init(1), sizeof(test_t));
    free(tmp);

    printf("%d\n", test_arr[0].capacity);
    printf("%d\n", test_arr[1].capacity);
    printf("%d\n", test_arr[2].capacity);

    set_value(&test_arr[0], str0, 6, 0);
    set_value(&test_arr[0], str1, 7, 1);
    set_value(&test_arr[0], str2, 12, 2);

    printf("%s\n", (char*)test_arr[0].arr[0]);
    printf("%s\n", (char*)test_arr[0].arr[1]);
    printf("%s\n", (char*)test_arr[0].arr[2]);

    destroy_whole(test_arr, 3);

    int i = 0;
    for(i = 0; i < LOOP; i++)
    {
        if (i % (LOOP / 10) == 0)
            printf("#Loop = %d\n", i);
        
        test_arr = (test_t*)malloc(sizeof(test_t)*3);
        test_t *tmp = init(3);
        memcpy(&test_arr[0], tmp, sizeof(test_t));
        free(tmp);
        tmp = init(2);
        memcpy(&test_arr[1], tmp, sizeof(test_t));
        free(tmp);
        tmp = init(1);
        memcpy(&test_arr[2], tmp, sizeof(test_t));
        free(tmp);

        destroy_whole(test_arr, 3);
    }

#ifdef _WIN32
    system("pause");
#endif

    return 0;
}