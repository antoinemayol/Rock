#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void haugh_transform(int l, int w, int *mat, int *haugh_val)
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
            *(haugh_val + (int)(i*max_p*2 + j)) = 0;

    for(int i = 0; i < l;i++)
        for(int j = 0; j < w; j++)
            if(*(mat + i*w + j))
                    for(double arg = -90; arg < 90; arg++)
                    {
                        float radian = arg * (M_PI / 180.0);
                        int p = (int)(i*cos(radian) + j*sin(radian));


                        *(haugh_val + (int)((p + max_p)*180 + (arg+90))) +=1;
                    }
}

void haugh_traitement(int l, int w, int *mat)
{
    double max_p = l;
    double mat_size = 180*max_p*2;
    
    int* haugh_val = malloc(mat_size*sizeof(int));
    
    //haugh_transform(l, w, input, haugh_val);

    //récupération des équations

    free(haugh_val);
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
            else if((i*w + j)[matrix] < 62)
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
