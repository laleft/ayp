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
#include "lib/helpers.c"

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
    int f_random = 0;      // flag numero random (toma valor true cuando el nUmero sea random)
    srand(time(NULL));     // usa el reloj como semilla
    char name[50];

    /* PresentaciOn */
    if (debug == 0)
    {
        // system("cls"); // solo para Windows
    }
    printf("%s", COLOR_YELLOW);
    printf("\n%s%s%s%s", "BIENVENIDO A ", COLOR_CYAN, "MUNERO", COLOR_YELLOW ", UN JUEGO EN EL QUE DEBERAS ADIVINAR UN NUMERO DE 4 CIFRAS QUE ELEGIRE AL AZAR");
    printBreakline(2);
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
    printf("INGRESA TU NOMBRE: ");
    fgets(name, sizeof(name), stdin);
    printBreakline(1);
    printf(">>> HOLA, %s", name);
    printBreakline(1);
    printf("GENERANDO NUMERO ALEATORIO...\n");
    printBreakline(1);

    /* Busca un nUmero de 4 cifras aleatoreas no repetidas */
    while (f_random == 0)
    {
        int random_1 = rand() % 10;
        int random_2 = rand() % 10;
        int random_3 = rand() % 10;
        int random_4 = rand() % 10;
        sprintf(munero, "%d%d%d%d", random_1, random_2, random_3, random_4);
        if (debug)
            printf("\nNumero %s\n", munero);
        f_random = checkNotEqualNumbers(munero, 0);
    }
    printf("NUMERO GENERADO: ****\n");
    printBreakline(1);

    /* Variables del loop */
    char input[5];
    int i;
    int attempts = 0;
    int success = 0;
    /* Mientras no supere los intentos y no adivine el numero */
    while (attempts < MAX_ATTEMPTS && success != 1)
    {
        printf("INGRESA 4 DIGITOS DIFERENTES: ");
        if (fgets(input, sizeof(input), stdin))
        {
            fflush(stdin); // Limpia el buffer del standard input

            /* Si el usuario ingresa "fin" sale del programa*/
            if (strcmp(strupr(input), "FIN\n") == 0)
            {
                printBreakline(2);
                printf("*** HASTA LA PROXIMA! ***");
                printBreakline(2);
                exit(0);
            }

            if (1 == sscanf(input, "%d", &i))
            {
                if (sizeof(input) < 4)
                {
                    printf(">>> DEBE INGRESAR 4 DIGITOS!\n");
                    continue;
                }
                if (checkNotEqualNumbers(input, 0) == 0)
                {
                    printError(">>> LOS DIGITOS NO PUEDEN REPETIRSE!\n");
                }
                else
                {
                    printf("2 BIEN 1 REGULAR\n");
                    attempts++;
                    printf("INTENTO: %d\n", attempts);
                }
            }
            else
            {
                printError(">>> SOLO DEBE INGRESAR DIGITOS!\n");
            }
        }
    }

    printBreakline(2);
    printf("*** EL NUMERO ERA: %s ***", munero);
    printBreakline(2);
    printf("MAS SUERTE LA PROXIMA VEZ!\n");

    return 0;
}