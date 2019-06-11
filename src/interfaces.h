#ifndef interfaces
#define interfaces
#include <stdlib.h>

#define stackSize 16000
typedef struct node {
    int arr[stackSize];
    unsigned int sp;
} *stack;

typedef struct tab {
    int cod;
    int par;
    char p1[10], p2[10];
    char name[15];
    struct tab *next;
} *table;

void addFunction(table *t, int cod, char *p1, char *p2, char *name);
void loadTable(table *t);
void destroy(table t);
void overflow(int t);
#endif
