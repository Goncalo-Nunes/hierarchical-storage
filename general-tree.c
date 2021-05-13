#include "auxiliary.h"


Node *init_tree() {
    Directory directory;
    Node *node;

    directory.name = malloc(sizeof(char) * 2);
    strcpy(directory.name, "/");

    return node = new_node(directory);
}



Node *new_node(Directory directory) {
    Node *newNode = malloc(sizeof(Node));
    check_memory(newNode);

    newNode->nextSibling = NULL;
    newNode->firstChild = NULL;
    newNode->directory = directory;

    return newNode;
}



Node *insert_sibling(Node *node, Directory directory) {
    Node *newNode = new_node(directory);
    Node *tempNode = node;

    newNode->directory = directory;
    newNode->nextSibling = NULL;

    while (tempNode != NULL && tempNode->nextSibling != NULL)
        tempNode = tempNode->nextSibling;

    tempNode->nextSibling = newNode;

    return newNode;
}



Node *insert_child(Node *node, Directory directory) {
    Node *newNode;

    if (node->firstChild) {
        newNode = insert_sibling(node, directory);
    } else {
        newNode = new_node(directory);
        node->firstChild = newNode;
    }

    return newNode;
}


void print_tree(Node *tree)
{
	if((tree->firstChild) != NULL){
		fprintf(stderr, "%s->", tree->directory.name);
		print_tree(tree->firstChild);
	}
	if((tree->nextSibling) != NULL){
		fprintf(stderr, "%s", tree->directory.name);
		fprintf(stderr, "\n%s--", tree->directory.name);
		print_tree(tree->nextSibling);
	}
	if(!(tree->firstChild) && !(tree->nextSibling)){
		fprintf(stderr, "%s", tree->directory.name);
	}
}


void *word_is_in_children(Node *node, char *word) {
    Node *children = node->firstChild;

    while (children != NULL) {
        if (strcmp(children->directory.name, word) == 0) {
            return children;
        }

        children = children->nextSibling;
    }

    return NULL; /* The word was not found in the nodes*/
}


void *create_node_with_path(Node *root, char *path) {
    Node *node = root;
    Node *tempNode;
    Directory directory;
    char *word;
    word = strtok(path, "/");

    while (word != NULL) {

        if ((tempNode = word_is_in_children(node, word)) != NULL)
            node = tempNode;
        
        else {
            directory.name = malloc((strlen(word) + 1) * sizeof(char));
            strcpy(directory.name, word);
            node = insert_child(node, directory);

        }

        word = strtok(NULL, "/");
    }
    
    return node;
}