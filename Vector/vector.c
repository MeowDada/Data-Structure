#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#include "vector.h"

int vector_resize_check(vector_t *vec)
{
	if (!vec)
		return 0;
	
	if ((vec->size == vec->capacity) || vec->size <= (vec->capacity / (VECTOR_GROWTH_RATE*2)))
		return 1;

	return 0;
}

static void vector_free_element(vector_t *vec, int index)
{
	if (!vec || index < 0 || index >= vec->size)
		return;
	
	object_t *obj = vec->items[index];
	object_destroy(obj);
	obj = NULL;
	vec->size--;
}

vector_t *vector_create()
{
	vector_t *vec = (vector_t*)malloc(sizeof(vector_t));
	if (!vec)
		return NULL;
	
	vector_init(vec);
	return vec;
}

static void vector_init(vector_t *vec)
{	
	if (!vec) {
		fprintf(stderr, "[vector_init] Cannot initiate vector with a NULL pointer!\n");
		return;
	}

	vec->size = 0;
	vec->capacity = VECTOR_INIT_CAPACITY;
	vec->items = (object_t**)malloc(sizeof(object_t*)*vec->capacity);
	if (!vec->items) {
		fprintf(stderr, "%s\n", "[vector_init] malloc failed!");
		return;
	}

	/* 
	 * Initialize a fixed space when creating a new vector
	 * We'll put some garbage value inside the object in order
	 * to make the object_create operation valid.
	 */
	int i = 0;
	for(i = 0; i < vec->capacity; i++){
		/*
		vec->items[i] = (object_t*)malloc(sizeof(object_t));
		object_t *obj = object_create(&i, sizeof(int));
		memcpy(vec->items[i], obj, sizeof(object_t));
		free(obj);
		*/
		vec->items[i] = object_create(NULL, sizeof(void*));
	}
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

void vector_add(vector_t *vec, void *item, size_t size)
{
	if (!vec || !item || size<0)
		return;

	if (vector_resize_check(vec))
		vector_resize(vec, vec->capacity * VECTOR_GROWTH_RATE);

	if (object_set_content(vec->items[vec->size], item, size))
		vec->size++;
}

/* return the item of the vector[index] if it is valid or return NULL */
void *vector_get(vector_t *vec, int index)
{
	if (vec && vec->items && index >= 0 && index < vec->size) {
		return vec->items[index]->content;
	}
	return NULL;
}

void *vector_pop(vector_t *vec, int index)
{
	if (!vec || index < 0 || index >= vec->size)
		return NULL;
	
	object_t *obj = vec->items[index];
	void *data = malloc(obj->size);
	if (!data)
		return NULL;
	memcpy(data, obj->content, obj->size);

	vector_free_element(vec, index);

	int i = index;
	for (i = index; i < vec->size-1; i++) {
		object_t *cur = vec->items[i];
		object_t *next = vec->items[i+1];
		*cur = *next;
	}

	if (vector_resize_check(vec))
		vector_resize(vec, vec->capacity/VECTOR_GROWTH_RATE);

	return data;
}

/* return 0 if it set new value for the vector successfully, otherwise return -1 */
void vector_set(vector_t *vec, int index, void *item, size_t size)
{
	if (!vec || index >= vec->size || index < 0 || size < 0)
		return;
	
	object_set_content(vec->items[index], item, size);
}

void vector_delete(vector_t *vec, int index)
{
	if (!vec || index < 0 || index >= vec->size || vec->size==0) {
		fprintf(stderr, "[vector_delete] delete element failed! There are 4 possible reason:\n");
		fprintf(stderr, "				 (1) Input vector pointer is a NULL pointer\n");
		fprintf(stderr, "				 (2) Index cannot be smaller than 0\n");
		fprintf(stderr, "				 (3) Index out of bound\n");
		fprintf(stderr, "				 (4) There is no elements exist in this vector\n");
		return;
	}

	object_t *tmp = vec->items[index];
	
	// Move each element behind index to the front index 
	int idx = 0;
	for( idx = index; idx < vec->size-1; idx++)
		*vec->items[idx] = *vec->items[idx+1];
	
	*vec->items[vec->size-1] = *tmp;
	object_clear_content(vec->items[vec->size-1]);
	vec->size--;

	if (vector_resize_check(vec))
		vector_resize(vec, vec->capacity / VECTOR_GROWTH_RATE);
}

void vector_free(vector_t *vec)
{
	if (!vec)
		return;
	
	// Destroy each object inside the vector
	int i = 0;
	for(i = 0; i < vec->capacity; i++)
		object_destroy(vec->items[i]);	
	
	free(vec->items);
	vec->items = NULL;
	free(vec);
}

void vector_clear(vector_t *vec)
{
	if (!vec)
		return;
	
	int i = 0;
	for(i = 0; i < vec->size; i++) {
		object_clear_content(vec->items[i]);
		vec->items[i] = NULL;
	}
	
	vec->size = 0;
}

void vector_reverse(vector_t *vec)
{
	if (!vec)
		return;
	
	int idx = 0;
	int half_idx = vec->size / 2;
	for (idx = 0; idx < half_idx; idx++) {
		int rev_idx = (vec->size-1) - idx;
		object_t *tmp = vec->items[idx];
		vec->items[idx] = vec->items[rev_idx];
		vec->items[rev_idx] = tmp;
	}
}

void vector_sort(vector_t *vec, int num_elements, size_t size, int (*cmp)(const void *lhs,const void *rhs))
{
	qsort(vec->items, num_elements, sizeof(object_t*), cmp);
}

static void vector_resize(vector_t *vec, int capacity)
{
	if (!vec || capacity < 0) {
		fprintf(stderr, "[vector_resize] Cannot resize a NULL vector pointer or with parameter \'capacity\' < 0\n");
		return;
	}

	object_t **items = (object_t**)malloc(sizeof(object_t*) * capacity);
	if (!items) {
		fprintf(stderr, "%s", "[vector resize] realloc failed!\n");
		return;	
	}

	int i = 0;
	for (i = 0; i < capacity; i++) {
		if (i < vec->size) {
			items[i] = object_copy(vec->items[i]);
			object_destroy(vec->items[i]);
			vec->items[i] = NULL;
		}
		else
			items[i] = object_create(NULL, sizeof(void*));
	}

	free(vec->items);
	vec->items = items;
	vec->capacity = capacity;
}

void vector_dump_status(vector_t *vec)
{
	if (!vec) {
		fprintf(stderr, "[vector_dump_status] Cannot dump NULL vector pointer!\n");
		return;
	}

	fprintf(stdout, "Info of this vector:\n");
	fprintf(stdout, "[Element Counts]: %d\n", vec->size);
	fprintf(stdout, "[Capacity]:       %d\n", vec->capacity);
}

