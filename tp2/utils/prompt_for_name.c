#include <stdio.h>
#include <string.h>
/*
 * Solicita nombre de usuario
 *
 * DescripciOn:
 * FunciOn para solicitar el ingreso por teclado del nombre de usuario
 *
 * ParAmetros:
 * - input: puntero de tipo char donde se almacenarA el nombre de usuario
 * - max_username_length: logitud mAxima de la cadena a almacenar
 *
 * Retorna:
 *  - sin valor de retorno (void)
 *
 */
void promptForName(char *input, int max_username_lenth)
{
    /* Solicita nombre de usuario (o anOnimo) */
    printf("INGRESA TU NOMBRE: ");
    fgets(input, max_username_lenth, stdin);
    if (strcmp(input, "\n") == 0)
        strcpy(input, "Anonymus\n");

    input[strcspn(input, "\n")] = 0; // Elimina el salto de lInea al final
}