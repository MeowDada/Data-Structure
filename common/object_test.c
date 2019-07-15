#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "object.h"

#define TEST_OBJECT_LOOP 100000
#define TEST_PRINT_PER_LOOP ((TEST_OBJECT_LOOP) / (10))
#define TEST_OBJECT_ARRAY_SIZE 1000

void object_print_int(void *data)
{
    printf("%d\n", *(int*)data);
}

void object_print_string(void *data)
{
    printf("%s\n", (char*)data);
}

int main(int argc, char **argv)
{
    // Test for initialization a object
    int value = 5;
    int *ptr = &value; 
    object_t *obj = object_create(ptr, 4);
    object_set_print_func(obj, object_print_int);
    if (obj) {
        printf("obj->size = %d\n", obj->size);
        object_print(obj);
    }

    // Test for object_copy
    object_t *copy = object_copy(obj);
    if (copy) {
        printf("copy->size = %d\n", copy->size);
        object_print(copy);
    }

    // Test for object clear and set content 
    char *str = "Hello World!!";
    int sizeof_str = strlen(str)+1;
    printf("%d\n", sizeof("Hello World!!"));
    printf("[Before Clear] copy->size = %d\n", copy->size);
    printf("[Before Clear] copy.content = %d\n", *(int*)copy->content);
    object_clear_content(copy);
    printf("[After Clear] copy->size = %d\n", copy->size);
    if (!copy->content)
        printf("[After Clear] copy.content = NULL\n");
    object_set_content(copy, str, sizeof_str);
    object_set_print_func(copy, object_print_string);
    printf("[After Set] copy->size = %d\n", copy->size);
    printf("[After Set] copy.content = %s\n", (char*)copy->content);
    object_print(copy);


    // Test for object_destroy
    object_destroy(obj);
    obj = NULL;
    object_destroy(copy);
    copy = NULL;
    if (obj)
        fprintf(stderr, "Destroy might failed! obj is a danling pointer\n");
    else
        fprintf(stdout, "Destroy object successfully\n");

    // Check for memory leak
    int i = 0;
    int value_arr[TEST_OBJECT_ARRAY_SIZE];
    for ( i = 0; i < TEST_OBJECT_ARRAY_SIZE; i++)
        value_arr[i] = i;

    for ( i = 0; i < TEST_OBJECT_LOOP; i++) {
        object_t **arr = (object_t**)malloc(sizeof(object_t*)*TEST_OBJECT_ARRAY_SIZE);
        int j = 0;
        for (j = 0; j < TEST_OBJECT_ARRAY_SIZE; j++)
            arr[j] = object_create(&value_arr[j] ,sizeof(int));
        
        for (j = 0; j < TEST_OBJECT_ARRAY_SIZE; j++) {
            object_destroy(arr[j]);
            arr[j] = NULL;
        }
        
        free(arr);
        if (i % TEST_PRINT_PER_LOOP == 0)
            fprintf(stdout, "#Loop = %d\n", i);
    }
    

#ifdef _WIN32
    system("pause");
#endif

    return 0;
}