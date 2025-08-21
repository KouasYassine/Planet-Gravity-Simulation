#include "vector.h"
#include<cmath>
Vector operator+(Vector  a, Vector b){return(Vector{a.x+b.x,a.y+b.y});}

Vector operator-(Vector a, Vector b){return(Vector{a.x-b.x,a.y-b.y});}

double norm2(Vector a){return(sqrt(a.x*a.x+a.y*a.y));}

Vector operator*(Vector a, double lambda){return(Vector{lambda*a.x,lambda*a.y});}

Vector operator*(double lambda , Vector a){return(a*lambda);}
