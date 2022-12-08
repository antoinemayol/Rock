#include "cut.h"
#include <stddef.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "print_function.h"

int* resize(int h, int w, int* matrix, int new)
{
    int* resized = malloc(sizeof(int)*new*new);

    float x_rat = (float)(w - 1)/(new - 1);
    float y_rat = (float)(h - 1)/(new - 1);

    for(int i = 0; i < new; i++)
        for(int j = 0; j< new; j++)
        {
            int x_l = floor(x_rat * j);
            int y_l = floor(x_rat * i);
            int x_h = ceil(x_rat * j);
            int y_h = ceil(x_rat * i);

            int x_w = x_rat*j - x_l;
            int y_w = y_rat * i - y_l;

            int a = matrix[y_l*w + x_l];
            int b = matrix[y_l*w + x_h];
            int c = matrix[y_h*w + x_l];
            int d = matrix[y_h*w + x_h];

            int pixel = a*(1 - x_w) * (1 - y_w)
                    + b * x_w * (1 - y_w) +
                    c * y_w * (1 - y_w) +
                    d * x_w * y_w;
            resized[i*new + j] = pixel;
        }
    return resized;
}

int** extract_intersections(int* horizontal_equ, int* vertical_equ, int lenh, int lenv)
{
    //int threshold = 2;
    int **coordonates = malloc(sizeof(int *)*81);
    
    for(int i = 0; i < lenh - 1; i++)
        for(int j = 0; j < lenv - 1; j++)
        {
            int* coo = malloc(sizeof(int)*4);
            *coo = *(horizontal_equ + i) + 1;
            *(coo + 1) = *(vertical_equ + j + 1) + 1;
            *(coo + 2) = *(horizontal_equ + i + 1);
            *(coo + 3) = *(vertical_equ + j);
            *(coordonates + i*(lenv - 1) + j) = coo;
        }
    return coordonates;
}
void __tej_bordure(int h, int w, int* mat, int x, int y)
{
    if(x>=0 && y >=0 && x<h && y<w && *(mat + x*w +y) != 0)
    {
        *(mat+x*w+y) = 0;
        __tej_bordure(h,w,mat, x, y + 1);
        __tej_bordure(h,w,mat, x+1, y);
        __tej_bordure(h,w,mat, x, y - 1);
        __tej_bordure(h,w,mat, x-1, y);
    }
}
void tej_bordure(int h, int w, int* mat)
{
    __tej_bordure(h,w,mat, 0,0);
    __tej_bordure(h,w,mat, 0,w-1);
    __tej_bordure(h,w,mat, h-1,0);
    __tej_bordure(h,w,mat, h-1,w-1);
}

double* convert_to_double(int* m)
{
    double* res = malloc(sizeof(double)*25*25);
    int is_empty = 1;
    for(int i = 0; i < 25*25;i++)
    {
        *(res + i) = (double)*(m + i);
        if(*(res + i) == 1)
            is_empty = 0;
    }
    if(is_empty)
        return NULL;
    return res;
}

double** stockage_cases(int** coo, int* matrix, int width, int** cases)
{
    /* Stock all matrix of cases
     * ARGS:
     *  -coo (int**) cordonates of cases
     *  -width (int) : width of the matrix
     *  -matrix (int[]) : the matrix to print
     *  -cases (int**) : destination pointers
     * OUT:
     *  none
     */
    int nb_case = 81;
    int l = 0;
    int w = 0;

    double** final = malloc(sizeof(double*)*81);
    for(int i = 0 ; i < nb_case ; ++i)
    {
        int X1 = *(*(coo+i));
        int Y1 = *(*(coo+i) +1);
        int X2 = *(*(coo+i) +2);
        int Y2 = *(*(coo+i) +3);
        l = X2 - X1;
        w = Y2 - Y1;
        int* new = malloc(sizeof(int)*l*w); 
        for(int j = 0; j < l; j++)
            for(int k = 0; k < w; k++)
                *(new +j*w + k) = *(matrix +(X1 + j)*width + Y1 + k);
        *(cases + i ) = new;
        int* resized = resize(l,w,*(cases +i),25);
        tej_bordure(25,25,resized);
               
        *(final + i) = malloc(sizeof(double)*25*25);
        *(final + i) = convert_to_double(resized);
        if(*(final + i) != NULL)
            print_mat(25,25,resized,0,0,25,25);
    }
    return final;
}
