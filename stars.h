#ifndef _STARS_
#define _STARS_

typedef struct remember { // структура для хранения координат и цветов звёзд
   int x, y, col;
} remember;

void rast_stars(int i);
void stars();
void stars_for_main();
#endif
