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
{
    Window window=openWindow(width, height);
    initRandom();
    Ball list_obj[12];
    double xs;
    double ys;
    double rs;
    Vector pos ={ width/8,height *0.4};
    Vector vitesse={ 5, 10};
    double r = 1;
    Color col = RED;
    double mass=10;
    Ball Player1 ={{pos.x,pos.y},vitesse,r*10,BLUE,mass};
    Ball Player2 ={{width-pos.x,pos.y},vitesse,r*10,GREEN,mass};
    list_obj[10]=Player1,list_obj[11]=Player2;
    DisplayBall(Player1);
    DisplayBall(Player2);
    xs=  intRandom( 0, width);
    ys=  intRandom( 0, height);
    rs= intRandom(5, 15);
    Ball Sun={{xs,ys},{0,0},rs,YELLOW,rs*50};
    for (int i=0 ; i<10;i++){
        while((verif(Sun,list_obj,i)==false)){xs=  intRandom( 0, width);
            ys=  intRandom( 0, height);
            rs= intRandom(5, 15);
            Sun={{xs,ys},{0,0},rs,YELLOW,rs*50};}
        if (verif(Sun,list_obj,i)){list_obj[i]=Sun;
            DisplayBall(list_obj[i]);}       
    }  
    //****************** INITIALISATION *******************
    Ball ActivePlayer;
    Ball OtherPlayer;
    int s=0;
    int x;
    int y;

    while (true){
        if (s % 2==0){ActivePlayer=Player1;
            OtherPlayer=Player2;
            int v= getMouse(x,y);
            s++;
            double ox = ActivePlayer.pos.x+ActivePlayer.r*1.5, oy = ActivePlayer.pos.y;
            Vector vitesse ={0.00025*(x-ActivePlayer.pos.x),0.00025*(y-ActivePlayer.pos.y)};
            double r=1;
            double massmissile=5;
            Ball Missile ={{ox,oy},vitesse,r,RED,massmissile};
            Ball Oldball=Missile;
            int n=0;
            for(int timeStep=0; timeStep<10000*freqDisplay; timeStep++) {
                //******** Display ************
                if ((timeStep%freqDisplay)==0){
                    noRefreshBegin();
                    DisplayBall(Oldball);
                    DisplayBall(
                        Missile);
                    ox=Missile.pos.x;oy= Missile.pos.y;
                    Oldball={{ox,oy},vitesse,r*0.5,RED,mass};
                    noRefreshEnd();
                    milliSleep(50);
                }
                for (int i=0;i<12;i++)
                {Modify_speed(Missile,list_obj[i]);}

                Deplacer_Ball(Missile);
                if (!(Missile.pos.x >= 0 && Missile.pos.x + Missile.r <= width && Missile.pos.y >= 0 && Missile.pos.y + Missile.r<= height)) {break;}

                if (collision( Missile, OtherPlayer)){cout << "attack successful  Player1 wins" << endl;
                    break;}
                for (int i=0;i<12;i++)
                {
                    if (collision( Missile,list_obj[i])){if (i!=10){ shockSimple(
                                Missile,list_obj[i]);
                            n+=1;}}}
                if(n==5 ){break; }
                if(timeStep==1000){
                    break;}}
            if (s % 2==1){ActivePlayer=Player2;
                OtherPlayer=Player1;
                int v= getMouse(x,y);
                s++;
                ox = ActivePlayer.pos.x-ActivePlayer.r*1.5, oy = ActivePlayer.pos.y;
                vitesse ={0.00025*(x-ActivePlayer.pos.x),0.00025*(y-ActivePlayer.pos.y)};

                Ball Missile ={{ox,oy},vitesse,r,RED,mass};
                Ball Oldball=Missile;
                int n=0;
                for(int timeStep=0; timeStep<10000*freqDisplay; timeStep++) {
                    //******** Display ************
                    if ((timeStep%freqDisplay)==0){
                        noRefreshBegin();
                        DisplayBall(Oldball);
                        DisplayBall(
                            Missile);
                        ox=Missile.pos.x;oy= Missile.pos.y;
                        Oldball={{ox,oy},vitesse,r*0.5,RED,mass};
                        noRefreshEnd();
                        milliSleep(50);
                    }
                    for (int i=0;i<12;i++){if(i!=11)
                        {Modify_speed(Missile,list_obj[i]);}}

                    Deplacer_Ball(Missile);
                    if (!(Missile.pos.x >= 0 && Missile.pos.x + Missile.r <= width && Missile.pos.y >= 0 && Missile.pos.y + Missile.r<= height)) {break;
                    }
                    if (collision( Missile, OtherPlayer)){cout << "attack successful  Player2 wins" << endl;
                        break;
                    }
                    for (int i=0;i<12;i++)
                    {
                        if (collision( Missile,list_obj[i])){if (i!=11){shockSimple(
                                    Missile,list_obj[i]);
                                n+=1;}}}
                    if(n==5 ){break;}
                    if(timeStep==3000){break;}
                }}
        }
    }
    endGraphics();
    return 0;
}

