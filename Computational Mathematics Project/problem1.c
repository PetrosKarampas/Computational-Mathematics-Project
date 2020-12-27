//
//  main.c
//  Computational Mathematics Project
//
//  Created by Alexandros Alexiou on 25/12/20.
//
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../include/pbPlots.h"
#include "../include/supportLib.h"

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
#define fy(t, x, y) ((fz - (g * M) - (Cz * Absolute(y) * y))/M)
#define fw(t, w, u) (u)
#define fu(t, w, u) ((tz - (0.5 * Cpsi *  Absolute(u) * u))/Iz)

//prtotypes
void createPlot(double y[], double t[], wchar_t* ylabel, wchar_t* xlabel, wchar_t* graphTitle, char * filename);


int main(){
    
    double y [30002];
    double y2 [30002];
    double t [30002];
    double time = 0.0;
    double y_x_1 = z0;
    double y_y_1 = zpar0;
    
    double y_w_1 = psi0;
    double y_u_1 = psipar0;
    
    for(int i = 1; i<=30001; i++, time+=h ){
        
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
   
    // Plotting stuff
    y[0]=0;
    t[0]=0;
    createPlot(y, t, L"position", L"time", L"Euler's Method", "plot.png");
    createPlot(y, t, L"look", L"time", L"test", "plot2.png");
    

    return 0;
}



void createPlot(double y[], double t[], wchar_t* ylabel, wchar_t* xlabel, wchar_t* graphTitle, char * filename){
    ScatterPlotSeries *series = GetDefaultScatterPlotSeriesSettings();
    series->xs = t;
    series->xsLength = 30002;
    series->ys = y;
    series->ysLength = 30002;
    series->linearInterpolation = true;
    series->lineTypeLength = wcslen(series->lineType);
    series->lineThickness = 2;
    series->color = GetBlack(0.6);

    ScatterPlotSettings *settings = GetDefaultScatterPlotSettings();
    settings->width = 1000;
    settings->height = 600;
    settings->autoBoundaries = true;
    settings->autoPadding = true;
    settings->title = graphTitle;
    settings->titleLength = wcslen(settings->title);
    settings->xLabel = xlabel;
    settings->xLabelLength = wcslen(settings->xLabel);
    settings->yLabel = ylabel;
    settings->yLabelLength = wcslen(settings->yLabel);
    ScatterPlotSeries *s [] = {series};
    settings->scatterPlotSeries = s;
    settings->scatterPlotSeriesLength = 1;

    RGBABitmapImageReference *canvasReference = CreateRGBABitmapImageReference();
    DrawScatterPlotFromSettings(canvasReference, settings);

    size_t length;
    double *pngdata = ConvertToPNG(&length, canvasReference->image);
    WriteToFile(pngdata, length, filename);
    DeleteImage(canvasReference->image);
}
