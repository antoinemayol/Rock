#ifndef MATRIX2_H
#define MATRIX2_H

void transpose(double **A, int n);
double **inverse(double **A0, int n);
double **dot_matrix(double** mat1, double** mat2, int rows1, int cols1, int rows2, int cols2);
double **copy_mat(double **A, int n);
double **create_empty_mat(int rows, int cols);

#endif
