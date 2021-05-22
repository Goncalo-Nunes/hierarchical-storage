#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "auxiliary.h"



int main() {

    char command[COMMAND_BUF_SIZE];
    Node *root = init_tree();
    
    scanf(ARGS_FORMAT_NO_SPACING, command);

    while (strcmp(command, COMMAND_QUIT)) {
 
        if (strcmp(command, COMMAND_HELP) == 0)
            handle_command_help();

        else if (strcmp(command, COMMAND_SET) == 0)
            handle_command_set(root);

        else if (strcmp(command, COMMAND_PRINT) == 0)
           handle_command_print(root);

        else if (strcmp(command, COMMAND_FIND) == 0)
            handle_command_find(root);

        else if (strcmp(command, COMMAND_LIST) == 0)
           handle_command_list(root);

        else if (strcmp(command, COMMAND_SEARCH) == 0)
            handle_command_search(root);
        
        else if (strcmp(command, COMMAND_DELETE) == 0)
            handle_command_delete(root);

        peek_nonspace();
        scanf(ARGS_FORMAT_NO_SPACING, command);
    }

    delete_branch(root);
    return 0;
}