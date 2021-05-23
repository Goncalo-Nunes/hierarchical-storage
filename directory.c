/*
 * File:  directory.c
 * Author:  Gonçalo Nunes (99074)
 * Description: Functions to manipulate the directory structure.
*/


#include "auxiliary.h"

/* Allocates memory to the directory's name and initializes it with the given name.
 * Returns the directory. */
Directory initialize_directory_name(Directory directory, char *name) {
    directory.name = safe_malloc((strlen(name) + 1) * sizeof(char));
    strcpy(directory.name, name);

    return directory;
}


/* Allocates memory to the directory's path and initializes it with the given path. 
 * Returns the directory. */
Directory initialize_directory_path(Directory directory, char *path) {
    directory.path = safe_malloc((strlen(path) + 1) * sizeof(char));
    check_memory(directory.path);
    strcpy(directory.path, path);

    return directory;
}


/* Allocates memory to the directory's value and initializes it with the given value.
 * Returns the directory. */
Directory initialize_directory_value(Directory directory, char *value) {
    directory.value = safe_malloc((strlen(value) + 1) * sizeof(char));
    check_memory(directory.value);
    strcpy(directory.value, value);

    return directory;
}


/* Allocates the memory need and Intializes the components of the given directory.
 * Returns the directory. */
Directory initialize_directory(Directory directory, char *name, char *path, char *value) {
    directory = initialize_directory_name(directory, name);
    directory = initialize_directory_path(directory, path);
    directory = initialize_directory_value(directory, value);

    return directory;
}


/* Reallocates the memory related to the directory value. 
 * Returns the directory. */
Directory change_directory_value(Directory directory, char *value) {
    directory.value = safe_realloc(directory.value, (strlen(value) + 1) * sizeof(char));
    strcpy(directory.value, value);

    return directory;
}


/* Frees all the memory allocated relative to the direcory. */
void free_directory(Directory directory) {
    free(directory.name);
    free(directory.path);
    free(directory.value);
}