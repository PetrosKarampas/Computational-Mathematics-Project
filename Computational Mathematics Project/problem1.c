//
//  main.c
//  Computational Mathematics Project
//
//  Created by Alexandros Alexiou on 25/12/20.
//

#include "../include/pbPlots.h"
#include "../include/supportLib.h"

int main(){
    double x []  = {-10, 0, 1, 2, 3, 4, 5, 6};
    double y []  = {-5, -4, -3, -2, 1, 0, 1, 2};
    RGBABitmapImageReference *imageRef = CreateRGBABitmapImageReference();
    
    DrawScatterPlot(imageRef, 1000, 600, x, 8, y, 8);
    size_t length;
    double *pngData = ConvertToPNG(&length, imageRef->image);
    WriteToFile(pngData, length, "plot.png");
    system("open plot.png");
    return 0;
}
