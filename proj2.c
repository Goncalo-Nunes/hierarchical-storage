#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "auxiliary.h"


int main() {

    char *command;


    while ((command = read_input()) != 0) {

        if (strcmp(command, "help") == 0)
            printf("%s", "HELP!");

        else if (strcmp(command, "quit") == 0)
            break;

        

        free(command);
    }

    free(command);

    return 0;
}