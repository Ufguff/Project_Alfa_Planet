





using namespace std;


#ifndef _MENU_
#define _MENU_

#define blue COLOR(20, 5, 35)
#define WX 1200
#define WY 700
#define M_PI 3.141592653589793
#endif
int currentPage = 0;

typedef struct planet{
   int ID, BASEID, X, Y;
   int P_RAD, ORB_RAD;
   double SPEED, t;
   IMAGE * bmp;
}Planet;

vector<Planet> all_planets;

void read_file();
void put_planets();
void move_planet();
void setACPage();
void setVSPage();
void change_dir(int index);

int main()
{
   initwindow(WX, WY, "Планетарная система", 200, 200, true);
   read_file();
   setbkcolor(blue);
   clearviewport();
   put_planets();
   while(true){
      move_planet();
      delay(10);
      //clearviewport();
   }
   return 0;
}

void move_planet()
{
   putimage(all_planets[0].X , all_planets[0].Y, all_planets[0].bmp, TRANSPARENT_PUT);
   for (int i = 1; i < all_planets.size(); i++) {change_dir(i);}
   swapbuffers();
   //setACPage();
   clearviewport();
}

void change_dir(int index)
{
   int x0 = WX / 2, y0 = WY / 2; // начальные координаты точки
   int a = all_planets[index].ORB_RAD + all_planets[0].P_RAD ;
   int b = a - all_planets[index].P_RAD; // полуоси эллипса
   double dt = 0.01; // начальный параметр и шаг
   double v = _abracadabra_cast(all_planets[i]);