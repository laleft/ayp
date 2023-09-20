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
#include <string.h>
#include <time.h>

#include "config/colors.c"
#include "config/settings.c"
#include "lib/check_not_equal_numbers.c"
#include "lib/print_breakline.c"

int debug = 0; // variable global para activar modo debug


int main(int argc, char *argv[]) {
    /* Modo debug */
    if(argc >= 2) {
        if(! strcmp(argv[1],"debug")) {
            debug = 1;
        }
    }

    /* InicializaciOn */
    setlocale(LC_ALL, ""); // No sé si funciona
    char munero[4]; // nUmero a adivinar
    int f_random = 1;    // flag numero random (toma valor true cuando el nUmero sea random)
    srand(time(NULL)); // usa el reloj como semilla
    

    /* PresentaciOn */
    printf("%s%s%s%s\n", "Bienvenido a ", COLOR_CYAN, "MUNERO", COLOR_RESET ", un juego en el que deberAs adivinar un nUmero de 4 cifras que elegirE al azar");
    printf("%s", COLOR_YELLOW);
    printBreakline(2);
    // system("pause");
    printf("%s", COLOR_RESET);
    printf("Generando nUmero aleatorio...\n");

    /* Busca un nUmero de 4 cifras aleatoreas no repetidas */
    while(f_random == 1) {
        int random_1 = rand() % 10;
        int random_2 = rand() % 10;
        int random_3 = rand() % 10;
        int random_4 = rand() % 10;
        sprintf(munero, "%d%d%d%d", random_1, random_2, random_3, random_4);
        if (debug) printf("El numero es %s\n", munero);
        f_random = checkNotEqualNumbers(munero, 0);
    }
    
    return 0;
}