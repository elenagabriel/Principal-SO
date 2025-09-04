#include <stdio.h>
#include <string.h>
#include "interprete.h"

int main() { 

    char texto[50];
    char copia_texto[50];
    int bandera = 0; 

    do {
        printf("$ ");
        fgets(texto, sizeof(texto), stdin);
        strcpy(copia_texto, texto);
        bandera = interprete(copia_texto);
        
    } while(bandera == 0);

    return 0;
}