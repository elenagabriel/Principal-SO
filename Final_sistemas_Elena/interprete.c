#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>
#include "interprete.h"
#include "operaciones.h"
#include <ctype.h>

int proceso_id = -1;
char nombre_archivo_actual[50] = "";
/// validar si una cadena es un número entero válido

int validacion_numerica(const char *str)
{
    if (str == NULL || *str == '\0')
    {             // si la cadena es nula o vacia
        return 0; // Cadena vacía
    }

    // si es negativo
    int i = 0;
    if (str[0] == '-')
    {                       // si el primer caracter es un signo negativo
        i = 1;              // empieza a verificar desde el siguiente caracter
        if (str[1] == '\0') // si solo hay un signo negativo

            return 0; // No es un número válido
    }

    // Verificar que todos los caracteres sean dígitos
    for (; str[i] != '\0'; i++)
    {
        if (!isdigit(str[i]))
        {             // si no es digito
            return 0; // No es un número válido
        }
    }
    return 1;
}

int validar_extension(const char *nombre){
    char *punto = strrchr(nombre, '.'); // busca el último '.'
    if (punto != NULL && strcmp(punto, ".asm") == 0)
    {
        return 1; // válido
    }
    return 0; // inválido
}

int interprete(char texto[100])
{
    char *delimitador = " \n";
    char *token;
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
            // Recorremos todos los archivos después de "ejecutar"
            token = strtok(NULL, delimitador);

            while (token != NULL)
            {
                if (validar_extension(token))
                {
                    mvprintw(1, 0, "Archivo válido: %s\n", token);
                    refresh();
                    sleep(2);
                    //move(1, 0);
                    //clrtoeol();
                    //refresh();

                    comando_valido = 1;

                    strcpy(nombre_archivo, token);
                    proceso_id++;
                    strcpy(nombre_archivo_actual, nombre_archivo);

                    // Se procesa el archivo completo hasta END o cuando ya o hay nada en el archivo
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

                // Pasar al siguiente archivo
                token = strtok(NULL, delimitador);
            }

            if (!comando_valido)
            {
                mvprintw(1, 0, "Instrucción no válida\n");
                refresh();
                sleep(2);
                move(1, 0);
                clrtoeol();
                refresh();
            }
        }
    }
    return bandera;
}

