#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"



/*
int **homography_transform(double **A, int h, int w, int* corners)
{
    int size = 500;
    double **X = malloc(sizeof(int*)*8);
    for(int i = 0; i<8; i++)
    {
        for(int j = 0; j<8; j++)
        {
            malloc(sizeof(int)*8);
        }
    }
    double *bis = malloc(sizeof(int)*8);
    bis[0][0] = 0;
    bis[0][1] = 0;
    bis[0][2] = 0;
    bis[0][0] = 0;
    bis[0][0] = 0;
    bis[0][0] = 0;
    bis[0][0] = 0;
    bis[0][0] = 0;

    for(int i = 0; i < 8; i++)
    {
        if(i%2 == 0)
        {
            X[i][0] = corners[2*i];
            X[i][1] = corners[2*i+1];
            X[i][2] = 1;
            X[i][3] = 0;
            X[i][4] = 0;
            X[i][5] = 0;
            X[i][0] = corners[2*i];
            X[i][0] = corners[2*i+1];
        }
    }
}*/
