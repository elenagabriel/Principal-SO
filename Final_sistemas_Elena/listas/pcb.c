#include <stdio.h>
#include <stdlib.h>
#include "pcb.h"

struct pcb *crear(int id, char *nombre_archivo){

    struct pcb *pcb = NULL;
    
    pcb = (struct pcb *)malloc(sizeof(struct pcb));
    pcb->id = id;
    pcb->pc = pcb->ax = pcb->bx = pcb->cx = pcb->dx = 0;
    strcpy(pcb->IR, "");
    strcpy(pcb->nombre_archivo, nombre_archivo);
    pcb->siguiente = NULL;

    return pcb;
}

void agregar_listos(struct pcb **lista_listos, struct pcb *nuevo){

    if (*lista_listos == NULL)
    {                          // si la lista esta vacia
        *lista_listos = nuevo; // el nuevo pcb sera el primer elemento de la lista
    }
    else
    {
        struct pcb *cabezal = *lista_listos; // cabezal apunta al primer elemento de la lista
        while (cabezal->siguiente != NULL)
        {                                 // recorre la lista hasta encontrar el ultimo elemento
            cabezal = cabezal->siguiente; // avanza al siguiente elemento
        }
        cabezal->siguiente = nuevo; // el ultimo elemento apunta al nuevo pcb
    }
}

void agregar_ejecutando(struct pcb **lista_ejecutando, struct pcb *nuevo){

    if (*lista_ejecutando == NULL)
    {                              // si la lista esta vacia
        *lista_ejecutando = nuevo; // el nuevo pcb sera el primer elemento de la lista
    }
    else
    {
        struct pcb *cabezal = *lista_ejecutando; // cabezal apunta al primer elemento de la lista
        while (cabezal->siguiente != NULL)
        {                                 // recorre la lista hasta encontrar el ultimo elemento
            cabezal = cabezal->siguiente; // avanza al siguiente elemento
        }
        cabezal->siguiente = nuevo; // el ultimo elemento apunta al nuevo pcb
    }
}

void agregar_terminados(struct pcb **lista_terminados, struct pcb *nuevo){

    if (*lista_terminados == NULL)
    {                              // si la lista esta vacia
        *lista_terminados = nuevo; // el nuevo pcb sera el primer elemento de la lista
    }
    else
    {
        struct pcb *cabezal = *lista_terminados; // cabezal apunta al primer elemento de la lista
        while (cabezal->siguiente != NULL)
        {                                 // recorre la lista hasta encontrar el ultimo elemento
            cabezal = cabezal->siguiente; // avanza al siguiente elemento
        }
        cabezal->siguiente = nuevo; // el ultimo elemento apunta al nuevo pcb
    }
}

void listar_listos(struct pcb **lista_listos){

    struct pcb *auxiliar;
    auxiliar = *lista_listos;
    while (auxiliar != NULL)
    {
        printf("Id: %d\n", auxiliar->id);
        auxiliar = auxiliar->siguiente;
    }
    printf("\n");
}

void listar_ejecutando(struct pcb **lista_ejecutando){

    struct pcb *auxiliar;
    auxiliar = *lista_ejecutando;
    while (auxiliar != NULL)
    {
        printf("Id: %d\n", auxiliar->id);
        auxiliar = auxiliar->siguiente;
    }
    printf("\n");
}

void listar_terminados(struct pcb **lista_terminados){
    
    struct pcb *auxiliar;
    auxiliar = *lista_terminados;
    while (auxiliar != NULL)
    {
        printf("Id: %d\n", auxiliar->id);
        auxiliar = auxiliar->siguiente;
    }
    printf("\n");
}


struct pcb *extraer_de_listos(struct pcb **lista_listos){
    if (*lista_listos == NULL)
    { // si la lista no esta vacia
        return 0;
    }
    else
    {
        struct pcb *aux;     // puntero auxiliar
        aux = *lista_listos; // aux apunta al primer pcb de la lista
        *lista_listos = aux->siguiente;
        aux->siguiente = NULL;
        return aux; // retorna el pcb extraido
    }
}

struct pcb *extraer_de_ejecutando(struct pcb **lista_ejecutando){
    if (*lista_ejecutando == NULL)
    { // si la lista no esta vacia
        return 0;
    }
    else
    {
        struct pcb *aux;     // puntero auxiliar
        aux = *lista_ejecutando; // aux apunta al primer pcb de la lista
        *lista_ejecutando = aux->siguiente;
        aux->siguiente = NULL;
        return aux; // retorna el pcb extraido
    }
}

void liberar(struct pcb **elemento){ // Debe liberar el nodo que se extrajó, hacer uso de free y apuntar el nodo a NULL
    free(*elemento);
    *elemento = NULL;
}

void vaciar_listos(struct pcb **lista_listos){

    struct pcb *auxiliar = *lista_listos;
    struct pcb *siguiente;

    while (auxiliar != NULL)
    {
        siguiente = auxiliar->siguiente; 
        free(auxiliar);                  
        auxiliar = siguiente;            
    }
    *lista_listos = NULL;
    printf("'Listos' vaciada completamente\n");
}

void vaciar_ejecutando(struct pcb **listar_ejecutando){

    struct pcb *auxiliar = *listar_ejecutando;
    struct pcb *siguiente;

    while (auxiliar != NULL)
    {
        siguiente = auxiliar->siguiente; 
        free(auxiliar);                  
        auxiliar = siguiente;            
    }
    *listar_ejecutando = NULL;
    printf("'Ejecutando' vaciada completamente\n");
}

void vaciar_terminados(struct pcb **listar_terminados){

    struct pcb *auxiliar = *listar_terminados;
    struct pcb *siguiente;

    while (auxiliar != NULL)
    {
        siguiente = auxiliar->siguiente; 
        free(auxiliar);                  
        auxiliar = siguiente;            
    }
    *listar_terminados = NULL;
    printf("'Terminados' vaciada completamente\n");
}