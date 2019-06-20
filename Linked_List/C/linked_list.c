#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"

int list_count(linked_list *list)
{
	int cnt = 0;
	
	while (list) {
		list = list->next;
		cnt++;
	}
	return cnt;
}

linked_list* list_get_tail(linked_list *list)
{
	if(!list)
		return NULL;
		
	linked_list *cur = list;
	while (cur->next)
		cur = cur->next;
	return cur;
}

/* return node->next whereas node is the node we want to delete it */
linked_list* list_delete_node(linked_list *node)
{
	if (!node)
		return NULL;
	
	linked_list *next = node->next;
	free(node);
	
	return next;
}

void list_insert_head(linked_list *list, void *item)
{
	linked_list *node = (linked_list*)malloc(sizeof(linked_list));
	if (node) {
		node->next = (list)? NULL : list;
		node->item = item;
	}
}

void list_insert_tail(linked_list *list, void *item)
{	
	linked_list *tail = list_get_tail(list);
	
	linked_list *node = (linked_list*)malloc(sizeof(linked_list));
	if (!node)
		return;
	
	node->item = item;
	node->next = NULL;
	if (tail)
		tail->next = node;
	else
		tail = node;  
}

linked_list* list_delete_head(linked_list *list)
{
	return list_delete_node(list);
}

linked_list* list_delete_tail(linked_list *list)
{
	if (!list)
		return NULL;
	
	linked_list *slower = list;
	linked_list *faster = list->next;
	
	if (!faster) {
		return list_delete_node(list);
	}
	
	while (faster->next) {
		faster = faster->next;
		slower = slower->next;
	}
	slower->next = list_delete_node(faster);
	
	return list;
}
