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
    setlocale(LC_ALL, ""); // No s� si funciona
    char munero[4]; // nUmero a adivinar
    int f_random = 1;    // flag numero random (toma valor true cuando el nUmero sea random)
    srand(time(NULL)); // usa el reloj como semilla
    

    /* PresentaciOn */
    system("cls"); // solo para Windows
    printf("%s", COLOR_YELLOW);
    printf("\n%s%s%s%s", "BIENVENIDO A ", COLOR_CYAN, "MUNERO", COLOR_YELLOW ", UN JUEGO EN EL QUE DEBERAS ADIVINAR UN NUMERO DE 4 CIFRAS QUE ELEGIRE AL AZAR");
    printBreakline(2);
    printf("%s", COLOR_RESET);
    
    int c;
    FILE *file;
    file = fopen("intro.txt", "r");
    if (file) {
        while ((c = getc(file)) != EOF)
            putchar(c);
        fclose(file);
    }
    system("pause");
    
    printf("GENERANDO NUMERO ALEATORIO...\n");

    

    /* Busca un nUmero de 4 cifras aleatoreas no repetidas */
    while(f_random == 1) {
        int random_1 = rand() % 10;
        int random_2 = rand() % 10;
        int random_3 = rand() % 10;
        int random_4 = rand() % 10;
        sprintf(munero, "%d%d%d%d", random_1, random_2, random_3, random_4);
        if (debug) printf("\nNumero %s\n", munero);
        f_random = checkNotEqualNumbers(munero, 0);
    }
    
    return 0;
}