//
//  problem1d.c
//  Problem-1d
//
//  Created by Alexandros Alexiou, Petros Karampas, Nikos Amvazas.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../utils/utils.h"

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
double psi0     = (double)AM / 10000;
double z_des    = (double)AM / 200;
double psi_des  = (double) - AM/3000;
double Cz       = 3 + (double)AM / 5000;
double Kdz      = 15 + (double)AM / 1000;

//Macros
//#define fx(t, x, y) (y)
//#define fy(t, x, y) ( (((Kpz) * ((z_des) - (x))) - ((Kdz) * (y)) - ((Cz) * (fabs(y)) * (y)) )/(M))
//#define fw(t, w, u) (u)
//#define fu(t, w, u) ( (((Kp_psi) * ((psi_des)-(w))) - ((Kd_psi) * (u)) - (0.5 * (Cpsi) * (fabs(u)) * (u)) )/(Iz))

//prototypes
double fx(double t, double x, double y);
double fy(double t, double x, double y);
double fw(double t, double w, double u);
double fu(double t, double w, double u);

int main(int argc, const char * argv[]) {
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
    time = h;

    for(int i = 0; i<30000; i++, time+=h ) {
        
        x[i+1] = x[i] + h * fx(time, x[i], y[i]);
        y[i+1] = y[i] + h * fy(time, x[i], y[i]);
        
        w[i+1] = w[i] + h * fw(time, w[i], u[i]);
        u[i+1] = u[i] + h * fu(time, w[i], u[i]);
        
        t[i+1] = time;
    }
    
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
    
    /*--------------------plotting--------------------------*/
    createPlotData(x, t, "../plots/euler_method_z.txt");
    createPlotData(w, t, "../plots/euler_method_Psi.txt");
    createPlotData(x_imp, t, "../plots/improved_euler_method_z.txt");
    createPlotData(w_imp, t, "../plots/improved_euler_method_Psi.txt");
    
    createPlot("../plots/euler_method_z.txt", "Euler's method for z", "displacement", "../plots/euler\\_method\\_z.txt", "#FF0000");
    createPlot("../plots/euler_method_Psi.txt", "Euler's method for Psi", "orientation", "../plots/euler\\_method\\_Psi.txt", "#0000FF");
    createPlot("../plots/improved_euler_method_z.txt", "Improved Euler's method z", "displacement", "../plots/improved\\_euler\\_method\\_z.txt", "#FF0000");
    createPlot("../plots/improved_euler_method_Psi.txt", "Improved Euler's method for Psi", "orientation", "../plots/improved\\_euler\\_method\\_Psi.txt", "#0000FF");
    return 0;
}

double fx(double t, double x, double y){
    return (y);
}
double fy(double t, double x, double y){
    return (Kpz * (z_des - x) - (Kdz * y) - (Cz * fabs(y) * y) )/M;
}
double fw(double t, double w, double u){
    return (u);
}
double fu(double t, double w, double u){
    return (Kp_psi * (psi_des-w) - (Kd_psi * u) - (0.5 * Cpsi * fabs(u) * u) )/Iz;
}
