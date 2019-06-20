#ifndef _VECTOR_H_
#define _VECTOR_H_

#define VECTOR_INIT_CAPACITY 32

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
void vector_free(vector_t *vec);
static int vector_resize(vector_t *vec, int capacity);

#endif /* _VECTOR_H_ */
