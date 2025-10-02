#ifndef PCB
#define PCB
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//estados de los procesos
typedef enum {
    nuevo,
    listo,
    terminado,  
    bloqueado,
    suspendido
} Estado_Proceso;
//la estructura del bloque de control de procesos

struct pcb{
    int id;
    int pc;
    int ax;
    int bx;
    int cx;
    int dx;
    char IR[50];
    Estado_Proceso estado; //estado actual del proceso
    char nombre_archivo[50]; //a.asm
    FILE *archivo; //puntero al archivo abierto para leer las instruccciones
    struct pcb *siguiente; // puntero al siguiente PCB en la lista
};


//listas en las que se almacennaran los procesos segun su estado
//extern PCB *lista_listos; //procesos que estan en espera para ejecutarse
//extern PCB *lista_ejecucion; //los procesos que estan en ejecucion
//extern PCB *lista_terminados; // los procesos que ya terminaron su ejecucion

// Declaraciones de funciones
struct pcb *crear(int id, char *nombre_archivo);

void agregar_listos(struct pcb **lista_listos, struct pcb *nuevo);
void agregar_ejecutando(struct pcb **lista_ejecutando, struct pcb *nuevo);
void agregar_terminados(struct pcb **lista_terminados, struct pcb *nuevo);

void listar_listos(struct pcb **lista_listos);
void listar_ejecutando(struct pcb **lista_ejecutando);
void listar_terminados(struct pcb **lista_terminados);

struct pcb *extraer_de_listos(struct pcb **lista_listos);
struct pcb *extraer_de_ejecutando(struct pcb **lista_ejecutando);

void liberar(struct pcb **elemento);// no lo ocupamos por que liberamos las listas hasta el final de la ejecucion

void vaciar_listos(struct pcb **listar_listos);
void vaciar_ejecutando(struct pcb **listar_ejecutando);
void vaciar_terminados(struct pcb **listar_terminados);


#endif

