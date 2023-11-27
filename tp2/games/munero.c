#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../config/const.c"
#include "../utils/helpers.c"
#include "../lib/check_all_are_digits.c"
#include "../lib/check_not_equal_numbers.c"
#include "../lib/print_txt_file.c"
extern int debug;

int munero()
{
    CLS;
    printBox("BIENVENIDO A MUNERO!", -1, '*');
    printTxtFile("help/munero.txt");

    char munero[4];    // nUmero a adivinar
    int f_random = 0;  // flag (toma valor true cuando el nUmero sea random)
    srand(time(NULL)); // usa el reloj como semilla

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
    CYN;
    printf("NUMERO GENERADO: ");
    if (debug)
        printf("%s", munero);
    else
        printf("****");
    RST;
    BR(2);

    char input[5]; // input de usuario
    int i;
    int attempts = 0; // contador de intentos
    time_t start_time, end_time;

    time(&start_time); // toma el tiempo de inicio de la ronda
    while (attempts < MAX_ATTEMPTS)
    {
        fflush(stdin); // vacIa el buffer

        printf("INGRESA 4 DIGITOS: ");
        if (fgets(input, sizeof(input), stdin))
        {
            /* Si el usuario ingresa "fin" sale del programa */
            if (strcmp(strupr(input), "FIN\n") == 0)
            {
                BR(2);
                printf("*** HASTA LA PROXIMA! ***");
                BR(2);
                exit(0); // sale del programa
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
                    attempts++;
                    int wrong = 4;
                    int right = 0;
                    int regular = 0;
                    for (int x = 0; x < sizeof(input - 1); x++) // recorre el input
                    {
                        for (int y = 0; y < sizeof(munero - 1); y++) // recorre el numero aleatorio
                        {
                            if (input[x] == munero[y]) // coicide el nUmero
                            {
                                if (debug)
                                    printf("[DEBUG] POSICION COINCIDENCIAS [%d, %d](%c = %c)\n", x, y, input[x], munero[y]);
                                if (x == y) // coincide la posiciOn
                                {
                                    right++; // +1 bien
                                }
                                else
                                {
                                    regular++; // +1 regular
                                }
                            }
                        }
                    }
                    wrong -= (right + regular); // calcula los dIgitos incorrectos
                    printf(">>> ");
                    if (wrong == 4)
                    {
                        printf("%sTODOS MAL!%s", COLOR_CYAN, COLOR_RESET);
                    }
                    else if (right == 4)
                    {
                        /* Calcula el intervalo de tiempo */
                        time(&end_time);
                        double total_time_in_seconds = difftime(end_time, start_time);
                        int minutes = total_time_in_seconds / 60;
                        int seconds = (int)total_time_in_seconds % 60;

                        printf("%sBIEN!!! ACERTASTE EL NUMERO EN %d INTENTOS EN %d MINUTOS Y %d SEGUNDOS %s", COLOR_GREEN, attempts, minutes, seconds, COLOR_RESET);
                        BR(2);
                        return 1;
                    }
                    else
                    {
                        if (right > 0)
                            printf("%s%d BIEN%s ", COLOR_GREEN, right, COLOR_RESET);
                        if (regular > 0)
                            printf("%s%d REGULAR%s", COLOR_YELLOW, regular, COLOR_RESET);
                    }
                    BR(1);

                    if (debug)
                        printf("[DEBUG] INTENTO: %d\n", attempts);
                }
            }
            else // Si no son dIgitos
            {
                ERR(">>> DEBES INGRESAR 4 DIGITOS!\n");
            }
        }
    }
    BR(2);
    printf(">>> NO TENES MAS INTENTOS, EL NUMERO ERA: %s\n", munero);
    BR(2);
    printf(">>> MAS SUERTE LA PROXIMA VEZ!\n");
    BR(2);
    return 0;
}