//
//  problem1d.c
//  Problem-1d
//
//  Created by Alexandros Alexiou,Petros Karampas, Nikos Amvazas.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Constants
#define M       1
#define Iz      0.08
#define g       9.81
#define AM      2987
#define z0      0
#define zpar0   0
#define psipar0 0
#define Kpz     5
#define Kp_psi  5
#define Kd_psi  20
#define Cpsi    5
#define h       0.001

// globals
double psi0 = (double)AM/10000;
double z_des = (double)AM/200;
double psi_des = (double)-AM/3000;
double Cz = 3 + (double)AM/5000;
double Kdz = 15 + (double)AM/1000;

//Macros
#define fx(t, x, y) (y)
#define fy(t, x, y) ( (Kpz * (z_des - x) - Kdz * y - Cz * fabs(y) * y )/M)
#define fw(t, w, u) (u)
#define fu(t, w, u) ( (Kp_psi * (psi_des-w) - Kd_psi * u - 0.5 * Cpsi * fabs(u) * u )/Iz)

//prtotypes
void createPlotData(double y[], double t[], char* filename, char* commands[]);


int main(int argc, const char * argv[]) {
    /*--------------- Euler's Method --------------*/
    double z [30001];
    double y [30001];
    double t [30001];
    double time = 0.0;
    double x_n = z0;
    double y_n = zpar0;
    
    double w_n = psi0;
    double u_n = psipar0;
    
    for(int i = 0; i<=30000; i++, time+=h ) {
        
        z[i] = x_n;
        x_n  = x_n + h * fx(time, x_n, y_n);
        y_n  = y_n + h * fy(time, x_n, y_n);
        
        y[i] = w_n;
        w_n  = w_n + h * fw(time, w_n, u_n);
        u_n  = u_n + h * fu(time, w_n, u_n);
        
        t[i] = time;
    }
    
    /*--------------- Improved Euler's Method --------------*/
    double z_improved [30001];
    double y_improved [30001];
    
    time = 0.0;
    
    x_n = z0;
    y_n = zpar0;
    
    w_n = psi0;
    u_n = psipar0;
    
    for(int i = 0; i<=30000; i++, time+=h ) {
        
        z_improved[i] = x_n;
        x_n = x_n + (h/2) * ( fx( time , x_n, y_n) + fx( time+h, x_n + h * fx(time, x_n, y_n), y_n + h * fy(time, x_n, y_n) )  );
        y_n = y_n + (h/2) * ( fy( time , x_n, y_n) + fy( time+h, x_n + h * fx(time, x_n, y_n), y_n + h * fy(time, x_n, y_n) )  );
        
        y_improved[i] = w_n;
        w_n = w_n + (h/2) * ( fw( time , w_n, u_n) + fw( time+h, w_n + h * fw(time, w_n, u_n), u_n + h * fu(time, w_n, u_n) )  );
        u_n = u_n + (h/2) * ( fu( time , w_n, u_n) + fu( time+h, w_n + h * fw(time, w_n, y_n), u_n + h * fu(time, w_n, u_n) )  );
    
    }
    /*----------------------------------------------*/
    
    
    /*--------------------plotting--------------------------*/
    
    // plotting for euler method z and psi
    char * commandsForGnuplot[] = {"set title \"Euler's method for z\"", "set xlabel \"time\"", "set ylabel \"displacement\"", "plot '../plots/euler_method_z.txt' lt rgb \"red\" with lines"};
    createPlotData(z, t, "../plots/euler_method_z.txt", commandsForGnuplot);
    
    commandsForGnuplot[0]="set title \"Euler's method for Psi\"";
    commandsForGnuplot[2]="set ylabel \"orientation\"";
    commandsForGnuplot[3]="plot '../plots/euler_method_Psi.txt' lt rgb \"blue\" with lines";
    createPlotData(y, t, "../plots/euler_method_Psi.txt", commandsForGnuplot);
    
    // plotting for improved euler method z and psi
    commandsForGnuplot[0]="set title \"Improved Euler's method z\"";
    commandsForGnuplot[2]="set ylabel \"displacement\"";
    commandsForGnuplot[3]="plot '../plots/improved_euler_method_z.txt' lt rgb \"red\" with lines";
    createPlotData(z_improved, t, "../plots/improved_euler_method_z.txt", commandsForGnuplot);
    
    commandsForGnuplot[0]="set title \"Improved Euler's method for Psi\"";
    commandsForGnuplot[2]="set ylabel \"orientation\"";
    commandsForGnuplot[3]="plot '../plots/improved_euler_method_Psi.txt' lt rgb \"blue\" with lines";
    createPlotData(y_improved, t, "../plots/improved_euler_method_Psi.txt", commandsForGnuplot);

    return 0;
}


// create data and open a pipe to the gnuplot programm and feed it commands to create the plots
void createPlotData(double y[], double t[], char* filename, char* commands[]) {
    FILE * gnuplotPipe = popen ("gnuplot -persistent", "w");
    FILE *fp=NULL;
    fp=fopen(filename,"w");

    for(int i = 0; i<=30000; i++) {
        fprintf(fp,"%lf\t %lf\n", t[i], y[i]);
    }
    
    for (int i=0; i < 4; i++)
    {
        fprintf(gnuplotPipe, "%s \n", commands[i]); //Send commands to gnuplot one by one.
    }
}
