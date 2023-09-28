extern int debug; // variable global

int checkNotEqualNumbers(char numbers[], int start_at)
{
    if (strlen(numbers) == start_at)
    { // Si llega hasta esta igualdad, todos los retornos fueron 1
        return 1;
    }
    int flag = 1;
    for (int i = start_at; i < strlen(numbers) - 1; i++)
    {
        if (debug)
        {
            printf("[%d] --> ", start_at);
            printf("%c == %c ", numbers[start_at], numbers[i + 1]);
        }
        if (numbers[start_at] == numbers[i + 1])
        {
            if (debug)
                printf(" T\n");
            flag = 0;
            break; // Interrumpe el bucle para no seguir comparando
        }
        else
        {
            if (debug)
                printf(" F\n");
        }
    }
    if (flag == 0)
    { // Si ya encontró dos números iguales retorna false y termina la función
        return flag;
    }
    else
    {
        flag = checkNotEqualNumbers(numbers, start_at + 1);
    }
}