//
//  main.c
//  Computational Mathematics Project
//
//  Created by Alexandros Alexiou on 25/12/20.
//
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Constants
#define M       1
#define Iz      0.08
#define g       9.81
#define AM      2987
#define tz      0
#define psi0    0
#define zpar0   0
#define psipar0 0
#define h       0.001

// globals
double fz = (M*g) + ((double)AM/1000);
double z0 = (double)AM/1000;
double Cz = 3.0-((double)AM/5000);
double Cpsi = 5.0-((double)AM/5000);

//Macros
#define fx(t, x, y) (y)
#define fy(t, x, y) ((fz - (g * M) - (Cz * fabs(y) * y))/M)
#define fw(t, w, u) (u)
#define fu(t, w, u) ((tz - (0.5 * Cpsi *  fabs(u) * u))/Iz)

//prtotypes
void createPlotData(double y[], double t[], char * filename);


int main(){
    double y [30002];
    double y2 [30002];
    double t [30002];
    double time = 0.0;
    double y_x_1 = z0;
    double y_y_1 = zpar0;
    
    double y_w_1 = psi0;
    double y_u_1 = psipar0;
    
    for(int i = 1; i<=30001; i++, time+=h ) {
        
        y[i] = y_x_1;
        y_x_1 = y_x_1 + h * fx(time, y[i], y_y_1);
        y_y_1 = y_y_1 + h * fy(time, y[i], y_y_1);
        
        y2[i] = y_w_1;
        y_w_1 = y_w_1 + h * fw(time, y2[i], y_u_1);
        y_u_1 = y_u_1 + h * fu(time, y2[i], y_u_1);
        
        t[i] = time;
    }

//    int i;
//    for (i=0; i < (sizeof (y2) /sizeof (y2[0])); i++) {
//        printf("%lf\n",y2[i]);
//    }
    createPlotData(y, t, "euler_method_z.txt");
    createPlotData(y2, t, "euler_method_y.txt");
    return 0;
}


void createPlotData(double y[], double t[], char * filename) {
    FILE *fp=NULL;
    fp=fopen(filename,"w");

    for(int i = 1; i<=30001; i++) {
        fprintf(fp,"%lf\t %lf\n",t[i],y[i]);
    }
}
