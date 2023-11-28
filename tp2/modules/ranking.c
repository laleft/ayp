#include <stdio.h>

#define MAX_RANKING_RECORDS 2
typedef struct
{
    char name[50];
    int score;
} UserScore;

int ranking(char *name, int score)
{

    // Variable para los datos que vienen del juego
    UserScore user_score;
    strcpy(user_score.name, name);
    user_score.score = score;

    // memset(&user_score, 0, sizeof(UserScore));

    printf("NOMBRE: %s\n", user_score.name);
    printf("SCORE: %d\n", user_score.score);

    // Abre el archivo o lo crea si no existe
    FILE *loaded_ranking = fopen("data/ranking.dat", "ab+");
    if (loaded_ranking == NULL)
    {
        perror("No se pudo cargar el ranking");
        exit(1);
    }

    // Asigna memoria para la lista de entradas
    UserScore *list = malloc(sizeof(UserScore) * (MAX_RANKING_RECORDS + 1));

    UserScore loaded;

    // Contador de registros en el archivo
    int num_records = 0;

    while (!feof(loaded_ranking))
    {
        size_t items_read = fread(&loaded, sizeof(UserScore), 1, loaded_ranking);
        // Si lee el registro lo agrega a la lista
        if (items_read == 1)
        {
            // printf("Nombre: %s, Score: %d, \n", loaded.name, loaded.score);
            strcpy(list[num_records].name, loaded.name);
            list[num_records].score = loaded.score;
            num_records++;
        }
    }
    fclose(loaded_ranking);
    printf("LEIDOS: %d\n", num_records);

    int to_insert;

    if (num_records == 0)
    {
        strcpy(list[0].name, user_score.name);
        list[0].score = user_score.score;
        to_insert = 1;
        printf("TO INSERT CERO: %d\n", to_insert);
    }
    else
    {
        int record_index = -1;
        // Si ya estAn ocupados todos los lugares
        if (num_records == MAX_RANKING_RECORDS)
        {
            for (int i = 0; i < MAX_RANKING_RECORDS; i++)
            {
                if (list[i].score > user_score.score)
                {
                    printf("%s tiene mejor puntaje que %s\n", user_score.name, list[i].name);
                    strcpy(list[i].name, user_score.name);
                    list[i].score = user_score.score;
                    record_index = i;
                    break;
                }
            }
            to_insert = num_records;
            printf("TO INSERT COMPLETO: %d\n", to_insert);
        }
        else
        {
            strcpy(list[num_records].name, user_score.name);
            list[num_records].score = user_score.score;
            // list[num_records + 1] = user_score;
            to_insert = num_records + 1;
            printf("TO INSERT DISPONIBLE: %d\n", to_insert);
        }
    }

    printf("TO INSERT %d\n", to_insert);

    FILE *ranking = fopen("data/ranking.dat", "wb");
    int stored = fwrite(list, sizeof(UserScore), to_insert, ranking);
    printf("GUARDADO: %d\n", stored);
    fclose(ranking);

    for (int i = 0; i < num_records; i++)
    {
        printf("%d) %s ...... %d\n", i, list[i].name, list[i].score);
    }

    printf("PRESIONA [ENTER] PARA VOLVER AL MENU PRINCIPAL...");
    while (getchar() != '\n')
        ;
    getchar();

    return 0;
}