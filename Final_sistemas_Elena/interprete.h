#ifndef INTERPRETE_H
#define INTERPRETE_H
#include <string.h>
#include <stdio.h>

int interprete(char texto[100]);
void validar_archivo(char *nombre_archivo);
int validacion_numerica(const char *str);
int validar_extension(const char *nombre);

#endif