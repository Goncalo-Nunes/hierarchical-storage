#include "auxiliary.h"


char *read_input() {
    int size = 8;
    int i = 0;
    char c = '_';
    char* string = malloc(size * sizeof(char));

    check_memory(string);

    while ((c = getchar()) != '\n') {
        if (i == size) {
            size *= 2;
            string = safeRealloc(string, size * sizeof(char));
            check_memory(string);
        }
        
        string[i++] = c;
    }
    string[i++] = '\0';
    string = safeRealloc(string, i);
    return string;
}



void check_memory(void *memory) {
    if (memory == NULL) {
        printf("%s", "no memory");
        exit(137);
    }
}


char *safeRealloc(void *ptr, int size) {
  void *newPtr = realloc(ptr, size);
  if (newPtr == NULL) { 
    free(ptr); 
  }
  return newPtr;
}