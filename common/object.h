#ifndef OBJECT_H
#define OBJECT_H 

typedef struct object {
    void *content;
    size_t size;
    int _has_set_value;
    int (*equal_func)(void*);
    const char* (*to_string_func)(void*);
    void (*content_destructor)(void*);
    void (*print_func)(void*);
} object_t;

/* Create & Destroy operation */
object_t *object_create(void *data, size_t size);
object_t *object_copy(object_t *src);
void object_destroy(object_t *obj);

/* Utilites */
int object_has_set_value(object_t *obj);
int object_equal(object_t *src, object_t *tar);
void object_print(object_t *obj);
const char *object_to_string(object_t *obj);
void object_clear_content(object_t *obj);
int object_set_content(object_t *obj, void *data, size_t size);
void object_set_equal_func(object_t *obj, int (*equal_func)(void*));
void object_set_to_string_func(object_t *obj, const char *(*to_string_func)(void*));
void object_set_print_func(object_t *obj, void (*print_func)(void*));
void object_set_destructor(object_t *obj, void (*destructor)(void*));
                                    

#endif /* OBJECT_H */
