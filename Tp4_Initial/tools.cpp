#include <Imagine/Graphics.h>
#include "tools.h"
#include "vector.h"
#include <iostream>
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
    const double collision_margin = 0.9;
    return ((dx*dx + dy*dy) <= (collision_margin * r * r));
}

void DisplayBall (Ball D){ fillCircle(D.pos.x,D.pos.y,D.r,D.color);}

void EraseBall(Ball D){ fillCircle(D.pos.x,D.pos.y,D.r,WHITE);}

void Deplacer_Ball(Ball  & D){
    D.pos = D.pos + D.v * dt;    
}
void Modify_speed( Ball & D,Ball Sun) {
    double r=sqrt((D.pos.x-Sun.pos.x)*(D.pos.x-Sun.pos.x)+(D.pos.y-Sun.pos.y)*(D.pos.y-Sun.pos.y));
    if (r>= D.r+Sun.r){
        D.v=D.v+Sun.mass*dt*(D.pos-Sun.pos)*(-1/pow(r,3));}
}

void shock(Ball & D1,Ball &D2){
    shock(D1.pos.x,  D1.pos.y, D1.v.x,  D1.v.y,  D1.mass,
          D2.pos.x, D2.pos.y, D2.v.x, D2.v.y, D2.mass);}

void shockSimple( Ball & D1,Ball D2){shockSimple(D1.pos.x,  D1.pos.y,  D1.v.x, D1.v.y, D1.mass,
                D2.pos.x, D2.pos.y, D2.v.x, D2.v.y);}

bool collision(Ball  D1,Ball D2){return collision(D1.pos.x, D1.pos.y, D1.v.x, D1.v.y, D1.r,
              D2.pos.x, D2.pos.y, D2.v.x, D2.v.y, D2.r);}

void failure(){cout <<"attack failed click to go to the next round"<< endl;}

bool verif(Ball D, Ball list[12], int i) {
    double r1_sq = (D.pos.x - list[10].pos.x) * (D.pos.x - list[10].pos.x) +
                   (D.pos.y - list[10].pos.y) * (D.pos.y - list[10].pos.y);
    double r2_sq = (D.pos.x - list[11].pos.x) * (D.pos.x - list[11].pos.x) +
                   (D.pos.y - list[11].pos.y) * (D.pos.y - list[11].pos.y);
    if (r1_sq < 10000 || r2_sq < 10000) return false;
    for (int j = 0; j < i; j++) {
        double r3_sq = (D.pos.x - list[j].pos.x) * (D.pos.x - list[j].pos.x) +
                       (D.pos.y - list[j].pos.y) * (D.pos.y - list[j].pos.y);
        double min_dist_sq = (D.r + list[j].r) * (D.r + list[j].r);
        if (r3_sq < min_dist_sq) return false;
    }

    return true;
}

