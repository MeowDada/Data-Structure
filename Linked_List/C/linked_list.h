#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_ 

typedef struct linked_list {
	void *item;
	struct linked_list *next;
} linked_list;

int list_count(linked_list *list);
linked_list* list_get_node(linked_list *list, int index);

linked_list* list_insert_head(linked_list *list, void *item, size_t data_size);
linked_list* list_insert_tail(linked_list *list, void *item, size_t data_size);
linked_list* list_delete_head(linked_list *list);
linked_list* list_delete_tail(linked_list *list);
linked_list* list_search(linked_list *list, void *item);
linked_list* list_delete_node(linked_list *list, linked_list *target);
linked_list* list_reverse(linked_list *list);

void list_print_node(linked_list *node, void (*fptr)(void *item));
void list_print_all(linked_list *list, void (*fptr)(void *item));
void list_print_range(linked_list *list, int start, int end, void (*fptr)(void *item));

/* define function to print specific data type */
void _print_int(void *item);
void _print_float(void *item);
void _print_double(void *item);
void _print_binary(void *item);
void _print_hex(void *item);
void _print_char(void *item);
void _print_string(void *item);

enum list_print_type {
	LIST_PRINT_INT,
	LIST_PRINT_FLOAT,
	LIST_PRINT_DOUBLE,
	LIST_PRINT_BINARY,
	LIST_PRINT_HEX,
	LIST_PRINT_CHAR,
	LIST_PRINT_STRING
};

static void *_print_fptr[] = {
	_print_int,
	_print_float,
	_print_double,
	_print_binary,
	_print_hex,
	_print_char,
	_print_string 
};

#endif
