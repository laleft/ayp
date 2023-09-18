/*
* filename: munero.c
* 
* author: sdebernardez
* version: 0.0.1
*
*/

#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>

#include "config/colors.c"
#include "config/settings.c"
#include "lib/print_breakline.c"

int main(void) {
    system("cls");
    setlocale(LC_ALL, "");  

    printf("%s%s%s%s\n", "Bienvenido a ", COLOR_CYAN, "MUNERO", COLOR_RESET ", un juego en el que deberás adivinar un número de 4 cifras que elegiré al azar");
    printf("%s", COLOR_YELLOW);
    printBreakline(2);
    // system("pause");
    printf("%s", COLOR_RESET);

    char munero[4]; // número a adivinar
    int random;    // numero random
    int completado = 0; // contador
    time_t reloj; // semilla para rand()
    srand((unsigned) (&reloj));

    random = rand() % 10;
    for(int x = 0; x < 100; x++) {
        printf("%d ", rand() % 10);
    }
    
    while(completado < 4) {
        printf("%d", random);
        munero[completado] = random;
        completado++;
    }
    
    printf("El numero es ");
    for(int i = 0; i < 4; i++) {
        printf("%d", munero[i]);
    }
    return 0;
}