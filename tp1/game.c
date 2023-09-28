#include <stdio.h>
#include "config/settings.c"
#include "lib/helpers.c"

extern int debug;

void game()
{
    char munero[4];   // nUmero a adivinar
    int f_random = 0; // flag (toma valor true cuando el nUmero sea random)
    srand(time(NULL));

    printf("GENERANDO NUMERO ALEATORIO...\n");
    BR(1);

    /* Busca un nUmero de 4 cifras aleatoreas no repetidas */
    while (f_random == 0)
    {
        /* RND en helpers.c => rand() % 10 */
        int random_1 = RND;
        int random_2 = RND;
        int random_3 = RND;
        int random_4 = RND;
        sprintf(munero, "%d%d%d%d", random_1, random_2, random_3, random_4);
        if (debug)
            printf("\n[DEBUG] NUMERO: %s\n", munero);
        f_random = checkNotEqualNumbers(munero, 0);
    }
    CYN
        printf("NUMERO GENERADO: ****\n");
    RST
        BR(1);
    /* Variables del loop */
    char input[5];
    int i;
    int attempts = 0;
    int success = 0;
    /* Mientras no supere los intentos y no adivine el numero */
    while (attempts < MAX_ATTEMPTS && success != 1)
    {
        printf("INGRESA 4 DIGITOS: ");
        if (fgets(input, sizeof(input), stdin))
        {
            fflush(stdin); // vacIa el buffer

            /* Si el usuario ingresa "fin" sale del programa */
            if (strcmp(strupr(input), "FIN\n") == 0)
            {
                BR(2);
                printf("*** HASTA LA PROXIMA! ***");
                BR(2);
                exit(0);
            }
            /* Chequea que los primeros 4 caracteres sean dIgitos */
            if (1 == sscanf(input, "%d", &i) && checkAllAreDigits(input, 4))
            {
                /* Chequea que no se repitan nUmeros */
                if (checkNotEqualNumbers(input, 0) == 0)
                {
                    ERR(">>> LOS DIGITOS NO PUEDEN REPETIRSE!\n");
                }
                else
                {
                    /* PasO las validaciones, chequea  los nUmeros */
                    int wrong = 4;
                    int right = 0;
                    int regular = 0;
                    for (int x = 0; x < sizeof(input - 1); x++)
                    {
                        for (int y = 0; y < sizeof(munero - 1); y++)
                        {
                            if (input[x] == munero[y])
                            {
                                if (debug)
                                    printf("[%d, %d](%c = %c)\n", x, y, input[x], munero[y]);
                                if (x == y)
                                {
                                    right++;
                                }
                                else
                                {
                                    regular++;
                                }
                            }
                        }
                    }
                    wrong -= (right + regular);
                    printf(">>> ");
                    if (wrong == 4)
                    {
                        printf("%sTODOS MAL!%s", COLOR_CYAN, COLOR_RESET);
                    }
                    else if (right == 4)
                    {
                        printf("%sBIEN!!! ACERTASTE EL NUMERO EN %d INTENTOS%s", COLOR_GREEN, attempts, COLOR_RESET);
                    }
                    else
                    {
                        if (right > 0)
                            printf("%s%d BIEN%s ", COLOR_GREEN, right, COLOR_RESET);
                        if (regular > 0)
                            printf("%s%d REGULAR%s", COLOR_YELLOW, regular, COLOR_RESET);
                    }
                    BR(1);
                    attempts++;
                    if (debug)
                        printf("INTENTO: %d\n", attempts);
                }
            }
            else
            {
                ERR(">>> DEBES INGRESAR 4 DIGITOS!\n");
            }
        }
    }

    BR(2);
    printf(">>> NO TENES MAS INTENTOS, EL NUMERO ERA: %s\n", munero);
    BR(2);
    printf(">>> MAS SUERTE LA PROXIMA VEZ!\n");
}