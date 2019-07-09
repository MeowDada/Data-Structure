#ifndef VECTOR_H
#define VECTOR_H

#define VECTOR_INIT_CAPACITY 1

#include "object.h"

typedef struct vector_t {
	int size;
	int capacity;
	object_t *items;
} vector_t;

void vector_init(vector_t *vec);
int vector_size(vector_t *vec);
int vector_capacity(vector_t *vec);
void vector_add(vector_t *vec, void *item, size_t size);
void *vector_get(vector_t *vec, int index);
void vector_set(vector_t *vec, int index, void *item, size_t size);
void vector_delete(vector_t *vec, int index);
void vector_free(vector_t **vec);
void vector_reverse(vector_t *vec);
void vector_sort(vector_t *vec, int num_elements, size_t size, int (*cmp)(const void *lhs, const void *rhs));
void vector_dump_status(vector_t *vec);
static void vector_resize(vector_t *vec, int capacity);

#endif /* _VECTOR_H_ */
