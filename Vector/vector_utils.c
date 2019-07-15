#include <stdio.h>

#include "vector.h"

void vector_check_all_content_exist(vector_t *vec)
{
    fprintf(stdout, "\n");
    fprintf(stdout, "============  [DEBUG] CHECK VECTOR STATUS START ============\n");
    if (!vec) {
        fprintf(stderr, "[vector_check_all_content_exist] Cannot use null vector as input!\n");
        fprintf(stdout, "============  [DEBUG] CHECK VECTOR STATUS DONE ============\n");
        fprintf(stdout, "\n");
        return;
    }
    fprintf(stdout, "( size , capacity ) of this vector = ( %d , %d )\n", vec->size, vec->capacity);
    if (vec->items) {
        fprintf(stdout, "vector items array is alive !\n");
        int i = 0;
        for (i = 0; i < vec->capacity; i++) {
            if (vec->items[i]) {
                if (vec->items[i]->content) {
                    if (vec->items[i]->_has_set_value)
                        fprintf(stdout, "#items[%04d] (O) -> content_ptr (O) -> value (O) and size = %4d\n", i, vec->items[i]->size);
                    else
                        fprintf(stdout, "#items[%04d] (O) -> content_ptr (O) -> value (X) and size = %4d\n", i, vec->items[i]->size);
                }
                else{
                    fprintf(stdout, "#items[%04d] (O) -> content_ptr (X)\n", i);
                }
            }
            else {
                fprintf(stdout, "#items[%04d] (X)\n", i);
            }
        }
    }
    else {
        fprintf(stderr, "vector items array is NULL !\n");
        fprintf(stdout, "============  [DEBUG] CHECK VECTOR STATUS DONE ============\n");
        fprintf(stdout, "\n");
        return;
    }
    fprintf(stdout, "============  [DEBUG] CHECK VECTOR STATUS DONE ============\n");
    fprintf(stdout, "\n");

#ifdef _WIN32
    system("pause");
#endif
}
