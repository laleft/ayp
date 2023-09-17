/*
* filename: munero.c
* 
* author: sdebernardez
* version: 0.0.1
*
*/

#include <stdio.h>

#include "config/colors.c"
#include "config/settings.c"
#include "lib/print_breakline.c"

int main(void) {
    system("cls");

    char cadena[MAX_INPUT_LENGTH];
    printf("%s%s%s%s", "Bienvenido a ", COLOR_CYAN, "MUNERO", COLOR_RESET ", un juego en el que deberás adivinar un número de 4 cifras que elegiré al azar\n");
    printf("%s", COLOR_YELLOW);
    printBreakline(2);
    system("pause");
    printf("%s", COLOR_RESET);
    return 0;
}