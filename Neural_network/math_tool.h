#pragma once
#include <string.h>

double sum(int s_index, double list[], size_t len);
double logloss(double as[], double ys[], size_t m);
double perceptron(double x1, double x2, double b, double w1, double w2);
double sigmoide(double z);
double *gradient(double *A, double *Y,double *X, size_t len);
void update(double *res,double* b,double *W, double learning_rate, size_t len);
