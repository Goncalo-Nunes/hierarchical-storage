#include "auxiliary.h"


void handle_command_help() {
    puts(COMMAND_HELP ": " COMMAND_HELP_DESCRIPTION);
    puts(COMMAND_QUIT ": " COMMAND_QUIT_DESCRIPTION);
    puts(COMMAND_SET ": " COMMAND_SET_DESCRIPTION);
    puts(COMMAND_PRINT ": " COMMAND_PRINT_DESCRIPTION);
    puts(COMMAND_FIND ": " COMMAND_FIND_DESCRIPTION);
    puts(COMMAND_LIST ": " COMMAND_LIST_DESCRIPTION);
    puts(COMMAND_SEARCH ": " COMMAND_SEARCH_DESCRIPTION);
    puts(COMMAND_DELETE ": " COMMAND_DELETE_DESCRIPTION);
}



void handle_command_set(Node *root) {
    Node *node;
    char *path = read_input(NO_SPACING);
    char *value;

    node = create_node_with_path(root, path);

    /* Set the value of the node's directory value to the one inserted by the user. */
    value = read_input(SPACING);
    node->directory = change_directory_value(node->directory, value);

    free(path);
    free(value);
}



void handle_command_print(Node *root) {
    print_nodes_with_value(root);
}



void handle_command_find(Node *root) {
    Node *node;
    char *path = read_input(NO_SPACING);

    node = find_node(root, path);

    if(node != NULL) {
        if (node->directory.value[0] == '\0')
            puts(ERROR_NO_DATA);
        else
            puts(node->directory.value);
    }
} 



void handle_command_search(Node *root) {
    Node *node;
    char *value = read_input(SPACING);

    node = search_value(root, value);

    if (node == NULL)
        puts(ERROR_NOT_FOUND);
    else 
        puts(node->directory.name);
    
}