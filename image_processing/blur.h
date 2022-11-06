#ifndef BLUR_H
#define BLUR_H

#include "image.h"

void generate_kernel(double ker[3][3]);
void blur(Image image, double ker[3][3]);

#endif
