#ifndef FLOOD_FILL_H
#define FLOOD_FILL_H
#include "dot.h"
int __flood_fill(int h, int w, int* matrix, struct dot* d, int c);
int* flood_fill(int h, int w, int* matrix);

#endif
