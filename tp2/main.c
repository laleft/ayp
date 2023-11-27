#include <stdio.h>
#include <windows.h>
#include "config/const.c"
#include "modules/prompt_for_name.c"
#include "modules/welcome.c"
#include "games/munero.c"
#include "games/ahorcado.c"
#include "modules/select_game.c"

int debug = 0; // variable global para activar modo debug

int main(int argc, char *argv[])
{
    if (argc >= 2)
    {
        if (!strcmp(argv[1], "debug"))
        {
            debug = 1;
        }
    }

    int selected_game;
    char *user_name = NULL;

    // Ejecutar el programa hasta que se seleccione la opciOn 3
    do
    {
        RST; // Resetea el color de la consola
        if (!debug)
            CLS; // Limpia la pantalla

        // Dibuja la presentaciOn
        YLW;
        printBox("<<<<<< AYP GAMES 0.1 >>>>>>\n(sdebernardez)", -1, '#');
        RST;
        BR(2);

        // Chequea si ya se ingresO un nombre de usuario
        if (!user_name)
        {
            // Si no hay nombre de usuario se solicita
            // y se dibuja una bienvenida
            user_name = welcome();
        }
        else
        {
            printf("ESTA JUGANDO: %s\n\n", user_name);
        }

        // Seleccionar opciOn
        selected_game = selectGame();

        switch (selected_game)
        {
        case 1:
            munero();
            break;

        case 2:
            ahorcado();
            break;
        case 3:
            return 0;
            break;
        };
    } while (selected_game != 3);
}