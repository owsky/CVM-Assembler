/*P1G114*/
/*Nicolò Bertocco 873896 - Beatrice Messano 876673*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "read.h"
#include "print.h"

/*Controlla se la stringa fornita contiene un intero*/
int checkNumber(char *s) {
    int i = 0;
    while(s[i] != '\0') {
        if(s[i] == ';') {
            return 0;
        } else if(s[i] >= 48 && s[i] <= 57) {
            return 1;
        }
        i++;
    }
    return 0;
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
/*Ritorna il numero di righe del file, escluse quelle prive di istruzioni
o commenti*/
int getSize(FILE *input) {
    char *num, *linea, delim[] = " ;";
    int res;
    size_t dime = 0;
    while(getline(&linea, &dime, input)) {
        if(checkNumber(linea)) {
            num = strtok(linea, delim);
            res = atoi(num);
            free(linea);
            return res;
        }
    }
    if(linea) {
        free(linea);
    }
    return -1;
}

/*Data una stringa contenente il nome del file effettua l'apertura carica le
istruzioni in un array e ne ritorna il puntatore*/
int *load(char *str, int *len) {
    int c, i = 0, *arr;
    char *num, *line, delim[] = " ;";
    size_t dim = 0;

    /*Apertura file*/
    FILE *stream = fopen(str, "r");
    if(!stream) {
        printf("File non trovato\n");
        exit(1);
    }

    /*Istanziazione dinamica dell'array*/
    *len = getSize(stream);
    arr = (int*)malloc(sizeof(int) * (*len));
    assert(arr);

    while(i < *len && getline(&line, &dim, stream)) {
        if(checkNumber(line)) {
            num = strtok(line, delim);
            c = atoi(num);
            arr[i] = c;
            i++;
        }
    }
    free(line);
    return arr;
}
