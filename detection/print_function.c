#include <stdio.h>
#include "LineParameter.h"

void print_lines(LineParameter* lines, int nb)
{
    for(int i = 0; i < nb; i++)
        printf("%f %f\n", (lines + i)->angle, (lines + i)->distance);
}


void print_mat(int l, int w, int *matrix, int x1, int y1, int x2, int y2)
{
    /* Print a matrix
     * ARGS:
     *  -lenght (int) : lenght of the matrix
     *  -width (int) : width of the matrix
     *  -matrix (int[]) : the matrix to print
     * OUT:
     *  none
     */
    int l1 = x2==0?l:x2;
    int l2 = y2==0?w:y2;

    for(int i = x1 ; i < l1 ; ++i)
    {
    	for (int j = y1; j < l2; ++j)
        {
            printf("%d",*(matrix + i*w + j));
        }
    	printf("\n");
    }
    printf("\n");
}

void print_case(int **coo, int* mat, int width)
{
    /* Print cases of the sudoku
     * ARGS:
     *  -coo (int**) : coodrinates of cases
     *  -width (int) : width of the matrix
     *  -matrix (int[]) : the matrix to print
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
        printf("case %d:\n",i+1);
        for(int j = X1; j < X2; j++)
        {
            for(int k = Y1; k < Y2; k++)
                printf("%d", mat[j*width + k]);
            printf("\n");
        }
        printf("\n");
    } 
    printf("\n");
}
