
void validar_archivo(const char *nombre_archivo) {
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
            int *registro = segundo_parte_en_linea;
            int *valor = coma + 1; // avanza enla coma que ahora es \0 y apunta a valor

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