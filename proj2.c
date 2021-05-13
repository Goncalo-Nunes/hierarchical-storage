#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "auxiliary.h"



int main() {

    char *command = read_input(NO_SPACING);
    Node *root = init_tree();
    
    while (strcmp(command, COMMAND_QUIT)) {
 
        if (strcmp(command, COMMAND_HELP) == 0)
            handle_command_help();

        else if (strcmp(command, COMMAND_SET) == 0)
            handle_command_set(root);

        else if (strcmp(command, COMMAND_PRINT) == 0)
            break;

        else if (strcmp(command, COMMAND_FIND) == 0)
            break;

        else if (strcmp(command, COMMAND_LIST) == 0)
            break;

        else if (strcmp(command, COMMAND_SEARCH) == 0)
            break;
        
        else if (strcmp(command, COMMAND_DELETE) == 0)
            break;

        free(command);
        command = read_input(NO_SPACING);
    }

    free(command);

    return 0;
}