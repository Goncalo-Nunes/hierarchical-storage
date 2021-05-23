/*
 * File:  proj2.c
 * Author:  Gonçalo Nunes (99074)
 * Description: Contains the functions that handle the commands inserted by the user.
*/


#include "auxiliary.h"


/* Handles the help command. Prints all commands available and their description. */
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


/* Handles the set command. Creates a new directory if the one inserted 
 * by the user does not exist yet. Otherwise, changes the directory value to 
 * the one chosen by the user. 
*/
void handle_command_set(Node *root) {
    Node *node;
    char buf[BUF_SIZE]; 

    scanf(ARGS_FORMAT_NO_SPACING, buf);

    node = create_node_with_path(root, buf);

    /* Set the value of the node's directory value to the one inserted by the user. */
    scanf(ARGS_FORMAT_SPACING, buf);
    node->directory = change_directory_value(node->directory, buf);

}


/* Handles the print command. Prints all nodes with a value 
* The traversal is in Pre-Order
*/
void handle_command_print(Node *root) {
    print_nodes_with_value(root);
}


/* Handles the find command.
 * Prints the value of the directory inserted by the user.
*/
void handle_command_find(Node *root) {
    Node *node;
    char path[BUF_SIZE];

    scanf(ARGS_FORMAT_NO_SPACING, path);

    node = find_node(root, path); /* Finds the node with the given path. */

    if(node != NULL) {
        /* Check if node has a value. */
        if (node->directory.value[0] == '\0') 
            puts(ERROR_NO_DATA);
        else
            puts(node->directory.value);
    }
} 


/* Handles the list command. Gets all the direct components of a given path
 * and prints them in alphabetical order.
*/
void handle_command_list(Node *root) {
    char path[BUF_SIZE], **nameArray;
    Node *node;
    int i = 0, childrenCount;

    /* Check if the command has arguments or not. */
    if (peek_nonspace() == '\n')
        node = root;
    else {
        scanf(ARGS_FORMAT_NO_SPACING, path);
        node = find_node(root, path);
        if (node == NULL)
            return;
    }
    
    /* Count the node's children. */
    childrenCount = count_children(node); 
    /* Allocate space for the names of the children directories. */
    nameArray = (char **)safe_malloc(childrenCount * sizeof(char*)); 
    node = node->firstChild;

    while(node != NULL) {
        /* Allocate space for the child name. */
        nameArray[i] = (char *)safe_malloc((strlen(node->directory.name) + 1) * sizeof(char));
        /* Copy the directory name to the newly allocated memory. */
        strcpy(nameArray[i], node->directory.name);
        node = node->nextSibling;
        i++;
    }

    /* Use the quicksort algorithm to sort the array of names. */
    quick_sort(nameArray, 0, childrenCount-1);

    /* Loops through the sorted array to print and free the names. */
    for (i = 0; i < childrenCount; i++) {
        puts(nameArray[i]);
        free(nameArray[i]);
    }

   free(nameArray); /* Free the array */
}


/* Handles the search command. Finds the directory with the given value 
 * and prints the directory path.
*/
void handle_command_search(Node *root) {
    Node *node;
    char value[BUF_SIZE];

    scanf(ARGS_FORMAT_SPACING, value);

    node = search_value(root, value);

    /* Check if the directory was found or not. */
    if (node == NULL)
        puts(ERROR_NOT_FOUND);
    else {
        puts(node->directory.path);
    }
}


/* Handles the delete command. Deletes the directory with the given path
 * as well as it's sub-directories. If no arguments are provided, 
 * all directories are deleted.
*/
void handle_command_delete(Node *root) {
    Node *node;
    char path[BUF_SIZE];

    /* If thera are no arguments, delete all directories */
    if (peek_nonspace() == '\n') {
        delete_children(root); /* Delete the root's children. */ 
        /* As a consequence, the root now has no children. */
        root->firstChild = NULL; 
        return;
    }    
    
    scanf(ARGS_FORMAT_NO_SPACING, path);
    node = find_node(root, path);
    if (node == NULL)
        return;

    /* If the given path was found, we delete it's node. */
    delete_node(node); 
}