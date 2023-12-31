/*
 * filename: main.c
 *
 * author: sdebernardez
 * version: 0.1.15
 *
 */

#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "config/colors.c"
#include "config/settings.c"
#include "lib/helpers.c"
#include "lib/check_not_equal_numbers.c"
#include "lib/check_all_are_digits.c"
#include "munero.c"

/*
Macros:

BR  -> imprime saltos de lInea
YLW -> cambia a color amarillo
CYN -> cambia a color cyan
RPT -> repite un caracter
RST -> resetea color
ERR -> muestra un mensaje de error (rojo)

*/

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

    setlocale(LC_ALL, ""); // No sE si funciona
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

    /* Muestra instrucciones */
    int t;
    FILE *file;
    file = fopen("intro.txt", "r");
    if (file)
    {
        while ((t = getc(file)) != EOF)
            putchar(t);
        fclose(file);
    }

    /* Solicita nombre de usuario (o anOnimo) */
    printf("INGRESA TU NOMBRE: ");
    fgets(name, sizeof(name), stdin);
    if (strcmp(name, "\n") == 0)
        strcpy(name, "Anonymus\n");
    BR(1);
    printf(">>> HOLA, %s", name);
    BR(1);

    /* Inicia el juego */
    int play = 1;
    do // Se ejecuta el juego mientras play sea true
    {
        /* Inicia la partida */
        game();

        /* Menu de opciones */
        char ch;
        do // Se ejecuta mientras no se ingresen las opciones correctas
        {
            while ((ch = getchar()) != '\n' && ch != EOF)
                continue;
            printf("JUGAR OTRA VEZ? (S)I/(N)O: ");
            ch = getchar();
            if (ch == 'N' || ch == 'n')
            {
                play = 0;
            }

        } while (ch != 'S' && ch != 's' && ch != 'N' && ch != 'n');

    } while (play);

    BR(2);
    printf("*** HASTA LA PROXIMA! ***");
    BR(2);

    return 0;
}