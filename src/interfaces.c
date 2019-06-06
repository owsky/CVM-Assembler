#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "interfaces.h"

void destroy(table *t) {
    int i;
    for(i=0; i<16; i++) {
        free(t[i]);
    }
}

void addFunction(table *t, int cod, int par, int *reg, char *name) {
    if(t == NULL) {
        *t = (table)malloc(sizeof(struct tab));
        assert(t);
        (*t)->cod = cod;
        (*t)->par = par;
        if(par > 0 && reg != NULL) {
            if(par == 1) {
                (*t)->reg[0] = reg[0];
            } else if(par == 2) {
                (*t)->reg[0] = reg[0];
                (*t)->reg[1] = reg[1];
            }
        }
        strcpy((*t)->name, name);
    } else {
        addFunction(t+1, cod, par, reg, name);
    }
}

void loadTable(table *t) {
    int reg[2];
    addFunction(t, 0, 0, NULL, "HALT");

    reg[0] = 1;
    addFunction(t, 1, 1, reg, "DISPLAY");

    reg[0] = 0;
    addFunction(t, 2, 1, reg, "PRINT_STACK");

    reg[0] = 1;
    addFunction(t, 10, 1, reg, "PUSH");

    reg[0] = 1;
    addFunction(t, 11, 1, reg, "POP");

    reg[0] = 1;
    addFunction(t, 12, 2, reg, "MOV");

    reg[0] = 0;
    addFunction(t, 20, 1, reg, "CALL");

    reg[0]= 0;
    addFunction(t, 21, 1, reg, "RET");

    reg[0] = 0;
    addFunction(t, 22, 1, reg, "JMP");

    reg[0] = 0;
    addFunction(t, 23, 1, reg, "JZ");

    reg[0] = 0;
    addFunction(t, 24, 1, reg, "JPOS");

    reg[0] = 0;
    addFunction(t, 25, 1, reg, "JNEG");

    reg[0] = 1;
    reg[1] = 1;
    addFunction(t, 30, 2, reg, "ADD");

    reg[0] = 1;
    reg[1] = 1;
    addFunction(t, 31, 2, reg, "SUB");

    reg[0] = 1;
    reg[1] = 1;
    addFunction(t, 32, 2, reg, "MUL");

    reg[0] = 1;
    reg[1] = 1;
    addFunction(t, 33, 2, reg, "DIV");
}

table match(table *t, int num) {
    int i;
    for(i=0; i<16; i++) {
        if(num == t[i]->cod) {
            return t[i];
        }
    }
    return NULL;
}

void overflow() {
    printf("Overflow\n");
    exit(1);
}

void stackUnderflow() {
    printf("Stack underflow\n");
    exit(1);
}

void stackOverflow() {
    printf("Stack overflow\n");
    exit(1);
}
