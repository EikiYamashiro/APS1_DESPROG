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

int left(point p, point a, point b){
    double m = (double)(a.y - b.y)/(a.x - b.x);
    double b_intercept = a.y - m*a.x;
    double x = (p.y - b_intercept)/m;
    int y_min = a.y;
    if (a.y > b.y){y_min = b.y;}

    if(a.y == b.y){
        return 0;
    } 
    if(a.x == b.x && a.x > p.x && between(p.y, a.y, b.y)){
        if (fabs(p.y-y_min) < dif){
            return 0;
        }
        return 1;
    } 
    if (p.x < x && between(p.y, a.y, b.y)){
        if (fabs(p.y-y_min) < dif){
            return 0;
        }
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
    if (left(p, a, b)){
        return 1;
    }
    return 0;
}

int inside(point p, point poly[], int n) {

    int v;
    int walls = 0;

    for (int i=0; i<n; i++){

        if (i==n-1){
            v = verify(p, poly[0], poly[n-1]);
        } else {
            v = verify(p, poly[i], poly[i+1]);
        }

        if (v==2) {
            return 1;
        }
        if (v==1){
            walls++;
        }
    }
    if (walls%2 != 0) {
        return 1;
    }
    return 0;
}
