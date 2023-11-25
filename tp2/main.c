#include <stdio.h>
#include <windows.h>
#include "config/const.c"
#include "utils/prompt_for_name.c"
#include "modules/launch.c"
#include "games/munero.c"
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

    char *user_name = launch(); // Arranque del programa.

    int selected_game = selectGame();

    switch (selected_game)
    {
    case 1:
        munero();
        break;

    default:
        break;
    }

    return 0;
}