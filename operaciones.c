#include "operaciones.h"
#include <stdio.h>
#include <string.h>

// Valores de las variables de la ALU
int Axval = 0;
int Bxval = 0;
int Cxval = 0;
int Dxval = 0;

// Punteros a las variables de la ALU

int *Ax = &Axval;
int *Bx = &Bxval;
int *Cx = &Cxval;
int *Dx = &Dxval;


//MOV - ASIGNACIÓN
int mov(int a, int b){
    a=b;
    return a;
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

int divi(int a, int b){
    return a/b;
}

int inc(int a){
    int valor = a+1;
  return valor; 
}

int dec(int a){
    int valor = a-1;
  return valor;  
}

void tabla(int numero_linea, char copia_linea[20], char err[40]){
    //printf("ID\t"); // ID del proceso, osea cuantos programas ejecutó anteriormente, si es el primero ID = 0, si es el segundo ID = 1, etc
    printf("\t%d\t", numero_linea); // El contador con el número de la linea sigueinte
    printf("\t\t%d\t", Axval);
    printf("%d\t", Bxval);
    printf("%d\t", Cxval);  
    printf("%d\t", Dxval);
    //printf("Proceso\t", ); // El nombre del archivo que se esta ejecutando
    printf("%s\t", copia_linea); //Linea de instrucción actual
    printf("\t%s", err); //Los errores, correcto, (Error, division por 0), (ERROR, registro invalido) etc
    printf("\n");
}