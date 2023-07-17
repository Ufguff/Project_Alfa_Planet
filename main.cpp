#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include "graphics.h"
using namespace std;


#ifndef _MENU_
#define _MENU_

//#define COSMIC_LATTE COLOR(255, 248, 231)
#define WX 800
#define WY 600

#endif



typedef struct planet{
   int ID, BASEID;
   int R_RAD, ORB_RAD;
   double SPEED;
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
            temp.ID = stoi(out[0]);        temp.BASEID = stoi(out[1]);
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

int main()
{
   initwindow(WX, WY, "Планетарная система", 200, 200);
   setbkcolor(COLOR(255, 248, 231));
   clearviewport();
   //swapbuffers();
   read_file();
   while(true);
   return 0;
}