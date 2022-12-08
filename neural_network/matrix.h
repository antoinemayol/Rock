#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    double** inputs;
    int rows;
    int cols;
} matrix;


matrix* create_mat(int rows, int cols);
void free_m(matrix* mat);
void fill_m(matrix* mat, int k);
void fill_rand_m(matrix* mat);
int catch_dim_m(matrix* mat1, matrix* mat2);
matrix* mult_m(matrix* mat1, matrix* mat2);
matrix* add_m(matrix* mat1, matrix* mat2);
matrix* sub_m(matrix* mat1, matrix* mat2);
matrix* dot_m(matrix* mat1, matrix* mat2);
matrix* cp_m(matrix* mat);
matrix* mult_scale_m(matrix* mat, double lamb);
matrix* add_scale_m(matrix* mat, double lamb);
matrix* trans_m(matrix* mat);
void print_m(matrix* mat);

double sigmoid(double z);
double Dsigmoid(double z);

matrix* sig_m(matrix* mat);
matrix* Dsig_m(matrix* mat);
