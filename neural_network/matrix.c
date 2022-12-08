#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <err.h>
#include "matrix.h"

matrix* create_mat(int rows, int cols)
{
    matrix* mat = malloc(sizeof(matrix));
    mat->rows = rows;
    mat->cols = cols;
    mat->inputs = malloc(rows*sizeof(double*));

    for(int i = 0; i < rows; i++)
    {
        mat->inputs[i] = malloc(cols * sizeof(double));
    }
    return mat;
}

double get_rand(double min, double max)
{
    double range = max - min;
    double div = RAND_MAX / range;
    return min + (rand()/div);
}

void free_m(matrix* mat)
{
    for(int i = 0; i < mat->rows; i ++)
    {
        free(mat->inputs[i]);
    }
    free(mat);
    //mat = NULL;
}

void fill_m(matrix* mat, int k)
{
    for(int i = 0; i < mat->rows; i++)
    {
        for(int j = 0; j < mat->cols; j++)
        {
            mat->inputs[i][j] = k;
        }
    }
}

void fill_rand_m(matrix* mat)
{
    for(int i = 0; i < mat->rows; i++)
    {
        for(int j = 0; j < mat->cols; j++)
        {
            mat->inputs[i][j] = get_rand(-0.5f,0.5f);
        }
    }
}


int catch_dim_m(matrix* mat1, matrix* mat2)
{
    return (mat1->rows == mat2->rows && mat1->cols == mat2->cols);
}

matrix* mult_m(matrix* mat1, matrix* mat2)
{
    if(catch_dim_m(mat1, mat2))
    {
        matrix* res = create_mat(mat1->rows, mat2->cols);
        for(int i = 0; i < mat1->rows; i++)
        {
            for(int j = 0; j < mat2->cols; j++)
            {
                res->inputs[i][j] = mat1->inputs[i][j] * mat2->inputs[i][j];
            }
        }
        return res;
    }
    else
    {
        errx(1,"matrices does not have same dim !");
    }
}

matrix* add_m(matrix* mat1, matrix* mat2)
{
    if(catch_dim_m(mat1, mat2))
    {
        matrix* res = create_mat(mat1->rows, mat2->cols);
        for(int i = 0; i < mat1->rows; i++)
        {
            for(int j = 0; j < mat2->cols; j++)
            {
                res->inputs[i][j] = mat1->inputs[i][j] + mat2->inputs[i][j];
            }
        }
        return res;
    }
    else
    {
        errx(1,"matrices does not have same dim !");
    }
}

matrix* sub_m(matrix* mat1, matrix* mat2)
{
    if(catch_dim_m(mat1, mat2))
    {
        matrix* res = create_mat(mat1->rows, mat2->cols);
        for(int i = 0; i < mat1->rows; i++)
        {
            for(int j = 0; j < mat2->cols; j++)
            {
                res->inputs[i][j] = mat1->inputs[i][j] - mat2->inputs[i][j];
            }
        }
        return res;
    }
    else
    {
        errx(1,"matrices does not have same dim !");
    }
}

matrix* dot_m(matrix* mat1, matrix* mat2)
{
    if(mat1->cols == mat2->rows)
    {
        matrix* res = create_mat(mat1->rows, mat2->cols);
        for(int i = 0; i < mat1->rows; i++)
        {
            for(int j = 0; j < mat2->cols; j++)
            {
                double tmp = 0;
                for(int n = 0; n < mat2->rows; n++)
                {
                    tmp += mat1->inputs[i][n] * mat2->inputs[n][j];
                }
                res->inputs[i][j] = tmp;
            }
        }
        return res;
    }
    else
    {
        errx(1,"dim are not good for a dot ! m1 : %d m2 : %d",mat1->cols,mat2->rows);
    }
}

matrix* cp_m(matrix* mat)
{
    matrix* res = create_mat(mat->rows, mat->cols);
    for(int i = 0; i < mat->rows; i++)
    {
        for(int j = 0; j < mat->cols; j++)
        {
            res->inputs[i][j] = mat->inputs[i][j];
        }
    }
    return res;
}

matrix* mult_scale_m(matrix* mat, double lamb)
{
    matrix* res = cp_m(mat);
    for(int i = 0; i < mat->rows; i++)
    {
        for(int j = 0; j < mat->cols; j++)
        {
            res->inputs[i][j] *= lamb;
        }
    }
    return res;
}

matrix* add_scale_m(matrix* mat, double lamb)
{
    matrix* res = cp_m(mat);
    for(int i = 0; i < mat->rows; i++)
    {
        for(int j = 0; j < mat->cols; j++)
        {
            res->inputs[i][j] += lamb;
        }
    }
    return res;
}

matrix* trans_m(matrix* mat)
{
    matrix* res = create_mat(mat->rows, mat->cols);
    for(int i = 0; i < mat->rows; i++)
    {
        for(int j = 0; j < mat->cols; j++)
        {
            res->inputs[i][j] = mat->inputs[j][i];
        }
    }
    return res;
}

void print_m(matrix* mat)
{
    for(int i = 0; i < mat->rows; i++)
    {
        for(int j = 0; j < mat->cols; j++)
        {
            printf("%.f ",mat->inputs[i][j]);
        }
        printf("\n");
    }
}

double sigmoid(double z)
{
   return 1 / (1 + exp(-z));
}

double Dsigmoid(double z)
{
    return z * (1 - z);
}

matrix* sig_m(matrix* mat)
{
    matrix* res = create_mat(mat->rows, mat->cols);
    for(int i = 0; i < mat->rows; i++)
    {
        for(int j = 0; j < mat->cols; j++)
        {
            res->inputs[i][j] = sigmoid(mat->inputs[i][j]);
        }
    }
    return res;
}

matrix* Dsig_m(matrix* mat)
{
    matrix* res = create_mat(mat->rows, mat->cols);
    for(int i = 0; i < mat->rows; i++)
    {
        for(int j = 0; j < mat->cols; j++)
        {
            res->inputs[i][j] = Dsigmoid(mat->inputs[i][j]);
        }
    }
    return res;
}


