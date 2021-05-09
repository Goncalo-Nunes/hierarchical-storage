#ifndef AUXILIARY_H_INCLUDE
#define AUXILIARY_H_INCLUDE


#include <stdio.h>
#include <stdlib.h>
#include <string.h>



/* Function Prototipes */
char *read_input();
void check_memory(void *memory);
char *safeRealloc(void *ptr, int size);

#endif