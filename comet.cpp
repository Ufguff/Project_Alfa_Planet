#define WIDTH 1200
#define HEIGHT 800

#include <graphics.h>
#include <math.h>

void comet();
void move_comet();

void comet(){
   double p=80,e=0.8,phi=1;
   
    for(double angle = 0;angle<acos(-1)*2;angle+=0.01)
    {
       double r=p/(1-e*cos(angle+phi));
       putpixel(r*cos(angle)+WIDTH/2,r*sin(angle)+HEIGHT/2,WHITE);
    }
}

void move_comet(){
   
}

int main()
{
    initwindow(WIDTH, HEIGHT);
    comet();
    getch();
    return 0;
}