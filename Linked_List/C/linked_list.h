#ifndef LINKED_LIST_H
#define LINKED_LIST_H

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
linked_list* list_clear(linked_list *list);
linked_list* list_search(linked_list *list, void *item);
linked_list* list_delete_node(linked_list *list, linked_list *target);
linked_list* list_reverse(linked_list *list);

void list_print_node(linked_list *node, void (*fptr)(void *item));
void list_print_all(linked_list *list, void (*fptr)(void *item));
void list_print_range(linked_list *list, int start, int end, void (*fptr)(void *item));

/* define function to print specific data type */
void list_print_int(void *item);
void list_print_float(void *item);
void list_print_double(void *item);
void list_print_binary(void *item);
void list_print_hex(void *item);
void list_print_char(void *item);
void list_print_string(void *item);

enum list_print_type {
	LIST_PRINT_INT,
	LIST_PRINT_FLOAT,
	LIST_PRINT_DOUBLE,
	LIST_PRINT_BINARY,
	LIST_PRINT_HEX,
	LIST_PRINT_CHAR,
	LIST_PRINT_STRING
};

#endif /* _LINKED_LIST_H_ */
