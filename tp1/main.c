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
#include <ctype.h>

#include "config/colors.c"
#include "config/settings.c"
#include "lib/check_not_equal_numbers.c"
#include "lib/check_all_are_digits.c"
#include "lib/helpers.c"
#include "game.c"

int debug = 0; // variable global para activar modo debug

int main(int argc, char *argv[])
{
    /* Modo debug */
    if (argc >= 2)
    {
        if (!strcmp(argv[1], "debug"))
        {
            debug = 1;
        }
    }

    /* InicializaciOn */
    setlocale(LC_ALL, ""); // No sE si funciona
    char munero[4];        // nUmero a adivinar
    int f_random = 0;      // flag (toma valor true cuando el nUmero sea random)
    srand(time(NULL));     // usa el reloj como semilla
    char name[50];         // nombre del usuario

    /* PresentaciOn */
    if (debug == 0)
    {
        system("cls"); // solo para Windows
    }
    YLW;
    RPT("*", 100);
    RST;
    BR(1);
    printf(" BIENVENIDO A ");
    printf("%sMUNERO%s", COLOR_CYAN_BOLD, COLOR_RESET);
    printf(", UN JUEGO EN EL QUE DEBERAS ADIVINAR UN NUMERO DE 4 CIFRAS QUE ELEGIRE AL AZAR \n");
    YLW;
    RPT("*", 100);
    RST;
    BR(2);
    printf("%s", COLOR_RESET);

    int t;
    FILE *file;
    file = fopen("intro.txt", "r");
    if (file)
    {
        while ((t = getc(file)) != EOF)
            putchar(t);
        fclose(file);
    }
    /* Fin presentaciOn */

    printf("INGRESA TU NOMBRE: ");
    fgets(name, sizeof(name), stdin);
    if (strcmp(name, "\n") == 0)
        strcpy(name, "Anonymus\n");
    BR(1);
    printf(">>> HOLA, %s", name);
    BR(1);

    int play = 1;
    do
    {
        game();
        char ch;
        while (ch != 'S' || ch != 'N')
        {
            printf("JUGAR OTRA VEZ? (S/N): ");
            ch = getchar();
            putchar(ch);
            printf("\n");
        }
        if (ch == 'N')
        {
            play = 0;
        }

    } while (play);

    return 0;
}