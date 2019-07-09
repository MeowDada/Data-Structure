#include "object.h"

static inline void reset_object_funcptr(object_t *obj)
{
    if (!obj)
        return;
    
    obj->print_func = NULL;
    obj->to_string_func = NULL;
    obj->content_destructor = NULL;
    obj->equal_func = NULL;
}

static inline void object_funcptr_set_by_other_object(object_t *src, object_t *tar)
{
    if (!src || !tar)
        return;

    src->print_func = tar->print_func;
    src->to_string_func = tar->to_string_func;
    src->content_destructor = tar->content_destructor;
    src->equal_func = tar->equal_func;
}

/* Create & Destroy operation */
object_t *object_create(void *data, size_t size)
{
    if (!data || size < 0) {
        fprintf(stderr, "[object_create] Cannot create a object with NULL pointer or size < 0!\n");
        return NULL;
    }

    object_t *obj = (object_t*)malloc(sizeof(object_t));
    if (!obj)
        return NULL;

    obj->content = malloc(size);
    if (!obj->content) {
        free(obj);
        return NULL;
    }

    memcpy(obj->content, data, size);
    obj->size = size;
    reset_object_funcptr(obj);

    return obj;
}

object_t *object_copy(object_t *src)
{
    if (!src)
        return NULL;

    object_t *copy = object_create(src->content, src->size);
    if (!copy)
        return NULL;
    
    object_funcptr_set_by_other_object(copy, src);

    return copy;
}

void object_destroy(object_t **obj)
{
    if (!obj) {
        fprintf(stderr, "[object_destroy] No need to destroy a NULL pointer\n");
        return;
    }
    
    // Call the corresponding destructor of the content if it exist
    if ((*obj)->content_destructor)
        (*(*obj)->content_destructor)((*obj)->content);
    else {
        free((*obj)->content);
        (*obj)->content = NULL;
    }

    free(*obj);
    *obj = NULL;
}

/* Utilites */
int object_equal(object_t *src, object_t *tar)
{
    if (!src && !tar)
        return 1;
    
    if (src && tar) {
        if (src->equal_func && tar->equal_func && src->content && tar->content) {
            return (*src->equal_func)(tar->content) && (*tar->equal_func)(src->content);
        }
        return 0;
    }
    
    return 0;
}

void object_print(object_t *obj)
{
    if (!obj)
        return;
    
    (*obj->print_func)(obj->content);
}

const char *object_to_string(object_t *obj)
{
    if (!obj)
        return NULL;

    return (*obj->to_string_func)(obj->content);
}

void object_clear_content(object_t *obj)
{
    if (!obj) {
        fprintf(stderr, "[object_clear_content] Wont do anything with a null pointer input.\n");
        return;
    }
    
    if(obj->content_destructor)
        (*obj->content_destructor);
    else {
        free(obj->content);
        obj->content = NULL;
        reset_object_funcptr(obj);
    }
}

int object_set_content(object_t *obj, void *data, size_t size)
{
    if (!obj || !data || size < 0) {
        fprintf(stderr, "[object_set_content] Invalid operation!!! There are 3 possible reasons:\n");
        fprintf(stderr, "                 (1) The object is a NULL pointer\n");
        fprintf(stderr, "                 (2) The data is a NULL pointer\n");
        fprintf(stderr, "                 (3) The parameter \'size\' is smaller than 0\n");
        return 0;
    }
    
    // Re-allocate the object->content space if needed
    if (obj->content && obj->size != size) {
        free(obj->content);
        obj->content = malloc(size);
        if (!obj->content) {
            fprintf(stderr, "[object_set_content] Reallocate Failed!\n");
            return 0;
        }
    }
    else if(!obj->content)
        obj->content = malloc(size);

    if (obj->content) {
        memcpy(obj->content, data, size);
        obj->size = size;
    }
    else {
        fprintf(stderr, "[object_set_content] Object content has no memory assigned!\n");
        return 0;
    }
    return 1;
}

void object_set_equal_func(object_t *obj, int (*equal_func)(void*))
{
    if (!obj || !equal_func)
        return;
    
    obj->equal_func = equal_func;
}

void object_set_to_string_func(object_t *obj, const char *(*to_string_func)(void*))
{
    if (!obj || !to_string_func)
        return;
    
    obj->to_string_func = to_string_func;
}

void object_set_print_func(object_t *obj, void (*print_func)(void*))
{
    if (!obj || !print_func)
        return;
    
    obj->print_func = print_func;
}

void object_set_destructor(object_t *obj, void (*destructor)(void*))
{
    if (!obj || !destructor)
        return;
    
    obj->content_destructor = destructor;
}