#include <stdio.h>
#include "components_connexes.h"
#include "haugh_transform.h"
#include <math.h>
#include <stdlib.h>

int** detection(int* mat, int w, int h)
{
    int w2 = 0;
    int h2 = 0;
    int* output = connected_components(w,h,mat,&h2,&w2);
    int** cases = hough_traitement(h2, w2, output);

    free(output);
    return cases;
}

