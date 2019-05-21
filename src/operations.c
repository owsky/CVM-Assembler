#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
        printf("File non trovato\n");
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

void esegui(char *str) {
    int len = 0;
    int *arr = load(&(*str), &len), regs[32] = {0};
    unsigned int ip = 0;
    stack s = (stack)malloc(sizeof(struct node));
    if(s == NULL) {
        exit(1);
    }

    s->arr[0] = 0;
    s->sp = 0;

    if(arr == NULL) {
        return;
    }
    do {
        switch(arr[ip]) {
            case 0:
                return;
            case 1:
                display(arr[ip+1], regs, &ip);
                break;
            case 2:
                print_stack(arr[ip+1], s, &ip);
                break;
            case 10:
                push(arr[ip+1], s, regs, &ip);
                break;
            case 11:
                pop(arr[ip+1], s, regs, &ip);
                break;
            case 12:
                mov(arr[ip+1], arr[ip+2], regs, &ip);
                break;
            case 20:
                call(arr[ip+1], s, &ip);
                break;
            case 21:
                ret(s, &ip);
                break;
            case 22:
                jmp(arr[ip+1], &ip);
                break;
            case 23:
                jz(arr[ip+1], s, &ip);
                break;
            case 24:
                jpos(arr[ip+1], s, &ip);
                break;
            case 25:
                jneg(arr[ip+1], s, &ip);
                break;
            case 30:
                add(arr[ip+1], arr[ip+2], regs, s, &ip);
                break;
            case 31:
                sub(arr[ip+1], arr[ip+2], regs, s, &ip);
                break;
            case 32:
                mul(arr[ip+1], arr[ip+2], regs, s, &ip);
                break;
            case 33:
                divi(arr[ip+1], arr[ip+2], regs, s, &ip);
                break;
            default:
                break;
        }
    }while((int)ip < len);
}
