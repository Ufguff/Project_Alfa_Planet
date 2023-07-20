#ifndef _const_
#define _const_

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <random>
#include "graphics.h"

using namespace std;

#define WX 1200
#define WY 700
#define col_stars 150
#define M_PI 3.141592653589793

typedef struct planet{
   int ID, BASEID, X, Y;
   int P_RAD, ORB_RAD;
   double SPEED, t;
   IMAGE * bmp;
}Planet;

void read_file();
void put_planets();
void move_planet();
void change_dir(int index);
void comet(double p, double e, double phi);
#endif