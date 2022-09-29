#ifndef NEURAL_LINK
#define NEURAL_LINK
#include <string.h>

void Initialisation(double **X,size_t lenX,double W[][2]);
void modele(double **X,double **W, double b, size_t lenXW,double A[]);


#endif
