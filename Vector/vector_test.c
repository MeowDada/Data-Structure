#include <stdio.h>
#include <stdlib.h> 
#include "vector.h"

int main(int argc, char **argv)
{
	vector_t *vector;
	vector_init(vector);
	printf("%d\n", vector_size(vector));
	
	return 0;
}
