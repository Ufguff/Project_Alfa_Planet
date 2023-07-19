









using namespace std;


#ifndef _MENU_
#define _MENU_

#define blue COLOR(20, 5, 35)
#define WX 1200
#define WY 700
#define col_stars 150
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

extern remember stars_rem[col_stars];

int main()
{
   srand(time(NULL));
   initwindow(WX, WY, "Планетарная система", 200, 200, true);
   read_file();
   setbkcolor(BLACK);
   clearviewport();
   stars();
   put_planets();
   while(true){
      stars_for_main();
      move_planet();
      delay(10);
   }
   return 0;
}

void move_planet()
{
   putimage(all_planets[0].X , all_planets[0].Y, all_planets[0].bmp, TRANSPARENT_PUT);
   for (int i = all_planets.size() - 1; i >= 1 ; i--) {change_dir(i);}
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
      int a = all_planets[index].ORB_RAD + all_planets[k].P_RAD, b = a;
      int xe = all_planets[k].X + all_planets[k].P_RAD;
      int ye = all_planets[k].Y + all_planets[k].P_RAD;
      ellipse(xe, ye, 0, 360, a, b);
      x = xe - all_planets[index].P_RAD + round(a * cos(all_planets[index].t));
      y = ye / 2 - all_planets[index].P_RAD + round(b * sin(all_planets[index].t));
   }
   else{
      int a = all_planets[index].ORB_RAD, b = a;
      ellipse(WX / 2, WY / 2, 0, 360, a, b);
      x = WX / 2 - all_planets[index].P_RAD + round(a * cos(all_planets[index].t));
      y = WY / 2 - all_planets[index].P_RAD + round(b * sin(all_planets[index].t));
   }
   all_planets[index].X = x;    all_planets[index].Y = y;

   all_planets[index].t += dt;

   if (all_planets[index].t > 2 * M_PI)
      all_planets[index].t -= 2 * M_PI;
   
   putimage(all_planets[index].X , all_planets[index].Y, all_planets[index].bmp, TRANSPARENT_PUT);
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
   char s[30];
   int n, k;
   IMAGE * bmp;
   for (int i = 0; i < all_planets.size(); i++){
      if (all_planets[i].ID != 0){
         n = rand() % 14 + 1;
         cout << n << endl;
         sprintf(s, "./Pic_Plan/planet%d.bmp", n);
         cout << s << endl;
         bmp = loadBMP(s);
      }
      else      {bmp = loadBMP("./Pic_Plan/planet0.bmp");}
      
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
            all_planets[i].X = all_planets[k].X + all_planets[k].P_RAD + _abracadabra_cast(all_planets[i]);