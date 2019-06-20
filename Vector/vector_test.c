#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"

int str_cmp(const void* lhs, const void* rhs);

int main(int argc, char **argv)
{
	vector_t v;
	vector_init(&v);
	
	int i = 0;
	
	vector_add(&v, "Bonjour");
    vector_add(&v, "tout");
    vector_add(&v, "le");
    vector_add(&v, "monde");

    for (i = 0; i < vector_size(&v); i++)
        printf("%s ", (char *) vector_get(&v, i));
    printf("\n");

    vector_delete(&v, 3);
    vector_delete(&v, 2);
    vector_delete(&v, 1);

    vector_set(&v, 0, "Hello");
    vector_add(&v, "Happy_World");

    for (i = 0; i < vector_size(&v); i++)
        printf("%s ", (char *) vector_get(&v, i));
    printf("\n");

	vector_reverse(&v);
	for (i = 0; i < vector_size(&v); i++)
        printf("%s ", (char *) vector_get(&v, i));
    printf("\n");

	vector_add(&v, "Bonjour");
    vector_add(&v, "tout");
    vector_add(&v, "le");
    vector_add(&v, "monde");

	printf("size of this vector = %d\n", vector_size(&v));
	vector_sort(&v, vector_size(&v), sizeof(v.items[0]), str_cmp);
	for (i = 0; i < vector_size(&v); i++)
        printf("%s ", (char *) vector_get(&v, i));
    printf("\n");

    vector_free(&v);
	
	return 0;
}

int str_cmp(const void *lhs, const void *rhs)
{
	char *a = *(char**)lhs;
	char *b = *(char**)rhs;
	return strlen(a) > strlen(b) ? 1 : 0;
}
