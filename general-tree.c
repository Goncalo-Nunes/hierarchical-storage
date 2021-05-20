#include "auxiliary.h"


Node *init_tree() {
    Directory directory;
    Node *node;

    directory = initialize_directory(directory, "/",  "\0", "\0");

    return node = new_node(directory);
}



Node *new_node(Directory directory) {
    Node *newNode = malloc(sizeof(Node));
    check_memory(newNode);

    newNode->nextSibling = NULL;
    newNode->firstChild = NULL;
    newNode->parent = NULL;
    newNode->previousSibling = NULL;
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
    newNode->previousSibling = tempNode;
    newNode->parent = tempNode->parent;

    return newNode;
}



Node *insert_child(Node *node, Directory directory) {
    Node *newNode;

    if (node->firstChild != NULL) {
        newNode = insert_sibling(node->firstChild, directory);
    } else {
        newNode = new_node(directory);
        node->firstChild = newNode;
        newNode->parent = node;
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
    char *word, res_path[BUF_SIZE];
    strcpy(res_path, "\0");

    word = strtok(path, "/");

    while (word != NULL) {
        strcat(res_path, "/");
        strcat(res_path, word);
        if ((tempNode = word_is_in_children(node, word)) != NULL)
            node = tempNode;
        
        else {
            directory = initialize_directory(directory, word, res_path, "\0");
            node = insert_child(node, directory);
        }

        word = strtok(NULL, "/");
    }
    
    return node;
}



void print_nodes_with_value(Node *node) {
    while (node != NULL) {        
        /* If the node has a value, print the node */
        if (node->directory.value[0] != '\0')
            printf("%s %s\n", node->directory.path, node->directory.value);

        if (node->firstChild != NULL)
            print_nodes_with_value(node->firstChild);

        node = node->nextSibling;
    }
}


void *find_node(Node *root, char *path) {
    Node *node = root;
    char *word, res_path[BUF_SIZE];

    strcpy(res_path, "\0");
    word = strtok(path, "/");

    while (word != NULL) {
        strcat(res_path, "/");
        strcat(res_path, word);

        node = word_is_in_children(node, word);

        if (node == NULL) {
            puts(ERROR_NOT_FOUND);
            return node;
        }

        word = strtok(NULL, "/");
    }
    
    return node;
}


int count_children(Node *node) {
    int count = 0;

    node = node->firstChild;
    
    while (node != NULL) {
        count++;
        node = node->nextSibling;
    }

    return count;
}


void *search_value(Node *node, char *value) {
    Node *ret = NULL;


    if (strcmp(node->directory.value, value) == 0) {
        return node;
    }

    if (node->firstChild != NULL) 
        ret = search_value(node->firstChild, value);
    
    if (ret != NULL) {
        return ret;
    }

    if (node->nextSibling != NULL)
        ret = search_value(node->nextSibling, value);

    return ret;
}




/*
void *search_value(Node *node, char *value) {
    while (node != NULL) {        
        printf("node value: %s\n", node->directory.value);
        printf("value: %s\n", value);
        if (strcmp(node->directory.value, value) == 0) {
            puts("FOUND!");
            break;
        }
        if (node->firstChild != NULL)
            search_value(node->firstChild, value);

        node = node->nextSibling;
    }


    return node;
}
*/


void free_node(Node *node) {
    free_directory(node->directory);
    free(node);
}


void delete_node(Node *node) {
    if (node->previousSibling == NULL) {
        
        node->parent->firstChild = node->nextSibling;

        if (node->nextSibling != NULL) {

            node->nextSibling->previousSibling = NULL;
            node->nextSibling->parent = node->parent;
        }
    }
    else if (node->nextSibling == NULL && node->previousSibling != NULL)
        node->previousSibling->nextSibling = NULL;

    else if(node->previousSibling != NULL)
        node->previousSibling->nextSibling = node->nextSibling;


    delete_branch(node);
}


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




/*------------------------- DEBUGGING ------------------------- */
void printTabs(int count)
{
    int i = 0;
    for (i = 0; i < count; i++)
    {
        putchar('\t');
    }
}


void printTreeRecursive(Node *node, int level)
{
    while (node != NULL)
    {
        printTabs(level);
        printf("Node: %s\n", node->directory.name);

        if (node->firstChild != NULL)
        {
            printTabs(level);
            printf("Children:\n");
            printTreeRecursive(node->firstChild, level + 1);
        }

        node = node->nextSibling;
    }
}