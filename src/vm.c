#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include "interfaces.h"
#include "execute.h"

int main(int argc, char **argv) {
    /*int i;*/
    table t = NULL;
    loadTable(&t);
    assert(t);

    switch(argc) {
        case 1:
            printf("Nessun comando inserito\n");
            break;
        case 2:
            printf("Nessun file selezionato\n");
            break;
        case 3:
        /*
            for(i = 0; *argv[i]; i++){
                *argv[i] = tolower(*argv[i]);
            }
            */
            if(!strcmp(argv[1], "esegui")) {
                esegui(argv[2]);
            }
            break;
        default:
            printf("Errore\n");
            break;
    }

    destroy(t);
    return 0;
}
