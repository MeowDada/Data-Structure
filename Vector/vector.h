#ifndef VECTOR_H
#define VECTOR_H

#define VECTOR_INIT_CAPACITY 1
 
typedef struct vector_t {
	int size;
	int capacity;
	void **items;
} vector_t;

int vector_init(vector_t *vec);
int vector_size(vector_t *vec);
int vector_capacity(vector_t *vec);
int vector_add(vector_t *vec, void *item);
void *vector_get(vector_t *vec, int index);
int vector_set(vector_t *vec, int index, void *item);
int vector_delete(vector_t *vec, int index);
void vector_free(vector_t **vec);
void vector_reverse(vector_t *vec);
void vector_sort(vector_t *vec, int num_elements, int size, int (*cmp)(const void *lhs, const void *rhs));
static int vector_resize(vector_t *vec, int capacity);

#endif /* _VECTOR_H_ */
