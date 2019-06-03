#include "functions.h"
#include <stdlib.h>
#include <stdio.h>

/*Stampa su console il valore del registro indicato*/
void display(int reg, int *regs, unsigned int *ip) {
    printf("%d\n", regs[reg]);
    *ip+=2;
}

/*stampa su console il numero indicato di posizioni dello stack.
Stampare le posizioni in ordine inverso a partire dalla posizione SP-1
fino a SP-N inclusa.
Stampare l’indice della posizione ed il valore in essa contenuto*/
void print_stack(int num, stack s, unsigned int *ip) {
    while(num != 0) {
        printf("%d: %d\n", num, s->arr[num]);
        num--;
    }
    *ip+=2;
}

/*Inserisce il contenuto del registro indicato nello stack (in posizione SP)
ed incrementa SP*/
void push(int reg, stack s, int *regs, unsigned int *ip) {
    /*segfault indice stack*/
    s->arr[s->sp] = regs[reg];
    s->sp++;
    *ip+=2;
}

/*Decrementa SP e copia il valore in posizione SP (dopo il decremento)
nel registro indicato*/
void pop(int reg, stack s, int *regs, unsigned int *ip) {
    s->sp--;
    regs[reg] = s->arr[s->sp];
    *ip+=2;
}

/*Copia il valore P2 nel registro indicato*/
void mov(int reg, int num, int *regs, unsigned int *ip) {
    regs[reg] = num;
    *ip+=3;
}

/*Chiamata a subroutine. PUSH IP (posizione successiva a CALL)
e JMP alla posizione indicata*/
void call(int pos, stack s, unsigned int *ip) {
    int bak = *ip;
    s->arr[s->sp] = bak+2;
    s->sp++;
    *ip = pos;
}

/*Ritorno da chiamata a subroutine, POP in IP*/
void ret(stack s, unsigned int *ip) {
    s->sp--;
    *ip = s->arr[s->sp];
}

/*Sostituisce il valore di IP con il valore indicato*/
void jmp(int pos, unsigned int *ip) {
    *ip = pos;
}

/*Sostituisce il valore di IP con il valore indicato se l’ultimo elemento
inserito nello stack `e diverso da zero e lo rimuove, decrementando SP*/
void jz(int pos, stack s, unsigned int *ip) {
    int num = s->arr[s->sp-1];
    if(num != 0) {
        *ip = pos;
    } else {
        *ip+=2;
    }
    s->sp--;
}

/*Sostituisce il valore di IP con il valore indicato se l’ultimo elemento
inserito nello stack `e maggiore di zero e lo rimuove, decrementando SP*/
void jpos(int pos, stack s, unsigned int *ip) {
    int num = s->arr[s->sp-1];
    if(num > 0) {
        *ip = pos;
    } else {
        *ip+=2;
    }
    s->sp--;
}

/*Sostituisce il valore di IP con il valore indicato se l’ultimo elemento
inserito nello stack `e minore di zero e lo rimuove, decrementando SP*/
void jneg(int pos, stack s, unsigned int *ip) {
    int num = s->arr[s->sp-1];
    if(num < 0) {
        *ip = pos;
    } else {
        *ip+=2;
    }
    s->sp--;
}

/*Addizione intera P1 + P2. Il risultato viene inserito nello stack.
 Se non c'è overflow, la funzione restituisce 0, altrimenti restituisce -1*/
void add(int reg1, int reg2, int *regs, stack s, unsigned int *ip) {
    s->arr[s->sp] = regs[reg1] + regs[reg2];
    s->sp++;
    *ip+=3;
    if(regs[reg1]>0 && regs[reg2]>0 && s->arr[s->sp] < 0)
        return -1; 
    if(regs[reg1]<0 && regs[reg2]<0 && s->arr[s->sp] > 0)
        return -1;
    return 0; 
}

/*Sottrazione intera P1 - P2. Il risultato viene inserito nello stack.
Terminazione i Se non c'è overflow, la funzione restituisce 0, altrimenti restituisce -1*/
n caso di overflow*/
void sub(int reg1, int reg2, int *regs, stack s, unsigned int *ip) {
    s->arr[s->sp] = regs[reg1] - regs[reg2];
    s->sp++;
    *ip+=3;
    if(regs[reg1]>0 && regs[reg2]>0 && s->arr[s->sp] < 0)
        return -1; 
    if(regs[reg1]<0 && regs[reg2]<0 && s->arr[s->sp] > 0)
        return -1;
    return 0; 
}

/*Moltiplicazione intera P1 * P2. Il risultato viene inserito nello stack.
 Se non c'è overflow, la funzione restituisce 0, altrimenti restituisce -1*/
void mul(int reg1, int reg2, int *regs, stack s, unsigned int *ip) {
    s->arr[s->sp] = regs[reg1] * regs[reg2];
    s->sp++;
    *ip+=3;
    if(regs[reg1]>0 && regs[reg2]>0 && s->arr[s->sp] < 0)
        return -1; 
    if(regs[reg1]<0 && regs[reg2]<0 && s->arr[s->sp] > 0)
        return -1;
    return 0; 
}

/*Divisione intera P1 / P2. Il risultato viene inserito nello stack.
Terminazione con errore in caso di divisione per zero*/
void divi(int reg1, int reg2, int *regs, stack s, unsigned int *ip) {
    if(regs[reg2]==0)
        return -1;
    else {
        s->arr[s->sp] = regs[reg1] / regs[reg2];
        s->sp++;
        *ip+=3;
    return 0;
}
