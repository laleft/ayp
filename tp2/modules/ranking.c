#include <stdio.h>
/*
 * MOdulo para manejo del ranking
 *
 * DescripciOn:
 * Funciones para cargar, actualizar
 * y ordenar el ranking de jugadores
 *
 */

#include "../utils/helpers.c"

#define MAX_RANKING_RECORDS 10

typedef struct
{
    char name[50];
    int score;
} UserScore;

// Ordena el ranking
void sortScore(UserScore *list, int length)
{
    // Ordena la lista por score en forma creciente
    // MEtodo burbuja
    for (int i = 0; i < length - 1; i++)
    {
        for (int j = 0; j < length - i - 1; j++)
        {
            if (list[j].score > list[j + 1].score)
            {
                UserScore temp = list[j];
                list[j] = list[j + 1];
                list[j + 1] = temp;
            }
        }
    }
}

// Imprime el ranking con formato
void printRanking(UserScore *list, int list_length, int *position)
{
    BR(2);
    MGT;
    printBox("RANKING", 60, '*');
    RST;
    BR(2);
    printf("%4s %52s", "USUARIO", "SEGUNDOS");
    BR(2);
    for (int i = 0; i < list_length; i++)
    {
        if (*position == i)
            CYN;
        printf("%2d - %s ", i + 1, list[i].name);
        int name_length = strlen(list[i].name);
        for (int d = 0; d < 50 - name_length; d++)
        {
            printf(".");
        }
        printf(" %d\n", list[i].score);
        RST;
    }
    BR(2);
}

void loadRanking(UserScore *list, int *num_records)
{

    // Abre el archivo o lo crea si no existe
    FILE *loaded_ranking = fopen("data/ranking.dat", "ab+");
    if (loaded_ranking == NULL)
    {
        perror("No se pudo cargar el ranking");
        exit(1);
    }

    // Para usuarios de la lista
    UserScore user;

    // Contador de registros en el archivo
    *num_records = 0;
    while (!feof(loaded_ranking))
    {
        size_t items_read = fread(&user, sizeof(UserScore), 1, loaded_ranking);
        // Si lee el registro lo agrega a la lista
        if (items_read == 1)
        {
            strcpy(list[(*num_records)].name, user.name);
            list[(*num_records)].score = user.score;
            (*num_records)++;
        }
    }
    fclose(loaded_ranking);
}

void updateRanking(UserScore user_score, UserScore *list, int *num_records, int *position)
{

    // Toma el valor del total de registros a guardar
    // en el archivo
    int to_insert;

    // Si no existen registros se inserta el primero
    if (*num_records == 0)
    {
        strcpy(list[0].name, user_score.name);
        list[0].score = user_score.score;
        to_insert = 1;
        *position = 0;
    }
    else
    {
        // Si ya estAn ocupados todos los lugares
        if (*num_records == MAX_RANKING_RECORDS)
        {
            for (int i = 0; i < MAX_RANKING_RECORDS; i++)
            {
                // Ubica el score actual en la lista
                if (list[i].score > user_score.score)
                {
                    // printf("%s tiene mejor puntaje que %s\n", user_score.name, list[i].name);
                    strcpy(list[i].name, user_score.name);
                    list[i].score = user_score.score;
                    *position = i;
                    break;
                }
            }
            // Inserta el nUmero mAximo de registros
            to_insert = *num_records;
        }
        else
        {
            // Si quedan lugares disponibles
            // Busca en quE posiciOn va a quedar
            for (int i = 0; i < *num_records; i++)
            {
                if (list[i].score > user_score.score)
                {
                    *position = i;
                    break;
                }
            }
            strcpy(list[(*num_records)].name, user_score.name);
            list[(*num_records)].score = user_score.score;
            // NUmero de registros + 1 ya que num_records
            // comienza en 0
            to_insert = (*num_records) + 1;
        }

        // Longitud final de la lista
        *num_records = to_insert;
    }

    // Ordena el ranking
    sortScore(list, to_insert);

    // Guarda la lista en el archivo
    FILE *ranking = fopen("data/ranking.dat", "wb");
    int stored = fwrite(list, sizeof(UserScore), to_insert, ranking);
    fclose(ranking);
}

int ranking(char *name, int score)
{
    // Variable para los datos que vienen del juego
    UserScore user_score;
    strcpy(user_score.name, name);
    user_score.score = score;

    UserScore *list;
    // Asigna memoria para la lista de entradas
    list = malloc(sizeof(UserScore) * (MAX_RANKING_RECORDS + 1));

    // Para longitud final de la lista
    int list_length;

    loadRanking(list, &list_length);

    // PosiciOn del usuario en el ranking
    int position;

    if (score > 0)
    {
        // Actualiza el ranking
        updateRanking(user_score, list, &list_length, &position);
    }

    // Imprime el ranking
    printRanking(list, list_length, &position);

    // Vuelve al menU principal
    printf("PRESIONA [ENTER] PARA VOLVER AL MENU PRINCIPAL...");
    while (getchar() != '\n')
        ;
    getchar();

    return 0;
}