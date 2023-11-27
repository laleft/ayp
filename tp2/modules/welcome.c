#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../utils/helpers.c"
#include "../utils/print_box.c"
#include "../config/const.c"
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
 *  - user_name: puntero a char con el nombre de usuario ingresado
 *
 */
extern int debug;

char *welcome()
{
    // Solictar nombre de usuario
    char *user_name = malloc(MAX_USERNAME_LENGTH * sizeof(char));
    promptForName(user_name, MAX_USERNAME_LENGTH);

    // Variable temporal para concatenar con el mensaje de bienvenida
    // Usar la variable original la destruirIa con strcat
    char tmp[MAX_INPUT_LENGTH];
    strcpy(tmp, user_name);

    // Saludo de bienvenida
    // Se concatena para pasarla como argumento a printBox
    char greetings[] = "Bienvenid@, ";
    strcat(greetings, tmp);
    strcat(greetings, "!");

    BR(1);
    CYN;
    printBox(greetings, strlen(greetings) + 30, '*');
    RST;
    BR(2);

    return user_name;
}