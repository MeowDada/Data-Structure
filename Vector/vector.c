#include "vector.h"
#include <stdio.h>
#include <stdlib.h>

/* initiate a vector only when it have not been initiated before */
int vector_init(vector_t *vec)
{
	if(vec)
		return;
	
	vec->size = 0;
	vec->capacity = VECTOR_INIT_CAPACITY;
	vec->data = malloc(sizeof(void*) * vec->capacity);
	
	if (!vec->data) {
		fprintf(stderr, "vector_init malloc failed!");
		return -1;
	}
	
	return 0;
}

int vector_size(vector_t *vec)
{
	if (!vec)
		return -1;
		
	return vec->size;
}

int vector_capacity(vector_t *vec)
{
	if (!vec)
		return -1;
	
	return vec->capacity; 
}

void vector_add(vector_t *vec, void *val);
void vector_get(vector_t *vec, int index);
void vector_set(vector_t *vec, int index, void *value);
void vector_delete(vector *vec, int index);
void vector_free(vector_t *vec);

static void vector_resize(vector_t *vec, int capacity)
{
	if (!vec || capacity < 1)
		return -1;
	
	void **items = realloc(vec->items, sizeof(void*) * capacity);
	if (!items) {
		fprintf(stderr, "vector_resize realloc failed!");
		return -1;	
	}
	
	vec->items = items;
	vec->capacity = capacity;
	
	return 0;
}

