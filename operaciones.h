#ifndef OPERACIONES_H
#define OPERACIONES_H

extern int *Ax;
extern int *Bx;
extern int *Cx;
extern int *Dx;


void tabla(int numero_linea, char copia_linea[20], char err[40]);

int mov(int a, int b);
int add(int a, int b);
int sub(int a, int b);
int mul(int a, int b); 
int divi(int a, int b);
int inc(int a);
int dec(int a);


#endif