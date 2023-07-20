#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <random>
#include "stars.h"

#include "graphics.h"
using namespace std;


#ifndef _MENU_
#define _MENU_

#define blue COLOR(20, 5, 35)
#define WX 1200
#define WY 700
#define col_stars 150
#define M_PI 3.141592653589793
#endif

double scale = 1.0, scalen = 1.0;
double offx = 0, offy = 0, offxn = 0, offyn = 0;

typedef struct planet{
   int ID, BASEID, X, Y;
   int P_RAD, ORB_RAD;
   double SPEED, t;
   IMAGE * bmp;
}Planet;

vector<Planet> all_planets;
planet cometa;

void read_file();
void put_planets();
void move_planet();
void setACPage();
void setVSPage();
void change_dir(int index);
void comet(double p, double e, double phi);

extern remember stars_rem[col_stars];

void wheelhandler(int x, int y)
{
   double grmin = 0.4, grmax = 15;
   double xa,ya;
   xa=mousex()/scale+offx;
   ya=mousey()/scale+offy;   
   if(x<0 && scale * 0.9 > grmin)      scale*=0.9;     // вверх.
   else if (x > 0 && scale / 0.9 < grmax)         scale/=0.9;     // вниз
   cout << scale << endl;
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

void move_planet()
{
   putimage((all_planets[0].X - offxn)*scalen, (all_planets[0].Y - offyn)*scalen, all_planets[0].bmp, TRANSPARENT_PUT, 2 * all_planets[0].P_RAD * scalen);
   for (int i = all_planets.size() - 1; i >= 1 ; i--) {change_dir(i);}
   comet(80, 0.5, 1);
   comet(60, 0.5, 0.1);
   swapbuffers();
   clearviewport();
}

void change_dir(int index)
{
   int k, x, y;
   double dt = 0.01;
   double v = all_planets[index].SPEED;
   if (all_planets[index].BASEID != 0){
      k = all_planets[index].BASEID;
      int r = all_planets[index].ORB_RAD + all_planets[k].P_RAD;
      int xe = all_planets[k].X + all_planets[k].P_RAD;
      int ye = all_planets[k].Y + all_planets[k].P_RAD;
      circle((xe - offxn) * scalen, (ye - offyn) * scalen, r * scalen);
      x = xe - all_planets[index].P_RAD + round(r * cos(all_planets[index].t));
      y = ye - all_planets[index].P_RAD + round(r * sin(all_planets[index].t));
   }
   else{
      int r = all_planets[index].ORB_RAD;
      circle((WX / 2 - offxn) * scalen, (WY / 2 - offyn) * scalen, r * scalen);
      x = WX / 2 - all_planets[index].P_RAD + round(r * cos(all_planets[index].t));
      y = WY / 2 - all_planets[index].P_RAD + round(r * sin(all_planets[index].t));
   }
   all_planets[index].X = x;    all_planets[index].Y = y;

   all_planets[index].t += dt * (v / all_planets[index].ORB_RAD);

   if (all_planets[index].t > 2 * M_PI)
      all_planets[index].t -= 2 * M_PI;
   
   putimage((all_planets[index].X - offxn)*scalen, (all_planets[index].Y - offyn)*scalen, all_planets[index].bmp, TRANSPARENT_PUT, 2 * all_planets[index].P_RAD * scalen);
}

void read_file()
{
   string s;
   ifstream F("pl.txt");
   if (F.is_open()){
      while(getline(F, s))
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
            temp.ID = stoi(out[0]);        temp.P_RAD = stoi(out[1]) / 3 ;
         }
         else{
            temp.ID = stoi(out[0]);
            temp.BASEID = stoi(out[1]); 
            temp.P_RAD = stoi(out[2]) / 3;
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

void comet(double p, double e, double phi){
   double angle = cometa.t;
   double r=p/(1-e*cos(angle+phi));
   
    for(double angle = 0;angle<acos(-1)*2;angle+=0.01)
    {
       double r=p/(1-e*cos(angle+phi));
       putpixel((r*cos(angle)+WX/2 - offxn) * scalen , (r*sin(angle)+WY/2 - offyn) * scalen, WHITE);
    }
    
   putimage((r*cos(angle)+WX/2 - offxn - 5) * scalen, (r*sin(angle)+WY/2 - offyn - 5) * scalen, cometa.bmp, TRANSPARENT_PUT, 10 * scalen);
   cometa.t += 0.01;
}

void put_planets()
{
   vector<int> pics;
   for (int i = 1; i <= 30; i++)        pics.push_back(i);
   random_shuffle(pics.begin(), pics.end());
   char s[30];
   int n, k;
   IMAGE * bmp;
   bmp = loadBMP("./Pic_Plan/comet.bmp");
   cometa.bmp = imageresize(bmp, 10, 10, COLORONCOLOR_RESIZE);
   for (int i = 0; i < all_planets.size(); i++){
      if (all_planets[i].ID != 0){
         n = pics[i];
         sprintf(s, "./Pic_Plan/Planet%d.bmp", n);
         bmp = loadBMP(s);
      }
      else      {bmp = loadBMP("./Pic_Plan/Planet0.bmp");}
      
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
            all_planets[i].X = all_planets[k].X + all_planets[k].P_RAD + all_planets[i].ORB_RAD;      all_planets[i].Y = all_planets[k].Y + all_planets[k].P_RAD + all_planets[i].ORB_RAD;
         }
      }
      putimage(all_planets[i].X, all_planets[i].Y, all_planets[i].bmp, TRANSPARENT_PUT);
   }
   swapbuffers();
}