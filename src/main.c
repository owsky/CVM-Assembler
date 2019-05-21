#include "operations.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *input;
    size_t dim = 0;
    char *token, command[100], argument[100];

    table t[16];
    loadTable(t);

    do {
        printf("Inserisci un comando\n");
        getline(&input, &dim, stdin);
        token = strtok(input, " \n");
        strcpy(command, token);
        while(token != NULL) {
            strcpy(argument, token);
            token = strtok(NULL, " \n");
        }
        if(strcmp(command, argument)) {
            if(command != NULL) {
                if(argument != NULL) {
                    if(!strcmp(command, "stampa")) {
                        stampa(argument, t);
                    } else if(!strcmp(command, "esegui")) {
                        esegui(argument);
                    } else {
                        printf("Comando non trovato\n");
                    }
                }
            }
        }
    }while(strcmp(command, "esci"));
    free(input);
    destroy(t);
    return 0;
}
