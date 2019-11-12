
#include <stdio.h>
#include <stdlib.h>
#include <math.h> 
#define NSTEPS 80
#define pi 3.14f


typedef struct 
{
    // a struct that has 2 elements, x and y
    double x, y;
    double ploty;
} points;



int main(int argc, char ** argv){
    char frameBuffer[NSTEPS][10];
    float step = (float) 4*pi/NSTEPS;
    points pts[NSTEPS] = {[0 ... NSTEPS-1].x=0};    
    float temp=0;

    for (int i=0; i<NSTEPS; i++){
        pts[i].x = (float)temp + step;
        temp += step; 
    }

    for (int i=0; i<NSTEPS; i++){
        pts[i].y = (double)sin((double) pts[i].x); 
        pts[i].ploty = (pts[i].y + 1)*9/2;
    }


    for (int i=0; i<NSTEPS; i++) {
        for (int j=0; j<10; j++) {
            frameBuffer[i][j] = ' ';
            if (round(pts[i].ploty)==j){
                frameBuffer[i][j] = '*';
            }
        }     
    }

    for (int i = 0; i<10; i++) {
        printf("\n");
        for (int j = 0; j<NSTEPS; j++) {
            printf("%c",frameBuffer[j][i]);
        }
    }
    return 0;
}