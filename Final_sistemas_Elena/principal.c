// COMPILAR: gcc -o programa principal.c interprete.c operaciones.c
// EJECUTAR: ./programa
// y teclear en la terminal ejecutar a.asm
#include <stdio.h>
#include <string.h>
#include <ncurses.h>
#include <unistd.h>

#include "interprete.h"
#include "operaciones.h"

int main() {
    
    WINDOW *window = NULL;  // inicializa y obtiene la ventana principal
    window = initscr();

    char texto[50];
    char copia_texto[50];
    int bandera = 0; 

    do {
        mvprintw(0, 0, "$ ");
        clrtoeol();             // limpia hasta el final de la línea
        refresh(); 
        getstr(texto);
        //fgets(texto, sizeof(texto), stdin);
        strcpy(copia_texto, texto);

        bandera = interprete(copia_texto);

        
    } while(bandera == 0);

        endwin();
}