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

    printTreeRecursive(root);


    free(path);
    free(value);
}