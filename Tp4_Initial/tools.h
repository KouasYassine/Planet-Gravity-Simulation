#pragma once
#include <Imagine/Graphics.h>
#include"vector.h"
#include <list>
using namespace Imagine;
#include <iostream>
#include <cmath>
#include <ctime>
using namespace std;
const double dt = 0.2;
const int width = 512;
const int height =512;
const int freqDisplay =10;
struct Ball{ Vector pos; Vector v;double r; Color color;double mass;};
void shock(double x,  double y,  double &vx,  double &vy,  double m,double x2, double y2, double &vx2, double &vy2, double m2);
void shockSimple(double x,  double y,  double &vx, double &vy, double m,double x2, double y2, double vx2, double vy2) ;
bool collision(double x1, double y1, double vx1, double vy1, double r1,double x2, double y2, double vx2, double vy2, double r2);
void DisplayBall (Ball D);
void EraseBall(Ball D);
void Deplacer_Ball(Ball  & D);
void Modify_speed( Ball & D,Ball Sun);
void shock(Ball & D1,Ball &D2);
void shockSimple( Ball & D1,Ball D2);
bool collision(Ball  D1,Ball D2);
void failure();
bool verif(Ball D,Ball list[12],int i);


