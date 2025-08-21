// Imagine++ project
// Project:  Tp4_Initial
// Student(s): Yassine KOUAS

#include <Imagine/Graphics.h>
#include "tools.h"
#include"vector.h"
#include <list>
using namespace Imagine;
#include <iostream>
#include <cmath>
#include <ctime>
using namespace std;
/////////////////////////////////////////////
int main()
{   Window window=openWindow(width, height);
    initRandom();
    Ball list_obj[11];
    double xs;
    double ys;
    double rs;
    double vxs;
    double vys;

    for (int i=0 ; i<10;i++){xs=  intRandom( 0, width);
        ys=  intRandom( 0, height);
        rs= intRandom(5, 15);
        vxs=intRandom(-5, 5);
        vys=intRandom(-5,5);
        Ball Sun={{xs,ys},{vxs,vys},rs,YELLOW,rs*1000/20};
        list_obj[i]=Sun;
    }
    //****************** INITIALISATION *******************
    Vector pos ={ width/10.,height* 9. / 10};
    Vector vitesse={0.5, 0.5};
    double r = 3;
    Color col = RED;
    double mass=100;
    Ball planet={{pos.x,pos.y},vitesse,r,col,mass};
    list_obj[10]=planet;
    Ball Oldball;
    int shocks[11];
    for(int timeStep=0; timeStep<100000*freqDisplay; timeStep++) {
        int s=0;
        if ((timeStep%freqDisplay)==0){
            noRefreshBegin();
            for (int j=0;j<11;j++){
                Oldball = list_obj[j];
                for (int i=0;i<11;i++){
                    if (i != j) {
                        if (collision(list_obj[j], list_obj[i]) ) {
                            shock(list_obj[i], list_obj[j]);
                            if (j==10){s+=1;}
                        }
                        Modify_speed(list_obj[j], list_obj[i]);
                    }
                }
                Deplacer_Ball(list_obj[j]);
                EraseBall(Oldball);
                DisplayBall(list_obj[j]);
            }
            noRefreshEnd();
            milliSleep(1);
        }
        planet=list_obj[10];
        if (!(planet.pos.x-planet.r>= 0 && planet.pos.x + planet.r <= width && planet.pos.y >= 0 && planet.pos.y + planet.r<= height)) {break;}
        if(s==5){break;}
    }
    endGraphics();
    return 0;
}





