#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include "interfaces.h"
#include "execute.h"
#include "print.h"

int main(int argc, char **argv) {
    int i;
    char command[10];

    table t = NULL;
    loadTable(&t);
    assert(t);

    switch(argc) {
        case 1:
            printf("Input a command\n");
            break;
        case 2:
            printf("Select a file\n");
            break;
        case 3:
            strcpy(command, argv[1]);

            for(i = 0; command[i]; i++){
                command[i] = tolower(command[i]);
            }

            if(!strcmp(command, "execute")) {
                execute(argv[2]);
            } else if(!strcmp(command, "print")) {
                print(argv[2], t);
            } else {
                printf("Unsupported command\n");
            }
            break;
        default:
            printf("Error: too many parameters\n");
            break;
    }
    destroy(t);
    return 0;
}
