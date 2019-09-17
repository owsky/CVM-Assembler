#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "interfaces.h"
#include "read.h"
#include "execute.h"

#define MAX_INT  2147483647
#define MIN_INT -2147483648

int regs[32] = {0};
unsigned int ip = 0;
stack s = NULL;
int *arr;

void display(int reg) {
    printf("%d\n", regs[reg]);
    ip+=2;
}

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

void push(int reg) {
    if(s->sp >= stackSize) {
        overflow(2);
    }
    s->arr[s->sp] = regs[reg];
    s->sp++;
    ip += 2;
}

void pushInternal(int num) {
    if(s->sp >= stackSize) {
        overflow(2);
    }
    s->arr[s->sp] = num;
    s->sp++;
}

void pop(int reg) {
    if(s->sp <= 0) {
        overflow(3);
    }
    s->sp--;
    regs[reg] = s->arr[s->sp];
    ip += 2;
}

int popInternal() {
    if(s->sp <= 0) {
        overflow(3);
    }
    s->sp--;
    return s->arr[s->sp];
}

void mov(int reg, int num) {
    regs[reg] = num;
    ip+=3;
}

void call(int pos) {
    pushInternal(ip+2);
    ip = pos;
}

void ret() {
    ip = popInternal();
}

void jmp(int pos) {
    ip = pos;
}

void jz(int pos) {
    int num = popInternal();
    if(num == 0) {
        ip = pos;
    } else {
        ip+=2;
    }
}

void jpos(int pos) {
    int num = popInternal();
    if(num > 0) {
        ip = pos;
    } else {
        ip+=2;
    }
}

void jneg(int pos) {
    int num = popInternal();
    if(num < 0) {
        ip = pos;
    } else {
        ip+=2;
    }
}

void add(int reg1, int reg2) {
    long check = (long) reg1 + (long) reg2;
    if(check > MAX_INT) {
        overflow();
    } else if(check < MIN_INT) {
        underflow();
    }
    pushInternal(regs[reg1] + regs[reg2]);
    ip+=3;
}

void sub(int reg1, int reg2) {
    long check = (long) reg1 - (long) reg2;
    if(check > MAX_INT) {
        overflow();
    } else if(check < MIN_INT) {
        underflow();
    }
    pushInternal(regs[reg1] - regs[reg2]);
    ip+=3;
}

void mul(int reg1, int reg2) {
    long check = (long) reg1 * (long) reg2;
    if(check > MAX_INT) {
        overflow();
    } else if(check < MIN_INT) {
        underflow();
    }
    pushInternal(regs[reg1] * regs[reg2]);
    ip+=3;
}

void divi(int reg1, int reg2) {
    if(regs[reg2] == 0) {
        printf("Error: can't divide by 0\n");
        halt();
        exit(1);
    } else {
        pushInternal(regs[reg1] / regs[reg2]);
        ip+=3;
    }
}

void halt() {
    free(s);
    free(arr);
}

/*Instruction parse and execution*/
void execute(char *str) {
    int len = 0;
    /*Loads instructions and parameters from file*/
    arr = load(str, &len);
    assert(arr);
    s = (stack)malloc(sizeof(struct node));
    assert(s);

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
                printf("Unsupported function\n");
                break;
        }
    }while((int)ip < len);
}
