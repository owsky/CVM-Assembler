#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "read.h"

int checkComment(char *s) {
    int i = 0;
    while(s[i] != '\0') {
        if(s[i] >= 48 && s[i] <= 57) {
            return 0;
        }
        i++;
    }
    return 1;
}

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

int getSize(FILE *input) {
    char *num, *linea, delim[] = " ;";
    int res;
    size_t dime = 0;
    while(getline(&linea, &dime, input)) {
        if(!checkComment(linea)) {
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

int *load(char *str, int *len) {
    int c, i = 0, *arr;
    char *num, *line, delim[] = " ;";
    size_t dim = 0;
    FILE *stream = fopen(str, "r");
    if(stream == NULL) {
        printf("File not found\n");
        return NULL;
    }
    *len = getSize(stream);
    arr = (int*)malloc(sizeof(int) * *len);
    if(!arr) {
        exit(1);
    }

    while(getline(&line, &dim, stream)) {
        if(i >= *len) {
            break;
        }
        if(!checkComment(line)) {
            num = strtok(line, delim);
            c = atoi(num);
            num = strtok(NULL, delim);
            arr[i] = c;
            i++;
        }
    }
    free(line);
    return arr;
}
