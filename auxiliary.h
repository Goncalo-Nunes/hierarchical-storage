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

#define BUF_SIZE 65536

#define COMMAND_HELP "help" /* Command 'Help' string */
#define COMMAND_QUIT "quit" /* Command 'Quit' string */
#define COMMAND_SET "set" /* Command 'Set' string */
#define COMMAND_PRINT "print" /* Command 'Print' string */
#define COMMAND_FIND "find" /* Command 'Find' string */
#define COMMAND_LIST "list" /* Command 'List' string */
#define COMMAND_SEARCH "search" /* Command 'Search' string */
#define COMMAND_DELETE "delete" /* Command 'Delete' string */
#define COMMAND_HELP_DESCRIPTION "Imprime os comandos disponíveis."
#define COMMAND_QUIT_DESCRIPTION "Termina o programa."
#define COMMAND_SET_DESCRIPTION "Adiciona ou modifica o valor a armazenar."
#define COMMAND_PRINT_DESCRIPTION "Imprime todos os caminhos e valores."
#define COMMAND_FIND_DESCRIPTION "Imprime o valor armazenado."
#define COMMAND_LIST_DESCRIPTION "Lista todos os componentes imediatos de um sub-caminho."
#define COMMAND_SEARCH_DESCRIPTION "Procura o caminho dado um valor."
#define COMMAND_DELETE_DESCRIPTION "Apaga um caminho e todos os subcaminhos."

#define ERROR_NOT_FOUND "not found"
#define ERROR_NO_DATA "no data"
#define ERROR_NO_MEMORY "No memory."

#define ARGS_FORMAT_SPACING " %[^\n]"
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
    struct Node *firstChild;
    struct Node *nextSibling;
} Node;











/* Function Prototipes */
char *read_input(char end_char);
void check_memory(void *memory);
char *safe_realloc(void *ptr, int size);
void clear_line();
char *concatenate(const char *string1, const char *string2);
char peek_nonspace();


Directory initialize_directory_name(Directory directory, char *name);
Directory initialize_directory_path(Directory directory, char *path);
Directory initialize_directory_value(Directory directory, char *value);
Directory initialize_directory(Directory directory, char *name, char *path, char *value);
Directory change_directory_value(Directory directory, char *value);

Node *init_tree();
Node *new_node(Directory directory);
Node *insert_sibling(Node *node, Directory directory);
Node *insert_child(Node *node, Directory directory);
void print_tree(Node *tree);
void *create_node_with_path(Node *root, char *path);
void print_nodes_with_value(Node *node);
void *find_node(Node *root, char *path);
int count_children(Node *node);
void *search_value(Node *node, char *value);

int less(char *s1, char *s2);
void exch(char **s1_ptr, char **s2_ptr);
void insertion_sort(char **string, int l, int r);
int partition(char **string, int l, int r);
void quick_sort(char **string, int l, int r);

void printTabs(int count);
void printTreeRecursive(Node *node, int level);


void handle_command_help();
void handle_command_set(Node *root);
void handle_command_print(Node *root);
void handle_command_find(Node *root);
void handle_command_list(Node *root);
void handle_command_search(Node *root);

#endif