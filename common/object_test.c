#include <stdio.h>
#include "object.h"

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
    object_destroy(&obj);
    object_destroy(&copy);
    if (obj)
        fprintf(stderr, "Destroy might failed! obj is a danling pointer\n");
    else
        fprintf(stdout, "Destroy object successfully\n");
    

#ifdef _WIN32
    system("pause");
#endif

    return 0;
}