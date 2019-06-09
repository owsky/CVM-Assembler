/*P1G114*/
/*Nicolò Bertocco 873896 - Beatrice Messano 876673*/
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
    /*Creazione della tabella delle funzioni*/
    table t = NULL;
    loadTable(&t);
    assert(t);

    /*Gestione input CLI*/
    switch(argc) {
        case 1:
            printf("Nessun comando inserito\n");
            break;
        case 2:
            printf("Nessun file selezionato\n");
            break;
        case 3:
            /*Gestione case dei comandi*/
            strcpy(command, argv[1]);
            for(i = 0; command[i]; i++){
                command[i] = tolower(command[i]);
            }
            if(!strcmp(command, "esegui")) {
                esegui(argv[2]);
            } else if(!strcmp(command, "stampa")) {
                stampa(argv[2], t);
            } else {
                printf("Comando non supportato\n");
            }
            break;
        default:
            printf("Errore\n");
            break;
    }

    destroy(t);
    return 0;
}
