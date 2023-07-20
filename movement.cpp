#include "movement.h"

#include "graphics.h"

vector<Planet> all_planets;
planet cometa;

extern double scale, scalen, offx, offy, offxn, offyn;

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

