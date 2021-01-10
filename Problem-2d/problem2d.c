//
//  	problem2d.c
//
//	Created by Alexandros Alexiou, Petros Karampas, Nikos Amvazas.
//
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "../utils/utils.h"

// Constants
#define M       1.5
#define AM      2987
#define zpar0   0
#define Kpz     5
#define Kdz     15
#define h       0.001

//globals
double fz;
double z0    = 0;
double Cz    = 4 - ((double)AM / 5000);
double z_des = (double)AM / 200;

//Macros
#define fx(t, x, y) (y)
#define fy(t, x, y) (((((Kpz) * ((z_des) - (x))) - ((Kdz) * (y)) - ((Cz) * (y)))/(M)))

int main(int argc, char * argv[]){
    /*--------------- Analytical solution of the differential equation-------------*/
    double dif[30001];
    double t  [30001];
    double time = 0.0;

    for(int i = 0; i<=30000; i++, time+=h){
        dif[i] = -15.2894903563 * exp(-0.27800018214 * time) + 0.35449035632 * exp(-11.9903998179 * time) + 14.935;
        t[i] = time;
    }
    createPlotData(dif, t, "../plots/differential.txt");
    
    /*--------------- Euler's method ---------------*/
    double x [30001];
    double y [30001];
    x[0] = z0;
    y[0] = zpar0;
    time = 0.0;
    
    for(int i = 0; i<30000; i++, time+=h){
        x[i+1] = x[i] + h * fx(time, x[i], y[i]);
        y[i+1] = y[i] + h * fy(time, x[i], y[i]);
    }
    createPlotData(x, t, "../plots/euler_method_z_2d.txt");
    createPlotData(y, t, "../plots/euler_method_y_2d.txt");
    
    /*--------------- Improved Euler's Method --------------*/
    double x_imp [30001];
    double y_imp [30001];
    time = 0.0;
    x_imp[0] = z0;
    y_imp[0] = zpar0;

    for (int i = 0; i<30000; i++, time+=h){
        x_imp[i+1] = x_imp[i] + ((h/2) * ( fx( time, x_imp[i], y_imp[i]) + fx( time+h, x_imp[i] + h * fx(time, x_imp[i], y_imp[i]), y_imp[i] + h * fy(time, x_imp[i], y_imp[i])) )  );
        y_imp[i+1] = y_imp[i] + ((h/2) * ( fy( time, x_imp[i], y_imp[i]) + fy( time+h, x_imp[i] + h * fx(time, x_imp[i], y_imp[i]), y_imp[i] + h * fy(time, x_imp[i], y_imp[i])) )  );
    }
    createPlotData(x_imp, t, "../plots/improved_euler_method_z_2d.txt");
    createPlotData(y_imp, t, "../plots/improved_euler_method_y_2d.txt");
    
    createTruncationErrorData(dif, x, x_imp, t);
    
    /*--------------- Plotting ---------------*/
    createPlot("../plots/differential.txt", "Differential Equation", "displacement", "..plots/differential.txt", "#FF0000");
    
    createPlot("../plots/euler_method_z_2d.txt", "Euler's method for z", "displacement", "..plots/euler\\_method\\_z\\_2d.txt", "#FF0000");

    createPlot("../plots/euler_method_y_2d.txt", "Euler's method for y", "velocity", "..plots/euler\\_method\\_y\\_2d.txt", "#0000FF");
    
    createPlot("../plots/improved_euler_method_z_2d.txt", "Improved Euler's method z", "displacement", "..plots/improved\\_euler\\_method\\_z\\_2d.txt", "#FF0000");
    
    createPlot("../plots/improved_euler_method_y_2d.txt", "Improved Euler's method for y", "velocity", "..plots/improved\\_euler\\_method\\_y\\_2d.txt", "#0000FF");
    
    createPlot("../plots/errors_E.txt", "Truncation Error Euler's method", "error", "e_n(Euler)", "#00FF00");
    
    createPlot("../plots/errors_BE.txt", "Truncation Error Improved Euler's method", "error", "e_n(Improved Euler)", "#FF00FF");
    
    createMultiPlot("../plots/errors_E.txt", "e_n(E)", "../plots/errors_BE.txt", "e_n(BE)", "error");
    
    return 0;
}
