#include <stdio.h>
#include <stdlib.h>
#include "pcb.h"

struct pcb *lista_listos = NULL;
struct pcb *lista_ejecutando = NULL;
struct pcb *lista_terminados = NULL;
struct pcb *nodo = NULL;
struct pcb *nodo2 = NULL;
struct pcb *nodo3 = NULL;

int menu(void)
{
    int opt;
    printf("\nMENU\n");
    printf("1. Agregar a listos\n");
    printf("2. Listar listos\n");
    printf("3. Extraer de listos y pasar a ejecutando\n");
    printf("4. listar ejecutando\n");
    printf("5. Extraer de ejecutando a terminados\n");
    printf("6. Listar terminados\n");
    printf("7. Salir\n");
    printf(" opción: ");
    scanf("%d", &opt);
    return opt;
}

int main()
{
    int id = 0;
    int opt;

    do
    {
        opt = menu();

        switch (opt)
        {
        case 1:
            printf("1. Agregar a listos\n");
            char *nombre_archivo = "a.asm";
            nodo = crear(id, nombre_archivo);
            agregar_listos(&lista_listos, nodo);
            id++; 
            break;

        case 2:
            printf("2. Listar listos\n");

            listar_listos(&lista_listos);
            break;

        case 3:
            printf("3. Extraer de listos y pasar a ejecutando\n");
            nodo = extraer_de_listos(&lista_listos);
            agregar_ejecutando(&lista_ejecutando, nodo);
            break;

        case 4:
            printf("4. listar ejecutando\n");
            listar_ejecutando(&lista_ejecutando);
            break;

        case 5:
            printf("5. Extraer de ejecutando a terminados\n");
            nodo = extraer_de_ejecutando(&lista_ejecutando);
            agregar_terminados(&lista_terminados, nodo);
            break;
        case 6:
            printf("6. Listar terminados\n");
            listar_terminados(&lista_terminados);
            break;
        case 7:
            printf("7. Salir\n");
            break;
        default:
            printf("opción válida\n");
            break;
        }
    } while (opt != 7);
    vaciar_listos(&lista_listos);
    vaciar_ejecutando(&lista_ejecutando);
    vaciar_terminados(&lista_terminados);
    return 0;
}