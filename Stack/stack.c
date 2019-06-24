#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#include "stack.h"

void stack_impl_init(stack_impl **s)
{
    if (!s)
        return;
    
    *s = (stack_impl*)malloc(sizeof(stack_impl));
    if (!(*s))
        return;
    
    (*s)->fn_table = (stack_impl_fn_table*)malloc(sizeof(stack_impl_fn_table));
    if (!((*s)->fn_table))
        free(*s);
    return;
}

void stack_impl_by_array_init(stack *s, int size_member)
{
    if (!s)
        return;
    
    s->size = 0;
    s->capacity = MAX_STACK_SIZE;
    s->size_member = size_member;
    s->data = (void*)malloc(size_member * s->capacity);

    stack_impl_init(&s->stack_impl);
    s->stack_impl->fn_table->stack_init = _stack_impl_array_init;
    s->stack_impl->fn_table->stack_push = _stack_impl_array_push;
    s->stack_impl->fn_table->stack_pop = _stack_impl_array_pop;
    s->stack_impl->fn_table->stack_top = _stack_impl_array_top;
    s->stack_impl->fn_table->stack_isfull = _stack_impl_array_isfull;
    s->stack_impl->fn_table->stack_isempty = _stack_impl_array_isempty;
    s->stack_impl->fn_table->stack_size = _stack_impl_array_size;
    s->stack_impl->fn_table->stack_capacity = _stack_impl_array_capacity;
}

void _stack_impl_array_init(stack *s)
{

}

void _stack_impl_array_push(stack *s, void *item)
{
    if (!s || !item || s->size==s->capacity)
        return;

    void *location = (char*)s->data + (s->size * s->size_member);
    memcpy(location, item, s->size_member);
    s->size++;
}

void *_stack_impl_array_pop(stack *s)
{
    if (!s)
        return NULL;
    
    void* location = (char*)s->data + ((s->size-1) * s->size_member);
    s->size--;

    return location;
}

void *_stack_impl_array_top(stack *s)
{
    if (!s)
        return NULL;
    
    return (char*)s->data + ((s->size - 1)*s->size_member);
}

int _stack_impl_array_isfull(stack *s)
{
    if (!s)
        return -1;
    
    return (s->size==s->capacity)? 1 : 0;
}

int _stack_impl_array_isempty(stack *s)
{
    if (!s)
        return -1;
    
    return (s->size==0)? 1 : 0;
}

int _stack_impl_array_size(stack *s)
{
    if (!s)
        return -1;
    
    return s->size;
}

int _stack_impl_array_capacity(stack *s)
{
    if (!s)
        return -1;
    
    return s->capacity;
}

void stack_impl_by_vector_init(stack *s, int size_number)
{

}

/* Function pointers for determining which kinds of implementations is adapted */
static void (*stack_impl_fptr[])(stack* s, int size_member) = {
    stack_impl_by_array_init,
    stack_impl_by_vector_init
};

/* Operations */
void stack_init(stack *s, stack_impl_type type, int size_member)
{
    (*stack_impl_fptr[type])(s, size_member);
}

void stack_push(stack *s, void *item)
{
    (*s->stack_impl->fn_table->stack_push)(s, item);
}

void *stack_pop(stack *s)
{
    return (*s->stack_impl->fn_table->stack_pop)(s);
}

void *stack_top(stack *s)
{
    return (*s->stack_impl->fn_table->stack_top)(s);
}

void stack_clear(stack *s)
{
    (*s->stack_impl->fn_table->stack_clear)(s);
}

int stack_isfull(stack *s)
{
    return (*s->stack_impl->fn_table->stack_isfull)(s);
}

int stack_isempty(stack *s)
{
    return (*s->stack_impl->fn_table->stack_isempty)(s);
}

int stack_size(stack *s)
{
    return (*s->stack_impl->fn_table->stack_size)(s);
}

int stack_capacity(stack *s)
{
    return (*s->stack_impl->fn_table->stack_capacity)(s);
}