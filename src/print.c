/*Nicolò Bertocco 873896 - Beatrice Messano 876673*/
#include "interfaces.h"
#include "read.h"
#include "print.h"
#include <stdio.h>
#include <string.h>

/*
        [posizione] istruzione P1 P2
        dove posizione è la posizione nell'array, istruzione il codice mnemonico, P1 e P2 sono gli eventuali parametri.
        Nel caso uno del parametri sia un registro stampare la rappresentazione mnemonica corrispondente (es: R3 anziché 3)
        [0] MOV R0 5
        [3] CALL 8
        [5] DISPLAY R30
*/
table match(table t, int b){
  while(t){
    if(b == t-> cod){
      return t;
    }
   t= t->next;
  }
  return NULL;
}

void stampa(char *str, table t) {
    int i = 0,  len = 0, *arr = load(&(*str), &len);
    table c;

    if(arr != NULL){
      while(i<len){
        c = match(t, arr[i]);
        printf("[%d], %s", i , c-> name);
        i++;
        if(t->par>0){

            if(!strcmp(t-> p1, "reg")){
              printf("R%d", arr[i]);

            }
            else {
              printf("%d", arr[i]);
            }
            if(t-> p2 != NULL){
              if(!strcmp(t-> p2, "reg")){
                printf("R%d", arr[i+1]);

              }
              else {
                printf("%d", arr[i+1]);

              }
            }



      } else
        printf("\n");




      }
    }
  }
