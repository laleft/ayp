#include <stdio.h>
#include "../utils/helpers.c"
#include "../utils/print_box.c"

/*
 * Arranque de la aplicaciOn
 *
 * DescripciOn:
 * FunciOn para mostrar la presentaciOn, solicitar nombre de usuario
 *
 * ParAmetros:
 * - no recibe argumentos
 *
 * Retorna:
 *  - sin valor de retorno (void)
 *
 */
void launch()
{
    printBox("A ver, a ver mas despacio cerebrito", 10, '*');
    BR(1);
    printf("SELECCIONE UN JUEGO\n");
}