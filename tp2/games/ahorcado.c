#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../utils/helpers.c"
#include "ahorcado/drawHangman.c"

#define MAX_WORD_LENGTH 100
#define MAX_JUGADORES 10

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

int play(char *word)
{
    int attempts = 7;
    int hits = 0;
    int word_length = strlen(word);
    int correct_letter[word_length];
    char used_letters[26];
    int used_letters_number = 0;
    int already_used = 0; // para analizar si repitió una letra
    int win;

    for (int i = 0; i < word_length; i++)
    {
        correct_letter[i] = 0;
    }

    while (attempts > 0 && hits < word_length)
    {
        BR(2);
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

        char letter;
        int hit = 0;
        printf("INGRESA UNA LETRA: ");
        scanf(" %c", &letter);
        CLS;
        printBox("EL AHORCADO", -1, '*');

        // Analizo si la letra ya fue utilizada
        for (int i = 0; i <= used_letters_number; i++)
        {
            if (tolower(used_letters[i]) == tolower(letter))
            {
                ERR("YA USASTE ESA LETRA!");
                BR(1);
                // printf("TE QUEDAN %d INTENTOS.\n", attempts);
                already_used = 1;
            }
        }

        // si no está usada, analizo el acierto
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

        // muestro las letras en uso y adiciono la nueva letra, solamente si no fue utilizada
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

        if (!already_used)
        {
            used_letters_number++;
            if (hit)
            {
                HIT("ESTA!");
                printf("TE QUEDAN %d INTENTOS.", attempts);
            }
            else
            {
                attempts--;
                ERR("NO ESTA!");
                printf("TE QUEDAN %d INTENTOS.", attempts);
            }
        }
        already_used = 0;
        BR(2);
        drawHangman(attempts);
    }

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
    return win;
}

int ahorcado()
{
    CLS;
    printBox("EL AHORCADO", -1, '*');

    char *dictionary[MAX_WORD_LENGTH];
    int totalWords;
    loadDictionary(dictionary, &totalWords);

    srand(time(NULL));
    char *word = dictionary[rand() % totalWords];
    time_t start_time, end_time;
    int option;

    time(&start_time); // toma el tiempo de inicio de la ronda
    int win = play(word);
    time(&end_time);
    double total_time_in_seconds = difftime(end_time, start_time);
    int minutes = total_time_in_seconds / 60;
    int seconds = (int)total_time_in_seconds % 60;

    printf("\n%sTIEMPO TOTAL: %d MINUTOS Y %d SEGUNDOS %s", COLOR_GREEN, minutes, seconds, COLOR_RESET);

    if (win == 1)
        return total_time_in_seconds;
    else
        return 0;
}
