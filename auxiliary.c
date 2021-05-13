#include "auxiliary.h"

/* Reads de user's input and returns a pointer to the inserted 
input based on the argument. The argument indicates the final character to read.*/
char *read_input(char end_char) {
    int size = 8, i = 0, flag = NO_CHAR_FOUND;
    char c = '_';
    char* string = malloc(size * sizeof(char));
    check_memory(string);

    while ((c = getchar()) != '\n') {

        if (c != ' ')
            flag = CHAR_FOUND;

        if (flag == CHAR_FOUND) {
            if (c == end_char)
                break;
            string[i++] = c;
        }

        if (i == size) {
            size *= 2;
            string = safe_realloc(string, size * sizeof(char));
        }
    }

    /*  if (c != '\n')
        clear_line(); 
    */
    string[i++] = '\0';
    string = safe_realloc(string, i);
    return string;
}


/* Checks if the given pointer is valid. If not, prints an error message 
indicating that there is no memory available and exits the program. */
void check_memory(void *memory) {
    if (memory == NULL) {
        printf("%s", "no memory");
        exit(137);
    }
}

/* Reallocates memory based on the given pointer ans size. If this operation
is not possible prints an error message and exists the program. */
char *safe_realloc(void *ptr, int size) {
  void *newPtr = realloc(ptr, size);
  if (newPtr == NULL) { 
    free(ptr);
    check_memory(newPtr);
  }
  return newPtr;
}

/* Reads the remainder of the user's input that was not stored in memory
because it was not relevant. */
void clear_line() {
    char c;
    while((c = getchar()) != '\n' && c != ' ');
}



