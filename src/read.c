#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "read.h"
#include "print.h"

/*Checks if the given string contains a valid instruction or parameter*/
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

/*Looks for the first valid number indicating the file size*/
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

/*Opens the file and loads the content into an array*/
int *load(char *str, int *len) {
    int c, i = 0, *arr;
    char *num, *line, delim[] = " ;";
    size_t dim = 0;
    FILE *stream = fopen(str, "r");
    if(!stream) {
        printf("File not found\n");
        exit(1);
    }

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
