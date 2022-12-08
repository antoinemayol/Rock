#include "image_processing/processing_final.h"
#include "detection/detection.h"
#include <stdio.h>
#include <stdlib.h>


int main()
{
    /*  
     *  1-start graphic interface
     *  2-image selection
     *  3-image traitment: from an image
     *      must return a matrix of 0 and 1
     *  4-image detection: from a matrix of 0 and 1
     *      .grid detection
     *      .case detection
     *      must return all case
     *  5-neuronal network: from all case
     *      .found numbers associated to each cases
     *      must return a matrix with known number and empty for missing numbers
     *  6-sudoku solver: from a matrix of int
     *      .resolve the sudoku
     *      must return a none empty matrix with solve sudoku
     *  7-resolved sudoku display
    */
    int w = 0;
    int h = 0;
    int* bin_mat = image_processing("images/image_03.jpeg",&w,&h);
    int** cases = detection(bin_mat, w, h);
    free(bin_mat);
    free(cases);
    printf("lol\n");
    return 1;

}
