#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"

#define PRINT_PER_LOOP  1000000
#define TEST_LOOP_SIZE 10000000

int main(int argc, char **argv)
{
	int arr[] = {1,2,3,4,5};
	int i = 0;
	linked_list *list = NULL;
	
	for (i = 0; i < 5; i++)
		list = list_insert_tail(list, &arr[i], sizeof(int));

	list_print_range(list, 0, 5, list_print_int);
	list_print_range(list, 2, 4, list_print_int);
	
	/* Check for the basic operation is working fine*/
	list_print_all(list, list_print_int); // 1 2 3 4 5
	
	list = list_delete_tail(list);
	list = list_delete_head(list);
	list_print_all(list, list_print_int); // 2 3 4
	
	list = list_delete_tail(list);
	list = list_delete_tail(list);
	list_print_all(list, list_print_int); // 2
	
	list = list_delete_tail(list);
	list_print_all(list, list_print_int); // PRINT NOTHING
	
	/* Check what will happend if we delete a Null linked list */ 
	list = list_delete_tail(list);
	list = list_delete_tail(list);
	list = list_delete_head(list);
	list = list_delete_tail(list);
	list = list_delete_head(list);
	list = list_delete_head(list);
	
	/* Test utility 'reverse' */
	list = list_insert_head(list, &arr[4], sizeof(int));
	list = list_reverse(list);
	list_print_all(list, list_print_int); // 5
	
	list = list_insert_head(list, &arr[3], sizeof(int));
	list = list_insert_head(list, &arr[2], sizeof(int));
	list = list_insert_head(list, &arr[1], sizeof(int));
	list = list_insert_head(list, &arr[0], sizeof(int));
	list_print_all(list, list_print_int); // 1 2 3 4 5
	
	list = list_reverse(list);
	list_print_all(list, list_print_int); // 5 4 3 2 1
	
	list = list_delete_tail(list);
	list = list_delete_head(list);
	list = list_delete_head(list);
	list = list_delete_tail(list);
	list = list_reverse(list);
	list_print_all(list, list_print_int); // 3
	
	list = list_delete_tail(list);
	list_print_all(list, list_print_int); // PRINT NOTHING
	
	/* Combine our list with different data type */
	char *test_str = "Abner_win";
	char *test_char = "c";
	float num = 1.2345;
	float *test_float = &num;
	printf("sizeof(test_str) = %d\n", sizeof(test_str));
	
	list = list_insert_head(list, &arr[0], sizeof(int));
	list_print_range(list, 0, 1, list_print_int);

	list = list_insert_head(list, test_str, sizeof(char)*strlen(test_str));
	list_print_range(list, 0, 1, list_print_string);

	list = list_insert_head(list, test_char, sizeof(char));
	list_print_range(list, 0, 1, list_print_char);

	list = list_insert_head(list, test_float, sizeof(float));
	list_print_range(list, 0, 1, list_print_float);
	
	list = list_delete_tail(list);
	list = list_delete_head(list);
	list = list_delete_head(list);
	list = list_delete_tail(list);
	
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

	for (i = 0; i < TEST_LOOP_SIZE; i++) {
		if ((i % PRINT_PER_LOOP)==0)
			printf("#Loop = %d\n", i);
		list = list_insert_head(list, &arr[0], sizeof(int));
		list = list_insert_head(list, &arr[1], sizeof(int));
		list = list_insert_head(list, &arr[2], sizeof(int));
		list = list_insert_head(list, &arr[3], sizeof(int));
		list = list_clear(list);
		// list_print_all(list, _print_fptr[LIST_PRINT_INT]);
	}
	
	return 0;
}
