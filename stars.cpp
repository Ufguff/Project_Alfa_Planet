#include <ctime>
#define WX 1200
#define WY 700
#define col_stars 150
#include "stars.h"
#include "graphics.h"

int count_st = 0;
int colors[10] = { COLOR(252, 245, 245), COLOR(127, 239, 153), COLOR(239, 153, 127), COLOR(214, 210, 239), COLOR(239, 191, 127), COLOR(242, 176, 237) }; // массив цветов звёзд
remember stars_rem[col_stars];

void rast_stars(int i) { // случайный выбор расположений и цветов звёзд
   stars_rem[i].x = rand() % WX;
   stars_rem[i].y = rand() % WY;
   stars_rem[i].col = rand() % 7;
   putpixel(stars_rem[i].x, stars_rem[i].y, colors[stars_rem[i].col]);
}

void stars() { // изначальная случайная расстановка звёзд
   srand(static_cast<unsigned>(time(NULL)));
   for (int i = 0; i < col_stars; i++)
      rast_stars(i);
}

void stars_for_main() { // закрашивание случайных звёзд и отрисовка новых на смену закрашенным
   if (count_st == 40) {
      int col_help = rand() % col_stars;
      rast_stars(col_help);
      count_st = 0;
   }
   count_st++;
   clearviewport();
   for (int j = 0; j < col_stars; j++)
      putpixel(stars_rem[j].x, stars_rem[j].y, colors[stars_rem[j].col]);
}
