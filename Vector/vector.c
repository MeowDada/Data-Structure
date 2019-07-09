#include "vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

void vector_init(vector_t *vec)
{	
	if (!vec) {
		fprintf(stderr, "[vector_init] Warnning! You are initiating an NULL pointer!\n");
	}

	vec->size = 0;
	vec->capacity = VECTOR_INIT_CAPACITY;
	vec->items = (object_t*)malloc(sizeof(object_t)*vec->capacity);
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
		object_t *obj = object_create(&i, sizeof(int));
		memcpy(&(vec->items[i]), obj, sizeof(*obj));
		if (!vec->items[i].content) {
			int j = i;
			for(i = 0; i <= j; i++) {
				object_t *t = &vec->items[i];
				object_destroy(&t);
			}
			free(vec->items);
			vec->items = NULL;
			vec = NULL;
			return;
		}
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
	if (!vec)
		return;
	
	if (vec->size == vec->capacity)
		vector_resize(vec, vec->capacity * 2);
	
	if (object_set_content(&(vec->items[vec->size]), item, size))
		vec->size++;
}

/* return the item of the vector[index] if it is valid or return NULL */
void *vector_get(vector_t *vec, int index)
{
	if (vec && index >= 0 && index < vec->size) {
		return vec->items[index].content;
	}
	return NULL;
}

/* return 0 if it set new value for the vector successfully, otherwise return -1 */
void vector_set(vector_t *vec, int index, void *item, size_t size)
{
	if (!vec || index >= vec->size || index < 0, size < 0)
		return;
	
	object_set_content(&(vec->items[index]), item, size);
}

/* return 0 if the value has been successfully deleted, else return -1 */
void vector_delete(vector_t *vec, int index)
{
	if (!vec || index < 0 || index >= vec->size) {
		fprintf(stderr, "[vector_delete] delete element failed! There are 3 possible reason:\n");
		fprintf(stderr, "				 (1) Input vector pointer is a NULL pointer\n");
		fprintf(stderr, "				 (2) Index cannot be smaller than 0\n");
		fprintf(stderr, "				 (3) Index out of bound\n");
		return;
	}

	object_clear_content(&(vec->items[index]));
	
	// Move each element behind index to the front index 
	int idx = 0;
	for( idx = index; idx < vec->size - 1 ; idx++) {
		memcpy(&(vec->items[idx]), &(vec->items[idx+1]), sizeof(object_t));
	}

	// Clear the last element if exist 
	if (vec->size > 0) {
		memcpy(&vec->items[vec->size-1], &idx, sizeof(int));
		vec->size--;
	}
	
	if (vec->size > 0 && vec->size == vec->capacity / 4)
		vector_resize(vec, vec->capacity / 2);
}

void vector_free(vector_t **vec)
{
	if (!vec)
		return;
	
	// Destroy each object inside the vector
	int i = 0;
	for(i = 0; i < (*vec)->capacity; i++) {
		object_t *tmp = &(*vec)->items[i];
		object_destroy(&tmp);
	}
	
	free((*vec)->items);
	free(*vec);
	vec = NULL;
}

void vector_reverse(vector_t *vec)
{
	if (!vec)
		return;
	
	int idx = 0;
	int half_idx = vec->size / 2;
	for (idx = 0; idx < half_idx; idx++) {
		object_t *tmp = malloc(sizeof(object_t));
		memcpy(tmp, &(vec->items[idx]), sizeof(object_t));
		memcpy(&(vec->items[idx]), &(vec->items[idx+1]), sizeof(object_t));
		memcpy(&(vec->items[idx+1]), tmp, sizeof(object_t));
		free(tmp);
	}
}

void vector_sort(vector_t *vec, int num_elements, size_t size, int (*cmp)(const void *lhs,const void *rhs))
{
	qsort(vec->items, num_elements, size, cmp);
}

static void vector_resize(vector_t *vec, int capacity)
{
	if (!vec || capacity < 0) {
		fprintf(stderr, "[vector_resize] Cannot resize a NULL vector pointer or with parameter \'capacity\' < 0\n");
		return;
	}

	// Need to free object element if the size reduced
	if (vec->capacity > capacity) {
		int i = vec->capacity - 1;
		for ( ; i >= capacity; i--) {
			object_t *obj = &(vec->items[i]);
			object_destroy(&obj);
		}
	}

	object_t *items = (object_t*)realloc(vec->items, sizeof(object_t) * capacity);
	if (!items) {
		fprintf(stderr, "%s", "[vector resize] realloc failed!\n");
		return;	
	}

	vec->items = items;

	// Need to create new object for these new allocated space
	if (vec->capacity < capacity) {
		int i = vec->size;
		for ( ; i < capacity; i++) {
			object_t *obj = object_create(&i, sizeof(int));
			memcpy(&(vec->items[i]), obj, sizeof(*obj));
		}
	}

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

