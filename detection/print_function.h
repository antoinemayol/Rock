#ifndef PRINT_FUNCTION_H
#define PRINT_FUNCTION_H
#include "LineParameter.h"

void print_lines(LineParameter* lines, int nb, int x1, int y1, int x2, int y2);
void print_case(int **coo, int* mat, int width);

void print_mat(int l, int w, int *matrix, int x1, int y1, int x2, int y2);
#endif
