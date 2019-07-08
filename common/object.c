#include "object.h"

static inline void initial_object_funcptr(object_t *obj)
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
    object_t *obj = (object_t*)malloc(sizeof(object_t));
    if (!obj)
        return NULL;
    
    obj->content = malloc(sizeof(size));
    if (!obj->content) {
        free(obj);
        return NULL;
    }

    memcpy(obj->content, data, size);
    obj->size = size;
    initial_object_funcptr(obj);

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
    if (!obj)
        return;
    
    // Call the corresponding destructor of the content if it exist
    if ((*obj)->content_destructor)
        (*(*obj)->content_destructor)((*obj)->content);
    else {
        free((*obj)->content);
        (*obj)->content = NULL;
    }    

    free(*obj);
    obj = NULL;
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

const char *object_to_string(object_t *obj)
{
    if (!obj)
        return NULL;

    return (*obj->to_string_func)(obj->content);
}

void object_set_content(object_t *obj, void *data, size_t size)
{
    if (!obj)
        return;
    
    realloc(obj->content, size);
    memcpy(obj->content, data, size);
}

static inline void object_set_equal_func(object_t *obj, int (*equal_func)(void*))
{
    if (!obj || !equal_func)
        return;
    
    obj->equal_func = equal_func;
}

static inline void object_set_to_string_func(object_t *obj, const char *(*to_string_func)(void*))
{
    if (!obj || !to_string_func)
        return;
    
    obj->to_string_func = to_string_func;
}

static inline void object_set_print_func(object_t *obj, void (*print_func)(void*))
{
    if (!obj || !print_func)
        return;
    
    obj->print_func = print_func;
}

static inline void object_set_destructor(object_t *obj, void (*destructor)(void*))
{
    if (!obj || !destructor)
        return;
    
    obj->content_destructor = destructor;
}