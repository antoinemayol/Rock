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

    for(int i = 0; i < h; i++)
        for(int j = 0; j< w; j++)
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
            resized[i*w + j] = pixel;
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

void stockage_cases(int** coo, int* matrix, int width, int** cases)
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
    for(int i = 0 ; i < nb_case ; ++i)
    {
        int X1 = *(*(coo+i));
        int Y1 = *(*(coo+i) +1);
        int X2 = *(*(coo+i) +2);
        int Y2 = *(*(coo+i) +3);
        int l = X2 - X1;
        int w = Y2 - Y1;
        int* new = malloc(sizeof(int)*l*w); 
        for(int j = 0; j < l; j++)
            for(int k = 0; k < w; k++)
                *(new +j*w + k) = *(matrix +(X1 + j)*width + Y1 + k);
        *(cases + (i/9)*9 + 9 - i % 9 - 1) = new;
    } 
}

int** get_cases(int h, int w, int* matrix, struct LineParameter* lines)
{
    int y1 = (int)(lines)->distance;
    int x1 = (int)(lines + 1)->distance;
    int y2 = (int)(lines + 2)->distance;
    int x2 = (int)(lines + 3)->distance;
    printf("%d %d %d %d-%d\n", x1, y1, x2, y2,w);
    print_mat(h, w, matrix, x1, y1, x2, y2);
    int** cases = malloc(sizeof(int*)*81);
    return cases;
}


