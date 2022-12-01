#ifndef OTSU_H
#define OTSU_H
#include "image.h"

void otsu(Image *image);
void sobel(Image *image);
double* initialize(int n);

#endif
