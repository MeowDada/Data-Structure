#ifndef _VECTOR_H_
#define _VECTOR_H_

typedef struct vector_t {
	int size;
	int capacity;
	void **data;
} vector_t;

void vector_init(vector_t *vec);
void vector_append(vector_t *vec, void *val);
void vector_get(vector_t *vec, int index);
void vector_set(vector_t *vec, int index, void *value);
void vector_free(vector_t *vec);

#endif /* _VECTOR_H_ */
