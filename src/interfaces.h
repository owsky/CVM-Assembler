/*Nicolò Bertocco 873896 - Beatrice Messano NUMEROMATRICOLA*/
#ifndef interfaces
#define interfaces
#include <stdlib.h>

/*Definizione stack*/
typedef struct node {
    int arr[16384];
    unsigned int sp;
} *stack;

/*Definizione tabella funzioni*/
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
