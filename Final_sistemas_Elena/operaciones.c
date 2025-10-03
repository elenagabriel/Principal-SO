
 #include "operaciones.h"
    #include <stdio.h>
    #include <string.h>
    #include <ncurses.h>
    #include <unistd.h>

  extern int proceso_id;
  extern char nombre_archivo_actual[50];




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
    
    return b;
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

void reinciar_registros() {
    *Ax = 0;
    *Bx = 0;
    *Cx = 0;
    *Dx = 0;
}


void tabla(int numero_linea, char copia_linea[20], char err[40]) {

    // limpiar la línea antes de escribir
    move(2, 0);
    clrtoeol();

    mvprintw(2, 0, "%-5d %-5d %-8d %-8d %-8d %-8d %-12s",
         proceso_id, numero_linea, Axval, Bxval, Cxval, Dxval,
         nombre_archivo_actual);
    mvprintw(2, 60, " %s",copia_linea);
    mvprintw(2, 80, " %s",err);

    refresh();  // actualiza pantalla
    getch();    
    move(2, 0);
    clrtoeol();
    refresh();
}