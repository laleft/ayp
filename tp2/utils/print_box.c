#include <stdio.h>
#include <string.h>
#include "helpers.c"

void printBox(char *text, int size, int style)
{
    int text_length = strlen(text);
    if (text_length >= size)
        size = text_length + 3;
    int blank = size - text_length - 2; // El (-2) es para los caracteres al comienzo y al final de la caja
    int blank_left = (size / 2) - (text_length / 2);
    int blank_right = blank - blank_left;

    RPT(style, size); // Top

    BR(1);
    RPT(style, 1);
    RPT(' ', size - 2);
    RPT(style, 1);

    BR(1);
    RPT(style, 1);
    RPT(' ', blank_left);
    printf("%s", text);
    RPT(' ', blank_right);
    RPT(style, 1);

    BR(1);
    RPT(style, 1);
    RPT(' ', size - 2);
    RPT(style, 1);
    BR(1);

    RPT(style, size); // Bottom
}