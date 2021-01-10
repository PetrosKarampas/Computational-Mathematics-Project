//
//  problem1b.c
//  Computational Mathematics Project
//
//  Created by Alexandros Alexiou, Petros Karampas, Nikos Amvazas.
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
#define psi0    0
#define zpar0   0
#define psipar0 0
#define h       0.001

// globals
double fz;
double tz;
double z0   = (double)AM / 1000;
double Cz   = 3.0-((double)AM / 5000);
double Cpsi = 5.0-((double)AM / 5000);

//Macros
//#define fx(t, x, y) (y)
//#define fy(t, x, y) (((fz) - (g * M) - ((Cz) * fabs(y) * (y)))/M)
//#define fw(t, w, u) (u)
//#define fu(t, w, u) (((tz) - (0.5 * (Cpsi) *  (fabs(u)) * (u)))/Iz)

//prototypes
void createPlot(double y[], double t[], char* filename, char* commands[]);
double fx(double t, double x, double y);
double fy(double t, double x, double y);
double fw(double t, double w, double u);
double fu(double t, double w, double u);

int main(int argc, const char* argv[]) {
    
    if (argc < 2) {
        printf("Please pass 1 or 2 for the two different inputs (fz, tz)\n");
        return 1;
    }
    
    if( atoi(argv[1]) == 1){
        fz = (M*g) + ((double)AM/1000);
        tz = 0;
    }else if(atoi(argv[1]) == 2) {
        fz = M*g;
        tz = (double)AM/10000;
    }
    
    /*--------------- Euler's Method --------------*/
    double x [30001];
    double y [30001];
   
    double w [30001];
    double u [30001];
    
    double t [30001];
    double time = 0.0;
    
    x[0] = z0;
    y[0] = zpar0;
    
    w[0] = psi0;
    u[0] = psipar0;

    t[0] = 0.0;
    time+= h;

    for(int i = 0; i<30000; i++, time+=h ) {
        
        x[i+1] = x[i] + h * fx(time, x[i], y[i]);
        y[i+1] = y[i] + h * fy(time, x[i], y[i]);
        
        w[i+1] = w[i] + h * fw(time, w[i], u[i]);
        u[i+1] = u[i] + h * fu(time, w[i], u[i]);
        
        t[i+1] = time;
    }
    /*----------------------------------------------*/
    
    
    /*--------------- Improved Euler's Method --------------*/
    double x_imp [30001];
    double y_imp [30001];
    
    double w_imp [30001];
    double u_imp [30001];
    
    time = 0.0;
    
    x_imp[0] = z0;
    y_imp[0] = zpar0;
    
    w_imp[0] = psi0;
    u_imp[0] = psipar0;
    
    for(int i = 0; i<30000; i++, time+=h ) {
        
        x_imp[i+1] = x_imp[i] + (h/2) * ( fx( time, x_imp[i], y_imp[i]) + fx( time+h, x_imp[i] + h * fx(time, x_imp[i], y_imp[i]), y_imp[i] + h * fy(time, x_imp[i], y_imp[i]) )  );
        y_imp[i+1] = y_imp[i] + (h/2) * ( fy( time, x_imp[i], y_imp[i]) + fy( time+h, x_imp[i] + h * fx(time, x_imp[i], y_imp[i]), y_imp[i] + h * fy(time, x_imp[i], y_imp[i]) )  );
        
        w_imp[i+1] = w_imp[i] + (h/2) * ( fw( time, w_imp[i], u_imp[i]) + fw( time+h, w_imp[i] + h * fw(time, w_imp[i], u_imp[i]), u_imp[i] + h * fu(time, w_imp[i], u_imp[i]) )  );
        u_imp[i+1] = u_imp[i] + (h/2) * ( fu( time, w_imp[i], u_imp[i]) + fu( time+h, w_imp[i] + h * fw(time, w_imp[i], u_imp[i]), u_imp[i] + h * fu(time, w_imp[i], u_imp[i]) )  );
    
    }
    /*----------------------------------------------*/


    /*--------------- Plotting --------------*/
    if( atoi(argv[1]) == 1){
        // plotting for euler method and improved euler for z and psi
        char * commandsForGnuplot[] = {"set title \"Euler's method for z (input 1)\"", "set xlabel \"time\"", "set ylabel \"displacement\"", "plot '../plots/euler_method_z_input1.txt' lt rgb \"red\" with lines"};
        createPlot(x, t, "../plots/euler_method_z_input1.txt", commandsForGnuplot);

        commandsForGnuplot[0] ="set title \"Improved Euler's method for z (input 1)\"";
        commandsForGnuplot[3] ="plot '../plots/improved_euler_method_z_input1.txt' lt rgb \"red\" with lines";
        createPlot(x_imp, t, "../plots/improved_euler_method_z_input1.txt", commandsForGnuplot);

        commandsForGnuplot[0] ="set title \"Euler's method for Psi (input 1)\"";
        commandsForGnuplot[3] ="plot '../plots/euler_method_Psi_input1.txt' lt rgb \"blue\" with lines";
        commandsForGnuplot[2] ="set ylabel \"orientation\"";
        createPlot(w, t, "../plots/euler_method_Psi_input1.txt", commandsForGnuplot);
        
        commandsForGnuplot[0] ="set title \"Improved Euler's method for Psi (input 1)\"";
        commandsForGnuplot[3] ="plot '../plots/improved_euler_method_Psi_input1.txt' lt rgb \"blue\" with lines";
        commandsForGnuplot[2] ="set ylabel \"orientation\"";
        createPlot(w_imp, t, "../plots/improved_euler_method_Psi_input1.txt", commandsForGnuplot);
        
        
    }else if(atoi(argv[1]) == 2) {
        char * commandsForGnuplot[] = {"set title \"Euler's method for z (input 2)\"", "set xlabel \"time\"", "set ylabel \"displacement\"", "plot '../plots/euler_method_z_input2.txt' lt rgb \"red\" with lines"};
        createPlot(x, t, "../plots/euler_method_z_input2.txt", commandsForGnuplot);

        commandsForGnuplot[0] ="set title \"Improved Euler's method for z (input 2)\"";
        commandsForGnuplot[3] ="plot '../plots/improved_euler_method_z_input2.txt' lt rgb \"red\" with lines";
        createPlot(x_imp, t, "../plots/improved_euler_method_z_input2.txt", commandsForGnuplot);

        commandsForGnuplot[0] ="set title \"Euler's method for Psi (input 2)\"";
        commandsForGnuplot[3] ="plot '../plots/euler_method_Psi_input2.txt' lt rgb \"blue\" with lines";
        commandsForGnuplot[2] ="set ylabel \"orientation\"";
        createPlot(w, t, "../plots/euler_method_Psi_input2.txt", commandsForGnuplot);
        
        commandsForGnuplot[0] ="set title \"Improved Euler's method for Psi (input 2)\"";
        commandsForGnuplot[3] ="plot '../plots/improved_euler_method_Psi_input2.txt' lt rgb \"blue\" with lines";
        commandsForGnuplot[2] ="set ylabel \"orientation\"";
        createPlot(w_imp, t, "../plots/improved_euler_method_Psi_input2.txt", commandsForGnuplot);
    }
    return 0;
    /*----------------------------------------------*/
}

// create data and open a pipe to the gnuplot programm and feed it commands to create the plots
void createPlot(double y[], double t[], char* filename, char* commands[]) {
    FILE * gnuplotPipe = popen ("gnuplot -persistent", "w");
    FILE *fp=NULL;
    fp=fopen(filename,"w");

    for(int i = 0; i<=30000; i++) {
        fprintf(fp,"%lf\t %.10lf\n", t[i], y[i]);
    }
    
    for (int i=0; i < 4; i++){
        fprintf(gnuplotPipe, "%s \n", commands[i]); //Send commands to gnuplot one by one.
    }
}

double fx(double t, double x, double y){
    return (y);
}

double fy(double t, double x, double y){
    return (fz - (g * M) - (Cz * fabs(y) * y))/M;
}

double fw(double t, double w, double u){
    return (u);
}

double fu(double t, double w, double u){
    return (tz - (0.5 * Cpsi *  fabs(u) * u))/Iz;
}
