#ifndef _VECTOR_H_
#define _VECTOR_H_

#define VECTOR_INIT_CAPACITY 32

typedef struct vector_t {
	int size;
	int capacity;
	void **item;
} vector_t;

int vector_init(vector_t *vec);
int vector_size(vector_t *vec);
int vector_capacity(vector_t *vec);
int vector_add(vector_t *vec, void *val);
void *vector_get(vector_t *vec, int index);
void vector_set(vector_t *vec, int index, void *value);
void vector_delete(vector *vec, int index);
void vector_free(vector_t *vec);
static void vector_resize(vector_t *vec, int capacity);

#endif /* _VECTOR_H_ */
