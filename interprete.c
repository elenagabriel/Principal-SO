#include <stdio.h>
#include <string.h>
#include "interprete.h"


int interprete(char texto[50]){  // ejecutar o salir
    char *delimitador = " \n";
    char *token;
    char copia_texto[50];
    int bandera=0;
    char nombre_archivo[20];
    int comando_valido;


if (strcmp(texto, "salir\n") == 0 || strcmp(texto, "Salir\n") == 0 || strcmp(texto, "SALIR\n") == 0) {
            printf("Saliendo...\n");
            bandera = 1;
        } else {
            comando_valido = 0;

            token = strtok(texto, delimitador);
            
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
                        strcpy(nombre_archivo, token);  // ahora sí guardamos el nombre
                        validar_archivo(nombre_archivo);
                        
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
        return bandera;
}


void validar_archivo(char *nombre_archivo) {
    FILE *archivo = fopen(nombre_archivo, "r");

    char linea[256];
    int numero_linea = 0;
    int hay_error = 0;
    int linea_correcta = 0;

    while (fgets(linea, sizeof(linea), archivo)) {
        numero_linea++;

        // eliminar salto de línea al final
        linea[strcspn(linea, "\n")] = '\0';

        // primer token = operación
        char *token_operacion = strtok(linea, " ");
        if (!token_operacion) continue;

        int es_tipo_1 = 0;
        int es_tipo_2 = 0;

        if (strcmp(token_operacion, "MOV") == 0 || strcmp(token_operacion, "ADD") == 0 || strcmp(token_operacion, "SUB") == 0 || strcmp(token_operacion, "MUL") == 0 || strcmp(token_operacion, "DIV") == 0) {
            es_tipo_1 = 1;
        } else if (strcmp(token_operacion, "INC") == 0 || strcmp(token_operacion, "DEC") == 0) {
            es_tipo_2 = 1;
        } else {
            printf("Error en línea %d: Operación desconocida: %s\n", numero_linea, token_operacion);
            hay_error = 1;
            continue;
        }

        // siguiente token = registro + posible valor
        char *segundo_parte_en_linea = strtok(NULL, ""); // esto avanza en token 2
        if (!segundo_parte_en_linea) {
            printf("Error en línea %d: Falta el registro\n", numero_linea);
            hay_error = 1;
            continue;
        }

        if (es_tipo_2) {
            // INC/DEC solo aceptan un registro exacto
            if (!(strcmp(segundo_parte_en_linea, "Ax") == 0 || strcmp(segundo_parte_en_linea, "Bx") == 0 || strcmp(segundo_parte_en_linea, "Cx") == 0 || strcmp(segundo_parte_en_linea, "Dx") == 0)) {
                printf("Error en línea %d: Registro inválido %s\n", numero_linea, segundo_parte_en_linea);
                hay_error = 1;
                continue;
            }
            printf("Línea %d válida: %s %s\n", numero_linea, token_operacion, segundo_parte_en_linea);
            linea_correcta++;
        } else if (es_tipo_1) {
            // Debe ser del tipo Ax,valor sin espacios
            char *coma = strchr(segundo_parte_en_linea, ','); // Encuentra una coma 
            if (!coma) { // si no hya coma
                printf("Error en línea %d: Falta coma entre registro y valor\n", numero_linea);
                hay_error = 1;
                continue;
            }

            *coma = '\0'; // ya parto ese token en dos, si hay coma lo separo en registro y valor
            char *registro = segundo_parte_en_linea;
            char *valor = coma + 1; // avanza enla coma que ahora es \0 y apunta a valor

            if (!(strcmp(registro, "Ax") == 0 || strcmp(registro, "Bx") == 0 || strcmp(registro, "Cx") == 0 || strcmp(registro, "Dx") == 0)) {
                printf("Error en línea %d: Registro inválido %s\n", numero_linea, registro);
                hay_error = 1;
                continue;
            }
        // aqui deberia validar que sea un numero afuerzas, porque si no meto nada 
            printf("Línea %d válida: %s %s,%s\n", numero_linea, token_operacion, registro, valor);
            linea_correcta++;
        }
    }
    fclose(archivo);
}