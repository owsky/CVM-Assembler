/*Nicolò Bertocco 873896 - Beatrice Messano 876673*/
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "interfaces.h"
#include "read.h"
#include "execute.h"

#define MAX_INT  2147483647
#define MIN_INT -2147483647

/*Array dei registri interni*/
int regs[32] = {0};
/*Instruction pointer*/
unsigned int ip = 0;
/*Stack*/
stack s = NULL;
/*Array delle istruzioni*/
int *arr;

/*Stampa su console il valore del registro indicato*/
void display(int reg) {
    printf("%d\n", regs[reg]);
    ip+=2;
}

/*Stampa su console il numero indicato di posizioni dello stack*/
void print_stack(int num) {
    int dim = s->sp-1;
    while(dim >= 0) {
        printf("%d: %d\n", num-1, s->arr[dim]);
        num--;
        dim--;
    }
    if(num > 0) {
        overflow(3);
    }
    ip+=2;
}

/*Inserisce il contenuto del registro indicato nello stack (in posizione SP)
ed incrementa SP*/
void push(int reg) {
    if(s->sp >= dimStack) {
        overflow(2);
    }
    s->arr[s->sp] = regs[reg];
    s->sp++;
    ip += 2;
}

/*Push con integer anziché registri*/
void pushInternal(int num) {
    if(s->sp >= dimStack) {
        overflow(2);
    }
    s->arr[s->sp] = num;
    s->sp++;
}

/*Decrementa SP e copia il valore in posizione SP (dopo il decremento)
nel registro indicato*/
void pop(int reg) {
    if(s->sp <= 0) {
        overflow(3);
    }
    s->sp--;
    regs[reg] = s->arr[s->sp];
    ip += 2;
}

/*Pop con integer anziché registri*/
int popInternal() {
    if(s->sp <= 0) {
        overflow(3);
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
inserito nello stack `e uguale a zero e lo rimuove, decrementando SP*/
void jz(int pos) {
    int num = popInternal();
    if(num == 0) {
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

/*Addizione intera P1 + P2. Il risultato viene inserito nello stack*/
void add(int reg1, int reg2) {
    if(regs[reg1] > 0 && regs[reg2] > MAX_INT - regs[reg1]) {
        overflow(0);
    } else if(regs[reg1] < 0 && regs[reg2] < (MIN_INT-1) - regs[reg1]) {
        overflow(1);
    }
    pushInternal(regs[reg1] + regs[reg2]);
    ip+=3;
}

/*Sottrazione intera P1 - P2. Il risultato viene inserito nello stack*/
void sub(int reg1, int reg2) {
    if(regs[reg1] > 0 && regs[reg2] < 0 && regs[reg2] < MAX_INT - regs[reg1]) {
        overflow(0);
    } else if(regs[reg1] < 0 && regs[reg2] > 0 && regs[reg2] > (MIN_INT-1) - regs[reg1]) {
        overflow(1);
    }
    pushInternal(regs[reg1] - regs[reg2]);
    ip+=3;
}

/*Moltiplicazione intera P1 * P2. Il risultato viene inserito nello stack*/
void mul(int reg1, int reg2) {
    if(regs[reg1] > 0 && regs[reg2] > 0 && regs[reg1] > MAX_INT / regs[reg2]) {
        overflow(0);
    } else if(regs[reg1] < 0 && regs[reg2] < 0 && regs[reg1] < MAX_INT / regs[reg2]) {
        overflow(0);
    } else if(regs[reg1] < 0 && regs[reg2] > 0 && regs[reg1] < (MIN_INT-1) / regs[reg2]) {
        overflow(1);
    } else if(regs[reg1] > 0 && regs[reg2] < 0 && regs[reg2] < (MIN_INT-1) / regs[reg1]) {
        overflow(1);
    }
    pushInternal(regs[reg1] * regs[reg2]);
    ip+=3;
}

/*Divisione intera P1 / P2. Il risultato viene inserito nello stack.
Terminazione con errore in caso di divisione per zero*/
void divi(int reg1, int reg2) {
    if(regs[reg2] == 0) {
        printf("Impossibile dividere per 0\n");
        halt();
        exit(1);
    } else {
        pushInternal(regs[reg1] / regs[reg2]);
        ip+=3;
    }
}

/*Termina libera la memoria allocata prima della terminazione del programma*/
void halt() {
    free(s);
    free(arr);
}

/*Parse ed esecuzione delle istruzioni*/
void esegui(char *str) {
    int len = 0;
    /*Caricamento delle istruzioni da file in un array*/
    arr = load(&(*str), &len);
    assert(arr);
    /*Istanziazione della stack*/
    s = (stack)malloc(sizeof(struct node));
    assert(s);

    /*Parse delle istruzioni tramite instruction pointer*/
    do {
        switch(arr[ip]) {
            case 0:
                halt();
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
                printf("Istruzione non supportata\n");
                break;
        }
    }while((int)ip < len);
}
