#include <stdio.h>
/*
 * Solicita seleccionar el juego
 *
 * DescripciOn:
 * FunciOn para solicitar que el usuario ingrese el nUmero de juego
 * que quiere jugar.
 *
 * ParAmetros:
 * - no recibe argumentos
 *
 * Retorna:
 *  - int game: nUmero de juego
 *
 */

int selectGame()
{
    // Lista de juegos
    printf("SELECCIONA UN JUEGO:\n\n");
    printf("    1) MUNERO\n");
    printf("    2) AHORCADO\n");
    printf("    3) SALIR\n\n");
    printf("OPCION: ");

    int game;
    do
    {
        scanf("%d", &game);

        while (getchar() != '\n')
            ;
        if (game < 1 || game > 3)
        {
            ERR("OPCION NO VALIDA! POR FAVOR, SELECCIONA UN JUEGO DE LA LISTA.\n");
        }

    } while (game < 1 || game > 3);

    return game;
}
