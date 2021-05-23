/*
 * File:  auxiliary.h
 * Author:  Gonçalo Nunes (99074)
 * Description: Defines all functions and structures required.
*/


#ifndef AUXILIARY_H_INCLUDE
#define AUXILIARY_H_INCLUDE


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define BUF_SIZE 65536 /* Maximum size of the user's input */
#define COMMAND_BUF_SIZE 21 /* Maximum size of the command */

#define COMMAND_HELP "help" /* Command 'Help' string */
#define COMMAND_QUIT "quit" /* Command 'Quit' string */
#define COMMAND_SET "set" /* Command 'Set' string */
#define COMMAND_PRINT "print" /* Command 'Print' string */
#define COMMAND_FIND "find" /* Command 'Find' string */
#define COMMAND_LIST "list" /* Command 'List' string */
#define COMMAND_SEARCH "search" /* Command 'Search' string */
#define COMMAND_DELETE "delete" /* Command 'Delete' string */


/* Description of the 'help' command. */
#define COMMAND_HELP_DESCRIPTION "Imprime os comandos disponíveis."
/* Description of the 'help' command. */
#define COMMAND_QUIT_DESCRIPTION "Termina o programa."
/* Description of the 'help' command. */
#define COMMAND_SET_DESCRIPTION "Adiciona ou modifica o valor a armazenar."
/* Description of the 'help' command. */
#define COMMAND_PRINT_DESCRIPTION "Imprime todos os caminhos e valores."
/* Description of the 'help' command. */
#define COMMAND_FIND_DESCRIPTION "Imprime o valor armazenado."
/* Description of the 'help' command. */
#define COMMAND_LIST_DESCRIPTION "Lista todos os componentes imediatos de um sub-caminho."
/* Description of the 'help' command. */
#define COMMAND_SEARCH_DESCRIPTION "Procura o caminho dado um valor."
/* Description of the 'help' command. */
#define COMMAND_DELETE_DESCRIPTION "Apaga um caminho e todos os subcaminhos."


#define ERROR_NOT_FOUND "not found" /* Error when a path was not found. */
#define ERROR_NO_DATA "no data" /* Error when a direcoty has no value associated. */
#define ERROR_NO_MEMORY "No memory." /* Error when there is no more meory available. */

/* Regex expression to get the user input when spaces are allowed. */
#define ARGS_FORMAT_SPACING " %[^\n]" 
/* Regex expression to get the user input when no spaces are allowed. */
#define ARGS_FORMAT_NO_SPACING " %s" 

#define TRUE 1
#define FALSE 0


/* Structures */

typedef struct Directory {
    char *name;
    char *path;
    char *value;
} Directory;


typedef struct Node {
    Directory directory;
    struct Node *parent;
    struct Node *firstChild;
    struct Node *nextSibling;
    struct Node *previousSibling;
} Node;



/* Function Prototipes */


/* Function prototypes related to the 'auxiliary.c' file. */

void check_memory(void *memory);
void *safe_realloc(void *ptr, unsigned int size);
void *safe_malloc(unsigned int size);
char peek_nonspace();


/* Function prototypes related to the 'directory.c' file. */

Directory initialize_directory_name(Directory directory, char *name);
Directory initialize_directory_path(Directory directory, char *path);
Directory initialize_directory_value(Directory directory, char *value);
Directory initialize_directory(Directory directory, char *name, char *path, char *value);
Directory change_directory_value(Directory directory, char *value);
void free_directory(Directory directory);


/* Function prototypes related to the 'general-tree.c' file. */

Node *init_tree();
Node *new_node(Directory directory);
Node *insert_sibling(Node *node, Directory directory);
Node *insert_child(Node *node, Directory directory);
void *name_is_in_children(Node *node, char *name);
Node *create_node_with_path(Node *root, char *path);
void print_nodes_with_value(Node *node);
void *find_node(Node *root, char *path);
int count_children(Node *node);
void *search_value(Node *node, char *value);
void free_node(Node *node);
void delete_node(Node *node);
void delete_children(Node *node);
Node *delete_branch(Node *node);



/* Function prototypes related to the 'sorting.c' file. */

int less(char *s1, char *s2);
void exch(char **s1_ptr, char **s2_ptr);
void insertion_sort(char **string, int l, int r);
int partition(char **string, int l, int r);
void quick_sort(char **string, int l, int r);



/* Function prototypes related to the 'commands.c' file. */

void handle_command_help();
void handle_command_set(Node *root);
void handle_command_print(Node *root);
void handle_command_find(Node *root);
void handle_command_list(Node *root);
void handle_command_search(Node *root);
void handle_command_delete(Node *root);

#endif