#include <stdio.h>
#include <string.h>
#include "helpers.c"

#define MARGINS 4 // Margen por si el texto supera el tamanio de la caja
#define PADDING 2 // Espacio desde el borde contando el primer caracter

void printBox(char *text, int size, int style)
{
    char tmp[strlen(text)];
    strcpy(tmp, text);
    char *token = strtok(tmp, "\n");
    while (token != NULL)
    {

        printf("%s\n", token);
        token = strtok(NULL, "\n");
    }

    int text_length = strlen(text);
    // Si el texto supera el tamanio de la caja
    if (text_length >= size)
        size = text_length + MARGINS;

    int blank = size - text_length - PADDING; // Espacios en blanco
    int blank_left = blank / 2;               // A la izquierda
    int blank_right = blank - blank_left;     // A la derecha

    // printf("Box size: %d\n", size);
    // printf("Text length: %d\n", text_length);
    // printf("Space: %d\n", blank);
    // printf("Blank left: %d\n", blank_left);
    // printf("Blank right: %d\n", blank_right);

    RPT(style, size); // Top

    BR(1);
    RPT(style, 1);
    RPT(' ', size - PADDING);
    RPT(style, 1);

    BR(1);
    RPT(style, 1);
    RPT(' ', blank_left);
    printf("%s", text);
    RPT(' ', blank_right);
    RPT(style, 1);

    BR(1);
    RPT(style, 1);
    RPT(' ', size - PADDING);
    RPT(style, 1);
    BR(1);

    RPT(style, size); // Bottom
}