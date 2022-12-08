#ifndef CUT_H
#define CUT_H
#include "LineParameter.h"
double** stockage_cases(int** coo, int* matrix, int width, int** cases);

int** get_cases(int h, int w, int* matrix, struct LineParameter* lines);

#endif
