#include <stdio.h>
#include <string.h>
/*
 * Dibuja cajas de texto
 *
 * DescripciOn:
 * FunciOn para dibujar cajas con el caracter especificado
 * y con texto alineado al centro
 *
 * ParAmetros:
 * - text: puntero de tipo char con el texto a imprimir
 * - size: tamanio en columnas de la caja
 * - style: caracter que se usarA para dibujar la caja
 *
 * Retorna:
 * - sin valor de retorno (void)
 *
 * ToDo:
 * - Centrar la caja en la pantalla
 */

#include "helpers.c"
#include "screen_size.c"

#define MARGINS 4 // Margen por si el texto supera el tamanio de la caja
#define PADDING 2 // Espacio desde el borde contando el primer caracter

void printBox(char *text, int size, int style)
{

    // Recupera ancho y alto de la consola
    int columns;
    int rows;
    screenSize(&columns, &rows);
    // Si size es -1 toma el ancho total de la consola
    if (size == -1)
        size = columns;

    char tmp[strlen(text)]; // Variable temporal para split
    char aux[strlen(text)]; // Variable auxiliar para contadores
    strcpy(tmp, text);
    strcpy(aux, text);

    unsigned int lines = 0; // Cantidad de lIneas
    unsigned int max = 0;   // LInea mas extensa

    // Cuenta la cantidad de lIneas y el tamanio de
    // lInea mAs grande
    char *aux_lines = strtok(aux, "\n");
    while (aux_lines != NULL)
    {
        ++lines;
        int line_lenght = strlen(aux_lines);
        if (max < line_lenght)
            max = line_lenght;
        aux_lines = strtok(NULL, "\n");
    }

    // Dibuja la caja segUn la cantidad de lIneas
    char *token = strtok(tmp, "\n");
    unsigned int loop = 1;
    while (token != NULL)
    {
        int text_length = strlen(token);
        // Si el texto supera el tamanio de la caja
        if (max >= size)
            size = max + MARGINS;

        int blank = size - text_length - PADDING; // Espacios en blanco
        int blank_left = blank / 2;               // A la izquierda
        int blank_right = blank - blank_left;     // A la derecha

        // printf("Box size: %d\n", size);
        // printf("Text length: %d\n", text_length);
        // printf("Space: %d\n", blank);
        // printf("Blank left: %d\n", blank_left);
        // printf("Blank right: %d\n", blank_right);

        // Si estamos en el primer loop dibuja
        // el borde superior
        if (loop == 1)
            RPT(style, size); // Top

        BR(1);
        RPT(style, 1);
        RPT(' ', size - PADDING);
        RPT(style, 1);

        BR(1);
        RPT(style, 1);
        RPT(' ', blank_left);
        printf("%s", token);
        RPT(' ', blank_right);
        RPT(style, 1);

        // Si estamos en la Ultima lInea dibuja el padding y
        // el borde inferior
        if (loop == lines)
        {
            BR(1);
            RPT(style, 1);
            RPT(' ', size - PADDING);
            RPT(style, 1);
            BR(1);
            RPT(style, size); // Bottom
        }
        loop++;
        token = strtok(NULL, "\n");
    }
}