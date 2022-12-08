#include <stdio.h>
#include <stdlib.h>
#include "matrix2.h"

double **homography_transform(double **A, int h, int w, double **corners)
{
    int n = 8;
    int size = 500;
    double **X = malloc(sizeof(double*)*8);
    for(int i = 0; i<8; i++)
    {
        X[i] = malloc(sizeof(double)*8);
    }
    double **bis = malloc(sizeof(double*));
    bis[0] = malloc(sizeof(double)*8);
    bis[0][0] = 0;
    bis[0][1] = 0;
    bis[0][2] = size;
    bis[0][3] = 0;
    bis[0][4] = 0;
    bis[0][5] = size;
    bis[0][6] = size;
    bis[0][7] = size;

    for(int i = 0; i < 8; i++)
    {
        if(i%2 == 0)
        {
            X[i][0] = corners[0][i];
            X[i][1] = corners[0][i+1];
            X[i][2] = 1;
            X[i][3] = 0;
            X[i][4] = 0;
            X[i][5] = 0;
            X[i][6] = -bis[0][i]*corners[0][i];
            X[i][7] = bis[0][i]*corners[0][i+1];
        }
        else
        {
            X[i][0] = 0;
            X[i][1] = 0;
            X[i][2] = 0;
            X[i][3] = corners[0][i-1];
            X[i][4] = corners[0][i];
            X[i][5] = 1;
            X[i][6] = -bis[0][i]*corners[0][i-1];
            X[i][7] = bis[0][i]*corners[0][i-1];
        }
    }
    double **tr = copy_mat(X, n);
    transpose(tr,n);
    double **M2 = dot_matrix(tr,X,n,n,n,n);
    double ** inv = copy_mat(M2,n);
    inverse(inv,n);
    double **M3 = dot_matrix(inv,tr, n, n, n, n);
    double **M4 = dot_matrix(M3, corners,8,8,8,1);
    double **M5 = create_empty_mat(3,3);
    for(int i=0; i < 2; i++)
    {
        for(int j = 0; j<3; j++)
        {
            M5[i][j] = M4[0][i];
        }
    }
    M5[3][0] = M4[0][5]; 
    M5[3][1] = M4[0][6]; 
    M5[3][1] = 1; 
    double **res = malloc(sizeof(double*)*size);
    for(int i = 0; i < size; i++)
    {
        res[i] = malloc(sizeof(double)*size);
    }
    for(int i = 0; i < size; i++)
    {
        for(int  j = 0; j < size; j++)
        {
            double *p = malloc(sizeof(int)*3);
            p[0] = i;
            p[1] = j;
            p[2] = 1;
            double **M6 = dot_matrix(&p,M5,1,3,3,3);
            int x = M6[0][0]/M6[0][2];
            int y = M6[0][1]/M6[0][2];
            res[i][j] = A[x][y];
        }
    }
    return res;
}
