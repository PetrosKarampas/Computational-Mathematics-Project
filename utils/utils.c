//
//  utils.c
//  Computational Mathematics Project
//
//  Created by Alexandros Alexiou on 10/1/21.
//

#include "utils.h"
#include <stdlib.h>
#include <math.h>
#include <string.h>

/**
 * @name createPlotData - creates a text file with the two array parameters and saves it on disk
 * @param y : the y coordinates
 * @param t : the x coordinates
 * @param outfile_path : the name of the file to be created
 */
void createPlotData(double y[], double t[], char* outfile_path) {
    FILE* fp = fopen(outfile_path, "w");
    for(int i = 0; i<=30000; i++) {
        fprintf(fp, "%.3lf\t %.10lf\n", t[i], y[i]);
    }
}

/**
 * @name createTruncationErrorData - calculates the truncation error of the euler methods and saves the data on disk
 * @param original : the coordinates of the analytical solution
 * @param euler : the coordinates of the euler's numerical solution
 * @param euler_improved : the coordinates of the improved euler's numerical solution
 * @param t : the x coordinates representing the time
 */
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

/**
 * @name createPlot - creates a plot from a text file by opening a pipe and executing commands using gnuplot
 * @param data_filepath : the text file location on disk
 * @param plot_title : the title of the plot to be created
 * @param ylabel : the label of the y axis
 * @param legend_label : the label of the legend
 * @param rgb : the color of the line in hex representation
 */
void createPlot(char* data_filepath, char* plot_title, char* ylabel, char* legend_label, char* rgb) {
    FILE* gnuplotPipe = popen ("gnuplot -persistent", "w");
    char * commandsForGnuplot[] = {"set title \"", plot_title, "\";", "set xlabel \"time\";", "set ylabel \"", ylabel, "\";",\
        "plot '", data_filepath, "' using 1:2 title '", legend_label,"'lt rgb \"" , rgb,"\" with lines;"};
    
    char *cat = concatenate(14, commandsForGnuplot, "");
    fprintf(gnuplotPipe, "%s \n", cat); //Send command to gnuplot.
    free(cat);
}

/**
 * @name createMultiPlot - creates a multiplot from two text files by opening a pipe and executing commands using gnuplot
 * @param data1 : the first text file location on disk
 * @param legend_title_1 : the first file label of the legend of the plot
 * @param data2 : the second text file location on disk
 * @param legend_title_2 : the second file label of the legend of the plot
 * @param ylabel : the label of the y axis
 */
void createMultiPlot(char* data1, char* legend_title_1, char* data2, char* legend_title_2, char* ylabel) {
    FILE* gnuplotPipe = popen ("gnuplot -persistent", "w");
    
    char * commandsForGnuplot[] = {"set title \"Truncation Error\"; set xlabel \"time\"; set ylabel \"", ylabel, "\"; plot '", data1, "' using 1:2 title '", legend_title_1, "' lw 3 lt rgb \"#00FF00\" with lines, '", data2,"' using 1:2 title '", legend_title_2,"'lw 4 lt rgb \"#FF00FF\" with lines"};
    char *cat = concatenate(11, commandsForGnuplot, "");
    fprintf(gnuplotPipe, "%s \n", cat); //Send commands to gnuplot one by one.
    free(cat);
}

/**
 * @name concatenate - creates a single string from an array of string. Use to create the parameterized gnuplot commands
 * @param size : the size of the array
 * @param array : the array of the strings to be concatenated
 * @param joint : the delimiter
 *
 * @return result : the concatenated string
 */
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
