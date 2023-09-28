#include "check_not_equal_numbers.c"

extern int debug;

int *findRandomNumber()
{
    int f_random = 1; // Flag
    char number[4];
    while (f_random == 1)
    {
        int random_1 = rand() % 10;
        int random_2 = rand() % 10;
        int random_3 = rand() % 10;
        int random_4 = rand() % 10;
        sprintf(number, "%d%d%d%d", random_1, random_2, random_3, random_4);
        if (debug)
            printf("[DEBUG] EL NUMERO ES %s\n", number);
        f_random = checkNotEqualNumbers(number, 0);
    }
    return number;
}