#ifndef NEURAL_LINK
#define NEURAL_LINK
#include <string.h>

double* Initialisation(size_t lenX);
void modele(double **X,double **W, double b, size_t lenXW,double A[]);


#endif
