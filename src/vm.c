#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include "interfaces.h"
#include "print.h"
#include "execute.h"

int main(int argc, char **argv) {
    /*
    char *input;
    size_t dim = 0;
    char *token, command[100], parameter[100];
    */


    int i;
    table *t = NULL;
    loadTable(t);
    assert(t);

    switch(argc) {
        case 1:
            printf("Nessun file selezionato\n");
            break;
        case 2:
            for(i = 0; *argv[i]; i++){
                *argv[i] = tolower(*argv[i]);
            }
            if(!strcmp(argv[1], "esegui")) {
                esegui(argv[1]);
            } else if(!strcmp(argv[1], "stampa")) {
                stampa(argv[1], t);
            }
            break;
        default:
            printf("Errore\n");
            break;
    }

/*
    do {
        printf("Inserisci un comando\n");
        getline(&input, &dim, stdin);
        token = strtok(input, " \n\r");
        strcpy(command, token);
        for(i = 0; command[i]; i++){
            command[i] = tolower(command[i]);
        }
        while(token != NULL) {
            strcpy(parameter, token);
            token = strtok(NULL, " \n");
        }
        for(i = 0; parameter[i]; i++){
            parameter[i] = tolower(parameter[i]);
        }
        if(strcmp(command, parameter)) {
            if(command != NULL) {
                if(parameter != NULL) {
                    if(!strcmp(command, "stampa")) {
                        stampa(parameter, t);
                    } else if(!strcmp(command, "esegui")) {
                        esegui(parameter);
                    } else {
                        printf("Comando non trovato\n");
                    }
                }
            }
        }
    }while(strcmp(command, "esci"));
    free(input);
    */
    destroy(t);
    return 0;
}
