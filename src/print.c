#include "interfaces.h"
#include "read.h"
#include "print.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

table match(table t, int b){
    while(t){
        if(b == t-> cod){
            return t;
        }
        t= t->next;
    }
    return NULL;
}

void stampa(char *str, table t) {
    int i = 0,  len = 0, *arr = load(&(*str), &len);
    table c;

    if(arr != NULL){
        while(i< len){
            if((c = match(t, arr[i])) != NULL){

                printf("[%d] %s ", i , c-> name);
                i++;
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
                }

                else {
                    printf("\n");
                }
            }
            i++;
        }
    }
    free(arr);
}
