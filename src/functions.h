#include "interfaces.h"

void display(int reg, int *regs, unsigned int *ip);
void print_stack(int num, stack s, unsigned int *ip);
void push(int reg, stack s, int *regs, unsigned int *ip);
void pop(int reg, stack s, int *regs, unsigned int *ip);
void mov(int reg, int num, int *regs, unsigned int *ip);
void call(int pos, stack s, unsigned int *ip);
void ret(stack s, unsigned int *ip);
void jmp(int pos, unsigned int *ip);
void jz(int pos, stack s, unsigned int *ip);
void jpos(int pos, stack s, unsigned int *ip);
void jneg(int pos, stack s, unsigned int *ip);
int add(int reg1, int reg2, int *regs, stack s, unsigned int *ip);
int sub(int reg1, int reg2, int *regs, stack s, unsigned int *ip);
int mul(int reg1, int reg2, int *regs, stack s, unsigned int *ip);
int divi(int reg1, int reg2, int *regs, stack s, unsigned int *ip);
