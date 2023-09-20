extern int debug; // variable global

int checkNotEqualNumbers(char numbers[], int start_at) {
    if(strlen(numbers) == start_at) {  // Si llega hasta esta igualdad, todos los retornos fueron 0
        return 0;
    }
    int flag = 0;
    for(int i = start_at; i < strlen(numbers) - 1; i++) {
        if (debug) {
            printf("[Indice: %d] ", start_at);
            printf("%c - %c ", numbers[start_at], numbers[i + 1]);
        }
        if(numbers[start_at] == numbers[i + 1]) {
            if (debug) printf("Son iguales\n");
            flag = 1;
            break; // Interrumpe el bucle para no seguir comparando
        } else {
            if (debug) printf("Son distintos\n");
        }
    }
    if(flag == 1) { // Si ya encontró dos números iguales retorna false y termina la función
        return flag;
    } else {
        flag = checkNotEqualNumbers(numbers, start_at + 1);
    }
}