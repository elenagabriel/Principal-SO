#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#include <ncurses.h>
#include <unistd.h>
#include "interprete.h" 
#include "operaciones.h" 
 
int proceso_id = -1; 
char nombre_archivo_actual[50] = ""; 
 
int interprete(char texto[50]) 
{ // ejecutar o salir 
    char *delimitador = " \n"; 
    char *token; 
    char copia_texto[50]; 
    int bandera = 0; 
    char nombre_archivo[20]; 
    int comando_valido; 
 
     
 
    if (strcmp(texto, "salir") == 0 || strcmp(texto, "Salir") == 0 || strcmp(texto, "SALIR") == 0) 
    { 
        mvprintw(1, 0, "Saliendo...\n"); 
        refresh();
        sleep(1);
        bandera = 1; 
    } 
    else 
    { 
        comando_valido = 0; 
 
        token = strtok(texto, delimitador); 
 
        // Primer token debe ser "ejecutar" 
        if (token != NULL && strcmp(token, "ejecutar") == 0) 
        { 
            // Segundo token debe ser el nombre del archivo 
            token = strtok(NULL, delimitador); 
 
            if (token != NULL) 
            { 
                // Verificar extensión .asm 
                char *punto = strrchr(token, '.'); 
                if (punto != NULL && strcmp(punto, ".asm") == 0) 
                { 
                    mvprintw(1, 0, "Archivo válido: %s\n", token); 
                    refresh();
                    sleep(2);
                    move(1, 0);
                    clrtoeol();
                    refresh();
                    comando_valido = 1; 
 
                    // Aquí puedes procesar el archivo... 
                    strcpy(nombre_archivo, token); // ahora sí guardamos el nombre 
                    proceso_id++; //se ira incrementando el id de cada proceso 
                    strcpy(nombre_archivo_actual, nombre_archivo); //nos guardara el archivo actual 
                     
                    validar_archivo(nombre_archivo); 
                
                } 
                else 
                { 
                    mvprintw(1, 0, "Error: El archivo debe tener extensión .asm\n"); 
                    refresh();
                    sleep(2);
                    move(1, 0);
                    clrtoeol();
                    refresh();
                } 
            } 
            else 
            { 
                mvprintw(1, 0, "Error: Falta el nombre del archivo\n"); 
                refresh();
                sleep(2);
                move(1, 0); // esto por que si no no se borra
                clrtoeol(); // para que no se quede fijo
                refresh();
            } 
        } 
 
        if (!comando_valido && token != NULL) 
        { 
            mvprintw(1, 0, "Instrucción no válida\n"); 
            refresh();
            sleep(2);
            move(1, 0);
            clrtoeol();
            refresh();
        } 
    } 
    return bandera; 
} 
 
