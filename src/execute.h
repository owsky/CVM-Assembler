/*P1G114*/
/*Nicolò Bertocco 873896 - Beatrice Messano 876673*/
void display(int reg);
void print_stack(int num);
void push(int reg);
void pushInternal(int num);
void pop(int reg);
int popInternal();
void mov(int reg, int num);
void call(int pos);
void ret();
void jmp(int pos);
void jz(int pos);
void jpos(int pos);
void jneg(int pos);
void add(int reg1, int reg2);
void sub(int reg1, int reg2);
void mul(int reg1, int reg2);
void divi(int reg1, int reg2);
void esegui(char *s);
void halt();
