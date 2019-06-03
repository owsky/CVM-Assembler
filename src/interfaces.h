#include <stdlib.h>

typedef struct node {
    int arr[65536/sizeof(int)];
    unsigned int sp;
} *stack;

typedef struct tab {
    int cod, par;
    int reg[2];
    char name[11];
} *table;

void loadTable(table *t);
table match(table *t, int num);
int isReg(table *t);
void destroy(table *t);
void overflow();
void stackOverflow();
void stackUnderflow();
