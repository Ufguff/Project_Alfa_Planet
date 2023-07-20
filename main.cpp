#include "stars.h"
#include "movement.h"
#include "graphics.h"

double scale = 1.0, scalen = 1.0;
double offx = 0, offy = 0, offxn = 0, offyn = 0;

extern remember stars_rem[col_stars];

void wheelhandler(int x, int y)
{
   double grmin = 0.4, grmax = 15;
   double xa,ya;
   xa=mousex()/scale+offx;
   ya=mousey()/scale+offy;   
   if(x<0 && scale * 0.9 > grmin)      scale*=0.9;     // вверх
   else if (x > 0 && scale / 0.9 < grmax)         scale/=0.9;     // вниз
   offx=-mousex()/scale+xa;
   offy=-mousey()/scale+ya;
}

int main()
{
   srand(time(NULL));
   initwindow(WX, WY, "Планетарная система", 200, 200, true);
   registermousehandler(WM_MOUSEWHEEL,wheelhandler);
   read_file();
   setbkcolor(BLACK);
   clearviewport();
   stars();
   put_planets();
   while(true){
      stars_for_main();
      move_planet();
      scalen = scale;   offxn = offx; offyn = offy;
      delay(10);
   }
   return 0;
}
