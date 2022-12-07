#include <stdio.h>
#include "filter.h"
#include "HT.h"
#include "cut.h"
#include <math.h>
#include <stdlib.h>
#include "print_function.h"
#include "LineParameter.h"
#include "flood_fill.h"

int** detection(int* mat, int w, int h)
{
    int* lol = flood_fill(h, w, mat); 

    for(int i =0; i<h;i++)
        for(int j =0; j<w;j++)
            *(mat +i*w +h) = !*(mat +i*w +h);

    int* nb_lines= malloc(sizeof(int));
    *nb_lines = 20;
    struct LineParameter* detected_lines = malloc(sizeof(LineParameter)**nb_lines);

    HTLineDetection(mat, nb_lines, detected_lines, h, w);
    struct LineParameter* new_lines = FilterLines(detected_lines, 50, 8, nb_lines);
    
    free(nb_lines);
    free(detected_lines);

    int** cases = get_cases(h, w, mat, new_lines);

    free(new_lines);
    free(mat);
    return cases;
}

