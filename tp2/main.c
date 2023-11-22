#include <stdio.h>
#include "config/const.c"
#include "utils/prompt_for_name.c"
#include "fragments/launch.c"

int main()
{

    launch(); // Arranque del programa.

    // Solictar nombre de usuario
    char user_name[MAX_USERNAME_LENGTH];
    promptForName(user_name, MAX_USERNAME_LENGTH);

    printf("Bienvenid@, %s!", user_name);

    return 0;
}