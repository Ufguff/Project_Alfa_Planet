#include <iostream>
#include <ctime>
#include <unistd.h>
#include "graphics.h"

using namespace std;

//const int wx = 1200, wy = 700; // ������� ����

const int col_stars = 150; // ����� ���������� ����
int colors[10] = { COLOR(252, 245, 245), COLOR(127, 239, 153), COLOR(239, 153, 127), COLOR(214, 210, 239), COLOR(239, 191, 127), COLOR(242, 176, 237) };

typedef struct remember { // ��������� �������� ��������� ����
   int ir, jr;
} remember;
remember stars_rem[col_stars];

void rast_stars(int i) { // ����������� ����
   stars_rem[i].ir = rand() % wx;
   stars_rem[i].jr = rand() % wy;
   setfillstyle(SOLID_FILL, colors[rand() % 7]); // ��������� ������ �� ��������� ������ �� ������ ������
   bar(stars_rem[i].ir, stars_rem[i].jr, stars_rem[i].ir+1, stars_rem[i].jr+1);
}

void stars() { // ����������� ��������� ����������� ����
   srand(static_cast<unsigned>(time(NULL)));
   for (int i = 0; i < col_stars; i++)
      rast_stars(i);
}

void stars_for_main() { // ������������ ��������� ���� ������ � ��������� ����� �� ����� �����������
   int col_help = rand() % col_stars;
   setfillstyle(SOLID_FILL, BLACK);
   bar(stars_rem[col_help].ir, stars_rem[col_help].jr, stars_rem[col_help].ir+1, stars_rem[col_help].jr+1);
   rast_stars(col_help);
   delay(3);
}

/*
int main() {
   initwindow(wx, wy, "�����", 0, 0);
   stars();
   while (1)
      stars_for_main();
   
   return 0;
}*/