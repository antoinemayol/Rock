#ifndef MATRIX_H
#define MATRIX_H

void transpose(double **A, int n);
double **inverse(double **A0, int n);
double **dot_matrix(double** mat1, double** mat2, int cols1, int cols2, int rows1, int rows2);
double **copy_mat(double **A, int n);

#endif
