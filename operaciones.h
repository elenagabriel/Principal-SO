
#ifndef OPERACIONES_H
#define OPERACIONES_H

extern int *Ax;
extern int *Bx;
extern int *Cx;
extern int *Dx;

void reinciar_registros();
void tabla(int numero_linea, char copia_linea[9], char err[20]);

int mov(int a, int b);
int add(int a, int b);
int sub(int a, int b);
int mul(int a, int b); 
int divi(int a, int b);
int inc(int a);
int dec(int a);


#endif