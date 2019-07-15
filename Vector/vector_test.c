#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"

#define TEST_VECTOR_LOOP 10000

int str_cmp(const void* lhs, const void* rhs);

int main(int argc, char **argv)
{
    vector_t *v = vector_create();
    int i = 0;
    printf("%d\n", sizeof("Bonjour"));
	printf("(size / capacity) = ( %d, %d )\n", vector_size(v), vector_capacity(v));
    vector_add(v, "Bonjour", sizeof("Bonjour"));
    printf("first element size = %d\n", v->items[0]->size);
    vector_add(v, "tout", sizeof("tout"));
    vector_add(v, "le", sizeof("le"));
    vector_add(v, "monde", sizeof("monde"));

    for (i = 0; i < vector_size(v); i++)
        printf("vec[%d] = %s\n", i, (char*)vector_get(v, i));
    printf("\n");

    vector_dump_status(v);
    vector_delete(v, 3);
    vector_dump_status(v);
    vector_delete(v, 2);
    vector_dump_status(v);
    vector_delete(v, 0);
    vector_dump_status(v);

    for (i = 0; i < vector_size(v); i++)
        printf("%s ", (char *) vector_get(v, i));
    printf("\n");

    vector_check_all_content_exist(v);

    vector_set(v, 0, "Hello", sizeof("Hello"));
    vector_dump_status(v);
    for (i = 0; i < vector_size(v); i++)
        printf("%s ", (char *) vector_get(v, i));
    printf("\n");

    vector_add(v, "Happy_World", sizeof("Happy_World"));
    vector_dump_status(v);

    for (i = 0; i < vector_size(v); i++)
        printf("%s ", (char *) vector_get(v, i));
    printf("\n");

	vector_reverse(v);
	for (i = 0; i < vector_size(v); i++)
        printf("%s ", (char *) vector_get(v, i));
    printf("\n");

	vector_add(v, "Bonjour", sizeof("Bonjour"));
    vector_add(v, "tout", sizeof("tout"));
    vector_add(v, "le", sizeof("le"));
    vector_add(v, "monde", sizeof("monde"));

	printf("size of this vector = %d\n", vector_size(v));
	vector_sort(v, vector_size(v), sizeof(object_t), str_cmp);
	for (i = 0; i < vector_size(v); i++)
        printf("%s ", (char *) vector_get(v, i));
    printf("\n");

    vector_check_all_content_exist(v);

    // Test for memory leak
    for (i = 0; i < TEST_VECTOR_LOOP; i++) {
        if (i % (TEST_VECTOR_LOOP/10)==0)
            fprintf(stdout, "#Loop = %d\n", i);
        vector_add(v, "Bonjour", sizeof("Bonjour"));
        // vector_check_all_content_exist(v);
        vector_add(v, "tout", sizeof("tout"));
        // vector_check_all_content_exist(v);
        vector_add(v, "le", sizeof("le"));
        // vector_check_all_content_exist(v);
        vector_add(v, "monde", sizeof("monde"));
        // vector_check_all_content_exist(v);
        vector_delete(v, 0);
        // vector_check_all_content_exist(v);
        vector_delete(v, 0);
        // vector_check_all_content_exist(v);
        vector_delete(v, 0);
        // vector_check_all_content_exist(v);
        vector_delete(v, 0);
        // vector_check_all_content_exist(v);
    }

    vector_check_all_content_exist(v);

    printf("FREEing!\n");
    vector_free(v);
    v = NULL;

#ifdef _WIN32
    system("pause");
#else
#endif

	return 0;
}

int str_cmp(const void *lhs, const void *rhs)
{
	object_t *a = (object_t*)lhs;
	object_t *b = (object_t*)rhs;
	return strlen((char*)a->content) > strlen((char*)b->content) ? 1 : 0;
}
