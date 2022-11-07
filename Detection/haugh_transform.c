#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void hough_transform(int l, int w, int *mat, int *hough_val)
{
    /* Calculate the number of occurences for each equation possible
     * ARGS:
     *  -lenght (int) : lenght of the matrix
     *  -width (int) : width of the matrix
     *  -matrix (*int) : the matrix to print
     *  -haugh_val (*int) : the haugh table
     * OUT:
     *  none
     */
    
    double max_p = l;

    for(double i = 0; i < 180;i++)
        for(double j = 0; j < max_p*2; j++)
            *(hough_val + (int)(i*max_p*2 + j)) = 0;

    for(int i = 0; i < l;i++)
        for(int j = 0; j < w; j++)
            if(*(mat + i*w + j))
                    for(double arg = -90; arg < 90; arg++)
                    {
                        float radian = arg * (M_PI / 180.0);
                        int p = (int)(i*cos(radian) + j*sin(radian));


                        *(hough_val + (int)((p + max_p)*180 + (arg+90))) +=1;
                    }
}

int get_max_hough_occ(int l, int w, int *hough)
{
    int max = 0;
    for(int i = 0; i < l; i ++)
       for(int j = 0; j < w; j++)
           if(*(hough + i*w +j) > max)
                   max = *(hough +i*w +j);
    return max;
}

void get_equation(int phi,int roh, int *hough_val)
{
    int max_occ = get_max_hough_occ(phi*2, roh*2, hough_val);

    for(int i = 0; i < phi*2; i ++)
    {
       for(int j = 0; j < roh*2; j++)
       {
           if(*(hough_val + i*roh*2 + j) >= max_occ -6)
               printf("roh=%d phi=%d\n",j - roh, i -phi);
       }

    }
}

void hough_traitement(int l, int w, int *mat)
{
    double max_p = l;
    double mat_size = 180*max_p*2;

    int* hough_val = malloc(mat_size*sizeof(int));

    hough_transform(l, w, mat, hough_val);

    get_equation((int)max_p,90,hough_val);

    //récupération des équations
    //print_graph((int)max_p*2,180,hough_val);
    free(hough_val);
}

void print_graph(int l, int w, int *matrix)
{
    /* Print a matrix
     * ARGS:
     *  -lenght (int) : lenght of the matrix
     *  -width (int) : width of the matrix
     *  -matrix (int[]) : the matrix to print
     * OUT:
     *  none
     */
    for(int i = 0 ; i < l ; ++i)
    {
    	for (int j = 0; j < w; ++j)
        {
            if((i*w + j)[matrix] < 3)
                printf("\033[0;32m");
            else if((i*w + j)[matrix] < 64)
                printf("\033[0;33m");
            else{
                printf("\033[0;31m");
            }
    		printf("●\033[0m");
        }
    	printf("\n");
    }
    printf("\n");
}
