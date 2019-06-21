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

linked_list* list_create_node(void *item, size_t data_size)
{
	linked_list *node = (linked_list*)malloc(sizeof(linked_list));
	if (!node)
		return NULL;
	
	node->item = (void*)malloc(data_size);
	if (!node->item) {
		free(node);
		return NULL;
	}
	
	memcpy(node->item, item, data_size);
	node->next = NULL;
	
	return node;
}

/* return node->next whereas node is the node we want to delete it */
linked_list* list_delete_node(linked_list *node)
{
	if (!node)
		return NULL;
	
	linked_list *next = node->next;
	free(node->item);
	free(node);
	
	return next;
}

void list_insert_head(linked_list *list, void *item, size_t data_size)
{
	linked_list *node = list_create_node(item, data_size);
	if (node) {
		node->next = (list)? NULL : list;
		node->item = item;
	}
}

linked_list* list_insert_tail(linked_list *list, void *item, size_t data_size)
{	
	linked_list *node = list_create_node(item, data_size);
	
	if (!node)
		return NULL;
	
	linked_list *tail = list_get_tail(list);
	
	if (tail)
		tail->next = node;
	else
		list = node;
		
	return list;
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

void list_print_all(linked_list *node, void (*fptr)(void *item))
{
	while (node) {
		(*fptr)(node->item);
		node = node->next;
	}
	printf("\n");
}

/* print functions for specific type */
void _print_int(void *item) 
{
	printf("%d ", *(int *)item);
}

void _print_float(void *item)
{
	printf("%f ", *(float*)item);
}

void _print_double(void *item)
{
	printf("%lf ", *(double*)item);
}

void _print_binary(void *item)
{
	printf("%b ", *(int*)item);
}

void _print_hex(void *item)
{
	printf("%04X ", *(int*)item);
}

void _print_char(void *item)
{
	printf("%c ", *(char*)item);
}

void _print_string(void *item)
{
	printf("%s ", *(char**)item);
}
