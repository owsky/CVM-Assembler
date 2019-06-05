#include "interfaces.h"
#include "read.h"

void stampa(char *str, table *t) {
    int len = 0;
    int *arr = load(&(*str), &len);
    int i = 0;
    table inst;

    if(arr != NULL) {
        for(i=0; i<len; i++) {
            if((inst = match(t, arr[i])) != NULL) {
                printf("[");
                padding(len , i);
                printf("%d]\t %s ", i, inst->name);
                if(inst->par > 0) {
                    if(inst->par == 1) {
                        i++;
                        if(inst->reg[0] == 1) {
                            printf("R%d\n", arr[i]);
                        } else {
                            printf("%d\n", arr[i]);
                        }
                    } else {
                        i++;
                        if(inst->reg[0] == 1) {
                            printf("R%d ", arr[i]);
                        } else {
                            printf("%d ", arr[i]);
                        }
                        if(inst->reg[1] == 1) {
                            printf("R%d\n", arr[i+1]);
                        } else {
                            printf("%d\n", arr[i+1]);
                        }
                        i++;
                    }
                } else {
                    printf("\n");
                }
            }
        }
    }
    free(arr);
}