void validar_archivo(char *nombre_archivo) 
{ 
    //encabezado
    //mvprintw(1, 0, "\nTabla de Registros:\n"); 
    //mvprintw(1, 0, "ID\tPC\tAx\tBx\tCx\tDx\tProceso\t\tIR\t\tStatus\n"); 
    mvprintw(1, 0, "%-5s %-5s %-8s %-8s %-8s %-10s %-10s %-20s %-50s",
             "ID", "PC", "Ax", "Bx", "Cx", "Dx",
             "Proceso", "IR", "Status");
    refresh();
    //move(1, 0);
    clrtoeol();
    refresh();
    FILE *archivo = fopen(nombre_archivo, "r"); 
 
    char linea[20]; 
    char copia_linea[20]; 
    char sin_error[40] = "Correcto"; 
 
    int numero_linea = 1; 
    int hay_error = 0; 
    int linea_correcta = 0; // contador de lineas 
    int linea_incorrecta = 0; 
 
    while (fgets(linea, sizeof(linea), archivo)) 
    { 
        numero_linea++; 
 
        // eliminar salto de línea al final 
        linea[strcspn(linea, "\n")] = '\0'; 
        strcpy(copia_linea, linea); 
 
        // primer token = operación 
        char *token_operacion = strtok(linea, "  "); 
 
        if (!token_operacion) 
            continue; 
 
        int es_tipo_1 = 0; 
        int es_tipo_2 = 0; 
 
        if (strcmp(token_operacion, "MOV") == 0 || strcmp(token_operacion, "ADD") == 0 || strcmp(token_operacion, "SUB") == 0 || strcmp(token_operacion, "MUL") == 0 || strcmp(token_operacion, "DIV") == 0) 
        { 
            es_tipo_1 = 1; 
        } 
        else if (strcmp(token_operacion, "INC") == 0 || strcmp(token_operacion, "DEC") == 0) 
        { 
            es_tipo_2 = 1; 
        } 
        else 
        { 
            // error a 
            char error_a[40] = "Operación desconocida"; 
            hay_error = 1; 
            tabla(numero_linea, copia_linea, error_a); 
            linea_incorrecta = 1; 
            continue; 
        } 
 
        // siguiente token = registro + posible valor 
        char *segundo_parte_en_linea = strtok(NULL, ""); // esto avanza en token 2 
        if (!segundo_parte_en_linea) 
        { 
            // error b 
            char error_b[40] = "Falta el registro"; 
            hay_error = 2; 
            tabla(numero_linea, copia_linea, error_b); 
            linea_incorrecta = 1; 
            continue; 
        } 
 
        int *registro_corres; 
 
        if (es_tipo_2) 
        { 
            segundo_parte_en_linea[strcspn(segundo_parte_en_linea, "\n")] = '\0'; // elimina el \n si existe
            // INC/DEC solo aceptan un registro exacto 
            if (!(strcmp(segundo_parte_en_linea, "Ax") == 0 || strcmp(segundo_parte_en_linea, "Bx") == 0 || strcmp(segundo_parte_en_linea, "Cx") == 0 || strcmp(segundo_parte_en_linea, "Dx") == 0)) 
            { 
                // error c 

                char error_c[40] = "Registro inválido"; 
                hay_error = 3; 
                tabla(numero_linea, copia_linea, error_c); 
                linea_incorrecta = 1; 
                continue; 
            } 
            // printf("Línea %d válida: %s %s\n", numero_linea, token_operacion, segundo_parte_en_linea); 
            linea_correcta++; 
            char *registro = segundo_parte_en_linea; 
 
            if (strcmp(registro, "Ax") == 0) 
            { 
                registro_corres = Ax; 
            } 
            else if (strcmp(registro, "Bx") == 0) 
            { 
                registro_corres = Bx; 
            } 
            else if (strcmp(registro, "Cx") == 0) 
            { 
                registro_corres = Cx; 
            } 
            else if (strcmp(registro, "Dx") == 0) 
            { 
                registro_corres = Dx; 
            } 
 
            if (strcmp(token_operacion, "INC") == 0) 
            { 
                *registro_corres = inc(*registro_corres); 
                tabla(numero_linea, copia_linea, sin_error); 
            } 
            else if (strcmp(token_operacion, "DEC") == 0) 
            { 
                *registro_corres = dec(*registro_corres); 
                tabla(numero_linea, copia_linea, sin_error); 
            } 
        } 
        else if (es_tipo_1) 
        { 
            // Debe ser del tipo Ax,valor sin espacios 
            char *coma = strchr(segundo_parte_en_linea, ','); // Encuentra una coma 
            if (!coma) 
            { // si no hay coma 
                // error d 
                char error_d[40] = "Falta coma entre registro y valor"; 
                hay_error = 4; 
                tabla(numero_linea, copia_linea, error_d); 
 
                linea_incorrecta = 1; 
                continue; 
            } 
 
            *coma = '\0'; // ya parto ese token en dos, si hay coma lo separo en registro y valor 
            char *registro = segundo_parte_en_linea; 
            char *valor = coma + 1; // avanza enla coma que ahora es \0 y apunta a valor 
            int valor_numerico = atoi(valor); 
 
            if (!(strcmp(registro, "Ax") == 0 || strcmp(registro, "Bx") == 0 || strcmp(registro, "Cx") == 0 || strcmp(registro, "Dx") == 0)) 
            { 
                // error e 
                char error_e[40] = "Registro inválido"; 
                hay_error = 5; 
                tabla(numero_linea, copia_linea, error_e); 
                linea_incorrecta = 1; 
                continue; 
            } 
 
            if (strcmp(registro, "Ax") == 0) 
            { 
                registro_corres = Ax; 
            } 
            else if (strcmp(registro, "Bx") == 0) 
            { 
                registro_corres = Bx; 
            } 
            else if (strcmp(registro, "Cx") == 0) 
            { 
                registro_corres = Cx; 
            } 
            else if (strcmp(registro, "Dx") == 0) 
            { 
                registro_corres = Dx; 
            } 
 
            // aqui deberia validar que sea un numero afuerzas, porque si no meto nada 
            // printf("Línea %d válida: %s %s,%s\n", numero_linea, token_operacion, registro, valor); 
            linea_correcta++; 
            // lo que va en el IR 
 
            if (strcmp(token_operacion, "MOV") == 0) 
            { 
                *registro_corres = mov(*registro_corres, valor_numerico); 
                tabla(numero_linea,copia_linea, sin_error); 
            } 
            else if (strcmp(token_operacion, "ADD") == 0) 
            { 
                *registro_corres = add(*registro_corres, valor_numerico); 
                tabla(numero_linea,copia_linea, sin_error); 
            } 
            else if (strcmp(token_operacion, "SUB") == 0) 
            { 
                *registro_corres = sub(*registro_corres, valor_numerico); 
                tabla(numero_linea, copia_linea, sin_error); 
            } 
            else if (strcmp(token_operacion, "MUL") == 0) 
            { 
                *registro_corres = mul(*registro_corres, valor_numerico); 
                tabla(numero_linea,copia_linea, sin_error); 
            } 
            else if (strcmp(token_operacion, "DIV") == 0) 
            { 
 
                if (valor_numerico != 0) 
                { 
                    *registro_corres = divi(*registro_corres, valor_numerico); 
                    tabla(numero_linea, copia_linea, sin_error); 
                } 
                else 
                { 
                    char error_divi[40] = "No se puede dividir entre cero"; 
                    tabla(numero_linea, copia_linea, error_divi); 
 
                } 
                //tabla(copia_linea, sin_error); 
            } 
        } 
    } 
    fclose(archivo); 
    reinciar_registros();
    move(1, 0); // para que no se quede el encabezado
    clrtoeol();
    refresh();

    
} 
