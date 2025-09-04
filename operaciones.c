#include "operaciones.h"

#include <stdio.h>
#include <string.h>

//Punteros a las variables de la ALU

int *Ax = &Axval;
int *Bx = &Bxval;
int *Cx = &Cxval;
int *Dx = &Dxval;

//Valores de las variables de la ALU
int Axval = 0;
int Bxval = 0;
int Cxval = 0;
int Dxval = 0;

//MOV - ASIGNACIÓN
int mov(int a, int b){
    a=5;
    int b;
    b=a;
}

//
int add(int a, int b){
    return a+b;
}

int sub(int a, int b){
    return a-b;
}

int mul(int a, int b){
    return a*b;
}

int div(int a, int b){
    if(b==0){
        printf("error. No se puede dividir entre cero\n");
    }
     return a/b;
}

int inc(int a){
   return a++;
}

int dec(int a){
  return a--;  
}