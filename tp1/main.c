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
#include "lib/print_breakline.c"


int checkNotEqualNumbers(char numbers[], int start_at) {
    for(int i = start_at; i < strlen(numbers) - 1; i++) {
        printf("%c - %c ", numbers[start_at], numbers[i + 1]);
        if(numbers[start_at] == numbers[i + 1]) {
            printf("Son iguales\n");
            return 0;
        } else {
            checkNotEqualNumbers(numbers, start_at + 1);
            printf("Son distintos\n");
            return 1;
        }
    }
}

int main(void) {
    setlocale(LC_ALL, "");  

    printf("%s%s%s%s\n", "Bienvenido a ", COLOR_CYAN, "MUNERO", COLOR_RESET ", un juego en el que deberás adivinar un número de 4 cifras que elegiré al azar");
    printf("%s", COLOR_YELLOW);
    printBreakline(2);
    // system("pause");
    printf("%s", COLOR_RESET);

    char munero[4]; // número a adivinar
    int f_random = 0;    // numero random

    srand(time(NULL)); // usa el reloj como semilla
    
    while(f_random == 0) {
        int random_1 = rand() % 10;
        int random_2 = rand() % 10;
        int random_3 = rand() % 10;
        int random_4 = rand() % 10;
        sprintf(munero, "%d%d%d%d", random_1, random_2, random_3, random_4);
        f_random = checkNotEqualNumbers(munero, 0);
        printf("%d", f_random);
    }
    
    printf("El numero es %s", munero);
    return 0;
}