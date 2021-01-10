//
//  utils.h
//  Computational Mathematics Project
//
//  Created by Alexandros Alexiou 2929, Petros Karampas 2987, Nikos Amvazas 2932.
//

#ifndef utils_h
#define utils_h

#include <stdio.h>

void createPlotData(double y[], double t[], char* outfile_path);
void createPlot(char* data_filepath, char* plot_title, char* ylabel, char* legend_label, char* rgb);
void createMultiPlot(char* data1, char* legend_title_1, char* data2, char* legend_title_2, char* ylabel);
void createTruncationErrorData(double original[], double euler[], double euler_improved[], double t[]);
char* concatenate(size_t size, char *array[size], const char *joint);

#endif /* utils_h */
