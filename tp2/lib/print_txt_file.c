#include <stdio.h>

void printTxtFile(char *file_name)
{
    int t;
    FILE *file;
    file = fopen(file_name, "r");
    if (file)
    {
        while ((t = getc(file)) != EOF)
            putchar(t);
        fclose(file);
    }
}