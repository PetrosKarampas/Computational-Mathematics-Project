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
double z0    = 0;
double Cz    = 4 - ((double)AM / 5000);
double z_des = (double)AM / 200;

//Macros
#define fx(t, x, y) (y)
#define fy(t, x, y) (((((Kpz) * ((z_des) - (x))) - ((Kdz) * (y)) - ((Cz) * (y)))/(M)))

//prototypes
void createPlotData(double y[], double t[], char* outfile_path);
void createPlot(char* errors_filepath, char* plot_title, char* ylabel, char* legend_label, char* rgb);
void createMultiPlot(char* data1, char* legend_title_1, char* data2, char* legend_title_2, char* ylabel);
void createTruncationErrorData(double original[], double euler[], double euler_improved[], double t[]);
char* concatenate(size_t size, char *array[size], const char *joint);

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


void createPlotData(double y[], double t[], char* outfile_path) {
    FILE* fp = fopen(outfile_path, "w");
    for(int i = 0; i<=30000; i++) {
        fprintf(fp, "%.3lf\t %.10lf\n", t[i], y[i]);
    }
}

void createTruncationErrorData(double original[], double euler[], double euler_improved[], double t[]) {
    FILE* euler_error_fp = fopen("../plots/errors_E.txt", "w");
    FILE* improved_euler_error_fp = fopen("../plots/errors_BE.txt", "w");
    
    // calculate truncation error data
    double errors_euler[30001];
    double errors_improved_euler[30001];
    for (int i = 0; i<=30000; i++) {
        errors_euler[i]          = fabs(original[i] - euler[i]);
        errors_improved_euler[i] = fabs(original[i] - euler_improved[i]);
    }
    
    for(int i = 0; i<=30000; i++) {
        fprintf(euler_error_fp,"%.3lf\t %.10lf\n", t[i], errors_euler[i]);
        fprintf(improved_euler_error_fp,"%.3lf\t %.10lf\n", t[i], errors_improved_euler[i]);
    }
}

// open a pipe to the gnuplot programm and feed it commands to create the plot
void createPlot(char* errors_filepath, char* plot_title, char* ylabel, char* legend_label, char* rgb) {
    FILE* gnuplotPipe = popen ("gnuplot -persistent", "w");
    char * commandsForGnuplot[] = {"set title \"", plot_title, "\";", "set xlabel \"time\";", "set ylabel \"", ylabel, "\";",\
        "plot '", errors_filepath, "' using 1:2 title '", legend_label,"'lt rgb \"" , rgb,"\" with lines;"};
    
    char *cat = concatenate(14, commandsForGnuplot, "");
    fprintf(gnuplotPipe, "%s \n", cat); //Send command to gnuplot.
    free(cat);
}

// open a pipe to the gnuplot programm and feed it commands to create the plot
void createMultiPlot(char* data1, char* legend_title_1, char* data2, char* legend_title_2, char* ylabel) {
    FILE* gnuplotPipe = popen ("gnuplot -persistent", "w");
    
    char * commandsForGnuplot[] = {"set title \"Truncation Error\"; set xlabel \"time\"; set ylabel \"", ylabel, "\"; plot '", data1, "' using 1:2 title '", legend_title_1, "' lw 3 lt rgb \"#00FF00\" with lines, '", data2,"' using 1:2 title '", legend_title_2,"'lw 4 lt rgb \"#FF00FF\" with lines"};
    char *cat = concatenate(11, commandsForGnuplot, "");
    fprintf(gnuplotPipe, "%s \n", cat); //Send commands to gnuplot one by one.
    free(cat);
}

// takes an array of strings and concatenates them to a single one
char* concatenate(size_t size, char* array[size], const char *joint){
    size_t jlen, lens[size];
    size_t i, total_size = (size-1) * (jlen=strlen(joint)) + 1;
    char *result, *p;

    for(i=0;i<size;++i){
        total_size += (lens[i]=strlen(array[i]));
    }
    p = result = malloc(total_size);
    for(i=0;i<size;++i){
        memcpy(p, array[i], lens[i]);
        p += lens[i];
        if(i<size-1){
            memcpy(p, joint, jlen);
            p += jlen;
        }
    }
    *p = '\0';
    return result;
}
