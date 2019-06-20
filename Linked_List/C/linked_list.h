#ifndf  _LINKED_LIST_H_
#define _LINKED_LIST_H_ 

typedef struct linked_list {
	void *item;
	linked_list *next;
} linked_list;

void list_count(linked_list *list);
void list_insert_head(linked_list *list, void *item);
void list_insert_tail(linked_list *list, void *item);
linked_list list_delete_head(linked_list *list);
linked_list list_delete_tail(linked_list *list);
linked_list *list_search(linked_list *list, void *item);
