#include "vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

int vector_init(vector_t *vec)
{	
	if (!vec)
		return -1;
	
	vec->size = 0;
	vec->capacity = VECTOR_INIT_CAPACITY;
	vec->items = malloc(sizeof(void*) * vec->capacity);
	
	if (!vec->items) {
		printf("%s\n", "vector_init malloc failed!");
		return -1;
	}
	
	return 0;
}

/* return -1 if null vector */
int vector_size(vector_t *vec)
{
	if (!vec)
		return -1;
		
	return vec->size;
}

/* return -1 if null vector */
int vector_capacity(vector_t *vec)
{
	if (!vec)
		return -1;
	
	return vec->capacity; 
}

/* return 0 only if it succeed to add an element, otherwise should return -1 */
int vector_add(vector_t *vec, void *item)
{
	if (!vec)
		return -1;
	
	if (vec->size == vec->capacity) {
		if (vector_resize(vec, vec->capacity * 2) != 0) {
			return -1;
		}
	}
	
	vec->items[vec->size++] = item;
	
	return 0;
}

/* return the item of the vector[index] if it is valid or return NULL */
void *vector_get(vector_t *vec, int index)
{
	if (vec && index >= 0 && index < vec->size) {
		return vec->items[index];
	}
	return NULL;
}

/* return 0 if it set new value for the vector successfully, otherwise return -1 */
int vector_set(vector_t *vec, int index, void *item)
{
	if (!vec || index >= vec->size || index < 0)
		return -1;
	
	vec->items[index] = item;
	
	return 0;
}

/* return 0 if the value has been successfully deleted, else return -1 */
int vector_delete(vector_t *vec, int index)
{
	if (!vec || index < 0 || index >= vec->size)
		return -1;
	
	vec->items[index] = NULL;
	
	int idx = 0;
	for( idx = index; idx < vec->size - 1 ; idx++) {
		vec->items[idx] = vec->items[idx + 1];
		vec->items[idx + 1] = NULL;
	}
	
	vec->size--;
	
	if (vec->size > 0 && vec->size == vec->capacity / 4) {
		if (vector_resize(vec, vec->capacity / 2) != 0) {
			return -1;
		}
	}
	
	return 0;
}

/* only free the items of this vector pointer */
void vector_free(vector_t *vec)
{
	if (!vec)
		return;
	
	free(vec->items);
}

void vector_reverse(vector_t *vec)
{
	if (!vec)
		return;
	
	int idx = 0;
	int half_idx = vec->size / 2;
	for (idx = 0; idx < half_idx; idx++) {
		void *temp = vec->items[idx];
		vec->items[idx] = vec->items[vec->size-idx-1];
		vec->items[vec->size-idx-1] = temp;
	}
}

void vector_sort(vector_t *vec, int num_elements, int size, int (*cmp)(const void *lhs,const void *rhs))
{
	qsort(vec->items, num_elements, size, cmp);
}

static int vector_resize(vector_t *vec, int capacity)
{
	if (!vec || capacity < 0)
		return -1;
	
	void **items = realloc(vec->items, sizeof(void*) * capacity);
	if (!items) {
		printf("%s", "vector_resize realloc failed!");
		return -1;	
	}
	
	vec->items = items;
	vec->capacity = capacity;
	
	return 0;
}

