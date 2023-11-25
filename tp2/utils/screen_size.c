#include <windows.h>
/*
 * TamanIo de la consola
 *
 * DescripciOn:
 * FunciOn que calcula el temanio de la consola
 * en filas y columnas
 *
 * ParAmetros:
 * - columns: puntero entero a donde se almacenarA la cantidad de columnas
 * - rows: puntero entero a donde se almacenarA la cantidad de filas
 *
 * Retorna:
 *  - sin valor de retorno (void)
 *
 */
void screenSize(int *columns, int *rows)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    *columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    *rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}