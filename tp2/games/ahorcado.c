#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*
 * Juego El Ahorcado
 *
 * DescripciOn:
 * Funciones para ejecutar el juego
 *
 * - void ahorcado
 * - void loadDictionary
 * - int play
 *
 */

#include "../utils/helpers.c"
#include "ahorcado/drawHangman.c"

#define MAX_WORD_LENGTH 100
#define MAX_JUGADORES 10
#define ATTEMPTS 7

extern int debug;

// Carga la lista de palabras a adivinar
void loadDictionary(char *words[], int *totalWords)
{
    FILE *dictionary = fopen("games/ahorcado/dictionary.txt", "r");
    if (dictionary == NULL)
    {
        printf("No se pudo abrir el diccionario.\n");
        exit(1);
    }

    *totalWords = 0;
    char word[MAX_WORD_LENGTH];

    while (fgets(word, MAX_WORD_LENGTH, dictionary) != NULL)
    {
        word[strcspn(word, "\n")] = '\0'; // Eliminar el carácter de nueva línea
        words[*totalWords] = strdup(word);
        (*totalWords)++;
    }

    fclose(dictionary);
}

// Rutina del juego
int play(char *word)
{
    int attempts = ATTEMPTS;         // Contador de intentos
    int hits = 0;                    // Letras acertadas
    int word_length = strlen(word);  // Longitud de la palabra
    int correct_letter[word_length]; // Letras correctas
    char used_letters[26];           // Letras usadas (abecedario)
    int used_letters_number = 0;     // Contador de letras ya usadas
    int already_used = 0;            // para analizar si repitió una letra
    int win;                         // Flag juego ganado

    // Inicializa array de letras correctas
    for (int i = 0; i < word_length; i++)
    {
        correct_letter[i] = 0;
    }

    // Mitras no agote los intentos ni acierte
    while (attempts > 0 && hits < word_length)
    {
        BR(2);
        // Dibuja las letras acertas o un _
        for (int i = 0; i < word_length; i++)
        {
            if (correct_letter[i])
            {
                printf("%c ", word[i]);
            }
            else
            {
                printf("_ ");
            }
        }
        BR(2);

        // Entrada de usuario
        char letter;
        int hit = 0;
        printf("INGRESA UNA LETRA: ");
        scanf(" %c", &letter);

        // Redibuja el encabezado
        CLS;
        printBox("EL AHORCADO", -1, '*');
        printf("\n\n");

        // Analiza si la letra ya fue utilizada
        for (int i = 0; i <= used_letters_number; i++)
        {
            if (tolower(used_letters[i]) == tolower(letter))
            {
                ERR("YA USASTE ESA LETRA!");
                already_used = 1;
            }
        }

        // Si no está usada chequea si estA en la palabra
        if (!already_used)
        {
            for (int i = 0; i < word_length; i++)
            {
                if (!correct_letter[i] && tolower(word[i]) == tolower(letter))
                {
                    correct_letter[i] = 1;
                    hits++;
                    hit = 1;
                }
            }
        }

        // Muestra las letras ingresadas
        printf("LETRAS UTILIZADAS: ");
        YLW;
        if (!already_used)
        {
            used_letters[used_letters_number] = toupper(letter);
        }
        for (int i = 0; i <= used_letters_number; i++)
        {
            printf("%c ", used_letters[i]);
        }
        RST;
        BR(2);

        // Notifica acierto o no
        if (!already_used)
        {
            used_letters_number++;
            if (hit)
            {
                HIT("ESTA! ");
                printf("TE QUEDAN %d INTENTOS.", attempts);
            }
            else
            {
                attempts--;
                ERR("NO ESTA! ");
                printf("TE QUEDAN %d INTENTOS.", attempts);
            }
        }
        already_used = 0;
        BR(2);

        // Dibuja la horca
        drawHangman(attempts);
    }

    // Fuera del while evalUa el acierto
    if (hits == word_length)
    {
        BR(2);
        CYN;
        for (int i = 0; i < strlen(word); i++)
        {
            printf("%c ", word[i]);
        }
        RST;
        BR(2);
        HIT("GANASTE!!!!")
        BR(1);
        win = 1;
    }
    else
    {
        BR(1);
        ERR("PERDISTE :(");
        BR(2);
        printf("LA PALABRA ERA: ");
        CYN;
        for (int i = 0; i < strlen(word); i++)
        {
            printf("%c ", word[i]);
        }
        RST;
        win = 0;
    }
    // Retorna el flag
    return win;
}

int ahorcado()
{
    CLS;
    printBox("EL AHORCADO", -1, '*');

    // Carga del diccionario
    char *dictionary[MAX_WORD_LENGTH];
    int totalWords;
    loadDictionary(dictionary, &totalWords);

    // Selecciona una palabra al azar
    srand(time(NULL));
    char *word = dictionary[rand() % totalWords];

    // Inicia tiempo de la ronda
    time_t start_time, end_time;
    int option;
    time(&start_time); // toma el tiempo de inicio de la ronda

    // Inicia el juego
    int win = play(word);

    // Fin del tiempo de la ronda
    time(&end_time);
    double total_time_in_seconds = difftime(end_time, start_time);
    int minutes = total_time_in_seconds / 60;
    int seconds = (int)total_time_in_seconds % 60;

    // Si el usuario gana retorna el tiempo que le llevO
    // Si pierde retorna 0 para posterior evaluaciOn
    if (win == 1)
    {
        printf("\n%sTIEMPO TOTAL: %d MINUTOS Y %d SEGUNDOS %s", COLOR_GREEN, minutes, seconds, COLOR_RESET);
        return total_time_in_seconds;
    }
    else
    {

        return 0;
    }
}
