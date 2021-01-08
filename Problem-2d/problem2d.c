//
//  	problem2d.c
//
//	Created by Alexandros Alexiou, Petros Karampas, Nikos Amvazas.
//
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// Constants
#define M       1.5
#define AM      2987
#define zpar0   0
#define Kpz     5
#define Kdz     15
#define h       0.001


//globals
double fz;
double z0    = 0.0;
double Cz    = 4 - ((double)AM / 5000);
double z_des = (double)AM / 200;

//Macros
//#define fx(t, x, y) (y)
//#define fy(t, x, y) (((((Kpz) * ((z_des) - (x))) - ((Kdz) * (y)) - ((Cz) * (y)))/(M)))

//prototypes
void createPlotData(double y[], double t[], char* filename, char* commands[]);
double fx(double t, double x, double y);
double fy(double t, double x, double y);

int main(int argc, char * argv[]){
    int i;
    /*--------------- Analytical solution of the differential equation-------------*/
    double dif[30001];
    double t[30001];
    
    double time = 0.0;

    for(i = 0; i<=30000; i++, time+=h){
        dif[i] = -15.2894903563 * exp(-0.27800018214 * time) + 0.35449035632 * exp(-11.9903998179 * time) + 14.935;
        t[i] = time;
    }

    
    /*--------------- Euler's method ---------------*/
    double z [30001];
    double y [30001];
    double x_n = z0;
    double y_n = zpar0;
    
    time = 0.0;
    
    for(i = 0; i<=30000; i++, time+=h){
        z[i] = x_n;
        y[i] = y_n;
        x_n  = x_n + h * fx(time, x_n, y_n);
        y_n  = y_n + h * fy(time, x_n, y_n);
    }

    /*--------------- Improved Euler's Method --------------*/
    double z_improved [30001];
    double y_improved [30001];

    time = 0.0;

    x_n = z0;
    y_n = zpar0;

    for (i = 0; i<=30000; i++, time+=h){
        z_improved[i] = x_n;
        y_improved[i] = y_n;
        
        x_n = x_n + (h/2) * ( fx( time, x_n, y_n) + fx( time+h, x_n + h * fx(time, x_n, y_n), y_n + h * fy(time, x_n, y_n) )  );
        y_n = y_n + (h/2) * ( fy( time, x_n, y_n) + fy( time+h, x_n + h * fx(time, x_n, y_n), y_n + h * fy(time, x_n, y_n) )  );
    }

    
    /*--------------- Plotting ---------------*/

    // plotting for differential equation z
    char * commandsForGnuplot[] = {"set title \"Differential Equation\"", "set xlabel \"time\"", "set ylabel \"displacement\"", "plot '../plots/differential.txt' lt rgb \"red\" with lines"};
    createPlotData(dif, t, "../plots/differential.txt", commandsForGnuplot);

    // plotting for euler's method z and y
    commandsForGnuplot[0]="set title \"Euler's method for z\"";
    commandsForGnuplot[2]="set ylabel \"displacement\"";
    commandsForGnuplot[3]="plot '../plots/euler_method_z_2d.txt' lt rgb \"red\" with lines";
    createPlotData(z, t, "../plots/euler_method_z_2d.txt", commandsForGnuplot);
    
    commandsForGnuplot[0]="set title \"Euler's method for y\"";
    commandsForGnuplot[2]="set ylabel \"velocity\"";
    commandsForGnuplot[3]="plot '../plots/euler_method_y_2d.txt' lt rgb \"blue\" with lines";
    createPlotData(y, t, "../plots/euler_method_y_2d.txt", commandsForGnuplot);

    //plotting for improved euler's method z and y
    commandsForGnuplot[0]="set title \"Improved Euler's method z\"";
    commandsForGnuplot[2]="set ylabel \"displacement\"";
    commandsForGnuplot[3]="plot '../plots/improved_euler_method_z_2d.txt' lt rgb \"red\" with lines";
    createPlotData(z_improved, t, "../plots/improved_euler_method_z_2d.txt", commandsForGnuplot);

    commandsForGnuplot[0]="set title \"Improved Euler's method for y \"";
    commandsForGnuplot[2]="set ylabel \"velocity\"";
    commandsForGnuplot[3]="plot '../plots/improved_euler_method_y_2d.txt' lt rgb \"blue\" with lines";
    createPlotData(y_improved, t, "../plots/improved_euler_method_y_2d.txt", commandsForGnuplot);

    return 0;
}

// create data and open a pipe to the gnuplot programm and feed it commands to create the plots
void createPlotData(double y[], double t[], char* filename, char* commands[]) {
    FILE * gnuplotPipe = popen ("gnuplot -persistent", "w");
    FILE *fp=NULL;
    fp=fopen(filename,"w");

    for(int i = 0; i<=30000; i++) {
        fprintf(fp,"%.3lf\t %lf\n", t[i], y[i]);
    }
    
    for (int i=0; i < 4; i++)
    {
        fprintf(gnuplotPipe, "%s \n", commands[i]); //Send commands to gnuplot one by one.
    }
}

double fx(double t, double x, double y){
    return y;
}

double fy(double t, double x, double y){
    return (Kpz * (z_des - x) - Kdz * y - (Cz * y))/M;
}
