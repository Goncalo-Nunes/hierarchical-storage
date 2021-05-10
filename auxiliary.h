#ifndef AUXILIARY_H_INCLUDE
#define AUXILIARY_H_INCLUDE


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Represents the terminal character when reading the user's input,
indicating that spaces are allowed. */
#define SPACING '\n' 
/* Represents the terminal character when reading the user's input,
indicating that spaces are not allowed. */
#define NO_SPACING ' '

/* Indicates that no character has been found yet. */
#define NO_CHAR_FOUND 0
/* Indicates that a character was found. */
#define CHAR_FOUND 1

#define COMMAND_HELP "help" /* Command 'Help' string */
#define COMMAND_QUIT "quit" /* Command 'Quit' string */
#define COMMAND_SET "set" /* Command 'Set' string */
#define COMMAND_PRINT "print" /* Command 'Print' string */
#define COMMAND_FIND "find" /* Command 'Find' string */
#define COMMAND_LIST "list" /* Command 'List' string */
#define COMMAND_SEARCH "search" /* Command 'Search' string */
#define COMMAND_DELETE "delete" /* Command 'Delete' string */



/* Function Prototipes */
char *read_input(char end_char);
void check_memory(void *memory);
char *safe_realloc(void *ptr, int size);
void clear_line();

#endif