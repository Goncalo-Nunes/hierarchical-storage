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
    char buf[BUF_SIZE]; 

    scanf(ARGS_FORMAT_NO_SPACING, buf);

    node = create_node_with_path(root, buf);

    /* Set the value of the node's directory value to the one inserted by the user. */
    scanf(ARGS_FORMAT_SPACING, buf);
    node->directory = change_directory_value(node->directory, buf);

}



void handle_command_print(Node *root) {
    print_nodes_with_value(root);
}



void handle_command_find(Node *root) {
    Node *node;
    char path[BUF_SIZE];

    scanf(ARGS_FORMAT_NO_SPACING, path);

    node = find_node(root, path);

    if(node != NULL) {
        if (node->directory.value[0] == '\0')
            puts(ERROR_NO_DATA);
        else
            puts(node->directory.value);
    }
} 




void handle_command_list(Node *root) {
    char path[BUF_SIZE], **nameArray;
    Node *node;
    int i = 0, childrenCount;

    if (peek_nonspace() == '\n')
        node = root;
    else {
        scanf(ARGS_FORMAT_NO_SPACING, path);
        node = find_node(root, path);
        if (node == NULL)
            return;
    }
    
    childrenCount = count_children(node);
    nameArray = (char **)malloc(childrenCount * sizeof(char*));
    node = node->firstChild;
    if (node == NULL) {
        free(nameArray);
        return;
    }

    while(node != NULL) {
        nameArray[i] = (char *)malloc((strlen(node->directory.name) + 1) * sizeof(char));
        strcpy(nameArray[i], node->directory.name);
        node = node->nextSibling;
        i++;
    }

    quick_sort(nameArray, 0, childrenCount-1);

    for (i = 0; i < childrenCount; i++) {
        puts(nameArray[i]);
        free(nameArray[i]);
    }

   free(nameArray); 
}



void handle_command_search(Node *root) {
    Node *node;
    char value[BUF_SIZE];

    scanf(ARGS_FORMAT_SPACING, value);

    node = search_value(root, value);

    if (node == NULL)
        puts(ERROR_NOT_FOUND);
    else 
        puts(node->directory.path);

}


void handle_command_delete(Node *root) {
    Node *node;
    char path[BUF_SIZE];

    if (peek_nonspace() == '\n') {
        delete_children(root);
        return;
    }    
    
    scanf(ARGS_FORMAT_NO_SPACING, path);
    node = find_node(root, path);
    if (node == NULL)
        return;
   
    
    delete_node(node);
    /*  printTreeRecursive(root, 0); */
}