#include <ctype.h>

extern int debug; // variable global

int checkAllAreDigits(char *numbers, int size)
{
    for (int z = 0; z < sizeof(numbers - 1); z++)
    {
        if (0 == isdigit(numbers[z]))
        {
            if (debug == 1)
                printf("%c NO ES DIGITO\n", numbers[z]);
            return 0;
        }
    }
    return 1;
}