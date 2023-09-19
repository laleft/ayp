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
    if(strlen(numbers) == start_at) {
        return 0;
    }
    int flag = 0;
    for(int i = start_at; i < strlen(numbers) - 1; i++) {
        printf("Arranca en %d\n", start_at);
        printf("%c - %c ", numbers[start_at], numbers[i + 1]);
        if(numbers[start_at] == numbers[i + 1]) {
            printf("Son iguales\n");
            flag = 1;
            break;
        } 
    }
    if(flag == 1) {
        return flag;
    } else {
        flag = checkNotEqualNumbers(numbers, start_at + 1);
    }
    return flag;
}

int main(void) {
    setlocale(LC_ALL, "");  

    printf("%s%s%s%s\n", "Bienvenido a ", COLOR_CYAN, "MUNERO", COLOR_RESET ", un juego en el que deber�s adivinar un n�mero de 4 cifras que elegir� al azar");
    printf("%s", COLOR_YELLOW);
    printBreakline(2);
    // system("pause");
    printf("%s", COLOR_RESET);

    char munero[4]; // n�mero a adivinar
    int f_random = 1;    // flag numero random

    srand(time(NULL)); // usa el reloj como semilla
    
    while(f_random == 1) {
        int random_1 = rand() % 10;
        int random_2 = rand() % 10;
        int random_3 = rand() % 10;
        int random_4 = rand() % 10;
        sprintf(munero, "%d%d%d%d", random_1, random_2, random_3, random_4);
        f_random = checkNotEqualNumbers(munero, 0);
        printf("Valor del flag: %d\n", f_random);
        // f_random = 0;
    }
    
    printf("El numero es %s", munero);
    return 0;
}