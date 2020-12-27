//
//  problem1b.c
//  Computational Mathematics Project
//
//  Created by Alexandros Alexiou on 25/12/20.
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
double z0 = (double)AM/1000;
double Cz = 3.0-((double)AM/5000);
double Cpsi = 5.0-((double)AM/5000);

//Macros
#define fx(t, x, y) (y)
#define fy(t, x, y) ((fz - (g * M) - (Cz * fabs(y) * y))/M)
#define fw(t, w, u) (u)
#define fu(t, w, u) ((tz - (0.5 * Cpsi *  fabs(u) * u))/Iz)

//prtotypes
void createPlotData(double y[], double t[], char* filename, char* commands[]);


int main(int argc, const char* argv[]) {
    
    if (argc < 2) {
        printf("Please pass 1 or 2 for the two different inputs (fz, tz)");
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
    double z [30001];
    double y [30001];
    double t [30001];
    double time = 0.0;
    double y_x_1 = z0;
    double y_y_1 = zpar0;
    
    double y_w_1 = psi0;
    double y_u_1 = psipar0;
    
    for(int i = 0; i<=30000; i++, time+=h ) {
        
        z[i] = y_x_1;
        y_x_1 = y_x_1 + h * fx(time, z[i], y_y_1);
        y_y_1 = y_y_1 + h * fy(time, z[i], y_y_1);
        
        y[i] = y_w_1;
        y_w_1 = y_w_1 + h * fw(time, y[i], y_u_1);
        y_u_1 = y_u_1 + h * fu(time, y[i], y_u_1);
        
        t[i] = time;
    }
    /*----------------------------------------------*/
    
    
    /*--------------- Improved Euler's Method --------------*/
    double z_improved [30001];
    double y_improved [30001];
    
    time = 0.0;
    
    double y_a_ve = z0;
    double y_b_ve = zpar0;
    
    double y_c_ve = psi0;
    double y_d_ve = psipar0;
    
    for(int i = 0; i<=30000; i++, time+=h ) {
        
        z_improved[i]=y_a_ve;
        y_a_ve = z_improved[i] + (h/2) * ( fx( time , z_improved[i], y_b_ve) + fx( time+h, z_improved[i] + h * fx(time, z_improved[i], y_b_ve), y_b_ve + h * fy(time, z_improved[i], y_b_ve) )  );
        y_b_ve = y_b_ve        + (h/2) * ( fy( time , z_improved[i], y_b_ve) + fy( time+h, z_improved[i] + h * fx(time, z_improved[i], y_b_ve), y_b_ve + h * fy(time, z_improved[i], y_b_ve) )  );
        
        y_improved[i]=y_c_ve;
        y_c_ve = y_improved[i] + (h/2) * ( fw( time , y_improved[i], y_d_ve) + fw( time+h, y_improved[i] + h * fw(time, y_improved[i], y_d_ve), y_d_ve + h * fu(time, y_improved[i], y_d_ve) )  );
        y_d_ve = y_d_ve        + (h/2) * ( fu( time , y_improved[i], y_d_ve) + fu( time+h, y_improved[i] + h * fw(time, y_improved[i], y_b_ve), y_d_ve + h * fu(time, y_improved[i], y_d_ve) )  );
    
    }
    /*----------------------------------------------*/


    /*--------------- Plotting --------------*/
    if( atoi(argv[1]) == 1){
        // plotting for euler method and improved euler for z and psi
        char * commandsForGnuplot[] = {"set title \"Euler's method\"", "set xlabel \"time\"", "set ylabel \"displacement\"", "plot 'plots/euler_method_z_input1.txt' lt rgb \"red\""};
        createPlotData(z, t, "plots/euler_method_z_input1.txt", commandsForGnuplot);

        commandsForGnuplot[0] ="set title \"Improved Euler's method\"";
        commandsForGnuplot[3] ="plot 'plots/improved_euler_method_z_input1.txt' lt rgb \"red\"";
        createPlotData(z_improved, t, "plots/improved_euler_method_z_input1.txt", commandsForGnuplot);

        commandsForGnuplot[0] ="set title \"Euler's method\"";
        commandsForGnuplot[3] ="plot 'plots/euler_method_y_input1.txt' lt rgb \"blue\"";
        commandsForGnuplot[2] ="set ylabel \"orientation\"";
        createPlotData(y, t, "plots/euler_method_y_input1.txt", commandsForGnuplot);
        
        commandsForGnuplot[0] ="set title \"Improved Euler's method\"";
        commandsForGnuplot[3] ="plot 'plots/improved_euler_method_y_input1.txt' lt rgb \"blue\"";
        commandsForGnuplot[2] ="set ylabel \"orientation\"";
        createPlotData(y_improved, t, "plots/improved_euler_method_y_input1.txt", commandsForGnuplot);
        
        
    }else if(atoi(argv[1]) == 2) {
        char * commandsForGnuplot[] = {"set title \"Euler's method\"", "set xlabel \"time\"", "set ylabel \"displacement\"", "plot 'plots/euler_method_z_input2.txt' lt rgb \"red\""};
        createPlotData(z, t, "plots/euler_method_z_input2.txt", commandsForGnuplot);

        commandsForGnuplot[0] ="set title \"Improved Euler's method\"";
        commandsForGnuplot[3] ="plot 'plots/improved_euler_method_z_input2.txt' lt rgb \"red\"";
        createPlotData(z_improved, t, "plots/improved_euler_method_z_input2.txt", commandsForGnuplot);

        commandsForGnuplot[0] ="set title \"Euler's method\"";
        commandsForGnuplot[3] ="plot 'plots/euler_method_y_input2.txt' lt rgb \"blue\"";
        commandsForGnuplot[2] ="set ylabel \"orientation\"";
        createPlotData(y, t, "plots/euler_method_y_input2.txt", commandsForGnuplot);
        
        commandsForGnuplot[0] ="set title \"Improved Euler's method\"";
        commandsForGnuplot[3] ="plot 'plots/improved_euler_method_y_input2.txt' lt rgb \"blue\"";
        commandsForGnuplot[2] ="set ylabel \"orientation\"";
        createPlotData(y_improved, t, "plots/improved_euler_method_y_input2.txt", commandsForGnuplot);
    }
    return 0;
    /*----------------------------------------------*/
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
