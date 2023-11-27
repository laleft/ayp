#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ENTRIES 10

typedef struct
{
    char name[50];
    int score;
} RankingEntry;

int compareEntries(const void *a, const void *b)
{
    return ((RankingEntry *)b)->score - ((RankingEntry *)a)->score;
}

RankingEntry createEntry()
{
    RankingEntry newEntry;
    printf("Enter the name: ");
    scanf("%s", newEntry.name);
    printf("Enter the score: ");
    scanf("%d", &newEntry.score);
    return newEntry;
}

void saveToFile(const char *fileName, RankingEntry *list, int numEntries)
{
    FILE *file = fopen(fileName, "wb");
    if (file == NULL)
    {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }

    fwrite(list, sizeof(RankingEntry), numEntries, file);

    fclose(file);
}

void loadFromFile(const char *fileName, RankingEntry **list, int *numEntries)
{
    FILE *file = fopen(fileName, "rb");
    if (file == NULL)
    {
        perror("Error opening file for reading");
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    *numEntries = fileSize / sizeof(RankingEntry);

    *list = (RankingEntry *)malloc(fileSize);

    rewind(file);
    fread(*list, sizeof(RankingEntry), *numEntries, file);

    fclose(file);
}

void printAlignedEntry(const char *name, int score)
{
    printf("%-50s %d\n", name, score);
}

int main()
{
    // Load the list from the binary file
    RankingEntry *ranking;
    int numEntries;
    loadFromFile("ranking.bin", &ranking, &numEntries);

    // Display the current ranking
    printf("Current Ranking:\n");
    for (int i = 0; i < numEntries; i++)
    {
        printAlignedEntry(ranking[i].name, ranking[i].score);
    }

    // Get a new entry from the user
    printf("\nEnter a new entry:\n");
    RankingEntry newEntry = createEntry();

    // Add the new entry if it's among the top 10
    int insertIndex = numEntries;
    for (int i = 0; i < numEntries; i++)
    {
        if (newEntry.score > ranking[i].score)
        {
            insertIndex = i;
            break;
        }
    }

    if (insertIndex < MAX_ENTRIES)
    {
        // Shift entries to make room for the new entry
        for (int i = numEntries - 1; i > insertIndex; i--)
        {
            ranking[i] = ranking[i - 1];
        }

        // Insert the new entry
        ranking[insertIndex] = newEntry;

        // Update the number of entries
        numEntries = (numEntries < MAX_ENTRIES) ? (numEntries + 1) : MAX_ENTRIES;

        // Sort the updated list
        qsort(ranking, numEntries, sizeof(RankingEntry), compareEntries);

        // Save the updated list to the file
        saveToFile("ranking.bin", ranking, numEntries);
        printf("\nThe new entry has been added to the ranking.\n");
    }
    else
    {
        printf("\nThe new entry did not make it to the top 10.\n");
    }

    // Display the updated ranking
    printf("\nUpdated Ranking:\n");
    for (int i = 0; i < numEntries; i++)
    {
        printAlignedEntry(ranking[i].name, ranking[i].score);
    }

    // Free the memory used by the list
    free(ranking);

    return 0;
}
