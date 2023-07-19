#ifndef _STARS_
#define _STARS_

typedef struct remember { // структура для хранения координат и цветов звёзд
   int ir, jr, col;
} remember;

void scol_bar(int col, int col_help);
void rast_stars(int i);
void stars();
void stars_for_main();
#endif