void validar_archivo(char *nombre_archivo)
{
    // encabezado

    mvprintw(1, 0, "%-5s %-5s %-8s %-8s %-8s %-10s %-10s %-20s %-50s",
             "ID", "PC", "Ax", "Bx", "Cx", "Dx",
             "Proceso", "IR", "Status");
    refresh();
    // move(1, 0);
    clrtoeol();
    refresh();
    FILE *archivo = fopen(nombre_archivo, "r");

    char linea[20];
    char copia_linea[20];
    char sin_error[60] = "Correcto";

    // Mostrar registros en 0 antes de procesar instrucciones
    char vacio[9] = "";
    char snerror[40] = "";
    tabla(1, vacio, snerror);

    int numero_linea = 1;
    int hay_error = 0;
    int linea_correcta = 0; // contador de lineas
    int linea_incorrecta = 0;
    int end = 0; // bandera para saber si ya se llego al final del archivo

    while (fgets(linea, sizeof(linea), archivo) && !end)
    {
        numero_linea++;

        // eliminar salto de línea al final
        linea[strcspn(linea, "\n")] = '\0';
        strcpy(copia_linea, linea);

        // primer token = operación
        char *token_operacion = strtok(linea, "  ");

        if (!token_operacion)
            continue;

        if (strcmp(token_operacion, "END") == 0)
        { // si es END, termina el proceso

            end = 1; // bandera de fin
            char error_end[60] = "proceso finalizado";
            hay_error = 0;
            tabla(numero_linea, copia_linea, error_end);
            continue;
        }

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
            char error_a[60] = "Operación desconocida";
            hay_error = 1;
            tabla(numero_linea, copia_linea, error_a);
            linea_incorrecta = 1;
            continue;
        }

        // siguiente token = registro + posible valor
        char *segundo_parte_en_linea = strtok(NULL, ""); // esto avanza en token 2
        if (!segundo_parte_en_linea)
        {
            if (es_tipo_1)
            {
                char error_b[60] = "Falta el registro y valor";
                hay_error = 2;
                tabla(numero_linea, copia_linea, error_b);
                linea_incorrecta = 1;
                continue;
            }
            else if (es_tipo_2)
            {
                char error_b[60] = "Falta el registro";
                hay_error = 2;
                tabla(numero_linea, copia_linea, error_b);
                linea_incorrecta = 1;
                continue;
            }
        }

        int *registro_corres;

        if (es_tipo_2)
        {
            char *extra = strpbrk(segundo_parte_en_linea, " ,"); // busca coma o espacio
            if (extra)
            {
                *extra = '\0'; // aquí cortamos la cadena, ahora "segundo_parte_en_linea" queda solo con el registro
                extra++;       // avanzamos para ver qué había después
            }

            char *registro = segundo_parte_en_linea; // ahora sí apunta solo a "Ax"

            if (extra != NULL)
            { //

                if (!(strcmp(registro, "Ax") == 0 || strcmp(registro, "Bx") == 0 || strcmp(registro, "Cx") == 0 || strcmp(registro, "Dx") == 0))
                { // si no es un registro valido y el valor no es numerico

                    char error_com[60] = "Registro inválido y demasiados argumentos";

                    tabla(numero_linea, copia_linea, error_com);
                    linea_incorrecta = 1;
                    continue;
                }
                else if ((strcmp(registro, "Ax") == 0 || strcmp(registro, "Bx") == 0 || strcmp(registro, "Cx") == 0 || strcmp(registro, "Dx") == 0))
                {
                    char error_f[60] = "Demasiados argumentos";
                    hay_error = 6;
                    tabla(numero_linea, copia_linea, error_f);
                    linea_incorrecta = 1;
                    continue;
                }
            }
            else
            {

                if (!(strcmp(registro, "Ax") == 0 || strcmp(registro, "Bx") == 0 || strcmp(registro, "Cx") == 0 || strcmp(registro, "Dx") == 0))
                {
                    // error e
                    char error_e[60] = "Registro inválido";
                    hay_error = 5;
                    tabla(numero_linea, copia_linea, error_e);
                    linea_incorrecta = 1;
                    continue;
                }
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
                char error_d[60] = "Falta coma entre registro y valor";
                hay_error = 4;
                tabla(numero_linea, copia_linea, error_d);

                linea_incorrecta = 1;
                continue;
            }

            *coma = '\0';                            // ya parto ese token en dos, si hay coma lo separo en registro y valor
            char *registro = segundo_parte_en_linea; // apunta al registro
            char *valor = coma + 1;                  // avanza enla coma que ahora es \0 y apunta a valor

            if (!(strcmp(registro, "Ax") == 0 || strcmp(registro, "Bx") == 0 || strcmp(registro, "Cx") == 0 || strcmp(registro, "Dx") == 0) && !validacion_numerica(valor))
            { // si no es un registro valido y el valor no es numerico

                char error_com[60] = "Registro inválido y valor numérico inválido";

                tabla(numero_linea, copia_linea, error_com);
                linea_incorrecta = 1;
                continue;
            }

            if (!validacion_numerica(valor))
            { //
                char error_f[60] = "Valor numérico inválido";
                hay_error = 6;
                tabla(numero_linea, copia_linea, error_f);
                linea_incorrecta = 1;
                continue;
            }

            int valor_numerico = atoi(valor);

            if (!(strcmp(registro, "Ax") == 0 || strcmp(registro, "Bx") == 0 || strcmp(registro, "Cx") == 0 || strcmp(registro, "Dx") == 0))
            {
                // error e
                char error_e[60] = "Registro inválido";
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
                tabla(numero_linea, copia_linea, sin_error);
            }
            else if (strcmp(token_operacion, "ADD") == 0)
            {
                *registro_corres = add(*registro_corres, valor_numerico);
                tabla(numero_linea, copia_linea, sin_error);
            }
            else if (strcmp(token_operacion, "SUB") == 0)
            {
                *registro_corres = sub(*registro_corres, valor_numerico);
                tabla(numero_linea, copia_linea, sin_error);
            }
            else if (strcmp(token_operacion, "MUL") == 0)
            {
                *registro_corres = mul(*registro_corres, valor_numerico);
                tabla(numero_linea, copia_linea, sin_error);
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
                    char error_divi[60] = "error. No se puede dividir entre cero";
                    tabla(numero_linea, copia_linea, error_divi);
                }
                // tabla(copia_linea, sin_error);
            }
        }
    }
    fclose(archivo);
    reinciar_registros();
    move(1, 0); // para que no se quede el encabezado
    clrtoeol();
    refresh();


}
