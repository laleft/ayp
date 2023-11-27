#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ENTRIES 10
#define DATAFILE "data/ranking.dat"
typedef struct
{
    char name[50];
    int score;
} RankingEntry;

int compareEntries(const void *a, const void *b)
{
    return ((RankingEntry *)a)->score - ((RankingEntry *)b)->score;
}

RankingEntry createEntry(char *name, int score)
{
    RankingEntry newEntry;
    strcpy(newEntry.name, name);
    newEntry.score = score;
    return newEntry;
}

void saveToFile(const char *file_name, RankingEntry *list, int num_entries)
{
    FILE *file = fopen(file_name, "wb");
    if (file == NULL)
    {
        perror("Error abriendo el archivo para escritura.");
        exit(EXIT_FAILURE);
    }
    RankingEntry data;
    printf("ESCRIBIENDO...\n");
    fwrite(list, sizeof(data), num_entries, file);

    fclose(file);
}

void loadFromFile(const char *file_name, RankingEntry **list, int *num_entries)
{
    FILE *file = fopen(file_name, "rb");
    if (file == NULL)
    {
        perror("Error abriendo el archivo para lectura.");
        exit(EXIT_FAILURE);
    }

    RankingEntry data;

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    *num_entries = file_size / sizeof(data);

    *list = (RankingEntry *)malloc(file_size);

    rewind(file);
    printf("LEYENDO...\n");
    fread(*list, sizeof(data), *num_entries, file);

    fclose(file);
}

void printAlignedEntry(const char *name, int score)
{
    printf("%-50s %d\n", name, score);
}

int ranking(char *name, int score)
{
    // Load the list from the binary file
    RankingEntry *ranking;
    int num_entries;
    loadFromFile(DATAFILE, &ranking, &num_entries);

    printf("ENTRADAS: %d", num_entries);

    if (score > 0)
    {
        RankingEntry newEntry = createEntry(name, score);

        // Add the new entry if it's among the top 10
        int insertIndex = num_entries;
        for (int i = 0; i < num_entries; i++)
        {
            printf("New Entry Score: %d - Ranking Score: %d", newEntry.score, ranking[i].score);
            if (newEntry.score > ranking[i].score)
            {
                insertIndex = i;
                break;
            }
        }

        if (insertIndex < MAX_ENTRIES)
        {
            // Shift entries to make room for the new entry
            for (int i = num_entries - 1; i > insertIndex; i--)
            {
                ranking[i] = ranking[i - 1];
            }

            // Insert the new entry
            ranking[insertIndex] = newEntry;

            // Update the number of entries
            num_entries = (num_entries < MAX_ENTRIES) ? (num_entries + 1) : MAX_ENTRIES;

            // Sort the updated list
            qsort(ranking, num_entries, sizeof(RankingEntry), compareEntries);

            // Save the updated list to the file
            saveToFile(DATAFILE, ranking, num_entries);
            printf("\nThe new entry has been added to the ranking.\n");
        }
        else
        {
            printf("\nThe new entry did not make it to the top 10.\n");
        }
    }

    // Display the current ranking
    printf("\nRANKING DE USUARIOS:\n");
    for (int i = 0; i < num_entries; i++)
    {
        printAlignedEntry(ranking[i].name, ranking[i].score);
    }

    // Free the memory used by the list
    free(ranking);

    printf("PRESIONA [ENTER] PARA VOLVER AL MENU PRINCIPAL...");
    while (getchar() != '\n')
        ;
    getchar();

    return 0;
}
