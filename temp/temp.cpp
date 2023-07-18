





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
      //delay(100);
      clearviewport();
   }
   return 0;
}

void move_planet()
{
   /*
   for (int i = 1; i < all_planets.size(); i++){ 
      setACPage();
      for (int j = 0; j < all_planets.size(); j++){
         if (i == j) {change_dir(j);   continue;}
         
         putimage(all_planets[i].X , all_planets[i].Y, all_planets[i].bmp, TRANSPARENT_PUT);
         //delay(1000);
      }
      setVSPage();
   }
   */
   putimage(all_planets[0].X , all_planets[0].Y, all_planets[0].bmp, TRANSPARENT_PUT);
   for (int i = 1; i < _abracadabra_cast(all_planets);