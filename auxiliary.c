/*
 * File:  auxiliary.c
 * Author:  Gonçalo Nunes (99074)
 * Description: Contains the auxiliary functions that all files can use.
*/


#include "auxiliary.h"


/* Checks if the given pointer is valid. If not, prints an error message 
 * indicating that there is no memory available and exits the program.
*/
void check_memory(void *memory) {
    if (memory == NULL) {
        puts(ERROR_NO_MEMORY);
        exit(EXIT_FAILURE);
    }
}


/* Reallocates memory in the heap based on the given pointer and size.
 * If this operation is not possible prints an error message and
 * exists the program.
*/
void *safe_realloc(void *ptr, unsigned int size) {
    void *newPtr = realloc(ptr, size);
    check_memory(newPtr); 
    return newPtr;
}


/* Allocates memory in the heap based on the given size.
 * If this operation is not possible prints an error message and 
 * exists the program. 
*/
void *safe_malloc(unsigned int size) {
    void *ptr = malloc(size);
    check_memory(ptr);
    return ptr;
}


/* Consumes the stdin characters until a nonspace character is found.
 * Returns the first nonspace character found.
*/
char peek_nonspace() {
	char c;

	while ((c = getchar()) == ' ');
	ungetc(c, stdin);
	return c;
}

