#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include "graphics.h"
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
   int x0 = WX / 2 - all_planets[0].P_RAD, y0 = WY / 2 - all_planets[0].P_RAD; // начальные координаты точки
   int a = all_planets[index].ORB_RAD + all_planets[0].P_RAD ;
   int b = a - all_planets[index].P_RAD; // полуоси эллипса
   double dt = 0.01; // начальный параметр и шаг
   double v = all_planets[index].SPEED; 

   int x = v + x0 + round(a * cos(all_planets[index].t));
   int y = v + y0 + round(b * sin(all_planets[index].t));
   all_planets[index].X = x;    all_planets[index].Y = y;
   // отображение точки на экране

   // увеличение значения параметра t на шаг dt
   all_planets[index].t += dt;

   // если значение параметра t превышает 2?, то вернуть его к начальному значению t0
   if (all_planets[index].t > 2 * M_PI)
      all_planets[index].t -= 2 * M_PI;
   //setVSPage();
   
   putimage(all_planets[index].X , all_planets[index].Y, all_planets[index].bmp, TRANSPARENT_PUT);
   //swapbuffers();
   //setACPage();
   
                                                                                             //  delay(10); // задержка для плавного перемещения точки
   //cleardevice(); // очистка экрана
}

void read_file()
{
   string s;
   ifstream F("pl.txt");
   if (F.is_open()){
      while(getline(F, s))     // игнорит пока double
      {
         vector<string> out;
         stringstream ss(s);
         string word;
         while (ss >> word) {
            cout << word << endl;
            out.push_back(word);
         }
         planet temp;
         if(out.size() == 2){
            temp.ID = stoi(out[0]);        temp.P_RAD = stoi(out[1]);
         }
         else{
            temp.ID = stoi(out[0]);
            temp.BASEID = stoi(out[1]); 
            temp.P_RAD = stoi(out[2]);
            temp.ORB_RAD = stoi(out[3]);
            temp.SPEED = stod(out[4]);
            cout << "------------------" << temp.SPEED << endl;
         }
         temp.t = 0;
         all_planets.push_back(temp);
      }
   F.close();
   }
}

void put_planets()
{
   //setACPage();
   for (int i = 0; i < all_planets.size(); i++){
      int k;
      IMAGE * bmp = loadBMP("./Pic_Plan/planet.bmp");
      bmp = imageresize(bmp, all_planets[i].P_RAD * 2, all_planets[i].P_RAD * 2, COLORONCOLOR_RESIZE);
      all_planets[i].bmp = bmp;
      
      if (all_planets[i].ID == 0 )      {
         all_planets[i].X = WX / 2 - all_planets[i].P_RAD;      all_planets[i].Y = WY / 2 - all_planets[i].P_RAD;
      }
      else{
         if (all_planets[i].BASEID == 0){
            all_planets[i].X = WX / 2 - all_planets[i].P_RAD + all_planets[i].ORB_RAD;      all_planets[i].Y = WY / 2 - all_planets[i].P_RAD;
         }
         else{
            k = all_planets[i].BASEID;
            all_planets[i].X = WX / 2 + all_planets[k].P_RAD + 10 + all_planets[k].ORB_RAD;      all_planets[i].Y = WY / 2 - all_planets[k].P_RAD - 10;
         }
      }
      putimage(all_planets[i].X, all_planets[i].Y, all_planets[i].bmp, TRANSPARENT_PUT);
   }
   //setVSPage();
   swapbuffers();
}

void setACPage()
{
   if(currentPage == 3)        currentPage = 0;
   currentPage++;
   setactivepage(currentPage);
}

void setVSPage(){       setvisualpage(currentPage);     }