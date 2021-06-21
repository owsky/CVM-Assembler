#include "interfaces.h"
#include "read.h"
#include "print.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*Finds correspondent node in the table*/
table match(table t, int b){
    while(t){
        if(b == t-> cod){
            return t;
        }
        t= t->next;
    }
    return NULL;
}

/*Adds padding for pretty printing*/
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

/*Prints instructions from the input file*/
void print(char *str, table t) {
    int i = 0,  len = 0, *arr = load(str, &len);
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
