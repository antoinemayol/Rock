#ifndef BLUR_H
#define BLUR_H

#include "image.h"

void convolution(Image *image, double **ker, int n);
void gaussian_blur(Image *image, int n);
double** generate_kernel(int n);

#endif
