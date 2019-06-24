#ifndef STACK_H
#define STACK_H

#define MAX_STACK_SIZE 1024

typedef struct stack stack;

typedef enum stack_impl_type {
    STACK_IMPL_BY_ARRAY,
    STACK_IMPL_BY_VECTOR
} stack_impl_type;

typedef struct stack_impl_fn_table {
    void (*stack_init)(stack *s);
    void (*stack_push)(stack *s, void *item);
    void *(*stack_pop)(stack *s);
    void *(*stack_top)(stack *s);
    void (*stack_clear)(stack *s);
    int (*stack_isfull)(stack *s);
    int (*stack_isempty)(stack *s);
    int (*stack_size)(stack *s);
    int (*stack_capacity)(stack *s);
} stack_impl_fn_table;

typedef struct stack_impl {
    stack_impl_fn_table *fn_table;
} stack_impl;

typedef struct stack {
    int size;
    int capacity;
    void *data;
    int size_member;
    stack_impl *stack_impl;
} stack;

typedef struct stack_impl_array {
    stack_impl stack_impl;
} stack_impl_array;

typedef struct stack_impl_array_fn_table {
    stack_impl_fn_table base;
} stack_impl_array_fn_table;

void _stack_impl_array_init(stack *s);
void _stack_impl_array_push(stack *s, void *item);
void *_stack_impl_array_pop(stack *s);
void *_stack_impl_array_top(stack *s);
void _stack_impl_array_clear(stack *s);
int _stack_impl_array_isfull(stack *s);
int _stack_impl_array_isempty(stack *s);
int _stack_impl_array_size(stack *s);
int _stack_impl_array_capacity(stack *s);

typedef struct stack_impl_vector {
    stack_impl stack_impl;
} stack_impl_vector;

typedef struct stack_impl_vector_fn_table {
    stack_impl_fn_table base;
} stack_impl_vector_fn_table;

void stack_init(stack *s, stack_impl_type type, int size_member);
void stack_push(stack *s, void *item);
void *stack_pop(stack *s);
void *stack_top(stack *s);
void stack_clear(stack *s);
int stack_isfull(stack *s);
int stack_isempty(stack *s);
int stack_size(stack *s);
int stack_capacity(stack *s); 

void stack_impl_init(stack_impl **s);

#endif  /* _STACK_H_ */