#include <stdio.h>
#include "HT.h"
#include "filter.h"
#include <math.h>
#include <stdlib.h>

#include "LineParameter.h"
void print_lines(LineParameter* lines, int nb)
{
    for(int i = 0; i < nb; i++)
        printf("%f %f\n", (lines + i)->angle, (lines + i)->distance);
}

/*void free_cases()
{

}*/

int** detection(int* mat, int w, int h)
{
    for(int i =0; i<h;i++)
        for(int j =0; j<w;j++)
            *(mat +i*w +h) = !*(mat +i*w +h);

    int* nb_lines= malloc(sizeof(int));;
    *nb_lines = 20;
    struct LineParameter* detected_lines = malloc(sizeof(LineParameter)**nb_lines);

    HTLineDetection(mat, nb_lines, detected_lines, h, w);
    
    struct LineParameter* new_lines = FilterLines(detected_lines, 50, 8, nb_lines);
    //print_lines(new_lines, *nb_lines);
    printf("nb:%d\n",*nb_lines);
    free(nb_lines);
    free(detected_lines);
    return NULL;
}

