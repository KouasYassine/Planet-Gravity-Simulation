// Imagine++ project
// Project:  Tp4_Initial
// Student(s): Yassine KOUAS

#include <Imagine/Graphics.h>
using namespace Imagine;

#include <iostream>
#include <cmath> // For sqrt
using namespace std;

const int width = 512;
const int height =512;

const double dt = 1;
const int freqDisplay = 10;
struct Ball{ double x;double y; double vx;double vy;double r; Color color;double mass;};
Ball Sun={width/2,height/2,0,0,50,YELLOW,100};

void shock(double x,  double y,  double &vx,  double &vy,  double m,
           double x2, double y2, double &vx2, double &vy2, double m2) {
    double vvx = (m * vx + m2 * vx2)/(m + m2);
    double vvy = (m * vy + m2 * vy2)/(m + m2);
    double deltax = x2 - x;
    double deltay = y2 - y;
    double norme = deltax * deltax + deltay * deltay;
    double scal = -2. * ((vx-vvx)*deltax + (vy-vvy)*deltay)/norme;
    vx += scal * deltax;
    vy += scal * deltay;
    scal = -2. * ((vx2-vvx)*deltax + (vy2-vvy)*deltay)/norme;
    vx2 += scal * deltax;
    vy2 += scal * deltay;
}

void shockSimple(double x,  double y,  double &vx, double &vy, double m,
                 double x2, double y2, double vx2, double vy2) {
    shock(x,y,vx,vy,m,x2,y2,vx2,vy2,1000*m);
}

bool collision(double x1, double y1, double vx1, double vy1, double r1,
               double x2, double y2, double vx2, double vy2, double r2)
{
    double dx=x1-x2,dy=y1-y2,dvx=vx1-vx2,dvy=vy1-vy2,r=r1+r2;
    if(dvx*dvx + dvy*dvy != 0) {
        double t_min = -(dx*dvx + dy*dvy)/(dvx*dvx + dvy*dvy);
        double t_true;
        if (t_min < 0)
            t_true = 0;
        else if (t_min > dt)
            t_true = dt;
        else
            t_true = t_min;
        dx += dvx * t_true;
        dy += dvy * t_true;
    }
    return ((dx*dx + dy*dy) <= r*r);
}

void DisplayBall (Ball D){ fillCircle(D.x,D.y,D.r,D.color);}

void EraseBall(Ball D){ fillCircle(D.x,D.y,D.r,WHITE);}

void Deplacer_Ball(Ball  & D){D.x+=D.vx*dt;
    D.y+=D.vy*dt;}

void Modify_speed( Ball & D) {
    double r=sqrt((D.x-Sun.x)*(D.x-Sun.x)+(D.y-Sun.y)*(D.y-Sun.y));
    if (r>= D.r+Sun.r){
        D.vx+=
            Sun.mass*dt*-(D.x-Sun.x) /pow(r,3) ;
        D.vy+=Sun.mass*dt*-(D.y-Sun.y) /pow(r,3);}
}

void shockSimple( Ball & D1,Ball D2){shockSimple(D1.x,  D1.y,  D1.vx, D1.vy, D1.mass,
                D2.x, D2.y, D2.vx, D2.vy);}

bool collision(Ball  D1,Ball D2){ return collision(D1.x, D1.y, D1.vx, D1.vy, D1.r,
              D2.x, D2.y, D2.vx, D2.vy, D2.r);}

void shock(Ball & D1,Ball &D2){
    shock(D1.x,  D1.y, D1.vx,  D1.vy,  D1.mass,
          D2.x, D2.y, D2.vx, D2.vy, D2.mass);}

/////////////////////////////////////////////
int main()
{
    openWindow(width, height);
    initRandom();

    //****************** INITIALISATION *******************
    double x = width/10., y = height* 9. / 10;
    double vx = 0.5, vy = 0.5;
    double r = 3;
    Color col = RED;
    double mass=1;
    Ball D={x,y,vx,vy,r,col,mass}; 
    DisplayBall(Sun);
    //******* Save position for display ********
    double ox = x, oy = y;
    //****** Main loop ******
    Ball Oldball={ox,oy,vx,vy,r,col,mass};
    int s=0;
    for(int timeStep=0; timeStep<10000*freqDisplay; timeStep++) {
        //******** Display ************
        if ((timeStep%freqDisplay)==0){
            noRefreshBegin();
            EraseBall(Oldball);
            DisplayBall(D);
            ox=D.x;oy= D.y;
            Oldball={ox,oy,vx,vy,r,col,mass};
            noRefreshEnd();
            milliSleep(50);
        }
        if (collision( D,Sun)){shockSimple(D,Sun);
            s+=1;}
        Modify_speed(D);
        Deplacer_Ball(D);
        if (!(D.x >= 0 && D.x + D.r <= width && D.y >= 0 && D.y + D.r<= height)) {break;}
        if(s==5 ){break;}
        cout <<  " Faites un clic droit pour continuer..." << endl;
        cin.get();
    }
    endGraphics();
    return 0;
}
