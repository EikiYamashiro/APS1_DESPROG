#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "geometry.h"

double dif = 0.00000000001;


int between(int p, int a, int b){
    int min = a, max = b;
    if (a>b){
        min = b;
        max = a;
    }
    if((abs(p - min) < dif || p > min) && (abs(p - max) < dif || p < max)){
        return 1;
    }
    return 0;
}

int left(int p, int a, int b){
    int max = b;
    if (a>b){
        max = a;
    }
    if (p < max){
        return 1;
    }
    return 0;
}

int on_line(point p, point a, point b){
    double m = (double)(a.y - b.y)/(a.x - b.x);
    double b_intercept = a.y - m*a.x;
    double y = m*p.x + b_intercept;
    double x = (p.y - b_intercept)/m;

    if(a.y == b.y && a.y == p.y && between(p.x, a.x, b.x)){
        return 1;
    } 
    if(a.x == b.x && a.x == p.x && between(p.y, a.y, b.y)){
        return 1;
    } 
    if((fabs(p.y - y) < dif) && (fabs(p.x - x) < dif) && between(p.x, a.x, b.x) && between(p.y, a.y, b.y)){
        return 1;
    }
    return 0;
}

int verify(point p, point a, point b) {

    if (on_line(p,a,b)){
        return 2;
    }
    if (between(p.y, a.y, b.y) && left(p.x, a.x, b.x)){
        return 1;
    }
    return 0;
}

int inside(point p, point poly[], int n) {

    int v;

    for (int i=0; i<=n; i++){

        if (i==n){
            v = verify(p, poly[i], poly[0]);
        } else {
            v = verify(p, poly[i], poly[i+1]);
        }

        if (v==0) {
            return 0;
        }
        else if (v==1){

        }
        else {
            return 1;
        }

    }

    return 0;
}
