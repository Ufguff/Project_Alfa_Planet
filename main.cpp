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

#endif



typedef struct planet{
   int ID, BASEID;
   int R_RAD, ORB_RAD;
   double SPEED;
   IMAGE * bmp;
}Planet;

vector<Planet> all_planets;



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
            temp.ID = stoi(out[0]);        temp.R_RAD = stoi(out[1]);
         }
         else{
            temp.ID = stoi(out[0]);
            temp.BASEID = stoi(out[1]); 
            temp.R_RAD = stoi(out[2]);
            temp.ORB_RAD = stoi(out[3]);
            temp.SPEED = stod(out[4]);
            cout << "------------------" << temp.SPEED << endl;
         }
         all_planets.push_back(temp);
      }
   F.close();
   }
}

void put_planets()
{
   for (int i = 0; i < all_planets.size(); i++){
      IMAGE * bmp = loadBMP("./Pic_Plan/planet.bmp");
      bmp = imageresize(bmp, all_planets[i].R_RAD * 2, all_planets[i].R_RAD * 2, COLORONCOLOR_RESIZE);
       all_planets[i].bmp = bmp;
      if (all_planets[i].ID == 0 )      putimage(WX / 2 - all_planets[i].R_RAD, WY / 2 - all_planets[i].R_RAD, all_planets[i].bmp, TRANSPARENT_PUT);
      else      putimage(WX / 2 - all_planets[i].R_RAD + all_planets[i].ORB_RAD, WY / 2 - all_planets[i].R_RAD, all_planets[i].bmp, TRANSPARENT_PUT);
   }
   
}

int main()
{
   initwindow(WX, WY, "Планетарная система", 200, 200);
   read_file();
   setbkcolor(blue);
   clearviewport();
   //swapbuffers();
   //putimage(WX / 2, WY / 2, all_planets[0].bmp, TRANSPARENT_PUT);
   put_planets();
   while(true);
   return 0;
}