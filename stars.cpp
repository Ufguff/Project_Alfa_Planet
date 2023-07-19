#include <ctime>
#define WX 1200
#define WY 700
#define col_stars 150
#include "stars.h"
#include "graphics.h"

int colors[10] = { COLOR(252, 245, 245), COLOR(127, 239, 153), COLOR(239, 153, 127), COLOR(214, 210, 239), COLOR(239, 191, 127), COLOR(242, 176, 237) }; // массив цветов звёзд
remember stars_rem[col_stars];

void scol_bar(int col, int col_help) { // установка цвета и отрисовка звёзд
   setfillstyle(SOLID_FILL, col);
   bar(stars_rem[col_help].ir, stars_rem[col_help].jr, stars_rem[col_help].ir+1, stars_rem[col_help].jr+1);
}

void rast_stars(int i) { // расстановка звёзд
   stars_rem[i].ir = rand() % WX;
   stars_rem[i].jr = rand() % WY;
   stars_rem[i].col = rand() % 7;
   scol_bar(colors[stars_rem[i].col], i);
}

void stars() { // изначальная случайная расстановка звёзд
   srand(static_cast<unsigned>(time(NULL)));
   for (int i = 0; i < col_stars; i++)
      rast_stars(i);
}

void stars_for_main() { // закрышивание случайных звёзд чёрным и отрисовка новых на смену закрашенным
   int col_help = rand() % col_stars;
   scol_bar(BLACK, col_help);
   rast_stars(col_help);
   clearviewport();
   for (int j = 0; j < col_stars; j++)
      scol_bar(colors[stars_rem[j].col], j);
}
