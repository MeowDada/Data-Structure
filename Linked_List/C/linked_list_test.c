#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"

#define PRINT_PER_LOOP  10000000
#define TEST_LOOP_SIZE 100000000

int main(int argc, char **argv)
{
	int arr[] = {1,2,3,4,5};
	int i = 0;
	linked_list *list = NULL;
	
	for (i = 0; i < 5; i++)
		list = list_insert_tail(list, &arr[i], sizeof(int));
	
	list_print_range(list, 0, 5, _print_fptr[LIST_PRINT_INT]);
	list_print_range(list, 2, 4, _print_fptr[LIST_PRINT_INT]);
	
	/* Check for the basic operation is working fine*/
	list_print_all(list, _print_fptr[LIST_PRINT_INT]); // 1 2 3 4 5
	
	list = list_delete_tail(list);
	list = list_delete_head(list);
	list_print_all(list, _print_fptr[LIST_PRINT_INT]); // 2 3 4
	
	list = list_delete_tail(list);
	list = list_delete_tail(list);
	list_print_all(list, _print_fptr[LIST_PRINT_INT]); // 2
	
	list = list_delete_tail(list);
	list_print_all(list, _print_fptr[LIST_PRINT_INT]); // 
	
	/* Check what will happend if we delete a Null linked list */ 
	list = list_delete_tail(list);
	list = list_delete_tail(list);
	list = list_delete_head(list);
	list = list_delete_tail(list);
	list = list_delete_head(list);
	list = list_delete_head(list);
	
	/* To check if there is any memory leak */
	for (i = 0; i < TEST_LOOP_SIZE; i++) {
		if ((i % PRINT_PER_LOOP)==0)
			printf("#Loop = %d\n", i);
		list = list_insert_tail(list, &arr[0], sizeof(int));
		list = list_insert_tail(list, &arr[1], sizeof(int));
		list = list_insert_tail(list, &arr[2], sizeof(int));
		list = list_insert_tail(list, &arr[3], sizeof(int));
		list = list_delete_tail(list);
		list = list_delete_head(list);
		list = list_delete_head(list);
		list = list_delete_tail(list);
	}
	
	system("pause");
	
	return 0;
}
