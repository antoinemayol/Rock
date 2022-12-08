#include <stdio.h>
#include "filter.h"
#include "HT.h"
#include "cut.h"
#include <math.h>
#include <stdlib.h>
#include "LineParameter.h"
#include "flood_fill.h"

int* extract_matrix(int l, int w, int *matrix, int x1, int y1, int x2, int y2)
{

    int h2 = x2 - x1;
    int w2 = y2 - y1;

    int* new_mat = malloc(sizeof(int)*h2*w2);
    for(int i = x1 ; i < x2 ; ++i)
    	for (int j = y1; j < y2; ++j)
            *(new_mat+ (i-x1)*w2 + (j-y1))=*(matrix + i*w + j);
    return new_mat;
}

int** detection(int* mat, int w, int h)
{

    int* tmp_mat = malloc(sizeof(int)*w*h);
    for(int i =  0; i < h; i++)
        for(int j = 0; j < w; j++)
            *(tmp_mat + i*w + j) = *(mat +i*w + j)==0?1:0;
    

    int* max_area = flood_fill(h, w, tmp_mat); 
    free(tmp_mat);

    int x1 = *(max_area);
    int y1 = *(max_area + 1);
    int x2 = *(max_area + 2);
    int y2 = *(max_area + 3);
    int* sudoku_mat = extract_matrix(h,w,mat,x1,y1,x2,y2);
    
    int* h2 = x2-x1;
    int* w2 = y2-y1;
    
    int* nb_lines= malloc(sizeof(int));
    *nb_lines = 20;
    struct LineParameter* detected_lines = malloc(sizeof(LineParameter)**nb_lines);
    detected_lines = HTLineDetection(sudoku_mat, nb_lines, detected_lines, h2, w2);
    struct LineParameter* new_lines = FilterLines(detected_lines, 50, 8, nb_lines);
     
    print_lines(new_lines, 4);
    int xa = (int)(new_lines + 0)->distance;
    int xb = (int)(new_lines + 0)->distance;
    int xc = (int)(new_lines + 2)->distance;
    int xd = (int)(new_lines + 2)->distance;
    int ya = (int)(new_lines + 1)->distance;
    int yb = (int)(new_lines + 3)->distance;
    int yc = (int)(new_lines + 1)->distance;
    int yd = (int)(new_lines + 3)->distance;
    //a en haut à gauche
    //b en haut à droite
    //c en bas à gauche
    free(nb_lines);
    free(detected_lines);

    //Homography avec les 4corners

    int** cases = get_cases(h, w, sudoku_mat, new_lines);

    free(new_lines);
    free(mat);
    return cases;
}

