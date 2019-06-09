/*P1G114*/
/*Nicolò Bertocco 873896 - Beatrice Messano 876673*/
/*Codice scritto da Beatrice Messano 876673*/
#include "interfaces.h"
#include "read.h"
#include "print.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* la funzione mi ritorna una tabella data dell'unione della tabella delle funzioni
e un valore intero corrispondente*/
table match(table t, int b){
    while(t){
        if(b == t-> cod){
            return t;
        }
        t= t->next;
    }
    return NULL;
}

/*Gestione padding degli indici per la stampa*/
void padding(int size, int pos) {
    do {
        size /= 10;
        pos /= 10;
    }while(size > 0 && pos > 0);
    while(size > 0) {
        size /= 10;
        printf(" ");
    }
}

/*Data una stringa contenente il nome del file e una tabella , la funzione mi stampa la posizione , il nome
dell'istruzione che sta effettuando e gli eventuali parametri*/
void stampa(char *str, table t) {
    int i = 0,  len = 0, *arr = load(&(*str), &len);
    table c;

    if(arr != NULL){
        while(i< len){
            if((c = match(t, arr[i])) != NULL){

                printf("[");
                padding(len, i);
                printf("%d] %s ", i , c-> name);
                if(c->par >0  ){
                    i++;
                    if(!strcmp(c-> p1, "reg")){
                        printf("R%d", arr[i]);
                    }
                    else {
                        printf("%d", arr[i]);
                    }
                    if(c-> par == 2) {
                        i++;
                        if(!strcmp(c-> p2, "reg")){
                            printf(" R%d", arr[i]);
                        }
                        else {
                            printf(" %d", arr[i]);
                        }
                    }
                    printf("\n" );
                } else {
                    printf("\n");
                }
            }
            i++;
        }
    }
    free(arr);
}
