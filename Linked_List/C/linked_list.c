#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"

linked_list* list_get_node(linked_list *list, int index)
{
	if (!list)
		return NULL;
	
	int cur_index = 0;	
	linked_list *cur_node = list;
	while (cur_node && cur_index < index)
	{
		cur_node = cur_node->next;
		cur_index++;
	}
	
	return (cur_index==index)? cur_node : NULL;
}

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
	cur->next = NULL;
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

linked_list* list_delete_node(linked_list *list, linked_list *node)
{
	if (!list || !node)
		return NULL;
	
	linked_list *head = list;
	linked_list *cur = head;
	linked_list *target = node;
	
	if (head==target) {
		linked_list *next = head->next;
		free(head->item);
		free(head);
		return next; 
	}
	
	while (cur && cur->next != target){
		cur = cur->next;
	}
	if (!cur)
		return head;
	
	if (cur->next==target) {
		cur->next = target->next;
		free(target->item);
		free(target);
	}
	
	return head;
}

linked_list* list_insert_head(linked_list *list, void *item, size_t data_size)
{
	if (!item || data_size <= 0)
		return NULL;
	
	linked_list *node = list_create_node(item, data_size);
	if (!node)
		return list;
	
	if (list) 
		node->next = list;
		
	return node;
}

linked_list* list_insert_tail(linked_list *list, void *item, size_t data_size)
{	
	linked_list *node = list_create_node(item, data_size);
	if (!node)
		return list;
	
	linked_list *tail = list_get_tail(list);
	if (tail)
		tail->next = node;
	else
		list = node;
	
	return list;
}

linked_list* list_delete_head(linked_list *list)
{
	return list_delete_node(list, list);
}

linked_list* list_delete_tail(linked_list *list)
{
	if (!list)
		return NULL;
	
	linked_list *slower = list;
	linked_list *faster = list->next;
	
	if (!faster) {
		return list_delete_node(list, list);
	}
	
	while (faster->next) {
		faster = faster->next;
		slower = slower->next;
	}
	slower->next = NULL;
	free(faster->item);
	free(faster);
	
	return list;
}

void list_print_node(linked_list *node, void(*fptr)(void *item))
{
	if (!node || !fptr)
		return;
	
	(*fptr)(node->item);
}

void list_print_all(linked_list *node, void (*fptr)(void *item))
{
	if (!node || !fptr) {
		printf("PRINT NOTHING!\n");
		return;
	}
	
	while (node) {
		(*fptr)(node->item);
		node = node->next;
	}
	printf("\n");
}

/* print value in index range [start,end) */
void list_print_range(linked_list *node, int start, int end, void (*fptr)(void *item))
{
	if (!node || !fptr || start < 0 || start >= end) {
		printf("PRINT NOTHING!\n");
		return;
	}
	
	linked_list* cur_node = list_get_node(node, start);
	if (!cur_node)
		return;
	
	int cnt = end - start;
	while(cur_node && cnt--)
	{
		list_print_node(cur_node, fptr);
		cur_node = cur_node->next;
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
