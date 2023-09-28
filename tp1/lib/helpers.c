#include "../config/colors.c"

void printError(char *message)
{
    printf(COLOR_RED);
    printf("%s", message);
    printf(COLOR_RESET);
}