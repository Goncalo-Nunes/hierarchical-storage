/*
 * File:  general-tree.c
 * Author:  Gonçalo Nunes (99074)
 * Description: Functions to manipulate a n-ary tree.
*/


#include "auxiliary.h"


/* Initializes the n-ary tree. Returns a pointer to the tree's root. */
Node *init_tree() {
    Directory directory;
    Node *node;

    directory = initialize_directory(directory, "/",  "\0", "\0");

    return node = new_node(directory);
}


/* Creates a new node with the given directory. 
 * Returns a pointer to the newly created node.
*/
Node *new_node(Directory directory) {

    /* Allocates space for the node */
    Node *newNode = (Node *)safe_malloc(sizeof(Node));

    /* Initializes the node's components. */
    newNode->nextSibling = NULL;
    newNode->firstChild = NULL;
    newNode->parent = NULL;
    newNode->previousSibling = NULL;
    newNode->directory = directory;

    return newNode;
}


/* Creates a new node and sets it has being a sibling of the 
 * given node. This new node is added has being the youngest sibling, which
 * means it is added to the end of the sibling list. 
 * Returns a pointer to the newly created sibling node.
*/
Node *insert_sibling(Node *node, Directory directory) {
    Node *newNode = new_node(directory);
    Node *tempNode = node;

    /* Go to the end of the sibling list. */
    while (tempNode != NULL && tempNode->nextSibling != NULL)
        tempNode = tempNode->nextSibling;

    /* Set up the new node has being the youngest sibling */
    tempNode->nextSibling = newNode;
    newNode->previousSibling = tempNode;
    newNode->parent = tempNode->parent;

    return newNode;
}


/* Creates a new node and set's it has being a child of the given node. 
 * Returns a pointer to the newly created node.
*/
Node *insert_child(Node *node, Directory directory) {
    Node *newNode;

    if (node->firstChild != NULL) {
        /* if the given node already has children,
         we create a sibling to the given node's first child. */
        newNode = insert_sibling(node->firstChild, directory);
    } else {
        /* If the given node does not have children we create the first child. */
        newNode = new_node(directory);
        node->firstChild = newNode;
        newNode->parent = node;
    }

    return newNode;
}



/* Checks if the given name is in any of the nodes' directory names.
 * Returns the node which has the given name. If the node with that name
 * does not exist, returns NULL.
*/
void *name_is_in_children(Node *node, char *name) {
    Node *children = node->firstChild;

    /* Loops through the child nodes. */
    while (children != NULL) {
        /* Check if the name matches. */
        if (strcmp(children->directory.name, name) == 0) {
            return children;
        }

        children = children->nextSibling;
    }

    return NULL; /* The name was not found in the nodes*/
}


/* Creates a node with the given path and all other nodes that are needed to
 * reach that path. Returns a pointer to the newly created node.
*/
Node *create_node_with_path(Node *root, char *path) {
    Node *node = root;
    Node *tempNode;
    Directory directory;
    char *word, res_path[BUF_SIZE];
    strcpy(res_path, "\0");

    word = strtok(path, "/"); /* Get the word between the '/'s .*/

    while (word != NULL) {
        strcat(res_path, "/");
        strcat(res_path, word);

        /* If the word is in the child nodes we do not have to add a child. */
        if ((tempNode = name_is_in_children(node, word)) != NULL)
            node = tempNode; 
        
        else {
            /* Add a new child to the node. */
            directory = initialize_directory(directory, word, res_path, "\0");
            node = insert_child(node, directory);
        }

        word = strtok(NULL, "/");
    }
    
    return node;
}


/* Prints all the nodes with a value. The traversal is in Pre-Order. */
void print_nodes_with_value(Node *node) {
    while (node != NULL) {        
        /* If the node has a value, print the node */
        if (node->directory.value[0] != '\0')
            printf("%s %s\n", node->directory.path, node->directory.value);

        /* If the node does not have a value we print an error message. */
        if (node->firstChild != NULL)
            print_nodes_with_value(node->firstChild);

        node = node->nextSibling;
    }
}


/* Finds the node with the given path. Return a pointer to the found node.
 * If the node does not exist, returns NULL.
*/
void *find_node(Node *root, char *path) {
    Node *node = root;
    char *word;

    word = strtok(path, "/"); /* Get the word between the '/'s */

    while (word != NULL) {

        node = name_is_in_children(node, word); /* Check if the word is in the child nodes. */

        /* If not, we print an error */
        if (node == NULL) {
            puts(ERROR_NOT_FOUND);
            return node;
        }

        word = strtok(NULL, "/");
    }
    
    return node;
}


/* Counts the number of children a node has. Returns that count. */
int count_children(Node *node) {
    int count = 0;

    node = node->firstChild;
    
    /* Loop though the children. */
    while (node != NULL) {
        count++;
        node = node->nextSibling;
    }

    return count;
}


/* Searches the tree for the given value. The traversal is in Pre-Order.
 * Returns a pointer to the node in which the value was found.
 * If the node was not found, returns NULL.
*/
void *search_value(Node *node, char *value) {
    Node *temp = NULL;

    /* Loops through the node's siblings. */
    while (node != NULL) {        

        /* Check if the value is the same. */
        if (strcmp(node->directory.value, value) == 0)
            return node;

        
        if (node->firstChild != NULL)
            /* Recursive call to find the value in the children. */
            temp = search_value(node->firstChild, value);

        /* If the value was found we stop the recursion. */
        if (temp != NULL)  
            return temp;

        node = node->nextSibling;
    }

    return NULL;
}


/* Frees all the memory allocated referent to the given node. */
void free_node(Node *node) {
    if (node != NULL) {
        free_directory(node->directory);
        free(node);
    } 
}


/* Deletes the given node and it's branches. */
void delete_node(Node *node) {

    if (node == NULL)
        return;

    /* Node is the only child */
    if (node->previousSibling == NULL && node->nextSibling == NULL) {
        node->parent->firstChild = NULL;

    /* Node is the first child */
    } else if (node->previousSibling == NULL) {
        node->parent->firstChild = node->nextSibling;
        node->nextSibling->previousSibling = NULL;

    /* Node is the last child */
    } else if (node->nextSibling == NULL) {
        node->previousSibling->nextSibling = NULL;

    /* Node is middle child */
    } else {
        node->previousSibling->nextSibling = node->nextSibling;
        node->nextSibling->previousSibling = node->previousSibling;
    }

    delete_branch(node);
}


/* Delete the node's children */
void delete_children(Node *node) {
    Node *child = NULL;
    Node *temp;

    if (node != NULL) 
        child = node->firstChild;

    while (child != NULL) {
        temp = child->nextSibling;
        delete_branch(child);
        child = temp;
    }
}


/* Deletes the node and all it's branches. */
Node *delete_branch(Node *node) {
    Node *newChild = NULL;
    if (node != NULL) {
        while(node->firstChild != NULL)
            node->firstChild = delete_branch(node->firstChild);

        newChild = node->nextSibling;
        free_node(node);
    }
    return newChild;
}
