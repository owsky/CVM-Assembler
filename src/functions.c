#include "functions.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

int regs[32] = {0};
unsigned int ip = 0;
stack s = NULL;

/*Stampa su console il valore del registro indicato*/
void display(int reg) {
    printf("%d\n", regs[reg]);
    ip+=2;
}

/*stampa su console il numero indicato di posizioni dello stack.
Stampare le posizioni in ordine inverso a partire dalla posizione SP-1
fino a SP-N inclusa.
Stampare l’indice della posizione ed il valore in essa contenuto*/
void print_stack(int num) {
    while(num > 0) {
        printf("%d: %d\n", num, s->arr[num]);
        num--;
    }
    ip+=2;
}

/*Inserisce il contenuto del registro indicato nello stack (in posizione SP)
ed incrementa SP*/
void push(int reg) {
    if(s->sp >= 65536/sizeof(int)) {
        stackOverflow();
    }
    s->arr[s->sp] = regs[reg];
    s->sp++;
    ip += 2;
}

void pushInternal(int num) {
    if(s->sp >= 65536/sizeof(int)) {
        stackOverflow();
    }
    s->arr[s->sp] = num;
    s->sp++;
}

/*Decrementa SP e copia il valore in posizione SP (dopo il decremento)
nel registro indicato*/
void pop(int reg) {
    if(s->sp <= 0) {
        stackUnderflow();
    }
    s->sp--;
    regs[reg] = s->arr[s->sp];
    ip += 2;
}

int popInternal() {
    if(s->sp <= 0) {
        stackUnderflow();
    }
    s->sp--;
    return s->arr[s->sp];
}

/*Copia il valore P2 nel registro indicato*/
void mov(int reg, int num) {
    regs[reg] = num;
    ip+=3;
}

/*Chiamata a subroutine. PUSH IP (posizione successiva a CALL)
e JMP alla posizione indicata*/
void call(int pos) {
    pushInternal(ip+2);
    ip = pos;
}

/*Ritorno da chiamata a subroutine, POP in IP*/
void ret() {
    ip = popInternal();
}

/*Sostituisce il valore di IP con il valore indicato*/
void jmp(int pos) {
    ip = pos;
}

/*Sostituisce il valore di IP con il valore indicato se l’ultimo elemento
inserito nello stack `e diverso da zero e lo rimuove, decrementando SP*/
void jz(int pos) {
    int num = popInternal();
    if(num != 0) {
        ip = pos;
    } else {
        ip+=2;
    }
}

/*Sostituisce il valore di IP con il valore indicato se l’ultimo elemento
inserito nello stack `e maggiore di zero e lo rimuove, decrementando SP*/
void jpos(int pos) {
    int num = popInternal();
    if(num > 0) {
        ip = pos;
    } else {
        ip+=2;
    }
}

/*Sostituisce il valore di IP con il valore indicato se l’ultimo elemento
inserito nello stack `e minore di zero e lo rimuove, decrementando SP*/
void jneg(int pos) {
    int num = popInternal();
    if(num < 0) {
        ip = pos;
    } else {
        ip+=2;
    }
}

/*Addizione intera P1 + P2. Il risultato viene inserito nello stack.
 Se non c'è overflow, la funzione restituisce 0, altrimenti restituisce -1*/
void add(int reg1, int reg2) {
    int res = regs[reg1] + regs[reg2];
    pushInternal(res);
    ip+=3;
    if(regs[reg1]>0 && regs[reg2]>0 && res < 0) {
        overflow();
    } else if(regs[reg1]<0 && regs[reg2]<0 && res > 0) {
        overflow();
    }
}

/*Sottrazione intera P1 - P2. Il risultato viene inserito nello stack*/
void sub(int reg1, int reg2) {
    int res = regs[reg1] - regs[reg2];
    pushInternal(res);
    ip+=3;
    if(regs[reg1]>0 && regs[reg2]<0 && res < 0) {
        overflow();
    } else if(regs[reg1]<0 && regs[reg2]>0 && res > 0) {
        overflow();
    }
}

/*Moltiplicazione intera P1 * P2. Il risultato viene inserito nello stack.
 Se non c'è overflow, la funzione restituisce 0, altrimenti restituisce -1*/
void mul(int reg1, int reg2) {
    int res = regs[reg1] * regs[reg2];
    pushInternal(res);
    ip+=3;
    if(regs[reg1]>0 && regs[reg2]>0 && res < 0)
        overflow();
    if(regs[reg1]<0 && regs[reg2]<0 && res > 0)
        overflow();
}

/*Divisione intera P1 / P2. Il risultato viene inserito nello stack.
Terminazione con errore in caso di divisione per zero*/
void divi(int reg1, int reg2) {
    if(regs[reg2]==0) {
        printf("Divisione per 0\n");
        exit(1);
    } else {
        int res = regs[reg1] / regs[reg2];
        pushInternal(res);
        ip+=3;
    }
}

void exe(int *arr, int len) {
    s = (stack)malloc(sizeof(struct node));
    assert(s);
    s->arr[0] = 0;
    s->sp = 0;

    assert(arr);
    do {
        switch(arr[ip]) {
            case 0:
                return;
            case 1:
                display(arr[ip+1]);
                break;
            case 2:
                print_stack(arr[ip+1]);
                break;
            case 10:
                push(arr[ip+1]);
                break;
            case 11:
                pop(arr[ip+1]);
                break;
            case 12:
                mov(arr[ip+1], arr[ip+2]);
                break;
            case 20:
                call(arr[ip+1]);
                break;
            case 21:
                ret();
                break;
            case 22:
                jmp(arr[ip+1]);
                break;
            case 23:
                jz(arr[ip+1]);
                break;
            case 24:
                jpos(arr[ip+1]);
                break;
            case 25:
                jneg(arr[ip+1]);
                break;
            case 30:
                add(arr[ip+1], arr[ip+2]);
                break;
            case 31:
                sub(arr[ip+1], arr[ip+2]);
                break;
            case 32:
                mul(arr[ip+1], arr[ip+2]);
                break;
            case 33:
                divi(arr[ip+1], arr[ip+2]);
                break;
            default:
                break;
        }
    }while((int)ip < len);
    free(s);
}
