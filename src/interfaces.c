#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "interfaces.h"

void destroy(table *t) {
    int i;
    for(i=0; i<16; i++) {
        free(t[i]);
    }
}

void addFunction(table *t, int cod, int par) {
    if(t == NULL) {
        *t = (table)malloc(sizeof(struct tab));
        (*t)->cod = cod;
        (*t)->par = par;
    }
}

void loadTable(table *t) {


    int i;
    for(i=0; i<16; i++) {
        t[i] = (table)malloc(sizeof(struct tab));
    }

    t[0]->cod = 0;
    t[0]->par = 0;
    strcpy(t[0]->name, "HALT");

    t[1]->cod = 1;
    t[1]->par = 1;
    t[1]->reg[0] = 1;
    strcpy(t[1]->name, "DISPLAY");

    t[2]->cod = 2;
    t[2]->par = 1;
    t[2]->reg[0] = 0;
    strcpy(t[2]->name, "PRINT_STACK");

    t[3]->cod = 10;
    t[3]->par = 1;
    t[3]->reg[0] = 1;
    strcpy(t[3]->name, "PUSH");

    t[4]->cod = 11;
    t[4]->par = 1;
    t[4]->reg[0] = 1;
    strcpy(t[4]->name, "POP");

    t[5]->cod = 12;
    t[5]->par = 2;
    t[5]->reg[0] = 1;
    strcpy(t[5]->name, "MOV");

    t[6]->cod = 20;
    t[6]->par = 1;
    strcpy(t[6]->name, "CALL");

    t[7]->cod = 21;
    t[7]->par = 0;
    strcpy(t[7]->name, "RET");

    t[8]->cod = 22;
    t[8]->par = 1;
    strcpy(t[8]->name, "JMP");

    t[9]->cod = 23;
    t[9]->par = 1;
    strcpy(t[9]->name, "JZ");

    t[10]->cod = 24;
    t[10]->par = 1;
    strcpy(t[10]->name, "JPOS");

    t[11]->cod = 25;
    t[11]->par = 1;
    strcpy(t[11]->name, "JNEG");

    t[12]->cod = 30;
    t[12]->par = 2;
    t[12]->reg[0] = 1;
    t[12]->reg[1] = 1;
    strcpy(t[12]->name, "ADD");

    t[13]->cod = 31;
    t[13]->par = 2;
    t[13]->reg[0] = 1;
    t[13]->reg[1] = 1;
    strcpy(t[13]->name, "SUB");

    t[14]->cod = 32;
    t[14]->par = 2;
    t[14]->reg[0] = 1;
    t[14]->reg[1] = 1;
    strcpy(t[14]->name, "MUL");

    t[15]->cod = 33;
    t[15]->par = 2;
    t[15]->reg[0] = 1;
    t[15]->reg[1] = 1;
    strcpy(t[9]->name, "DIV");
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
