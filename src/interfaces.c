#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "interfaces.h"
#include "execute.h"

void addFunction(table *t, int cod, char *p1, char *p2, char *name) {
    if(!*t) {
        *t = (table)malloc(sizeof(struct tab));
        assert(t);
        (*t)->cod = cod;
        (*t)->par = 0;

        if(p1) {
            strcpy((*t)->p1, p1);
            (*t)->par++;
            if(p2) {
                strcpy((*t)->p2, p2);
                (*t)->par++;
            }
        }

        strcpy((*t)->name, name);
        (*t)->next = NULL;
    } else {
        addFunction(&(*t)->next, cod, p1, p2, name);
    }
}

void loadTable(table *t) {
    addFunction(t, 0, NULL, NULL, "HALT");
    addFunction(t, 1, "reg", NULL, "DISPLAY");
    addFunction(t, 2, "int", NULL, "PRINT_STACK");
    addFunction(t, 10, "reg", NULL, "PUSH");
    addFunction(t, 11, "reg", NULL, "POP");
    addFunction(t, 12, "reg", "int", "MOV");
    addFunction(t, 20, "int", NULL, "CALL");
    addFunction(t, 21, NULL, NULL, "RET");
    addFunction(t, 22, "int", NULL, "JMP");
    addFunction(t, 23, "int", NULL, "JZ");
    addFunction(t, 24, "int", NULL, "JPOS");
    addFunction(t, 25, "int", NULL, "JNEG");
    addFunction(t, 30, "reg", "reg", "ADD");
    addFunction(t, 31, "reg", "reg", "SUB");
    addFunction(t, 32, "reg", "reg", "MUL");
    addFunction(t, 33, "reg", "reg", "DIV");
}

void destroy(table t) {
    if(t->next) {
        destroy(t->next);
    }
    free(t);
}

void overflow() {
    printf("Error: arithmetic overflow");
    halt();
    exit(1);
}

void underflow() {
    printf("Error: arithmetic underflow");
    halt();
    exit(1);
}

void stackOverflow() {
    printf("Error: stack overflow");
    halt();
    exit(1);
}

void stackUnderflow() {
    printf("Error: arithmetic overflow");
        halt();
        exit(1);
}