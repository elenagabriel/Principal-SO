#ifndef INTERPRETE_H
#define INTERPRETE_H


#include <string.h>
#include <stdio.h>

int interprete(char texto[50]);

int interprete(char texto[50]){
    char *delimitador = " \n";
    char *token;
    char texto[50];
    char copia_texto[50];
    int bandera=0;

    char nombre_archivo[20];
    int comando_valido;


if (strcmp(texto, "salir\n") == 0 || strcmp(texto, "Salir\n") == 0 || strcmp(texto, "SALIR\n") == 0) {
            printf("Saliendo...\n");
            bandera = 1;
        } else {
            comando_valido = 0;
            token = strtok(copia_texto, delimitador);
            
            // Primer token debe ser "ejecutar"
            if (token != NULL && strcmp(token, "ejecutar") == 0) {
                // Segundo token debe ser el nombre del archivo
                token = strtok(NULL, delimitador);
                
                if (token != NULL) {
                    // Verificar extensión .asm
                    char *punto = strrchr(token, '.');
                    if (punto != NULL && strcmp(punto, ".asm") == 0) {
                        printf("Archivo válido: %s\n", token);
                        comando_valido = 1;
                        
                        // Aquí puedes procesar el archivo...
                        // Por ejemplo: strcpy(nombre_archivo, token);
                        strcpy(nombre_archivo, token);  // ahora sí guardamos el nombre
                        leerArchivo(nombre_archivo);
                        
                    } else {
                        printf("Error: El archivo debe tener extensión .asm\n");
                    }
                } else {
                    printf("Error: Falta el nombre del archivo\n");
                }
            }
            
            if (!comando_valido && token != NULL) {
                printf("Instrucción no válida\n");
            }
        }


}
#endif

